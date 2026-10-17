#include "valcan.h"

#include "mts/mts.h"
#include "libgcl/libgcl.h"

#include "okajima/bullet.h"     // for NewBulletEx
#include "okajima/blood.h"      // for NewBlood
#include "sound/g_sound.h"

SVECTOR valcan_muzzle_offset_800C3600 = {10, -2500, -70};
SVECTOR valcan_blood_offset_800C3608 = {0, 0, 100};
SVECTOR valcan_blood_rot_800C3610 = {-1024, 0, 0};

int SECTION(".bss") valcan_800E3480;
int SECTION(".bss") valcan_800E3484;

extern int     dword_8009F480;
extern int     dword_8009F49C;
extern int     amissile_alive_8009F490;
extern SVECTOR svector_8009F478;
extern SVECTOR svector_8009F494;
extern int     dword_8009F46C[];

void AN_HeadMark(MATRIX *world, int index);

void Valcan_800D9AB8(Work *work)
{
    CONTROL *control;

    control = &work->control;
    control->height = work->field_A0.height;
    control->r_sphere = GV_NearExp2(control->r_sphere, 450);

    if (work->field_66C < 0 && control->grounded != 0)
    {
        work->field_66C = 0;
    }
    work->field_66C -= 16;

    control->step.vy = work->field_66C;
}


void Valcan_800D9B3C(Work *work)
{
    Valcan_800DD578(work);
}


void Valcan_800D9B5C(Work *work)
{
    SVECTOR unused;

    Valcan_800DD03C(work);
    switch (work->field_90C)
    {
    case 0:
        work->field_90C = 1;
        break;

    case 1:
        work->field_90C = 2;
        Valcan_800D99F0(work);

    case 2:
        Valcan_800D990C(work);
        break;
    }

    Valcan_800D9AB8(work);

    unused.vx = 0;
    unused.vy = -730;
    unused.vz = -150;

    work->field_184.objs->root = &work->field_A0.objs->objs[4].world;
    GM_ActObject2(&work->field_184);

    if (GM_Item == IT_ThermG)
    {
        DG_AmbientObjs(work->field_184.objs);
    }
    else
    {
        DG_UnAmbientObjs(work->field_184.objs);
    }

    DG_GetLightMatrix2(&work->control.mov, work->field_624);

    switch (work->field_91C)
    {
    case 1:
        work->field_6B4 = 0;
        work->field_91C = 2;
        work->field_918 = 0;
        GM_SeSetMode(&work->field_910, 180, GM_SEMODE_BOMB);

    case 2:
        work->field_918++;
        work->field_6B4 += 20;
        if (work->field_918 >= 16)
        {
            work->field_91C = 3;
            work->field_918 = 0;
        }
        break;
    case 3:
        if (mts_get_tick_count() - work->field_6BC >= 4)
        {
            work->field_6BC = mts_get_tick_count();
            GM_SeSetMode(&work->field_910, 179, GM_SEMODE_BOMB);
        }
        break;

    default:
        work->field_6B4 -= 6;
        if (work->field_6B4 < 0)
        {
            work->field_6B4 = 0;
        }
        else if (mts_get_tick_count() - work->field_6BC > work->field_918 + 4)
        {
            work->field_918 += 6;
            work->field_6BC = mts_get_tick_count();
        }
        break;
    }
    work->field_184.rots[1].vy += work->field_6B4;
}

void Valcan_800D9D90(Work *work)
{
    RADAR_SIGHT_PARAM *r_param;

    work->control.radar_param.dir = work->control.rot.vy + work->field_5A4[6].vy;

    r_param = &work->control.radar_param;
    r_param->dis = work->field_944;
    r_param->range = work->field_948;
    r_param->r = 0;
}

int Valcan_800D9DC0(Work *work, int param_2)
{
    SVECTOR svec1, pos;
    int     vx, vy, vz;

    svec1.vx = work->field_A0.objs->objs[4].world.t[0];
    svec1.vy = work->field_A0.objs->objs[4].world.t[1];
    svec1.vz = work->field_A0.objs->objs[4].world.t[2];

    if (param_2)
    {
        pos = GM_PlayerPosition;
    }
    else
    {
        pos = work->field_51C;
    }

    vx = (svec1.vx - pos.vx) >> 4;
    vy = (svec1.vy - pos.vy) >> 4;
    vz = (svec1.vz - pos.vz) >> 4;
    return SquareRoot0(vx * vx + vy * vy + vz * vz) * 16;
}

// Identical to Eventmouse_800C9288
void Valcan_800D9EBC(SVECTOR *from, SVECTOR *to, SVECTOR *out)
{
    SVECTOR diff;
    int     y;

    GV_SubVec3(to, from, &diff);
    out->vy = ratan2(diff.vx, diff.vz) & 0xFFF;

    y = diff.vy;
    diff.vy = 0;

    out->vx = (ratan2(GV_VecLen3(&diff), y) & 0xFFF) - 1024;
    out->vz = 0;
}

void Valcan_800D9F3C(Work *work, int count)
{
    SVECTOR *out;
    int      i;

    out = work->field_5A4;
    work->field_690 = 0;
    for (i = 0; i < count; i++, out++)
    {
        *out = DG_ZeroVector;
    }
}

void Valcan_800D9F8C(Work *work)
{
    if (dword_8009F46C[0] == 1)
    {
        work->field_51C = svector_8009F478;
        return;
    }
    work->field_82C = 0;
    if (amissile_alive_8009F490 == 1)
    {
        work->field_51C = svector_8009F494;
        return;
    }
    work->field_838 = 0;
    work->field_51C = GM_PlayerPosition;
}

void Valcan_800DA044(Work *work)
{
    // FIXME: why does this function do everything on stack?
    // FIXME: is there a better for loop match (without those strange break/continues)?
    short sp0[6];

    sp0[4] = (work->field_6F8[1][0][0] - work->field_6F8[0][0][0]) / 2;
    sp0[5] = (work->field_6F8[0][1][1] - work->field_6F8[0][0][1]) / 2;

    sp0[0] = 0;
    for (;;)
    {
        if (work->control.mov.vx >= work->field_6F8[sp0[0]][0][0] + sp0[4])
        {
            if (++sp0[0] < 4)
            {
                continue;
            }
        }
        break;
    }

    sp0[1] = 0;
    for (;;)
    {
        if (work->control.mov.vz >= work->field_6F8[0][sp0[1]][1] + sp0[5])
        {
            if (++sp0[1] < 4)
            {
                continue;
            }
        }
        break;
    }

    work->field_7A0 = sp0[0];
    work->field_7A2 = sp0[1];
}

void Valcan_800DA140(Work *work)
{
    if (work->field_690 >= 48)
    {
        if (work->field_690 < 144)
        {
            work->field_5A4[6].vy -= 8;
        }
        else if (work->field_690 < 192)
        {
            work->field_5A4[6].vy += 8;
        }
    }
    else
    {
        work->field_5A4[6].vy += 8;
    }

    if (++work->field_690 >= 192)
    {
        work->field_690 = 0;
    }
}

int Valcan_800DA1AC(int arg0, int arg1)
{
    if (arg0 < 2)
    {
        arg0 = 1 - arg0;
    }

    arg0 = 1 - arg0 % 2 * 2;
    arg1 = 1 - (arg1 - (arg1 / 2 * 2)) * 2;

    return (arg0 * arg1 + 1) / 2 + 2;
}

