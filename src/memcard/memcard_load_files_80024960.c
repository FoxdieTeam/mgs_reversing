#include "linker.h"

struct mem_card_block
{
    char field_0_name[20];
    char field_14;
    char field_15;
    unsigned short field_16;
    int field_18_size;
};

struct mem_card
{
    unsigned char field_0_card_idx;
    unsigned char field_1_last_op;
    char field_2_file_count;
    char field_3_free_blocks;
    struct mem_card_block field_4_blocks[15];
};

extern struct mem_card gMemCards_800B52F8[2];

int memcard_loaddir_800247E8(int idx, int *pFreeBlockCount);

void memcard_load_files_80024960(int idx)
{
    int freeBlockCount;
    gMemCards_800B52F8[idx].field_0_card_idx = idx;
    gMemCards_800B52F8[idx].field_1_last_op = 1;
    gMemCards_800B52F8[idx].field_2_file_count = memcard_loaddir_800247E8(idx, &freeBlockCount);
    gMemCards_800B52F8[idx].field_3_free_blocks = 15 - freeBlockCount;
}
