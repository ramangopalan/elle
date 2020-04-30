// Shell: 'clear' implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <elle/inc/common.h>
#include <elle/inc/shell.h>
#include <elle/src/platform/xmc4700/platform_conf.h>
#include <elle/src/platform/xmc4700/type.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <elle/inc/term.h>
#include <elle/src/platform/xmc4700/lcd.h>

const char shell_help_clear[] = "\n"
  "Clears the working screen.\n";
const char shell_help_summary_clear[] = "clear screen";

extern lcd_t lcd;

void shell_clear( int argc, char **argv )
{
#if defined (BUILD_ELLE_SELF_HOSTED_MACHINE)
  clear(&lcd);
#else
  term_ansi("2J");
  term_ansi("%u;%uH", 0, 0);
#endif
}