void Valcan_800DA21C(Work *work) // it possibly returns a BulletWork*
{
    MATRIX  rotmat;
    SVECTOR svec;

    Valcan_800D9EBC(&work->control.mov, &GM_PlayerPosition, &svec);
    DG_SetPos2(&GM_PlayerPosition, &svec);
    ReadRotMatrix(&rotmat);
    NewBulletEx(BULLET_BLAST, &rotmat, 2, 0, 0, 30, 90, 30000, 100);
}

int Valcan_800DA2A8(Work *work)
{
    short   pos[2];
    short   idx[2];
    SVECTOR target;
    int     p;

    if (work->field_93C != 1 && GV_RandU(4) > 0)
    {
        return -1;
    }

    if (work->field_770 >= 2 && work->field_770 <= 3)
    {
        idx[0] = work->field_738;
        idx[1] = work->field_73A;
    }
    else
    {
        idx[0] = work->field_73C;
        idx[1] = work->field_73E;
    }

    pos[0] = work->field_6F8[idx[0]][idx[1]][0];
    pos[1] = work->field_6F8[idx[0]][idx[1]][1];
    target = work->field_51C;

    switch (work->field_740)
    {
    case 0:
    case 1:
        if (dyncon_800E3458[0] != 0 && (u_short)idx[1] < 2 && idx[0] == 1)
        {
            return -1;
        }
        if (dyncon_800E3458[3] != 0 && (u_short)idx[1] - 2U < 2 && idx[0] == 2)
        {
            return -1;
        }
        p = pos[1];
        if (p < target.vz && p < 9000)
        {
            return Valcan_800DA1AC(work->field_740, 3);
        }
        if (target.vz < p && p > -6000)
        {
            return Valcan_800DA1AC(work->field_740, 2);
        }
        break;

    case 2:
    case 3:
        if (dyncon_800E3458[1] != 0 && (u_short)idx[0] - 2U < 2 && idx[1] == 1)
        {
            return -1;
        }
        if (dyncon_800E3458[2] != 0 && (u_short)idx[0] < 2 && idx[1] == 2)
        {
            return -1;
        }
        p = pos[0];
        if (p < target.vx && p < 9000)
        {
            return Valcan_800DA1AC(work->field_740, 1);
        }
        if (target.vx < p && p > -9000)
        {
            return Valcan_800DA1AC(work->field_740, 0);
        }
        break;
    }

    return -1;
}

int Valcan_800DA558(Work *work, int arg1)
{
    SVECTOR svec1;
    SVECTOR svec2;
    SVECTOR svec3;
    int     diffdir;
    int     var_s0;
    int     flag;

    svec1.vx = work->field_A0.objs->objs[4].world.t[0];
    svec1.vy = work->field_A0.objs->objs[4].world.t[1];
    svec1.vz = work->field_A0.objs->objs[4].world.t[2];

    Valcan_800D9EBC(&svec1, &work->field_51C, &svec2);
    diffdir =
        GV_DiffDirAbs(svec2.vy, work->control.rot.vy + work->field_5A4[1].vy + work->field_5A4[6].vy);
    if (arg1 != 0)
    {
        svec3.vx = -800;
        svec3.vy = 0;
        svec3.vz = 0;
        DG_SetPos2(&svec1, &svec2);
        DG_PutVector(&svec3, &svec1, 1);
    }

    flag = 0;
    var_s0 = 0;
    if (dword_8009F46C[0] == 1 || amissile_alive_8009F490 == 1)
    {
        if (HZD_OnlineHazardCheck(work->control.map->hzd, &svec1, &work->field_51C, HZD_CHK_SEGMENT, SEGMENT_ATR) == 0)
        {
            if (HZD_OnlineHazardCheck(work->control.map->hzd, &svec1, &GM_PlayerPosition, HZD_CHK_SEGMENT, SEGMENT_ATR) == 0)
            {
                var_s0 = Valcan_800D9DC0(work, 1);
                if (var_s0 < work->field_68C)
                {
                    work->field_51C = GM_PlayerPosition;
                    flag = 1;
                }
            }
            if (work->field_93C != 0 && amissile_alive_8009F490 == 1)
            {
                work->field_838 = amissile_alive_8009F490;
                return 1;
            }
        }
        else if (HZD_OnlineHazardCheck(work->control.map->hzd, &svec1, &GM_PlayerPosition, HZD_CHK_SEGMENT, SEGMENT_ATR) == 0)
        {
            var_s0 = Valcan_800D9DC0(work, 1);
            flag = 1;
            work->field_51C = GM_PlayerPosition;
        }
        else
        {
            work->field_788 = 0;
            return 0;
        }
    }
    else if (HZD_OnlineHazardCheck(work->control.map->hzd, &svec1, &GM_PlayerPosition, HZD_CHK_SEGMENT, SEGMENT_ATR) != 0)
    {
        work->field_788 = 0;
        return 0;
    }
    else
    {
        var_s0 = Valcan_800D9DC0(work, 1);
        flag = 1;
    }

    if (!flag)
    {
        if (diffdir > 512)
        {
            return work->field_68C < 3500;
        }

        work->field_7A4 = svec2;

        if (dword_8009F46C[0] == 1 && work->field_950 < 0)
        {
            work->field_82C = dword_8009F46C[0];
        }
        else if (amissile_alive_8009F490 == 1)
        {
            work->field_838 = 1;
        }
        else
        {
            work->field_93C = 0;
        }
        return 1;
    }
    else if (var_s0 < 3000)
    {
        if (diffdir < 256)
        {
            if (!(GM_PlayerStatus & (PLAYER_INVINCIBLE | PLAYER_DAMAGED | PLAYER_NOT_PLAYABLE)))
            {
                GM_SeSet2(0, 0x7F, SE_HIT);
                Valcan_800DA21C(work);
            }
        }
        return 1;
    }
    else if (diffdir > 512)
    {
        if (work->field_68C < 4000 || work->field_924 > 0)
        {
            return 1;
        }

        return 0;
    }
    else
    {
        work->field_7A4 = svec2;
        work->field_93C = 0;
    }
    return 1;
}

void Valcan_800DA8E4(Work *work)
{
    SVECTOR  svecs[2];
    CONTROL *control;

    control = &work->control;

    svecs[0].vx = GV_RandU(512);
    svecs[0].vy = GV_RandU(512) + 256;
    svecs[0].vz = 500;
    svecs[1].vx = GV_RandU(256);
    svecs[1].vy = GV_RandU(256);
    svecs[1].vz = 200;

    DG_SetPos2(&control->mov, &control->rot);
    DG_PutVector(svecs, svecs, 2);

    DG_SetTmpLight(svecs, 500, 1000);
    DG_SetTmpLight(svecs, 500, 500);
}

