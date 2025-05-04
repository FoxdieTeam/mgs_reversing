#include "weapon.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Menu/menuman.h"
#include "chara/snake/sna_init.h"
#include "Thing/sgtrect3.h"
#include "Thing/sight.h"

extern int              amissile_alive_8009F490;
extern SVECTOR          svector_8009F494;
extern short            N_ChanlPerfMax;
extern GV_PAD           GV_PadData_800B05C0[4];
extern unsigned short   gOldRootCnt_800B1DC8[];
extern TARGET          *target_800BDF00;

/*---------------------------------------------------------------------------*/
// Stinger Sight

typedef struct _StnSightWork
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
    int         field_58_ybase;             //'delay' in the leaks, but they must mean deltay
    int         field_5C_xbase;
    DVECTOR     field_60_coords_9Array[9];
    int         field_84_4Array[4];
    int         field_94;
} StnSightWork;

#define EXEC_LEVEL GV_ACTOR_AFTER2

STATIC short word_800AB8EC = 0;

/*---------------------------------------------------------------------------*/

STATIC void addPrimEX_80068320(unsigned int *ot, unsigned int *prim)
{
    if (!(GM_PlayerStatus & PLAYER_NOT_SIGHT))
    {
        addPrim(ot, prim);
    }
}

STATIC void stnsight_act_helper_8006837C(StnSightWork *work)
{
    int iVar1;

    if (!target_800BDF00)
    {
        work->field_84_4Array[1] = 0;
        return;
    }

    iVar1 = work->field_84_4Array[1]++;

    if ((GM_PlayerStatus & 0x4000000) != 0)
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

STATIC void stnsight_act_helper_80068420(StnSightWork *work, unsigned int *ot)
{
    ushort   pad_status;
    LINE_F4 *lines;
    LINE_F4 *lines2;
    TILE_1  *tiles;
    int      ybase;

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
        if (abs(work->field_58_ybase) < 8)
        {
            if ((pad_status & PAD_UP) != 0)
            {
                work->field_58_ybase--;
            }
            if ((pad_status & PAD_DOWN) != 0)
            {
                work->field_58_ybase++;
            }
        }
    }

    if (abs(work->field_5C_xbase) < 8)
    {
        if ((pad_status & PAD_LEFT) != 0)
        {
            work->field_5C_xbase--;
        }

        if ((pad_status & PAD_RIGHT) != 0)
        {
            work->field_5C_xbase++;
        }
    }

    lines = work->field_30_lines_2Array[GV_Clock];
    lines2 = work->field_28_lines_2Array[GV_Clock];
    tiles = work->field_48_tiles_2Array[GV_Clock];
    ybase = work->field_58_ybase;

    MENU_Color(0x68, 0x6f, 0x74);

    for (; v6 < 210; v6 += 16, v7 -= 5)
    {
        MENU_Locate(0x28, v6 - 2, 1);

        if ((GM_PlayerStatus & 0x4000000) == 0)
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
        addPrimEX_80068320(ot, (unsigned int *)lines);
        lines++;

        if (v7 != 10 * (v7 / 10))
        {
            continue;
        }

        tiles->y0 = v6 + ybase;

        addPrimEX_80068320(ot, (unsigned int *)tiles);
        tiles++;

        lines2->y1 = v6 + ybase - 4;
        lines2->y0 = v6 + ybase - 4;
        lines2->y3 = v6 + ybase + 4;
        lines2->y2 = v6 + ybase + 4;
        addPrimEX_80068320(ot, (unsigned int *)lines2);
        lines2++;

        lines2->y0 = v6 + ybase - 4;
        lines2->y1 = v6 + ybase + 4;
        addPrimEX_80068320(ot, (unsigned int *)lines2);
        lines2++;
    }
}

STATIC void stnsight_act_helper_80068798(StnSightWork *work, unsigned int *ot)
{
    LINE_F4 *p = work->field_40_lines_2Array[GV_Clock];
    DVECTOR *coords = work->field_60_coords_9Array;
    int      ybase = work->field_58_ybase;
    int      xbase = work->field_5C_xbase;
    short    xoff = xbase;
    short    yoff;

    p->x0 = coords[0].vx;
    p->y0 = coords[0].vy;
    p->x1 = coords[1].vx;
    p->y1 = coords[1].vy;
    p->x2 = coords[2].vx;
    p->y2 = coords[2].vy;
    p->x3 = coords[3].vx;
    p->y3 = coords[3].vy;

    if (work->field_58_ybase < 0)
    {
        yoff = ybase;
    }
    else
    {
        yoff = 0;
    }

    p->x0 += xoff;
    p->y0 += yoff;
    p->x1 += xoff;
    p->y1 += yoff;
    p->x2 += xoff;
    p->y2 += yoff;
    p->x3 += xoff;
    p->y3 += yoff;
    addPrimEX_80068320(ot, (unsigned int *)p);
    p++;

    p->x0 = coords[3].vx;
    p->y0 = coords[3].vy;
    p->x1 = coords[4].vx;
    p->y1 = coords[4].vy;
    p->x0 += xoff;
    p->y0 += yoff;
    p->x1 += xoff;
    p->y1 += yoff;
    addPrimEX_80068320(ot, (unsigned int *)p);
    p++;

    p->x0 = coords[5].vx;
    p->y0 = coords[5].vy;
    p->x1 = coords[6].vx;
    p->y1 = coords[6].vy;
    p->x2 = coords[7].vx;
    p->y2 = coords[7].vy;
    p->x3 = coords[8].vx;
    p->y3 = coords[8].vy;

    yoff = ( work->field_58_ybase > 0 ) ? ybase : 0 ;

    p->x0 -= xoff;
    p->y0 += yoff;
    p->x1 -= xoff;
    p->y1 += yoff;
    p->x2 -= xoff;
    p->y2 += yoff;
    p->x3 -= xoff;
    p->y3 += yoff;
    addPrimEX_80068320(ot, (unsigned int *)p);
}

