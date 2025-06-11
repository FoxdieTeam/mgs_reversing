#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "menu/menuman.h"
#include "chara/snake/sna_init.h"
#include "thing/sgtrect3.h"
#include "thing/sight.h"

extern int              amissile_alive_8009F490;
extern SVECTOR          svector_8009F494;
extern short            N_ChanlPerfMax;
extern GV_PAD           GV_PadData_800B05C0[4];
extern unsigned short   gOldRootCnt_800B1DC8[];
extern TARGET          *target_800BDF00;

/*---------------------------------------------------------------------------*/
// clang-format off
// TODO: check if these are used elsewhere and move to an appropriate header.

// Similar to the "Set Primitive Screen Points" macros in libgpu.h
// but breaks from SCE's naming convention where
//
//      setXY0() modifies only (p)->x0 and (p)->y0
//      setXY2() modifies 2 dimensions (x0/y0, x1/y1)
//      setXY3() modifies 3 dimensions (x0/y0, x1/y1, x2/y2)
//      setXY4() modifies 4 dimensions (x0/y0, x1/y1, x2/y2, x3/y3)
//
// Our addXY#() macros only operate on one dimension, with the number
// indicating which fields are accessed.
//
//      addXY0() modifies (p)->x0 and (p)->y0
//      addXY1() modifies (p)->x1 and (p)->y1
//      and so on...

#define addXY0(p,_x0,_y0)                                               \
        (p)->x0 += (_x0), (p)->y0 += (_y0)

#define addXY1(p,_x1,_y1)                                               \
        (p)->x1 += (_x1), (p)->y1 += (_y1)

#define addXY2(p,_x2,_y2)                                               \
        (p)->x2 += (_x2), (p)->y2 += (_y2)

#define addXY3(p,_x3,_y3)                                               \
        (p)->x3 += (_x3), (p)->y3 += (_y3)

// clang-format on
/*---------------------------------------------------------------------------*/
// Stinger Sight

#define EXEC_LEVEL GV_ACTOR_AFTER2

typedef struct _Work
{
    GV_ACT      actor;
    CONTROL    *control;
    GV_PAD     *pad_data;
    LINE_F4    *field_28_lines_2Array[2];
    LINE_F4    *field_30_lines_2Array[2];
    LINE_F4    *field_38_lines_2Array[2];
    LINE_F4    *field_40_lines_2Array[2];
    TILE_1     *field_48_tiles_2Array[2];
    POLY_G4    *field_50_polys_2Array[2];
    int         delay;      //'delay' in the leaks, but they must mean deltay
    int         deltax;
    DVECTOR     pos[9];
    int         field_84_4Array[4];
    int         field_94;
} Work;

STATIC short word_800AB8EC = 0;

/*---------------------------------------------------------------------------*/

STATIC void addPrimEX( u_long *ot, void *prim )
{
    if (!(GM_PlayerStatus & PLAYER_NOT_SIGHT))
    {
        addPrim(ot, prim);
    }
}

STATIC void stnsight_act_helper_8006837C( Work *work )
{
    int iVar1;

    if (!target_800BDF00)
    {
        work->field_84_4Array[1] = 0;
        return;
    }

    iVar1 = work->field_84_4Array[1]++;

    if ((GM_PlayerStatus & PLAYER_NOT_SIGHT) != 0)
    {
        return;
    }

    if (((iVar1 / 8) & 1) != 0)
    {
        return;
    }

    MENU_Color(0x2e, 0x41, 0x41);
    MENU_Locate(0xb4, 0x10, 0);
    MENU_Printf("LOCK_ON\n");
    menu_Text_Init_80038B98();
}

