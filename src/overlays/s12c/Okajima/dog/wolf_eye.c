#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _WolfEyeWork
{
    GV_ACT   actor;
    int      map;
    SVECTOR  verts_right[4];
    SVECTOR  verts_left[4];
    char     pad[0x3E];
    DG_PRIM *prim_right;
    DG_PRIM *prim_left;
    int      timer;
    MATRIX  *root;
    int     *visible;
} WolfEyeWork;

int SECTION("overlay.bss") s12c_dword_800DA414;
SVECTOR SECTION("overlay.bss") s12c_800DA418;
int SECTION("overlay.bss") s12c_800DA420;
int SECTION("overlay.bss") s12c_dword_800DA424;

extern int GM_CurrentMap_800AB9B0;
extern SVECTOR DG_ZeroVector_800AB39C;

#define EXEC_LEVEL 5

void WolfEye_800D3518()
{
    s12c_800DA418 = DG_ZeroVector_800AB39C;
    s12c_800DA420 = 0;
}

void WolfEye_800D3554()
{
}

void WolfEye_800D355C(POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    int x, y, w, h;

    while (--n_packs >= 0)
    {
        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, 255, 0, 0);

        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;
        setUVWH(packs, x, y, w, h);

        packs->tpage = tex->tpage;
        packs->clut = tex->clut;

        packs->tpage |= 0x20;

        packs++;
    }
}

void WolfEyeAct_800D35EC(WolfEyeWork *work)
{
    GM_CurrentMap_800AB9B0 = work->map;

    if (--work->timer < 0)
    {
        work->timer = GV_RandU_80017090(128) + 10;
    }

    if (*work->visible == 0 || work->timer < 5)
    {
        DG_InvisiblePrim(work->prim_right);
        DG_InvisiblePrim(work->prim_left);
    }
    else
    {
        DG_VisiblePrim(work->prim_right);
        DG_VisiblePrim(work->prim_left);
    }
}

void WolfEyeDie_800D36C0(WolfEyeWork *work)
{
    DG_PRIM *prim;

    prim = work->prim_right;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->prim_left;
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

    prim = DG_GetPrim(0x1012, 1, 0, work->verts_right, NULL);
    work->prim_right = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 300;
    prim->root = root;

    WolfEye_800D355C(&prim->packs[0]->poly_ft4, 1, tex);
    WolfEye_800D355C(&prim->packs[1]->poly_ft4, 1, tex);

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("wolf_eye_l"));

    prim = DG_GetPrim(0x1012, 1, 0, work->verts_left, NULL);
    work->prim_left = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 300;
    prim->root = root;

    WolfEye_800D355C(&prim->packs[0]->poly_ft4, 1, tex);
    WolfEye_800D355C(&prim->packs[1]->poly_ft4, 1, tex);

    work->verts_right[0].vx = -55;
    work->verts_right[0].vy = 50;
    work->verts_right[0].vz = 160;

    work->verts_right[1].vx = -30;
    work->verts_right[1].vy = 45;
    work->verts_right[1].vz = 170;

    work->verts_right[2].vx = -55;
    work->verts_right[2].vy = 10;
    work->verts_right[2].vz = 160;

    work->verts_right[3].vx = -30;
    work->verts_right[3].vy = 5;
    work->verts_right[3].vz = 170;

    work->verts_left[0].vx = 30;
    work->verts_left[0].vy = 45;
    work->verts_left[0].vz = 170;

    work->verts_left[1].vx = 55;
    work->verts_left[1].vy = 50;
    work->verts_left[1].vz = 160;

    work->verts_left[2].vx = 30;
    work->verts_left[2].vy = 5;
    work->verts_left[2].vz = 170;

    work->verts_left[3].vx = 55;
    work->verts_left[3].vy = 10;
    work->verts_left[3].vz = 160;

    work->visible = visible;
    work->timer = 0;

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