void Valcan_800DA990(Work *work)
{
    MATRIX  mat;
    SVECTOR rot;
    int     damage;

    if (work->field_830 == 0 && work->field_82C == 1)
    {
        work->field_830 = work->field_82C;
        work->field_834 = GV_RandU((work->field_770 != 3) ? 2 : 32) + 3;
    }

    if (work->field_830 == 1 && --work->field_834 == 0)
    {
        dword_8009F480 = 1;
        work->field_950 = 3;
        work->field_82C = 0;
        work->field_830 = 0;
    }

    if (work->field_83C == 0 && work->field_838 == 1)
    {
        work->field_83C = work->field_838;
        work->field_840 = GV_RandU(2) + 12;
    }

    if (work->field_83C == 1 && --work->field_840 == 0)
    {
        dword_8009F49C = 1;
        work->field_838 = 0;
        work->field_83C = 0;
    }

    if (work->field_6A4 % 5 != 0)
    {
        return;
    }

    if (work->field_8DC++ >= 2)
    {
        work->field_8DC = 0;
        if (work->field_8F0 != 0)
        {
            if (work->field_6A4 % 100 == 0)
            {
                switch (GV_RandU(4))
                {
                case 0:
                    GM_SeSetMode(&work->field_910, SE_V_ENE_GRENADE, GM_SEMODE_BOMB);
                    break;
                case 1:
                    GM_SeSetMode(&work->field_910, SE_V_ENE_HUH, GM_SEMODE_BOMB);
                    break;
                case 2:
                case 3:
                    GM_SeSetMode(&work->field_910, SE_V_ENE_RETURN, GM_SEMODE_BOMB);
                    break;
                }
            }
            else if (work->field_6A4 % 100 == 50 && GV_RandU(2) == 0)
            {
                GM_SeSetMode(&work->field_910, SE_V_ENE_LOST, GM_SEMODE_BOMB);
            }
        }
    }

    switch (GM_GameLevel)
    {
    case GM_LEVEL_VERYEASY:
    case GM_LEVEL_EASY:
    default:
        damage = 90;
        break;
    case GM_LEVEL_NORMAL:
        damage = 135;
        break;
    case GM_LEVEL_HARD:
        damage = 180;
        break;
    case GM_LEVEL_EXTREME:
        damage = 225;
        break;
    }

    if (work->field_91C == 0)
    {
        work->field_91C = 1;
        return;
    }

    if (GM_GameLevel == GM_LEVEL_EXTREME)
    {
        work->field_5A4[1].vy += GV_RandS(32);
    }

    DG_SetPos(&work->field_A0.objs->objs[4].world);
    DG_MovePos(&valcan_muzzle_offset_800C3600);
    rot.vx = 1024;
    rot.vy = 0;
    rot.vz = 0;
    DG_RotatePos(&rot);
    ReadRotMatrix(&mat);
    NewBulletEx(0x920, &mat, 2, 1, 0, 30, damage, 30000, 1000);
    Valcan_800DA8E4(work);
}

void Valcan_800DACCC(Work *work)
{
    if (work->field_758 != 0)
    {
        return;
    }

    switch (work->field_740)
    {
    case 0:
        Valcan_800DA044(work);
        work->control.mov.vz = work->field_6F8[work->field_7A0][work->field_7A2][1];
        if (work->field_6C4.vx < work->field_754)
        {
            work->field_758 = -1;
        }
        break;
    case 1:
        Valcan_800DA044(work);
        work->control.mov.vz = work->field_6F8[work->field_7A0][work->field_7A2][1];
        if (work->field_6C4.vx > work->field_754)
        {
            work->field_758 = -1;
        }
        break;
    case 2:
        Valcan_800DA044(work);
        work->control.mov.vx = work->field_6F8[work->field_7A0][work->field_7A2][0];
        if (work->field_6C4.vz < work->field_756)
        {
            work->field_758 = -1;
        }
        break;
    case 3:
        Valcan_800DA044(work);
        work->control.mov.vx = work->field_6F8[work->field_7A0][work->field_7A2][0];
        if (work->field_6C4.vz > work->field_756)
        {
            work->field_758 = -1;
        }
        break;
    }
}

int Valcan_800DAE38()
{
    return GV_RandU(4096) % 3 + 1;
}

int Valcan_800DAE7C(Work *work)
{
    int ret;

    work->field_828 = 0;

    ret = Valcan_800DA2A8(work);
    work->field_79C = ret;
    if (ret != -1)
    {
        return ret;
    }

    switch (work->field_740)
    {
    case 0:
        if (work->field_738 == 1)
        {
            work->field_828 = 1;
            return 1;
        }
        if (dyncon_800E3458[2] != 0 && work->field_738 == 2 && work->field_73A == 2)
        {
            return Valcan_800DAE38();
        }
        break;

    case 1:
        if (work->field_738 == 2)
        {
            work->field_828 = 1;
            return 1;
        }
        if (dyncon_800E3458[1] != 0 && work->field_738 == 1 && work->field_73A == 1)
        {
            return Valcan_800DAE38();
        }
        break;

    case 2:
        if (work->field_73A == 1)
        {
            work->field_828 = 1;
            return 1;
        }
        if (dyncon_800E3458[0] != 0 && work->field_738 == 1 && work->field_73A == 2)
        {
            return Valcan_800DAE38();
        }
        break;

    case 3:
        if (work->field_73A == 2)
        {
            work->field_828 = 1;
            return 1;
        }
        if (dyncon_800E3458[3] != 0 && work->field_738 == 2 && work->field_73A == 1)
        {
            return Valcan_800DAE38();
        }
        break;
    }

    return 0;
}
int Valcan_800DAFCC(Work *work)
{
    int *flags;

    work->field_828 = 1;

    if (work->field_73A == 0)
    {
        if (work->field_738 == 0 && work->field_73C == 0)
        {
            if (work->field_73E == 1)
            {
                work->field_76C = 0;
                work->field_774 = work->field_770;
                flags = dyncon_800E3458;
                if (flags[0] != 0 && flags[2] != 0)
                {
                    work->field_770 = 3;
                }
                else
                {
                    work->field_770 = 2;
                }
                work->field_6A4 = 0;
                work->field_69C = 0;
            }

            if (work->field_740 >= 0 && work->field_740 <= 1)
            {
                return Valcan_800DA1AC(work->field_740, 3);
            }
            if (work->field_740 == 2)
            {
                return 1;
            }
            work->field_828 = 0;
            return 0;
        }

        if (work->field_740 >= 2 && work->field_740 <= 3)
        {
            return Valcan_800DA1AC(work->field_740, 0);
        }
        if (work->field_740 == 1)
        {
            return 1;
        }
        if (work->field_738 == 1)
        {
            return 3;
        }
        work->field_828 = 0;
        return 0;
    }

    if (work->field_740 >= 0 && work->field_740 <= 1)
    {
        if (dyncon_800E3458[3] != 0 &&
            ((work->field_738 == 1 && work->field_73A == 3 && work->field_740 == 1) ||
             (work->field_738 == 3 && work->field_73A == 3 && work->field_740 == 0)))
        {
            return 0;
        }
        if (dyncon_800E3458[0] != 0)
        {
            if (work->field_738 == 1 && work->field_73A == 2)
            {
                return Valcan_800DA1AC(work->field_740, 0);
            }
            if ((work->field_738 == 0 && work->field_73A == 1 && work->field_740 == 1) ||
                (work->field_738 == 2 && work->field_73A == 1 && work->field_740 == 0))
            {
                return 0;
            }
        }
        return Valcan_800DA1AC(work->field_740, 2);
    }

    if (work->field_740 == 3)
    {
        return 1;
    }
    if (work->field_73A == 1)
    {
        if (work->field_738 == 0)
        {
            return 1;
        }
        return 3;
    }
    if (dyncon_800E3458[0] != 0 && work->field_738 == 1 && work->field_73A == 2)
    {
        return Valcan_800DA1AC(work->field_740, 0);
    }
    work->field_828 = 0;
    return 0;
}
int Valcan_800DB200(Work *work)
{
    int *flags;

    work->field_828 = 0;
    work->field_69C++;

    switch (work->field_740)
    {
    case 0:
        if (work->field_738 == 1)
        {
            flags = dyncon_800E3458;
            if (flags[0] != 0 && flags[2] != 0)
            {
                work->field_770 = 3;
                work->field_6A4 = 0;
                work->field_69C = 0;
                return 3;
            }
        }
        break;

    case 1:
        if (work->field_738 == 2)
        {
            return 1;
        }
        break;

    case 2:
        if (work->field_73A == 1)
        {
            return 2;
        }
        break;

    case 3:
        if (work->field_73A == 2)
        {
            return 1;
        }
        break;
    }

    return 0;
}

