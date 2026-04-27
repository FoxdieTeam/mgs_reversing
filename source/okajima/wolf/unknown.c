#include "wolf2.h"

#include "linkvar.h"
#include "game/camera.h"
#include "libgcl/libgcl.h"
#include "okajima/blood.h"
#include "okajima/bullet.h"
#include "weapon/weapon.h"

#define TARGET_FLAG    ( TARGET_AVAIL | TARGET_POWER | TARGET_SEEK )

#define MOTION_DATA    GV_StrCode("sniper")
#define BODY_DATA      GV_StrCode("snp_ded0")
#define WEAPON_DATA    GV_StrCode("rifle")

#define BODY_FLAG      ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_IRTEXTURE )
#define WEAPON_FLAG    ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

static SVECTOR s12a_dword_800C3498 = {0, 0, 100};
static SVECTOR s12a_dword_800C34A0 = {-1024, 0, 0};
static SVECTOR s12a_dword_800C34A8 = {10, -2000, -70};
static SVECTOR s12a_dword_800C34B0 = {10, -800, -120};

extern GM_CAMERA        GM_Camera;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

extern SVECTOR wolf2_position;

void *AN_Unknown_800CA1EC( MATRIX* mat, int mark );
void NewAnime_8005E1A0( MATRIX* mat );
void s01a_object_800D952C( SVECTOR *pos, short scr_num );

void s12a_wolf2_800CED64(Wolf2Work *work)
{
    work->fA5C = 5;
    ((SVECTOR *)&work->f6AC)->vy = 0;
    work->f65C->size.vx = 150;
    work->f65C->size.vy = 200;
    work->f65C->size.vz = 150;

    work->fA60 = 0;
    work->f6B4.vy = -300;
    work->f660->size.vx = 150;
    work->f660->size.vy = 500;
    work->f660->size.vz = 150;
}

void s12a_wolf2_800CEDC0(Wolf2Work *work)
{
    work->fA5C = 0;
    ((SVECTOR *)&work->f6AC)->vy = 500;
    work->f65C->size.vx = 10;
    work->f65C->size.vy = 500;
    work->f65C->size.vz = 100;

    work->fA60 = 0;
    work->f6B4.vy = -500;
    work->f660->size.vx = 10;
    work->f660->size.vy = 500;
    work->f660->size.vz = 100;
}

void s12a_wolf2_800CEE1C(Wolf2Work *work)
{
    work->fA5C = 0;
    ((SVECTOR *)&work->f6AC)->vy = 200;
    work->f65C->size.vx = 250;
    work->f65C->size.vy = 200;
    work->f65C->size.vz = 250;

    work->fA60 = 0;
    work->f6B4.vy = -200;
    work->f660->size.vx = 250;
    work->f660->size.vy = 200;
    work->f660->size.vz = 250;
}

void s12a_wolf2_800CEE78(Wolf2Work *work)
{
    work->fA5C = 0;
    ((SVECTOR *)&work->f6AC)->vy = 125;
    work->f65C->size.vx = 350;
    work->f65C->size.vy = 125;
    work->f65C->size.vz = 350;

    work->fA60 = 0;
    work->f6B4.vy = -125;
    work->f660->size.vx = 350;
    work->f660->size.vy = 125;
    work->f660->size.vz = 350;
}

void s12a_wolf2_800CEED4(int yaw, SVECTOR *to, SVECTOR *from, SVECTOR *ang)
{
    int x, y, z;

    x = to->vx - from->vx;
    y = to->vy - from->vy;
    z = to->vz - from->vz;
    ang->vy = ratan2(x, z) & 0xFFF;
    ang->vx = ratan2(yaw, y) & 0xFFF;
    ang->vz = 0;
}

void s12a_wolf2_800CEF50(Wolf2Work *work)
{
    work->f6E8 = GV_RandU(16);

    switch (GM_DifficultyFlag)
    {
    case DIFFICULTY_VERY_EASY:
    case DIFFICULTY_EASY:
    default:
        work->f6E8 += 150;
        break;
    case DIFFICULTY_NORMAL:
        work->f6E8 += 120;
        break;
    case DIFFICULTY_HARD:
        work->f6E8 += 90;
        break;
    case DIFFICULTY_EXTREME:
        work->f6E8 += 20;
        break;
    }
}

void s12a_wolf2_800CEFF0(Wolf2Work *work, int arg1)
{
    s12a_wolf2_800CEF50(work);

    work->f710 = GV_RandS(16);
    work->f714 = GV_RandS(16);
    work->f6D4 = arg1;
}

void s12a_wolf2_800CF03C(SVECTOR *vecs, int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        vecs[i] = DG_ZeroVector;
    }
}

void s12a_wolf2_800CF084(Wolf2Work *work, int arg1, int arg2, int arg3)
{
    int x, y, z;
    int ax;
    int len;
    int temp_s0;
    int temp_s1;
    int temp_v1;
    int temp_v0;
    int var_s3;
    int var_s4;
    int var_s5;

    var_s5 = arg3;

    if (work->f6D4 == 20)
    {
        return;
    }

    var_s4 = 0;
    var_s3 = 0;

    if (work->f718 == 0)
    {
        temp_v1 = work->f71C;

        switch (work->f720)
        {
        case 0:
            if (arg1 < temp_v1)
            {
                arg1 = 0;
            }
            else if (arg1 <= temp_v1 + 32)
            {
                arg1 = temp_v1 - arg1;
            }
            else if (arg1 <= temp_v1 + 96)
            {
                temp_v0 = arg1 - temp_v1;
                arg1 = temp_v0 - 64;
            }
            else if (arg1 <= temp_v1 + 128)
            {
                temp_v0 = arg1 - 64;
                arg1 = temp_v1 - temp_v0;
            }
            else
            {
                arg1 = 0;
            }

            var_s4 = (arg2 * arg1) / 32;
            var_s3 = (var_s5 * arg1) / 32;
            break;
        case 1:
        case 2:
        case 3:
            if (arg1 < 0)
            {
                var_s4 = 0;
                var_s3 = 0;
                work->f710 = 0;
                work->f714 = 0;
            }
            else
            {
                temp_s1 = rsin(arg1 * 32);
                temp_s0 = rsin(arg1 * 16);

                if (temp_s1 == 0)
                {
                    work->f714 = GV_RandS(16);
                    var_s5 = work->f714;
                }

                var_s4 = temp_s0 / 1024;
                var_s3 = (var_s5 * temp_s1) / 4096;
            }
            break;
        }
    }

    x = (work->f9FC.vx - work->body.objs->objs[4].world.t[0]) >> 1;
    z = (work->f9FC.vz - work->body.objs->objs[4].world.t[2]) >> 1;

    arg3 = (var_s3 + ratan2(x, z)) & 0xFFF;

    len = SquareRoot0(z * z + x * x);
    y = (work->f9FC.vy - work->body.objs->objs[4].world.t[1]) >> 1;
    ax = (ratan2(len, y) - 1024 + var_s4) & 0xFFF;

    work->adjust[4].vx = ax;
    work->adjust[6].vx = ax;
    work->adjust[7].vx = ax;
    work->adjust[1].vy = arg3;
}

