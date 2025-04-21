#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("pwd");
        return 1;
    }
    return 0;
}
