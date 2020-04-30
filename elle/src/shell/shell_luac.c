// Shell: 'luac' implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <elle/inc/shell.h>
#include <elle/inc/common.h>
#include <elle/src/platform/xmc4700/type.h>
#include <elle/src/platform/xmc4700/platform_conf.h>

const char shell_help_luac[] = "[-e <stat>] [-l <name>] [-i] [-v] [<script>]\n"
  "  [<script>]: execute the given script.\n"
  "  [-e <stat>]: execute string 'stat'.\n"
  "  [-l <name>]: require library 'name'.\n"
  "  [-i]: enter interactive mode after executing 'script'.\n"
  "  [-v]: show version information.\n"
  "Without arguments it executes the interactive Lua interpreter.\n";
const char shell_help_summary_luac[] = "invoke the Lua byte-code compiler";

void shell_luac( int argc, char **argv )
{
  luac_main( argc, argv );
}