void s12a_wolf2_800CF294(TILE *packs)
{
    int i;

    for (i = 2; i > 0; i--)
    {
        setRGB0(packs, 255, 63, 63);
        packs++;
    }
}

void s12a_wolf2_800CF2C4(Wolf2Work *work)
{
    SVECTOR   sp18;
    SVECTOR   sp20;
    SVECTOR   sp28;
    SVECTOR   sp30;
    VECTOR    sp38;
    VECTOR    sp48;
    MATRIX    sp58;
    MATRIX    sp78;
    short     sp98[2];
    long      p;
    long      flag;
    int       height;
    int       count;
    MAP      *map;
    int       i;
    int       hit;
    int       hit_target;
    int       dist;
    DG_CHANL *chanl;
    int       step;
    int       zoom;

    if (work->f9F8 != 1)
    {
        DG_InvisiblePrim(work->f7E0);
        DG_InvisiblePrim(work->lsight_prim);
        return;
    }

    DG_VisiblePrim(work->f7E0);
    DG_VisiblePrim(work->lsight_prim);

    map = work->control.map;

    height = 0;
    step = 30000;
    count = (work->f6D8 / step) + 1;

    sp18.vx = 0;
    sp18.vy = -step;
    sp18.vz = 0;

    sp20.vx = 0;
    sp20.vy = -550;
    sp20.vz = 100;

    sp58 = work->body.objs->objs[4].world;
    sp58.t[0] = 0;
    sp58.t[1] = 0;
    sp58.t[2] = 0;

    DG_SetPos(&sp58);
    DG_PutVector(&sp18, &sp18, 1);

    sp58 = work->body.objs->objs[4].world;
    DG_SetPos(&sp58);
    DG_PutVector(&sp20, &sp20, 1);

    work->f7E4[0] = sp20;
    work->f7E4[1] = sp20;

    hit = 0;
    hit_target = 0;

    s12a_wolf2_800CF294(work->f7E0->packs[GV_Clock]);

    sp30 = sp20;

    for (i = 0; i < count; i++)
    {
        sp28 = sp20;
        sp38.vx = sp20.vx + sp18.vx;
        sp38.vy = sp20.vy + sp18.vy;
        sp38.vz = sp20.vz + sp18.vz;

        if ((abs(sp38.vx) > 32768) || (abs(sp38.vy) > 32768) || (abs(sp38.vz) > 32768))
        {
            if (sp38.vx > 32700)
            {
                sp18.vy = (sp18.vy * (32700 - sp20.vx)) / sp18.vx;
                sp18.vz = (sp18.vz * (32700 - sp20.vx)) / sp18.vx;
                sp38.vx = 32700;
                sp38.vy = sp20.vy + sp18.vy;
                sp38.vz = sp20.vz + sp18.vz;
                sp48.vx = 32700 - sp20.vx;
            }
            else if (sp38.vx < -32700)
            {
                sp18.vy = (sp18.vy * (-32700 - sp20.vx)) / sp18.vx;
                sp18.vz = (sp18.vz * (-32700 - sp20.vx)) / sp18.vx;
                sp38.vx = -32700;
                sp38.vy = sp20.vy + sp18.vy;
                sp38.vz = sp20.vz + sp18.vz;
                sp48.vx = -32700 - sp20.vx;
            }

            if (sp38.vy > 32700)
            {
                sp18.vx = (sp18.vx * (32700 - sp20.vy)) / sp18.vy;
                sp18.vz = (sp18.vz * (32700 - sp20.vy)) / sp18.vy;
                sp38.vx = sp20.vx + sp18.vx;
                sp38.vy = 32700;
                sp38.vz = sp20.vz + sp18.vz;
                sp48.vy = 32700 - sp20.vy;
            }
            else if (sp38.vy < -32700)
            {
                sp18.vx = (sp18.vx * (-32700 - sp20.vy)) / sp18.vy;
                sp18.vz = (sp18.vz * (-32700 - sp20.vy)) / sp18.vy;
                sp38.vx = sp20.vx + sp18.vx;
                sp38.vy = -32700;
                sp38.vz = sp20.vz + sp18.vz;
                sp48.vy = -32700 - sp20.vy;
            }

            if (sp38.vz > 32700)
            {
                sp18.vy = (sp18.vy * (32700 - sp20.vz)) / sp18.vz;
                sp18.vx = (sp18.vx * (32700 - sp20.vz)) / sp18.vz;
                sp38.vx = sp20.vx + sp18.vx;
                sp38.vy = sp20.vy + sp18.vy;
                sp38.vz = 32700;
                sp48.vz = 32700 - sp20.vz;
            }
            else if (sp38.vz < -32700)
            {
                sp18.vy = (sp18.vy * (-32700 - sp20.vz)) / sp18.vz;
                sp18.vx = (sp18.vx * (-32700 - sp20.vz)) / sp18.vz;
                sp38.vx = sp20.vx + sp18.vx;
                sp38.vy = sp20.vy + sp18.vy;
                sp38.vz = -32700;
                sp48.vz = -32700 - sp20.vz;
            }
        }

        sp20.vx = sp38.vx;
        sp20.vy = sp38.vy;
        sp20.vz = sp38.vz;

        if (GM_Target_8002E1B8(&sp28, &sp20, map->index, &sp20, ENEMY_SIDE))
        {
            hit = 1;
            hit_target = 1;
        }

        if (HZD_LineCheck(map->hzd, &sp28, &sp20, 5, 4))
        {
            HZD_LineNearVec(&sp20);
            hit = 1;
        }

        if (hit == 0)
        {
            continue;
        }

        sp20.vx += GV_RandS(16);
        sp20.vy += GV_RandS(16);
        sp20.vz += GV_RandS(16);

        DG_PointCheck(&work->control.mov, 1);

        if ((work->control.mov.pad == 1) &&
            (GM_Camera.zoom > 900) &&
            (work->f9A8 == 0) &&
            (hit_target == 1) &&
            ((GM_CurrentWeaponId == WP_Rifle) || (GM_CurrentItemId == IT_Scope)))
        {
            chanl = DG_Chanl(0);
            DG_Clip(&chanl->clip_rect, chanl->clip_distance);
            gte_SetRotMatrix(&chanl->eye_inv);
            gte_SetTransMatrix(&chanl->eye_inv);
            RotTransPers(&sp20, (long *)sp98, &p, &flag);

            dist = (ABS(160 - sp98[0]) + ABS(102 - sp98[1])) & 0xFFF;
            if (dist < 90)
            {
                work->fA64 = 1;
                GM_SeSet2(0, 127, SE_LASER_SIGHT);

                DG_InvisiblePrim(work->f7E0);
                DG_InvisiblePrim(work->lsight_prim);

                i = (90 - dist) / 2 + 160;
                if (i > work->fA10.vx)
                {
                    work->fA10.vx = i;
                    work->fA10.vy = i / 4;
                    work->fA10.vz = 0;
                }

                sp78 = sp58;
                sp78.t[0] = (work->f9FC.vx * 3 + work->body.objs->objs[4].world.t[0]) / 4;
                sp78.t[1] = (work->f9FC.vy * 3 + work->body.objs->objs[4].world.t[1]) / 4;
                sp78.t[2] = (work->f9FC.vz * 3 + work->body.objs->objs[4].world.t[2]) / 4;
                DG_SetPos(&sp78);

                sp18 = DG_ZeroVector;
                zoom = (GM_Camera.zoom - 320) * 17000 / 3401 + 1000;
                sp18.vy = zoom - work->f6D8 / 4;
                DG_PutVector(&sp18, &sp30, 1);

                sp30.vx += GV_RandS(8);
                sp30.vy += GV_RandS(8);
                sp30.vz += GV_RandS(8);
                s01a_object_800D952C(&sp30, 0);

                sp30.vx += GV_RandS(128);
                sp30.vy += GV_RandS(128);
                sp30.vz += GV_RandS(128);
                s01a_object_800D952C(&sp30, 1);

                sp18.vx = work->body.objs->objs[4].world.t[0];
                sp18.vy = work->body.objs->objs[4].world.t[1];
                sp18.vz = work->body.objs->objs[4].world.t[2];

                for (i = 0; i < 8; i++)
                {
                    work->lsight_verts[i * 2] = sp18;
                    work->lsight_verts[i * 2 + 1] = sp18;
                }
            }

            return;
        }

        GV_SubVec3(&sp28, &sp20, &sp18);
        height = i * 30000 + GV_VecLen3(&sp18);
        break;
    }

    sp18.vx = 0;
    sp18.vy = -height / 8;
    sp18.vz = 0;

    sp20 = sp30;

    if (work->f6FC <= 0)
    {
        for (i = 0; i < 8; i++)
        {
            work->lsight_verts[i * 2] = sp20;
            work->lsight_verts[i * 2 + 1] = sp20;
        }
    }
    else
    {
        for (i = 0; i < 8; i++)
        {
            sp58.t[0] = sp20.vx;
            sp58.t[1] = sp20.vy;
            sp58.t[2] = sp20.vz;

            work->lsight_verts[i * 2] = sp20;

            DG_SetPos(&sp58);
            DG_PutVector(&sp18, &sp20, 1);

            work->lsight_verts[i * 2 + 1] = sp20;
        }
    }

    work->f7E4[1] = work->f7CC;
}

