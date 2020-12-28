#include "dgd.h"

extern void kmd_file_handler_link_vertices_to_parent_8001F3CC(DG_KmdObject *, DG_KmdObject *);

typedef struct DG_KmdFile
{
    int unknown0;
    unsigned int num_objects;
    int unknown1[6];
    DG_KmdObject objects[0];
} DG_KmdFile;

int kmd_file_handler_8001F4EC(unsigned char *pFileData, int fileNameHashed)
{
    DG_KmdFile *kmd = (DG_KmdFile *)pFileData;
    DG_KmdObject *current = kmd->objects;
    int remaining = kmd->num_objects;

    --remaining;
    while (remaining >= 0)
    {
        if (current->vertOfs_38)
        {
            (char *)current->vertOfs_38 += (unsigned int)kmd;
        }
        if (current->indexOfs_3C)
        {
            (char *)current->indexOfs_3C += (unsigned int)kmd;
        }
        if (current->normOfs_44)
        {
            (char *)current->normOfs_44 += (unsigned int)kmd;
        }
        if (current->normIndex_48)
        {
            (char *)current->normIndex_48 += (unsigned int)kmd;
        }
        if (current->ofsUV_4C)
        {
            (char *)current->ofsUV_4C += (unsigned int)kmd;
        }
        if (current->ofsTextureNameHashes_50)
        {
            (char *)current->ofsTextureNameHashes_50 += (unsigned int)kmd;
        }
        if (current->mRef_2C_parentObjIndex >= 0)
        {
            kmd_file_handler_link_vertices_to_parent_8001F3CC(
                    current, &kmd->objects[current->mRef_2C_parentObjIndex]);
        }
        ++current;
        --remaining;
    }
    return 1;
}
