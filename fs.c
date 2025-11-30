// fs.c
#include "fs.h"
#include "sync.h"

static file_t files[MAX_FILES];
static mutex_t fs_lock;

void fs_init(void) {
    for (int i = 0; i < MAX_FILES; i++) {
        files[i].used = 0;
        files[i].name[0] = '\0';
        files[i].data[0] = '\0';
    }
    mutex_init(&fs_lock);
}

static int find_file(const char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].used && !strcmp(files[i].name, name)) {
            return i;
        }
    }
    return -1;
}

int fs_create(const char *name, const char *content) {
    mutex_lock(&fs_lock);
    int idx = find_file(name);
    if (idx >= 0) {
        mutex_unlock(&fs_lock);
        return -1; // already exists
    }
    for (int i = 0; i < MAX_FILES; i++) {
        if (!files[i].used) {
            files[i].used = 1;
            strncpy(files[i].name, name, MAX_NAME - 1);
            files[i].name[MAX_NAME-1] = '\0';
            strncpy(files[i].data, content, MAX_CONTENT - 1);
            files[i].data[MAX_CONTENT-1] = '\0';
            mutex_unlock(&fs_lock);
            return 0;
        }
    }
    mutex_unlock(&fs_lock);
    return -1;
}

int fs_read(const char *name, char *buf, int bufsize) {
    mutex_lock(&fs_lock);
    int idx = find_file(name);
    if (idx < 0) {
        mutex_unlock(&fs_lock);
        return -1;
    }
    int len = strlen(files[idx].data);
    if (len >= bufsize) len = bufsize - 1;
    memcpy(buf, files[idx].data, len);
    buf[len] = '\0';
    mutex_unlock(&fs_lock);
    return len;
}

int fs_write(const char *name, const char *content) {
    mutex_lock(&fs_lock);
    int idx = find_file(name);
    if (idx < 0) {
        mutex_unlock(&fs_lock);
        return -1;
    }
    strncpy(files[idx].data, content, MAX_CONTENT - 1);
    files[idx].data[MAX_CONTENT - 1] = '\0';
    mutex_unlock(&fs_lock);
    return 0;
}