int Valcan_800DB2E4(Work *work)
{
    short diffs[2];
    int   flag;
    Valcan_800DA044(work);

    if (work->field_7DC[work->field_6A0][0] == work->field_7A0 &&
        work->field_7DC[work->field_6A0][1] == work->field_7A2)
    {
        if (++work->field_6A0 >= 21)
        {
            work->field_6A0 = 0;
        }
    }

    diffs[0] = work->field_7DC[work->field_6A0][0] - work->field_7A0;
    diffs[1] = work->field_7DC[work->field_6A0][1] - work->field_7A2;

    flag = 0;

    if (diffs[0] > 0)
    {
        if (work->field_740 >= 2 && work->field_740 <= 3)
        {
            flag = Valcan_800DA1AC(work->field_740, 1);
        }
        else if (work->field_740 == 0)
        {
            flag = 1;
        }
    }
    else if (diffs[0] < 0)
    {
        if (work->field_740 < 2 || work->field_740 > 3)
        {
            if (work->field_740 == 1)
            {
                flag = 1;
            }
        }
        else
        {
            flag = Valcan_800DA1AC(work->field_740, 0);
        }
    }
    else if (diffs[1] > 0)
    {
        if (work->field_740 < 0 || work->field_740 > 1)
        {
            if (work->field_740 == 2)
            {
                flag = 1;
            }
        }
        else
        {
            flag = Valcan_800DA1AC(work->field_740, 3);
        }
    }
    else if (diffs[1] < 0)
    {
        if (work->field_740 >= 0 && work->field_740 <= 1)
        {
            flag = Valcan_800DA1AC(work->field_740, 2);
        }
        else if (work->field_740 == 3)
        {
            flag = 1;
        }
    }

    if (flag)
    {
        Valcan_800D9F3C(work, 16);
    }

    return flag;
}

int Valcan_800DB470(Work *work)
{
    switch (work->field_770)
    {
    case 0:
        return Valcan_800DAE7C(work);
    case 1:
        return Valcan_800DAFCC(work);
    case 2:
        return Valcan_800DB200(work);
    case 3:
        return Valcan_800DB2E4(work);
    default:
        return 0;
    }
}

void Valcan_800DB500(Work *work)
{
    work->field_738 = work->field_73C;
    work->field_73A = work->field_73E;

    // We love switches!!!
    switch (work->field_770)
    {
    case 3:
    case 0:
        switch (work->field_768)
        {
        case 0:
            if (--work->field_73C < 0)
            {
                work->field_73C = 1;
            }
            break;
        case 1:
            if (++work->field_73C >= 4)
            {
                work->field_73C = 2;
            }
            break;
        case 2:
            if (--work->field_73E < 0)
            {
                work->field_73E = 1;
            }
            break;
        case 3:
            if (++work->field_73E >= 4)
            {
                work->field_73E = 2;
            }
            break;
        }
        break;
    case 1:
        switch (work->field_768)
        {
        case 0:
            if (--work->field_73C < 0)
            {
                work->field_73C = 0;
                if (--work->field_73E < 0)
                {
                    work->field_73E = 1;
                }
            }
            break;
        case 1:
            if (++work->field_73C >= 4)
            {
                work->field_73C = 3;
                if (--work->field_73E < 0)
                {
                    work->field_73C = 2;
                    work->field_73E = 0;
                }
            }
            break;
        case 2:
            if (--work->field_73E < 0)
            {
                work->field_73C--;
                work->field_73E = 0;
                if (work->field_73C < 0)
                {
                    work->field_73C = 0;
                    work->field_73E = 1;
                }
            }
            break;
        case 3:
            if (++work->field_73E >= 4)
            {
                work->field_73C--;
                work->field_73E = 3;
                if (work->field_73C < 0)
                {
                    work->field_73C = 0;
                    work->field_73E = 2;
                }
            }
            break;
        }
        break;
    case 2:
        switch (work->field_768)
        {
        case 0:
            if (--work->field_73C < 0)
            {
                work->field_768 = 3;

                work->field_73C = 0;
                work->field_73E = 1;
            }
            break;
        case 1:
            if (++work->field_73C >= 4)
            {
                work->field_73C = 2;
            }
            break;
        case 2:
            if (--work->field_73E < 0)
            {
                work->field_768 = 1;
                work->field_73C = 1;
                work->field_73E = 0;
            }
            break;
        case 3:
            if (++work->field_73E >= 4)
            {
                work->field_73E = 2;
            }
            break;
        }
        break;
    }
}

void Valcan_800DB868(Work *work)
{
    int diff1, diff2;

    if (work->field_770 == 2)
    {
        work->field_76C = 0;
    }
    else if (work->field_770 == 3 || (work->field_770 == 1 && work->field_774 != 0))
    {
        work->field_76C = 500;
    }
    else if ((work->field_770 == 0 && work->field_774 == 2) || (work->field_770 == 1 && work->field_774 == 0))
    {
        work->field_76C = 0;
    }
    else
    {
        work->field_76C = 2800;
    }

    diff1 = work->field_73C - work->field_738;
    diff2 = work->field_73E - work->field_73A;
    if (diff1 < 0)
    {
        work->field_740 = 0;
        work->field_754 = work->field_6F8[work->field_73C][work->field_73E][0] + work->field_76C;
    }
    else if (diff1 > 0)
    {
        work->field_740 = 1;
        work->field_754 = work->field_6F8[work->field_73C][work->field_73E][0] - work->field_76C;
    }
    else if (diff2 < 0)
    {
        work->field_740 = 2;
        work->field_756 = work->field_6F8[work->field_73C][work->field_73E][1] + work->field_76C;
    }
    else if (diff2 > 0)
    {
        work->field_740 = 3;
        work->field_756 = work->field_6F8[work->field_73C][work->field_73E][1] - work->field_76C;
    }
}

