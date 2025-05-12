#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER 100000

void print_tail_lines(FILE *file, int num_lines) {
    char buffer[MAX_BUFFER];
    char *lines[MAX_BUFFER];
    int line_count = 0;
    
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (line_count < num_lines) {
            lines[line_count] = strdup(buffer);
        } else {
            free(lines[line_count % num_lines]);
            lines[line_count % num_lines] = strdup(buffer);
        }
        line_count++;
    }
    
    int start = line_count <= num_lines ? 0 : line_count % num_lines;
    for (int i = 0; i < num_lines && i < line_count; i++) {
        printf("%s", lines[(start + i) % num_lines]);
        free(lines[(start + i) % num_lines]);
    }
}

void follow_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long position = ftell(file);
    
    printf("Following file %s...\n", filename);
    
    while (1) {
        char buffer[1024];
        fseek(file, position, SEEK_SET);
        
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
            position = ftell(file);
        }
        
        sleep(1);  
    }
}

int main(int argc, char *argv[]) {
    FILE *file = stdin;
    int num_lines = 10; 
    int follow_mode = 0;
    int quiet_mode = 0;
    char *filename = NULL;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            num_lines = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-f") == 0) {
            follow_mode = 1;
        } else if (strcmp(argv[i], "-q") == 0) {
            quiet_mode = 1;
        } else if (argv[i][0] != '-') {
            filename = argv[i];
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return 1;
        }
    }
    
    if (filename != NULL) {
        file = fopen(filename, "r");
        if (file == NULL) {
            perror("fopen");
            return 1;
        }
    } else if (follow_mode) {
        fprintf(stderr, "Cannot follow standard input\n");
        return 1;
    }
    
    if (!quiet_mode && filename != NULL) {
        printf("==> %s <==\n", filename);
    }
    
    print_tail_lines(file, num_lines);
    
    if (filename != NULL) {
        fclose(file);
    }
    
    if (follow_mode && filename != NULL) {
        follow_file(filename);
    }
    
    return 0;
}