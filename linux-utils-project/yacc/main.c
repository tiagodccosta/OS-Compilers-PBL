// filepath: /Users/tiagodccosta/Desktop/PBL OS-Compiladores/linux-utils-project/yacc/main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "y.tab.h"
#include "command.h"

extern int yyparse();
extern FILE *yyin;

char* get_command_path(int cmd, const char *base_dir) {
    char *path = malloc(1024);
    
    switch (cmd) {
        case CMD_LS:
            sprintf(path, "%s/ls/ls", base_dir);
            break;
        case CMD_PWD:
            sprintf(path, "%s/pwd/pwd", base_dir);
            break;
        case CMD_HEAD:
            sprintf(path, "%s/head/head", base_dir);
            break;
        case CMD_TAIL:
            sprintf(path, "%s/tail/tail", base_dir);
            break;
        case CMD_MKDIR:
            sprintf(path, "%s/mkdir/mkdir", base_dir);
            break;
        case CMD_RMDIR:
            sprintf(path, "%s/rmdir/rmdir", base_dir);
            break;
        case CMD_FIND:
            sprintf(path, "%s/find/find", base_dir);
            break;
        default:
            free(path);
            return NULL;
    }
    
    return path;
}

int main(int argc, char *argv[]) {
    char command_buffer[1024] = {0};
    char *base_dir = NULL;
    
    if (argc > 1) {
        base_dir = argv[1];
    } else {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            base_dir = cwd;
        } else {
            perror("getcwd");
            return EXIT_FAILURE;
        }
    }
    
    if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            strcat(command_buffer, argv[i]);
            if (i < argc - 1) {
                strcat(command_buffer, " ");
            }
        }
    } else {
        printf("Enter command: ");
        if (fgets(command_buffer, sizeof(command_buffer), stdin) == NULL) {
            return EXIT_FAILURE;
        }
    }
    
    FILE *cmd_stream = fmemopen(command_buffer, strlen(command_buffer), "r");
    if (!cmd_stream) {
        perror("fmemopen");
        return EXIT_FAILURE;
    }
    
    yyin = cmd_stream;
    init_command_info();
    int result = yyparse();
    fclose(cmd_stream);
    
    if (result == 1) {
        char *cmd_path = get_command_path(cmd_info.command, base_dir);
        if (cmd_path) {
            printf("Executing: %s\n", cmd_path);
            // Execute the command with the arguments
            execv(cmd_path, arg_array);
            
            perror("execv");
            free(cmd_path);
            return EXIT_FAILURE;
        } else {
            fprintf(stderr, "Unknown command\n");
        }
    } else {
        fprintf(stderr, "Command parsing error\n");
    }
    
    for (int i = 0; i < arg_count; i++) {
        free(arg_array[i]);
    }
    free(arg_array);
    
    return EXIT_SUCCESS;
}