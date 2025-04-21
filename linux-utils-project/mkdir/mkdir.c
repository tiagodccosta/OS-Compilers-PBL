#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    if (mkdir(argv[1], 0755) == -1)
    {
        perror("mkdir");
        return 1;
    }

    printf("Directory '%s' created.\n", argv[1]);
    return 0;
}
