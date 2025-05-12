#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

void create_parent_dirs(char *path, mode_t mode, int verbose) {
    char *p;
    
    for (p = path; *p == '/'; p++);
    
    while ((p = strchr(p, '/'))) {
        *p = '\0';  
        
        if (mkdir(path, mode) == -1) {
            if (errno != EEXIST) {
                perror("mkdir");
                exit(1);
            }
        } else if (verbose) {
            printf("created directory '%s'\n", path);
        }
        
        *p = '/'; 
        p++;       
    }
}

int main(int argc, char *argv[]) {
    int create_parents = 0;
    int verbose = 0;
    mode_t mode = 0755; 
    int i = 1;
    
    while (i < argc && argv[i][0] == '-') {
        if (strcmp(argv[i], "-p") == 0) {
            create_parents = 1;
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            i++;
            mode = (mode_t)strtol(argv[i], NULL, 8);
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return 1;
        }
        i++;
    }
    
    if (i >= argc) {
        fprintf(stderr, "mkdir: missing operand\n");
        fprintf(stderr, "Usage: mkdir [OPTION]... DIRECTORY...\n");
        return 1;
    }
    
    for (; i < argc; i++) {
        char *dir = argv[i];
        
        if (create_parents) {
            char *dir_copy = strdup(dir);
            create_parent_dirs(dir_copy, mode, verbose);
            free(dir_copy);
        }
        
        if (mkdir(dir, mode) == -1) {
            if (errno == EEXIST && create_parents) {
                continue;
            }
            perror("mkdir");
            return 1;
        } else if (verbose) {
            printf("created directory '%s'\n", dir);
        }
    }
    
    return 0;
}