void Valcan_800DB9F0(Work *work)
{
    int dir;

    dir = work->field_764;

    if ((work->field_770 == 1 && work->field_774 != 0) || work->field_770 == 2 || work->field_770 == 3 ||
        work->field_76C == 0 || work->field_774 == 2 || work->field_774 == 3)
    {
        if (work->field_774 >= 2 && work->field_774 <= 3)
        {
            work->field_774 = work->field_770;
        }

        switch (work->field_740)
        {
        case 0:
            if (dir > 0)
            {
                work->field_768 = 2;
            }
            else
            {
                work->field_768 = 3;
            }
            break;
        case 1:
            if (dir > 0)
            {
                work->field_768 = 3;
            }
            else
            {
                work->field_768 = 2;
            }
            break;
        case 2:
            if (dir > 0)
            {
                work->field_768 = 1;
            }
            else
            {
                work->field_768 = 0;
            }
            break;
        case 3:
            if (dir > 0)
            {
                work->field_768 = 0;
            }
            else
            {
                work->field_768 = 1;
            }
            break;
        }

        work->control.turn.vy = work->field_744[work->field_768];

        Valcan_800DB500(work);
        Valcan_800DB868(work);
        work->field_758 = 0;
        work->field_75C = 0;
        return;
    }

    if (--work->field_75C >= 8)
    {
        work->control.turn.vy -= dir * 14;
        return;
    }

    if (work->field_75C >= 0)
    {
        switch (work->field_740)
        {
        case 0:
            if (dir > 0)
            {
                work->field_768 = 2;
            }
            else
            {
                work->field_768 = 3;
            }
            work->control.mov.vx = (work->control.mov.vx + work->field_6F8[work->field_73C][work->field_73E][0]) / 2;
            break;
        case 1:
            if (dir > 0)
            {
                work->field_768 = 3;
            }
            else
            {
                work->field_768 = 2;
            }
            work->control.mov.vx = (work->control.mov.vx + work->field_6F8[work->field_73C][work->field_73E][0]) / 2;
            break;
        case 2:
            if (dir > 0)
            {
                work->field_768 = 1;
            }
            else
            {
                work->field_768 = 0;
            }
            work->control.mov.vz = (work->control.mov.vz + work->field_6F8[work->field_73C][work->field_73E][1]) / 2;
            break;
        case 3:
            if (dir > 0)
            {
                work->field_768 = 0;
            }
            else
            {
                work->field_768 = 1;
            }
            work->control.mov.vz = (work->control.mov.vz + work->field_6F8[work->field_73C][work->field_73E][1]) / 2;
            break;
        }

        work->control.turn.vy = work->field_744[work->field_768];
        return;
    }

    Valcan_800DB500(work);
    Valcan_800DB868(work);
    work->field_758 = 0;
    work->field_75C = 0;
}
void Valcan_800DBCB4(Work *work)
{
    if ((work->field_770 == 1 && work->field_774 != 0) || work->field_770 == 2 || work->field_770 == 3 ||
        work->field_76C == 0 || work->field_774 == 2 || work->field_774 == 3)
    {
        if (work->field_774 >= 2 && work->field_774 <= 3)
        {
            work->field_774 = work->field_770;
        }

        switch (work->field_740)
        {
        case 0:
            work->field_768 = 1;
            work->control.turn.vy = work->field_744[1];
            break;
        case 1:
            work->field_768 = 0;
            work->control.turn.vy = work->field_744[0];
            break;
        case 2:
            work->field_768 = 3;
            work->control.turn.vy = work->field_744[3];
            break;
        case 3:
            work->field_768 = 2;
            work->control.turn.vy = work->field_744[2];
            break;
        }

        work->control.rot.vy = work->control.turn.vy;

        Valcan_800DB500(work);
        Valcan_800DB868(work);
        work->field_758 = 0;
        work->field_75C = 0;
        return;
    }

    if (--work->field_75C >= 40)
    {
        work->control.turn.vy += 16;
        return;
    }

    if (work->field_75C >= 8)
    {
        work->control.turn.vy -= 64;
        return;
    }

    if (work->field_75C >= 0)
    {
        switch (work->field_740)
        {
        case 0:
            work->control.mov.vz = (work->control.mov.vz + work->field_6F8[work->field_738][work->field_73A][1]) / 2;
            work->control.turn.vy = work->field_744[1];
            work->field_768 = 1;
            break;
        case 1:
            work->control.mov.vz = (work->control.mov.vz + work->field_6F8[work->field_738][work->field_73A][1]) / 2;
            work->control.turn.vy = work->field_744[0];
            work->field_768 = 0;
            break;
        case 2:
            work->control.mov.vx = (work->control.mov.vx + work->field_6F8[work->field_738][work->field_73A][0]) / 2;
            work->control.turn.vy = work->field_744[3];
            work->field_768 = 3;
            break;
        case 3:
            work->control.mov.vx = (work->control.mov.vx + work->field_6F8[work->field_738][work->field_73A][0]) / 2;
            work->control.turn.vy = work->field_744[2];
            work->field_768 = 2;
            break;
        }
        return;
    }

    Valcan_800DB500(work);
    Valcan_800DB868(work);
    work->field_758 = 0;
    work->field_75C = 0;
}

void Valcan_800DBF74(Work *work)
{
    int sqrt;
    int vx, vy;
    int diff1, diff2;
    int tan1, tan2;

    work->control.mov.vx = work->field_7AC.vx;
    work->control.mov.vz = work->field_7AC.vz;

    Valcan_800D9F3C(work, 16);

    diff1 = work->field_51C.vx - work->field_6C4.vx;
    diff2 = work->field_51C.vz - work->field_6C4.vz;
    tan1 = ratan2(diff1, diff2);

    vy = (tan1 + GV_RandS(64)) & 0xFFF;

    sqrt = SquareRoot0(diff2 * diff2 + diff1 * diff1);
    diff1 = work->field_51C.vy - work->field_6C4.vy;
    tan2 = ratan2(sqrt, diff1);

    vx = (GV_RandS(8) + tan2 - 1008) & 0xFFF;

    work->field_5A4[4].vx = vx - 32;
    work->field_5A4[7].vx = vx - 64;
    work->field_5A4[6].vx = vx - 32;
    work->field_5A4[9].vx = -512;

    work->control.turn.vy = vy;
    work->control.turn.vx = 0;
}

void Valcan_800DC06C(Work *work, int index, int blood_count)
{
    MATRIX mat;

    DG_SetPos(&work->field_A0.objs->objs[index].world);
    DG_MovePos(&valcan_blood_offset_800C3608);

    valcan_blood_rot_800C3610.vx += GV_RandS(128);
    valcan_blood_rot_800C3610.vy += GV_RandS(128);
    valcan_blood_rot_800C3610.vz += GV_RandS(512);
    DG_RotatePos(&valcan_blood_rot_800C3610);

    ReadRotMatrix(&mat);
    NewBlood(&mat, blood_count);
}

void Valcan_800DC124(Work *work)
{
    if (work->field_94C >= 30 && Valcan_800DA558(work, 1) && (work->field_940 >= 0x1E || work->field_68C < 0x1F41))
    {
        work->field_7AC = work->control.mov;
        work->field_698 = 0;
        work->field_7B4 = work->control.turn.vy;
        work->field_778 = work->field_684;
        work->field_77C = work->field_688;

        if (work->field_6C0 > 150)
        {
            work->field_6C0 = 0;
            work->field_940 = 0;
            GM_SeSet2(0, 0x3F, SE_EXCLAMATION);
            AN_HeadMark(&work->field_A0.objs->objs[6].world, 0);
            if (work->field_8E4++ >= 2)
            {
                work->field_8E4 = 0;
                switch (work->field_770)
                {
                case 1:
                    GM_SeSetMode(&work->field_910, SE_V_ENE_FOUND01, GM_SEMODE_BOMB);
                    break;
                case 2:
                    GM_SeSetMode(&work->field_910, SE_V_ENE_FOUND02, GM_SEMODE_BOMB);
                    break;
                case 3:
                    GM_SeSetMode(&work->field_910, SE_V_ENE_UNUSED10, GM_SEMODE_BOMB);
                    break;
                }
            }
        }

        work->field_684 = 1;
        work->field_688 = 12;
    }
}

