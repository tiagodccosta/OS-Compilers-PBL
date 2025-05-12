#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void print_help() {
    printf("Usage: pwd [OPTION]...\n");
    printf("Print the current working directory\n\n");
    printf("Options:\n");
    printf("  -L    use PWD from environment, even if it contains symlinks\n");
    printf("  -P    avoid all symlinks (default)\n");
    printf("  --help  display this help and exit\n");
}

int main(int argc, char *argv[]) {
    char cwd[1024];
    int logical = 0; 
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-L") == 0) {
            logical = 1;
        } else if (strcmp(argv[i], "-P") == 0) {
            logical = 0;
        } else if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else {
            fprintf(stderr, "pwd: Unknown option: %s\n", argv[i]);
            fprintf(stderr, "Try 'pwd --help' for more information.\n");
            return 1;
        }
    }
    
    if (logical) {
        char *pwd_env = getenv("PWD");
        if (pwd_env != NULL) {
            printf("%s\n", pwd_env);
            return 0;
        }
    }
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd");
        return 1;
    }
    
    return 0;
}