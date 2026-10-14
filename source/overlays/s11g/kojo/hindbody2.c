#include "mgstype.h"
#include "game/game.h"
#include "hind.h"
#include "mts/mts.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "bullet/blast.h"
#include "okajima/blurpure.h"
#include "takabe/cinema.h"
#include "takabe/fadeio.h"
#include "takabe/spark2.h"

void s11g_hind_800D5E44(HindWork *work, int a1);
void s11g_hind_800D5E54(int arg0, SVECTOR *arg1, int se_id);
void s11g_hind_800D619C(HindWork *work, int index);
void s11g_hind_800D61F8(HindWork *work);
void s11g_hind_800D62BC(VECTOR *vec, VECTOR *pos, int len);
void s11g_hind_800D60D8(int arg0, SVECTOR *arg1, int se_id);
void s11g_hind_800D6260(long *vec, long *pos, long *old, int len);
void s11g_hind_800D648C(SVECTOR *a, SVECTOR *b, int len);
void s11g_hind_800D5FB4(HindWork *work, int a1);
void s11g_hind_800D60F0(HindWork *work);
void s11g_hind_800D66F0(HindWork *work);
int  s11g_hind_800D5CD8(SVECTOR *from, SVECTOR *to, SVECTOR *out);
void Function_800D63A4(SVECTOR *vec, SVECTOR *pos, int len);
void s11g_hind_800D6848(HindWork *work);
void s11g_hind_800D7644(HindWork *work);
void AN_Blast_Rand(SVECTOR *pos);
void *NewBlastoff(SVECTOR *arg0, int arg1, int arg2, int *arg3);

extern int amissile_alive_8009F490;

