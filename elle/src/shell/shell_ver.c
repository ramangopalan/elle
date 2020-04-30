// Shell: 'ver' implementation

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

#if defined( USE_GIT_REVISION )
#include "git_version.h"
#else
#include <elle/inc/version.h>
#endif

const char shell_help_ver[] = "\n"
  "This displays the git revision of the tree used to build Elle or an official version number if applicable.\n";
const char shell_help_summary_ver[] = "show version information";

void shell_ver( int argc, char **argv )
{
  if( argc != 1 )
  {
    SHELL_SHOW_HELP( ver );
    return;
  }
  printf( "Elle %s\n", ELUA_STR_VERSION );
}

