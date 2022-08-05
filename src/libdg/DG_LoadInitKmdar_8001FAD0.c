#include "dgd.h"
#include "libdg.h"
#include "libgv/libgv.h"

int DG_LoadInitKmdar_8001FAD0(unsigned char *pFileData, int fileNameHashed)
{
    DG_ZmdFile *zmdFile = (DG_ZmdFile *)pFileData;
    DG_ZmdEntry *zmdEntry = &zmdFile->zmdEntries[0];
    unsigned int offset = (unsigned int)zmdEntry + zmdFile->vertOffset;
    int numZmds = zmdFile->numZmds + 1;
    while (--numZmds > 0)
    {
        DG_ZmdObject *zmdObject = &zmdEntry->data;
        int nameHashed;
        int numMeshes = zmdObject->numMeshes;
        DG_MDL *kmdObject = &zmdObject->kmdObjects[0];
        while (--numMeshes >= 0)
        {
            (char *)kmdObject->vertexIndexOffset_38 += offset;
            if (kmdObject->faceIndexOffset_3C)
            {
                (char *)kmdObject->faceIndexOffset_3C += offset;
            }
            if (kmdObject->normalIndexOffset_44)
            {
                (char *)kmdObject->normalIndexOffset_44 += offset;
            }
            if (kmdObject->normalFaceOffset_48)
            {
                (char *)kmdObject->normalFaceOffset_48 += offset;
            }
            if (kmdObject->uvOffset_4C)
            {
                (char *)kmdObject->uvOffset_4C += offset;
            }
            if (kmdObject->materialOffset_50)
            {
                (char *)kmdObject->materialOffset_50 += offset;
            }
            if (kmdObject->parent_2C >= 0)
            {
                kmd_file_handler_link_vertices_to_parent_8001F3CC(kmdObject,
                                                                  &zmdObject->kmdObjects[kmdObject->parent_2C]);
            }
            ++kmdObject;
        }
        nameHashed = GV_CacheID_800152DC(zmdEntry->fileNameHashed, 107);
        zmdEntry = (DG_ZmdEntry *)kmdObject;
        GV_SetCache_800153C0(nameHashed, zmdObject);
    }
    return 1;
}
