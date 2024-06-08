#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Anime/animeconv/anime.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "overlays/s00a/Enemy/enemy.h"
#include "libgcl/hash.h"

// Strange
typedef struct _SearchlightSub
{
    SVECTOR  fFC;
    SVECTOR  f104;
    SVECTOR  f10C;
    SVECTOR  f114;
    SVECTOR  f11C;
    SVECTOR  pad2[36]; // 124
    SVECTOR  f244;
    char     pad3[0x8]; // 24C
    DG_PRIM *prim;      // 254
    DG_TEX  *tex;
} SearchlightSub;

typedef struct _SearchlightWork
{
    GV_ACT         actor;
    CONTROL        control;
    char           pad[0x60]; // 9C
    SearchlightSub fFC;
    char           pad4[0x4];
    SVECTOR        f260;
    short          f268;
    short          f26A;
    short          height;
    short          f26E;
    short          angle;
    short          f272;
    short          f274;
    short          f276;
    short          f278;
    short          f27A;
    short          f27C;
    short          f27E;
    int            debug;
    SVECTOR        f284;
    int            f28C;
    int            f290;
    int            f294;
    char           pad6[0x4];
    int            f29C;
    int            f2A0;
    int            f2A4;
    int            f2A8;
    int            f2AC;
    int            f2B0;
    int            f2B4;
    char           pad8[0x8];
    GV_ACT        *lit_mdl;
    MATRIX         lit_mtx;
} SearchlightWork;

extern MATRIX   DG_ZeroMatrix_8009D430;
extern SVECTOR  DG_ZeroVector_800AB39C;
extern int      GM_PlayerMap_800ABA0C;
extern SVECTOR  GM_PlayerPosition_800ABA10;
extern int      GM_PlayerStatus_800ABA50;
extern GV_PAD   GV_PadData_800B05C0[4];
extern CONTROL *GM_WhereList_800B56D0[96];
extern OBJECT  *GM_PlayerBody_800ABA20;
extern int      dword_800ABA1C;
extern CONTROL *GM_PlayerControl_800AB9F4;
extern int     COM_VibTime_800E0F68;

extern ENEMY_COMMAND     EnemyCommand_800E0D98;
extern TOPCOMMAND_STRUCT TOPCOMMAND_800E0F20;

const SVECTOR s01a_svec_800E4660 = {0, 0, 65024};

const char aSearchliUDRotXLRRotY[] = "UD:ROT.X  LR:ROT.Y\n";
const char aSearchliUDPosXLRPosZ[] = "UD:POS.X  LR:POS.Z\n";
const char aSearchliUDPosYLRAngle[] = "UD:POS.Y  LR:ANGLE\n";
const char aSearchliRot7D7D7D[] = "ROT:%7d %7d %7d\n";
const char aSearchliPos7D7D7D[] = "POS:%7d %7d %7d\n";
const char aSearchliAngle4D[] = "ANGLE:%4d \n";

const SVECTOR SearchliCenter_800E46D8 = {0, 0, 3000, 0};


void    s00a_command_800CEC40(SVECTOR *, int);
void    s01a_object_800D9424(CONTROL *, int);
void    s01a_800E2364(MATRIX *, SVECTOR *, VECTOR *);
GV_ACT *s01a_lit_mdl_800E2C88(MATRIX *arg0, int arg1, int arg2, int arg3);
void    s01a_lit_mdl_800E2D3C(GV_ACT *, int angle);

#define EXEC_LEVEL 4

void s01a_searchli_800D7320(DG_PRIM *prim, DG_TEX *tex, int r, int g, int b)
{
    POLY_FT4 *poly;

    poly = &prim->packs[0]->poly_ft4;
    setRGB0(poly, r, g, b);

    poly = &prim->packs[1]->poly_ft4;
    setRGB0(poly, r, g, b);
}

