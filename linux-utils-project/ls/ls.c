#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

int compare(const struct dirent **a, const struct dirent **b) {
    return strcoll((*a)->d_name, (*b)->d_name);
}

int compare_reverse(const struct dirent **a, const struct dirent **b) {
    return -strcoll((*a)->d_name, (*b)->d_name);
}

void print_long_format(const char *dirname, const char *filename) {
    struct stat file_stat;
    char filepath[1024];
    
    snprintf(filepath, sizeof(filepath), "%s/%s", dirname, filename);
    
    if (stat(filepath, &file_stat) == -1) {
        perror("stat");
        return;
    }
    
    printf("%c", S_ISDIR(file_stat.st_mode) ? 'd' : '-');
    printf("%c", file_stat.st_mode & S_IRUSR ? 'r' : '-');
    printf("%c", file_stat.st_mode & S_IWUSR ? 'w' : '-');
    printf("%c", file_stat.st_mode & S_IXUSR ? 'x' : '-');
    printf("%c", file_stat.st_mode & S_IRGRP ? 'r' : '-');
    printf("%c", file_stat.st_mode & S_IWGRP ? 'w' : '-');
    printf("%c", file_stat.st_mode & S_IXGRP ? 'x' : '-');
    printf("%c", file_stat.st_mode & S_IROTH ? 'r' : '-');
    printf("%c", file_stat.st_mode & S_IWOTH ? 'w' : '-');
    printf("%c", file_stat.st_mode & S_IXOTH ? 'x' : '-');
    
    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    
    printf(" %2lu %-8s %-8s %8lu ", 
           (unsigned long)file_stat.st_nlink,
           pw ? pw->pw_name : "unknown",
           gr ? gr->gr_name : "unknown",
           (unsigned long)file_stat.st_size);
    
    char time_str[80];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
    printf("%s ", time_str);
    
    printf("%s\n", filename);
}

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent **namelist;
    int n;
    char *dirname = ".";  
    int i = 1;
    int show_hidden = 0;  
    int long_format = 0; 
    int reverse_sort = 0; 
    
    while (i < argc && argv[i][0] == '-') {
        if (strcmp(argv[i], "-a") == 0) {
            show_hidden = 1;
        } else if (strcmp(argv[i], "-l") == 0) {
            long_format = 1;
        } else if (strcmp(argv[i], "-r") == 0) {
            reverse_sort = 1;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return 1;
        }
        i++;
    }
    
    if (i < argc) {
        dirname = argv[i];
    }
    
    if (reverse_sort) {
        n = scandir(dirname, &namelist, NULL, compare_reverse);
    } else {
        n = scandir(dirname, &namelist, NULL, compare);
    }
    
    if (n < 0) {
        perror("scandir");
        return 1;
    }
    
    for (int j = 0; j < n; j++) {
        // Skip hidden files unless -a flag is set
        if (!show_hidden && namelist[j]->d_name[0] == '.') {
            free(namelist[j]);
            continue;
        }
        
        if (long_format) {
            print_long_format(dirname, namelist[j]->d_name);
        } else {
            printf("%s  ", namelist[j]->d_name);
        }
        
        free(namelist[j]);
    }
    
    if (!long_format) printf("\n");
    free(namelist);
    
    return 0;
}