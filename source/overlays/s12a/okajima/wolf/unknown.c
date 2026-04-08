#include "wolf2.h"

#include "linkvar.h"
#include "game/camera.h"
#include "libgcl/libgcl.h"
#include "okajima/blood.h"
#include "okajima/bullet.h"

static SVECTOR s12a_dword_800C3498 = {0, 0, 100};
static SVECTOR s12a_dword_800C34A0 = {-1024, 0, 0};
static SVECTOR s12a_dword_800C34A8 = {10, -2000, -70};
static SVECTOR s12a_dword_800C34B0 = {10, -800, -120};

extern GM_CAMERA        GM_Camera;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

void *AN_Unknown_800CA1EC( MATRIX* mat, int mark );
void NewAnime_8005E1A0( MATRIX* mat );

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

// jump table padding
const char s12a_dword_800DD150[] = {0x0, 0x0, 0x0, 0x0};

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

#pragma INCLUDE_ASM("asm/overlays/s12a/s12a_wolf2_800CF084.s")

void s12a_wolf2_800CF294(TILE *packs)
{
    int i;

    for (i = 2; i > 0; i--)
    {
        setRGB0(packs, 255, 63, 63);
        packs++;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s12a/s12a_wolf2_800CF2C4.s")

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

#pragma INCLUDE_ASM("asm/overlays/s12a/s12a_wolf2_800D0ED4.s")
void s12a_wolf2_800D0ED4(Wolf2Work *work);

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

#pragma INCLUDE_ASM("asm/overlays/s12a/s12a_wolf2_800D1EBC.s")

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
