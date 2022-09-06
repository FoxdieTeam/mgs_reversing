#include "libdg.h"

extern unsigned char kVertexIndexingOrder_8009D46C[];

void kmd_file_handler_link_vertices_to_parent_8001F3CC(DG_MDL *pKmdObj, DG_MDL *pParentObj)
{
    unsigned int uVar2;
    int faces;
    unsigned char *fio;
    unsigned char *fio2;
    short uVar7;
    SVECTOR *vio;
    SVECTOR *vio2;
    int index;
    unsigned short pad;
    int iter;
    int offset;

    vio = pKmdObj->vertexIndexOffset_38;
    uVar7 = 0;
    fio = pKmdObj->faceIndexOffset_3C;
    
    for (iter = pKmdObj->numFaces_4 * 4; iter > 0; iter--)
    {
        index = *fio;
        vio2 = &vio[index];

        if (vio2->pad != -1)
        {
            uVar7 |= index;
            *fio |= 0x80;
        }

        fio++;
    }

    if (uVar7 & 0x80)
    {
        return;
    }

    vio2 = pKmdObj->vertexIndexOffset_38;
    
    for (iter = pKmdObj->numVertex_34; iter > 0; iter--)
    {
        pad = vio2->pad;
        
        if (pad != 0xffff)
        {
            fio2 = pParentObj->faceIndexOffset_3C;

            for (faces = pParentObj->numFaces_4 * 4; faces > 0; faces--)
            {                
                if ((*fio2 & 0x7f) == pad)
                {
                    break;
                }

                fio2++;
            }

            offset = fio2 - pParentObj->faceIndexOffset_3C;
            uVar2 = (offset / 4) * 52;
            
            vio2->pad = kVertexIndexingOrder_8009D46C[offset & 3] * 12 + uVar2 + 8;
        }

        vio2++;
    }
}
