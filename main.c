#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pdirs;
    // Not implemented currently
    int lfmt;
} FLAGS;

void ls(char *dirname, FLAGS *flags, int multiple);
int starts_with(char *a, char *b);
int get_dirs_to_process(char *dirname, struct dirent ***namelist);
int process_files(int n, struct dirent ***namelist, FLAGS *flags);

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
        ls("/", &flags, 0);
    } else {
        int multiple = argc > 1 ? 1 : 0;
        while (argc-- > 0) {
            ls(*argv++, &flags, multiple);
        }
    }

    return 0;
}


int starts_with(char *prefix, char *word){
    return strncmp(prefix, word, strlen(prefix));
}

int process_files(int n, struct dirent ***namelist, FLAGS *flags) {
    int i = 1;
    while (i < n) {
        char *dir = (*(namelist[i]))->d_name;

        // Don't print directories that are private
        if (!flags->pdirs && starts_with(".", dir) == 0) {
            free((*namelist)[i]);
            i++;
            continue;
        }

        // Print all directories
        printf("%s\n", dir);
        free((*namelist)[i]);
        i++;
    }

    free(*namelist);
    printf("\n");
    return n;
}

int get_dirs_to_process(char *dirname, struct dirent ***namelist) {
    int n;
    // n is the number of files that were scanned in dirname and added to
    // namelist. They'll need to be looped through one by one.
    n = scandir(dirname, namelist, NULL, alphasort);

    // https://linux.die.net/man/3/scandir
    if (n < 1) {
        perror("scandir");
        return -1;
    }

    return n;
}

void ls(char *dirname, FLAGS *flags, int multiple){
    struct dirent **namelist;
    int n;
    n = get_dirs_to_process(dirname, &namelist);

    if (multiple) {
        printf("%s:\n", dirname);
    }

    process_files(n, &namelist, flags);
}


