// Shell: 'mkdir' implementation

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

const char shell_help_mkdir[] = "<path>\n"
  "  <path>: the directory to create.\n";
const char shell_help_summary_mkdir[] = "create directories";

void shell_mkdir( int argc, char **argv )
{
  if( argc != 2 )
  {
    SHELL_SHOW_HELP( mkdir );
    return;
  }
  if( mkdir( argv[ 1 ], 0 ) != 0 )
    printf( "Error creating directory '%s'\n", argv[ 1 ] );
  printf( "Created directory '%s'.\n", argv[ 1 ] );
}