STATIC void stnsight_act_helper_80068420( Work *work, u_long *ot )
{
    u_short  pad_status;
    LINE_F4 *lines;
    LINE_F4 *lines2;
    TILE_1  *tiles;
    int      deltay;

    int v3; // $a2
    int v4; // $a1
    int v5; // $v1
    int v6; // $s4
    int v7; // $s3

    pad_status = work->pad_data->status;
    GM_CheckShukanReverse(&pad_status);

    if (GV_PauseLevel || ((GM_PlayerStatus & PLAYER_PAD_OFF) != 0))
    {
        pad_status = 0;
    }

    v3 = -work->control->turn.vx;
    v4 = 5 * (v3 / 32 / 5);
    v5 = 16 * (v3 / 32 % 5) / 5 + 112;

    while (v5 >= 31)
    {
        v5 -= 16;
        v4 += 5;
    }

    v6 = v5 + 16;
    v7 = v4 - 5;

    if (abs(v3) != 512)
    {
        if (abs(work->delay) < 8)
        {
            if ((pad_status & PAD_UP) != 0)
            {
                work->delay--;
            }
            if ((pad_status & PAD_DOWN) != 0)
            {
                work->delay++;
            }
        }
    }

    if (abs(work->deltax) < 8)
    {
        if ((pad_status & PAD_LEFT) != 0)
        {
            work->deltax--;
        }

        if ((pad_status & PAD_RIGHT) != 0)
        {
            work->deltax++;
        }
    }

    lines = work->field_30_lines_2Array[GV_Clock];
    lines2 = work->field_28_lines_2Array[GV_Clock];
    tiles = work->field_48_tiles_2Array[GV_Clock];
    deltay = work->delay;

    MENU_Color(0x68, 0x6f, 0x74);

    for (; v6 < 210; v6 += 16, v7 -= 5)
    {
        MENU_Locate(0x28, v6 - 2, 1);

        if ((GM_PlayerStatus & PLAYER_NOT_SIGHT) == 0)
        {
            if (abs(v7) < 10)
            {
                if (v7 < 0)
                {
                    MENU_Printf("-0%d", -v7);
                }
                else
                {
                    MENU_Printf("0%d", v7);
                }
            }
            else
            {
                MENU_Printf("%d", v7);
            }
        }

        lines->y0 = v6 - 1;
        lines->y1 = v6 + 1;
        lines->y3 = v6;
        lines->y2 = v6;
        addPrimEX( ot, lines );
        lines++;

        if (v7 != 10 * (v7 / 10))
        {
            continue;
        }

        tiles->y0 = v6 + deltay;

        addPrimEX( ot, tiles );
        tiles++;

        lines2->y1 = v6 + deltay - 4;
        lines2->y0 = v6 + deltay - 4;
        lines2->y3 = v6 + deltay + 4;
        lines2->y2 = v6 + deltay + 4;
        addPrimEX( ot, lines2 );
        lines2++;

        lines2->y0 = v6 + deltay - 4;
        lines2->y1 = v6 + deltay + 4;
        addPrimEX( ot, lines2 );
        lines2++;
    }
}

STATIC void stnsight_act_helper_80068798( Work *work, u_long *ot )
{
    LINE_F4 *lines = work->field_40_lines_2Array[GV_Clock];
    DVECTOR *pos = work->pos;
    int      dy = work->delay;
    int      dx = work->deltax;
    short    dy2 = dx;
    short    buf;

    setXY4( lines, pos[0].vx, pos[0].vy, pos[1].vx, pos[1].vy,
           pos[2].vx, pos[2].vy, pos[3].vx, pos[3].vy );
    buf = ( work->delay < 0 ) ? dy : 0;
    addXY0( lines, dy2, buf );
    addXY1( lines, dy2, buf );
    addXY2( lines, dy2, buf );
    addXY3( lines, dy2, buf );
    addPrimEX( ot, lines );
    lines++;

    setXY2( lines, pos[3].vx, pos[3].vy, pos[4].vx, pos[4].vy );
    addXY0( lines, dy2, buf );
    addXY1( lines, dy2, buf );
    addPrimEX( ot, lines );
    lines++;

    setXY4( lines, pos[5].vx, pos[5].vy, pos[6].vx, pos[6].vy,
           pos[7].vx, pos[7].vy, pos[8].vx, pos[8].vy );
    buf = ( work->delay > 0 ) ? dy : 0 ;
    addXY0( lines, -dy2, buf );
    addXY1( lines, -dy2, buf );
    addXY2( lines, -dy2, buf );
    addXY3( lines, -dy2, buf );
    addPrimEX( ot, lines );
}