void s12a_wolf2_800D0168(Wolf2Work *work, int unit, int count)
{
    MATRIX world;

    DG_SetPos(&work->body.objs->objs[unit].world);
    DG_MovePos(&s12a_dword_800C3498);
    DG_RotatePos(&s12a_dword_800C34A0);
    ReadRotMatrix(&world);
    NewBlood(&world, count);
}

int s12a_wolf2_800D01D8(Wolf2Work *work)
{
    SVECTOR pos;
    SVECTOR center;

    pos.vx = work->body.objs->objs[4].world.t[0];
    pos.vy = work->body.objs->objs[4].world.t[1];
    pos.vz = work->body.objs->objs[4].world.t[2];
    center.vx = (work->f9FC.vx + pos.vx) / 2;
    center.vy = (work->f9FC.vy + pos.vy) / 2;
    center.vz = (work->f9FC.vz + pos.vz) / 2;
    return HZD_LineCheck(work->control.map->hzd, &pos, &center, 5, 4) != 0;
}

int s12a_wolf2_800D0298(Wolf2Work *work)
{
    SVECTOR pos;
    SVECTOR center;

    pos.vx = work->body.objs->objs[4].world.t[0];
    pos.vy = work->body.objs->objs[4].world.t[1];
    pos.vz = work->body.objs->objs[4].world.t[2];
    center.vx = (work->f9FC.vx + pos.vx) / 2;
    center.vy = (work->f9FC.vy + pos.vy) / 2;
    center.vz = (work->f9FC.vz + pos.vz) / 2;
    return HZD_LineCheck(work->control.map->hzd, &work->f9FC, &center, 5, 4) != 0;
}

void s12a_wolf2_800D0358(Wolf2Work *work)
{
    MATRIX  sp28;
    MATRIX  sp48;
    SVECTOR sp68;
    SVECTOR sp70;

    if (GM_PlayerStatus & ( PLAYER_NOT_PLAYABLE | PLAYER_DAMAGED | PLAYER_INVINCIBLE ))
    {
        return;
    }

    if ((work->f9E8 == 2) || (work->fA04 == 1) || (work->f718 == 1) ||
        ((s12a_wolf2_800D0298(work) != 1) && (s12a_wolf2_800D01D8(work) != 1)))
    {
        work->f71C = 0;
        work->f6DC--;

        sp68.vx = work->body.objs->objs[4].world.t[0];
        sp68.vy = work->body.objs->objs[4].world.t[1];
        sp68.vz = work->body.objs->objs[4].world.t[2];
        s12a_wolf2_800CEED4(work->f6D8, &sp68, &work->f9FC, &sp70);

        sp28 = work->body.objs->objs[4].world;
        RotMatrixYXZ_gte(&sp70, &sp28);

        sp48 = sp28;
        DG_SetPos(&sp48);
        DG_MovePos(&s12a_dword_800C34B0);
        ReadRotMatrix(&sp28);

        sp70.vx = 1024;
        sp70.vy = 0;
        sp70.vz = 0;

        if (work->f718 != 1)
        {
            NewAnime_8005E1A0(&sp28);

            DG_SetPos(&sp28);
            DG_MovePos(&s12a_dword_800C34A8);
            DG_RotatePos(&sp70);
            ReadRotMatrix(&sp28);

            if (work->f99C == 0)
            {
                NewBulletEx(512, &sp28, ENEMY_SIDE, 0, 1, 10, 128, 300000, 5000);
            }
            else
            {
                NewBulletEx(1024, &sp28, ENEMY_SIDE, 0, 1, 10, 128, 300000, 5000);
            }
        }
        else
        {
            sp70.vx = 512;
            sp70.vy = 0;
            sp70.vz = 0;

            if ((GM_SnakeCurrentHealth != 0) && (GM_GameOverTimer == 0))
            {
                work->fA70 = 1;

                DG_SetPos2(&GM_PlayerPosition, &sp70);
                ReadRotMatrix(&sp28);

                if (work->f9C8 != -1)
                {
                    NewBulletEx(2048, &sp28, ENEMY_SIDE, 0, 1, 10, 0, 500, 2000);

                    if (work->f9C8 != -1)
                    {
                        work->last_item = GM_CurrentItemId;
                        work->last_weapon = GM_CurrentWeaponId;

                        if ((GM_CurrentItemId == IT_Scope) || (GM_CurrentItemId == IT_Camera) ||
                            (GM_CurrentItemId == IT_NVG) || (GM_CurrentItemId == IT_ThermG))
                        {
                            GM_CurrentItemId = -1;
                        }

                        if ((GM_CurrentWeaponId == WP_Rifle) || (GM_CurrentWeaponId == WP_Stinger))
                        {
                            GM_CurrentWeaponId = -1;
                        }

                        work->f9CC = 1;
                    }
                }
                else
                {
                    NewBulletEx(2048, &sp28, ENEMY_SIDE, 0, 1, 10, 64, 500, 2000);
                }
            }
        }

        GM_SeSet2(0, 19, 179);
        s12a_wolf2_800CF03C(work->adjust, 16);
    }
}

