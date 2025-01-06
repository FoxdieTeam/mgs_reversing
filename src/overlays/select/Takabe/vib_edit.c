#include <stdio.h>
#include "common.h"
#include "Game/game.h"
#include "Game/vibrate.h"
#include "Takabe/thing.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct _VibEditPrims
{
    TILE    tiles1[2][16];
    TILE    tiles2[2][16];
    LINE_F2 lines[2][3];
} VibEditPrims;

typedef struct VibPair
{
    unsigned char first;
    unsigned char second;
} VibPair;

typedef struct _VibEditWork
{
    GV_ACT         actor;
    int            field_20_status;
    int            field_24;
    int            field_28;
    int            field_2C;
    int            field_30;
    int            field_34;
    int            field_38;
    int            field_3C;
    int            field_40;
    VibEditPrims  *field_44_prims;
    VibrateWork   *field_48_vibrate;
    VibPair        field_4C_pairs[16];
    int            field_6C;
    VibPair        field_70_pairs[16];
    int            field_90;
    VibPair        field_94_pairs[32][32];
    VibPair        field_894_pairs[16];
    VibPair        field_8B4_pairs[16];
} VibEditWork;

extern int    GM_PlayerStatus_800ABA50;
extern int    GV_Clock_800AB920;
extern GV_PAD GV_PadData_800B05C0[4];

// VibEditGetResources is calling this with two missing parameters for some reason.
int PCopen(const char *name /*, int flags, int perms*/);
int PCread(int fd, char *buff, int len);
int PCclose(int fd);

// For some reason VibEditDie_800C467C calls this with a missing
// last argument!? But it's not bad - PsyQ documentation says
// that argument is ignored anyways...
int PCcreat(char *name /*, int perms */);
int PCwrite(int fd, char *buff, int len);

#define EXEC_LEVEL 3

const char *select_dword_800C3220[4] = {
    "INS PARAM",
    "DEL PARAM",
    "SWAP BACK",
    "SWAP FORWARD",
};

const char *select_dword_800C3230[5] = {
    "CHANGE BANK", "QUICK SAVE HIGH", "QUICK SAVE LOW", "QUICK LOAD HIGH", "QUICK LOAD LOW",
};

void VibEdit_800C34F0(VibEditWork *work)
{
    VibEditPrims *prims;
    TILE         *tile1;
    TILE         *tile2;
    int           i;
    LINE_F2      *line;

    work->field_44_prims = GV_Malloc(sizeof(VibEditPrims));
    prims = work->field_44_prims;

    tile1 = prims->tiles1[0];
    tile2 = prims->tiles1[1];

    for (i = 16; i > 0; i--)
    {
        setTile(tile1);
        *tile2++ = *tile1++;
    }

    tile1 = prims->tiles2[0];
    tile2 = prims->tiles2[1];

    for (i = 16; i > 0; i--)
    {
        setTile(tile1);
        *tile2++ = *tile1++;
    }

    line = &prims->lines[0][0];
    setLineF2(line);
    setXY2(line, 16, 155, 320, 155);
    setRGB0(line, 0, 180, 0);
    prims->lines[1][0] = *line;

    line = &prims->lines[0][1];
    setLineF2(line);
    setXY2(line, 16, 70, 320, 70);
    setRGB0(line, 180, 0, 0);
    prims->lines[1][1] = *line;

    line = &prims->lines[0][2];
    setLineF2(line);
    setXY2(line, 16, 155, 16, 70);
    setRGB0(line, 0, 0, 180);
    prims->lines[1][2] = *line;
}

