#include <util/idaTypes.h>
#include "linker.h"
#include "mts_new.h"
#include "memcard.h"

extern void memcard_load_files_80024960(int);
extern int erase_800995FC(char *);
extern int sprintf_8008E878(char *buffer, const char *format, ...);

struct mem_card_daemon SECTION(".gMemoryCardFiles_800B52C8") gMemCardDaemon_800B52C8;
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
