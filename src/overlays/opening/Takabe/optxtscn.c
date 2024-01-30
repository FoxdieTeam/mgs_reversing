#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct OpTxtScnUnk
{
    int   field_0;
    int   field_4;
    short field_8;
    short field_A;
    short field_C;
    short field_E;
    int  *field_10;
    int  *field_14;
} OpTxtScnUnk;

typedef struct OpTxtScnPrims
{
    DR_STP stp[2];
    char   padding[0xc0];
} OpTxtScnPrims;

typedef struct OpTxtScnWork
{
    GV_ACT         actor;
    int            field_20;
    OpTxtScnUnk   *field_24;
    DG_TEX        *field_28;
    DG_TEX        *field_2C;
    RECT           field_30;
    RECT           field_38;
    OpTxtScnPrims *field_40;
    DG_OBJS       *field_44_objs[2];
    MATRIX         field_4C_light;
    int            field_6C;
    int            field_70;
    int            field_74;
    int            field_78;
    int            field_7C;
    int            field_80;
    int            field_84;
    int            field_88;
} OpTxtScnWork;

#define EXEC_LEVEL 5

extern int  opening_dword_800C32C8;
OpTxtScnUnk opening_dword_800C33E4[2] = {{0, 655392, 0, 0, 32, 70, &opening_dword_800C32C8, &opening_dword_800C32C8},
                                         {0, 327700, 0, 128, 32, 70, &opening_dword_800C32C8, &opening_dword_800C32C8}};

extern MATRIX DG_ZeroMatrix_8009D430;
extern int    GM_CurrentMap_800AB9B0;

void s16b_800C4594(unsigned short address, unsigned short message);

void opening_optxtscn_800CCBDC(DG_TEX *tex, RECT *out)
{
    out->x = (tex->field_8_offx >> 2) + (tex->field_4_tPage << 6 & 0x3C0);
    out->y = tex->field_9_offy + (((tex->field_4_tPage * 0x10) & 0x100) + ((tex->field_4_tPage >> 2) & 0x200));
    out->w = (tex->field_A_width + 3) / 4;
    out->h = tex->field_B_height;
}

#pragma INCLUDE_ASM("asm/overlays/opening/opening_optxtscn_800CCC4C.s")
#pragma INCLUDE_ASM("asm/overlays/opening/opening_optxtscn_800CCD08.s")

void opening_optxtscn_800CCD80(OpTxtScnWork *work)
{
    RECT rect;
    rect.x = work->field_30.x;
    rect.y = work->field_30.y;
    rect.w = work->field_30.w;
    rect.h = work->field_30.h;

    ClearImage(&rect, 0, 0, 0);
}

int opening_optxtscn_800CCDCC(int arg0)
{
    if ((unsigned int)(arg0 & 0xFF) >= 28)
    {
        arg0 = 0;
    }
    return arg0 & 0xFF;
}

#pragma INCLUDE_ASM("asm/overlays/opening/opening_optxtscn_800CCDE8.s")
void opening_optxtscn_800CCDE8(OpTxtScnWork *);

void OpTxtScnDie_800CCFFC(OpTxtScnWork *work)
{
    int i;

    if (work->field_40)
    {
        GV_DelayedFree_80016254(work->field_40);
    }

    s16b_800C4594(0x53B6, 0x448B);

    for (i = 0; i < 2; i++)
    {
        if (work->field_44_objs[i])
        {
            DG_DequeueObjs_800181E4(work->field_44_objs[i]);
            DG_FreeObjs_800318D0(work->field_44_objs[i]);
        }
    }
}

int opening_optxtscn_800CD080(OpTxtScnWork *work)
{
    unsigned short cacheIds[2];
    DG_DEF        *def;
    DG_OBJS       *objs;
    OpTxtScnPrims *prims;
    DG_TEX        *tex;
    MATRIX        *mat;
    int            i;

    work->field_28 = tex = DG_GetTexture_8001D830(0xCC22);
    opening_optxtscn_800CCBDC(tex, &work->field_30);

    work->field_2C = tex = DG_GetTexture_8001D830(0xEF71);
    opening_optxtscn_800CCBDC(tex, &work->field_38);

    s16b_800C4594(0x53B6, 0xA8A4);

    work->field_40 = prims = GV_Malloc_8001620C(sizeof(OpTxtScnPrims));
    SetDrawStp(&prims->stp[0], 0);
    SetDrawStp(&prims->stp[1], 0);

    work->field_24 = opening_dword_800C33E4;
    do {} while (0);

    mat = &DG_ZeroMatrix_8009D430;
    cacheIds[0] = 0xEFAA;
    cacheIds[1] = 0xEFAB;
    DG_SetPos_8001BC44(mat);

    for (i = 0; i < 2; i++)
    {
        def = GV_GetCache_8001538C(GV_CacheID_800152DC(cacheIds[i], 'k'));
        if (def == NULL)
        {
            return -1;
        }

        objs = DG_MakeObjs_80031760(def, 0x15D, 0);
        work->field_44_objs[i] = objs;
        DG_PutObjs_8001BDB8(objs);
        objs->light = &work->field_4C_light;
        DG_QueueObjs_80018178(objs);
        DG_GroupObjs(objs, GM_CurrentMap_800AB9B0);

        tex = DG_GetTexture_8001D830(def->model[0].materialOffset_50[0]);
        tex->field_6_clut = work->field_2C->field_6_clut;
        tex->field_4_tPage = (work->field_28->field_4_tPage & 0xFF9F) | 0x20;

        tex->field_8_offx = work->field_24[i].field_8 * 4;
        tex->field_9_offy = work->field_24[i].field_A;
        tex->field_A_width = work->field_24[i].field_C * 4 - 1;
        tex->field_B_height = work->field_24[i].field_E - 1;
    }

    work->field_4C_light.t[0] = 0x800;
    work->field_4C_light.t[1] = 0x800;
    work->field_4C_light.t[2] = 0x800;
    return 0;
}

GV_ACT *NewOpTxtScn_800CD29C()
{
    OpTxtScnWork *work;

    work = (OpTxtScnWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(OpTxtScnWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)opening_optxtscn_800CCDE8,
                                  (TActorFunction)OpTxtScnDie_800CCFFC, "optxtscn.c");
        if (opening_optxtscn_800CD080(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
