#include "libdg.h"
#include "Game/target.h"

// TODO: This is something inside GM_Target
typedef struct GM_Target_Ukn
{
    SVECTOR vector[2];
    CVECTOR color[2];
} GM_Target_Ukn;

extern MATRIX DG_LightMatrix_8009D384;
extern MATRIX DG_ColorMatrix_8009D3A4;

extern CVECTOR DG_PacketCode_800AB394[2];

extern GM_Target gTargets_800B64E0[64];

//there are a few of these that are close to gte_MulMatrix0 but with the first part changed
#define gte_Unknown(r1, r2)                                                                                            \
    {                                                                                                                  \
        gte_ldclmv(r1);                                                                                                \
        gte_rtir();                                                                                                    \
        gte_stclmv(r2);                                                                                                \
        gte_ldclmv((char *)r1 + 2);                                                                                    \
        gte_rtir();                                                                                                    \
        gte_stclmv((char *)r2 + 2);                                                                                    \
        gte_ldclmv((char *)r1 + 4);                                                                                    \
        gte_rtir();                                                                                                    \
        gte_stclmv((char *)r2 + 4);                                                                                    \
    }

static inline void * DG_GetLightMatrix(void)
{
    return &DG_LightMatrix_8009D384;
}

CVECTOR * DG_MakePreshade_helper_80031BD4(DG_MDL *pMdl, CVECTOR *pRgbs, DG_OBJS *pObjs)
{
    MATRIX light;
    MATRIX color;
    MATRIX world_light;
    CVECTOR *pPacketCode;
    int faces;
    unsigned char *pFio;
    unsigned char *pNfo;
    SVECTOR *pNio;
    unsigned int index;
    GM_Target_Ukn *unk;

    memcpy(&light, DG_GetLightMatrix(), 8);
    
    color.m[0][0] = DG_ColorMatrix_8009D3A4.m[0][0];
    color.m[1][0] = DG_ColorMatrix_8009D3A4.m[1][0];
    color.m[2][0] = DG_ColorMatrix_8009D3A4.m[2][0];
    
    pPacketCode = &DG_PacketCode_800AB394[0];

    if (pMdl->flags_0 & 2)
    {
        pPacketCode = &DG_PacketCode_800AB394[1];
    }

    gte_ldrgb(pPacketCode);

    pFio = pMdl->faceIndexOffset_3C;
    pNfo = pMdl->normalFaceOffset_48;
    pNio = pMdl->normalIndexOffset_44;

    for (faces = pMdl->numFaces_4 * 4; faces > 0; faces--)
    {
        index = *pFio;

        if (index < 42)
        {
            unk = (GM_Target_Ukn *)getScratchAddr(0) + index;
        }
        else
        {
            unk = (GM_Target_Ukn *)&gTargets_800B64E0[62].field_10_size + index;
        }

        *(SVECTOR *)&light.m[1] = unk->vector[0];
        *(SVECTOR *)&light.m[2] = unk->vector[1];
        
        gte_SetRotMatrix(&light);
        gte_Unknown(&pObjs->world, &world_light);
        gte_SetLightMatrix(&world_light);

        color.m[0][1] = unk->color[0].r << 4;
        color.m[1][1] = unk->color[0].g << 4;
        color.m[2][1] = unk->color[0].b << 4;
        color.m[0][2] = unk->color[1].r << 4;
        color.m[1][2] = unk->color[1].g << 4;
        color.m[2][2] = unk->color[1].b << 4;
        
        gte_SetColorMatrix(&color);
        gte_ldv0(pNio + *pNfo++);
        gte_ncs();
        gte_strgb(pRgbs++);
        
        pFio++;
    }
    
    return pRgbs;
}
