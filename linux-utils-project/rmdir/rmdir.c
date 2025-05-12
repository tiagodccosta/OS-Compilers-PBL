#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

void remove_parent_dirs(char *path, int verbose) {
    char *p;
    
    for (p = path + strlen(path); p > path && *p != '/'; p--);
    
    while (p > path) {
        *p = '\0';  
        
        if (rmdir(path) == -1) {
            perror("rmdir");
            break;
        } else if (verbose) {
            printf("removed directory '%s'\n", path);
        }
        
        for (; p > path && *p != '/'; p--);
    }
}

int main(int argc, char *argv[]) {
    int remove_parents = 0;
    int verbose = 0;
    int ignore_non_empty = 0;
    int i = 1;
    
    while (i < argc && (argv[i][0] == '-' || strncmp(argv[i], "--", 2) == 0)) {
        if (strcmp(argv[i], "-p") == 0) {
            remove_parents = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "--ignore-fail-on-non-empty") == 0) {
            ignore_non_empty = 1;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return 1;
        }
        i++;
    }
    
    if (i >= argc) {
        fprintf(stderr, "rmdir: missing operand\n");
        fprintf(stderr, "Usage: rmdir [OPTION]... DIRECTORY...\n");
        return 1;
    }
    
    for (; i < argc; i++) {
        char *dir = argv[i];
        
        if (rmdir(dir) == -1) {
            if (errno == ENOTEMPTY && ignore_non_empty) {
                if (verbose) {
                    printf("ignoring non-empty directory '%s'\n", dir);
                }
                continue;
            }
            perror("rmdir");
            continue; 
        } else if (verbose) {
            printf("removed directory '%s'\n", dir);
        }
        
        if (remove_parents) {
            char *dir_copy = strdup(dir);
            remove_parent_dirs(dir_copy, verbose);
            free(dir_copy);
        }
    }
    
    return 0;
}