void select_800C36BC(VibEditWork *work)
{
    VibPair       *pairs;
    LINE_F2       *line;
    TILE          *tile;
    unsigned char *mOt;
    int            x0;
    int            i;

    pairs = work->field_4C_pairs;
    x0 = 16;

    tile = work->field_44_prims->tiles1[GV_Clock_800AB920];
    mOt = DG_Chanl(1)->mOrderingTables[GV_Clock_800AB920];

    for (i = 0; i < 16; i++, pairs++, tile++)
    {
        if (work->field_38 == i && work->field_3C == 1)
        {
            tile->r0 = 0;
            tile->g0 = 80;
            tile->b0 = 200;
        }
        else
        {
            tile->r0 = 100;
            tile->g0 = 180;
            tile->b0 = 180;
        }

        tile->x0 = x0;
        tile->w = pairs->second;
        x0 += tile->w;
        tile->y0 = 155 - pairs->first / 3;
        tile->h = 1;

        addPrim(mOt, tile);
    }

    pairs = work->field_70_pairs;
    x0 = 16;

    tile = work->field_44_prims->tiles2[GV_Clock_800AB920];

    for (i = 0; i < 16; i++, pairs++, tile++)
    {
        if (work->field_38 == i && work->field_3C == 0)
        {
            tile->r0 = 200;
            tile->g0 = 80;
            tile->b0 = 0;
        }
        else
        {
            tile->r0 = 180;
            tile->g0 = 180;
            tile->b0 = 100;
        }

        tile->x0 = x0;
        tile->w = pairs->second;
        x0 += tile->w;
        tile->y0 = 155 - pairs->first / 3;
        tile->h = 1;

        addPrim(mOt, tile);
    }

    line = work->field_44_prims->lines[GV_Clock_800AB920];
    line[2].x0 = line[2].x1 = work->field_34 + 16;

    for (i = 0; i < 3; i++, line++)
    {
        addPrim(mOt, line);
    }
}

void select_800C3974(VibEditWork *work)
{
    int      i;
    VibPair *iter;

    printf("pad vibation parameter (for gcl)\n");
    printf("high:{ ");

    iter = work->field_4C_pairs;
    for (i = 0; i < 16; iter++, i++)
    {
        if (iter->first == 0 && iter->second == 0)
        {
            break;
        }
        printf("%d,%d ", iter->first, iter->second);
    }
    printf("}\n");
    printf("low:{ ");
    iter = work->field_70_pairs;
    for (i = 0; i < 16; iter++, i++)
    {
        if (iter->first == 0 && iter->second == 0)
        {
            break;
        }
        printf("%d,%d ", iter->first, iter->second);
    }
    printf("}\n");
    printf("pad vibation parameter (for program)\n");
    printf("high:{ ");

    iter = work->field_4C_pairs;
    for (i = 0; i < 16; iter++, i++)
    {
        if (iter->first == 0 && iter->second == 0)
        {
            printf("0,0", iter->first, iter->second); // unnecessary args...
            break;
        }
        printf("%d,%d,", iter->first, iter->second);
    }
    printf("}\n");
    printf("high:{ ");
    iter = work->field_70_pairs;
    for (i = 0; i < 16; iter++, i++)
    {
        if (iter->first == 0 && iter->second == 0)
        {
            printf("0,0", iter->first, iter->second); // unnecessary args...
            break;
        }
        printf("%d,%d,", iter->first, iter->second);
    }
    printf("}\n\n");
}

void select_800C3BB8(VibPair *ptr, int cnt)
{
    int i;
    ptr += cnt;
    for (i = 16 - cnt; i > 0; i--)
    {
        ptr[0] = ptr[1];
        ptr++;
    }
}

void select_800C3BF4(VibPair *ptr, int cnt)
{
    int i;
    for (i = 15 - cnt, ptr += 15; i > 0; i--)
    {
        ptr[0] = ptr[-1];
        ptr--;
    }
}

void select_800C3C28(VibPair *ptr, int cnt)
{
    VibPair pair;

    if (cnt >= 15)
    {
        return;
    }

    pair = ptr[cnt + 1];
    ptr[cnt + 1] = ptr[cnt];
    ptr[cnt] = pair;
}