int s12a_wolf2_800D0734(Wolf2Work *work)
{
    if ((work->fA64 == 1) && ((GV_Time % 32) == 0) && (GV_RandU(8) == 0))
    {
        return 1;
    }

    return 0;
}

void s12a_wolf2_800D078C(Wolf2Work *work)
{
    if (work->fA2C <= 0)
    {
        work->f65C->damaged &= ~TARGET_POWER;
        work->f660->damaged &= ~TARGET_POWER;
        work->f748 = 0;
    }
}

int s12a_wolf2_800D07D8(Wolf2Work *work, SVECTOR *pos)
{
    int x, y, z;

    x = (pos->vx - work->f9FC.vx) >> 4;
    y = (pos->vy - work->f9FC.vy) >> 4;
    z = (pos->vz - work->f9FC.vz) >> 4;
    return SquareRoot0(x * x + y * y + z * z) << 4;
}

void s12a_wolf2_800D0848(Wolf2Work *work, int action, int arg2)
{
    if (work->f6C0 != action)
    {
        work->f6C0 = action;
        GM_ConfigObjectAction(&work->body, action, 0, 4);
    }
    else if (work->body.is_end == 1)
    {
        work->f6D4 = arg2;
    }
}

void s12a_wolf2_800D08A0(Wolf2Work *work, int action)
{
    if (work->body.is_end == 1)
    {
        work->f6C0 = action;
        GM_ConfigObjectAction(&work->body, action, 0, 4);
    }
}

void s12a_wolf2_800D08D8(Wolf2Work *work, int action)
{
    work->f6C0 = action;
    GM_ConfigObjectAction(&work->body, action, 0, 4);
}

void s12a_wolf2_800D0904(Wolf2Work *work, int action1, int action2, int arg3)
{
    if (work->f6C0 != action1)
    {
        work->f6C0 = action1;
        GM_ConfigObjectAction(&work->body, action1, 0, 4);
    }
    else if (work->body.is_end == 1)
    {
        work->f6C0 = action2;
        GM_ConfigObjectAction(&work->body, action2, 0, 4);
        work->f6D4 = arg3;
    }
}

void s12a_wolf2_800D0980(Wolf2Work *work)
{
    if ((work->fA0C == 0) && (work->fA68 == 0))
    {
        work->fA0C = 1;

        if (GM_GameOverTimer == 0)
        {
            /* Zanzibar Breeze */
            GM_SetSong(0x01000002);
        }
    }
}

void s12a_wolf2_800D09D4(Wolf2Work *work, int arg1)
{
    if ((s12a_wolf2_800D01D8(work) == 1) || (GM_Camera.zoom < 900))
    {
        return;
    }

    if (work->body.objs->bound_mode != 0)
    {
        if ((work->f704 == 0) && (GM_CurrentWeaponId == WP_Rifle))
        {
            work->f704 = 1;
            work->f708 = 150;
        }

        if (work->body.objs->bound_mode != 0)
        {
            if (work->f708 != 0)
            {
                if (--work->f708 == 30)
                {
                    GM_SeSet2(0, 127, 131);
                    AN_Unknown_800CA1EC(&work->body.objs->objs[6].world, 0);
                }

                if (work->f708 == 1)
                {
                    if ((work->f6D4 != 0) && (work->f6D4 != 34))
                    {
                        work->f6D4 = arg1;
                    }

                    work->f708 = 0;
                }
            }

            if (work->body.objs->bound_mode == 0)
            {
                work->f704 = 0;
            }
        }
        else
        {
            work->f704 = 0;
        }
    }
    else
    {
        work->f704 = 0;
    }
}

void s12a_wolf2_800D0B04(Wolf2Work *work, int arg1)
{
    int dir;

    if (GV_RandU(4) == 0)
    {
        if (work->f728 == 1)
        {
            work->f728 = 0;
        }

        if (work->f728 == 0)
        {
            work->f728 = 1;
        }
    }

    if (work->f728 == 1)
    {
        dir = -1;
    }
    else
    {
        dir = 1;
    }

    work->f884 = work->f880 + dir;
    if ((work->f7FC - 1) < work->f884)
    {
        work->f884 = work->f7FC - 2;
        work->f728 = 1;
    }

    if (work->f884 < 0)
    {
        work->f884 = 1;
        work->f728 = 0;
    }

    if (work->f888[work->f884].vx > work->control.mov.vx)
    {
        if (arg1 == 0)
        {
            work->control.turn.vy -= 1024;
        }
    }
    else
    {
        if (arg1 == 0)
        {
            work->control.turn.vy += 1024;
        }
    }

    work->f880 = work->f884;
}

void s12a_wolf2_800D0C1C(Wolf2Work *work, int arg1)
{
    int x, z;

    z = work->f988.vz - work->control.mov.vz;
    x = work->f988.vx - work->control.mov.vx;
    work->control.turn.vy = ratan2(x, z) & 0xFFF;

    if (work->control.mov.vx < work->f888[work->f884].vx)
    {
        if (arg1 == 0)
        {
            work->control.turn.vy -= 1024;
        }
    }
    else
    {
        if (arg1 == 0)
        {
            work->control.turn.vy += 1024;
        }
    }
}

int s12a_wolf2_800D0CAC(Wolf2Work *work)
{
    SVECTOR tgt;
    SVECTOR pos;
    SVECTOR center;
    int     mov;
    int     i, j;

    mov = 100;

    if (work->f99C == 0)
    {
        return 3;
    }

    pos = work->control.mov;
    pos.vy += 1000;

    center.vx = (work->f9FC.vx + pos.vx) / 2;
    center.vy = (work->f9FC.vy + pos.vy) / 2;
    center.vz = (work->f9FC.vz + pos.vz) / 2;

    tgt = center;
    for (i = 0; i < 4; i++)
    {
        if (!HZD_LineCheck(work->control.map->hzd, &pos, &tgt, 5, 2))
        {
            break;
        }

        tgt.vx -= mov;
        pos.vx -= mov;
    }

    pos = work->control.mov;
    pos.vy += 1000;

    tgt = center;
    for (j = 0; j < 4; j++)
    {
        if (!HZD_LineCheck(work->control.map->hzd, &pos, &tgt, 5, 2))
        {
            break;
        }

        tgt.vx += mov;
        pos.vx += mov;
    }

    if ((i == 4) || (j == 4))
    {
        return 0;
    }

    if ((i != 0) && (i == j))
    {
        return 3;
    }

    if (i >= j)
    {
        return (i > j) ? 2 : 0;
    }

    return 1;
}

