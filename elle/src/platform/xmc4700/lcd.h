#ifndef LCD_H_
#define LCD_H_

/*
 * Hacked by Raman Gopalan <ramangopalan@gmail.com>, Jan, 2020.
 * For Elle, the tiny, self hosted Lua machine.
 * Adapted from code at https://github.com/arduino-libraries/LiquidCrystal
 */

#include <inttypes.h>
#include <DAVE.h>
#include "dwt.h"

/* Number of rows and columns */
#define LCD_COLS                   (20U)
#define LCD_ROWS                   (4U)
#define HEIGHT                     (LCD_ROWS)
#define WIDTH                      (LCD_COLS)

#define LCD_MAX_PHYSICAL_LINES     (8U)

/* Commands */
#define LCD_CLEARDISPLAY           (0x01)
#define LCD_RETURNHOME             (0x02)
#define LCD_ENTRYMODESET           (0x04)
#define LCD_DISPLAYCONTROL         (0x08)
#define LCD_CURSORSHIFT            (0x10)
#define LCD_FUNCTIONSET            (0x20)
#define LCD_SETCGRAMADDR           (0x40)
#define LCD_SETDDRAMADDR           (0x80)

/* Flags for display entry mode */
#define LCD_ENTRYRIGHT             (0x00)
#define LCD_ENTRYLEFT              (0x02)
#define LCD_ENTRYSHIFTINCREMENT    (0x01)
#define LCD_ENTRYSHIFTDECREMENT    (0x00)

/* Flags for display on/off control */
#define LCD_DISPLAYON              (0x04)
#define LCD_DISPLAYOFF             (0x00)
#define LCD_CURSORON               (0x02)
#define LCD_CURSOROFF              (0x00)
#define LCD_BLINKON                (0x01)
#define LCD_BLINKOFF               (0x00)

/* Flags for display/cursor shift */
#define LCD_DISPLAYMOVE            (0x08)
#define LCD_CURSORMOVE             (0x00)
#define LCD_MOVERIGHT              (0x04)
#define LCD_MOVELEFT               (0x00)

/* Flags for function set */
#define LCD_8BITMODE               (0x10)
#define LCD_4BITMODE               (0x00)
#define LCD_2LINE                  (0x08)
#define LCD_1LINE                  (0x00)
#define LCD_5x10DOTS               (0x04)
#define LCD_5x8DOTS                (0x00)

#define LCD_ECHO(s)                lcd_echo(&lcd, (uint8_t *)s)

/********************************************************************************
   ENUMERATIONS
 *******************************************************************************/

typedef enum TERMINAL_STATE_t {
  K_INITIAL,
  K_ESCAPE,
  K_CONTROL_SEQUENCE
} TERMINAL_STATE_t;

/********************************************************************************
   STRUCTURES
 *******************************************************************************/

typedef struct frame_buffer_t {
  int m_cursor_x;
  int m_cursor_y;
  char m_buffer[HEIGHT][WIDTH];
} frame_buffer_t;

typedef struct terminal_t {
  int m_width;
  int m_height;
  int m_ctrl_seq[16];
  int m_ctrl_idx;
  TERMINAL_STATE_t m_state;
} terminal_t;

typedef struct lcd_t {
  const DIGITAL_IO_t *rs_pin, *rw_pin, *enable_pin;
  const DIGITAL_IO_t *data_pins[8];
  uint8_t display_function;
  uint8_t display_control;
  uint8_t display_mode;
  uint8_t initialized;
  uint8_t num_lines;
  uint8_t row_offsets[4];
  frame_buffer_t fb;
  terminal_t t;
} lcd_t;

/********************************************************************************
   FUNCTION PROTOTYPES
 *******************************************************************************/

/* LCD system commands */
void lcd_set_row_offsets (lcd_t *l, int row0, int row1, int row2, int row3);
void lcd_set_cursor (lcd_t *l, uint8_t col, uint8_t row);
size_t lcd_write (lcd_t *l, uint8_t value);
void lcd_command (lcd_t *l, uint8_t value);
void lcd_send (lcd_t *l, uint8_t value, uint8_t mode);
void lcd_write4bits (lcd_t *l, uint8_t value);
void lcd_write8bits (lcd_t *l, uint8_t value);
void lcd_pulse_enable (lcd_t *l);
void lcd_begin (lcd_t *l, uint8_t cols, uint8_t lines, uint8_t dotsize);
void lcd_create_char (lcd_t *l, uint8_t location, uint8_t charmap[]);

/* LCD user commands, I would hope */
void lcd_clear (lcd_t *l);
void lcd_home (lcd_t *l);
void lcd_no_display (lcd_t *l);
void lcd_display (lcd_t *l);
void lcd_no_blink (lcd_t *l);
void lcd_blink (lcd_t *l);
void lcd_no_cursor (lcd_t *l);
void lcd_cursor (lcd_t *l);
void lcd_scroll_display_left (lcd_t *l);
void lcd_scroll_display_right (lcd_t *l);
void lcd_left_to_right (lcd_t *l);
void lcd_right_to_left (lcd_t *l);
void lcd_autoscroll (lcd_t *l);
void lcd_no_autoscroll (lcd_t *l);
void lcd_init (lcd_t *l,
               uint8_t four_bit_mode,
			   const DIGITAL_IO_t *rs_pin,
			   const DIGITAL_IO_t *rw_pin,
			   const DIGITAL_IO_t *enable_pin,
			   const DIGITAL_IO_t *data_pins[]);
void lcd_init_4bits_mode (lcd_t *l);
void lcd_echo (lcd_t *l, uint8_t *s);
void terminal_init (lcd_t *l, int w, int h);
void terminal_put_char (lcd_t *l, char c);
void clear (lcd_t *l);

#endif /* #ifndef LCD_H_ */
