// Shell: 'recv' implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "elle/inc/shell.h"
#include "elle/inc/common.h"
#include "elle/src/platform/xmc4700/type.h"
#include "elle/src/platform/xmc4700/platform_conf.h"

#ifdef BUILD_EDITOR_ED

/* All functions shall return :) */
extern int ed_main( int argc, char ** argv );

const char shell_help_ed[] = "[<get-to-this-later>]\n";
const char shell_help_summary_ed[] = "edit a file with a GNU ed";

void shell_ed( int argc, char **argv )
{
  ed_main(argc,argv);
}

#else // #ifdef BUILD_EDITOR_ED

const char shell_help_ed[] = "";
const char shell_help_summary_ed[] = "";

void shell_ed( int argc, char **argv )
{
  shellh_not_implemented_handler( argc, argv );
}

#endif // #ifdef BUILD_EDITOR_ED

