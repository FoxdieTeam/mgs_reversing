#include <stdio.h>
#include "common.h"
#include "Bullet/blast.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"
#include "Game/vibrate.h"
#include "Takabe/thing.h"
#include "strcode.h"

typedef struct _WireWork
{
    GV_ACT   actor;
    int      name;
    OBJECT   objects[25];
    DG_PRIM *f1668;
    int      f166C;
    int      f1670;
    SVECTOR  verts[112];
    int      map;
    int      f19F8;
    MATRIX   f19FC[2];
    MATRIX   f1A3C[2];
    MATRIX   f1A7C[2];
    MATRIX   f1ABC[2];
    MATRIX   f1AFC[2];
    MATRIX   f1B3C[2];
    MATRIX   f1B7C[2];
    MATRIX   f1BBC[2];
    MATRIX   f1BFC[2];
    MATRIX   f1C3C[2];
    MATRIX   f1C7C[2];
    MATRIX   f1CBC[2];
    MATRIX   f1CFC[2];
    MATRIX   f1D3C[2];
    MATRIX   f1D7C[2];
    MATRIX   f1DBC[2];
    MATRIX   f1DFC[2];
    MATRIX   f1E3C[2];
    MATRIX   f1E7C[2];
    MATRIX   f1EBC[2];
    MATRIX   f1EFC[2];
    MATRIX   f1F3C[2];
    MATRIX   f1F7C[2];
    MATRIX   f1FBC[2];
    MATRIX   f1FFC[2];
    TARGET  *f203C;
    char     pad1[0x7C];
    SVECTOR  f20BC;
    SVECTOR  f20C4;
    int      f20CC;
    int      f20D0;
    TARGET  *f20D4;
    SVECTOR  f20D8;
} WireWork;

extern BLAST_DATA blast_data_8009F4B8[8];
extern int        GM_CurrentMap;
extern SVECTOR    GM_PlayerPosition_800ABA10;

