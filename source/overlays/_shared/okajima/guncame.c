#include "guncame.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "bullet/blast.h"
#include "game/control.h"
#include "game/game.h"
#include "linkvar.h"
#include "game/object.h"
#include "sd/g_sound.h"

// We came, we saw, GunCame
typedef struct GunCameWork
{
    GV_ACT   actor;
    CONTROL  control;
    OBJECT   field_9C;
    MATRIX   field_180[2];
    MATRIX   world;
    TARGET  *target;
    int      field_1E4;
    int      field_1E8;
    int      field_1EC;
    int      field_1F0;
    OBJECT   field_1F4;
    MATRIX   field_2D8[2];
    SVECTOR  field_318;
    int      field_320;
    int      field_324;
    DG_PRIM *field_328;
    DG_TEX  *field_32C;
    SVECTOR  field_330;
    SVECTOR  field_338;
    int      field_340;
    int      field_344;
    int      field_348;
    int      field_34C;
    int      field_350;
    int      field_354;
    int      field_358;
    int      field_35C;
    int      field_360;
    int      field_364;
    int      field_368;
    int      field_36C;
    int      field_370;
    int      field_374;
    int      map;
    SVECTOR  field_37C[2];
    SVECTOR  field_38C[2];
    int      field_39C;
    int      field_3A0;
    int      field_3A4;
    int      field_3A8;
    SVECTOR  field_3AC[3];
    int      field_3C4;
    int      field_3C8;
    int      field_3CC;
    int      field_3D0;
    int      proc;
    int      field_3D8;
    int      name;
    int      field_3E0;
    int      field_3E4;
    int      field_3E8;
    int      field_3EC;
    int      field_3F0;
    SVECTOR  field_3F4;
    SVECTOR  field_3FC;
    int      field_404;
    int      field_408;
    int      field_40C;
    int      field_410;
    int      field_414;
    int      field_418;
} GunCameWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL4

int s03e_dword_800C32B4 = 0x00000000;
int s03e_dword_800C32B8 = 0x00000000;
int s03e_dword_800C32BC = 0x00000000;

RECT guncame_rect = {80, 80, 160, 160};
SVECTOR guncame_svec = {300, 300, 300, 0};

int SECTION("overlay.bss") s03e_dword_800CC6BC;

extern int     dword_8009F480;
extern int     s03e_dword_800C32B8;
extern int     s03e_dword_800C32B4;
extern SVECTOR guncame_svec;
extern int     s03e_dword_800C32B4;
extern RECT    guncame_rect;
extern int     dword_8009F46C[];
extern int     dword_8009F480;
extern SVECTOR svector_8009F478;
extern int     s03e_dword_800C32BC;

void AN_Unknown_800CA1EC(MATRIX *world, int index);
void AN_Unknown_800D6BCC(SVECTOR *pos, SVECTOR *rot);
void AN_Unknown_800D6EB0(SVECTOR *pos);

void *NewSpark2_800CA714(MATRIX *world);
void *NewBulletEx(int, MATRIX *, int, int, int, int, int, int, int);

