#include <util/idaTypes.h>
#include "linker.h"
#include "mts_new.h"

extern void memcard_getfiles_helper_80024960(int);
extern int erase_800995FC(char *);
extern int sprintf_8008E878(char *buffer, const char *format, ...);

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

    struct mem_card gMemCards_800B52F8[2];
    int gMemCard_io_size_800B5648;
};

struct mem_card_daemon SECTION(".gMemoryCardFiles_800B52C8") gMemCardDaemon_800B52C8;

extern const char SECTION(".rdata") aBu02xS[];
extern const char SECTION(".rdata") aDeletedFileS[];
extern const char SECTION(".rdata") aErrorCanTDelet[];

struct mem_card *memcard_get_files_80025350(int idx)
{
    struct mem_card *pCardBase = gMemCardDaemon_800B52C8.gMemCards_800B52F8;
    struct mem_card *pCard = &pCardBase[idx];

    if (pCard->field_1_last_op == 1 || pCard->field_1_last_op == 4)
    {
        memcard_getfiles_helper_80024960(idx); // memcard_load_files_80024960
        pCard->field_1_last_op = 1;
        return pCard;
    }
    return 0;
}

int memcard_delete_800253C4(int idx, const char *pFileName)
{
    char tmp[32];

    struct mem_card *pCardBase = gMemCardDaemon_800B52C8.gMemCards_800B52F8;
    struct mem_card *pCard = &pCardBase[idx];

    if (pCard->field_1_last_op == 1)
    {
        sprintf_8008E878(tmp, aBu02xS, 0x10 * idx, pFileName);
        if (erase_800995FC(tmp))
        {
            mts_printf_8008BBA0(aDeletedFileS, pFileName);
            return 1;
        }
        mts_printf_8008BBA0(aErrorCanTDelet, pFileName);
    }
    return 0;
}