unsigned short s04c_dword_800C35E8[] = {HASH_KILL};
char           s04c_dword_800C35EC[] = {0x7F, 0x03, 0x00, 0x00};
SVECTOR        s04c_dword_800C35F0 = {2000, 2000, 2000, 0};
SVECTOR        s04c_dword_800C35F8 = {2500, 10000, 2500, 0};

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void s04c_wire_800D2E7C(WireWork *work)
{
    int   px, pz;
    int   x, z;

    GM_CurrentMap = work->map;

    px = GM_PlayerPosition_800ABA10.vx;
    pz = GM_PlayerPosition_800ABA10.vz;

    if (GM_PlayerPosition_800ABA10.vy > 300)
    {
        if (px <= 0)
        {
            if (px >= -5000 && pz <= 8500 && pz >= 3500)
            {
                if (px >= -5000 && px <= -4000)
                {
                    if (pz >= (-px + 2500) || pz <= (px + 9500))
                    {
                        GM_SeSet2(0, 63, 182);
                        NewPadVibration(s04c_dword_800C35EC, 1);

                        work->f1670 = 1;
                        work->f166C++;

                        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                        {
                            printf("Wire Cut!!\n");
                            GM_GameOverTimer = -2;

                            if (GM_CurrentItemId == ITEM_CAMERA || GM_CurrentItemId == ITEM_SCOPE)
                            {
                                GM_CurrentItemId = ITEM_NONE;
                            }
                        }

                        work->f203C->class &= ~TARGET_PUSH;
                        return;
                    }
                }
                else if (px >= -4000 && px <= -3500)
                {
                    if ((pz >= (-px + 2500) && pz <= (-px + 4500)) || (pz <= (px + 9500) && pz >= (px + 7500)))
                    {
                        GM_SeSet2(0, 63, 182);
                        NewPadVibration(s04c_dword_800C35EC, 1);

                        work->f1670 = 1;
                        work->f166C++;

                        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                        {
                            printf("Wire Cut!!\n");
                            GM_GameOverTimer = -2;

                            if (GM_CurrentItemId == ITEM_CAMERA || GM_CurrentItemId == ITEM_SCOPE)
                            {
                                GM_CurrentItemId = ITEM_NONE;
                            }
                        }

                        work->f203C->class &= ~TARGET_PUSH;
                        return;
                    }
                }
                else if (px >= -3500 && px <= -2500)
                {
                    if (pz <= (-px + 4500) && pz >= (px + 7500))
                    {
                        GM_SeSet2(0, 63, 182);
                        NewPadVibration(s04c_dword_800C35EC, 1);

                        work->f1670 = 1;
                        work->f166C++;

                        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                        {
                            printf("Wire Cut!!\n");
                            GM_GameOverTimer = -2;

                            if (GM_CurrentItemId == ITEM_CAMERA || GM_CurrentItemId == ITEM_SCOPE)
                            {
                                GM_CurrentItemId = ITEM_NONE;
                            }
                        }

                        work->f203C->class &= ~TARGET_PUSH;
                        return;
                    }
                }
                else if (px >= -2500 && px <= -1500)
                {
                    if (pz >= (-px + 2500) && pz <= (px + 9500))
                    {
                        GM_SeSet2(0, 63, 182);
                        NewPadVibration(s04c_dword_800C35EC, 1);

                        work->f1670 = 1;
                        work->f166C++;

                        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                        {
                            printf("Wire Cut!!\n");
                            GM_GameOverTimer = -2;

                            if (GM_CurrentItemId == ITEM_CAMERA || GM_CurrentItemId == ITEM_SCOPE)
                            {
                                GM_CurrentItemId = ITEM_NONE;
                            }
                        }

                        work->f203C->class &= ~TARGET_PUSH;
                        return;
                    }
                }
                else if (px >= -1500 && px <= -1000)
                {
                    if ((pz <= (px + 9500) && pz >= (px + 7500)) || (pz <= (-px + 0x1194) && pz >= (-px + 2500)))
                    {
                        GM_SeSet2(0, 63, 182);
                        NewPadVibration(s04c_dword_800C35EC, 1);

                        work->f1670 = 1;
                        work->f166C++;

                        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                        {
                            printf("Wire Cut!!\n");
                            GM_GameOverTimer = -2;

                            if (GM_CurrentItemId == ITEM_CAMERA || GM_CurrentItemId == ITEM_SCOPE)
                            {
                                GM_CurrentItemId = ITEM_NONE;
                            }
                        }

                        work->f203C->class &= ~TARGET_PUSH;
                        return;
                    }
                }
                else if (px >= -1000 && px <= 0 && pz >= (px + 7500) && pz <= (-px + 4500))
                {
                    GM_SeSet2(0, 63, 182);
                    NewPadVibration(s04c_dword_800C35EC, 1);

                    work->f1670 = 1;
                    work->f166C++;

                    if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                    {
                        printf("Wire Cut!!\n");
                        GM_GameOverTimer = -2;

                        if (GM_CurrentItemId == ITEM_CAMERA || GM_CurrentItemId == ITEM_SCOPE)
                        {
                            GM_CurrentItemId = ITEM_NONE;
                        }
                    }

                    work->f203C->class &= ~TARGET_PUSH;
                    return;
                }
            }
        }
    }
    else if (px <= -1500)
    {
        if (px >= -3500 && pz <= 7000 && pz >= 5000)
        {
            GM_SeSet2(0, 63, 182);
            NewPadVibration(s04c_dword_800C35EC, 1);

            work->f1670 = 1;
            work->f166C++;

            if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
            {
                printf("Wire Cut by HOFUKU!!\n");
                GM_GameOverTimer = -2;

                if (GM_CurrentItemId == ITEM_CAMERA || GM_CurrentItemId == ITEM_SCOPE)
                {
                    GM_CurrentItemId = ITEM_NONE;
                }
            }

            work->f203C->class &= ~TARGET_PUSH;
            return;
        }
    }

    if (work->f20CC == 1)
    {
        if (px > -500)
        {
            work->f20CC = 0;
            work->f20BC = work->f20C4;
        }
        else if (px < -4500)
        {
            work->f20CC = 0;
            work->f20BC = work->f20C4;
        }
        else if (pz > 8000)
        {
            work->f20CC = 0;
            work->f20BC = work->f20C4;
        }
        else if (pz < 4000)
        {
            work->f20CC = 0;
            work->f20BC = work->f20C4;
        }
    }

    if (work->f203C->damaged & 0x8)
    {
        x = work->f203C->field_34_vec.vx;
        if (x != 0)
        {
            work->f20BC.vx += (x / abs(x)) * 150;
        }

        z = work->f203C->field_34_vec.vz;
        if (z != 0)
        {
            work->f20BC.vz += (z / abs(z)) * 150;
        }

        work->f20CC = 1;

        work->f203C->damaged &= ~0x8;
    }

    if ((work->f20D4->damaged & 0x4) && work->f20D4->a_mode == 2)
    {
        GM_SeSet2(0, 63, 182);
        NewPadVibration(s04c_dword_800C35EC, 1);

        work->f166C = 15;
        work->f1670 = 1;

        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
        {
            printf("Wire Cut by BAKUFUU!!\n");
            GM_GameOverTimer = -2;

            if (GM_CurrentItemId == ITEM_CAMERA || GM_CurrentItemId == ITEM_SCOPE)
            {
                GM_CurrentItemId = ITEM_NONE;
            }
        }

        work->f203C->class &= ~TARGET_PUSH;
    }
}

