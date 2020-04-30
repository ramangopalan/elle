
/*
 * Hacked by Raman Gopalan <ramangopalan@gmail.com>, Jan, 2020.
 * For Elle, the tiny, self hosted Lua machine.
 * Adapted from code at https://github.com/arduino-libraries/LiquidCrystal
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "lcd.h"
#include "dwt.h"
#include "ps2.h"

// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set: 
//    DL = 1; 8-bit interface data 
//    N = 0; 1-line display 
//    F = 0; 5x8 dot character font 
// 3. Display on/off control: 
//    D = 0; Display off 
//    C = 0; Cursor off 
//    B = 0; Blinking off 
// 4. Entry mode set: 
//    I/D = 1; Increment by 1 
//    S = 0; No shift 
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

/********************************************************************************
   INITIALIZATION FUNCTIONS
 *******************************************************************************/

static const DIGITAL_IO_t *data_pins[LCD_MAX_PHYSICAL_LINES] = {
  &LCD_DATA4_PIN,
  &LCD_DATA5_PIN,
  &LCD_DATA6_PIN,
  &LCD_DATA7_PIN,
  NULL,
  NULL,
  NULL,
  NULL,
};

void lcd_init_4bits_mode (lcd_t *l) {
  lcd_init(l,
           1,
		   &LCD_RS_PIN,
		   NULL,
		   &LCD_ENABLE_PIN,
		   data_pins);
}

void lcd_init (lcd_t *l, uint8_t four_bit_mode, const DIGITAL_IO_t *rs_pin, const DIGITAL_IO_t *rw_pin,
			   const DIGITAL_IO_t *enable_pin, const DIGITAL_IO_t *data_pins[]) {
  int i;

  /* Timer initialization */
  dwt_init();

  /* Pins */
  l->rs_pin        = rs_pin;
  l->rw_pin        = rw_pin;
  l->enable_pin    = enable_pin;
  for (i = 0; i < LCD_MAX_PHYSICAL_LINES; i++) {
    l->data_pins[i]  = data_pins[i];
  }

  if (four_bit_mode)
    l->display_function = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  else 
    l->display_function = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
  
  lcd_begin(l, LCD_COLS, LCD_ROWS, LCD_5x8DOTS);
  lcd_blink(l);
}

void lcd_begin (lcd_t *l, uint8_t cols, uint8_t lines, uint8_t dotsize) {
  if (lines > 1) {
    l->display_function |= LCD_2LINE;
  }
  l->num_lines = lines;

  lcd_set_row_offsets(l, 0x00, 0x40, 0x00 + cols, 0x40 + cols);

  /* For some 1 line displays you can select a 10 pixel high font */
  if ((dotsize != LCD_5x8DOTS) && (lines == 1)) {
    l->display_function |= LCD_5x10DOTS;
  }

  DIGITAL_IO_Init(l->rs_pin);
  // we can save 1 pin by not using RW. Indicate by passing NULL instead of pin#
  if (l->rw_pin != NULL) {
    DIGITAL_IO_Init(l->rw_pin);
  }
  DIGITAL_IO_Init(l->enable_pin);
  
  /* Do these once, instead of every time a character is drawn for speed reasons. */
  for (int i = 0; i < ((l->display_function & LCD_8BITMODE) ? 8U : 4U); ++i) {
    DIGITAL_IO_Init(l->data_pins[i]);
  }

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
  dwt_delay(50000);
  // Now we pull both RS and R/W low to begin commands
  DIGITAL_IO_SetOutputLow(l->rs_pin);
  DIGITAL_IO_SetOutputLow(l->enable_pin);
  if (l->rw_pin != NULL) {
    DIGITAL_IO_SetOutputLow(l->rw_pin);
  }
  
  //put the LCD into 4 bit or 8 bit mode
  if (!(l->display_function & LCD_8BITMODE)) {
    // this is according to the hitachi HD44780 datasheet
    // figure 24, pg 46

    // we start in 8bit mode, try to set 4 bit mode
    lcd_write4bits(l, 0x03);
    dwt_delay(4500); // wait min 4.1ms

    // second try
    lcd_write4bits(l, 0x03);
    dwt_delay(4500); // wait min 4.1ms
    
    // third go!
    lcd_write4bits(l, 0x03);
    dwt_delay(150);

    // finally, set to 4-bit interface
    lcd_write4bits(l, 0x02);
  } else {
    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    lcd_command(l, LCD_FUNCTIONSET | l->display_function);
    dwt_delay(4500);  // wait more than 4.1ms

    // second try
    lcd_command(l, LCD_FUNCTIONSET | l->display_function);
    dwt_delay(150);

    // third go
    lcd_command(l, LCD_FUNCTIONSET | l->display_function);
  }

  // finally, set # lines, font size, etc.
  lcd_command(l, LCD_FUNCTIONSET | l->display_function);

  // turn the display on with no cursor or blinking default
  l->display_control = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  lcd_display(l);

  // clear it off
  lcd_clear(l);

  // Initialize to default text direction (for romance languages)
  l->display_mode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  // set the entry mode
  lcd_command(l, LCD_ENTRYMODESET | l->display_mode);

  /* Fill the terminal buffer with spaces and initialize */
  for (int y = 0; y < lines; ++y) {
    for (int x = 0; x < cols; ++x) {
      l->fb.m_buffer[y][x] = ' ';
    }
  }

  terminal_init(l, cols, lines);
}