void s12a_wolf2_800D0ED4(Wolf2Work *work)
{
    SVECTOR pos;
    SVECTOR rot;
    SVECTOR local_20;
    SVECTOR local_18;
    int     x, y, z;
    int     len;
    int     rnd;

    switch (work->f6D4)
    {
    case 18:
        work->f9FC = GM_PlayerPosition;

        s12a_wolf2_800CED64(work);
        work->f720 = GV_RandU(4);
        work->f9A8 = 0;

        s12a_wolf2_800CF03C(work->adjust, 16);
        work->f6F4 = 0;
        work->f6F8 = 0;

        s12a_wolf2_800D0B04(work, 1);
        work->f6D4 = 19;

        pos = work->f888[work->f880];
        x = (pos.vx - work->f9FC.vx) >> 4;
        y = (pos.vy - work->f9FC.vy) >> 4;
        z = (pos.vz - work->f9FC.vz) >> 4;

        len = SquareRoot0(x * x + y * y + z * z) << 4;
        s12a_wolf2_800CEED4(len, &work->f9FC, &pos, &rot);
        rot.vx -= 1024;

        DG_SetPos2(&pos, &rot);

        local_20 = DG_ZeroVector;
        local_20.vz = -1500;
        DG_PutVector(&local_20, &local_20, 1);
        work->f988 = local_20;
        /* fallthrough */
    case 19:
        s12a_wolf2_800D0C1C(work, 1);

        local_18.vx = ABS(work->control.mov.vx - work->f988.vx);
        local_18.vz = ABS(work->control.mov.vz - work->f988.vz);

        if (local_18.vx < 200)
        {
            work->control.turn = DG_ZeroVector;
            work->control.rot = DG_ZeroVector;

            if (((work->f99C == 1) && (work->f988.vx > -4000 && work->f988.vx < 7000)) ||
                ((GV_RandU(16) == 0) && (work->f800[work->f880] != 1)))
            {
                work->f6D4 = 18;
                break;
            }

            switch (work->f800[work->f880])
            {
            case 0:
                GM_SeSet2(0, 31, SE_READY_WEAPON);
                s12a_wolf2_800CEFF0(work, 6);
                s12a_wolf2_800D0904(work, 3, 0, 0);
                break;
            case 1:
                GM_SeSet2(0, 31, SE_READY_WEAPON);
                s12a_wolf2_800CEFF0(work, 7);
                s12a_wolf2_800D08D8(work, 11);
                break;
            case 2:
                work->f6F8 = 0;
                work->f6D4 = 20;
                s12a_wolf2_800CEDC0(work);
                s12a_wolf2_800D08D8(work, 13);
                break;
            case 3:
                work->f6D4 = 30;
                break;
            }
        }
        else
        {
            s12a_wolf2_800D0848(work, 25, 19);
        }
        break;
    case 30:
        work->f9A8 = 1;
        s12a_wolf2_800D0904(work, 3, 0, 31);

        work->f6F4 = GV_RandU(32) + 150;
        break;
    case 31:
        s12a_wolf2_800D08D8(work, 0);

        if (work->f6F4-- <= 0)
        {
            work->f6D4 = 33;
        }
        break;
    case 20:
        work->f6D4 = 21;
        s12a_wolf2_800CEDC0(work);
        /* fallthrough */
    case 21:
        pos = work->f888[work->f880];
        x = (pos.vx - GM_PlayerPosition.vx) / 16;
        y = (pos.vy - GM_PlayerPosition.vy) / 16;
        z = (pos.vz - GM_PlayerPosition.vz) / 16;
        len = SquareRoot0(x * x + y * y + z * z) << 4;

        s12a_wolf2_800CEED4(len, &GM_PlayerPosition, &pos, &rot);
        rot.vx -= 1024;


        DG_SetPos2(&pos, &rot);

        local_20 = DG_ZeroVector;
        local_20.vz = -1000;
        DG_PutVector(&local_20, &local_20, 1);

        x = (local_20.vx - work->control.mov.vx) / 16;
        y = (local_20.vy - work->control.mov.vy) / 16;
        z = (local_20.vz - work->control.mov.vz) / 16;
        len = SquareRoot0(x * x + y * y + z * z) << 4;

        if (len > 1100)
        {
            work->f6D4 = 18;
            s12a_wolf2_800D08D8(work, 13);
        }
        else
        {
            work->control.mov = local_20;
            work->f9F8 = 0;

            rnd = GV_RandU(1024);
            s12a_wolf2_800CEF50(work);

            if (work->f6F8 == 30)
            {
                if (GV_RandU(8) == 0)
                {
                    work->f6D4 = 18;
                }

                s12a_wolf2_800D08D8(work, 13);
            }
            else
            {
                if ((rnd <= 512) && (work->f6F8 >= 240))
                {
                    work->f6F8 = 0;
                    work->f6E4 = 1;
                    work->f6F4++;

                    switch (s12a_wolf2_800D0CAC(work))
                    {
                    case 0:
                        work->f6D4 = 18;
                        break;
                    case 1:
                        work->f6D4 = 22;
                        GM_SeSet2(0, 31, SE_READY_WEAPON);
                        s12a_wolf2_800CED64(work);
                        break;
                    case 2:
                        work->f6D4 = 26;
                        GM_SeSet2(0, 31, SE_READY_WEAPON);
                        s12a_wolf2_800CED64(work);
                        break;
                    case 3:
                        if (GV_RandU(2) == 0)
                        {
                            work->f6D4 = 22;
                        }
                        else
                        {
                            work->f6D4 = 26;
                        }

                        GM_SeSet2(0, 31, SE_READY_WEAPON);
                        s12a_wolf2_800CED64(work);
                        break;
                    }
                }
                else if (rnd <= work->f6F4)
                {
                    work->f6D4 = 18;
                    s12a_wolf2_800CED64(work);
                }
                else
                {
                    s12a_wolf2_800D08D8(work, 13);
                    break;
                }

                s12a_wolf2_800D08D8(work, 13);
            }
        }
        break;
    case 22:
        work->f9F8 = 1;
        s12a_wolf2_800D0848(work, 14, 23);
        break;
    case 23:
        s12a_wolf2_800D09D4(work, 18);

        if ((work->f6E8-- < 0) || s12a_wolf2_800D0734(work))
        {
            work->f6D4 = 24;
        }

        s12a_wolf2_800D08D8(work, 15);
        break;
    case 24:
        work->f9F8 = 0;
        s12a_wolf2_800D0358(work);

        work->f6D4 = 25;
        s12a_wolf2_800D08D8(work, 16);
        break;
    case 25:
        s12a_wolf2_800D0848(work, 17, 20);
        break;
    case 26:
        work->f9F8 = 1;
        s12a_wolf2_800D0848(work, 18, 27);
        break;
    case 27:
        s12a_wolf2_800D09D4(work, 18);

        if ((work->f6E8-- < 0) || s12a_wolf2_800D0734(work))
        {
            work->f6D4 = 28;
        }

        s12a_wolf2_800D08D8(work, 19);
        break;
    case 28:
        work->f9F8 = 0;
        s12a_wolf2_800D0358(work);

        work->f6D4 = 29;
        s12a_wolf2_800D08D8(work, 20);
        break;
    case 29:
        s12a_wolf2_800D0848(work, 21, 20);
        break;
    case 6:
        work->f6F4 = 1;
        s12a_wolf2_800D0904(work, 3, 0, 0);
        break;
    case 7:
        work->f6F4 = 1;
        s12a_wolf2_800D08D8(work, 11);
        s12a_wolf2_800CEFF0(work, 1);
        break;
    case 0:
        work->fA2C = -1;

        s12a_wolf2_800CEE78(work);
        work->f9F8 = 1;

        s12a_wolf2_800D09D4(work, 4);

        if ((work->f6E8-- < 0) || s12a_wolf2_800D0734(work))
        {
            work->f6D4 = 2;
        }
        else
        {
            s12a_wolf2_800D08D8(work, 0);
        }
        break;
    case 1:
        s12a_wolf2_800CEE1C(work);

        if (!s12a_wolf2_800D01D8(work))
        {
            work->f6E8 = 30;
        }

        work->f6D4 = 34;
        /* fallthrough */
    case 34:
        work->f9F8 = 1;
        s12a_wolf2_800D09D4(work, 5);

        if ((work->f6E8-- < 0) || s12a_wolf2_800D0734(work))
        {
            work->f6D4 = 3;
        }
        else
        {
            s12a_wolf2_800D08D8(work, 11);
        }
        break;
    case 2:
        s12a_wolf2_800D08A0(work, 1);
        work->f9F8 = 0;

        s12a_wolf2_800D0358(work);

        if (work->f6DC <= 0)
        {
            work->f6D4 = 16;
            work->f6DC = work->f6E0;
        }
        else if (GV_RandU(2) == 0)
        {
            work->f6D4 = 4;
        }
        else
        {
            work->f6F4 = 1;
            s12a_wolf2_800CEFF0(work, 0);
        }
        break;
    case 3:
        s12a_wolf2_800D08A0(work, 12);
        work->f9F8 = 0;

        s12a_wolf2_800D0358(work);

        if (work->f6DC <= 0)
        {
            work->f6D4 = 17;
            work->f6DC = work->f6E0;
        }
        else
        {
            work->f6D4 = 5;
        }
        break;
    case 16:
        s12a_wolf2_800D0848(work, 24, 0);
        break;
    case 17:
        s12a_wolf2_800D0848(work, 23, 1);
        break;
    case 4:
        work->f9F8 = 0;
        s12a_wolf2_800D0848(work, 2, 18);
        break;
    case 5:
        work->f9F8 = 0;
        work->f6D4 = 18;
        break;
    case 8:
        s12a_wolf2_800D0848(work, 7, 18);
        break;
    case 9:
        if (work->fA4C != -1)
        {
            GM_GameStatus |= STATE_PADRELEASE;
        }

        if (work->f6C0 != 10)
        {
            work->f6C0 = 10;
            GM_ConfigObjectAction(&work->body, 10, 0, 0);
        }
        else if (work->body.is_end == 1)
        {
            work->f6C0 = 9;
            GM_ConfigObjectAction(&work->body, 9, 0, 0);

            work->f6F4 = 90;
            work->f6D4 = 11;
        }
        break;
    case 10:
    case 33:
        s12a_wolf2_800D0848(work, 2, 18);
        break;
    case 12:
        if (GV_RandU(16) < 2)
        {
            s12a_wolf2_800D0848(work, 6, 15);
        }
        else
        {
            s12a_wolf2_800D0848(work, 6, 4);
        }
        break;
    case 13:
        if (work->fA4C != -1)
        {
            GM_GameStatus |= STATE_PADRELEASE;
        }

        work->f6F4 = 90;
        s12a_wolf2_800D0904(work, 8, 9, 11);
        break;
    case 15:
        work->f6F4 = 1;
        s12a_wolf2_800CEFF0(work, 0);
        s12a_wolf2_800D08D8(work, 0);
        break;
    case 11:
        s12a_wolf2_800D0848(work, 9, 11);
        work->f9BC = 1;

        if (work->f6F4 > 0)
        {
            work->f6F4--;

            if ((work->fA4C != -1) && (GM_SnakeCurrentHealth != 0) && (GM_GameOverTimer == 0))
            {
                GCL_ForceExecProc(work->fA4C, 0);
            }
        }
        break;
    }
}

