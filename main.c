#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pdirs;
    // Not implemented currently
    int lfmt;
} FLAGS;

int ls(char *dirname, FLAGS *flags, int multiple);

int main(int argc, char *argv[]) {
    FLAGS flags = {
        0,
        0
    };
    char c;

    // This will take care of the options
    while (--argc > 0 && (*++argv)[0] == '-') {
        while ((c = *++argv[0])) {
            switch (c) {
                case 'a':
                    flags.pdirs = 1;
                    break;
//                case 'o':
//                    flags.lfmt = 1;
//                    break;
                default:
                    printf("ls: illegal option %c\n", c);
                    return 1;
            }
        }
    }

    if (argc == 0) {
        char *cwd[1];
        ls("/", &flags, 0);
    } else {
        int multiple = argc > 1 ? 1 : 0;
        while (argc-- > 0) {
            ls(*argv++, &flags, multiple);
        }
    }

    return 0;
}

int starts_with(char *a, char *b);

int starts_with(char *prefix, char *word){
    return strncmp(prefix, word, strlen(prefix));
}

int ls(char *dirname, FLAGS *flags, int multiple) {
    int n;
    struct dirent **namelist;
    n = scandir(dirname, &namelist, NULL, alphasort);

    // https://linux.die.net/man/3/scandir
    if (n < 1) {
        perror("scandir");
        return -1;
    }

    if (multiple) {
        printf("%s:\n", dirname);
    }

    int i = 0;
    while (i < n) {
        char *dir = namelist[i]->d_name;

        // Don't print directories that are private
        if (!flags->pdirs && starts_with(".", dir) == 0) {
            free(namelist[i]);
            i++;
            continue;
        }

        // Print all directories
        printf("%s\n", dir);
        free(namelist[i]);
        i++;
    }

    free(namelist);
    printf("\n");
    return n;
}

//int get_dirs_to_process(char *dirname, struct dirent **namelist);
//int process_files(int n, struct dirent **namelist, FLAGS *flags);
//int process_files(int n, struct dirent **namelist, FLAGS *flags) {
//    int i = 0;
//    while (i++ < n - 1) {
//
//        char *dir = namelist[i]->d_name;
//        if (strcmp(dir, ".") == 0 || strcmp(dir, "..") == 0) {
//            free(namelist[i]);
//            continue;
//        }
//
//        if (!flags->lfmt) {
//            // Print all directories
//            if (!flags->pdirs && starts_with(".", dir)) {
//                free(namelist[i]);
//                continue;
//            }
//
//            // Don't print directories that are private
//            printf("%s\n", dir);
//        }
//
//
//        // If certain flags are used, I can use scandir in combination with
//        // stat to get the file information permissions, etc.
//        // printf("%s\n", namelist[i]->d_name);
//        free(namelist[i]);
//    }
//}
//
//int get_dirs_to_process(char *dirname, struct dirent **namelist) {
//    int n;
//    // n is the number of files that were scanned in dirname and added to
//    // namelist. They'll need to be looped through one by one.
//    n = scandir(dirname, &namelist, NULL, alphasort);
//
//    // https://linux.die.net/man/3/scandir
//    if (n < 1) {
//        perror("scandir");
//        return -1;
//    }
//
//    return n;
//}

//void ls(char *dirname, FLAGS *flags){
//    struct stat dirinfo;
//    // Start: Refactor this out into a method called get_dirs_to_process
//    struct dirent **namelist;
//    int n;
//    n = get_dirs_to_process(dirname, &namelist);
//    process_files(n, *namelist, flags);

    // Stop: Refactor this out into a method called get_dirs_to_process
//    printf("pdirs: %d\nlfmt: %d\n", flags.pdirs, flags.lfmt);
//
//    scandir(dirname, struct dirent ***namelist,
//    int (*select)(const struct dirent *),
//    int (*compar)(const struct dirent **, const struct dirent **));
//
//    if (stat(dirname, &dirinfo) == -1) {
//        fprintf(stderr, "ls: can't access %s\n", dirname);
//        return;
//    }
//    // stat(cwd, &dirinfo);
//    // Working with just the current directory
//    // Need to get the cwd no matter what, as it will need to be applied
//    // to added to the base of every directory
//    char cwd = obtaincwd();
//    if (dirname[0] == NULL) {
//        stat(cwd, &dirinfo);
//    }
//
//    printf("Next directory to be processed: %s\n", dirname[0]);
//}


//char *obtaincwd(){
//    long path_max;
//    size_t size;
//    char *buf;
//    char *ptr;
//
//    path_max = pathconf(".", _PC_PATH_MAX);
//    if (path_max == -1)
//        size = 1024;
//    else if (path_max > 10240)
//        size = 10240;
//    else
//        size = path_max;
//
//    for (buf = ptr = NULL; ptr == NULL; size *= 2) {
//        if ((buf = realloc(buf, size)) == NULL) {
//            printf("obtaincwd buf memory allocation issues");
//            break;
//        }
//
//        ptr = getcwd(buf, size);
//        if (ptr == NULL && errno != ERANGE) {
//            printf("obtaincwd getcwd memory issues");
//            break;
//        }
//    }
//
//    free (buf);
//    return ptr;
//}