/* Missile demo: the hind is hit by the stinger and crashes */
void s11g_hind_800D6848(HindWork *work)
{
    SVECTOR vec;
    SVECTOR rot;
    VECTOR  pos;
    SVECTOR step;
    SVECTOR rot2;
    SVECTOR step2;
    SVECTOR rot3;
    SVECTOR step3;
    SVECTOR rot4;
    SVECTOR blast;
    int     dist;

    work->target1->damaged |= TARGET_POWER;
    work->target2->damaged |= TARGET_POWER;
    work->target3->damaged |= TARGET_POWER;

    dist = GV_DiffVec3(&work->move_missile_target_pos, &work->move_missile_pos);

    switch (work->field_5C8)
    {
    case 0:
        work->field_5E4 = 150;
        work->field_5C8 = 1;
        /* fallthrough */
    case 1:
        vec.vx = 0;
        vec.vy = 0;
        vec.vz = 4096;

        rot.vx = 0;
        rot.vy = work->control.rot.vy;
        rot.vz = 0;

        DG_SetPos2(&DG_ZeroVector, &rot);
        DG_PutVector(&vec, &vec, 1);

        work->field_60C.vx += vec.vx;
        work->field_60C.vy = 30000;
        work->field_60C.vz += vec.vz;

        pos.vx = 130000;
        pos.vy = 30000;
        pos.vz = 20000;
        s11g_hind_800D62BC(&work->field_60C, &pos, 64);

        work->field_62C = work->field_60C;
        s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 128);

        if (work->field_5E4 < 0)
        {
            work->field_5E4 = 150;
            work->field_5C8 = 2;
            work->field_60C.vx = 130000;
            work->field_60C.vy = 23000;
            work->field_60C.vz = 20000;
        }
        break;

    case 2:
        if (work->field_5E4 < 0)
        {
            work->field_5C8 = 17;
            work->field_5E4 = 90;
            work->field_60C.vy = 23000;
            work->field_60C.vx = 130000;
            work->field_60C.vz = 20000;
        }

        s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 128);
        work->field_62C = work->field_5FC;
        break;

    case 17:
        if (work->field_5E4 > 1)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
        }
        else if (work->field_5E4 > 0)
        {
            work->last_item = GM_Item;
            work->last_weapon = GM_Weapon;

            if (GM_Item == IT_Scope || GM_Item == IT_Camera ||
                GM_Item == IT_NVG || GM_Item == IT_ThermG)
            {
                GM_Item = IT_None;
            }

            if (GM_Weapon == WP_Rifle || GM_Weapon == WP_Stinger)
            {
                GM_Weapon = WP_None;
            }
        }
        else if (GM_Vitality != 0 && GM_GameOverTimer == 0)
        {
            s11g_hind_800D619C(work, 18);
            work->field_8E4 = NewBlurPure();
            GM_GameStatus |= STATE_RADAR_OFF | STATE_MENU_DISABLE | STATE_LIFE_OFF;
            work->field_8E0 = (int)NewCinemaScreen(2000000000, 1);
            work->nMissileDemoMode2 = 11;
            work->field_5C8 = 18;
            work->field_5E4 = 90;
            work->field_60C.vx = 10000;
            work->field_60C.vy = 23000;
            work->field_60C.vz = -8000;
            work->field_5FC = work->field_60C;
            work->field_4BC = work->field_5FC;
        }
        else
        {
            work->nMissileDemoMode2 = 0;
        }
        break;

    case 18:
        work->field_60C.vx = 10000;
        work->field_60C.vy = 23000;
        work->field_60C.vz = -4000;
        work->field_5FC = work->field_60C;
        work->field_4BC = work->field_5FC;

        work->field_62C.vx = gUnkCameraStruct2_800B7868.position.vx;
        work->field_62C.vy = gUnkCameraStruct2_800B7868.position.vy;
        work->field_62C.vz = gUnkCameraStruct2_800B7868.position.vz;
        work->nMissileDemoMode2 = 11;

        work->move_missile_pos_v = work->field_4BC;
        work->move_missile_pos_v.vx += 2000;
        work->move_missile_pos_v.vy -= 4000;
        work->move_missile_pos_v.vz += 4000;
        work->move_missile_rot = work->control.rot;

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 256);
        }
        else
        {
            work->field_60C.vx += 3000;
            work->field_60C.vy += 3000;
            work->field_60C.vz -= 10000;
            GM_SeSet2(0, 63, 42);
            GM_SeSet2(0, 63, 191);
            GM_SeSet2(0, 63, 188);
            work->field_5C8 = 21;
            work->field_5E4 = 70;
        }
        break;

    case 21:
        s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);

        work->field_62C.vx = gUnkCameraStruct2_800B7868.position.vx;
        work->field_62C.vy = gUnkCameraStruct2_800B7868.position.vy;
        work->field_62C.vz = gUnkCameraStruct2_800B7868.position.vz;
        work->nMissileDemoMode2 = 11;

        if (work->field_5E4 > 0)
        {
            step.vx = 0;
            step.vy = 0;
            step.vz = 1000;
            rot2 = work->move_missile_rot;
            DG_SetPos2(&DG_ZeroVector, &rot2);
            DG_PutVector(&step, &step, 1);

            work->move_missile_pos_v.vx += step.vx;
            work->move_missile_pos_v.vy += step.vy;
            work->move_missile_pos_v.vz += step.vz;

            AN_Blast_Mini(&work->move_missile_pos);

            vec = work->move_missile_pos;
            vec.vx += GV_RandS(256);
            vec.vy += GV_RandS(256);
            vec.vz += GV_RandS(256);
            AN_Blast_Mini(&vec);

            s11g_hind_800D5FB4(work, 0);
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 256);
        }
        else
        {
            GM_GameStatus &= ~(STATE_RADAR_OFF | STATE_MENU_DISABLE | STATE_LIFE_OFF);

            if (work->field_8E0)
            {
                NewCinemaScreenClose((void *)work->field_8E0);
                work->field_8E0 = 0;
            }

            if (work->field_8E4)
            {
                GV_DestroyActor(work->field_8E4);
                work->field_8E4 = NULL;
            }

            if (work->last_weapon == WP_Rifle || work->last_weapon == WP_Stinger)
            {
                GM_Weapon = work->last_weapon;
            }

            if (work->last_item == IT_Scope || work->last_item == IT_Camera ||
                work->last_item == IT_NVG || work->last_item == IT_ThermG)
            {
                GM_Item = work->last_item;
            }

            work->field_60C.vx = 130000;
            work->field_60C.vy = 25000;
            work->field_60C.vz = 15000;
            work->nMissileDemoMode2 = 0;
            work->field_5FC = work->field_60C;
            work->field_4BC = work->field_5FC;
            work->field_5C8 = 5;
            work->field_5E4 = 30;
            work->move_missile_pos_v = work->field_4BC;
            work->move_missile_target_pos.vx = 4000;
            work->move_missile_target_pos.vy = 2000;
            work->move_missile_target_pos.vz = 6500;
            work->move_missile_pos_v.vx += 2000;
            work->move_missile_pos_v.vy -= 4000;
            work->move_missile_pos_v.vz += 4000;
            s11g_hind_800D60F0(work);
        }
        break;

    case 5:
        if (work->field_5E4 > 0)
        {
            work->nMissileDemoMode = 1;
            work->move_missile_pos_v = work->field_4BC;
            s11g_hind_800D60F0(work);
        }
        else
        {
            GM_SeSet2(0, 63, 188);
            GM_SeSet2(0, 63, 189);
            work->field_5C8 = 6;
            work->field_5E4 = 120;
            work->field_5E8 = 22;
            work->field_5EC = 22;
        }
        break;

    case 6:
        if (work->field_5E4 > 0)
        {
            if (work->field_5E4 == 117)
            {
                NewBlastoff(&work->move_missile_pos_delay, 70, 0, &work->field_670);
                NewBlastoff(&work->move_missile_pos_delay, 70, 1, &work->field_670);
                NewBlastoff(&work->move_missile_pos_delay, 70, 2, &work->field_670);
                NewBlastoff(&work->move_missile_pos_delay, 70, 3, &work->field_670);
            }

            if (work->field_5EC > 0)
            {
                work->field_5EC--;
            }
            else
            {
                GM_SeSet2(0, 63, 79);

                if (--work->field_5E8 <= 0)
                {
                    work->field_5E8 = 1;
                }

                work->field_5EC = work->field_5E8;
            }

            s11g_hind_800D60F0(work);

            step2.vx = 0;
            step2.vy = 0;
            step2.vz = 1000;
            rot3 = work->move_missile_rot;
            DG_SetPos2(&DG_ZeroVector, &rot3);
            DG_PutVector(&step2, &step2, 1);

            work->move_missile_pos_delay = work->move_missile_pos_blast;
            work->move_missile_pos_blast = work->move_missile_pos;

            work->move_missile_pos_v.vx += step2.vx;
            work->move_missile_pos_v.vy += step2.vy;
            work->move_missile_pos_v.vz += step2.vz;
        }
        else
        {
            GM_SeSet2(0, 63, 79);
            work->field_5C8 = 7;
            work->field_5E4 = 10000;
        }
        break;

    case 7:
        if (dist > 2500)
        {
            GM_SeSet2(0, 63, 79);
            s11g_hind_800D60F0(work);

            step3.vx = 0;
            step3.vy = 0;
            step3.vz = 1000;
            rot4 = work->move_missile_rot;
            DG_SetPos2(&DG_ZeroVector, &rot4);
            DG_PutVector(&step3, &step3, 1);

            work->move_missile_pos_delay = work->move_missile_pos_blast;
            work->move_missile_pos_blast = work->move_missile_pos;

            work->move_missile_pos_v.vx += step3.vx;
            work->move_missile_pos_v.vy += step3.vy;
            work->move_missile_pos_v.vz += step3.vz;
        }
        else
        {
            GM_SetNoise(255, 32, &DG_ZeroVector);

            GM_PadVibration = GV_RandU(2);
            work->field_948 = 255;
            GM_PadVibration2 = 255;
            GM_SeSet2(0, 255, 192);

            work->field_5C8 = 8;
            work->field_5E4 = 50;
            work->move_missile_pos_help2 = work->move_missile_target_pos;
            work->nMissileDemoMode = 2;
            AN_Blast_high(&work->move_missile_pos_help2);

            if (work->field_8EC != -1)
            {
                GCL_ExecProc(work->field_8EC, NULL);
            }
        }
        break;

    case 8:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D60F0(work);

            work->move_missile_pos_help2.vx -= 200;
            blast = work->move_missile_pos_help2;
            blast.vx += GV_RandS(4096);
            blast.vz += GV_RandS(4096);

            if (GV_RandU(2) == 0)
            {
                GM_SeSet2(0, 255, 41);
            }

            if (GV_RandU(8) == 0)
            {
                GM_SeSet2(0, 255, 39);
            }

            if (GV_RandU(16) == 0)
            {
                GM_SeSet2(0, 255, 40);
                GM_SetNoise(255, 32, &DG_ZeroVector);
            }

            AN_Blast_Rand(&blast);

            GM_MoveTarget(&work->field_57C, &work->move_missile_pos_help2);
            GM_PowerTarget(&work->field_57C);

            work->field_948 -= 8;
            if (work->field_948 < 0)
            {
                work->field_948 = GV_RandU(128) + 128;
            }

            GM_PadVibration = GV_RandU(2);
            GM_PadVibration2 = work->field_948;
        }
        else
        {
            work->target1->damaged &= ~TARGET_POWER;
            work->target2->damaged &= ~TARGET_POWER;
            work->target3->damaged &= ~TARGET_POWER;

            work->field_658 = 0;
            work->field_5C4 = 0;
            work->field_5C8 = 0;
        }
        break;
    }
}


static inline int RandBase(int range, int base)
{
    return GV_RandU(range) + base;
}

