#ifndef _MEMCARD_H_
#define _MEMCARD_H_

// 8 KB
#define MC_BLOCK_SIZE 8192

typedef struct mem_card_block
{
    char            field_0_name[20];
    char            field_14;
    char            field_15;
    unsigned short  field_16;
    int             field_18_size;
} mem_card_block;

typedef struct mem_card
{
    unsigned char   field_0_card_idx;
    unsigned char   field_1_last_op;
    char            field_2_file_count;
    char            field_3_free_blocks;
    mem_card_block  field_4_blocks[15];
} mem_card;

typedef void (*TMemCardFunc)(int);

void memcard_reset_status(void);
int  memcard_check(int port);
void memcard_init(void);
void memcard_exit(void);
void memcard_retry(int port);
mem_card *memcard_get_files(int port);
int  memcard_delete(int port, const char *filename);

void memcard_write(int port, const char *filename, int seekPos, char *pBuffer, int bufferSize);
void memcard_read(int port, const char *filename, int seekPos, char *pBuffer, int bufferSize);
int  memcard_get_status(void);
int  memcard_format(int port);

#endif // _MEMCARD_H_
