#ifndef COMMAND_H
#define COMMAND_H

#include "y.tab.h"

typedef struct {
    int command;
    
    // ls options
    int ls_all;
    int ls_long;
    int ls_reverse;
    
    // pwd options
    int pwd_logical;
    int pwd_physical;
    int pwd_help;
    
    // head options
    int head_lines;
    int head_bytes;
    int head_quiet;
    
    // tail options
    int tail_lines;
    int tail_follow;
    int tail_quiet;
    
    // mkdir options
    int mkdir_parents;
    int mkdir_verbose;
    char *mkdir_mode;
    
    // rmdir options
    int rmdir_parents;
    int rmdir_verbose;
    int rmdir_ignore;
    
    // find options
    char *find_path;
    char *find_name;
    char find_type;
    int find_size;
    
} CommandInfo;

extern CommandInfo cmd_info;
extern char **arg_array;
extern int arg_count;

void init_command_info();
void add_argument(char *arg);

#endif