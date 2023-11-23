#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _WolfEyeWork
{
    GV_ACT   actor;
    int      map;
    SVECTOR  f24;
    short    f2C;
    short    f2E;
    short    f30;
    short    f32;
    short    f34;
    short    f36;
    short    f38;
    short    f3A;
    short    f3C;
    short    f3E;
    short    f40;
    short    f42;
    SVECTOR  f44;
    short    f4C;
    short    f4E;
    short    f50;
    short    f52;
    short    f54;
    short    f56;
    short    f58;
    short    f5A;
    short    f5C;
    short    f5E;
    short    f60;
    char     pad[0x40];
    DG_PRIM *right;
    DG_PRIM *left;
    int      blink_timer;
    MATRIX  *root;
    int     *visible;
} WolfEyeWork;

extern int GM_CurrentMap_800AB9B0;

#define EXEC_LEVEL 5

void WolfEye_800D355C(POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, 255, 0, 0);

        x = tex->field_8_offx;
        w = tex->field_A_width;
        y = tex->field_9_offy;
        h = tex->field_B_height;
        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->field_4_tPage;
        packs->clut = tex->field_6_clut;

        packs->tpage |= 0x20;

        packs++;
    }
}

void WolfEyeAct_800D35EC(WolfEyeWork *work)
{
    GM_CurrentMap_800AB9B0 = work->map;

    if (--work->blink_timer < 0)
    {
        work->blink_timer = GV_RandU_80017090(128) + 10;
    }

    if (*work->visible == 0 || work->blink_timer < 5)
    {
        DG_InvisiblePrim(work->right);
        DG_InvisiblePrim(work->left);
    }
    else
    {
        DG_VisiblePrim(work->right);
        DG_VisiblePrim(work->left);
    }
}

void WolfEyeDie_800D36C0(WolfEyeWork *work)
{
    DG_PRIM *prim;

    prim = work->right;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->left;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int WolfEyeGetResources_800D3728(WolfEyeWork *work, MATRIX *root, int *visible)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    work->root = root;
    work->map = GM_CurrentMap_800AB9B0;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("wolf_eye_r"));

    prim = DG_GetPrim(0x1012, 1, 0, &work->f24, NULL);
    work->right = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 300;
    prim->root = root;

    WolfEye_800D355C(&prim->field_40_pBuffers[0]->poly_ft4, 1, tex);
    WolfEye_800D355C(&prim->field_40_pBuffers[1]->poly_ft4, 1, tex);

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("wolf_eye_l"));

    prim = DG_GetPrim(0x1012, 1, 0, &work->f44, NULL);
    work->left = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 300;
    prim->root = root;

    WolfEye_800D355C(&prim->field_40_pBuffers[0]->poly_ft4, 1, tex);
    WolfEye_800D355C(&prim->field_40_pBuffers[1]->poly_ft4, 1, tex);

    work->f24.vx = -55;
    work->f24.vy = 50;
    work->f24.vz = 160;

    work->f2C = -30;
    work->f2E = 45;
    work->f30 = 170;

    work->f34 = -0x37;
    work->f36 = 10;
    work->f38 = 160;

    work->f3C = -30;
    work->f3E = 5;
    work->f40 = 170;

    work->f44.vx = 30;
    work->f44.vy = 45;
    work->f44.vz = 170;

    work->f4C = 55;
    work->f4E = 50;
    work->f50 = 160;

    work->f54 = 30;
    work->f56 = 5;
    work->f58 = 170;

    work->f5C = 55;
    work->f5E = 10;
    work->f60 = 160;

    work->visible = visible;
    work->blink_timer = 0;

    return 0;
}

GV_ACT * NewWolfEye_800D3930(MATRIX *root, int *visible)
{
    WolfEyeWork *work;

    work = (WolfEyeWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(WolfEyeWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)WolfEyeAct_800D35EC, (TActorFunction)WolfEyeDie_800D36C0, "wolf_eye.c");

        if (WolfEyeGetResources_800D3728(work, root, visible) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