/* Missile demo 2: the hind is destroyed */
void s11g_hind_800D7644(HindWork *work)
{
    SVECTOR vec;
    SVECTOR spark_rot;
    SVECTOR spark_pos;
    SVECTOR rot;
    SVECTOR cam_rot;
    SVECTOR cam_vec;
    MATRIX  mat;
    VECTOR  pos;
    SVECTOR step;
    SVECTOR rot2;
    SVECTOR step2;
    SVECTOR rot3;
    SVECTOR step3;
    SVECTOR rot4;
    SVECTOR blast;
    int     dist;
    int     swing;

    work->target1->damaged |= TARGET_POWER;
    work->target2->damaged |= TARGET_POWER;
    work->target3->damaged |= TARGET_POWER;

    dist = GV_DiffVec3(&work->move_missile_target_pos, &work->move_missile_pos);

    if (!(GV_Time & 3))
    {
        s11g_hind_800D66F0(work);
    }

    switch (work->field_5C8)
    {
    case 0:
        if (GM_GameOverTimer == 0)
        {
            GM_SetSong(0xFF0000FE);
        }

        work->field_60C.vy = 23000;
        s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);

        if (work->field_5FC.vy < 10000)
        {
            work->field_5C8 = 0;
        }
        else
        {
            work->field_5E4 = 150;
            work->field_5C8 = 1;
            s11g_hind_800D5E54(0, &work->control.mov, 132);
        }
        /* fallthrough */
    case 1:
        vec.vx = 0;
        vec.vy = 0;
        vec.vz = 4096;

        rot.vx = 0;
        rot.vy = work->control.rot.vy;
        rot.vz = 0;

        DG_SetPos2(&DG_ZeroVector, &rot);
        DG_PutVector(&vec, &vec, 1);

        work->field_60C.vx += vec.vx;
        work->field_60C.vy = 30000;
        work->field_60C.vz += vec.vz;

        pos.vx = 100000;
        pos.vy = 30000;
        pos.vz = 25000;
        s11g_hind_800D62BC(&work->field_60C, &pos, 64);

        work->field_62C = work->field_60C;
        s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 128);

        if (work->field_5E4 < 0)
        {
            work->field_5E4 = 150;
            work->field_5C8 = 2;
            work->field_60C.vy = 23000;
            work->field_60C.vx = 100000;
            work->field_60C.vz = 20000;
        }
        break;

    case 2:
        if (work->field_5E4 < 0)
        {
            work->field_5C8 = 17;
            work->field_5E4 = 90;
            work->field_60C.vy = 23000;
            work->field_60C.vx = 100000;
            work->field_60C.vz = 20000;
        }

        s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 128);
        work->field_62C = work->field_5FC;
        break;

    case 17:
        if (work->field_5E4 > 1)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
        }
        else if (work->field_5E4 > 0)
        {
            work->last_item = GM_Item;
            work->last_weapon = GM_Weapon;

            if (GM_Item == IT_Scope || GM_Item == IT_Camera || GM_Item == IT_NVG || GM_Item == IT_ThermG)
            {
                GM_Item = IT_None;
            }

            if (GM_Weapon == WP_Rifle || GM_Weapon == WP_Stinger)
            {
                GM_Weapon = WP_None;
            }
        }
        else if (GM_Vitality != 0 && GM_GameOverTimer == 0)
        {
            s11g_hind_800D619C(work, 18);
            work->field_8E4 = NewBlurPure();
            GM_GameStatus |= STATE_RADAR_OFF | STATE_MENU_DISABLE | STATE_LIFE_OFF;
            work->field_8E0 = (int)NewCinemaScreen(2000000000, 1);
            work->nMissileDemoMode2 = 12;
            work->field_5C8 = 18;
            work->field_5E4 = 90;
            work->field_60C.vx = 10000;
            work->field_60C.vy = 23000;
            work->field_60C.vz = -10000;
            work->field_5FC = work->field_60C;
            work->field_4BC = work->field_5FC;
        }
        else
        {
            work->nMissileDemoMode2 = 0;
        }
        break;

    case 18:
        work->field_60C.vx = 10000;
        work->field_60C.vy = 23000;
        work->field_60C.vz = -14000;
        work->field_5FC = work->field_60C;
        work->field_4BC = work->field_5FC;

        if (!(GV_Time & 15) && GV_RandU(4) == 0)
        {
            spark_rot.vx = GV_RandS(1024);
            spark_rot.vy = GV_RandU(4096);
            spark_rot.vz = 0;
            spark_pos.vx = work->control.mov.vx + GV_RandS(4096);
            spark_pos.vy = work->control.mov.vy - GV_RandU(2048);
            spark_pos.vz = work->control.mov.vz + GV_RandS(4096);
            DG_SetPos2(&spark_pos, &spark_rot);
            ReadRotMatrix(&mat);
            NewSpark2_800CA714(&mat);
        }

        work->nMissileDemoMode2 = 12;

        work->move_missile_pos_v = work->field_4BC;
        work->move_missile_pos_v.vx += 2000;
        work->move_missile_pos_v.vy -= 4000;
        work->move_missile_pos_v.vz -= 4000;
        work->move_missile_rot = work->control.rot;

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 256);
        }
        else
        {
            work->field_60C.vx += 3000;
            work->field_60C.vy += 3000;
            work->field_60C.vz += 10000;
            GM_SeSet2(0, 63, 42);
            GM_SeSet2(0, 63, 191);
            GM_SeSet2(0, 63, 188);
            work->field_5C8 = 21;
            work->field_5E4 = 40;
        }
        break;

    case 21:
        s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);

        if (!(GV_Time & 15) && GV_RandU(4) == 0)
        {
            spark_rot.vx = GV_RandS(1024);
            spark_rot.vy = GV_RandU(4096);
            spark_rot.vz = 0;
            spark_pos.vx = work->control.mov.vx + GV_RandS(4096);
            spark_pos.vy = work->control.mov.vy - GV_RandU(2048);
            spark_pos.vz = work->control.mov.vz + GV_RandS(4096);
            DG_SetPos2(&spark_pos, &spark_rot);
            ReadRotMatrix(&mat);
            NewSpark2_800CA714(&mat);
        }

        work->field_62C.vx = gUnkCameraStruct2_800B7868.position.vx;
        work->field_62C.vy = gUnkCameraStruct2_800B7868.position.vy;
        work->field_62C.vz = gUnkCameraStruct2_800B7868.position.vz;
        work->nMissileDemoMode2 = 12;

        if (work->field_5E4 > 0)
        {
            step.vx = 0;
            step.vy = 0;
            step.vz = 1000;
            rot2 = work->move_missile_rot;
            DG_SetPos2(&DG_ZeroVector, &rot2);
            DG_PutVector(&step, &step, 1);

            work->move_missile_pos_v.vx += step.vx;
            work->move_missile_pos_v.vy += step.vy;
            work->move_missile_pos_v.vz += step.vz;

            AN_Blast_Mini(&work->move_missile_pos);

            vec = work->move_missile_pos;
            vec.vx += GV_RandS(256);
            vec.vy += GV_RandS(256);
            vec.vz += GV_RandS(256);
            AN_Blast_Mini(&vec);

            s11g_hind_800D5FB4(work, 0);
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 256);
        }
        else
        {
            GM_GameStatus &= ~(STATE_RADAR_OFF | STATE_MENU_DISABLE | STATE_LIFE_OFF);

            if (work->field_8E0)
            {
                NewCinemaScreenClose((void *)work->field_8E0);
                work->field_8E0 = 0;
            }

            if (work->field_8E4)
            {
                GV_DestroyActor(work->field_8E4);
                work->field_8E4 = NULL;
            }

            if (work->last_weapon == WP_Rifle || work->last_weapon == WP_Stinger)
            {
                GM_Weapon = work->last_weapon;
            }

            if (work->last_item == IT_Scope || work->last_item == IT_Camera ||
                work->last_item == IT_NVG || work->last_item == IT_ThermG)
            {
                GM_Item = work->last_item;
            }

            work->field_60C.vx = 100000;
            work->field_60C.vy = 25000;
            work->field_60C.vz = 7000;
            work->nMissileDemoMode2 = 0;
            work->field_5FC = work->field_60C;
            work->field_4BC = work->field_5FC;
            work->field_5C8 = 5;
            work->field_5E4 = 30;
            work->move_missile_pos_v = work->field_4BC;
            work->move_missile_target_pos.vx = 5000;
            work->move_missile_target_pos.vy = 500;
            work->move_missile_target_pos.vz = -3000;
            work->move_missile_pos_v.vx += 2000;
            work->move_missile_pos_v.vy -= 4000;
            work->move_missile_pos_v.vz -= 4000;
            s11g_hind_800D60F0(work);
        }
        break;

    case 5:
        if (!(GV_Time & 15) && GV_RandU(4) == 0)
        {
            spark_rot.vx = GV_RandS(1024);
            spark_rot.vy = GV_RandU(4096);
            spark_rot.vz = 0;
            spark_pos.vx = work->control.mov.vx + GV_RandS(4096);
            spark_pos.vy = work->control.mov.vy - GV_RandU(2048);
            spark_pos.vz = work->control.mov.vz + GV_RandS(4096);
            DG_SetPos2(&spark_pos, &spark_rot);
            ReadRotMatrix(&mat);
            NewSpark2_800CA714(&mat);
        }

        if (work->field_5E4 > 0)
        {
            work->nMissileDemoMode = 1;
            work->move_missile_pos_v = work->field_4BC;
            s11g_hind_800D60F0(work);
        }
        else
        {
            GM_SeSet2(0, 63, 188);
            GM_SeSet2(0, 63, 189);
            work->field_5C8 = 6;
            work->field_5E4 = 90;
            work->field_5E8 = 23;
            work->field_5EC = 23;
        }
        break;

    case 6:
        if (work->field_5E4 > 0)
        {
            if (work->field_5E4 == 87)
            {
                NewBlastoff(&work->move_missile_pos_delay, 20, 0, &work->field_670);
                NewBlastoff(&work->move_missile_pos_delay, 20, 1, &work->field_670);
                NewBlastoff(&work->move_missile_pos_delay, 20, 2, &work->field_670);
                NewBlastoff(&work->move_missile_pos_delay, 20, 3, &work->field_670);
            }

            if (work->field_5EC > 0)
            {
                work->field_5EC--;
            }
            else
            {
                GM_SeSet2(0, 63, 79);

                if (--work->field_5E8 <= 0)
                {
                    work->field_5E8 = 1;
                }

                work->field_5EC = work->field_5E8;
            }

            s11g_hind_800D60F0(work);

            step2.vx = 0;
            step2.vy = 0;
            step2.vz = 1000;
            rot3 = work->move_missile_rot;
            DG_SetPos2(&DG_ZeroVector, &rot3);
            DG_PutVector(&step2, &step2, 1);

            work->move_missile_pos_delay = work->move_missile_pos_blast;
            work->move_missile_pos_blast = work->move_missile_pos;

            work->move_missile_pos_v.vx += step2.vx;
            work->move_missile_pos_v.vy += step2.vy;
            work->move_missile_pos_v.vz += step2.vz;
        }
        else
        {
            GM_SeSet2(0, 63, 79);
            work->field_5C8 = 7;
            work->field_5E4 = 10000;
        }
        break;

    case 7:
        if (dist > 3000)
        {
            GM_SeSet2(0, 63, 79);
            s11g_hind_800D60F0(work);

            step3.vx = 0;
            step3.vy = 0;
            step3.vz = 1000;
            rot4 = work->move_missile_rot;
            DG_SetPos2(&DG_ZeroVector, &rot4);
            DG_PutVector(&step3, &step3, 1);

            work->move_missile_pos_delay = work->move_missile_pos_blast;
            work->move_missile_pos_blast = work->move_missile_pos;

            work->move_missile_pos_v.vx += step3.vx;
            work->move_missile_pos_v.vy += step3.vy;
            work->move_missile_pos_v.vz += step3.vz;
        }
        else
        {
            GM_SetNoise(255, 32, &DG_ZeroVector);

            if (GM_GameOverTimer == 0)
            {
                GM_SetSong(0x01000001);
            }

            GM_SeSet2(0, 255, 192);
            work->nMissileDemoMode = 4;
            work->field_5C8 = 8;
            work->field_5E4 = 100;
            work->move_missile_pos_help2 = work->move_missile_target_pos;
            AN_Blast_high(&work->move_missile_pos_help2);
        }
        break;

    case 8:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D60F0(work);

            work->move_missile_pos_help2.vx -= 200;

            blast = work->move_missile_pos_help2;
            blast.vz += (work->field_5E4 - 100) * (swing = ((GV_Time % 2) * 2 - 1) * 150);

            if (GM_GameLevel <= GM_LEVEL_EXTREME)
            {
                if (GM_GameLevel >= GM_LEVEL_HARD && (GM_PlayerPosition.vx >= 0 || GM_PlayerPosition.vz >= -1500))
                {
                    GM_MoveTarget(&work->field_57C, &blast);
                    GM_PowerTarget(&work->field_57C);
                }
            }

            blast.vx += GV_RandS(4096);
            blast.vz += GV_RandS(4096);
            AN_Blast_Rand(&blast);

            blast = work->move_missile_pos_help2;
            blast.vz += (work->field_5E4 - 100) * (swing = ((GV_Time % 2) * 2 - 1) * 60);
            blast.vx += GV_RandS(4096);
            blast.vz += GV_RandS(4096);
            AN_Blast_Rand(&blast);

            if (GV_RandU(2) == 0)
            {
                GM_SeSet2(0, 255, 41);
            }

            if (GV_RandU(8) == 0)
            {
                GM_SeSet2(0, 255, 39);
            }

            if (GV_RandU(16) == 0)
            {
                GM_SeSet2(0, 255, 40);
            }

            if (GM_Vitality == 0 || GM_GameOverTimer != 0)
            {
                work->nMissileDemoMode2 = 0;
                return;
            }

            if (work->field_5E4 == 5)
            {
                blast.vx = 600;
                blast.vy = 500;
                blast.vz = -5300;
                AN_Blast_high(&blast);
            }

            if (work->field_5E4 == 4)
            {
                blast.vx = 260;
                blast.vy = 500;
                blast.vz = -2500;
                AN_Blast_high(&blast);
            }

            if (work->field_5E4 == 2)
            {
                blast.vx = -570;
                blast.vy = 500;
                blast.vz = -3900;
                AN_Blast_high(&blast);
            }

            work->field_948 -= 8;
            if (work->field_948 < 0)
            {
                work->field_948 = GV_RandU(128) + 128;
            }

            GM_PadVibration = GV_RandU(2);
            GM_PadVibration2 = work->field_948;

            if (GM_Vitality != 0 && GM_GameOverTimer == 0 && work->field_5E4 == 80)
            {
                work->move_missile_pos_help2 = work->move_missile_target_pos;
                work->field_8E0 = (int)NewCinemaScreen(2000000000, 1);
                work->nMissileDemoMode2 = 999;
                GM_GameStatus |= STATE_PADRELEASE;
                GM_GameStatus |= STATE_RADAR_OFF | STATE_MENU_DISABLE | STATE_LIFE_OFF | STATE_CUT_IN;

                if (work->field_94C != 1)
                {
                    work->field_8E4 = NewBlurPure();
                }

                work->last_item = GM_Item;
                work->last_weapon = GM_Weapon;

                if (GM_Item == IT_Scope || GM_Item == IT_Camera || GM_Item == IT_NVG || GM_Item == IT_ThermG)
                {
                    GM_Item = IT_None;
                }

                if (GM_Weapon == WP_Rifle || GM_Weapon == WP_Stinger)
                {
                    GM_Weapon = WP_None;
                }

                work->field_60C.vx = 25000;
                work->field_60C.vy = 10000;
                work->field_60C.vz = -2000;
                work->field_5FC = work->field_60C;
                work->field_4BC = work->field_5FC;

                work->field_908.vx = 0;
                work->field_908.vy = 0;
                work->field_908.vz = 0;
                work->field_910 = work->field_908;

                work->field_918.vx = work->field_60C.vx;
                work->field_918.vy = work->field_60C.vy;
                work->field_918.vz = work->field_60C.vz;
                work->field_918.vx -= 1000;
                work->field_918.vy += 3000;
                work->field_918.vz -= 500;
                work->field_920 = work->field_918;

                DG_MakeCameraMatrix(DG_Chanl(0), &work->field_918, &work->field_908, 320);
                GM_Camera.interp_mode = 0;
                gUnkCameraStruct2_800B7868.position = work->field_918;
                gUnkCameraStruct2_800B7868.target = work->field_908;
                s11g_hind_800D619C(work, 9);
            }
            else if (work->field_5E4 < 80)
            {
                work->field_60C.vx = 10000;
                work->field_60C.vy = 10000;
                work->field_60C.vz = -2000;
                work->field_5FC = work->field_60C;
                work->field_4BC = work->field_5FC;

                DG_MakeCameraMatrix(DG_Chanl(0), &work->field_918, &work->field_908, 320);
                GM_Camera.interp_mode = 0;
                gUnkCameraStruct2_800B7868.position = work->field_918;
                gUnkCameraStruct2_800B7868.target = work->field_908;

                if (!(GV_Time & 3))
                {
                    spark_rot.vx = GV_RandS(1024);
                    spark_rot.vy = GV_RandU(4096);
                    spark_rot.vz = 0;
                    spark_pos.vx = work->field_60C.vx + GV_RandU(4096) + 1000;
                    spark_pos.vy = work->field_60C.vy;
                    spark_pos.vz = work->field_60C.vz + GV_RandS(2048);
                    DG_SetPos2(&spark_pos, &spark_rot);
                    ReadRotMatrix(&mat);
                    NewSpark2_800CA714(&mat);
                }
            }
            else
            {
                GM_SetNoise(255, 32, &DG_ZeroVector);
            }
        }
        else if (GM_Vitality != 0 && GM_GameOverTimer == 0)
        {
            work->field_5C8 = 9;
            work->field_5E4 = 150;
            work->field_5E8 = 5;
            work->field_60C.vx = 30000;
            work->field_60C.vy = 13000;
            work->field_60C.vz = -10000;
            work->field_908 = GM_PlayerPosition;
            work->field_918.vx = -11000;
            work->field_918.vy = 5000;
            work->field_918.vz = 6300;
            work->field_910.vx = work->field_4BC.vx;
            work->field_910.vy = work->field_4BC.vy;
            work->field_910.vz = work->field_4BC.vz;
            work->field_920 = work->field_918;

            s11g_hind_800D5CD8(&work->field_918, &work->field_908, &cam_rot);
            cam_vec.vx = 0;
            cam_vec.vy = 4096;
            cam_vec.vz = 0;
            DG_SetPos2(&work->field_918, &cam_rot);
            DG_PutVector(&cam_vec, &cam_vec, 1);
            DG_MakeCameraMatrix(DG_Chanl(0), &work->field_918, &cam_vec, 320);
            GM_Camera.interp_mode = 0;
            gUnkCameraStruct2_800B7868.position = work->field_918;
            gUnkCameraStruct2_800B7868.target = work->field_908;

            if (work->field_8EC != -1)
            {
                GCL_ExecProc(work->field_8EC, NULL);
            }

            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->nMissileDemoMode2 = 0;
            return;
        }
        break;

    case 9:
        if (GM_Vitality == 0 || GM_GameOverTimer != 0)
        {
            work->nMissileDemoMode2 = 0;
            return;
        }

        if (!(GV_Time & 7))
        {
            spark_rot.vx = GV_RandS(1024);
            spark_rot.vy = GV_RandU(4096);
            spark_rot.vz = 0;
            spark_pos.vx = work->field_60C.vx - RandBase(4096, 1000);
            spark_pos.vy = work->field_60C.vy - GV_RandU(2048);
            spark_pos.vz = work->field_60C.vz + GV_RandS(2048);
            DG_SetPos2(&spark_pos, &spark_rot);
            ReadRotMatrix(&mat);
            NewSpark2_800CA714(&mat);
        }

        if (work->field_5E4 > 0)
        {
            work->field_60C.vx = 30000;
            work->field_60C.vy = 13000;
            work->field_60C.vz = -10000;
            work->field_910.vx = work->field_4BC.vx;
            work->field_910.vy = work->field_4BC.vy + 1000;
            work->field_910.vz = work->field_4BC.vz;
            Function_800D63A4(&work->field_908, &work->field_910, 128);

            s11g_hind_800D5CD8(&work->field_918, &work->field_908, &cam_rot);
            cam_vec.vx = 0;
            cam_vec.vy = 6096;
            cam_vec.vz = 0;
            DG_SetPos2(&work->field_918, &cam_rot);
            DG_PutVector(&cam_vec, &cam_vec, 1);
            DG_MakeCameraMatrix(DG_Chanl(0), &work->field_918, &cam_vec, (150 - work->field_5E4) * 4 + 320);
            GM_Camera.interp_mode = 0;
            gUnkCameraStruct2_800B7868.position = work->field_918;
            gUnkCameraStruct2_800B7868.target = work->field_908;
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);

            if (work->field_5E4 == 30)
            {
                work->field_900 = 1;
            }

            if (work->field_5E4 == 50)
            {
                GM_SeSet2(0, 127, 130);
            }
        }
        else
        {
            work->field_60C.vx = 30000;
            work->field_60C.vy = 13000;
            work->field_60C.vz = -10000;
            work->field_910.vx = work->field_4BC.vx;
            work->field_910.vy = work->field_4BC.vy;
            work->field_910.vz = work->field_4BC.vz;
            Function_800D63A4(&work->field_908, &work->field_910, 128);

            s11g_hind_800D5CD8(&work->field_918, &work->field_908, &cam_rot);
            cam_vec.vx = 0;
            cam_vec.vy = 4096;
            cam_vec.vz = 0;
            DG_SetPos2(&work->field_918, &cam_rot);
            DG_PutVector(&cam_vec, &cam_vec, 1);
            DG_MakeCameraMatrix(DG_Chanl(0), &work->field_918, &cam_vec, (150 - work->field_5E4) * 6 + 320);
            GM_Camera.interp_mode = 0;
            gUnkCameraStruct2_800B7868.position = work->field_918;
            gUnkCameraStruct2_800B7868.target = work->field_908;
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);

            work->field_5C8 = 10;
            work->field_5E4 = 30;
            work->field_8E8 = NewFadeInOut(0, 30);
        }
        break;

    case 10:
        if (GM_Vitality == 0 || GM_GameOverTimer != 0)
        {
            work->nMissileDemoMode2 = 0;
            return;
        }

        if (work->field_5E4 > 0)
        {
            work->field_910.vx = work->field_4BC.vx;
            work->field_910.vy = work->field_4BC.vy;
            work->field_910.vz = work->field_4BC.vz;
            Function_800D63A4(&work->field_908, &work->field_910, 128);

            s11g_hind_800D5CD8(&work->field_918, &work->field_908, &cam_rot);
            cam_vec.vx = 0;
            cam_vec.vy = 4096;
            cam_vec.vz = 0;
            DG_SetPos2(&work->field_918, &cam_rot);
            DG_PutVector(&cam_vec, &cam_vec, 1);
            DG_MakeCameraMatrix(DG_Chanl(0), &work->field_918, &cam_vec, 1220);
            GM_Camera.interp_mode = 0;
            gUnkCameraStruct2_800B7868.position = work->field_918;
            gUnkCameraStruct2_800B7868.target = work->field_908;
        }
        else
        {
            GM_GameStatus &= ~STATE_PADRELEASE;
            NewCinemaScreenClose((void *)work->field_8E0);
            work->field_8E0 = 0;

            work->target1->damaged &= ~TARGET_POWER;
            work->target2->damaged &= ~TARGET_POWER;
            work->target3->damaged &= ~TARGET_POWER;

            work->field_658 = 3;
            work->field_5C4 = 0;
            work->field_5C8 = 0;

            if (GM_GameOverTimer == 0)
            {
                GM_SetSong(0xFF0000FE);
            }
        }
        break;
    }

    work->field_60C.vx += rsin(GV_Time * 362) / 4;
    work->field_60C.vy += rsin(GV_Time * 232) / 16;
    work->field_60C.vz += rsin(GV_Time * 292) / 4;
}