/* ミサイル照準セット */
STATIC void SetMissileRect( Work *work, u_long *ot )
{
    LINE_F4        *lines;
    DVECTOR         sxy;
    long            p, flag;
    int             x, sx;
    int             y, sy;

    if (amissile_alive_8009F490 != 0)
    {
        if (++work->field_84_4Array[0] < 28)
        {
            return;
        }

        lines = work->field_38_lines_2Array[GV_Clock];

        DG_Clip(&DG_Chanl(0)->field_5C_clip_rect, DG_Chanl(0)->field_50_clip_distance);
        SetRotMatrix(&DG_Chanl(0)->field_10_eye_inv);
        SetTransMatrix(&DG_Chanl(0)->field_10_eye_inv);
        RotTransPers(&svector_8009F494, (long *)&sxy, &p, &flag);

        sx = sxy.vx;
        sy = sxy.vy;

        x = sx + 0xa0;
        y = sy + 0x70;

        if (x >= 320u || y < 0 || y >= 224)
        {
            return;
        }

        lines->x3 = sx + 0x9f;
        lines->x0 = sx + 0x9f;
        lines->x2 = sx + 0x8d;
        lines->x1 = sx + 0x8d;
        lines->y1 = sy + 0x62;
        lines->y0 = sy + 0x62;
        lines->y3 = sy + 0x7e;
        lines->y2 = sy + 0x7e;
        addPrimEX( ot, lines );
        lines++;

        lines->x3 = sx + 0xa1;
        lines->x0 = sx + 0xa1;
        lines->x2 = sx + 0xb3;
        lines->x1 = sx + 0xb3;
        lines->y1 = sy + 0x62;
        lines->y0 = sy + 0x62;
        lines->y3 = sy + 0x7e;
        lines->y2 = sy + 0x7e;

        addPrimEX( ot, lines );

        MENU_Locate(sx + 0x8d, sy + 0x7f, 0);
        MENU_Color(0x1d, 0x29, 0x29);

        if ((GM_PlayerStatus & PLAYER_NOT_SIGHT) == 0)
        {
            MENU_Printf("%d %d\n", ((u_short)svector_8009F494.vx << 16) >> 20,
                        ((u_short)svector_8009F494.vy << 16) >> 20);
        }
    }
    else
    {
        work->field_84_4Array[0] = 0;
    }
}

STATIC void stnsight_act_helper_80068BF4( Work *work, u_long *ot )
{
    int             x;
    int             s0;
    int             s2 = 24;
    int             v1;
    unsigned short *s4 = gOldRootCnt_800B1DC8;
    int             uVar9 = s4[0];
    POLY_G4        *poly = work->field_50_polys_2Array[GV_Clock]; // s5

    ++s4;
    for (x = N_ChanlPerfMax - 1; x > 0; --x)
    {
        s0 = (*s4++ - uVar9) & 0xffff;

        if (s0 > 0x1ff)
        {
            s0 = 0x1ff;
        }

        s0 /= 10;
        v1 = s2 + s0;

        if (v1 > 240)
        {
            break;
        }

        poly->x0 = poly->x2 = s2;
        poly->x1 = poly->x3 = v1;

        addPrimEX( ot, poly );

        s2 += s0 + 1;
        poly++;
    }
}

