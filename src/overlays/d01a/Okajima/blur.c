#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libgcl/hash.h"
#include "Game/game.h"

typedef struct _BlurSub
{
    void *ptr;
    char  pad[0xC];
} BlurSub;

typedef struct _BlurWork
{
    GV_ACT   actor;
    int      f20;
    BlurSub  f24[2];
    char     pad2[0x10];
    int      f54;
    int      f58;
    int      f5C;
    int      f60;
    int      f64;
    int      f68;
    int      f6C;
    int      f70;
    int      f74;
    char     pad3[0x8];
} BlurWork;

TILE   SECTION("overlay.bss") d01a_dword_800D1428[2];
DR_STP SECTION("overlay.bss") d01a_dword_800D1448[2];
int SECTION("overlay.bss") d01a_dword_800D1460;
int SECTION("overlay.bss") d01a_dword_800D1464;
DR_STP SECTION("overlay.bss") d01a_dword_800D1468[2];

extern int GV_Clock_800AB920;

void d01a_blur_800CCB28(void)
{
    unsigned int *ot;
    TILE         *tile;
    DR_STP       *stp;
    DR_STP       *stp2;

    ot = (unsigned int *)DG_Chanl(0)->mOrderingTables[GV_Clock_800AB920];

    tile = &d01a_dword_800D1428[GV_Clock_800AB920];
    SetTile(tile);
    setSemiTrans(tile, 1);
    setXY0(tile, -160, -112);
    setWH(tile, 320, 224);
    sub_80018574(tile);
    addPrim(&ot[0xFF], tile);

    stp = &d01a_dword_800D1448[GV_Clock_800AB920];
    SetDrawStp(stp, 1);
    addPrim(&ot[0xFF], stp);

    ot = (unsigned int *)DG_Chanl(1)->mOrderingTables[GV_Clock_800AB920];

    stp2 = &d01a_dword_800D1468[GV_Clock_800AB920];
    SetDrawStp(stp2, 1);
    addPrim(ot, stp2);
}

#pragma INCLUDE_ASM("asm/overlays/d01a/d01a_blur_800CCCC8.s")
void d01a_blur_800CCCC8(POLY_FT4 *packs, BlurWork *work, int arg3, int abr, int arg5, int arg6);

void BlurAct_800CD274(BlurWork *work)
{
    char *ot;
    void *prim;
    int   var_t0;
    int   var_t1;
    int   i;

    if (work->f20 != -1 && GM_CheckMessage_8002631C(&work->actor, work->f20, HASH_KILL))
    {
        GV_DestroyActor_800151C8(&work->actor);
        return;
    }

    work->f5C++;

    d01a_blur_800CCB28();

    if (work->f60 > 0)
    {
        work->f60--;
        return;
    }

    ot = DG_ChanlOTag(1);
    prim = work->f24[GV_Clock_800AB920].ptr;

    var_t0 = 1;
    var_t1 = 0;

    switch (work->f54)
    {
    case 0:
        break;

    case 1:
        var_t0 = 2;
        break;

    case 2:
        var_t0 = 3;
        break;

    case 3:
        var_t1 = 3;
        break;
    }

    d01a_blur_800CCCC8(prim, work, 0, GV_Clock_800AB920, var_t1, var_t0);

    for (i = 0; i < 4; i++)
    {
        addPrim(ot, prim);
        prim += 0x28;
    }
}

void BlurDie_800CD3E8(BlurWork *work)
{
    if (work->f24[0].ptr != NULL)
    {
        GV_DelayedFree_80016254(work->f24[0].ptr);
    }
}

int BlurGetResources_800CD418(BlurWork *work, int arg1, int arg2, int arg3)
{
    char *temp_v0;
    temp_v0 = GV_Malloc_8001620C(0x140);
    if (temp_v0 == NULL)
    {
        return -1;
    }

    work->f24[0].ptr = temp_v0;
    work->f24[1].ptr = temp_v0 + 160;
    work->f54 = arg3;

    switch (arg3)
    {
    case 0:
        break;

    case 1:
        arg3 = 0;
        break;

    case 2:
        arg3 = 0;
        break;
    }

    d01a_blur_800CCCC8(work->f24[0].ptr, work, 1, 0, arg3, 1);
    d01a_blur_800CCCC8(work->f24[1].ptr, work, 1, 1, arg3, 1);

    work->f5C = GV_RandU_80017090(4096);
    work->f60 = 4;
    work->f58 = arg1;

    if (arg2 != 0)
    {
        work->f64 = 0;
        work->f68 = 0;
        work->f6C = 0;
    }
    else
    {
        work->f68 = 24;
        work->f64 = 0;
        work->f6C = 40;
    }

    return 0;
}

#define EXEC_LEVEL 7

GV_ACT* d01a_blur_800CD530(int arg0, int arg1, int arg2)
{
    BlurWork *work;

    work = (BlurWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(BlurWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)BlurAct_800CD274, (TActorFunction)BlurDie_800CD3E8, "blur.c");

        if (BlurGetResources_800CD418(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->f20 = -1;
    }

    return &work->actor;
}

GV_ACT * NewBlur_800CD5D8(int arg0)
{
    BlurWork *work;
    int       opt;
    int       var_s2;
    int       var_s3;
    int        var_s4;

    var_s4 = 0;
    var_s3 = 0;
    var_s2 = 0;

    work = (BlurWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(BlurWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)BlurAct_800CD274, (TActorFunction)BlurDie_800CD3E8, "blur.c");

        opt = GCL_GetOption_80020968('d');
        if (opt != NULL)
        {
            var_s4 = GCL_StrToInt_800209E8((char *)opt);
            var_s3 = GCL_StrToInt_800209E8((char *)opt);
            var_s2 = GCL_StrToInt_800209E8((char *)opt);
        }

        if (BlurGetResources_800CD418(work, var_s4, var_s3, var_s2) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->f20 = arg0;
    }

    return &work->actor;
}