// Identical to d03a_red_alrt_800C437C
int GunCame_800C6F60(unsigned short name, int nhashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     hash;
    int     i;

    nmsgs = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; nmsgs > 0; nmsgs--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < nhashes; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

void GunCame_800C6FF8(GunCameWork *work)
{
    SVECTOR svec;

    svec.vx = 0;
    svec.vy = 200;
    svec.vz = 900;

    DG_SetPos2(&work->control.mov, &work->control.rot);
    DG_PutVector(&svec, &svec, 1);
    work->field_338 = svec;
}

void GunCame_800C7068(GunCameWork *work)
{
    work->field_3A0 = 1;
    work->field_3AC[0] = GM_PlayerPosition;

    if (dword_8009F46C[0] == 1)
    {
        work->field_3A4 = dword_8009F46C[0];
        work->field_3AC[1] = svector_8009F478;
    }
    else
    {
        work->field_3AC[1] = GM_PlayerPosition;
        work->field_3A4 = 0;
        dword_8009F480 = 0;
        work->field_3C4 = 0;
    }
}

void GunCame_800C7118(DG_PRIM *prim, DG_TEX *tex, int r, int g, int b)
{
    POLY_FT4 *poly;

    poly = &prim->packs[0]->poly_ft4;
    setRGB0(poly, r, g, b);

    poly = &prim->packs[1]->poly_ft4;
    setRGB0(poly, r, g, b);
}

void GunCame_800C7144(GunCameWork *work, int r, int g, int b)
{
    work->field_3F4.vx = r;
    work->field_3F4.vy = g;
    work->field_3F4.vz = b;
}

int GunCame_800C7154(char *opt, SVECTOR *svec)
{
    int   count;
    char *result;

    count = 0;

    while ((result = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(result, svec);

        svec++;
        count++;
    }

    return count;
}

void GunCame_800C71A8(SVECTOR* arg0, SVECTOR* arg1, SVECTOR* arg2) {

    SVECTOR sp10;
    int temp_s0;

    GV_SubVec3(arg1, arg0, &sp10);

    arg2->vy = (ratan2(sp10.vx, (int) sp10.vz) & 0xFFF);

    temp_s0 = sp10.vy;
    sp10.vy = 0;

    arg2->vx = (short int) ((ratan2(GV_VecLen3(&sp10), (int) temp_s0) & 0xFFF) - 0x400);
}

int GunCame_800C7224(GunCameWork *work)
{
    SVECTOR  ang;
    CONTROL *control;
    int      index;
    int      success;
    int      dx, dy;

    control = &work->control;

    if ((work->field_408 != 0) && (work->field_40C == 0))
    {
        GM_ConfigControlAttribute(&work->control, 0x4F);
        control->radar_atr |= 0x2000;
    }
    else
    {
        GM_ConfigControlAttribute(&work->control, 0x3);
        return 0;
    }

    if (GM_PlayerStatus & PLAYER_INTRUDE)
    {
        return 0;
    }

    index = 0;
    success = 0;

    if ((GM_CurrentItemId != IT_Stealth) || (work->field_3A4 != 0))
    {
        if (GM_CurrentItemId == IT_Stealth)
        {
            index = 1;
        }

        work->field_39C = -1;

        while (!success)
        {
            success = 0;

            GunCame_800C71A8(&work->control.mov, &work->field_3AC[index], &ang);

            dy = GV_DiffDirAbs(ang.vy, work->control.rot.vy);
            dx = GV_DiffDirAbs(ang.vx, work->control.rot.vx);

            if ((work->field_368 >= dx) &&
                (work->field_368 >= dy) &&
                (work->field_364 >= GV_DiffVec3(&work->control.mov, &work->field_3AC[index])) &&
                !HZD_80028454(work->control.map->hzd, &work->control.mov, &work->field_3AC[index], 15, 0))
            {
                success = 1;
                work->field_39C = index;
            }

            if (++index == 3)
            {
                return 0;
            }
        }

        return 1;
    }

    return 0;
}

void GunCame_800C73D0(GunCameWork *work)
{
    MATRIX pos;
    int    f3C4;

    dword_8009F480 = 0;

    GunCame_800C6FF8(work);

    if ((work->field_3C4 == 0) && ((work->field_39C > 0) && (work->field_39C < 3)))
    {
        work->field_3C4 = 1;
        work->field_3C8 = GV_RandU(4096) % work->field_3E4 + work->field_3E0;

        dword_8009F480 = 0;
    }

    f3C4 = work->field_3C4;
    if (f3C4 == 1)
    {
        if ((--work->field_3C8 == 0) && GunCame_800C7224(work))
        {
            dword_8009F480 = f3C4;
        }

        if (work->field_3C8 < 0)
        {
            dword_8009F480 = 0;
            work->field_3C4 = 0;
        }
    }

    DG_SetPos2(&work->field_338, &work->control.rot);
    ReadRotMatrix(&pos);

    if (GM_GameStatus & (STATE_DEMO | STATE_PADDEMO | STATE_PADRELEASE))
    {
        NewBulletEx(256, &pos, 0, 1, 0, 30, 0, work->field_364, 2000);
    }
    else
    {
        switch(GM_DifficultyFlag)
        {
        case DIFFICULTY_VERY_EASY:
        case DIFFICULTY_EASY:
        default:
            NewBulletEx(256, &pos, 0, 1, 0, 30, 80, work->field_364, 2000);
            break;

        case DIFFICULTY_NORMAL:
            NewBulletEx(256, &pos, 0, 1, 0, 30, 120, work->field_364, 2000);
            break;

        case DIFFICULTY_HARD:
            NewBulletEx(256, &pos, 0, 1, 0, 30, 120, work->field_364, 2000);;
            break;

        case DIFFICULTY_EXTREME:
            NewBulletEx(256, &pos, 0, 1, 0, 30, 160, work->field_364, 2000);
            break;
        }
    }

    AN_Unknown_800D6BCC(&work->field_338, &work->control.rot);
}

const SVECTOR s03e_svec_800CC084 = {0, -80, 0, 0};

void GunCame_800C75FC(SVECTOR *svec1, SVECTOR *svec2, GunCameWork *work)
{
    int dir;

    dir = GV_DiffDirS(svec1->vy, svec2->vy);
    if (work->field_36C < dir)
    {
        svec2->vy = (svec1->vy + work->field_36C) & 0xFFF;
    }
    else if (dir < -work->field_36C)
    {
        svec2->vy = (svec1->vy - work->field_36C) & 0xFFF;
    }

    dir = GV_DiffDirS(svec1->vx, svec2->vx);
    if (work->field_36C < dir)
    {
        svec2->vx = (svec1->vx + work->field_36C) & 0xFFF;
    }
    else if (dir < -work->field_36C)
    {
        svec2->vx = (svec1->vx - work->field_36C) & 0xFFF;
    }
}

void GunCame_800C76E8(GunCameWork* work)
{
    GunCame_800C71A8(&work->control.mov, &work->field_3AC[work->field_39C], &work->control.turn);
    GunCame_800C75FC(&work->field_330, &work->control.turn, work);
}

int GunCame_800C7740(GunCameWork *work)
{
    SVECTOR *vec;

    if (work->field_34C > 60)
    {
        if (work->field_404 != 0)
        {
            GM_SeSet(&work->control.mov, SE_CAMERA_SCAN);
        }

        vec = &work->control.turn;
        vec->vy = (vec->vy + 8) & 0xFFF;

        if (work->field_36C < GV_DiffDirAbs(work->field_330.vy, vec->vy))
        {
            return 1;
        }
    }
    work->field_34C++;
    return 0;
}

int GunCame_800C77D4(GunCameWork *work)
{
    SVECTOR *vec;

    if (work->field_34C > 60)
    {
        if (work->field_404 != 0)
        {
            GM_SeSet(&work->control.mov, SE_CAMERA_SCAN);
        }

        vec = &work->control.turn;
        vec->vy = (vec->vy - 8) & 0xFFF;

        if (work->field_36C < GV_DiffDirAbs(work->field_330.vy, vec->vy))
        {
            return 1;
        }
    }
    work->field_34C++;
    return 0;
}

int GunCame_800C7868(GunCameWork *work)
{
    SVECTOR *svec1, *svec2;
    int      dir;

    svec1 = &work->field_330;
    svec2 = &work->control.turn;

    dir = GV_DiffDirS(svec1->vy, svec2->vy);
    if (dir < -0xA)
    {
        svec2->vy += 8;
    }
    else if (dir < 0xA)
    {
        svec2->vy = svec1->vy;
    }
    else
    {
        svec2->vy -= 8;
    }

    dir = GV_DiffDirS(svec1->vx, svec2->vx);
    if (dir < -0xA)
    {
        svec2->vx += 8;
    }
    else if (dir < 0xA)
    {
        svec2->vx = svec1->vx;
    }
    else
    {
        svec2->vx -= 8;
    }

    if (svec2->vx != svec1->vx || svec2->vy != svec1->vy || work->field_34C < 0x91)
    {
        work->field_34C++;
        return 0;
    }

    return 1;
}

void GunCame_800C7994(GunCameWork *work)
{
    switch (work->field_344)
    {
    case 2:
        if (GunCame_800C7740(work))
        {
            work->field_344 = 3;
            work->field_34C = GV_RandU(32);
            work->control.turn.vy = work->field_330.vy + work->field_36C;
        }
        break;

    case 3:
        if (GunCame_800C77D4(work))
        {
            work->field_344 = 2;
            work->field_34C = GV_RandU(32);
            work->control.turn.vy = work->field_330.vy - work->field_36C;
        }
        break;

    case 4:
    case 5:
        break;
    }

    if ((((GV_Time + work->field_414) & 3) == 0) && GunCame_800C7224(work))
    {
        AN_Unknown_800CA1EC(&work->field_9C.objs->objs[0].world, 0);

        if (s03e_dword_800CC6BC <= 0)
        {
            s03e_dword_800CC6BC = 90;

            if (work->field_404 != 0)
            {
                GM_SeSet2(0, 63, SE_EXCLAMATION);
            }
        }

        work->field_340 = 1;
        work->field_344 = 5;
        work->field_34C = 0;

        GunCame_800C7144(work, 0xFF, 0, 0);

        work->field_3EC = 10;
    }
}

void GunCame_800C7AD8(GunCameWork *work)
{
    switch (work->field_344)
    {
    case 5:
        GunCame_800C76E8(work);
        work->field_348++;
        if (!(work->field_348 & 3))
        {
            if (work->field_354 < work->field_370)
            {
                work->field_354++;
                GunCame_800C73D0(work);
                if (work->field_404 != 0)
                {
                    GM_SeSetMode(&work->control.mov, SE_GUNCAM_SHOT, GM_SEMODE_BOMB);
                }
                work->field_350 = 1;
            }
            else
            {
                work->field_358++;
                if (work->field_358 >= work->field_374)
                {
                    work->field_354 = 0;
                    work->field_358 = 0;
                }
            }
        }
        else
        {
            work->field_350 = 0;
        }
        if (GunCame_800C7224(work) == 0)
        {
            work->field_344 = 1;
            work->field_34C = 0;
            break;
        }
        break;
    case 1:
        work->field_350 = 0;
        work->field_34C++;
        if (work->field_34C >= 0x5B)
        {
            work->field_340 = 2;
            work->field_344 = 6;
            work->field_34C = 0;
            break;
        }
        if (GunCame_800C7224(work) != 0)
        {
            work->field_344 = 5;
        }
        break;
    }
}

void GunCame_800C7C0C(GunCameWork *work)
{
    switch (work->field_344)
    {
    case 6:
        work->field_344 = 7;
        break;
    case 7:
        if (GunCame_800C7868(work) != 0)
        {
            work->field_340 = 0;
            if (work->field_360 == 1)
            {
                if (GV_RandU(2U) == 0)
                {
                    work->field_344 = 3;
                }
                else
                {
                    work->field_344 = 2;
                }
            }
            else
            {
                work->field_344 = 4;
            }
            work->field_34C = 0;
            GunCame_800C7144(work, 0, 0xFF, 0);
        }
        break;
    }

    if (GunCame_800C7224(work) != 0)
    {
        work->field_340 = 1;
        work->field_344 = 5;
        work->field_34C = 0;
        GunCame_800C7144(work, 0xFF, 0, 0);
    }
}

void GunCame_800C7CE0(GunCameWork *work)
{
    int time;
    int tx, ty;

    switch (work->field_344)
    {
    case 0:
        work->field_344 = 7;
        /* fallthrough */

    case 7:
        time = work->field_3D0 + GV_Time;

        if ((GV_RandU(16) == 0) && (work->field_404 != 0))
        {
            GM_SeSet(&work->control.mov, SE_CAMERA_JAMMED);
        }

        if (GM_GameStatus & STATE_CHAFF) // chaff active
        {
            ty = rsin(time * 64) - rsin(time * 31) / 2 - rsin(time * 231) / 2;
            work->control.turn.vy += ty / 16;

            tx = rsin(time * 23) - rsin(time * 45) / 2 - rsin(time * 245) / 2;
            work->control.turn.vx += tx / 16;

            work->control.turn.vx &= 0xFFF;
            work->control.turn.vy &= 0xFFF;

            GunCame_800C75FC(&work->field_330, &work->control.turn, work);

            // Each macro expansion calls rsin three times
            work->field_3FC.vx = ABS(rsin(time * 95) / 16);
            work->field_3FC.vy = ABS(rsin(time * 154) / 16);
            work->field_3FC.vz = ABS(rsin(time * 43) / 16);

            GunCame_800C7144(work, work->field_3FC.vx, work->field_3FC.vy, work->field_3FC.vz);
        }
        else
        {
            GunCame_800C7144(work, 0, 255, 0);

            work->field_3D0 = -1;
            work->field_340 = 2;
            work->field_344 = 6;
            work->field_34C = 0;
        }
        break;
    }
}

void GunCame_800C8024(GunCameWork *work)
{
    work->control.radar_cone.dir = work->control.rot.vy;
}

void GunCame_800C8030(GunCameWork *work)
{
    switch (work->field_340)
    {
    case 0:
        GM_ConfigControlInterp(&work->control, 4);
        GunCame_800C7994(work);
        break;
    case 1:
        GM_ConfigControlInterp(&work->control, 0);
        GunCame_800C7AD8(work);
        break;
    case 2:
        GM_ConfigControlInterp(&work->control, 4);
        GunCame_800C7C0C(work);
        break;
    case 3:
        GM_ConfigControlInterp(&work->control, 4);
        GunCame_800C7CE0(work);
        break;
    }
}

void GunCame_Act_800C80F4(GunCameWork *work)
{
    MATRIX         world;
    SVECTOR        rot;
    SVECTOR        disp_world;
    SVECTOR        mov;
    SVECTOR        disp_local;
    unsigned short hashes[7];
    int            found;
    CONTROL       *control;
    int            flags;
    TARGET        *target;
    int            i;

    disp_local = s03e_svec_800CC084;

    if (s03e_dword_800CC6BC > 0)
    {
        s03e_dword_800CC6BC--;
    }

    hashes[0] = GV_StrCode("kill");
    hashes[1] = GV_StrCode("音入れる");
    hashes[2] = GV_StrCode("音切る");
    hashes[3] = GV_StrCode("視力戻す");
    hashes[4] = GV_StrCode("視力無くす");
    hashes[5] = GV_StrCode("処理再開");
    hashes[6] = GV_StrCode("処理停止");

    found = GunCame_800C6F60(work->name, 7, hashes);
    switch(found)
    {
    case 0:
        GV_DestroyActor(&work->actor);
        break;

    case 1:
        work->field_404 = 1;
        break;

    case 2:
        work->field_404 = 0;
        break;

    case 3:
        work->field_408 = 1;
        break;

    case 4:
        work->field_408 = 0;
        break;

    case 5:
        work->field_410 = 0;
        break;

    case 6:
        work->field_410 = 1;
        break;
    }

    control = &work->control;

    if (((work->map & GM_PlayerMap) == 0) || (work->field_410 != 0))
    {
        DG_InvisibleObjs(work->field_9C.objs);
        DG_InvisibleObjs(work->field_1F4.objs);
        DG_InvisiblePrim(work->field_328);

        if (work->field_40C == 1)
        {
            return;
        }

        work->field_40C = 1;
    }
    else
    {
        work->field_40C = 0;

        DG_VisibleObjs(work->field_9C.objs);
        DG_VisibleObjs(work->field_1F4.objs);
        DG_VisiblePrim(work->field_328);
    }

    GM_CurrentMap = work->map;

    work->field_3FC.vx = (work->field_3FC.vx * 15 + work->field_3F4.vx) / 16;
    work->field_3FC.vy = (work->field_3FC.vy * 15 + work->field_3F4.vy) / 16;
    work->field_3FC.vz = (work->field_3FC.vz * 15 + work->field_3F4.vz) / 16;

    GunCame_800C7118(work->field_328, work->field_32C, work->field_3FC.vx, work->field_3FC.vy, work->field_3FC.vz);
    GunCame_800C7068(work);

    if (work->field_3EC > 0)
    {
        GM_PadVibration = 1;
        GM_PadVibration2 = 255;
        work->field_3EC--;
    }
    else
    {
        work->field_3EC = 0;
    }

    if ((work->field_3A4 == 1) || (work->field_3A8 == 1))
    {
        work->field_3CC = 60;
    }

    if (work->field_3CC >= 1)
    {
        work->field_3CC--;

        if (work->field_3E8 != 0)
        {
            flags = work->target->class & ~(TARGET_SEEK | TARGET_POWER | TARGET_AVAIL);
            work->target->class = flags | TARGET_AVAIL;
        }
    }
    else
    {
        work->target->class |= TARGET_SEEK | TARGET_POWER | TARGET_AVAIL;
    }

    if (work->field_40C == 0)
    {
        if (((GM_GameStatus & STATE_CHAFF) != 0) && (work->field_3D0 == -1))
        {
            work->field_3D0 = GV_RandU(4096);
            work->field_340 = 3;
            work->field_344 = 0;
            work->field_34C = 0;
        }
    }
    else
    {
        GunCame_800C7144(work, 0, 255, 0);

        work->field_3D0 = -1;
        work->field_340 = 2;
        work->field_344 = 6;
        work->field_34C = 0;
    }

    if (work->field_35C == 0)
    {
        if (work->field_350 == 1)
        {
            rot = control->rot;
            rot.vx -= 1024;

            RotMatrixYXZ_gte(&rot, &world);
            ApplyMatrixSV(&world, &disp_local, &disp_world);

            mov = control->mov;

            control->mov.vx -= disp_world.vx;
            control->mov.vy -= disp_world.vy;
            control->mov.vz -= disp_world.vz;

            GM_ActControl(control);

            control->mov = mov;
        }
        else
        {
            GM_ActControl(control);
        }

        if (GM_CurrentItemId == IT_ThermG)
        {
            work->field_3D8 = 1;

            DG_AmbientObjs(work->field_9C.objs);
            DG_AmbientObjs(work->field_1F4.objs);

            DG_GetLightMatrix2(&control->mov, work->field_180);
            DG_GetLightMatrix2(&control->mov, work->field_2D8);
        }
        else if (work->field_3D8 == 1)
        {
            work->field_3D8 = 0;

            DG_UnAmbientObjs(work->field_9C.objs);
            DG_UnAmbientObjs(work->field_1F4.objs);

            DG_GetLightMatrix(&control->mov, work->field_180);
            DG_GetLightMatrix(&control->mov, work->field_2D8);
        }

        GM_ActObject2(&work->field_9C);

        DG_PutPrim(&work->field_328->world);
        DG_SetPos(&work->world);

        GM_ActObject2(&work->field_1F4);

        target = work->target;

        GM_MoveTarget(target, &control->mov);

        if (target->damaged & TARGET_POWER)
        {
            if (target->a_mode != 2)
            {
                target->field_28 = 0;
                target->damaged = 0;
            }
            else if (s03e_dword_800C32B8 == 0)
            {
                s03e_dword_800C32B8 = 1;
                s03e_dword_800C32BC++;

                if (work->field_404 != 0)
                {
                    GM_SeSet(&control->mov, SE_SPARKS);
                }

                work->field_35C = 1;

                AN_Blast_Minimini(&control->mov);

                for (i = 0; i < 2; i++)
                {
                    rot.vz = 0;

                    disp_world.vx = GV_RandS(128);
                    disp_world.vy = GV_RandU(256) + 32;
                    disp_world.vz = 0;

                    rot.vx = GV_RandU(256) + 64;
                    rot.vy = control->rot.vy + GV_RandS(512);

                    RotMatrixYXZ_gte(&rot, &world);
                    ApplyMatrixSV(&world, &disp_world, &work->field_37C[i]);

                    work->field_38C[i] = control->mov;
                }
            }
        }
    }
    else
    {
        if (++work->field_35C == 19)
        {
            rot.vx = GV_RandU(1024);
            rot.vy = GV_RandU(2048);
            rot.vz = 0;

            DG_SetPos2(&control->mov, &rot);
            ReadRotMatrix(&world);

            NewSpark2_800CA714(&world);
        }

        DG_InvisibleObjs(work->field_9C.objs);
        DG_InvisibleObjs(work->field_1F4.objs);

        GunCame_800C7144(work, 0, 0, 0);

        if ((work->field_35C >= 20) || ((s03e_dword_800C32BC & 0x1) == 0))
        {
            if (work->proc != -1)
            {
                GCL_ExecProc(work->proc, 0);
            }

            GV_DestroyActor(&work->actor);
        }
        else
        {
            for (i = 0; i < 2; i++)
            {
                work->field_37C[i].vy -= 15;

                work->field_38C[i].vx += work->field_37C[i].vx;
                work->field_38C[i].vy += work->field_37C[i].vy;
                work->field_38C[i].vz += work->field_37C[i].vz;

                AN_Unknown_800D6EB0(&work->field_38C[i]);
            }
        }
    }

    GunCame_800C8024(work);
    GunCame_800C8030(work);
}

void GunCame_800C8940(GunCameWork *work)
{
    CONTROL    *control;
    RADAR_CONE *cone;

    control = &work->control;
    control->radar_atr |= 0x2000;

    cone = &work->control.radar_cone;
    cone->dir = 0;
    cone->len = work->field_364;
    cone->ang = work->field_368 * 2;
    cone->_pad = 0;
}

const SVECTOR s03e_svec_800CC0F4 = {0, -150, -400, 0};

int GunCame_800C8978(GunCameWork *work, int name, int map)
{
    SVECTOR disp_local;
    SVECTOR pos;
    SVECTOR dir;
    SVECTOR disp_world;
    MATRIX  rot;
    char   *opt;
    char   *param;

    disp_world = s03e_svec_800CC0F4;

    opt = GCL_GetOption('m');
    if (opt != NULL)
    {
        work->field_360 = GCL_StrToInt(opt);
        if (work->field_360 != 1)
        {
            work->field_360 = 0;
        }
    }
    else
    {
        work->field_360 = 0;
    }

    opt = GCL_GetOption('l');
    if (opt != NULL)
    {
        work->field_364 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_364 = 0xFFFF;
    }

    opt = GCL_GetOption('w');
    if (opt != NULL)
    {
        work->field_368 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_368 = 512;
    }

    opt = GCL_GetOption('p');
    if (opt != NULL)
    {
        GunCame_800C7154(opt, &pos);
    }
    else
    {
        pos = DG_ZeroVector;
    }

    opt = GCL_GetOption('d');
    if (opt != NULL)
    {
        GunCame_800C7154(opt, &dir);
    }
    else
    {
        dir = DG_ZeroVector;
    }

    work->control.mov = pos;
    work->control.turn = dir;

    RotMatrixYXZ_gte(&dir, &rot);
    ApplyMatrixSV(&rot, &disp_world, &disp_local);

    work->control.mov.vx -= disp_local.vx;
    work->control.mov.vy -= disp_local.vy;
    work->control.mov.vz -= disp_local.vz;

    DG_SetPos2(&pos, &dir);
    ReadRotMatrix(&work->world);

    opt = GCL_GetOption('r');
    if (opt != NULL)
    {
        GunCame_800C7154(opt, &pos);
        work->control.turn.vx += pos.vx;
        work->control.turn.vy += pos.vy;
    }

    work->control.rot = work->control.turn;
    work->field_330 = work->control.turn;

    opt = GCL_GetOption('x');
    if (opt != NULL)
    {
        work->field_36C = GCL_StrToInt(opt);
    }
    else
    {
        work->field_36C = 512;
    }

    opt = GCL_GetOption('g');
    if (opt != NULL)
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_370 = GCL_StrToInt(param);
        }

        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_374 = GCL_StrToInt(param);
        }
    }
    else
    {
        work->field_370 = 1;
        work->field_374 = 30;
    }

    opt = GCL_GetOption('v');
    if (opt != NULL)
    {
        work->field_418 = 1;
    }
    else
    {
        work->field_418 = 0;
    }

    work->field_340 = 0;

    if (work->field_360 == 1)
    {
        if ((work->field_418 == 0) && (GV_RandU(2) == 0))
        {
            work->field_344 = 3;
        }
        else
        {
            work->field_344 = 2;
        }
    }
    else
    {
        work->field_344 = 4;
    }

    work->field_3F4.vx = 0;
    work->field_3F4.vy = 255;
    work->field_3F4.vz = 0;

    opt = GCL_GetOption('n');
    if (opt != NULL)
    {
        work->field_3F0 = 0;
        GM_ConfigControlAttribute(&work->control, 0x3);
    }
    else
    {
        work->field_3F0 = 1;
        GM_ConfigControlAttribute(&work->control, 0x47);
        GunCame_800C8940(work);
    }

    opt = GCL_GetOption('o');
    if (opt != NULL)
    {
        work->field_3E8 = 1;
    }
    else
    {
        work->field_3E8 = 0;
    }

    work->field_348 = 0;
    work->field_34C = 0;
    work->field_354 = 0;
    work->field_358 = 0;
    work->field_35C = 0;
    work->field_3C4 = 0;
    work->field_3C8 = 0;
    work->field_3CC = 0;
    work->field_3D0 = -1;
    work->field_3D8 = 0;
    work->field_3EC = 0;

    opt = GCL_GetOption('e');
    if (opt != NULL)
    {
        work->proc = GCL_StrToInt(opt);
    }
    else
    {
        work->proc = -1;
    }

    opt = GCL_GetOption('a');
    if (opt != NULL)
    {
        work->field_3E0 = GCL_StrToInt(opt);
        if (work->field_3E0 < 2)
        {
            work->field_3E0 = 2;
        }
    }
    else
    {
        work->field_3E0 = 2;
    }

    opt = GCL_GetOption('b');
    if (opt != NULL)
    {
        work->field_3E4 = GCL_StrToInt(opt);
        if (work->field_3E4 < 2)
        {
            work->field_3E4 = 2;
        }
    }
    else
    {
        work->field_3E4 = 2;
    }

    return 0;
}