void s01a_searchli_800D734C(SVECTOR *from, SVECTOR *to, SVECTOR *out)
{
    SVECTOR diff;
    int     dy;

    GV_SubVec3_80016D40(to, from, &diff);
    out->vy = ratan2(diff.vx, diff.vz) & 0xFFF;

    dy = diff.vy;
    diff.vy = 0;

    out->vx = (ratan2(GV_VecLen3_80016D80(&diff), dy) & 0xFFF) - 1024;
    if (out->vx < 0)
    {
        out->vx += 4096;
    }
}

int s01a_searchli_800D73D8(SearchlightWork *work)
{
    if (!(work->control.map->index & GM_PlayerMap_800ABA0C) || (work->f2A4 == 0))
    {
        work->f290 = 0;
        return 0;
    }

    if ((TOPCOMMAND_800E0F20.mode != 1) && (GM_PlayerStatus_800ABA50 & PLAYER_CB_BOX))
    {
        if (work->f290 == 0)
        {
            work->f284 = GM_PlayerPosition_800ABA10;
            work->f28C = GM_WhereList_800B56D0[0]->rot.vy;
            work->f290 = 1;
            return 0;
        }

        if ((GV_DiffVec3_80016E84(&work->f284, &GM_PlayerPosition_800ABA10) < 50) &&
            (work->f28C == GM_WhereList_800B56D0[0]->rot.vy))
        {
            work->f290 = 1;
            return 0;
        }
    }

    work->f290 = 1;
    return 1;
}

void s01a_searchli_800D7500(SVECTOR *in, SVECTOR *out, SearchlightWork *work)
{
    int diff;

    if (out->vx > work->f276)
    {
        out->vx = work->f276;
    }
    else if (out->vx < work->f274)
    {
        out->vx = work->f274;
    }

    diff = GV_DiffDirS_8001704C(in->vy, out->vy);
    if (diff > work->f278)
    {
        out->vy = (in->vy + work->f278) & 0xFFF;
    }
    else if (diff < -work->f278)
    {
        out->vy = (in->vy - work->f278) & 0xFFF;
    }
}

void s01a_searchli_800D75C0(SearchlightWork *work)
{
    SVECTOR player;

    player = GM_PlayerPosition_800ABA10;
    player.vy = work->height;

    s01a_searchli_800D734C(&work->control.mov, &player, &work->control.turn);
    s01a_searchli_800D7500(&work->f260, &work->control.turn, work);
}

int s01a_searchli_800D763C(SearchlightWork *work)
{
    SVECTOR  player;
    SVECTOR *pos;
    SVECTOR *rot;

    pos = &work->control.mov;
    rot = &work->control.turn;

    player = GM_PlayerPosition_800ABA10;
    player.vy = work->height;

    s01a_searchli_800D734C(pos, &player, rot);
    s01a_searchli_800D7500(&work->f260, rot, work);

    if (work->f2A0 == 0)
    {
        s00a_command_800CEC40(pos, 64);
        COM_VibTime_800E0F68 = 10;
    }

    if (work->f2A0 < 0 || work->f2A0 > 14)
    {
        return 1;
    }

    work->f2A0++;
    return 0;
}

int s01a_searchli_800D770C(SearchlightWork *work)
{
    SVECTOR *rot;

    rot = &work->control.turn;
    if (work->f2A0 < 0 || work->f2A0 > 60)
    {
        rot->vy = (rot->vy + work->f27A) & 0xFFF;
        if (GV_DiffDirAbs_8001706C(work->f260.vy, rot->vy) > work->f26A)
        {
            rot->vy = work->f260.vy + work->f26A;
            return 1;
        }
    }

    work->f2A0++;
    return 0;
}

int s01a_searchli_800D77A4(SearchlightWork *work)
{
    SVECTOR *rot;

    rot = &work->control.turn;
    if (work->f2A0 < 0 || work->f2A0 > 60)
    {
        rot->vy = (rot->vy - work->f27A) & 0xFFF;
        if (GV_DiffDirAbs_8001706C(work->f260.vy, rot->vy) > work->f26A)
        {
            rot->vy = work->f260.vy - work->f26A;
            return 1;
        }
    }

    work->f2A0++;
    return 0;
}

