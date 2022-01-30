#include <util/idaTypes.h>
#include "linker.h"
#include "mts_new.h"
#include "memcard.h"

extern void memcard_load_files_80024960(int);
extern int erase_800995FC(char *);
extern int sprintf_8008E878(char *buffer, const char *format, ...);


long SECTION(".gMemoryCardFiles_800B52C8") gHardware_end_io_800B52C8;
long SECTION(".gMemoryCardFiles_800B52C8") gHardware_end_write_800B52CC;
long SECTION(".gMemoryCardFiles_800B52C8")gHardware_timeout_800B52D0;
long SECTION(".gMemoryCardFiles_800B52C8")gHardware_new_device_800B52D4;

long SECTION(".gMemoryCardFiles_800B52C8") gSoftware_end_io_800B52D8;
long SECTION(".gMemoryCardFiles_800B52C8") gSoftware_end_write_800B52DC;
long SECTION(".gMemoryCardFiles_800B52C8") gSoftware_timeout_800B52E0;
long SECTION(".gMemoryCardFiles_800B52C8") gSoftware_new_device_800B52E4;

int SECTION(".gMemoryCardFiles_800B52C8") gHwCard_do_op_800B52E8;
int SECTION(".gMemoryCardFiles_800B52C8") gSwCard_do_op_800B52EC;
int SECTION(".gMemoryCardFiles_800B52C8") gSwCardLastOp_800B52F0;
int SECTION(".gMemoryCardFiles_800B52C8") gHwCardLastOp_800B52F4;

struct mem_card SECTION(".gMemoryCardFiles_800B52C8") gMemCards_800B52F8[2];

extern const char SECTION(".rdata") aBu02xS[];
extern const char SECTION(".rdata") aDeletedFileS[];
extern const char SECTION(".rdata") aErrorCanTDelet[];

struct mem_card *memcard_get_files_80025350(int idx)
{
    struct mem_card *pCardBase = gMemCards_800B52F8;
    struct mem_card *pCard = &pCardBase[idx];

    if (pCard->field_1_last_op == 1 || pCard->field_1_last_op == 4)
    {
        memcard_load_files_80024960(idx);
        pCard->field_1_last_op = 1;
        return pCard;
    }
    return 0;
}

int memcard_delete_800253C4(int idx, const char *pFileName)
{
    char tmp[32];

    struct mem_card *pCardBase = gMemCards_800B52F8;
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
