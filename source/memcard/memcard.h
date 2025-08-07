#ifndef __MGS_MEMCARD_H__
#define __MGS_MEMCARD_H__

// 8 KB
#define MC_BLOCK_SIZE 8192

typedef struct MEM_CARD_FILE
{
    char            name[20];
    char            field_14;
    char            field_15;
    unsigned short  field_16;
    int             field_18_size;
} MEM_CARD_FILE;

typedef struct MEM_CARD
{
    unsigned char   card_idx;
    unsigned char   last_op;
    char            file_count;
    char            free_blocks;
    MEM_CARD_FILE   files[15];
} MEM_CARD;

typedef void (*TMemCardFunc)(int);

void memcard_reset_status(void);
int  memcard_check(int port);
void memcard_init(void);
void memcard_exit(void);
void memcard_retry(int port);
MEM_CARD *memcard_get_files(int port);
int  memcard_delete(int port, const char *filename);

void memcard_write(int port, const char *filename, int offset, char *buffer, int size);
void memcard_read(int port, const char *filename, int offset, char *buffer, int size);
int  memcard_get_status(void);
int  memcard_format(int port);

#endif // __MGS_MEMCARD_H__