void Searchli_800D783C(SearchlightWork *work)
{
  SVECTOR *rot;
  int rnd, vx, vy;

  if (!(work->f2A0 & 0x3F))
  {
    work->f2A0 += GV_RandU_80017090(16);

    work->control.field_54 = work->f27C;

    rot = &work->control.turn;

    rnd = rand();
    vy = work->f260.vy - work->f278 + (rnd * work->f278 * 2 >> 15);
    rot->vy = vy & 0xFFF;

    rot->vx = vx = rand() * (vx = work->f276) >> 15;
    s01a_searchli_800D7500(&work->f260, rot, work);
  }

  work->f2A0++;
}

int Searchli_800D7908(SearchlightWork *work)
{
    SVECTOR *from;
    SVECTOR *to;
    int      diff;

    from = &work->f260;
    to = &work->control.turn;

    diff = GV_DiffDirS_8001704C(from->vy, to->vy);
    if (diff < -10)
    {
        to->vy += 8;
    }
    else if (diff < 10)
    {
        to->vy = from->vy;
    }
    else
    {
        to->vy -= 8;
    }
    to->vy &= 0xFFF;

    diff = GV_DiffDirS_8001704C(from->vx, to->vx);
    if (diff < -10)
    {
        to->vx += 8;
    }
    else if (diff < 10)
    {
        to->vx = from->vx;
    }
    else
    {
        to->vx -= 8;
    }
    to->vx &= 0xFFF;

    if (to->vx == from->vx && to->vy == from->vy && (work->f2A0 < 0 || work->f2A0 > 96))
    {
        return 1;
    }

    work->f2A0++;
    return 0;
}

void Searchli_800D7A4C(SearchlightWork *work)
{
    switch (work->f29C)
    {
    case 2:
        if (s01a_searchli_800D770C(work))
        {
            work->f29C = 3;
            work->f2A0 = 0;
        }

        s01a_searchli_800D7500(&work->control.turn, &work->control.turn, work);

        if (s01a_searchli_800D73D8(work))
        {
            work->f29C = 1;
            work->f2A0 = 0;
        }
        break;

    case 3:
        if (s01a_searchli_800D77A4(work))
        {
            work->f29C = 2;
            work->f2A0 = 0;
        }

        s01a_searchli_800D7500(&work->control.turn, &work->control.turn, work);

        if (s01a_searchli_800D73D8(work))
        {
            work->f29C = 1;
            work->f2A0 = 0;
        }
        break;

    case 4:
        s01a_searchli_800D75C0(work);
        break;

    case 1:
        if (s01a_searchli_800D763C(work))
        {
            ENE_SetTopCommAL_800CEAE8(255);
            ENE_SetGopointLast_800CEB00();
            work->f294 = 1;
            work->f29C = 4;
            work->f2A0 = 0;
        }
        break;
    }

    if (TOPCOMMAND_800E0F20.mode == 1)
    {
        work->f294 = TOPCOMMAND_800E0F20.mode;

        do {} while (0);

        if (work->f294 == EnemyCommand_800E0D98.field_0x40)
        {
            work->f29C = 4;
        }
        else
        {
            work->f29C = 0;
        }

        work->f2A0 = 0;
    }
}

void Searchli_800D7BB8(SearchlightWork *work)
{
    switch (work->f29C)
    {
    case 4:
        s01a_searchli_800D75C0(work);

        if (s01a_searchli_800D73D8(work))
        {
            ENE_SetTopCommAL_800CEAE8(255);
            ENE_SetGopointLast_800CEB00();
        }
        break;

    case 0:
        if (s01a_searchli_800D73D8(work))
        {
            work->f29C = 4;
        }
        break;
    }

    if (TOPCOMMAND_800E0F20.mode != 1)
    {
        work->f294 = 2;
        work->f29C = 5;
        work->f2A0 = 0;
    }
}

