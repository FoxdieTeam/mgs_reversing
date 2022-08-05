#include "linker.h"
#include "dgd.h"
#include "mts/mts_new.h"
#include "libgv/actor.h"
#include "libgv/libgv.h"

extern unsigned char kVertexIndexingOrder_8009D46C[];
extern const char    aDgdC[];

Actor SECTION(".gDgdActor2_800B3750") gDgdActor2_800B3750;
Actor SECTION(".gDgdActor2_800B3750") gDgdActor1_800B3770; // same section as its directly after
int   SECTION(".gDgdActor2_800B3750") dword_800B3790;

void DG_StartDaemon_8001F284(void)
{
    mts_set_vsync_task_800892B8();
    mts_set_callback_800893B4(DG_DrawSyncResetGraph_8001F014);
    DG_InitDispEnv_800170F0(0, 0, 320, 240, 320);
    DG_InitChanlSystem_80017B98(320);
    DG_ClearResidentTexture_8001DB10();
    DG_8001F1DC();
    GV_SetLoader_80015418('p', DG_LoadInitPcx_8001F920);
    GV_SetLoader_80015418('k', DG_LoadInitKmd_8001F4EC);
    GV_SetLoader_80015418('l', DG_LoadInitLit_8001F6B4);
    GV_SetLoader_80015418('n', DG_LoadInitNar_8001F5F8);
    GV_SetLoader_80015418('o', DG_LoadInitOar_8001F610);
    GV_SetLoader_80015418('z', DG_LoadInitKmdar_8001FAD0);
    GV_SetLoader_80015418('i', DG_LoadInitImg_8001F644);
    GV_SetLoader_80015418('s', sgt_file_handler_8001F670);

    // 2D handler?
    GV_InitActor_800150A8(0, &gDgdActor2_800B3750, 0);
    GV_SetNamedActor_8001514C(&gDgdActor2_800B3750, (TActorFunction)DG_Update2_8001F078, 0, aDgdC);

    // 3D handler?
    GV_InitActor_800150A8(8, &gDgdActor1_800B3770, 0);
    GV_SetNamedActor_8001514C(&gDgdActor1_800B3770, (TActorFunction)DG_Update1_8001F1BC, 0, aDgdC);
}

/*
void kmd_file_handler_link_vertices_to_parent_8001F3CC(DG_MDL* pKmdObj, DG_MDL* pParentObj)
{
    unsigned int idx;
    int parentFaceCount;
    unsigned char *pIdxOffs;
    int pbVar1;
    SVECTOR *pVertOff;
    int counter;
    int flags;
    SVECTOR *pVertOffs;

    pIdxOffs = pKmdObj->indexOfs_3C;
    pVertOffs = pKmdObj->vertOfs_38;
    counter = pKmdObj->field_4_numFaces << 2;
    flags = 0;

    while (counter > 0)
    {
        idx = *pIdxOffs;
        if (pVertOffs[idx].pad != -1)
        {
            flags |= idx;
            *pIdxOffs = idx | 0x80;
        }
        counter--;
        pIdxOffs++;
    }

    if ((flags & 0x80) == 0)
    {
        pVertOff = &pKmdObj->vertOfs_38[0];
        for (counter = pKmdObj->numVerts_34; counter > 0; counter-- )
        {
            if ((unsigned short)pVertOff->pad != 0xffff)
            {


                pIdxOffs = pParentObj->indexOfs_3C;
                parentFaceCount = pParentObj->field_4_numFaces << 2;

                while (parentFaceCount > 0)
                {

                    parentFaceCount--;
                    if (((unsigned int)*pIdxOffs & 0x7f) != pVertOff->pad)
                    {
                        pIdxOffs++;
                    }
                }

                pbVar1 = pIdxOffs - pParentObj->indexOfs_3C;
                if ((int)pbVar1 < 0)
                {
                    //pbVar1 = pIdxOffs + 3;
                    pbVar1 += 3;
                }
                pVertOff->pad = (ushort)(kVertexIndexingOrder_8009D46C)[pbVar1 & 3] * 0xc + (short)((pbVar1 / 4) *
sizeof(POLY_GT4)) + 8;
            }
            pVertOff++;
        }
    }
}
*/
