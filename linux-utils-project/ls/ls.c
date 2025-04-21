#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    const char *path = (argc > 1) ? argv[1] : ".";

    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("ls");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s  ", entry->d_name);
    }
    printf("\n");

    closedir(dir);
    return 0;
}

