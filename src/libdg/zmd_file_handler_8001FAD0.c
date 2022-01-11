#include "dgd.h"

typedef struct DG_ZmdObject {
    unsigned int numFaces;
    unsigned int numMeshes;
    DG_Vec3 start;
    DG_Vec3 end;
    DG_KmdObject kmdObjects[0];
} DG_ZmdObject;

typedef struct DG_ZmdEntry {
    unsigned int fileNameHashed;
    DG_ZmdObject data;
} DG_ZmdEntry;

typedef struct DG_ZmdFile
{
    unsigned int magic;
    unsigned int numZmds;
    unsigned int vertOffset;
    unsigned int bodyLength;
    DG_ZmdEntry zmdEntries[0];
} DG_ZmdFile;

extern int GV_CacheID_800152DC(int hashedFileName, int param_2);
extern void kmd_file_handler_link_vertices_to_parent_8001F3CC(DG_KmdObject *, DG_KmdObject *);
extern void sub_800153C0(int, DG_ZmdObject *);

int zmd_file_handler_8001FAD0(unsigned char *pFileData)
{
    DG_ZmdFile *zmdFile = (DG_ZmdFile *)pFileData;
    DG_ZmdEntry *zmdEntry = &zmdFile->zmdEntries[0];
    unsigned int offset = (unsigned int)zmdEntry + zmdFile->vertOffset;
    int numZmds = zmdFile->numZmds + 1;
    while (--numZmds > 0) {
        DG_ZmdObject *zmdObject = &zmdEntry->data;
        int nameHashed;
        int numMeshes = zmdObject->numMeshes;
        DG_KmdObject *kmdObject = &zmdObject->kmdObjects[0];
        while (--numMeshes >= 0)
        {
            (char *)kmdObject->vertOfs_38 += offset;
            if (kmdObject->indexOfs_3C)
            {
                (char *)kmdObject->indexOfs_3C += offset;
            }
            if (kmdObject->normOfs_44)
            {
                (char *)kmdObject->normOfs_44 += offset;
            }
            if (kmdObject->normIndex_48)
            {
                (char *)kmdObject->normIndex_48 += offset;
            }
            if (kmdObject->ofsUV_4C)
            {
                (char *)kmdObject->ofsUV_4C += offset;
            }
            if (kmdObject->ofsTextureNameHashes_50)
            {
                (char *)kmdObject->ofsTextureNameHashes_50 += offset;
            }
            if (kmdObject->mRef_2C_parentObjIndex >= 0)
            {
                kmd_file_handler_link_vertices_to_parent_8001F3CC(
                    kmdObject,
                    &zmdObject->kmdObjects[kmdObject->mRef_2C_parentObjIndex]);
            }
            ++kmdObject;
        }
        nameHashed = GV_CacheID_800152DC(zmdEntry->fileNameHashed, 107);
        zmdEntry = (DG_ZmdEntry *)kmdObject;
        sub_800153C0(nameHashed, zmdObject);
    }
    return 1;
}
