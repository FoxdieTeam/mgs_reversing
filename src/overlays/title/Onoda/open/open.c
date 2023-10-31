#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _OpenWork
{
    GV_ACT   actor;
    DG_PRIM *prim[4];
    char     pad[0xB1C];
    char     field_B4C[24][44];
    char     pad2[0x1598];
} OpenWork;

extern int GM_GameStatus_800AB3CC;

extern int title_dword_800D92D0;

extern const char aOpenC[]; // = "open.c"

#define EXEC_LEVEL 1

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4500.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4674.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C47B8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4AD0.s")

void * title_open_800C4B20(void *ptr)
{
    return *((void **)ptr + 10);
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4B2C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4B94.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4BD4.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4C38.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C4F1C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5200.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5238.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5360.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C53E0.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5620.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5750.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5760.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C593C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5CB8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5CF0.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5D10.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C5D30.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C61E0.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C628C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CCDC8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD074.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD23C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD320.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD3B8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD800.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CDB4C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CDB9C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CDBF8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CDE44.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE378.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE4A8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE544.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE5F8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE6AC.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE748.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CEB14.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CF794.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D1B74.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D1CB4.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2374.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2460.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2E44.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D3500.s")

#pragma INCLUDE_ASM("asm/overlays/title/OpenAct_800D37F4.s")
void OpenAct_800D37F4(OpenWork *work);

void OpenDie_800D4098(OpenWork *work)
{
    DG_PRIM *prim;
    int      i;
    void    *ptr;

    prim = work->prim[0];
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->prim[2];
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->prim[3];
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->prim[1];
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    for (i = 0; i < 24; i++)
    {
        ptr = title_open_800C4B20(work->field_B4C[i]);
        GV_FreeMemory_80015FD0(2, ptr);
    }
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D4174.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D41E4.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D4368.s")

void title_open_800D4464(OpenWork *work, int name, POLY_GT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    DG_TEX *tex;
    int     u0, u1;
    int     v0, v1;

    tex = DG_GetTexture_8001D830(name);

    setPolyGT4(poly);

    u0 = tex->field_8_offx;
    u1 = u0 + tex->field_A_width + 1;
    v0 = tex->field_9_offy;
    v1 = v0 + tex->field_B_height + 1;

    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->field_4_tPage;
    poly->clut = tex->field_6_clut;

    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

#pragma INCLUDE_ASM("asm/overlays/title/OpenGetResources_800D4584.s")
int  OpenGetResources_800D4584(OpenWork *work, int);

GV_ACT * NewOpen_800D6814(int arg0, int arg1)
{
    OpenWork *work;

    GM_GameStatus_800AB3CC |= 0x4A6000;

    work = (OpenWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(OpenWork));
    title_dword_800D92D0 = 0;

    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)OpenAct_800D37F4, (TActorFunction)OpenDie_800D4098, aOpenC);

        if (OpenGetResources_800D4584(work, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