STATIC void StnSightAct( Work *work )
{
    u_long *ot;
    int     iVar3;
    int     iVar4;
    int     local_20[2];
    u_short pad_status;

    if (work->field_94 > 0)
    {
        if (!GV_PauseLevel)
        {
            work->field_94--;
        }

        return;
    }

    if (work->field_84_4Array[2] == 0)
    {
        // TODO: fix data
        work->field_84_4Array[2] =
            (int)NewSight(GV_StrCode("stinger"), GV_StrCode("stinger"), &word_800AB8EC, 1, 0);
    }

    if (work->field_84_4Array[3] == 0)
    {
        local_20[0] = 0x41412e;
        local_20[1] = 0x293df6;
        // todo: fix data.
        work->field_84_4Array[3] = (int)NewSgtRect3(&word_800AB8EC, 1, local_20, 1);
    }

    ot = (u_long *)DG_ChanlOTag(1);

    stnsight_act_helper_80068420(work, ot);
    stnsight_act_helper_80068798(work, ot);
    SetMissileRect(work, ot);
    stnsight_act_helper_80068BF4(work, ot);
    stnsight_act_helper_8006837C(work);
    menu_Text_Init_80038B98();

    if (GV_PauseLevel != 0)
    {
        return;
    }

    pad_status = work->pad_data->status;
    GM_CheckShukanReverse(&pad_status);

    iVar3 = work->delay;

    if ((iVar3 != 0) && ((pad_status & (PAD_UP | PAD_DOWN)) == 0))
    {
        iVar4 = iVar3 - 1;

        if (iVar3 < 1)
        {
            iVar4 = iVar3 + 1;
        }

        work->delay = iVar4;
    }

    iVar3 = work->deltax;

    if ((iVar3 != 0) && ((pad_status & (PAD_LEFT | PAD_RIGHT)) == 0))
    {
        iVar4 = iVar3 - 1;

        if (iVar3 < 1)
        {
            iVar4 = iVar3 + 1;
        }

        work->deltax = iVar4;
    }
}

STATIC void StnSightDie( Work *work )
{
    if (work->field_28_lines_2Array[0])
    {
        GV_DelayedFree(work->field_28_lines_2Array[0]);
    }

    if (work->field_48_tiles_2Array[0])
    {
        GV_DelayedFree(work->field_48_tiles_2Array[0]);
    }

    if (work->field_38_lines_2Array[0])
    {
        GV_DelayedFree(work->field_38_lines_2Array[0]);
    }

    if (work->field_40_lines_2Array[0])
    {
        GV_DelayedFree(work->field_40_lines_2Array[0]);
    }

    if (work->field_50_polys_2Array[0])
    {
        GV_DelayedFree(work->field_50_polys_2Array[0]);
    }

    word_800AB8EC = 0;
}

STATIC int stnsight_init_helper_helper_80068F74( Work *work )
{
    LINE_F4 *lines;
    TILE_1  *tiles;
    int      count;

    work->field_28_lines_2Array[0] = lines = GV_Malloc(sizeof(LINE_F4) * 56);

    if (!lines)
    {
        return -1;
    }

    work->field_28_lines_2Array[1] = lines + 14;
    work->field_30_lines_2Array[0] = lines + 28;
    work->field_30_lines_2Array[1] = lines + 42;

    work->field_48_tiles_2Array[0] = tiles = GV_Malloc(sizeof(TILE_1) * 14);

    if (!tiles)
    {
        return -1;
    }

    work->field_48_tiles_2Array[1] = tiles + 7;

    for (count = 0; count < 14; count++)
    {
        *(int *)&lines->r0 = 0x41412e;
        lines->x3 = 18;
        lines->x0 = 18;
        lines->x2 = 41;
        lines->x1 = 41;
        setLineF4(lines);
        lines++;

        *(int *)&lines->r0 = 0x41412e;
        lines->x1 = 18;
        lines->x0 = 18;
        setLineF2(lines);
        lines++;
    }

    for (count = 0; count < 28; count++)
    {
        *(int *)&lines->r0 = 0x41412e;
        lines->x2 = 42;
        lines->x1 = 42;
        lines->x0 = 42;
        lines->x3 = 45;
        setLineF4(lines);
        lines++;
    }

    tiles = work->field_48_tiles_2Array[0];

    for (count = 0; count < 14; count++)
    {
        *(int *)&tiles->r0 = 0x68b187;
        tiles->x0 = 47;
        setTile1(tiles);
        tiles++;
    }

    return 0;
}