void Searchli_800D7C58(SearchlightWork *work)
{
    switch (work->f29C)
    {
    case 5:
        Searchli_800D783C(work);

        if (TOPCOMMAND_800E0F20.mode == 0)
        {
            work->f29C = 6;
            work->f2A0 = 0;
        }
        break;

    case 6:
        if (Searchli_800D7908(work))
        {
            work->f294 = 0;
            work->f29C = 2;
            work->f2A0 = 0;
        }
        break;
    }

    if (s01a_searchli_800D73D8(work))
    {
        ENE_SetTopCommAL_800CEAE8(255);
        ENE_SetGopointLast_800CEB00();
        s00a_command_800CEC40(&work->control.mov, 64);
        COM_VibTime_800E0F68 = 10;
        work->f294 = 1;
        work->f29C = 4;
        work->f2A0 = 0;
    }
    else if (TOPCOMMAND_800E0F20.mode == 1)
    {
        work->f294 = 1;
        work->f29C = 4;
        work->f2A0 = 0;
    }
}

void Searchli_800D7D40(SearchlightWork *work)
{
    switch (work->f294)
    {
    case 0:
        Searchli_800D7A4C(work);
        break;

    case 1:
        Searchli_800D7BB8(work);
        break;

    case 2:
        Searchli_800D7C58(work);
        break;
    }
}

