#ifndef _MEMCARD_H_
#define _MEMCARD_H_

typedef struct mem_card_block
{
    char           field_0_name[20];
    char           field_14;
    char           field_15;
    unsigned short field_16;
    int            field_18_size;
} mem_card_block;

typedef struct mem_card
{
    unsigned char         field_0_card_idx;
    unsigned char         field_1_last_op;
    char                  field_2_file_count;
    char                  field_3_free_blocks;
    mem_card_block field_4_blocks[15];
} mem_card;

typedef void (*TMemCardFunc)(int);

void memcard_init_80024E48();
void memcard_exit_800250C4();
int  memcard_check_80024A54(int idx);
int  memcard_easy_format_test_800246C0(int hCard);
void memcard_reset_status_80024A3C();
void memcard_set_sw_hw_card_fns_8002469C();
void memcard_load_files_80024960(int);
int  memcard_loaddir_800247E8(int idx, int *pFreeBlockCount);

void memcard_hwcard_do_op_800244DC(int op);
void memcard_hwcard_end_io_800244FC();
void memcard_hwcard_end_write_80024524();
void memcard_hwcard_timeout_8002455C();
void memcard_hwcard_new_80024594();
void memcard_hwcard_read_write_handler_8002546C(int op);

void memcard_swcard_do_op_800244EC(int op);
void memcard_swcard_end_io_800245CC();
void memcard_swcard_end_write_800245F4();
void memcard_swcard_timeout_8002462C();
void memcard_swcard_new_80024664();

void memcard_read_8002569C(int idx, const char *pFilename, int seekPos, char *pBuffer, int bufferSize);
void memcard_write_8002554C(int idx, const char *pFileName, int seekPos, char *pBuffer, int bufferSize);
int  memcard_format_800257C0(int idx);
int  memcard_delete_800253C4(int idx, const char *pFileName);

int  memcard_get_status_800257B0(void);

mem_card *memcard_get_files_80025350(int idx);

#endif // _MEMCARD_H_
