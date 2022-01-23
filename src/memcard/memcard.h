#ifndef _MEMCARD_H_
#define _MEMCARD_H_

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

struct mem_card_daemon
{
    void *gHardware_end_io_800B52C8;
    void *gHardware_end_write_800B52CC;
    void *gHardware_timeout_800B52D0;
    void *gHardware_new_device_800B52D4;

    void *gSoftware_end_io_800B52D8;
    void *gSoftware_end_write_800B52DC;
    void *gSoftware_timeout_800B52E0;
    void *gSoftware_new_device_800B52E4;

    int gHwCard_do_op_800B52E8;
    int gSwCard_do_op_800B52EC;
    int gSwCardLastOp_800B52F0;
    int gHwCardLastOp_800B52F4;
};

#endif // _MEMCARD_H_
