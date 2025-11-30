// fs.h
#ifndef FS_H
#define FS_H

#define MAX_FILES   16
#define MAX_NAME    32
#define MAX_CONTENT 128

typedef struct {
    int  used;
    char name[MAX_NAME];
    char data[MAX_CONTENT];
} file_t;

void fs_init(void);
int  fs_create(const char *name, const char *content);
int  fs_read(const char *name, char *buf, int bufsize);
int  fs_write(const char *name, const char *content);

#endif