void s11g_hind_800D9344(HindWork *work)
{
    VECTOR  sp10;
    SVECTOR sp20;

    switch (work->field_5C8)
    {
    case 0:
        if ((work->field_430 * 7) / 8 < work->field_434)
        {
            s11g_hind_800D5E44(work, (GV_RandU(4096) % 2) + 130);
        }
        else
        {
            switch (work->field_8C4++ % 3)
            {
            case 0:
                s11g_hind_800D619C(work, 25);
                break;
            case 1:
                s11g_hind_800D619C(work, 26);
                break;
            case 2:
                s11g_hind_800D619C(work, 27);
                break;
            }
        }

        work->field_5C8 = 4;
        work->field_5E4 = GV_RandU(8) + 32;
        work->field_8D0 = 1;

        sp20.vx = (GV_RandU(4096) + 10000) * (GV_RandU(2) * 2 - 1);
        sp20.vy = (-1000 - GV_RandU(4096));
        sp20.vz = (GV_RandU(4096) + 10000) * (GV_RandU(2) * 2 - 1);

        work->field_60C.vx += sp20.vx;
        work->field_60C.vy += sp20.vy;
        work->field_60C.vz += sp20.vz;
        work->field_5F4 += GV_RandS(256);
        /* fallthrough */
    case 4:
        if (work->field_5E4 > 0)
        {
            sp10.vx = work->field_60C.vx - work->field_5FC.vx;
            sp10.vz = work->field_60C.vz - work->field_5FC.vz;
            SquareRoot0(sp10.vx * sp10.vx + sp10.vz * sp10.vz);
            s11g_hind_800D62BC(&work->field_60C, &work->field_5FC, 32);
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_5C8 = 5;
            work->field_5E4 = GV_RandU(8) + 32;
            work->field_60C = work->field_4BC;
        }
        break;
    case 5:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 16);
        }
        else
        {
            work->field_64C = 0;

            if (work->field_5C4 == 2)
            {
                work->field_5C8 = 6;
                work->field_5E4 = 0;
            }
            else if (work->field_5CC == 1 && work->field_5D0 == 5)
            {
                work->field_5C4 = work->field_5CC;
                work->field_5C8 = work->field_5D0;
                work->field_5E4 = 5;
            }
            else
            {
                work->field_5C8 = 0;
                work->field_5C4 = work->field_5CC;
            }
        }
        break;
    }
}