void s04c_wire_800D350C(WireWork *work)
{
    GM_CurrentMap = work->map;

    switch (work->f166C)
    {
    case 30:
        NewBlast(&work->objects[0].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 31:
        NewBlast(&work->objects[3].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 32:
        NewBlast(&work->objects[2].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 33:
        NewBlast(&work->objects[1].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 34:
        NewBlast(&work->objects[15].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 35:
        NewBlast(&work->objects[14].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 36:
        NewBlast(&work->objects[13].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 37:
        NewBlast(&work->objects[6].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 38:
        NewBlast(&work->objects[5].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 39:
        NewBlast(&work->objects[4].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 40:
        NewBlast(&work->objects[21].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 41:
        NewBlast(&work->objects[20].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 42:
        NewBlast(&work->objects[19].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 43:
        NewBlast(&work->objects[9].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 44:
        NewBlast(&work->objects[8].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 45:
        NewBlast(&work->objects[7].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 46:
        NewBlast(&work->objects[24].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 47:
        NewBlast(&work->objects[23].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 48:
        NewBlast(&work->objects[22].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 49:
        NewBlast(&work->objects[12].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 50:
        NewBlast(&work->objects[11].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 51:
        NewBlast(&work->objects[10].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 52:
        NewBlast(&work->objects[18].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 53:
        NewBlast(&work->objects[17].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 54:
        NewBlast(&work->objects[16].objs->world, &blast_data_8009F4B8[1]);
        break;

    case 55:
        GV_DestroyActor(&work->actor);
        break;
    }

    work->f166C++;
}

void WireAct_800D36B8(WireWork *work)
{
    SVECTOR pos;

    if (work->f19F8 < 6)
    {
        pos.vx = work->objects[0].objs->world.t[0];
        pos.vy = work->objects[0].objs->world.t[1];
        pos.vz = work->objects[0].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f19FC);

        pos.vx = work->objects[3].objs->world.t[0];
        pos.vy = work->objects[3].objs->world.t[1];
        pos.vz = work->objects[3].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1A3C);

        pos.vx = work->objects[2].objs->world.t[0];
        pos.vy = work->objects[2].objs->world.t[1];
        pos.vz = work->objects[2].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1A7C);

        pos.vx = work->objects[1].objs->world.t[0];
        pos.vy = work->objects[1].objs->world.t[1];
        pos.vz = work->objects[1].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1ABC);

        pos.vx = work->objects[15].objs->world.t[0];
        pos.vy = work->objects[15].objs->world.t[1];
        pos.vz = work->objects[15].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1D3C);

        pos.vx = work->objects[14].objs->world.t[0];
        pos.vy = work->objects[14].objs->world.t[1];
        pos.vz = work->objects[14].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1D7C);

        pos.vx = work->objects[13].objs->world.t[0];
        pos.vy = work->objects[13].objs->world.t[1];
        pos.vz = work->objects[13].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1DBC);

        pos.vx = work->objects[6].objs->world.t[0];
        pos.vy = work->objects[6].objs->world.t[1];
        pos.vz = work->objects[6].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1AFC);

        pos.vx = work->objects[5].objs->world.t[0];
        pos.vy = work->objects[5].objs->world.t[1];
        pos.vz = work->objects[5].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1B3C);

        pos.vx = work->objects[4].objs->world.t[0];
        pos.vy = work->objects[4].objs->world.t[1];
        pos.vz = work->objects[4].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1B7C);

        pos.vx = work->objects[21].objs->world.t[0];
        pos.vy = work->objects[21].objs->world.t[1];
        pos.vz = work->objects[21].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1EBC);

        pos.vx = work->objects[20].objs->world.t[0];
        pos.vy = work->objects[20].objs->world.t[1];
        pos.vz = work->objects[20].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1EFC);

        pos.vx = work->objects[19].objs->world.t[0];
        pos.vy = work->objects[19].objs->world.t[1];
        pos.vz = work->objects[19].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1F3C);

        pos.vx = work->objects[9].objs->world.t[0];
        pos.vy = work->objects[9].objs->world.t[1];
        pos.vz = work->objects[9].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1BBC);

        pos.vx = work->objects[8].objs->world.t[0];
        pos.vy = work->objects[8].objs->world.t[1];
        pos.vz = work->objects[8].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1BFC);

        pos.vx = work->objects[7].objs->world.t[0];
        pos.vy = work->objects[7].objs->world.t[1];
        pos.vz = work->objects[7].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1C3C);

        pos.vx = work->objects[24].objs->world.t[0];
        pos.vy = work->objects[24].objs->world.t[1];
        pos.vz = work->objects[24].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1F7C);

        pos.vx = work->objects[23].objs->world.t[0];
        pos.vy = work->objects[23].objs->world.t[1];
        pos.vz = work->objects[23].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1FBC);

        pos.vx = work->objects[22].objs->world.t[0];
        pos.vy = work->objects[22].objs->world.t[1];
        pos.vz = work->objects[22].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1FFC);

        pos.vx = work->objects[12].objs->world.t[0];
        pos.vy = work->objects[12].objs->world.t[1];
        pos.vz = work->objects[12].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1C7C);

        pos.vx = work->objects[11].objs->world.t[0];
        pos.vy = work->objects[11].objs->world.t[1];
        pos.vz = work->objects[11].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1CBC);

        pos.vx = work->objects[10].objs->world.t[0];
        pos.vy = work->objects[10].objs->world.t[1];
        pos.vz = work->objects[10].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1CFC);

        pos.vx = work->objects[18].objs->world.t[0];
        pos.vy = work->objects[18].objs->world.t[1];
        pos.vz = work->objects[18].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1DFC);

        pos.vx = work->objects[17].objs->world.t[0];
        pos.vy = work->objects[17].objs->world.t[1];
        pos.vz = work->objects[17].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1E3C);

        pos.vx = work->objects[16].objs->world.t[0];
        pos.vy = work->objects[16].objs->world.t[1];
        pos.vz = work->objects[16].objs->world.t[2];
        DG_GetLightMatrix(&pos, work->f1E7C);

        work->f19F8++;
    }

    switch (work->f1670)
    {
    case 0:
        s04c_wire_800D2E7C(work);
        GM_MoveTarget(work->f203C, &work->f20BC);
        GM_PushTarget(work->f203C);
        break;

    case 1:
        s04c_wire_800D350C(work);
        break;
    }

    if (THING_Msg_CheckMessage(work->name, 1, s04c_dword_800C35E8) == 0)
    {
        GV_DestroyActor(&work->actor);
    }
}