void Valcan_800DC290(Work *work, int arg1, int arg2)
{
    if (work->field_670 != arg1)
    {
        work->field_920 = 0;
        work->field_670 = arg1;
        GM_ConfigObjectAction(&work->field_A0, arg1, 0, 4);
    }
    else if (work->field_A0.is_end == 1)
    {
        work->field_688 = arg2;
    }
}

void Valcan_800DC2EC(Work *work, int action)
{
    work->field_670 = action;
    GM_ConfigObjectAction(&work->field_A0, action, 0, 4);
}

void Valcan_800DC318(Work *work)
{
    int mod;

    switch (work->field_688)
    {
    case 0:
        work->field_91C = 0;
        if (work->field_900 <= 0)
        {
            work->field_688 = 0;
        }
        else
        {
            work->field_688 = 1;
        }

    case 1:
        Valcan_800DC2EC(work, 0);
        break;

    case 2:
        work->field_91C = 0;
        work->field_688 = 3;
        work->field_694 = GV_RandU(128) + 64;

    case 3:
        Valcan_800DC2EC(work, 0);
        if (work->field_694-- <= 0)
        {
            work->field_688 = 4;
        }
        break;

    case 4:
        if (GM_GameLevel == GM_LEVEL_EXTREME && GV_Time % 256 < 240)
        {
            Valcan_800DA990(work);
        }
        else
        {
            work->field_91C = 0;
        }

        work->field_688 = 5;
        Valcan_800DC290(work, 1, 4);

        mod = work->field_920 % 22;
        if (mod == 0)
        {
            GM_SeSetMode(&work->field_910, 0xBE, GM_SEMODE_BOMB);
        }
        else if (mod == 11)
        {
            GM_SeSetMode(&work->field_910, 0xBF, GM_SEMODE_BOMB);
        }
        work->field_920++;
        break;

    case 5:
        Valcan_800DC290(work, 1, 4);
        break;

    case 6:
        Valcan_800DC290(work, 1, 0);
        break;

    case 8:
        work->field_91C = 0;
        work->field_688 = 9;
        Valcan_800DC290(work, 2, 8);

        mod = work->field_920 % 30;
        if (mod == 0)
        {
            GM_SeSetMode(&work->field_910, 0xBE, GM_SEMODE_BOMB);
        }
        else if (mod == 15)
        {
            GM_SeSetMode(&work->field_910, 0xBF, GM_SEMODE_BOMB);
        }
        work->field_920++;
        break;

    case 9:
        Valcan_800DC290(work, 2, 8);
        break;

    case 12:
        work->field_6B0 = 1;
        work->field_694 = 8;
        work->field_688 = 13;

    case 13:
        Valcan_800DC2EC(work, 3);
        if (work->field_694-- <= 0)
        {
            work->field_688 = 14;
            work->field_6B0 = 2;
        }
        break;

    case 14:
        Valcan_800DA990(work);
        Valcan_800DC290(work, 4, 14);
        break;

    case 17:
        work->field_6B0 = 1;
        work->field_694 = 8;
        work->field_688 = 18;

    case 18:
        Valcan_800DC2EC(work, 3);
        if (work->field_694-- <= 0)
        {
            work->field_688 = 19;
            work->field_6B0 = 2;
        }
        break;

    case 19:
        Valcan_800DA990(work);
        Valcan_800DC290(work, 5, 20);
        break;

    case 20:
        work->field_694 = 8;
        work->field_6B0 = 3;
        Valcan_800DA990(work);
        work->field_688 = 21;
        break;

    case 22:
        work->field_6B0 = 1;
        work->field_694 = 8;
        work->field_688 = 23;

    case 23:
        Valcan_800DC2EC(work, 3);
        if (work->field_694-- <= 0)
        {
            work->field_688 = 24;
            work->field_6B0 = 2;
        }
        break;

    case 24:
        Valcan_800DA990(work);
        Valcan_800DC290(work, 6, 25);
        break;

    case 25:
        work->field_694 = 8;
        work->field_6B0 = 3;
        Valcan_800DA990(work);
        work->field_688 = 26;
        break;

    case 21:
    case 26:
        Valcan_800DA990(work);
        Valcan_800DC2EC(work, 2);
        if (work->field_694-- <= 0)
        {
            work->field_91C = 0;
            work->field_6B0 = 0;
            work->control.turn.vy = work->field_744[work->field_740];
        }
        break;

    case 27:
        work->field_91C = 0;
        Valcan_800DC290(work, 7, 28);
        work->field_694 = 8;
        work->field_6B0 = 1;
        break;

    case 29:
        work->field_91C = 0;
        Valcan_800DC290(work, 8, 30);
        work->field_694 = 8;
        work->field_6B0 = 1;
        break;

    case 28:
    case 30:
        Valcan_800DC2EC(work, 2);
        if (work->field_694-- <= 0)
        {
            work->field_6B0 = 0;
        }
        break;
    }
}
void Valcan_800DC7A0(Work *work)
{
    if (work->field_94C < 300)
    {
        work->field_94C++;
    }

    if (work->field_950 >= -9)
    {
        work->field_950--;
    }

    if (work->field_6B0 == 0)
    {
        switch (work->field_770)
        {
        case 1:
            if (work->field_774 != 0)
            {
                work->field_688 = 4;
            }
            else
            {
                work->field_688 = 8;
            }
            break;
        case 2:
            work->field_688 = 4;
            break;
        case 3:
            work->field_688 = 4;
            Valcan_800DA990(work);
            break;
        default:
            work->field_688 = 8;
            break;
        }
    }

    if (work->field_688 != 17)
    {
        Valcan_800DACCC(work);
    }

    if (work->field_758 == -1)
    {
        if (work->field_770 == 1 && work->field_774 == 0)
        {
            work->field_774 = work->field_770;
        }

        if (work->field_770 == 0)
        {
            switch (GM_GameLevel)
            {
            case GM_LEVEL_VERYEASY:
            case GM_LEVEL_EASY:
            default:
                if (work->field_900 <= work->field_6A8 / 2 + 1)
                {
                    work->field_6A4 = 0;
                    work->field_774 = work->field_770;
                    work->field_770 = 1;
                }
                break;
            case GM_LEVEL_NORMAL:
                if (work->field_900 <= work->field_6A8 * 4 / 5 + 1)
                {
                    work->field_6A4 = 0;
                    work->field_774 = work->field_770;
                    work->field_770 = 1;
                }
                break;
            case GM_LEVEL_HARD:
                if (work->field_900 <= work->field_6A8 * 5 / 6 + 1)
                {
                    work->field_6A4 = 0;
                    work->field_774 = work->field_770;
                    work->field_770 = 1;
                }
                break;
            case GM_LEVEL_EXTREME:
                work->field_6A4 = 0;
                work->field_774 = work->field_770;
                work->field_770 = 3;
                break;
            }
        }

        work->field_758 = Valcan_800DB470(work);
        if (work->field_758 == 0)
        {
            Valcan_800DB500(work);
            Valcan_800DB868(work);
        }

        work->field_75C = 72;
        work->field_788 = 1;
    }

    if (work->field_6B0 == 0 || work->field_770 == 3)
    {
        switch (work->field_758)
        {
        case 1:
            Valcan_800DBCB4(work);
            break;
        case 2:
            work->field_764 = 1;
            Valcan_800DB9F0(work);
            break;
        case 3:
            work->field_764 = -1;
            Valcan_800DB9F0(work);
            break;
        }
    }

    if (work->field_788 != 0 && work->field_794 == 1)
    {
        work->field_788 = 2;
    }

    if (work->field_770 == 3)
    {
        work->field_788 = 0;
    }

    if (GM_GameStatus & STATE_STUN)
    {
        GM_SeSet2(0, 63, SE_V_ENE_HUH);
    }

    switch (work->field_788)
    {
    case 1:
        if (work->field_770 == 2 && work->field_69C > 0)
        {
            switch (work->field_740)
            {
            case 0:
            case 1:
                if (dyncon_800E3458[0] >= 2 && work->field_738 == 1 && work->field_73A == 0)
                {
                    work->field_828 = 1;
                }
                else
                {
                    work->control.turn.vy = work->field_744[3];
                }
                break;
            case 2:
            case 3:
                if (dyncon_800E3458[2] >= 2 && work->field_738 == 0 && work->field_73A == 2)
                {
                    work->field_828 = 1;
                }
                else
                {
                    work->control.turn.vy = work->field_744[1];
                }
                break;
            }

            work->control.mov.vz = work->field_6F8[work->field_738][work->field_73A][1];
            work->control.mov.vx = work->field_6F8[work->field_738][work->field_73A][0];
        }

        if (work->field_828 == 0)
        {
            if (work->field_8E8++ >= 3)
            {
                work->field_8E8 = 0;
                if (GV_RandU(2) != 0)
                {
                    GM_SeSetMode(&work->field_910, SE_V_ENE_NOTHING, GM_SEMODE_BOMB);
                }
                else
                {
                    GM_SeSetMode(&work->field_910, SE_V_ENE_FOUND03, GM_SEMODE_BOMB);
                }
            }
            work->field_688 = 17;
        }
        work->field_788 = 0;
        break;

    case 2:
        Valcan_800DC124(work);
        break;

    default:
        if (work->field_794 == 1)
        {
            Valcan_800DC124(work);
        }
        break;
    }
}