void s11g_hind_800D96B0(HindWork *work)
{
    int diff;

    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 4;
        work->field_5E4 = GV_RandU(16) + 30;

        if (work->field_60C.vz < 4000 || work->control.mov.vz < 4000)
        {
            work->field_60C.vy = 10000;
        }
        else
        {
            work->field_60C.vy = (work->field_60C.vy + 13000) / 2;
        }
        /* fallthrough */
    case 4:
        work->field_5D4 = 1;

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 16);
            break;
        }

        work->field_5C8 = 5;
        work->field_5E4 = GV_RandU(16) + 20;
        work->field_5E8 = GV_RandU(2);

        work->field_60C.vx = (rcos(work->field_5F4) * 25000) / 4096 + 9000;
        work->field_60C.vz = (rsin(work->field_5F4) * 25000) / 4096 + 9000;

        if (work->field_60C.vz < 4000 || work->control.mov.vz < 4000)
        {
            work->field_60C.vy = (work->field_60C.vy + 5000) / 2;
        }
        else
        {
            work->field_60C.vy = (work->field_60C.vy + 13000) / 2;
        }

        s11g_hind_800D61F8(work);
        break;

    case 5:
        if (work->field_5E4 < 10)
        {
            work->field_5D4 = 1;
        }

        work->field_62C.vx = GM_PlayerPosition.vx + work->field_664.vx + work->field_65C.vx * work->field_5E4;
        work->field_62C.vy = GM_PlayerPosition.vy + work->field_664.vy + work->field_65C.vy * work->field_5E4;
        work->field_62C.vz = GM_PlayerPosition.vz + work->field_664.vz + work->field_65C.vz * work->field_5E4;

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 40);
        }
        else if (work->field_5E8 > 0)
        {
            work->field_5E8--;
            work->field_5C8 = 5;
            work->field_5E4 = GV_RandU(16) + 40;

            if (GV_RandU(2))
            {
                diff = GV_RandU(64) + 256;
                work->field_5F4 += diff;
            }
            else
            {
                diff = GV_RandU(64) + 256;
                work->field_5F4 -= diff;
            }

            work->field_60C.vx = (rcos(work->field_5F4) * 25000) / 4096;
            work->field_60C.vz = (rsin(work->field_5F4) * 25000) / 4096;

            if (work->field_60C.vz < 4000 || work->control.mov.vz < 4000)
            {
                work->field_60C.vy = (work->field_60C.vy + 8000) / 2;
            }
            else
            {
                work->field_60C.vy = (work->field_60C.vy + 15000) / 2;
            }

            s11g_hind_800D61F8(work);
        }
        else
        {
            work->field_5C8 = 6;
            work->field_5E4 = GV_RandU(16) + 16;
        }
        break;

    case 6:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_8CC = 1;
            work->field_5C8 = 7;
            work->field_5E4 = GV_RandU(32) + 70;
            work->field_5F4 += 2048;
            work->field_60C.vx = (rcos(work->field_5F4) * 25000) / 4096 + 9000;
            work->field_60C.vy = 13000;
            work->field_60C.vz = (rsin(work->field_5F4) * 25000) / 4096 + 9000;
        }
        break;

    case 7:
        work->field_5D4 = 1;

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_5C4 = 1;
            work->field_5C8 = 0;
        }
        break;
    }
}
void s11g_hind_800D9B80(HindWork *work)
{
    int amount;
    int dir;
    int diff;

    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 4;
        work->field_5E4 = 20;
        work->field_60C = work->field_4BC;
        work->field_60C.vy = 10000;
        work->field_5F8 = GV_RandU(2);
        /* fallthrough */
    case 4:
        work->field_5D4 = 1;

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 8);
            break;
        }

        work->field_5F4 &= 0xFFF;

        if (work->field_5F4 > 256 && work->field_5F4 < 1792)
        {
            work->field_5C8 = 4;
            work->field_5E4 = 2;

            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_EASY:
            case GM_LEVEL_NORMAL:
                amount = 8;
                break;
            case GM_LEVEL_HARD:
                amount = 16;
                break;
            case GM_LEVEL_EXTREME:
                amount = 16;
                break;
            }

            work->field_5F4 = (work->field_5F4 < 1024) ? work->field_5F4 - amount : work->field_5F4 + amount;
            work->field_60C.vy = 13000;
        }
        else
        {
            work->field_5C8 = 5;

            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_EASY:
            case GM_LEVEL_NORMAL:
                work->field_5E4 = GV_RandU(32) + 70;
                work->field_5E8 = GV_RandU(4) * 4 + 4;
                break;
            case GM_LEVEL_HARD:
                work->field_5E4 = GV_RandU(16) + 20;
                work->field_5E8 = GV_RandU(2) + 3;
                break;
            case GM_LEVEL_EXTREME:
                work->field_5E4 = GV_RandU(16) + 20;
                work->field_5E8 = GV_RandU(2) + 2;
                break;
            }

            work->field_60C.vy = 13000;
        }

        work->field_60C.vx = rcos(work->field_5F4) * 8;
        work->field_60C.vz = rsin(work->field_5F4) * 8;
        break;

    case 5:
        if (work->field_5E4 > 0)
        {
            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_EASY:
            case GM_LEVEL_NORMAL:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 40);
                break;
            case GM_LEVEL_HARD:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
                break;
            case GM_LEVEL_EXTREME:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
                break;
            }
        }
        else if (work->field_5E8 > 0)
        {
            work->field_5E8--;
            work->field_5C8 = 5;

            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_EASY:
            case GM_LEVEL_NORMAL:
                work->field_5E4 = GV_RandU(32) + 30;
                break;
            case GM_LEVEL_HARD:
                work->field_5E4 = GV_RandU(16) + 20;
                break;
            case GM_LEVEL_EXTREME:
                work->field_5E4 = GV_RandU(16) + 20;
                break;
            }

            if (work->field_5F4 > 256 && work->field_5F4 < 1792)
            {
                if (work->field_5F4 > 1024)
                {
                    work->field_5F8 = 1;
                }
                else
                {
                    work->field_5F8 = 0;
                }

                work->field_5E8 = GV_RandU(4) * 2 + 4;
            }
            else if (work->field_5F4 > 2560 && work->field_5F4 < 3587 && !(GV_Time & 63) && GV_RandU(2) == 0)
            {
                work->field_5E8 = GV_RandU(4) * 2 + 4;
                work->field_5F8 = 1 - work->field_5F8;
            }

            if (work->field_5F8 != 0)
            {
                work->field_5F4 += 256;
            }
            else
            {
                work->field_5F4 -= 256;
            }

            work->field_60C.vx = (rcos(work->field_5F4) * 30000) / 4096;
            work->field_60C.vz = (rsin(work->field_5F4) * 30000) / 4096;
            work->field_60C.vy = (work->field_60C.vy - 15000) / 2;
        }
        else
        {
            work->field_5F4 &= 0xFFF;
            work->field_5E8 = GV_RandU(2);
            work->field_5E4 = GV_RandU(16) + 60;

            if (work->field_5F8 != 0)
            {
                work->field_5F4 += 256;
            }
            else
            {
                work->field_5F4 -= 256;
            }

            work->field_5C8 = 6;
        }
        break;

    case 6:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 16);
            break;
        }

        work->field_8D4 = 1;
        work->field_5C8 = 7;
        work->field_5E4 = GV_RandU(16) + 60;
        dir = work->field_5F4;

        if (work->field_5F8 != 0)
        {
            dir += GV_RandU(256);
        }
        else
        {
            dir -= GV_RandU(256);
        }

        if (work->field_5F4 <= 500 || work->field_5F4 >= 1600)
        {
            work->field_5F4 = dir;
        }

        work->field_60C.vx = (rcos(work->field_5F4) * 20000) / 4096;
        work->field_60C.vy = 10000;
        work->field_60C.vz = (rsin(work->field_5F4) * 20000) / 4096;
        break;

    case 7:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 4);
            break;
        }

        work->field_5C8 = 8;

        switch (GM_GameLevel)
        {
        default:
        case GM_LEVEL_EASY:
        case GM_LEVEL_NORMAL:
            work->field_5E4 = GV_RandU(8) + 32;
            work->field_5E8 = GV_RandU(2) + 2;
            break;
        case GM_LEVEL_HARD:
            work->field_5E4 = GV_RandU(8) + 32;
            work->field_5E8 = GV_RandU(2) + 1;
            break;
        case GM_LEVEL_EXTREME:
            work->field_5E4 = GV_RandU(4) + 32;
            work->field_5E8 = GV_RandU(2) + 1;
            break;
        }

        work->field_60C.vx = (rcos(work->field_5F4) * 25000) / 4096;
        work->field_60C.vz = (rsin(work->field_5F4) * 25000) / 4096;
        work->field_60C.vy = (work->field_60C.vy + 10000) / 2;

        switch (work->field_8C0++ % 4)
        {
        case 1:
            s11g_hind_800D619C(work, 23);
            break;
        case 0:
        case 2:
            s11g_hind_800D5E54(0, &work->field_964, 132);
            break;
        case 3:
            s11g_hind_800D619C(work, 24);
            break;
        }
        break;

    case 8:
        work->field_5D4 = 1;

        if (work->field_5E4 > 0)
        {
            switch (GM_GameLevel)
            {
            default:
            case GM_LEVEL_EASY:
            case GM_LEVEL_NORMAL:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
                break;
            case GM_LEVEL_HARD:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
                break;
            case GM_LEVEL_EXTREME:
                s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
                break;
            }
        }
        else if (work->field_5E8 > 0)
        {
            work->field_5E8--;
            work->field_5C8 = 8;
            work->field_5E4 = GV_RandU(8) + 32;
            work->field_5F8 = GV_RandU(2);

            if (work->field_5F8 != 0)
            {
                diff = GV_RandS(128) - 512;
                work->field_5F4 -= diff;
            }
            else
            {
                diff = GV_RandS(128) - 512;
                work->field_5F4 += diff;
            }

            work->field_60C.vx = (rcos(work->field_5F4) * 25000) / 4096 + 5000;
            work->field_60C.vz = (rsin(work->field_5F4) * 25000) / 4096 + 5000;

            if (work->field_60C.vz < 4000)
            {
                work->field_60C.vy = (work->field_60C.vy + 13000) / 2;
            }
            else
            {
                work->field_60C.vy = (work->field_60C.vy + 10000) / 2;
            }
        }
        else if (work->field_434 < work->field_430 / 5 && GV_RandU(4) < 3)
        {
            work->field_5C8 = 5;
            work->field_5E4 = GV_RandU(32) + 30;
            work->field_5E8 = GV_RandU(4) * 4 + 4;
            work->field_5F4 &= 0xFFF;
            work->field_5F4 = (work->field_5F4 / 512) * 512 + 256;
            work->field_60C.vx = (rcos(work->field_5F4) * 30000) / 4096;
            work->field_60C.vz = (rsin(work->field_5F4) * 30000) / 4096;
            work->field_60C.vy = (work->field_60C.vy + 10000) / 2;
        }
        else
        {
            work->field_5C4 = 2;
            work->field_5C8 = 0;
        }
        break;
    }
}

