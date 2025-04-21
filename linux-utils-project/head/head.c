#include <stdio.h>
#include <stdlib.h>

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
        perror("head");
        return 1;
    }

    char buffer[1024];
    int count = 0;
    while (fgets(buffer, sizeof(buffer), file) && count < LINES_TO_PRINT)
    {
        printf("%s", buffer);
        count++;
    }

    fclose(file);
    return 0;
}
