#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void search(const char *dir, const char *filename)
{
    DIR *dp = opendir(dir);
    if (!dp)
        return;

    struct dirent *entry;
    char path[1024];

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

        struct stat st;
        if (stat(path, &st) == -1)
            continue;

        if (S_ISDIR(st.st_mode))
        {
            search(path, filename); // Recurse
        }
        else if (strcmp(entry->d_name, filename) == 0)
        {
            printf("Found: %s\n", path);
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <directory> <filename>\n", argv[0]);
        return 1;
    }

    search(argv[1], argv[2]);
    return 0;
}