void GunCame_800C8E04(POLY_FT4 *poly, DG_TEX *tex, int col)
{
    char height;
    char width;
    unsigned char x_offset;
    unsigned char y_offset;

    setPolyFT4(poly);
    setRGB0(poly, col, col, col);
    setSemiTrans(poly, 1);

    x_offset = tex->off_x;
    width = x_offset + tex->w;

    y_offset = tex->off_y;
    height = y_offset + tex->h;

    poly->u0 = x_offset;
    poly->v0 = y_offset;
    poly->u1 = width;
    poly->v1 = y_offset;
    poly->u2 = x_offset;
    poly->v2 = height;
    poly->u3 = width;
    poly->v3 = height;

    poly->tpage = tex->tpage;
    poly->clut = (unsigned short) tex->clut;
}

int GunCame_800C8E7C(GunCameWork *work)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->field_318.vx = -90;
    work->field_318.vy = 300;
    work->field_318.vz = 350;
    prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, 0, &work->field_318, &guncame_rect);
    work->field_328 = prim;
    if (prim != NULL)
    {
        prim->field_2E_k500 = 500;
        tex = DG_GetTexture(GV_StrCode("camera_l"));
        work->field_32C = tex;
        if (tex != 0)
        {
            GunCame_800C8E04(&prim->packs[0]->poly_ft4, tex, 128);
            GunCame_800C8E04(&prim->packs[1]->poly_ft4, tex, 100);
            return 0;
        }
    }
    return -1;
}

