#include "linker.h"
#include "menuMan.h"

typedef struct
{
    char field_0_x;
    char field_1_y;
    char field_2_w;
    char field_3_h;
    unsigned char field_4_pixel_ptr[0];
} Menu_rpk_item;

typedef struct
{
    unsigned char field_0_count1;
    unsigned char field_1_count2;
    short pad;
    Menu_rpk_item *items[0]; // pointers ??
} RpkHeader;

Menu_rpk_item **SECTION(".sbss") gItemFile_table_800ABAE4;

int GV_HashFileName_800152FC(const char *pFileName, int ext);
void *GV_FindCachedFile_8001538C(int hash);

#define OffsetToPointer(offset, valueToAdd)   *((unsigned int *)offset) = (int)valueToAdd +  *((unsigned int *)offset);

Menu_rpk_item **sub_8003DD1C(const char *pFileName)
{
    Menu_rpk_item **pEnd;
    Menu_rpk_item **pIter;
    int i;
    int count;
    RpkHeader *pFileData = GV_FindCachedFile_8001538C( GV_HashFileName_800152FC(pFileName, 'r'));
    if (!pFileData)
    {
        return 0;
    }

    count = pFileData->field_0_count1 + pFileData->field_1_count2;
    pEnd = pFileData->items + count;

    gItemFile_table_800ABAE4 = pFileData->items;

    pIter = pFileData->items;
    for (i = 0; i < count; i++)
    {
        OffsetToPointer(pIter, pEnd);
        pIter++;
    }

    return gItemFile_table_800ABAE4;
}

Menu_rpk_item *sub_8003DD9C(int id)
{
    return gItemFile_table_800ABAE4[id];
}

Menu_rpk_item *sub_8003DDB4(int id)
{
    return gItemFile_table_800ABAE4[id];
}
