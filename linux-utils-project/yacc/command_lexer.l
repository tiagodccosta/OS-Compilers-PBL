%{
#include <string.h>
#include "y.tab.h"
#include "command.h"

extern YYSTYPE yylval;
%}

%%
"ls"                    { return CMD_LS; }
"pwd"                   { return CMD_PWD; }
"head"                  { return CMD_HEAD; }
"tail"                  { return CMD_TAIL; }
"mkdir"                 { return CMD_MKDIR; }
"rmdir"                 { return CMD_RMDIR; }
"find"                  { return CMD_FIND; }

"-a"                    { return OPT_ALL; }
"-l"                    { return OPT_LONG; }
"-r"                    { return OPT_REVERSE; }
"-L"                    { return OPT_LOGICAL; }
"-P"                    { return OPT_PHYSICAL; }
"--help"                { return OPT_HELP; }
"-n"                    { return OPT_LINES; }
"-c"                    { return OPT_BYTES; }
"-q"                    { return OPT_QUIET; }
"-f"                    { return OPT_FOLLOW; }
"-p"                    { return OPT_PARENTS; }
"-v"                    { return OPT_VERBOSE; }
"-m"                    { return OPT_MODE; }
"--ignore-fail-on-non-empty" { return OPT_IGNORE; }
"-name"                 { return OPT_NAME; }
"-type"                 { return OPT_TYPE; }
"-size"                 { return OPT_SIZE; }

[0-9]+                  { 
                          yylval.num_value = atoi(yytext); 
                          return NUMBER; 
                        }

[a-zA-Z0-9./_*?]+       { 
                          yylval.str_value = strdup(yytext);
                          return STRING; 
                        }

[ \t]+                  ; /* ignore whitespace */

\n                      { return NEWLINE; }

.                       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}