#define ABS(x) (((x) >= 0) ? (x) : -(x))

static inline int Valcan_800DCC84_helper(int a)
{
    return (a & 0xFFF) + 0x1000;
}

void Valcan_800DCC84(Work *work)
{
    int temp_a0;
    int temp_v0;

    if (work->field_794 == 1)
    {
        work->control.radar_atr |= RADAR_UNK4;
        Valcan_800DBF74(work);
    }
    else if (work->field_698 == 0)
    {
        work->field_698 = GV_RandU(4) + 26;
    }

    if (work->field_698 > 0)
    {
        work->field_698--;
        work->control.turn.vy += GV_RandS(8);
        if (work->field_794 == 1)
        {
            work->field_698 = 0;
        }
    }
    if (work->field_940 > 120)
    {
        if (work->field_770 >= 2 && work->field_770 <= 3)
        {
            temp_a0 = Valcan_800DCC84_helper((unsigned short)work->control.turn.vy);
            temp_v0 = Valcan_800DCC84_helper(work->field_744[work->field_768]);
        }
        else
        {
            temp_a0 = Valcan_800DCC84_helper((unsigned short)work->control.turn.vy);
            temp_v0 = Valcan_800DCC84_helper(work->field_7B4);
        }

        if (ABS(temp_a0 - temp_v0) < 256 || work->field_940 > 600)
        {
            work->field_940 = 0;
            work->field_6C0 = 0;
            work->field_698 = 1;
        }
    }
    if (work->field_698 == 1)
    {
        work->control.radar_atr &= ~RADAR_UNK4;
        Valcan_800D9F3C(work, 16);
        work->field_788 = 0;
        work->field_6B0 = 0;
        work->field_684 = work->field_778;
        work->field_688 = work->field_77C;
        if (work->field_770 >= 2 && work->field_770 <= 3)
        {
            work->control.turn.vy = work->field_744[work->field_768];
            if (work->field_770 == 2)
            {
                work->field_774 = work->field_770;
            }
        }
        else
        {
            work->control.turn.vy = work->field_7B4;
        }
        work->field_6A4 = 0;
    }
}

void Valcan_800DCE60(Work *work)
{
    if (work->field_698 == 0)
    {
        work->field_7AC = work->control.mov;
        work->field_698 = 35;
        GM_SeSet2(0, 0x3F, SE_V_ENE_FOOTPRINTS);
        if (GV_RandU(2) == 0)
        {
            work->field_688 = 27;
        }
        else
        {
            work->field_688 = 29;
        }
    }
    if (work->field_698 > 0)
    {
        work->field_698--;
        if (work->field_698 >= 16 && !(work->field_698 & 1))
        {
            Valcan_800DC06C(work, GV_RandU(8), 2);
        }
        if (work->field_698 == 1)
        {
            work->field_684 = work->field_780;
            work->field_688 = work->field_784;
            Valcan_800D9F3C(work, 16);
            work->field_6B0 = 0;
            work->field_6A4 = 0;
            work->field_788 = 0;
            if (work->field_770 >= 2 && work->field_770 <= 3)
            {
                work->control.turn.vy = work->field_744[work->field_768];
                if (work->field_770 == 2)
                {
                    work->field_774 = 2;
                }
            }
        }
    }
}

void Valcan_800DCF8C(Work *work)
{
    work->field_798 = work->field_794;
    work->field_794 = Valcan_800DA558(work, 0);
    switch (work->field_684)
    {
    case 0:
        work->field_8F0 = 0;
        Valcan_800DC7A0(work);
        Valcan_800DA140(work);
        break;
    case 1:
        work->field_8F0 = 1;
        Valcan_800DCC84(work);
        break;
    case 3:
        work->field_8F0 = 0;
        Valcan_800DCE60(work);
        break;
    }
    Valcan_800DC318(work);
}

