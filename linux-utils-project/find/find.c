#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <fnmatch.h>
#include <stdlib.h>

typedef struct {
    char *name_pattern; 
    char file_type;      
    long size;           
    int has_name;
    int has_type;
    int has_size;
} SearchCriteria;

int match_criteria(const char *path, const SearchCriteria *criteria) {
    struct stat st;
    
    if (stat(path, &st) == -1)
        return 0;
    
    if (criteria->has_type) {
        if (criteria->file_type == 'f' && !S_ISREG(st.st_mode))
            return 0;
        if (criteria->file_type == 'd' && !S_ISDIR(st.st_mode))
            return 0;
    }
    
    if (criteria->has_size && st.st_size != criteria->size)
        return 0;
    
    if (criteria->has_name) {
        const char *filename = strrchr(path, '/');
        if (filename)
            filename++; 
        else
            filename = path;
            
        if (fnmatch(criteria->name_pattern, filename, 0) != 0)
            return 0;
    }
    
    return 1; 
}

void search_recursive(const char *dir, const SearchCriteria *criteria) {
    DIR *dp = opendir(dir);
    if (!dp)
        return;

    struct dirent *entry;
    char path[1024];

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

        struct stat st;
        if (stat(path, &st) == -1)
            continue;

        if (match_criteria(path, criteria))
            printf("%s\n", path);

        if (S_ISDIR(st.st_mode))
            search_recursive(path, criteria); 
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    char *start_dir = "."; 
    SearchCriteria criteria = {0};
    int i = 1;
    
    if (i < argc && argv[i][0] != '-') {
        start_dir = argv[i++];
    }
    
    while (i < argc) {
        if (strcmp(argv[i], "-name") == 0 && i + 1 < argc) {
            criteria.name_pattern = argv[++i];
            criteria.has_name = 1;
        } else if (strcmp(argv[i], "-type") == 0 && i + 1 < argc) {
            criteria.file_type = argv[++i][0]; 
            criteria.has_type = 1;
        } else if (strcmp(argv[i], "-size") == 0 && i + 1 < argc) {
            criteria.size = atol(argv[++i]);
            criteria.has_size = 1;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return 1;
        }
        i++;
    }

    search_recursive(start_dir, &criteria);
    return 0;
}