void s11g_hind_800DA534(HindWork *work)
{
    s11g_hind_800D61F8(work);

    work->field_5C8 = 5;
    work->field_5E4 = 100;
    work->field_5F8 = GV_RandU(2);

    /* turn around: both directions end up at the same angle */
    if (work->field_5F8 != 0)
    {
        work->field_5F4 = (work->field_5F4 + 2048) & 0xFFF;
    }
    else
    {
        work->field_5F4 = (work->field_5F4 - 2048 + 4096) & 0xFFF;
    }

    if (work->field_5F4 > 256 && work->field_5F4 < 1792)
    {
        if (work->field_5F4 < 1024)
        {
            work->field_5F4 = 256;
        }
        else
        {
            work->field_5F4 = 1792;
        }
    }

    work->field_60C.vx = rcos(work->field_5F4) * 43;
    work->field_60C.vy = (work->field_60C.vy + 10000) / 2;
    work->field_60C.vz = rsin(work->field_5F4) * 43;
}

void s11g_hind_800DA614(HindWork *work)
{
    int amount;

    s11g_hind_800D61F8(work);

    work->field_5C8 = 6;
    work->field_5E4 = GV_RandU(8) + 16;

    switch (GM_GameLevel)
    {
    default:
    case GM_LEVEL_EASY:
    case GM_LEVEL_NORMAL:
        if ((work->field_5E8 < 10) && ((work->field_5E8 & 3) == 0))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 64;
        break;
    case GM_LEVEL_HARD:
        if ((work->field_5E8 == 5) || (work->field_5E8 == 10))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 70;
        break;
    case GM_LEVEL_EXTREME:
        if ((work->field_5E8 == 5) || (work->field_5E8 == 10))
        {
            if (GV_RandU(2) == 0)
            {
                work->field_5F8 = 1 - work->field_5F8;
            }
        }

        amount = 72;
        break;
    }

    if (work->field_5F8 != 0)
    {
        work->field_5F4 += amount;
    }
    else
    {
        work->field_5F4 -= amount;
    }

    work->field_60C.vx = rcos(work->field_5F4) * ((work->field_5E8 / 2) + 29);
    work->field_60C.vy = 32000;
    work->field_60C.vz = rsin(work->field_5F4) * ((work->field_5E8 / 2) + 29);
}

