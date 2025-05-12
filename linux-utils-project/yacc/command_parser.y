%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "command.h"

extern int yylex();
void yyerror(const char *s);

CommandInfo cmd_info;
char **arg_array = NULL;
int arg_count = 0;
int max_args = 10;

void init_command_info() {
    memset(&cmd_info, 0, sizeof(CommandInfo));
    arg_array = malloc(max_args * sizeof(char*));
    arg_count = 0;
}

void add_argument(char *arg) {
    if (arg_count >= max_args - 1) {
        max_args *= 2;
        arg_array = realloc(arg_array, max_args * sizeof(char*));
    }
    arg_array[arg_count++] = arg;
    arg_array[arg_count] = NULL;  // Always NULL-terminate
}

%}

%union {
    int num_value;
    char *str_value;
}

%token CMD_LS CMD_PWD CMD_HEAD CMD_TAIL CMD_MKDIR CMD_RMDIR CMD_FIND
%token OPT_ALL OPT_LONG OPT_REVERSE OPT_LOGICAL OPT_PHYSICAL OPT_HELP
%token OPT_LINES OPT_BYTES OPT_QUIET OPT_FOLLOW OPT_PARENTS OPT_VERBOSE
%token OPT_MODE OPT_IGNORE OPT_NAME OPT_TYPE OPT_SIZE
%token NEWLINE
%token <num_value> NUMBER
%token <str_value> STRING

%%

command:
    ls_command
    | pwd_command
    | head_command
    | tail_command
    | mkdir_command
    | rmdir_command
    | find_command
    | NEWLINE { return 0; }
    ;

ls_command:
    CMD_LS ls_opts ls_args { 
        cmd_info.command = CMD_LS; 
        return 1; 
    }
    ;

ls_opts:
    | ls_opts OPT_ALL { 
        cmd_info.ls_all = 1; 
        add_argument("-a");
    }
    | ls_opts OPT_LONG { 
        cmd_info.ls_long = 1; 
        add_argument("-l");
    }
    | ls_opts OPT_REVERSE { 
        cmd_info.ls_reverse = 1; 
        add_argument("-r");
    }
    ;

ls_args:
    | ls_args STRING { 
        add_argument($2);
    }
    ;

pwd_command:
    CMD_PWD pwd_opts { 
        cmd_info.command = CMD_PWD; 
        return 1; 
    }
    ;

pwd_opts:
    | pwd_opts OPT_LOGICAL { 
        cmd_info.pwd_logical = 1; 
        add_argument("-L");
    }
    | pwd_opts OPT_PHYSICAL { 
        cmd_info.pwd_physical = 1; 
        add_argument("-P");
    }
    | pwd_opts OPT_HELP { 
        cmd_info.pwd_help = 1; 
        add_argument("--help");
    }
    ;

head_command:
    CMD_HEAD head_opts head_args { 
        cmd_info.command = CMD_HEAD; 
        return 1; 
    }
    ;

head_opts:
    | head_opts OPT_LINES NUMBER { 
        cmd_info.head_lines = $3; 
        add_argument("-n");
        char num_str[20];
        sprintf(num_str, "%d", $3);
        add_argument(strdup(num_str));
    }
    | head_opts OPT_BYTES NUMBER { 
        cmd_info.head_bytes = $3; 
        add_argument("-c");
        char num_str[20];
        sprintf(num_str, "%d", $3);
        add_argument(strdup(num_str));
    }
    | head_opts OPT_QUIET { 
        cmd_info.head_quiet = 1; 
        add_argument("-q");
    }
    ;

head_args:
    | head_args STRING { 
        add_argument($2);
    }
    ;

tail_command:
    CMD_TAIL tail_opts tail_args { 
        cmd_info.command = CMD_TAIL; 
        return 1; 
    }
    ;

tail_opts:
    | tail_opts OPT_LINES NUMBER { 
        cmd_info.tail_lines = $3; 
        add_argument("-n");
        char num_str[20];
        sprintf(num_str, "%d", $3);
        add_argument(strdup(num_str));
    }
    | tail_opts OPT_FOLLOW { 
        cmd_info.tail_follow = 1; 
        add_argument("-f");
    }
    | tail_opts OPT_QUIET { 
        cmd_info.tail_quiet = 1; 
        add_argument("-q");
    }
    ;

tail_args:
    | tail_args STRING { 
        add_argument($2);
    }
    ;

mkdir_command:
    CMD_MKDIR mkdir_opts mkdir_args { 
        cmd_info.command = CMD_MKDIR; 
        return 1; 
    }
    ;

mkdir_opts:
    | mkdir_opts OPT_PARENTS { 
        cmd_info.mkdir_parents = 1; 
        add_argument("-p");
    }
    | mkdir_opts OPT_VERBOSE { 
        cmd_info.mkdir_verbose = 1; 
        add_argument("-v");
    }
    | mkdir_opts OPT_MODE STRING { 
        cmd_info.mkdir_mode = strdup($3); 
        add_argument("-m");
        add_argument($3);
    }
    ;

mkdir_args:
    STRING { 
        add_argument($1);
    }
    | mkdir_args STRING { 
        add_argument($2);
    }
    ;

rmdir_command:
    CMD_RMDIR rmdir_opts rmdir_args { 
        cmd_info.command = CMD_RMDIR; 
        return 1; 
    }
    ;

rmdir_opts:
    | rmdir_opts OPT_PARENTS { 
        cmd_info.rmdir_parents = 1; 
        add_argument("-p");
    }
    | rmdir_opts OPT_VERBOSE { 
        cmd_info.rmdir_verbose = 1; 
        add_argument("-v");
    }
    | rmdir_opts OPT_IGNORE { 
        cmd_info.rmdir_ignore = 1; 
        add_argument("--ignore-fail-on-non-empty");
    }
    ;

rmdir_args:
    STRING { 
        add_argument($1);
    }
    | rmdir_args STRING { 
        add_argument($2);
    }
    ;

find_command:
    CMD_FIND find_path find_opts { 
        cmd_info.command = CMD_FIND; 
        return 1; 
    }
    ;

find_path:
    | STRING { 
        cmd_info.find_path = strdup($1); 
        add_argument($1);
    }
    ;

find_opts:
    | find_opts OPT_NAME STRING { 
        cmd_info.find_name = strdup($3); 
        add_argument("-name");
        add_argument($3);
    }
    | find_opts OPT_TYPE STRING { 
        cmd_info.find_type = $3[0]; 
        add_argument("-type");
        add_argument($3);
    }
    | find_opts OPT_SIZE NUMBER { 
        cmd_info.find_size = $3; 
        add_argument("-size");
        char num_str[20];
        sprintf(num_str, "%d", $3);
        add_argument(strdup(num_str));
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}