// $13 replaced with $14 in gte_ld_intpol_sv0_xz
#define gte_ld_intpol_sv0_xz(r0)                                                                                       \
    __asm__ volatile("lh     $12, 0( %0 );"                                                                            \
                     "lh     $14, 4( %0 );"                                                                            \
                     "ctc2   $12, $21;"                                                                                \
                     "ctc2   $14, $23"                                                                                 \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12", "$14")

#define gte_ld_intpol_sv1_xz(r0)                                                                                       \
    __asm__ volatile("lhu    $12, 0( %0 );"                                                                            \
                     "lhu    $13, 4( %0 );"                                                                            \
                     "mtc2   $12, $9;"                                                                                 \
                     "mtc2   $13, $11"                                                                                 \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12", "$13")

#define gte_stsv_xz(r0)                                                                                                \
    __asm__ volatile("mfc2 $12, $9;"                                                                                   \
                     "mfc2 $14, $11;"                                                                                  \
                     "sh   $12, 0( %0 );"                                                                              \
                     "sh   $0,  2( %0 );"                                                                              \
                     "sh   $14, 4( %0 )"                                                                               \
                     :                                                                                                 \
                     : "r"(r0)                                                                                         \
                     : "$12", "$13", "$14", "memory")

void Searchli_800D7DBC(SVECTOR *in, SVECTOR *out, int count)
{

    SVECTOR *scratch;
    SVECTOR *var_a0;
    SVECTOR *var_t0;
    int      temp_lo;
    int      temp_t7;
    int      i;
    int      j;
    int      total;
    int      num;
    int      temp;
    int      one;

    temp_t7 = count + 1;
    temp_lo = temp_t7 * temp_t7;
    scratch = (SVECTOR *)0x1F800000;

    total = 4096 / count;

    scratch[0] = in[0];
    scratch[count] = in[1];
    scratch[temp_lo - temp_t7] = in[2];
    one = 1;
    scratch[temp_lo - one] = in[3];

    var_t0 = scratch;

    for (i = 2; i > 0; i--)
    {
        var_a0 = var_t0 + (temp_t7 - 1);
        gte_ld_intpol_sv0_xz(var_a0);

        var_a0 = var_t0;
        num = total;
        for (j = count - 1; j > 0; j--)
        {
            gte_ld_intpol_sv1_xz(var_t0);
            gte_lddp(num);

            num += total;
            var_a0++;

            gte_intpl_b();
            gte_stsv_xz(var_a0);
        }

        var_t0 = scratch + (temp_lo - temp_t7);
    }

    var_t0 = scratch;
    for (i = temp_t7; i > 0; i--)
    {
        var_a0 = var_t0 + (temp_lo - temp_t7);
        gte_ld_intpol_sv0_xz(var_a0);

        var_a0 = var_t0;

        num = total;
        for (j = count - 1; j > 0; j--)
        {
            gte_ld_intpol_sv1_xz(var_t0);
            gte_lddp(num);

            num += total;
            var_a0 += temp_t7;

            gte_intpl_b();
            gte_stsv_xz(var_a0);
        }

        var_t0++;
    }

    temp = temp_t7 + 1;
    var_t0 = scratch;
    for (i = count; i > 0; i--)
    {
        for (j = count; j > 0; j--)
        {
            out[0] = var_t0[0];
            out[1] = var_t0[1];
            out[2] = var_t0[temp_t7];
            out[3] = var_t0[temp];
            out += 4;
            var_t0++;
        }

        var_t0++;
    }
}

void Searchli_800D80AC(SVECTOR *vec, int x, int y, int z)
{
    vec->vx = x;
    vec->vy = y;
    vec->vz = z;
}

void Searchli_800D80BC(SearchlightWork *work)
{
    SVECTOR sp18;
    VECTOR  sp20;
    VECTOR  sp30;
    SVECTOR pos;
    SVECTOR rot;

    SearchlightSub *sp50;

    SVECTOR *temp_fp;
    SVECTOR *temp_s0_8;
    SVECTOR *temp_t0;
    int      var_s4;
    int      temp_a1;
    int      dx, dy, dz;
    int      dx2, dy2, dz2; // probably inline related
    int      temp_s0_2;
    int      temp_s0_7;
    int      temp_s1_2;
    int      temp_s2_2;
    int      temp_s6;
    int      shade;
    int      var_s5;
    int      target;

    sp50 = &work->fFC;
    temp_fp = &work->fFC.f244;
    temp_t0 = &sp50->fFC;

    if (GM_WhereList_800B56D0[0]->name != CHARA_SNAKE)
    {
        return;
    }
    var_s4 = GM_PlayerBody_800ABA20->objs->objs[6].world.t[1] - work->height;

    if (var_s4 < 300)
    {
        var_s4 = 10;
    }
    else if (var_s4 > 1000)
    {
        var_s4 += 300;
    }

    if ((work->f2B4 != 0) || (var_s4 < 0))
    {
        if (work->f2A8 < (work->f272 / 4))
        {
            shade = 78;
        }
        else
        {
            shade = ((work->f2A8 - (work->f272 / 4)) * 78) / (work->f272 / 4);
        }

        s01a_searchli_800D7320(work->fFC.prim, work->fFC.tex, shade, shade, shade);

        DG_VisiblePrim(work->fFC.prim);
        dword_800ABA1C |= 1 << (work->f26E + 1);
    }
    else
    {
        DG_InvisiblePrim(work->fFC.prim);
        dword_800ABA1C &= ~(1 << (work->f26E + 1));
        return;
    }

    dx = GM_PlayerPosition_800ABA10.vx - work->control.mov.vx;
    dy = GM_PlayerBody_800ABA20->objs->objs[6].world.t[1] - work->control.mov.vy;
    dz = GM_PlayerPosition_800ABA10.vz - work->control.mov.vz;

    target = 1024;

    temp_s0_2 = ratan2(dy, SquareRoot0(dx * dx + dz * dz)) + target;

    if ((temp_s0_2 & 0x7FF) != target)
    {
        var_s5 = (var_s4 * rsin(temp_s0_2)) / rcos(temp_s0_2);
    }
    else
    {
        var_s5 = var_s4 * rsin(temp_s0_2);
    }

    temp_t0->vy = ratan2(dx, dz);

    sp18 = GM_PlayerPosition_800ABA10;
    sp18.vy = GM_PlayerBody_800ABA20->objs->objs[6].world.t[1];

    s01a_800E2364(&work->lit_mtx, &sp18, &sp20);

    sp20.vx >>= 2;
    sp20.vy >>= 2;
    sp20.vz >>= 2;

    Square0(&sp20, &sp30);

    temp_s2_2 = ratan2(SquareRoot0(sp30.vx + sp30.vy), sp20.vz) & 0xFFF;
    if (temp_s2_2 > (work->f272 / 2))
    {
        temp_s6 = (rsin(work->f272 / 2) * 4096) / rcos(work->f272 / 2);
        temp_s1_2 = (rsin(work->f2A8) * 4096) / rcos(work->f2A8);
        temp_s0_7 = (rsin(temp_s2_2) * 4096) / rcos(temp_s2_2) - temp_s1_2;

        if (temp_s0_7 != 0)
        {
            var_s5 = (var_s5 * (temp_s6 - temp_s1_2)) / temp_s0_7;
        }
        else
        {
            var_s5 = 0;
        }
    }

    temp_a1 = -200 - var_s5;
    temp_s0_8 = &sp50->f104;

    Searchli_800D80AC(temp_s0_8, temp_a1, 0, temp_a1);

    *temp_fp = GM_PlayerPosition_800ABA10;
    temp_fp->vy = var_s4;

    temp_t0->vy = (temp_t0->vy + 1536) & 0xFFF;
    temp_fp->vy = work->height + 10;

    Searchli_800D7DBC(temp_s0_8, sp50->pad2, 3);

    DG_SetPos2_8001BC8C(temp_fp, temp_t0);
    DG_PutPrim_8001BE00(&sp50->prim->world);

    pos = s01a_svec_800E4660;

    dx2 = GM_PlayerPosition_800ABA10.vx - work->control.mov.vx;
    dy2 = GM_PlayerPosition_800ABA10.vy - work->control.mov.vy;
    dz2 = GM_PlayerPosition_800ABA10.vz - work->control.mov.vz;

    rot.vx = ratan2(dy2, SquareRoot0(dx2 * dx2 + dz2 * dz2)) + 1024;
    rot.vy = work->control.rot.vy;
    rot.vz = 0;

    DG_SetPos2_8001BC8C(&GM_PlayerControl_800AB9F4->mov, &rot);
    DG_PutVector_8001BE48(&pos, &pos, 1);
    DG_SetTmpLight_8001A114(&pos, 1024, 2000);
}

void SearchlightAct_800D86F0(SearchlightWork *work)
{
    SVECTOR  pos;
    VECTOR   sp18;
    VECTOR   sp28;
    SVECTOR  center;
    int      f2A8;
    int      status;

    GM_ActControl_80025A7C(&work->control);

    DG_SetPos2_8001BC8C(&work->control.mov, &work->control.rot);
    ReadRotMatrix(&work->lit_mtx);

    if (GM_CurrentItemId == ITEM_STEALTH)
    {
        work->f2A4 = 0;
        work->f2B4 = 0;
    }
    else
    {
        // Snake detected by searchlight logic
        pos.vx = GM_PlayerPosition_800ABA10.vx;
        pos.vz = GM_PlayerPosition_800ABA10.vz;
        pos.vy = work->height;

        s01a_800E2364(&work->lit_mtx, &pos, &sp18);

        sp18.vx >>= 2;
        sp18.vy >>= 2;
        sp18.vz >>= 2;

        Square0(&sp18, &sp28);

        f2A8 = ratan2(SquareRoot0(sp28.vx + sp28.vy), sp18.vz) & 0xFFF;
        work->f2A8 = f2A8;
        work->f2AC = SquareRoot0(sp28.vx + sp28.vy + sp28.vz);

        if ((work->angle / 2) < f2A8)
        {
            work->f2A4 = 0;
        }
        else
        {
            work->f2A4 = 1;
        }

        if (f2A8 < (work->f272 / 2))
        {
            work->f2B4 = 1;
        }
        else
        {
            work->f2B4 = 0;
        }
    }

    if ((work->debug != 0) && (GV_PadData_800B05C0[1].status & PAD_SQUARE))
    {
        status = GV_PadData_800B05C0[1].status;

        if ((GV_PadData_800B05C0[1].press & PAD_TRIANGLE) && (++work->debug >= 4))
        {
            work->debug = 1;
        }

        MENU_Locate_80038B34(8, 180, 0);

        switch (work->debug - 1)
        {
        case 0:
            MENU_Printf_80038C38(aSearchliUDRotXLRRotY);

            if (status & PAD_UP)
            {
                work->control.turn.vx -= 5;
            }

            if (status & PAD_DOWN)
            {
                work->control.turn.vx += 5;
            }

            if (status & PAD_LEFT)
            {
                work->control.turn.vy += 5;
            }

            if (status & PAD_RIGHT)
            {
                work->control.turn.vy -= 5;
            }
            break;

        case 1:
            MENU_Printf_80038C38(aSearchliUDPosXLRPosZ);

            if (status & PAD_UP)
            {
                work->control.mov.vz -= 20;
            }

            if (status & PAD_DOWN)
            {
                work->control.mov.vz += 20;
            }

            if (status & PAD_LEFT)
            {
                work->control.mov.vx -= 20;
            }

            if (status & PAD_RIGHT)
            {
                work->control.mov.vx += 20;
            }
            break;

        case 2:
            MENU_Printf_80038C38(aSearchliUDPosYLRAngle);

            if (status & PAD_UP)
            {
                work->control.mov.vy += 20;
            }

            if (status & PAD_DOWN)
            {
                work->control.mov.vy -= 20;
            }

            if (status & PAD_LEFT)
            {
                work->angle = sub_8002646C(work->angle, 0, 5);
            }

            if (status & PAD_RIGHT)
            {
                work->angle = sub_8002646C(work->angle, 512, 5);
            }
            break;
        }

        MENU_Printf_80038C38(aSearchliRot7D7D7D, work->control.turn.vx, work->control.turn.vy, work->control.turn.vz);
        MENU_Printf_80038C38(aSearchliPos7D7D7D, work->control.mov.vx, work->control.mov.vy, work->control.mov.vz);
        MENU_Printf_80038C38(aSearchliAngle4D, work->angle);

        s01a_lit_mdl_800E2D3C(work->lit_mdl, work->angle);

        if (status & PAD_L2)
        {
            center = SearchliCenter_800E46D8;
            DG_SetPos2_8001BC8C(&work->control.mov, &work->control.turn);
            DG_PutVector_8001BE48(&center, &center, 1);
            DG_LookAt_800172D0(DG_Chanl(0), &work->control.mov, &center, 320);
        }
        else
        {
            s01a_object_800D9424(&work->control, 2);
        }

        Searchli_800D80BC(work);
    }
    else
    {
        Searchli_800D80BC(work);

        if (work->debug == 0)
        {
            Searchli_800D7D40(work);
        }
    }
}

int Searchlight_800D8B84(SearchlightWork *work, int name, int map)
{
    int opt;

    opt = (int)GCL_GetOption_80020968('i');
    work->f26E = GCL_StrToInt_800209E8(opt ? (char *)opt : "0");

    opt = (int)GCL_GetOption_80020968('w');
    work->f268 = GCL_StrToInt_800209E8(opt ? (char *)opt : "0");
    if (work->f268 > 4000)
    {
        work->f268 = 4000;
    }

    opt = (int)GCL_GetOption_80020968('x');
    work->f26A = GCL_StrToInt_800209E8(opt ? (char *)opt : "0");
    if (work->f26A > 1024)
    {
        work->f26A = 1024;
    }

    opt = (int)GCL_GetOption_80020968('h');
    work->height = GCL_StrToInt_800209E8(opt ? (char *)opt : "0");
    if (work->height > 30000)
    {
        work->height = 30000;
    }

    work->f260 = work->control.rot;
    if (work->f260.vx > 1000)
    {
        work->f260.vx = 1000;
    }

    work->angle = 300;
    if (GCL_GetOption_80020968('a'))
    {
        work->angle = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    if (GCL_GetOption_80020968('l'))
    {
        work->f272 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    work->f272 += work->angle;

    if (GCL_GetOption_80020968('t'))
    {
        work->f274 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f276 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f26A = work->f278 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f27A = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->f274 = 280;
        work->f276 = 330;
        work->f278 = 512;
        work->f27A = 4;
    }

    work->f27C = 48;

    if (GCL_GetOption_80020968('z'))
    {
        work->debug = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    work->f294 = 0;
    work->f29C = 2;
    work->f2A0 = 0;
    work->f2B0 = 100000;

    return 0;
}

void Searchli_800D8DDC(POLY_FT4 *packs, DG_TEX *tex, int abr, int r, int g, int b, int size)
{
    int xs, ys;
    int x, y;
    int u0, u1, v0, v1;
    int u, v, w, h;

    xs = size;
    ys = size;

    for (y = 0; y < ys; y++)
    {
        for (x = 0; x < xs; x++)
        {
            setPolyFT4(packs);
            setRGB0(packs, r, g, b);

            if (abr < 4)
            {
                setSemiTrans(packs, 1);

                u0 = tex->field_8_offx + ((tex->field_A_width + 1) * x) / xs;
                u1 = tex->field_8_offx + ((tex->field_A_width + 1) * (x + 1)) / xs - 1;
                packs->u0 = packs->u2 = u0;
                packs->u1 = packs->u3 = u1;

                v0 = tex->field_9_offy + ((tex->field_B_height + 1) * y) / ys;
                v1 = tex->field_9_offy + ((tex->field_B_height + 1) * (y + 1)) / ys - 1;
                packs->v0 = packs->v1 = v0;
                packs->v2 = packs->v3 = v1;

                packs->tpage = tex->field_4_tPage;
                packs->clut = tex->field_6_clut;

                packs->tpage = (packs->tpage & ~0x60) | (abr << 5);
            }
            else
            {
                u = tex->field_8_offx;
                w = tex->field_A_width;
                v = tex->field_9_offy;
                h = tex->field_B_height;
                setUVWH(packs, u, v, w, h);
                packs->tpage = tex->field_4_tPage;
                packs->clut = tex->field_6_clut;
            }

            packs++;
        }
    }
}

int Searchli_800D9040(SearchlightWork *work)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    Searchli_800D80AC(&work->fFC.f244, 0, 0, 0);
    Searchli_800D80AC(&work->fFC.fFC, 0, 0, 0);
    Searchli_800D80AC(&work->fFC.f104, -200, 0, -200);
    Searchli_800D80AC(&work->fFC.f10C, 200, 0, -200);
    Searchli_800D80AC(&work->fFC.f114, -200, 0, 200);
    Searchli_800D80AC(&work->fFC.f11C, 200, 0, 200);

    prim = DG_GetPrim(0x12, 9, 0, work->fFC.pad2, NULL);
    work->fFC.prim = prim;
    if (prim == NULL)
    {
        return -1;
    }

    prim->field_2E_k500 = 600;

    tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC("shadow"));
    work->fFC.tex = tex;
    if (tex == NULL)
    {
        return -1;
    }

    Searchli_800D8DDC(&prim->packs[0]->poly_ft4, tex, 2, 78, 78, 78, 3);
    Searchli_800D8DDC(&prim->packs[1]->poly_ft4, tex, 2, 78, 78, 78, 3);
    return 0;
}

int SearchlightGetResources_800D91B0(SearchlightWork *work, int name, int map)
{
    CONTROL *control;
    char    *pos, *dir;

    control = &work->control;

    if (GM_InitLoader_8002599C(control, name, map) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption_80020968('p');
    dir = GCL_GetOption_80020968('d');

    GM_ConfigControlString_800261C0(control, pos, dir);
    GM_ConfigControlAttribute_8002623C(control, 0);
    GM_ConfigControlHazard_8002622C(control, -1, -2, -1);
    work->control.step = DG_ZeroVector_800AB39C;

    Searchli_800D9040(work);
    return 0;
}

void SearchlightDie_800D9274(SearchlightWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl_800260CC(&work->control);

    prim = work->fFC.prim;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

GV_ACT * NewSearchlight_800D92BC(int name, int where, int argc, char **argv)
{
    SearchlightWork *work;

    work = (SearchlightWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(SearchlightWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)SearchlightAct_800D86F0,
                                  (TActorFunction)SearchlightDie_800D9274, "searchli.c");

        if (SearchlightGetResources_800D91B0(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        Searchlight_800D8B84(work, name, where);

        work->lit_mtx = DG_ZeroMatrix_8009D430;
        work->lit_mdl = s01a_lit_mdl_800E2C88(&work->lit_mtx, work->height, work->f272, 500);
    }

    return &work->actor;
}