void s11g_hind_800DA7C4(HindWork *work)
{
    switch (work->field_5C8)
    {
    case 0:
        work->field_5C8 = 4;
        work->field_5E4 = 0;
        work->field_60C = work->field_4BC;
        work->field_60C.vy = 13000;
        /* fallthrough */
    case 4:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_5C8 = 7;
            work->field_5E4 = 0;
        }
        break;
    case 5:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 128);
            work->field_5D4 = 1;
        }
        else if (((work->field_430 * 2) / 3) < work->field_434)
        {
            if (GV_DiffDirS(work->field_5F4, work->control.turn.vy) > 0)
            {
                work->field_5F8 = 1;
            }
            else
            {
                work->field_5F8 = 0;
            }

            work->field_5E8 = 24;
            s11g_hind_800DA614(work);
        }
        else
        {
            work->field_5C8 = 8;
            work->field_5E4 = GV_RandU(16) + 32;
            work->field_60C.vx = (rcos(work->field_5F4) * 30000) / 4096;
            work->field_60C.vy = 25000;
            work->field_60C.vz = (rsin(work->field_5F4) * 30000) / 4096;
            work->field_5F4 += (GV_RandS(126) + 700) * (GV_RandU(2) * 2 - 1);
            work->field_5F4 &= 0xFFF;
        }
        break;
    case 6:
        if (work->field_5E8 > 9)
        {
            work->field_62C = work->field_60C;
        }

        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 64);
        }
        else if (work->field_5E8 > 0)
        {
            s11g_hind_800DA614(work);
            work->field_5E8--;
        }
        else
        {
            work->field_5C8 = 7;
            work->field_5E4 = 10;
        }
        break;
    case 7:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 32);
        }
        else
        {
            work->field_8CC = 1;
            s11g_hind_800DA534(work);
        }
        break;
    case 8:
        if (work->field_5E4 > 0)
        {
            s11g_hind_800D62BC(&work->field_5FC, &work->field_60C, 128);
        }
        else
        {
            work->field_5C4 = 2;
            work->field_5C8 = 0;
        }
        break;
    }
}