/* ミサイル照準セット */
STATIC void SetMissileRect(StnSightWork *work, unsigned int *ot)
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
        addPrimEX_80068320(ot, (unsigned int *)lines);
        lines++;

        lines->x3 = sx + 0xa1;
        lines->x0 = sx + 0xa1;
        lines->x2 = sx + 0xb3;
        lines->x1 = sx + 0xb3;
        lines->y1 = sy + 0x62;
        lines->y0 = sy + 0x62;
        lines->y3 = sy + 0x7e;
        lines->y2 = sy + 0x7e;

        addPrimEX_80068320(ot, (unsigned int *)lines);

        MENU_Locate(sx + 0x8d, sy + 0x7f, 0);
        MENU_Color(0x1d, 0x29, 0x29);

        if ((GM_PlayerStatus & 0x4000000) == 0)
        {
            MENU_Printf("%d %d\n", ((ushort)svector_8009F494.vx << 16) >> 20,
                        ((ushort)svector_8009F494.vy << 16) >> 20);
        }
    }
    else
    {
        work->field_84_4Array[0] = 0;
    }
}

STATIC void stnsight_act_helper_80068BF4(StnSightWork *work, unsigned int *ot)
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

        addPrimEX_80068320(ot, (unsigned int *)poly);

        s2 += s0 + 1;
        poly++;
    }
}

STATIC void StnSightAct(StnSightWork *work)
{
    unsigned int *uVar1;
    int           iVar3;
    int           iVar4;
    int           local_20[2];
    ushort        pad_status;

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
            (int)NewSight_80071CDC(GV_StrCode("stinger"), GV_StrCode("stinger"), &word_800AB8EC, 1, 0);
    }

    if (work->field_84_4Array[3] == 0)
    {
        local_20[0] = 0x41412e;
        local_20[1] = 0x293df6;
        // todo: fix data.
        work->field_84_4Array[3] = (int)NewSgtRect3(&word_800AB8EC, 1, local_20, 1);
    }

    uVar1 = (unsigned int *)DG_ChanlOTag(1);

    stnsight_act_helper_80068420(work, uVar1);
    stnsight_act_helper_80068798(work, uVar1);
    SetMissileRect(work, uVar1);
    stnsight_act_helper_80068BF4(work, uVar1);
    stnsight_act_helper_8006837C(work);
    menu_Text_Init_80038B98();

    if (GV_PauseLevel != 0)
    {
        return;
    }

    pad_status = work->pad_data->status;
    GM_CheckShukanReverse(&pad_status);

    iVar3 = work->field_58_ybase;

    if ((iVar3 != 0) && ((pad_status & (PAD_UP | PAD_DOWN)) == 0))
    {
        iVar4 = iVar3 - 1;

        if (iVar3 < 1)
        {
            iVar4 = iVar3 + 1;
        }

        work->field_58_ybase = iVar4;
    }

    iVar3 = work->field_5C_xbase;

    if ((iVar3 != 0) && ((pad_status & (PAD_LEFT | PAD_RIGHT)) == 0))
    {
        iVar4 = iVar3 - 1;

        if (iVar3 < 1)
        {
            iVar4 = iVar3 + 1;
        }

        work->field_5C_xbase = iVar4;
    }
}

STATIC void StnSightDie(StnSightWork *work)
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

STATIC int stnsight_init_helper_helper_80068F74(StnSightWork *work)
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

STATIC int stnsight_init_helper_helper_80069100(StnSightWork *work)
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

STATIC int stnsight_init_helper_helper_80069184(StnSightWork *work)
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

STATIC int stnsight_init_helper_helper_80069234(StnSightWork *work)
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

STATIC int StnSightGetResources(StnSightWork *work, CONTROL *control)
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

    work->field_60_coords_9Array[0].vx = 147;
    work->field_60_coords_9Array[0].vy = 117;
    work->field_60_coords_9Array[1].vx = 147;
    work->field_60_coords_9Array[1].vy = 104;
    work->field_60_coords_9Array[2].vx = 159;
    work->field_60_coords_9Array[2].vy = 116;
    work->field_60_coords_9Array[3].vx = 171;
    work->field_60_coords_9Array[3].vy = 104;
    work->field_60_coords_9Array[4].vx = 171;
    work->field_60_coords_9Array[4].vy = 117;
    work->field_60_coords_9Array[5].vx = 144;
    work->field_60_coords_9Array[5].vy = 120;
    work->field_60_coords_9Array[6].vx = 144;
    work->field_60_coords_9Array[6].vy = 123;
    work->field_60_coords_9Array[7].vx = 174;
    work->field_60_coords_9Array[7].vy = 123;
    work->field_60_coords_9Array[8].vx = 174;
    work->field_60_coords_9Array[8].vy = 120;
    work->pad_data = GV_PadData_800B05C0;
    work->field_5C_xbase = 0;
    work->field_58_ybase = 0;
    work->control = control;
    work->field_84_4Array[0] = 0;
    work->field_84_4Array[1] = 0;
    work->field_84_4Array[2] = 0;
    work->field_84_4Array[3] = 0;
    work->field_94 = 8;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewStnSight(CONTROL *control)
{
    StnSightWork *work;

    if (word_800AB8EC != 0)
    {
        return NULL;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(StnSightWork));

    if (work)
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
