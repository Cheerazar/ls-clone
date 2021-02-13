//typedef struct {
//    long ino;
//    char name[MAX_LINE + 1];
//} Dirent;
//
//typedef struct {
//    int fd;
//    Dirent d;
//} DIR;
//
//int ls(char *dirnames[]);
//DIR *opendir(char *dirname);
//Dirent *readdir(DIR *dfd);
//void closedir(DIR *dfd);