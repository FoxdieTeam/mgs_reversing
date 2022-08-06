#ifndef _MEMCARD_H_
#define _MEMCARD_H_

struct mem_card_block
{
    char           field_0_name[20];
    char           field_14;
    char           field_15;
    unsigned short field_16;
    int            field_18_size;
};

struct mem_card
{
    unsigned char         field_0_card_idx;
    unsigned char         field_1_last_op;
    char                  field_2_file_count;
    char                  field_3_free_blocks;
    struct mem_card_block field_4_blocks[15];
};

typedef void (*TMemCardFunc)(int);
typedef void (*TMemCardSetFunc)(TMemCardFunc);

void memcard_init_80024E48();
int  memcard_check_80024A54(int idx);
int  memcard_easy_format_test_800246C0(int hCard);
void memcard_reset_status_80024A3C();
void memcard_set_sw_hw_card_fns_8002469C();
void memcard_load_files_80024960(int);

void memcard_hwcard_do_op_800244DC(TMemCardSetFunc op);
void memcard_hwcard_end_io_800244FC();
void memcard_hwcard_end_write_80024524();
void memcard_hwcard_timeout_8002455C();
void memcard_hwcard_new_80024594();

void memcard_swcard_do_op_800244EC(TMemCardSetFunc op);
void memcard_swcard_end_io_800245CC();
void memcard_swcard_end_write_800245F4();
void memcard_swcard_timeout_8002462C();
void memcard_swcard_new_80024664();

#endif // _MEMCARD_H_