STATIC int stnsight_init_helper_helper_80069100( Work *work )
{
    LINE_F4 *lines;
    int      count;

    work->field_38_lines_2Array[0] = lines = GV_Malloc(sizeof(LINE_F4) * 4);

    if (!lines)
    {
        return -1;
    }

    work->field_38_lines_2Array[1] = lines + 2;

    for (count = 0; count < 4; count++)
    {
        *(int *)&lines->r0 = 0x41412e;
        setLineF4(lines);
        lines++;
    }

    return 0;
}

STATIC int stnsight_init_helper_helper_80069184( Work *work )
{
    LINE_F4 *lines;
    int      count;

    work->field_40_lines_2Array[0] = lines = GV_Malloc(sizeof(LINE_F4) * 6);

    if (!lines)
    {
        return -1;
    }

    work->field_40_lines_2Array[1] = lines + 3;

    for (count = 0; count < 2; count++)
    {
        *(int *)&lines->r0 = 0x7f7972;
        setLineF4(lines);
        lines++;

        *(int *)&lines->r0 = 0x7f7972;
        setLineF2(lines);
        lines++;

        *(int *)&lines->r0 = 0x7f7972;
        setLineF4(lines);
        lines++;
    }

    return 0;
}

STATIC int stnsight_init_helper_helper_80069234( Work *work )
{
    POLY_G4 *polys;
    int      count;

    work->field_50_polys_2Array[0] = polys = GV_Malloc(sizeof(POLY_G4) * 64);

    if (!polys)
    {
        return -1;
    }

    work->field_50_polys_2Array[1] = polys + 32;

    for (count = 0; count < 64; count++)
    {
        *(int *)&polys->r0 = 0x41412e;
        *(int *)&polys->r1 = 0x41412e;
        *(int *)&polys->r2 = 0x41412e;
        *(int *)&polys->r3 = 0x41412e;
        setPolyG4(polys);
        setSemiTrans(polys, 1);
        polys->y1 = 20;
        polys->y0 = 20;
        polys->y3 = 25;
        polys->y2 = 25;
        polys++;
    }

    return 0;
}

STATIC int StnSightGetResources( Work *work, CONTROL *control )
{
    if (stnsight_init_helper_helper_80068F74(work) < 0)
    {
        return -1;
    }

    if (stnsight_init_helper_helper_80069100(work) < 0)
    {
        return -1;
    }

    if (stnsight_init_helper_helper_80069184(work) < 0)
    {
        return -1;
    }

    if (stnsight_init_helper_helper_80069234(work) < 0)
    {
        return -1;
    }

    work->pos[0].vx = 147;
    work->pos[0].vy = 117;
    work->pos[1].vx = 147;
    work->pos[1].vy = 104;
    work->pos[2].vx = 159;
    work->pos[2].vy = 116;
    work->pos[3].vx = 171;
    work->pos[3].vy = 104;
    work->pos[4].vx = 171;
    work->pos[4].vy = 117;
    work->pos[5].vx = 144;
    work->pos[5].vy = 120;
    work->pos[6].vx = 144;
    work->pos[6].vy = 123;
    work->pos[7].vx = 174;
    work->pos[7].vy = 123;
    work->pos[8].vx = 174;
    work->pos[8].vy = 120;
    work->pad_data = GV_PadData_800B05C0;
    work->deltax = 0;
    work->delay = 0;
    work->control = control;
    work->field_84_4Array[0] = 0;
    work->field_84_4Array[1] = 0;
    work->field_84_4Array[2] = 0;
    work->field_84_4Array[3] = 0;
    work->field_94 = 8;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewStnSight( CONTROL *control )
{
    Work *work;

    if (word_800AB8EC != 0)
    {
        return NULL;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, StnSightAct, StnSightDie, "stnsight.c");

        if (StnSightGetResources(work, control) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        word_800AB8EC = 1;
    }

    return (void *)work;
}