void Valcan_800DD03C(Work *work)
{
    SVECTOR diff;
    int     time;

    if (mts_get_tick_count() - work->field_8EC > work->field_8E0)
    {
        work->field_8E0 = GV_RandU(64) + 120;
        work->field_8EC = mts_get_tick_count();

        if (work->field_770 >= 2 && work->field_770 <= 3 && work->field_924 == -1)
        {
            GM_SeSetMode(&work->field_910, SE_V_ENE_NOISE, GM_SEMODE_BOMB);
        }
    }

    dword_8009F480 = 0;
    dword_8009F49C = 0;

    work->field_6C0++;
    work->field_68C = Valcan_800D9DC0(work, 0);

    work->field_6C4 = work->control.mov;
    work->field_6CC = work->control.rot;

    Valcan_800D9F8C(work);

    if (dword_8009F46C[0] == 1 && (GV_PadData[2].status & PAD_TRIANGLE))
    {
        diff.vx = (work->control.mov.vx - svector_8009F478.vx) / 3;
        diff.vy = 0;
        diff.vz = (work->control.mov.vz - svector_8009F478.vz) / 3;

        work->field_910.vx = svector_8009F478.vx + diff.vx;
        work->field_910.vy = svector_8009F478.vy;
        work->field_910.vz = svector_8009F478.vz + diff.vz;
    }
    else
    {
        diff.vx = (work->control.mov.vx - GM_PlayerPosition.vx) / 4;
        diff.vy = 0;
        diff.vz = (work->control.mov.vz - GM_PlayerPosition.vz) / 4;

        work->field_910.vx = GM_PlayerPosition.vx + diff.vx;
        work->field_910.vy = GM_PlayerPosition.vy;
        work->field_910.vz = GM_PlayerPosition.vz + diff.vz;
    }

    Valcan_800DCF8C(work);

    work->field_6A4++;
    if (work->field_68C > 9000)
    {
        work->field_940++;
    }

    if (work->field_668->damaged & TARGET_PUSH)
    {
        work->field_668->damaged &= ~TARGET_PUSH;
    }

    if ((u_short)work->field_664->a_mode - 3U < 2)
    {
        if (!(work->field_664->damaged & TARGET_POWER))
        {
            goto skip;
        }

        work->field_664->damaged &= ~TARGET_POWER;
        work->field_664->vital = work->field_900;
    }

    if ((work->field_664->damaged & TARGET_POWER) && work->field_6B8 == 0)
    {
        work->field_944 = 0;
        work->field_948 = 0;
        work->field_698 = 0;

        if (work->field_664->damage > 256)
        {
            work->field_664->damage = 256;
        }

        switch (work->field_664->a_mode)
        {
        case 1:
            work->field_900 -= 8;
            work->field_664->vital = work->field_900;
            break;
        case 2:
            work->field_900 -= (short)(work->field_664->damage / 3);
            work->field_664->vital = work->field_900;
            break;
        }

        work->field_780 = work->field_684;
        work->field_784 = work->field_688;
        Valcan_800D9F3C(work, 16);
        work->field_6B8 = 1;

        if (GM_GameLevel != GM_LEVEL_EXTREME)
        {
            work->field_684 = 3;
        }
        else
        {
            GM_SeSet2(0, 63, SE_V_ENE_FOOTPRINTS);
        }

        work->field_924 = 90;
        work->field_6A4 = 0;
        work->field_69C = 0;
        work->field_93C = 1;
    }

skip:
    work->field_664->damage = 0;

    if (work->field_924 > 0)
    {
        work->field_924--;
        time = 90 - work->field_924;

        if (GM_GameLevel == GM_LEVEL_EXTREME && time < 30)
        {
            Valcan_800DC06C(work, GV_RandU(8), 2);
        }

        work->field_944 = time * 15000 / 90;
        work->field_948 = time * 1024 / 90;
    }

    if (work->field_924 == 0)
    {
        work->field_924 = -1;
        work->field_664->damaged &= ~TARGET_POWER;
        work->field_944 = 15000;
        work->field_6B8 = 0;
        work->field_948 = 1024;
    }

    if (work->field_900 <= 0 && work->field_81C == 0)
    {
        Valcan_800DC06C(work, GV_RandU(8), 2);
        work->field_81C = 1;
    }
    else
    {
        Valcan_800D9D90(work);
    }
}

void Valcan_800DD578(Work *work)
{
    work->field_69C = 0;
    work->field_6A0 = 0;
    work->field_690 = 0;
    work->field_698 = 0;
    work->field_6A4 = 0;
    work->field_694 = 0;
    work->field_6B8 = 0;
    work->field_6B0 = 0;
    work->field_670 = 9;
    GM_ConfigMotionAdjust(&work->field_A0, work->field_5A4);
    Valcan_800D9F3C(work, 16);
    Valcan_800DC2EC(work, 0);
    work->field_758 = 0;
    work->field_744[0] = 3072;
    work->field_744[1] = 1024;
    work->field_744[2] = 2048;
    work->field_744[3] = 0;
    Valcan_800DB868(work);
    work->field_768 = work->field_740;
    work->control.rot.vx = 0;
    work->control.rot.vy = work->field_744[work->field_740];
    work->control.rot.vz = 0;
    work->control.turn.vx = 0;
    work->control.turn.vy = work->field_744[work->field_740];
    work->control.turn.vz = 0;
    work->field_76C = 2800;
    work->field_774 = 0;
    work->field_778 = 0;
    work->field_77C = 0;
    work->field_770 = 0;
    work->field_788 = 0;
    work->field_78C = 0;
    work->field_790 = 0;
    work->field_794 = 0;
    work->field_798 = 0;
    work->field_81C = 0;
    work->field_828 = 0;
    work->field_830 = 0;
    work->field_834 = 0;
    work->field_83C = 0;
    work->field_840 = 0;
    work->field_8F0 = 0;
    work->field_90C = 0;
    work->field_918 = 0;
    work->field_91C = 0;
    work->field_920 = 0;
    work->field_924 = -1;
    work->field_6B4 = 0;
    work->field_6BC = 0;
    work->field_6C0 = 1000;
    work->field_93C = 0;
    work->field_940 = 0;
    work->field_8DC = 0;
    work->field_8E4 = 0;
    work->field_8E8 = 0;
    work->field_8E0 = GV_RandU(16) + 40;
    work->field_8EC = mts_get_tick_count();
    work->field_6BC = mts_get_tick_count();
    work->field_94C = 0;
    work->field_7DC[0][0] = 0;
    work->field_7DC[0][1] = 3;
    work->field_7DC[1][0] = 1;
    work->field_7DC[1][1] = 1;
    work->field_7DC[2][0] = 2;
    work->field_7DC[2][1] = 2;
    work->field_7DC[3][0] = 3;
    work->field_7DC[3][1] = 3;
    work->field_7DC[4][0] = 1;
    work->field_7DC[4][1] = 1;
    work->field_7DC[5][0] = 0;
    work->field_7DC[5][1] = 0;
    work->field_7DC[6][0] = 2;
    work->field_7DC[6][1] = 2;
    work->field_7DC[7][0] = 3;
    work->field_7DC[7][1] = 0;
    work->field_7DC[8][0] = 2;
    work->field_7DC[8][1] = 2;
    work->field_7DC[9][0] = 3;
    work->field_7DC[9][1] = 3;
    work->field_7DC[10][0] = 1;
    work->field_7DC[10][1] = 1;
    work->field_7DC[11][0] = 2;
    work->field_7DC[11][1] = 0;
    work->field_7DC[12][0] = 0;
    work->field_7DC[12][1] = 3;
    work->field_7DC[13][0] = 3;
    work->field_7DC[13][1] = 0;
    work->field_7DC[14][0] = 0;
    work->field_7DC[14][1] = 1;
    work->field_7DC[15][0] = 2;
    work->field_7DC[15][1] = 2;
    work->field_7DC[16][0] = 1;
    work->field_7DC[16][1] = 1;
    work->field_7DC[17][0] = 0;
    work->field_7DC[17][1] = 3;
    work->field_7DC[18][0] = 3;
    work->field_7DC[18][1] = 2;
    work->field_7DC[19][0] = 1;
    work->field_7DC[19][1] = 3;
    work->field_7DC[20][0] = 3;
    work->field_7DC[20][1] = 0;
    work->field_684 = 0;
    work->field_688 = 0;
    work->field_944 = 15000;
    work->field_948 = 1024;
    Valcan_800D9D90(work);
    GM_AlertMode = 4;
}
