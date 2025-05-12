#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_head_lines(FILE *file, int num_lines) {
    int c;
    int line_count = 0;
    
    while ((c = fgetc(file)) != EOF && line_count < num_lines) {
        putchar(c);
        if (c == '\n') {
            line_count++;
        }
    }
}

void print_head_bytes(FILE *file, int num_bytes) {
    int c;
    int byte_count = 0;
    
    while ((c = fgetc(file)) != EOF && byte_count < num_bytes) {
        putchar(c);
        byte_count++;
    }
}

int main(int argc, char *argv[]) {
    FILE *file = stdin;
    int num_lines = 10;
    int byte_mode = 0;
    int num_bytes = 0;
    int quiet_mode = 0;
    char *filename = NULL;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            num_lines = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            byte_mode = 1;
            num_bytes = atoi(argv[++i]);
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
    }
    
    if (!quiet_mode && filename != NULL) {
        printf("==> %s <==\n", filename);
    }
    
    if (byte_mode) {
        print_head_bytes(file, num_bytes);
    } else {
        print_head_lines(file, num_lines);
    }
    
    if (filename != NULL) {
        fclose(file);
    }
    
    return 0;
}