void select_800C3C74(VibPair *ptr, int cnt)
{
    VibPair pair;

    if (cnt <= 0)
    {
        return;
    }

    pair = ptr[cnt - 1];
    ptr[cnt - 1] = ptr[cnt];
    ptr[cnt] = pair;
}

void VibEdit_800C3CBC(VibEditWork *work, int idx)
{
    VibPair *dst, *src;
    int      i;

    dst = work->field_94_pairs[idx];
    src = work->field_4C_pairs;
    for (i = 16; i > 0; i--)
    {
        *dst++ = *src++;
    }

    src = work->field_70_pairs;
    for (i = 16; i > 0; i--)
    {
        *dst++ = *src++;
    }
}

// VibEdit_800C3CBC but with dst/src swapped:
void VibEdit_800C3D20(VibEditWork *work, int idx)
{
    VibPair *dst, *src;
    int      i;

    src = work->field_94_pairs[idx];
    dst = work->field_4C_pairs;
    for (i = 16; i > 0; i--)
    {
        *dst++ = *src++;
    }

    dst = work->field_70_pairs;
    for (i = 16; i > 0; i--)
    {
        *dst++ = *src++;
    }
}

void select_800C3D84(VibPair *src, VibPair *dst)
{
    int i;
    for (i = 16; i > 0; i--)
    {
        *dst++ = *src++;
    }
}