void lcd_set_row_offsets (lcd_t *l, int row0, int row1, int row2, int row3) {
  l->row_offsets[0] = row0;
  l->row_offsets[1] = row1;
  l->row_offsets[2] = row2;
  l->row_offsets[3] = row3;
}

/********************************************************************************
   USER FUNCTIONS
 *******************************************************************************/

void lcd_clear (lcd_t *l) {
  lcd_command(l, LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
  dwt_delay(2000);  // this command takes a long time!
}

void lcd_home (lcd_t *l) {
  lcd_command(l, LCD_RETURNHOME);  // set cursor position to zero
  dwt_delay(2000);  // this command takes a long time!
}

void lcd_set_cursor (lcd_t *l, uint8_t col, uint8_t row) {
  const size_t max_lines = sizeof(l->row_offsets) / sizeof(*l->row_offsets);
  if (row >= max_lines) {
    row = max_lines - 1;    // we count rows starting w/0
  }
  if (row >= l->num_lines) {
    row = l->num_lines - 1;    // we count rows starting w/0
  }
  
  lcd_command(l, LCD_SETDDRAMADDR | (col + l->row_offsets[row]));
}

// Turn the display on/off (quickly)
void lcd_no_display (lcd_t *l) {
  l->display_control &= ~LCD_DISPLAYON;
  lcd_command(l, LCD_DISPLAYCONTROL | l->display_control);
}

void lcd_display (lcd_t *l) {
  l->display_control |= LCD_DISPLAYON;
  lcd_command(l, LCD_DISPLAYCONTROL | l->display_control);
}

// Turns the underline cursor on/off
void lcd_no_cursor (lcd_t *l) {
  l->display_control &= ~LCD_CURSORON;
  lcd_command(l, LCD_DISPLAYCONTROL | l->display_control);
}

void lcd_cursor (lcd_t *l) {
  l->display_control |= LCD_CURSORON;
  lcd_command(l, LCD_DISPLAYCONTROL | l->display_control);
}

// Turn on and off the blinking cursor
void lcd_no_blink (lcd_t *l) {
  l->display_control &= ~LCD_BLINKON;
  lcd_command(l, LCD_DISPLAYCONTROL | l->display_control);
}

void lcd_blink (lcd_t *l) {
  l->display_control |= LCD_BLINKON;
  lcd_command(l, LCD_DISPLAYCONTROL | l->display_control);
}

// These commands scroll the display without changing the RAM
void lcd_scroll_display_left (lcd_t *l) {
  lcd_command(l, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void lcd_scroll_display_right (lcd_t *l) {
  lcd_command(l, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void lcd_left_to_right (lcd_t *l) {
  l->display_mode |= LCD_ENTRYLEFT;
  lcd_command(l, LCD_ENTRYMODESET | l->display_mode);
}

// This is for text that flows Right to Left
void lcd_right_to_left (lcd_t *l) {
  l->display_mode &= ~LCD_ENTRYLEFT;
  lcd_command(l, LCD_ENTRYMODESET | l->display_mode);
}

// This will 'right justify' text from the cursor
void lcd_autoscroll (lcd_t *l) {
  l->display_mode |= LCD_ENTRYSHIFTINCREMENT;
  lcd_command(l, LCD_ENTRYMODESET | l->display_mode);
}

// This will 'left justify' text from the cursor
void lcd_no_autoscroll (lcd_t *l) {
  l->display_mode &= ~LCD_ENTRYSHIFTINCREMENT;
  lcd_command(l, LCD_ENTRYMODESET | l->display_mode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void lcd_create_char (lcd_t *l, uint8_t location, uint8_t charmap[]) {
  uint32_t i;
  location &= 0x7; // we only have 8 locations 0-7
  lcd_command(l, LCD_SETCGRAMADDR | (location << 3));
  for (i = 0; i < 8; i++) {
    lcd_write(l, charmap[i]);
  }
}

void lcd_echo (lcd_t *l, uint8_t *s) {
  uint32_t len, i;

  len = strlen((const char *)s);
  if (s == NULL)
    return;
  for (i = 0; i < len; i++)
    lcd_write(l, *(s + i));
}

/********************************************************************************
   MID LEVEL FUNCTIONS (FOR SENDING DATA/COMMANDS)
 *******************************************************************************/

inline void lcd_command (lcd_t *l, uint8_t value) {
  lcd_send(l, value, 0U);
}

inline size_t lcd_write (lcd_t *l, uint8_t value) {
  lcd_send(l, value, 1U);
  return 1; // assume success
}

/********************************************************************************
   LOW LEVEL DATA PUSHING FUNCTIONS
 *******************************************************************************/

/* Write either command or data, with automatic 4/8-bit selection */
void lcd_send (lcd_t *l, uint8_t value, uint8_t mode) {
  if (mode)
    DIGITAL_IO_SetOutputHigh(l->rs_pin);
  else
    DIGITAL_IO_SetOutputLow(l->rs_pin);

  // If there is a RW pin indicated, set it low to write
  if (l->rw_pin != NULL) {
    DIGITAL_IO_SetOutputLow(l->rw_pin);
  }
  
  if (l->display_function & LCD_8BITMODE) {
    lcd_write8bits(l, value);
  } else {
    lcd_write4bits(l, value >> 4);
    lcd_write4bits(l, value);
  }
}

void lcd_pulse_enable (lcd_t *l) {
  DIGITAL_IO_SetOutputLow(l->enable_pin);
  dwt_delay(1);
  DIGITAL_IO_SetOutputHigh(l->enable_pin);
  dwt_delay(1);    // enable pulse must be >450ns
  DIGITAL_IO_SetOutputLow(l->enable_pin);
  dwt_delay(100);   // commands need > 37us to settle
}

void lcd_write4bits (lcd_t *l, uint8_t value) {
  uint32_t i;

  for (i = 0; i < 4; i++) {
    if ((value >> i) & 0x01)
      DIGITAL_IO_SetOutputHigh(l->data_pins[i]);
    else
      DIGITAL_IO_SetOutputLow(l->data_pins[i]);
  }

  lcd_pulse_enable(l);
}

void lcd_write8bits (lcd_t *l, uint8_t value) {
  uint32_t i;

  for (i = 0; i < 8; i++) {
    if ((value >> i) & 0x01)
      DIGITAL_IO_SetOutputHigh(l->data_pins[i]);
    else
      DIGITAL_IO_SetOutputLow(l->data_pins[i]);
  }
  
  lcd_pulse_enable(l);
}

/********************************************************************************
   APPLICATION FUNCTIONS
 *******************************************************************************/

/** Copy the framebuffer to the LCD */
void sync_buffer (lcd_t *l) {
  for (int y = 0; y < HEIGHT; ++y) {
    lcd_set_cursor(l, 0, y);
    for (int x = 0; x < WIDTH; ++x) {
      lcd_write(l, l->fb.m_buffer[y][x]);
    }
  }
}

/** Scroll up one line */
void scroll_up (lcd_t *l) {
  for (int y = 0; y < HEIGHT - 1; ++y) {
    memcpy(l->fb.m_buffer[y], l->fb.m_buffer[y + 1], WIDTH);
  }
  memset(l->fb.m_buffer[HEIGHT - 1], ' ', WIDTH);
  sync_buffer(l);
}

void next_row (lcd_t *l) {
  l->fb.m_cursor_x = 0;
  l->fb.m_cursor_y += 1;

  if (l->fb.m_cursor_y >= HEIGHT) {
    scroll_up(l);
    l->fb.m_cursor_y = HEIGHT - 1;
  }
  lcd_set_cursor(l, l->fb.m_cursor_x, l->fb.m_cursor_y);
}

void set_cursor (lcd_t *l, int x, int y) {
  l->fb.m_cursor_x = x;
  l->fb.m_cursor_y = y;
  lcd_set_cursor(l, x, y);
}

void move_cursor (lcd_t *l, int dx, int dy) {
  l->fb.m_cursor_x += dx;
  l->fb.m_cursor_y += dy;

  if (l->fb.m_cursor_x < 0)
    l->fb.m_cursor_x = 0;
  else if (l->fb.m_cursor_x >= WIDTH)
    l->fb.m_cursor_x = WIDTH - 1;

  if (l->fb.m_cursor_y < 0)
    l->fb.m_cursor_y = 0;
  else if (l->fb.m_cursor_y >= HEIGHT)
    l->fb.m_cursor_y = HEIGHT - 1;

  lcd_set_cursor(l, l->fb.m_cursor_x, l->fb.m_cursor_y);
}

void insert (lcd_t *l, char c) {
  if (l->fb.m_cursor_x >= WIDTH) {
    next_row(l);
  }

  lcd_write(l, c);
  l->fb.m_buffer[l->fb.m_cursor_y][l->fb.m_cursor_x] = c;
  l->fb.m_cursor_x += 1;
}

void newline (lcd_t *l) {
  next_row(l);
}

void carriage_return (lcd_t *l) {
  l->fb.m_cursor_x = 0;
  lcd_set_cursor(l, l->fb.m_cursor_x, l->fb.m_cursor_y);
}

void clear (lcd_t *l) {
  lcd_clear(l);
  l->fb.m_cursor_x = 0;
  l->fb.m_cursor_y = 0;
  lcd_set_cursor(l, l->fb.m_cursor_x, l->fb.m_cursor_y);
  for (int y = 0; y < HEIGHT; ++y) {
    memset(l->fb.m_buffer[y], ' ', WIDTH);
  }
}

void backspace (lcd_t *l) {
  if (l->fb.m_cursor_x == 0) {
	if (l->fb.m_cursor_y > 0) {
      move_cursor(l, WIDTH - 1, -1);
	} else {
      move_cursor(l, 0, -1);
	}
  } else {
    move_cursor(l, -1, 0);
  }

  l->fb.m_buffer[l->fb.m_cursor_y][l->fb.m_cursor_x] = ' ';
  sync_buffer(l);
  lcd_set_cursor(l, l->fb.m_cursor_x, l->fb.m_cursor_y);

}

void terminal_init (lcd_t *l, int w, int h) {
  l->t.m_width = w;
  l->t.m_height = h;
  l->t.m_ctrl_idx = 0;
  l->t.m_state = K_INITIAL;
}

void terminal_reset (lcd_t *l) {
  /* Nothing here for now */
}

void put_initial (lcd_t *l, char c) {
  switch (c) {
    case 27:
      l->t.m_state = K_ESCAPE;
      break;
    case '\n':
      newline(l);
      break;
    case '\r':
      carriage_return(l);
      break;
    case '\t':
      for (int i = 0; i < 8; ++i) {
        insert(l, ' ');
      }
      break;
    case PS2_BACKSPACE: /* Backspace */
      backspace(l);
      break;
    default:
      insert(l, c);
      break;
  }
}

void put_escape (lcd_t *l, char c) {
  switch (c) {
    case '[':
      l->t.m_state = K_CONTROL_SEQUENCE;
      l->t.m_ctrl_idx = 0;
      // FIXME: clear ctrl_seq
      l->t.m_ctrl_seq[l->t.m_ctrl_idx] = 0;
      break;
    case 'c':
      terminal_reset(l);
      break;
    default:
      break;
  }
}

void put_control_sequence (lcd_t *l, char c) {
  if (c == ';') {
    if (l->t.m_ctrl_idx < 15) {
      l->t.m_ctrl_idx += 1;
      l->t.m_ctrl_seq[l->t.m_ctrl_idx] = 0;
    } else {
      l->t.m_state = K_INITIAL;
    }
  } else if ('0' <= c && c <= '9') {
    l->t.m_ctrl_seq[l->t.m_ctrl_idx] *= 10;
    l->t.m_ctrl_seq[l->t.m_ctrl_idx] = c - '0';
  } else {
    switch (c) {
      case '@':
        // Insert the indicated # of blank characters.
        break;
      case 'A':
        // Move cursor up the indicated # of rows.
        move_cursor(l, 0, -l->t.m_ctrl_seq[0]);
        break;
      case 'B':
        // Move cursor down the indicated # of rows.
        move_cursor(l, 0, l->t.m_ctrl_seq[0]);
        break;
      case 'C':
        // Move cursor right the indicated # of columns.
        move_cursor(l, l->t.m_ctrl_seq[0], 0);
        break;
      case 'D':
        // Move cursor left the indicated # of columns.
        move_cursor(l, -l->t.m_ctrl_seq[0], 0);
        break;
      case 'E':
        // Move cursor down the indicated # of rows, to column 1.
        break;
      case 'F':
        // Move cursor up the indicated # of rows, to column 1.
        break;
      case 'G':
        // Move cursor to indicated column in current row.
        break;
      case 'H':
        // Move cursor to the indicated row, column (origin at 1,1).
        set_cursor(l, l->t.m_ctrl_seq[0] - 1, l->t.m_ctrl_seq[1] - 1);
        break;
      case 'J':
        // Erase display (default: from cursor to end of display).
        // ESC [ 1 J: erase from start to cursor.
        // ESC [ 2 J: erase whole display.
        // ESC [ 3 J: erase whole display including scroll-back buffer (since Linux 3.0).
        if (l->t.m_ctrl_seq[0] == 1) {
        } else if (l->t.m_ctrl_seq[0] == 2) {
          clear(l);
        } else if (l->t.m_ctrl_seq[0] == 3) {
          clear(l);
        }
        break;
      case 'K':
        // Erase line (default: from cursor to end of line).
        // ESC [ 1 K: erase from start of line to cursor.
        // ESC [ 2 K: erase whole line.
        break;
      case 'L': // Insert the indicated # of blank lines.
        break;
      case 'M':
        // Delete the indicated # of lines.
        break;
      case 'P':
        // Delete the indicated # of characters on current line.
        break;
      case 'X':
        // Erase the indicated # of characters on current line.
        break;
      case 'a':
        // Move cursor right the indicated # of columns.
        break;
      case 'c':
        // Answer ESC [ ? 6 c: "I am a VT102".
        break;
      case 'd':
        // Move cursor to the indicated row, current column.
        break;
      case 'e':
        // Move cursor down the indicated # of rows.
        break;
      case 'f':
        // Move cursor to the indicated row, column.
        break;
      case 'g':
        // Without parameter: clear tab stop at current position.
        //ESC [ 3 g: delete all tab stops.
        break;
      case 'h':
        // Set Mode (see below).
        break;
      case 'l':
        // Reset Mode (see below).
        break;
      case 'm':
        // Set attributes (see below).
        break;
      case 'n':
        // Status report (see below).
        break;
      case 'q': // Set keyboard LEDs.
        break;
      case 'r':
        // DECSTBM   Set scrolling region; parameters are top and bottom row.
        break;
      case 's':
        // Save cursor location.
        break;
      case 'u':
        // Restore cursor location.
        break;
      case '`':
        // Move cursor to indicated column in current row.
        break;
      default:
        break;
    }
    l->t.m_state = K_INITIAL;
  }
}

void terminal_put_char (lcd_t *l, char c) {
  switch (l->t.m_state) {
    case K_INITIAL:
      put_initial(l, c);
      break;
    case K_ESCAPE:
      put_escape(l, c);
      break;
    case K_CONTROL_SEQUENCE:
      put_control_sequence(l, c);
      break;
  }
}

void terminal_print (lcd_t *l, const char* text) {
  while (*text) {
    terminal_put_char(l, *text++);
  }
}

