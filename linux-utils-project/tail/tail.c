#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1024
#define LINES_TO_PRINT 10

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        perror("tail");
        return 1;
    }

    char *lines[MAX_LINES];
    char buffer[1024];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (count >= MAX_LINES)
            break;
        lines[count] = strdup(buffer);
        count++;
    }

    int start = (count > LINES_TO_PRINT) ? count - LINES_TO_PRINT : 0;
    for (int i = start; i < count; i++)
    {
        printf("%s", lines[i]);
        free(lines[i]);
    }

    fclose(file);
    return 0;
}
