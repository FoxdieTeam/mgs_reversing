#include "libgv/libgv.h"
#include "libdg/libdg.h"

typedef struct CameraWork
{
    GV_ACT         actor;
    char           padding1[0x10];
    DG_PRIM       *prim1, *prim2, *prim3;
    char           padding2[0x8e4];
    int            field_920;
    unsigned char *field_924_mOrderingTable;
    int            field_928;
    int            field_92C[2];
    char           padding3[0x4004];
    int            field_4938;
    char           padding4[0xac];
} CameraWork;

extern const char camera_aCamerac_800D06A4[]; // = "camera.c";

extern int GM_GameStatus_800AB3CC;

int            camera_800C3ED8(CameraWork *);
int            camera_800CDF18();
extern DG_CHNL DG_Chanls_800B1800[];
extern int     GV_Clock_800AB920;

void CameraAct_800CE404(CameraWork *work)
{
    work->field_920 = work->field_92C[GV_Clock_800AB920];
    work->field_924_mOrderingTable = DG_Chanl(1)->mOrderingTables[GV_Clock_800AB920];
    camera_800CDF18();
    camera_800C3ED8(work);
    work->field_4938++;
}

void CameraDie_800CE470(CameraWork *work)
{
    DG_PRIM *prim1;
    DG_PRIM *prim2;
    DG_PRIM *prim3;

    prim1 = work->prim1;
    if (prim1)
    {
        DG_DequeuePrim_800182E0(prim1);
        DG_FreePrim_8001BC04(prim1);
    }
    prim2 = work->prim2;
    if (prim2)
    {
        DG_DequeuePrim_800182E0(prim2);
        DG_FreePrim_8001BC04(prim2);
    }
    prim3 = work->prim3;
    if (prim3)
    {
        DG_DequeuePrim_800182E0(prim3);
        DG_FreePrim_8001BC04(prim3);
    }
}

int camera_800CE6EC(CameraWork *work, int where);

void camera_800CE4F8(int work, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans)
{
    setPolyFT4(pPoly);
    pPoly->r0 = 0x80;
    pPoly->g0 = 0x80;
    pPoly->b0 = 0x80;
    pPoly->x0 = x0;
    pPoly->y0 = y0;
    pPoly->y1 = y0;
    pPoly->x2 = x0;
    pPoly->x1 = x1;
    pPoly->y2 = y1;
    pPoly->x3 = x1;
    pPoly->y3 = y1;
    SetSemiTrans(pPoly, semiTrans);
}

void camera_800CE568(int work, int hashCode, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans, int arg9)
{
    DG_TEX *tex;
    camera_800CE4F8(work, pPoly, x0, y0, x1, y1, semiTrans);
    tex = DG_GetTexture_8001D830(hashCode);

    if (arg9 == 0)
    {
        int offx, offx2, offx3;
        int offy, offy2;

        offx = tex->field_8_offx;
        offx2 = offx + tex->field_A_width;
        offy = tex->field_9_offy;
        offx3 = offx2 + 1;
        offy2 = offy + tex->field_B_height + 1;

        setUV4(pPoly, offx, offy, offx3, offy, offx, offy2, offx3, offy2);
        pPoly->tpage = tex->field_4_tPage;
        pPoly->clut = tex->field_6_clut;
    }

    else if (arg9 == 1)
    {
        int offx, offx2, offx3;
        int offy, offy2;

        offx = tex->field_8_offx;
        offx2 = offx + tex->field_A_width;
        offy = tex->field_9_offy;
        offx3 = offx2 + 1;
        offy2 = offy + tex->field_B_height;

        setUV4(pPoly, offx, offy, offx3, offy, offx, offy2, offx3, offy2);
        pPoly->tpage = tex->field_4_tPage;
        pPoly->clut = tex->field_6_clut;
    }

    else if (arg9 == 2)
    {
        int offx, offx2;
        int offy, offy2;

        offx = tex->field_8_offx;
        offx2 = offx + tex->field_A_width;
        offy = tex->field_9_offy;
        offy2 = offy + tex->field_B_height + 1;

        setUV4(pPoly, offx, offy, offx2, offy, offx, offy2, offx2, offy2);
        pPoly->tpage = tex->field_4_tPage;
        pPoly->clut = tex->field_6_clut;
    }

    else if (arg9 == 3)
    {
        int offx, offx2;
        int offy, offy2;

        offx = tex->field_8_offx;
        offx2 = offx + tex->field_A_width;
        offy = tex->field_9_offy;
        offy2 = offy + tex->field_B_height;

        setUV4(pPoly, offx, offy, offx2, offy, offx, offy2, offx2, offy2);
        pPoly->tpage = tex->field_4_tPage;
        pPoly->clut = tex->field_6_clut;
    }
}

#pragma INCLUDE_ASM("asm/overlays/camera/camera_800CE6EC.s")

GV_ACT *NewCamera_800CF388(int name, int where, int argc, char **argv)
{
    CameraWork *work;

    GM_GameStatus_800AB3CC |= 0x4A6000;
    work = (CameraWork *)GV_NewActor_800150E4(1, sizeof(CameraWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)CameraAct_800CE404, (TActorFunction)CameraDie_800CE470,
                                  camera_aCamerac_800D06A4);
        if (camera_800CE6EC(work, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