void s12a_wolf2_800D1B64(Wolf2Work *work)
{
    if (work->f6D0 == 0)
    {
        s12a_wolf2_800D0ED4(work);
    }
}

void s12a_wolf2_800D1B94(Wolf2Work *work)
{
    GCL_ARGS args;
    long     data[3];

    args.argc = 3;
    args.argv = data;

    data[0] = GM_PlayerPosition.vx;
    data[1] = GM_PlayerPosition.vy;
    data[2] = GM_PlayerPosition.vz;
    GCL_ExecProc(work->f9C8, &args);
}

void s12a_wolf2_800D1BE8(Wolf2Work *work)
{
    SVECTOR eye;
    SVECTOR center;
    SVECTOR pos;

    if ((GV_Time % 60) == 0)
    {
        GM_SeSet2(0, 63, 135);
    }

    GV_PadData[0].status &= ~PAD_UP;
    GV_PadData[0].press = GV_PadData[0].status;

    pos = GM_PlayerPosition;
    pos.vy += (rsin(GV_Time * 64) - rsin(GV_Time * 31) / 2 - rsin(GV_Time * 131) / 2) / 16;
    pos.vx += (rsin(GV_Time * 23) - rsin(GV_Time * 45) / 2 - rsin(GV_Time * 145) / 2) / 16;

    eye = work->fA18;
    center.vx = (work->fA18.vx * 31 + pos.vx) / 32;
    center.vy = (work->fA18.vy * 31 + pos.vy) / 32;
    center.vz = (work->fA18.vz * 31 + pos.vz) / 32;

    DG_LookAt(DG_Chanl(0), &eye, &center, 3721);

    GM_Camera.field_2A = 0;
    GM_Camera.zoom = 3721;

    gUnkCameraStruct2_800B7868.eye = eye;
    gUnkCameraStruct2_800B7868.center = center;
}

