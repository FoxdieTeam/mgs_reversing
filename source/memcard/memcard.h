#ifndef __MGS_MEMCARD_H__
#define __MGS_MEMCARD_H__

#include <sys/types.h>

#define MEMCARD_BLOCK_SIZE  8192 /* 8 KiB */
#define MEMCARD_NAME_MAX    20
#define MEMCARD_BLOCK_MAX   15

typedef struct _MEMCARD_FILE {
    char name[ MEMCARD_NAME_MAX + 1 ];
    int size;
} MEMCARD_FILE;

typedef struct _MEMCARD {
    u_char port;
    u_char last_op;
    u_char file_count;
    u_char free_blocks;
    MEMCARD_FILE files[ MEMCARD_BLOCK_MAX ];
} MEMCARD;

void memcard_init(void);
void memcard_exit(void);
int  memcard_status(void);
int  memcard_check(int port);
int  memcard_format(int port);
int  memcard_delete(int port, const char *filename);
void memcard_write(int port, const char *filename, int offset, char *buffer, int size);
void memcard_read(int port, const char *filename, int offset, char *buffer, int size);

MEMCARD *memcard_files(int port);

#endif // __MGS_MEMCARD_H__