int GunCame_GetResources_800C8F64(GunCameWork *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *obj1, *obj2;

    control = &work->control;
    work->field_404 = 1;
    work->field_408 = 1;
    work->name = name;

    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlAttribute(control, 7);
    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 4);
    work->control.step = DG_ZeroVector;

    obj1 = &work->field_9C;
    do {} while (0);
    GM_InitObject(obj1, GV_StrCode("gca_gun"), 0x26D, 0);
    GM_ConfigObjectLight(obj1, work->field_180);

    obj2 = &work->field_1F4;
    do {} while (0);
    GM_InitObject(obj2, GV_StrCode("gca_arm"), 0x26D, 0);
    GM_ConfigObjectLight(obj2, work->field_2D8);

    if (GunCame_800C8E7C(work) == -1)
    {
        return -1;
    }

    work->target = GM_AllocTarget();
    if (work->target)
    {
        GM_SetTarget(work->target, 0x15, 2, &guncame_svec);
        GunCame_800C8978(work, name, where);
        DG_GetLightMatrix(&control->mov, work->field_180);
        DG_GetLightMatrix(&control->mov, work->field_2D8);
        s03e_dword_800CC6BC = 0;
        work->field_40C = 0;
        work->field_410 = 0;
        work->field_414 = s03e_dword_800C32B4;
        return 0;
    }

    return -1;
}

void GunCame_Die_800C911C(GunCameWork *work)
{
    s03e_dword_800C32B8 = 0;
    dword_8009F480 = 0;
    GM_FreeObject(&work->field_9C);
    GM_FreeObject(&work->field_1F4);
    GM_FreeTarget(work->target);
    GM_FreeControl(&work->control);
    GM_FreePrim(work->field_328);
}

void *NewGunCame_800C9190(int name, int where, int argc, char **argv)
{
    GunCameWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(GunCameWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, GunCame_Act_800C80F4, GunCame_Die_800C911C, "guncame.c");
        if (GunCame_GetResources_800C8F64(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->map = where;
        s03e_dword_800C32B4++;
    }
    return (void *)work;
}