void s12a_wolf2_800D1EBC(Wolf2Work *work)
{
    SVECTOR target_pos;
    MATRIX  world1;
    MATRIX  world2;
    TARGET *target1;
    TARGET *target2;
    u_long *ot;
    u_short x, y, z;

    work->fA64 = 0;

    world1 = work->body.objs->objs[work->fA5C].world;
    world2 = work->body.objs->objs[work->fA60].world;

    target1 = work->f65C;
    target2 = work->f660;

    if ((work->f99C == 0) && (GM_CurrentWeaponId == WP_Nikita))
    {
        target1->class &= ~TARGET_FLAG;
        target1->class |= TARGET_AVAIL;
        target2->class &= ~TARGET_FLAG;
        target2->class |= TARGET_AVAIL;
        work->fA54 = 90;
    }
    else if (work->fA54 > 0)
    {
        work->fA54--;
    }
    else
    {
        work->fA54 = 0;
        target1->class |= TARGET_FLAG;
        target2->class |= TARGET_FLAG;
    }

    if ((work->f99C == 0) || (work->f9C8 == -1))
    {
        GM_GameStatus &= ~STATE_PADRELEASE;
    }

    GM_GameStatus |= GAME_FLAG_BIT_09;

    if (work->voices[0] > 0)
    {
        work->voices[0]--;
    }

    if (work->f9C8 != -1)
    {
        if (work->f9CC == 2)
        {
            if (work->f9F0 != 1)
            {
                work->f9F0 = 1;
                NewRifleSightFast();
                GM_GameStatus |= ( STATE_RADAR_OFF | STATE_MENU_OFF | STATE_LIFEBAR_OFF );
            }

            s12a_wolf2_800D1BE8(work);

            if (!(GM_PlayerStatus & STATE_JAMMING) || GM_InBox())
            {
                work->f9CC = 3;
            }
        }

        if (work->f9CC > 2)
        {
            work->f9CC++;
            s12a_wolf2_800D1BE8(work);

            GV_DemoPadStatus[0] = 0;
            GV_DemoPadStatus[1] = 0;

            if (work->f9CC == 40)
            {
                GV_DemoPadStatus[0] = PAD_CROSS;
            }
            else if (work->f9CC == 70)
            {
                GV_DemoPadStatus[0] = PAD_UP;
            }
            else if (work->f9CC == 85)
            {
                GV_DemoPadStatus[0] = PAD_CROSS;
            }
            else if (work->f9CC == 119)
            {
                GM_SeSet2(0, 63, SE_RADIO_INCOMING);
            }
            else if (work->f9CC == 149)
            {
                if ((work->last_weapon == WP_Rifle) || (work->last_weapon == WP_Stinger))
                {
                    GM_CurrentWeaponId = work->last_weapon;
                }

                if ((work->last_item == IT_Scope) || (work->last_item == IT_Camera) ||
                    (work->last_item == IT_NVG) || (work->last_item == IT_ThermG))
                {
                    GM_CurrentItemId = work->last_item;
                }

                GV_DemoPadStatus[0] = ( PAD_L1 | PAD_R1 );
            }
            else if (work->f9CC > 149)
            {
                GM_GameStatus &= ~STATE_PADDEMO;
                s12a_wolf2_800D1B94(work);
                GV_DestroyActor(work);
            }
        }

        if ((work->f9CC == 1) && (GM_SnakeCurrentHealth != 0) && (GM_GameOverTimer == 0))
        {
            work->f9CC = 2;

            GV_DemoPadStatus[0] = 0;
            GV_DemoPadStatus[1] = 0;

            GM_GameStatus |= STATE_PADDEMO;

            if (GM_PlayerPosition.vx < 13000)
            {
                work->fA18.vx = 7464;
                work->fA18.vy = 8000;
                work->fA18.vz = -14000;
            }
            else
            {
                work->fA18.vx = 55000;
                work->fA18.vy = 8000;
                work->fA18.vz = -14000;
            }
        }
    }

    if (((GV_Time % 15) == 0) && (GV_RandU(2) == 0))
    {
        work->f9FC.vx = GM_PlayerBody->objs->objs[4].world.t[0];
        work->f9FC.vy = GM_PlayerBody->objs->objs[4].world.t[1];
        work->f9FC.vz = GM_PlayerBody->objs->objs[4].world.t[2];

        if (work->f9E8 == 2)
        {
            if (s12a_wolf2_800D0298(work))
            {
                work->fA04 = 1;
                work->f9FC = wolf2_position;
            }
            else
            {
                work->fA04 = 0;
            }
        }
    }

    work->f6D8 = s12a_wolf2_800D07D8(work, &work->control.mov);

    if ((work->f6FC > 0) &&
        (work->f9D0 > GM_PlayerPosition.vz) &&
        ~(GM_PlayerStatus & STATE_JAMMING) &&
        (GM_CurrentWeaponId != WP_Rifle) &&
        (GM_SnakeCurrentHealth != 0) &&
        (GM_GameOverTimer == 0))
    {
        GM_GameStatus |= STATE_PADRELEASE;

        if ((GM_CurrentItemId == IT_Scope) || (GM_CurrentItemId == IT_Camera) ||
            (GM_CurrentItemId == IT_NVG) || (GM_CurrentItemId == IT_ThermG))
        {
            GM_CurrentItemId = IT_None;
        }

        if ((GM_CurrentWeaponId == WP_Rifle) || (GM_CurrentWeaponId == WP_Stinger))
        {
            GM_CurrentWeaponId = WP_None;
        }

        work->f718 = 1;
        work->f6E8 = 0;

        work->control.rot = work->f990;

        work->f65C->damaged &= ~TARGET_POWER;
        work->f660->damaged &= ~TARGET_POWER;

        if (work->fA08 == 0)
        {
            work->fA08 = 1;
        }

        if ((work->f9C8 == -1) || (work->fA70 == 0))
        {
            s12a_wolf2_800D0358(work);
        }

        if (work->fA08 == 1)
        {
            work->fA08 = 2;
        }
    }
    else if ((work->fA68 != 1) || (work->fA6C != 0))
    {
        if (work->f9C8 != -1)
        {
            DG_InvisiblePrim(work->f7E0);
            DG_InvisiblePrim(work->lsight_prim);

            target1->class |= TARGET_NO_LOCKON;
            target2->class |= TARGET_NO_LOCKON;

            target1->damaged |= TARGET_POWER;
            target2->damaged |= TARGET_POWER;

            GM_MoveTarget(target1, &target_pos);
            GM_MoveTarget(target2, &target_pos);

            target1->center.vx = world1.t[0] + ((SVECTOR *)&work->f6AC)->vx;
            target1->center.vy = world1.t[1] + ((SVECTOR *)&work->f6AC)->vy;
            target1->center.vz = world1.t[2] + ((SVECTOR *)&work->f6AC)->vz;
            target2->center.vx = world2.t[0] + work->f6B4.vx;
            target2->center.vy = world2.t[1] + work->f6B4.vy;
            target2->center.vz = world2.t[2] + work->f6B4.vz;
            return;
        }

        work->f718 = 0;

        switch (work->f6CC)
        {
        case 0:
            s12a_wolf2_800D0980(work);
            work->f6CC = 1;
            break;
        case 1:
            s12a_wolf2_800D1B64(work);
            break;
        }

        if (work->f6FC < 1)
        {
            target_pos.vx = 0;
            target_pos.vy = -10000;
            target_pos.vz = 0;

            target1->class |= TARGET_NO_LOCKON;
            target2->class |= TARGET_NO_LOCKON;

            GM_MoveTarget(target1, &target_pos);
            GM_MoveTarget(target2, &target_pos);

            work->fA10 = DG_ZeroVector;
            return;
        }

        s12a_wolf2_800CF084(work, work->f6E8, work->f710, work->f714);
    }

    s12a_wolf2_800CF2C4(work);

    if (GM_CurrentWeaponId == WP_Rifle)
    {
        if (work->fA10.vx > 0)
        {
            ot = DG_Chanl(0)->ot[GV_Clock];
            addPrim(ot, &work->alloc->tile[GV_Clock]);
            addPrim(ot, &work->alloc->tpage[GV_Clock]);
        }

        setRGB0(&work->alloc->tile[GV_Clock], work->fA10.vx, work->fA10.vy, work->fA10.vz);

        work->fA10.vx -= work->fA10.vx / 8;
        work->fA10.vy -= work->fA10.vy / 8;
        work->fA10.vz -= work->fA10.vz / 8;

        x = work->fA10.vx - 1;
        if (x < 31)
        {
            work->fA10.vx--;
        }

        y = work->fA10.vy - 1;
        if (y < 31)
        {
            work->fA10.vy--;
        }

        z = work->fA10.vz - 1;
        if (z < 31)
        {
            work->fA10.vz--;
        }
    }
    else
    {
        work->fA10 = DG_ZeroVector;
    }

    if (GM_CurrentWeaponId == WP_Stinger)
    {
        target_pos.vx = 0;
        target_pos.vy = -10000;
        target_pos.vz = 0;

        target1->class |= TARGET_NO_LOCKON;
        target2->class |= TARGET_NO_LOCKON;

        GM_MoveTarget(target1, &target_pos);
        GM_MoveTarget(target2, &target_pos);
    }
    else
    {
        target1->class &= ~TARGET_NO_LOCKON;
        target2->class &= ~TARGET_NO_LOCKON;

        target_pos.vx = work->body.objs->objs[0].world.t[0];
        target_pos.vy = work->body.objs->objs[0].world.t[1] + ((SVECTOR *)&work->f6AC)->vy;
        target_pos.vz = work->body.objs->objs[0].world.t[2];
        GM_MoveTarget(target1, &target_pos);

        target_pos.vy = work->body.objs->objs[0].world.t[1] + work->f6B4.vy;
        GM_MoveTarget(target2, &target_pos);
    }

    target1->center.vx = world1.t[0] + ((SVECTOR *)&work->f6AC)->vx;
    target1->center.vy = world1.t[1] + ((SVECTOR *)&work->f6AC)->vy;
    target1->center.vz = world1.t[2] + ((SVECTOR *)&work->f6AC)->vz;
    target2->center.vx = world2.t[0] + work->f6B4.vx;
    target2->center.vy = world2.t[1] + work->f6B4.vy;
    target2->center.vz = world2.t[2] + work->f6B4.vz;

    if ((((target1->damaged & TARGET_POWER) || (target2->damaged & TARGET_POWER)) && (work->f748 == 0) && (work->fA54 == 0)) ||
        ((work->fA68 == 1) && (work->fA6C == 0)))
    {
        work->fA6C = 1;
        work->fA2C = 60;
        work->f9F8 = 0;

        if (target1->damaged & TARGET_POWER)
        {
            s12a_wolf2_800D0168(work, 6, 2);
        }
        else
        {
            s12a_wolf2_800D0168(work, 14, 2);
        }

        s12a_wolf2_800CF03C(work->adjust, 16);

        work->f748 = 1;
        work->f6FC--;
        work->fA40 -= work->fA48;

        switch(work->f6D4)
        {
        case 0:
        case 2:
        case 6:
        case 10:
        case 16:
            if (work->f6FC <= 0)
            {
                if (GM_GameOverTimer == 0)
                {
                    /* Outdoor ambience */
                    GM_SetSong(0x1000001);
                }

                work->f6D4 = 13;

                DG_InvisiblePrim(work->f7E0);
                DG_InvisiblePrim(work->lsight_prim);

                if (work->fA68 == 0)
                {
                    GM_SeSet2(0, 31, 130);
                }
            }
            else
            {
                work->f6D4 = 12;

                if (GV_RandU(2) != 0)
                {
                    GM_SeSet2(0, 31, 128);
                }
                else
                {
                    GM_SeSet2(0, 31, 129);
                }
            }
            break;
        default:
            if (work->f6FC <= 0)
            {
                if (GM_GameOverTimer == 0)
                {
                    /* Outdoor ambience */
                    GM_SetSong(0x1000001);
                }

                work->f6D4 = 9;

                DG_InvisiblePrim(work->f7E0);
                DG_InvisiblePrim(work->lsight_prim);

                if (work->fA68 == 0)
                {
                    GM_SeSet2(0, 31, 130);
                }
            }
            else
            {
                if (GV_RandU(2) != 0)
                {
                    GM_SeSet2(0, 31, 128);
                }
                else
                {
                    GM_SeSet2(0, 31, 129);
                }

                work->f6D4 = 8;
            }
            break;
        }

        if ((work->f6FC < 1) && (work->f99C != 0))
        {
            GM_FreeObject(&work->body);
            GM_FreeObject(&work->weapon);

            GM_InitObject(&work->body, BODY_DATA, BODY_FLAG, MOTION_DATA);
            GM_ConfigObjectJoint(&work->body);
            GM_ConfigMotionControl(&work->body, &work->m_ctrl, MOTION_DATA, work->m_segs, NULL, &work->control, work->rots);
            GM_ConfigObjectLight(&work->body, work->light);

            GM_InitObject(&work->weapon, WEAPON_DATA, WEAPON_FLAG, 0);
            GM_ConfigObjectLight(&work->weapon, work->light);
            GM_ConfigObjectRoot(&work->weapon, &work->body, 4);

            DG_InvisibleObjs(work->weapon.objs);
        }
    }

    s12a_wolf2_800D078C(work);

    work->f6F0--;
    work->f6F8++;

    if (work->fA2C > 0)
    {
        work->fA2C--;
    }
}

