#include "linker.h"
#include "memcard.h"
#include <KERNEL.H>

extern struct mem_card gMemCards_800B52F8[2];

int memcard_loaddir_800247E8(int idx, int *pFreeBlockCount);

extern const char aBu02x[];          // = "bu%02X:*";
extern const char aLoadDirSStart[];  // = "load_dir %s start\n";
extern const char aTotalDFilesUse[]; // = "TOTAL %d FILES used %d block\n";
extern const char aNoFile[];         // = "NO FILE\n";

struct DIRENTRY *firstfile_80099AEC(char *, struct DIRENTRY *);
struct DIRENTRY *nextfile_800995EC(struct DIRENTRY *);

int sprintf_8008E878(char *buffer, const char *format, ...);

// still has large diffs
/*
int memcard_loaddir_800247E8(int idx, int *pFreeBlockCount)
{
    int blockCount; // $s2
    int fileCount;  // $s1
    // int card_off;           // $s0
    struct mem_card_block *pBlocks; // $v0
    struct mem_card_block *pBlock;  // $v0
                                    // struct mem_card *pCard;        // $v1
    int v12;                        // $v0
                                    // int more;              // dc
    struct DIRENTRY dirEntry;       // [sp+10h] [-48h] BYREF
    char dirName[34];               // [sp+38h] [-20h] BYREF

    blockCount = 0;

    sprintf_8008E878(dirName, aBu02x, 0x10 * idx);

    mts_printf_8008BBA0(aLoadDirSStart, dirName);
    fileCount = 0;

    if (firstfile_80099AEC(dirName, &dirEntry))
    {
        //  pCard = &gMemCards_800B52F8[idx];
        //card_off = 0x1A8 * idx;
        pBlocks = &gMemCards_800B52F8[idx].field_4_blocks[0];
        do
        {
            //pCard = (struct mem_card *)((char *)gMemCards_800B52F8 + card_off);
            pBlock = &pBlocks[fileCount];
            memcpy(&pBlock->field_0_name, &dirEntry.name, 20);

            pBlock->field_14 = 0;
            pBlock->field_18_size = dirEntry.size;

            v12 = (dirEntry.size + 0x1FFF) >> 13;
            if (dirEntry.size + 0x1FFF < 0)
            {
                v12 = (dirEntry.size + 0x3FFE) >> 13;
            }
            blockCount += v12;

            // card_off += 0x1C; //1c = mem_card_block size
            ++fileCount;

            // pBlock = (struct mem_card_block *)((char *)gMemCards_800B52F8[0].field_4_blocks + card_off);
        } while (nextfile_800995EC(&dirEntry) != 0);

        mts_printf_8008BBA0(aTotalDFilesUse, fileCount, blockCount);
        *pFreeBlockCount = blockCount;
        return fileCount;
    }
    else
    {
        mts_printf_8008BBA0(aNoFile);
        *pFreeBlockCount = 0;
        return 0;
    }
}
*/

void memcard_load_files_80024960(int idx)
{
    int freeBlockCount;
    gMemCards_800B52F8[idx].field_0_card_idx = idx;
    gMemCards_800B52F8[idx].field_1_last_op = 1;
    gMemCards_800B52F8[idx].field_2_file_count = memcard_loaddir_800247E8(idx, &freeBlockCount);
    gMemCards_800B52F8[idx].field_3_free_blocks = 15 - freeBlockCount;
}