void VibEditAct_800C3DB0(VibEditWork *work)
{
    int      i, j, idx;
    int      old_field_28, sum;
    VibPair *pairs, *cur_pair;
    int      pad;

    pairs = work->field_3C == 0 ? work->field_70_pairs : work->field_4C_pairs;

    switch (work->field_24)
    {
    case 0:
        pad = GV_PadData_800B05C0[0].press;
        if (pad & PAD_L1)
        {
            if (work->field_38 > 0)
            {
                work->field_38--;
            }
        }
        if (pad & PAD_R1)
        {
            if (work->field_38 < 15)
            {
                work->field_38++;
            }
        }

        pad = GV_PadData_800B05C0[0].status;
        cur_pair = &pairs[work->field_38];
        if (pad & PAD_RIGHT)
        {
            if (cur_pair->second < 127)
            {
                cur_pair->second++;
            }
        }
        if (pad & PAD_LEFT)
        {
            if (cur_pair->second)
            {
                cur_pair->second--;
            }
        }
        if (work->field_3C == 0)
        {
            if (pad & PAD_UP)
            {
                if (cur_pair->first < 255)
                {
                    cur_pair->first++;
                }
            }
            if (pad & PAD_DOWN)
            {
                if (cur_pair->first)
                {
                    cur_pair->first--;
                }
            }
        }
        else
        {
            if (pad & PAD_UP)
            {
                cur_pair->first = 127;
            }
            if (pad & PAD_DOWN)
            {
                cur_pair->first = 0;
            }
        }
        pad = GV_PadData_800B05C0[0].status;
        if (pad & PAD_R2)
        {
            work->field_2C = 0;
            work->field_24 = 2;
        }
        if (pad & PAD_L2)
        {
            work->field_2C = 0;
            work->field_24 = 3;
        }
        pad = GV_PadData_800B05C0[0].press;
        if (pad & PAD_TRIANGLE)
        {
            work->field_3C ^= 1;
        }
        if (pad & PAD_SQUARE)
        {
            select_800C3974(work);
        }
        if (pad & PAD_CIRCLE)
        {
            work->field_48_vibrate = NewPadVibration((unsigned char *)work->field_4C_pairs, 1);
            work->field_48_vibrate = NewPadVibration((unsigned char *)work->field_70_pairs, 2);
            work->field_24 = 1;
            work->field_34 = 0;
            work->field_30 = 0;

            sum = 0;

            for (i = 0; i < 16; i++)
            {
                if (work->field_4C_pairs[i].second == 0 && work->field_4C_pairs[i].first == 0)
                {
                    break;
                }
                work->field_30 += work->field_4C_pairs[i].second;
            }

            for (i = 0; i < 16; i++)
            {
                if (work->field_70_pairs[i].second == 0 && work->field_70_pairs[i].first == 0)
                {
                    break;
                }
                sum += work->field_70_pairs[i].second;
            }

            if (work->field_30 < sum)
            {
                work->field_30 = sum;
            }
        }
        break;
    case 1:
        if (GV_PadData_800B05C0[0].press & PAD_CROSS)
        {
            work->field_30 = -1;
        }
        work->field_34++;
        if (--work->field_30 < 0)
        {
            work->field_24 = 0;
            work->field_34 = 0;
        }
        break;
    case 2:
        if (GV_PadData_800B05C0[0].status & PAD_R2)
        {
            pad = GV_PadData_800B05C0[0].press;
            if (pad & (PAD_LEFT | PAD_UP))
            {
                work->field_2C--;
            }
            if (pad & (PAD_RIGHT | PAD_DOWN))
            {
                work->field_2C++;
            }
            if (work->field_2C < 0)
            {
                work->field_2C = 3;
            }
            if (work->field_2C >= 4)
            {
                work->field_2C = 0;
            }
            if (pad & PAD_CIRCLE)
            {
                switch (work->field_2C)
                {
                case 0:
                    select_800C3BF4(pairs, work->field_38);
                    break;
                case 1:
                    select_800C3BB8(pairs, work->field_38);
                    break;
                case 2:
                    select_800C3C28(pairs, work->field_38);
                    if (work->field_38 < 15)
                    {
                        work->field_38++;
                    }
                    break;
                case 3:
                    select_800C3C74(pairs, work->field_38);
                    if (work->field_38 > 0)
                    {
                        work->field_38--;
                    }
                    break;
                }
            }
            MENU_Locate(230, 160, 0);
            MENU_Printf("EDIT MENU");
            for (i = 0; i < 4; i++)
            {
                if (work->field_2C == i)
                {
                    MENU_Locate(230, 180 + (i - 1) * 8, 0);
                }
                else
                {
                    MENU_Locate(238, 180 + (i - 1) * 8, 0);
                }
                MENU_Printf(select_dword_800C3220[i]);
            }
        }
        else
        {
            work->field_24 = 0;
        }
        break;
    case 3:
        if (GV_PadData_800B05C0[0].status & PAD_L2)
        {
            pad = GV_PadData_800B05C0[0].press;
            if (pad & PAD_UP)
            {
                work->field_2C--;
            }
            if (pad & PAD_DOWN)
            {
                work->field_2C++;
            }
            if (work->field_2C < 0)
            {
                work->field_2C = 4;
            }
            if (work->field_2C >= 5)
            {
                work->field_2C = 0;
            }
            if (work->field_2C == 0)
            {
                old_field_28 = work->field_28;
                if (pad & PAD_LEFT)
                {
                    if (work->field_28 > 0)
                    {
                        work->field_28--;
                    }
                }
                if (pad & PAD_RIGHT)
                {
                    if (work->field_28 < 31)
                    {
                        work->field_28++;
                    }
                }
                if (old_field_28 != work->field_28)
                {
                    VibEdit_800C3CBC(work, old_field_28);
                    VibEdit_800C3D20(work, work->field_28);
                }
            }
            if (pad & PAD_CIRCLE)
            {
                switch (work->field_2C)
                {
                case 0:
                    break;
                case 1:
                    select_800C3D84(work->field_4C_pairs, work->field_894_pairs);
                    break;
                case 2:
                    select_800C3D84(work->field_70_pairs, work->field_8B4_pairs);
                    break;
                case 3:
                    select_800C3D84(work->field_894_pairs, work->field_4C_pairs);
                    break;
                case 4:
                    select_800C3D84(work->field_8B4_pairs, work->field_70_pairs);
                    break;
                }
                work->field_24 = 0;
            }

            MENU_Locate(230, 160, 0);
            MENU_Printf("FILE MENU");
            if (work->field_2C == 0)
            {
                MENU_Locate(230, 172, 0);
            }
            else
            {
                MENU_Locate(238, 172, 0);
            }
            MENU_Printf("%s %d", select_dword_800C3230[0], work->field_28);

            for (i = 1; i < 5; i++)
            {
                if (work->field_2C == i)
                {
                    MENU_Locate(230, 180 + (i - 1) * 8, 0);
                }
                else
                {
                    MENU_Locate(238, 180 + (i - 1) * 8, 0);
                }

                MENU_Printf(select_dword_800C3230[i]);
            }
        }
        else
        {
            work->field_24 = 0;
        }
        break;
    }
    MENU_Locate(32, 16, 0);
    MENU_Printf("Vibration Editor   Ver 1.50\n");
    MENU_Printf("Select param  - < L1  R1 >\n");
    MENU_Printf("Change length - < L   R  >\n");
    MENU_Printf("Change power  - < U   D  >\n");
    MENU_Printf("EXIT          - < L3 >\n");
    MENU_Locate(168, 24, 0);
    MENU_Printf("PLAY          - < A >\n");
    MENU_Printf("Type change   - < X >\n");
    MENU_Printf("Disp param    - < Y >\n");
    MENU_Printf("Edit menu     - < R2 >\n");
    MENU_Printf("File menu     - < L2 >\n");
    MENU_Locate(32, 64, 0);
    MENU_Printf("Edit vibration - type %d\n", 2 - work->field_3C);

    for (j = 0; j < 2; j++)
    {
        for (i = 0; i < 8; i++)
        {
            idx = j * 8 + i;
            cur_pair = &pairs[idx];
            MENU_Locate(32 + 100 * j, 160 + i * 8, 0);
            if (idx == work->field_38)
            {
                MENU_Printf("E%2d- %3d %3d\n", idx, cur_pair->first, cur_pair->second);
            }
            else
            {
                MENU_Printf(" %2d- %3d %3d\n", idx, cur_pair->first, cur_pair->second);
            }
        }
    }

    select_800C36BC(work);

    if (GV_PadData_800B05C0[0].press & 0x200)
    {
        if (work->field_40)
        {
            GCL_ExecProc(work->field_40, 0);
        }
        GV_DestroyActor(&work->actor);
    }

    GM_GameStatus |= STATE_PAUSE_ONLY;
}
void VibEditDie_800C467C(VibEditWork *work)
{
    int fd;

    printf("Save vibration editor data !\n");

    VibEdit_800C3CBC(work, work->field_28);

    fd = PCcreat("VIB_EDIT.DAT");
    PCwrite(fd, (char *)work->field_94_pairs, sizeof(work->field_94_pairs));
    PCclose(fd);

    GM_GameStatus &= ~(work->field_20_status & STATE_PAUSE_ONLY);
    GM_PlayerStatus_800ABA50 &= ~PLAYER_PAD_OFF;
}

int VibEditGetResources_800C4720(VibEditWork *work, int flags, int perms)
{
    int fd;

    work->field_40 = THING_Gcl_GetInt('e');

    VibEdit_800C34F0(work);

    // Should have 3 args
    fd = PCopen("VIB_EDIT.DAT");
    PCread(fd, (char *)work->field_94_pairs, sizeof(work->field_94_pairs));
    PCclose(fd);

    VibEdit_800C3D20(work, work->field_28);

    work->field_20_status = GM_GameStatus;
    GM_PlayerStatus_800ABA50 |= PLAYER_PAD_OFF;

    return 0;
}

GV_ACT *NewVibEdit_800C47B4(int flags, int perms)
{
    VibEditWork *work;

    work = (VibEditWork *)GV_NewActor(EXEC_LEVEL, sizeof(VibEditWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)VibEditAct_800C3DB0,
                         (GV_ACTFUNC)VibEditDie_800C467C, "vib_edit.c");

        if (VibEditGetResources_800C4720(work, flags, perms) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
