#include "libdg.h"

extern DG_TEX gTextureRecs_800B1F50[512];

int DG_SearchForTextureRecord_8001D778(int hash, DG_TEX **ppFound)
{
    int start;
    DG_TEX *record;
    int index;
    int record_hash;
    
    start = hash % 512;
    record = &gTextureRecs_800B1F50[start];
    index = start;

    do
    {
        record_hash = record->field_0_hash;
        
        if (record_hash == 0)
        {
            *ppFound = record;
            return 0;
        }

        if (record_hash == hash)
        {
            *ppFound = record;
            return 1;
        }

        index++;
        record++;

        if (index == 512)
        {
            record = gTextureRecs_800B1F50;
            index = 0;
        }
    } while(index != start);

    *ppFound = 0;
    return 0;
}