void WireDie_800D3DB0(WireWork *work)
{
    DG_PRIM *prim;

    GM_FreeObject(&work->objects[0]);
    GM_FreeObject(&work->objects[3]);
    GM_FreeObject(&work->objects[2]);
    GM_FreeObject(&work->objects[1]);
    GM_FreeObject(&work->objects[15]);
    GM_FreeObject(&work->objects[14]);
    GM_FreeObject(&work->objects[13]);
    GM_FreeObject(&work->objects[6]);
    GM_FreeObject(&work->objects[5]);
    GM_FreeObject(&work->objects[4]);
    GM_FreeObject(&work->objects[21]);
    GM_FreeObject(&work->objects[20]);
    GM_FreeObject(&work->objects[19]);
    GM_FreeObject(&work->objects[9]);
    GM_FreeObject(&work->objects[8]);
    GM_FreeObject(&work->objects[7]);
    GM_FreeObject(&work->objects[24]);
    GM_FreeObject(&work->objects[23]);
    GM_FreeObject(&work->objects[22]);
    GM_FreeObject(&work->objects[12]);
    GM_FreeObject(&work->objects[11]);
    GM_FreeObject(&work->objects[10]);
    GM_FreeObject(&work->objects[18]);
    GM_FreeObject(&work->objects[17]);
    GM_FreeObject(&work->objects[16]);

    prim = work->f1668;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    GM_FreeTarget(work->f203C);
    GM_FreeTarget(work->f20D4);
}

int s04c_wire_800D3ED8(WireWork *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->f203C = target;
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, TARGET_PUSH, NO_SIDE, &s04c_dword_800C35F0);
    GM_MoveTarget(target, &work->f20C4);
    return 0;
}

int s04c_wire_800D3F40(WireWork *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->f20D4 = target;
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, TARGET_POWER, PLAYER_SIDE, &s04c_dword_800C35F8);
    GM_MoveTarget(target, &work->f20D8);
    return 0;
}

const char s04c_aWire_800DBBA8[] = "wire";
const char s04c_aBc_800DBBB0[] = "04b_c4";

#pragma INCLUDE_ASM("asm/overlays/s04c/s04c_wire_800D3FA8.s")
int s04c_wire_800D3FA8(WireWork *work, int name, int map);

GV_ACT *NewWire_800D709C(int name, int where)
{
    WireWork *work;

    work = (WireWork *)GV_NewActor(EXEC_LEVEL, sizeof(WireWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, WireAct_800D36B8, WireDie_800D3DB0, "wire.c");

        if (s04c_wire_800D3FA8(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
    }

    return &work->actor;
}
