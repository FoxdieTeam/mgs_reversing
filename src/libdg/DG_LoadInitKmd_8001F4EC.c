#include "dgd.h"
#include "libdg.h"

void kmd_file_handler_link_vertices_to_parent_8001F3CC(DG_MDL *, DG_MDL *);

typedef struct DG_KmdFile
{
    int unknown0;
    unsigned int num_objects;
    int unknown1[6];
    DG_MDL objects[0];
} DG_KmdFile;

int DG_LoadInitKmd_8001F4EC(unsigned char *pFileData, int fileNameHashed)
{
    DG_KmdFile *kmd = (DG_KmdFile *)pFileData;
    DG_MDL *current = kmd->objects;
    int remaining = kmd->num_objects;

    while (--remaining >= 0)
    {
        if (current->vertexIndexOffset_38)
        {
            (char *)current->vertexIndexOffset_38 += (unsigned int)kmd;
        }
        if (current->faceIndexOffset_3C)
        {
            (char *)current->faceIndexOffset_3C += (unsigned int)kmd;
        }
        if (current->normalIndexOffset_44)
        {
            (char *)current->normalIndexOffset_44 += (unsigned int)kmd;
        }
        if (current->normalFaceOffset_48)
        {
            (char *)current->normalFaceOffset_48 += (unsigned int)kmd;
        }
        if (current->uvOffset_4C)
        {
            (char *)current->uvOffset_4C += (unsigned int)kmd;
        }
        if (current->materialOffset_50)
        {
            (char *)current->materialOffset_50 += (unsigned int)kmd;
        }
        if (current->parent_2C >= 0)
        {
            kmd_file_handler_link_vertices_to_parent_8001F3CC(
                    current, &kmd->objects[current->parent_2C]);
        }
        ++current;
    }
    return 1;
}