void s12a_wolf2_800D2E0C(Wolf2Work *work)
{
    if (work->f9BC == 1)
    {
        GM_ConfigMotionAdjust(&work->body, work->adjust);
        s12a_wolf2_800CF03C(work->adjust, 16);
        s12a_wolf2_800D0848(work, 9, 11);
        return;
    }

    work->voices[0] = 30;
    work->f6C0 = 26;
    work->f6CC = 0;
    work->f9A8 = 0;
    work->f6F8 = 0;
    work->f6F4 = 0;
    work->f704 = 0;
    work->f708 = 0;
    work->f6E4 = 0;
    work->f748 = 0;
    work->f71C = 0;
    work->f9BC = 0;
    work->f990 = DG_ZeroVector;
    work->f718 = 0;
    work->f9EC = 0;
    work->f9F4 = 0;
    work->f9F8 = 0;
    work->fA08 = 0;
    work->fA04 = 0;
    work->f9CC = 0;
    work->fA0C = 0;
    work->fA10 = DG_ZeroVector;
    *(SVECTOR *)&work->f6AC = DG_ZeroVector;
    work->f6B4 = DG_ZeroVector;
    work->fA28 = 0;
    work->fA2C = 0;
    work->cinema_screen = NULL;
    work->fA50 = 0;
    work->fA54 = 0;
    work->f6D4 = 18;

    GM_ConfigMotionAdjust(&work->body, work->adjust);
    s12a_wolf2_800CF03C(work->adjust, 16);
    s12a_wolf2_800D08D8(work, 0);

    work->f9A4 = 0;
    work->f880 = GV_RandU(4096) % work->f7FC;
    work->f884 = work->f880 + 1;
    if (work->f884 >= work->f7FC)
    {
        work->f884 = work->f880 - 1;
    }

    work->control.mov = work->f888[work->f880];
    work->control.mov.vz -= 1000;

    work->fA70 = 0;
}
