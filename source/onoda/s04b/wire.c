#include <stdio.h>
#include "common.h"
#include "bullet/blast.h"
#include "game/game.h"
#include "libgcl/libgcl.h"
#include "linkvar.h"
#include "game/vibrate.h"
#include "takabe/thing.h"
#include "strcode.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      name;
    OBJECT   objects[25];
    DG_PRIM *f1668;
    int      f166C;
    int      wire_cut;
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
} Work;

extern BLAST_DATA blast_data_8009F4B8[8];

unsigned short s04c_dword_800C35E8[] = {HASH_KILL};
char           s04c_dword_800C35EC[] = {0x7F, 0x03, 0x00, 0x00};
SVECTOR        s04c_dword_800C35F0 = {2000, 2000, 2000, 0};
SVECTOR        s04c_dword_800C35F8 = {2500, 10000, 2500, 0};

#define EXEC_LEVEL GV_ACTOR_USER

static void CheckWireCut(Work *work)
{
    int   px, pz;
    int   x, z;

    GM_CurrentMap = work->map;

    px = GM_PlayerPosition.vx;
    pz = GM_PlayerPosition.vz;

    if (GM_PlayerPosition.vy > 300)
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

                        work->wire_cut = 1;
                        work->f166C++;

                        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                        {
                            printf("Wire Cut!!\n");
                            GM_GameOverTimer = -2;

                            if (GM_Item == IT_Camera || GM_Item == IT_Scope)
                            {
                                GM_Item = IT_None;
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

                        work->wire_cut = 1;
                        work->f166C++;

                        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                        {
                            printf("Wire Cut!!\n");
                            GM_GameOverTimer = -2;

                            if (GM_Item == IT_Camera || GM_Item == IT_Scope)
                            {
                                GM_Item = IT_None;
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

                        work->wire_cut = 1;
                        work->f166C++;

                        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                        {
                            printf("Wire Cut!!\n");
                            GM_GameOverTimer = -2;

                            if (GM_Item == IT_Camera || GM_Item == IT_Scope)
                            {
                                GM_Item = IT_None;
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

                        work->wire_cut = 1;
                        work->f166C++;

                        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                        {
                            printf("Wire Cut!!\n");
                            GM_GameOverTimer = -2;

                            if (GM_Item == IT_Camera || GM_Item == IT_Scope)
                            {
                                GM_Item = IT_None;
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

                        work->wire_cut = 1;
                        work->f166C++;

                        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                        {
                            printf("Wire Cut!!\n");
                            GM_GameOverTimer = -2;

                            if (GM_Item == IT_Camera || GM_Item == IT_Scope)
                            {
                                GM_Item = IT_None;
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

                    work->wire_cut = 1;
                    work->f166C++;

                    if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
                    {
                        printf("Wire Cut!!\n");
                        GM_GameOverTimer = -2;

                        if (GM_Item == IT_Camera || GM_Item == IT_Scope)
                        {
                            GM_Item = IT_None;
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

            work->wire_cut = 1;
            work->f166C++;

            if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
            {
                printf("Wire Cut by HOFUKU!!\n");
                GM_GameOverTimer = -2;

                if (GM_Item == IT_Camera || GM_Item == IT_Scope)
                {
                    GM_Item = IT_None;
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
        x = work->f203C->offset.vx;
        if (x != 0)
        {
            work->f20BC.vx += (x / abs(x)) * 150;
        }

        z = work->f203C->offset.vz;
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
        work->wire_cut = 1;

        if (!(GM_GameStatus & STATE_DEMO) && GM_GameOverTimer == 0)
        {
            printf("Wire Cut by BAKUFUU!!\n");
            GM_GameOverTimer = -2;

            if (GM_Item == IT_Camera || GM_Item == IT_Scope)
            {
                GM_Item = IT_None;
            }
        }

        work->f203C->class &= ~TARGET_PUSH;
    }
}

static void TriggerDetonation(Work *work)
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

static void Act(Work *work)
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

    switch (work->wire_cut)
    {
    case 0:
        CheckWireCut(work);
        GM_MoveTarget(work->f203C, &work->f20BC);
        GM_PushTarget(work->f203C);
        break;

    case 1:
        TriggerDetonation(work);
        break;
    }

    if (THING_Msg_CheckMessage(work->name, 1, s04c_dword_800C35E8) == 0)
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
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

    GM_FreePrim(work->f1668);

    GM_FreeTarget(work->f203C);
    GM_FreeTarget(work->f20D4);
}

int wire_CreateTarget(Work *work)
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

int wire_CreateTarget2(Work *work)
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


static inline void SetPacketTexture(POLY_GT4 *pack, DG_TEX *tex)
{
    int u0, v0, u1, v1;

    u0 = tex->off_x;
    u1 = u0 + tex->w;
    v0 = tex->off_y;
    v1 = v0 + tex->h;
    setUV4(pack, u0, v0, u1, v0, u0, v1, u1, v1);

    pack->tpage = tex->tpage;
    pack->clut = tex->clut;
}

int s04c_wire_800D3FA8(Work *work, int name, int map)
{
    SVECTOR   pos_arg;
    SVECTOR   dir_arg;
    SVECTOR   pos;
    SVECTOR   rot;
    SVECTOR   points[32];
    SVECTOR  *vertex;
    OBJECT   *obj;
    DG_PRIM  *prim;
    POLY_GT4 *packs0;
    POLY_GT4 *packs1;
    DG_TEX   *tex;
    char     *opt;
    int       i, n;

    opt = GCL_GetOption('p');
    if (opt != NULL)
    {
        GCL_StrToSV(opt, (short *)&pos_arg);
    }
    else
    {
        pos_arg = DG_ZeroVector;
    }

    opt = GCL_GetOption('d');
    if (opt != NULL)
    {
        GCL_StrToSV(opt, (short *)&dir_arg);
    }
    else
    {
        dir_arg = DG_ZeroVector;
    }

    if (GCL_GetOption('w'))
    {
        work->f20D0 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->f20D0 = 0;
    }

    vertex = work->verts;
    GM_CurrentMap = map;
    prim = GM_MakePrim(DG_PRIM_LINE_GT2, 56, vertex, NULL);
    work->f1668 = prim;

    packs0 = (POLY_GT4 *)prim->packs[0];
    packs1 = (POLY_GT4 *)prim->packs[1];

    tex = DG_GetTexture(GV_StrCode("wire"));

    for (i = 0; i < 8; i++)
    {
        setPolyGT4(packs0);
        setPolyGT4(packs1);

        SetPacketTexture(packs0, tex);
        SetPacketTexture(packs1, tex);

        SetSemiTrans(packs0, 1);
        SetSemiTrans(packs1, 1);

        setRGB0(packs0, 128, 175, 128);
        setRGB1(packs0, 128, 175, 128);
        setRGB2(packs0, 128, 175, 128);
        setRGB3(packs0, 128, 175, 128);

        setRGB0(packs1, 128, 175, 128);
        setRGB1(packs1, 128, 175, 128);
        setRGB2(packs1, 128, 175, 128);
        setRGB3(packs1, 128, 175, 128);

        packs0++;
        packs1++;
    }

    for (i = 0; i < 4; i++)
    {
        setPolyGT4(packs0);
        setPolyGT4(packs1);

        SetPacketTexture(packs0, tex);
        SetPacketTexture(packs1, tex);

        SetSemiTrans(packs0, 1);
        SetSemiTrans(packs1, 1);

        setRGB0(packs0, 32, 40, 32);
        setRGB1(packs0, 32, 40, 32);
        setRGB2(packs0, 32, 40, 32);
        setRGB3(packs0, 32, 40, 32);

        setRGB0(packs1, 32, 40, 32);
        setRGB1(packs1, 32, 40, 32);
        setRGB2(packs1, 32, 40, 32);
        setRGB3(packs1, 32, 40, 32);

        packs0++;
        packs1++;
    }

    for (i = 0; i < 16; i++)
    {
        setPolyGT4(packs0);
        setPolyGT4(packs1);

        SetPacketTexture(packs0, tex);
        SetPacketTexture(packs1, tex);

        SetSemiTrans(packs0, 1);
        SetSemiTrans(packs1, 1);

        setRGB0(packs0, 128, 175, 128);
        setRGB1(packs0, 32, 40, 32);
        setRGB2(packs0, 128, 175, 128);
        setRGB3(packs0, 32, 40, 32);

        setRGB0(packs1, 128, 175, 128);
        setRGB1(packs1, 32, 40, 32);
        setRGB2(packs1, 128, 175, 128);
        setRGB3(packs1, 32, 40, 32);

        packs0++;
        packs1++;
    }

    for (i = 0; i < 8; i++)
    {
        setPolyGT4(packs0);
        setPolyGT4(packs1);

        SetPacketTexture(packs0, tex);
        SetPacketTexture(packs1, tex);

        SetSemiTrans(packs0, 1);
        SetSemiTrans(packs1, 1);

        setRGB0(packs0, 128, 175, 128);
        setRGB1(packs0, 128, 175, 128);
        setRGB2(packs0, 128, 175, 128);
        setRGB3(packs0, 128, 175, 128);

        setRGB0(packs1, 128, 175, 128);
        setRGB1(packs1, 128, 175, 128);
        setRGB2(packs1, 128, 175, 128);
        setRGB3(packs1, 128, 175, 128);

        packs0++;
        packs1++;
    }

    for (i = 0; i < 4; i++)
    {
        setPolyGT4(packs0);
        setPolyGT4(packs1);

        SetPacketTexture(packs0, tex);
        SetPacketTexture(packs1, tex);

        SetSemiTrans(packs0, 1);
        SetSemiTrans(packs1, 1);

        setRGB0(packs0, 32, 40, 32);
        setRGB1(packs0, 32, 40, 32);
        setRGB2(packs0, 32, 40, 32);
        setRGB3(packs0, 32, 40, 32);

        setRGB0(packs1, 32, 40, 32);
        setRGB1(packs1, 32, 40, 32);
        setRGB2(packs1, 32, 40, 32);
        setRGB3(packs1, 32, 40, 32);

        packs0++;
        packs1++;
    }

    for (i = 0; i < 16; i++)
    {
        setPolyGT4(packs0);
        setPolyGT4(packs1);

        SetPacketTexture(packs0, tex);
        SetPacketTexture(packs1, tex);

        SetSemiTrans(packs0, 1);
        SetSemiTrans(packs1, 1);

        setRGB0(packs0, 128, 175, 128);
        setRGB1(packs0, 32, 40, 32);
        setRGB2(packs0, 128, 175, 128);
        setRGB3(packs0, 32, 40, 32);

        setRGB0(packs1, 128, 175, 128);
        setRGB1(packs1, 32, 40, 32);
        setRGB2(packs1, 128, 175, 128);
        setRGB3(packs1, 32, 40, 32);

        packs0++;
        packs1++;
    }

    /* per-point block scope for p is required for the match */
    {
        SVECTOR *p = &points[0];
        setVector(p, pos_arg.vx + 1750, 2500, pos_arg.vz - 2375);
    }
    {
        SVECTOR *p = &points[1];
        setVector(p, pos_arg.vx + 2375, 2500, pos_arg.vz - 2375);
    }
    {
        SVECTOR *p = &points[2];
        setVector(p, pos_arg.vx + 2375, 2500, pos_arg.vz - 1750);
    }
    {
        SVECTOR *p = &points[3];
        setVector(p, pos_arg.vx + 2375, 2500, pos_arg.vz + 1750);
    }
    {
        SVECTOR *p = &points[4];
        setVector(p, pos_arg.vx + 2375, 2500, pos_arg.vz + 2375);
    }
    {
        SVECTOR *p = &points[5];
        setVector(p, pos_arg.vx + 1750, 2500, pos_arg.vz + 2375);
    }
    {
        SVECTOR *p = &points[6];
        setVector(p, pos_arg.vx - 1750, 2500, pos_arg.vz + 2375);
    }
    {
        SVECTOR *p = &points[7];
        setVector(p, pos_arg.vx - 2375, 2500, pos_arg.vz + 2375);
    }
    {
        SVECTOR *p = &points[8];
        setVector(p, pos_arg.vx - 2375, 2500, pos_arg.vz + 1750);
    }
    {
        SVECTOR *p = &points[9];
        setVector(p, pos_arg.vx - 2375, 2500, pos_arg.vz - 1750);
    }
    {
        SVECTOR *p = &points[10];
        setVector(p, pos_arg.vx - 2375, 2500, pos_arg.vz - 2375);
    }
    {
        SVECTOR *p = &points[11];
        setVector(p, pos_arg.vx - 1750, 2500, pos_arg.vz - 2375);
    }
    {
        SVECTOR *p = &points[12];
        setVector(p, pos_arg.vx - 500, 1200, pos_arg.vz - 500);
    }
    {
        SVECTOR *p = &points[13];
        setVector(p, pos_arg.vx + 500, 1200, pos_arg.vz - 500);
    }
    {
        SVECTOR *p = &points[14];
        setVector(p, pos_arg.vx + 500, 1200, pos_arg.vz + 500);
    }
    {
        SVECTOR *p = &points[15];
        setVector(p, pos_arg.vx - 500, 1200, pos_arg.vz + 500);
    }
    {
        SVECTOR *p = &points[16];
        setVector(p, pos_arg.vx + 1625, 1000, pos_arg.vz - 2500);
    }
    {
        SVECTOR *p = &points[17];
        setVector(p, pos_arg.vx + 2500, 1000, pos_arg.vz - 2500);
    }
    {
        SVECTOR *p = &points[18];
        setVector(p, pos_arg.vx + 2500, 1000, pos_arg.vz - 1625);
    }
    {
        SVECTOR *p = &points[19];
        setVector(p, pos_arg.vx + 2500, 1000, pos_arg.vz + 1625);
    }
    {
        SVECTOR *p = &points[20];
        setVector(p, pos_arg.vx + 2500, 1000, pos_arg.vz + 2500);
    }
    {
        SVECTOR *p = &points[21];
        setVector(p, pos_arg.vx + 1625, 1000, pos_arg.vz + 2500);
    }
    {
        SVECTOR *p = &points[22];
        setVector(p, pos_arg.vx - 1625, 1000, pos_arg.vz + 2500);
    }
    {
        SVECTOR *p = &points[23];
        setVector(p, pos_arg.vx - 2500, 1000, pos_arg.vz + 2500);
    }
    {
        SVECTOR *p = &points[24];
        setVector(p, pos_arg.vx - 2500, 1000, pos_arg.vz + 1625);
    }
    {
        SVECTOR *p = &points[25];
        setVector(p, pos_arg.vx - 2500, 1000, pos_arg.vz - 1625);
    }
    {
        SVECTOR *p = &points[26];
        setVector(p, pos_arg.vx - 2500, 1000, pos_arg.vz - 2500);
    }
    {
        SVECTOR *p = &points[27];
        setVector(p, pos_arg.vx - 1625, 1000, pos_arg.vz - 2500);
    }
    {
        SVECTOR *p = &points[28];
        setVector(p, pos_arg.vx - 500, 600, pos_arg.vz - 500);
    }
    {
        SVECTOR *p = &points[29];
        setVector(p, pos_arg.vx + 500, 600, pos_arg.vz - 500);
    }
    {
        SVECTOR *p = &points[30];
        setVector(p, pos_arg.vx + 500, 600, pos_arg.vz + 500);
    }
    {
        SVECTOR *p = &points[31];
        setVector(p, pos_arg.vx - 500, 600, pos_arg.vz + 500);
    }

    n = 0;
    vertex[n] = points[0];
    n++;
    vertex[n] = points[1];
    n++;
    vertex[n] = points[1];
    n++;
    vertex[n] = points[2];
    n++;
    vertex[n] = points[3];
    n++;
    vertex[n] = points[4];
    n++;
    vertex[n] = points[4];
    n++;
    vertex[n] = points[5];
    n++;
    vertex[n] = points[6];
    n++;
    vertex[n] = points[7];
    n++;
    vertex[n] = points[7];
    n++;
    vertex[n] = points[8];
    n++;
    vertex[n] = points[9];
    n++;
    vertex[n] = points[10];
    n++;
    vertex[n] = points[10];
    n++;
    vertex[n] = points[11];
    n++;
    vertex[n] = points[12];
    n++;
    vertex[n] = points[13];
    n++;
    vertex[n] = points[13];
    n++;
    vertex[n] = points[14];
    n++;
    vertex[n] = points[14];
    n++;
    vertex[n] = points[15];
    n++;
    vertex[n] = points[15];
    n++;
    vertex[n] = points[12];
    n++;
    vertex[n] = points[0];
    n++;
    vertex[n] = points[12];
    n++;
    vertex[n] = points[0];
    n++;
    vertex[n] = points[14];
    n++;
    vertex[n] = points[2];
    n++;
    vertex[n] = points[12];
    n++;
    vertex[n] = points[2];
    n++;
    vertex[n] = points[14];
    n++;
    vertex[n] = points[3];
    n++;
    vertex[n] = points[13];
    n++;
    vertex[n] = points[3];
    n++;
    vertex[n] = points[15];
    n++;
    vertex[n] = points[5];
    n++;
    vertex[n] = points[13];
    n++;
    vertex[n] = points[5];
    n++;
    if (work->f20D0)
    {
        vertex[n] = points[5];
    }
    else
    {
        vertex[n] = points[5];
    }
    n++;
    vertex[n] = points[6];
    n++;
    if (work->f20D0)
    {
        vertex[n] = points[6];
    }
    else
    {
        vertex[n] = points[14];
    }
    n++;
    vertex[n] = points[6];
    n++;
    vertex[n] = points[12];
    n++;
    vertex[n] = points[8];
    n++;
    vertex[n] = points[14];
    n++;
    vertex[n] = points[8];
    n++;
    vertex[n] = points[12];
    n++;
    vertex[n] = points[9];
    n++;
    vertex[n] = points[15];
    n++;
    vertex[n] = points[9];
    n++;
    vertex[n] = points[13];
    n++;
    vertex[n] = points[11];
    n++;
    vertex[n] = points[13];
    n++;
    vertex[n] = points[11];
    n++;
    vertex[n] = points[15];
    n++;
    vertex[n] = points[16];
    n++;
    vertex[n] = points[17];
    n++;
    vertex[n] = points[17];
    n++;
    vertex[n] = points[18];
    n++;
    vertex[n] = points[19];
    n++;
    vertex[n] = points[20];
    n++;
    vertex[n] = points[20];
    n++;
    vertex[n] = points[21];
    n++;
    vertex[n] = points[22];
    n++;
    vertex[n] = points[23];
    n++;
    vertex[n] = points[23];
    n++;
    vertex[n] = points[24];
    n++;
    vertex[n] = points[25];
    n++;
    vertex[n] = points[26];
    n++;
    vertex[n] = points[26];
    n++;
    vertex[n] = points[27];
    n++;
    vertex[n] = points[28];
    n++;
    vertex[n] = points[29];
    n++;
    vertex[n] = points[29];
    n++;
    vertex[n] = points[30];
    n++;
    vertex[n] = points[30];
    n++;
    vertex[n] = points[31];
    n++;
    vertex[n] = points[31];
    n++;
    vertex[n] = points[28];
    n++;
    vertex[n] = points[16];
    n++;
    vertex[n] = points[28];
    n++;
    vertex[n] = points[16];
    n++;
    vertex[n] = points[30];
    n++;
    vertex[n] = points[18];
    n++;
    vertex[n] = points[28];
    n++;
    vertex[n] = points[18];
    n++;
    vertex[n] = points[30];
    n++;
    vertex[n] = points[19];
    n++;
    vertex[n] = points[29];
    n++;
    vertex[n] = points[19];
    n++;
    vertex[n] = points[31];
    n++;
    vertex[n] = points[21];
    n++;
    vertex[n] = points[29];
    n++;
    vertex[n] = points[21];
    n++;
    if (work->f20D0)
    {
        vertex[n] = points[21];
    }
    else
    {
        vertex[n] = points[31];
    }
    n++;
    vertex[n] = points[22];
    n++;
    if (work->f20D0)
    {
        vertex[n] = points[22];
    }
    else
    {
        vertex[n] = points[30];
    }
    n++;
    vertex[n] = points[22];
    n++;
    vertex[n] = points[28];
    n++;
    vertex[n] = points[24];
    n++;
    vertex[n] = points[30];
    n++;
    vertex[n] = points[24];
    n++;
    vertex[n] = points[28];
    n++;
    vertex[n] = points[25];
    n++;
    vertex[n] = points[31];
    n++;
    vertex[n] = points[25];
    n++;
    vertex[n] = points[29];
    n++;
    vertex[n] = points[27];
    n++;
    vertex[n] = points[29];
    n++;
    vertex[n] = points[27];
    n++;
    vertex[n] = points[31];
    n++;

    obj = &work->objects[0];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 20;
    pos.vy = pos_arg.vy;
    pos.vz = pos_arg.vz - 100;
    rot = dir_arg;
    rot.vy = 0x800;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[0].objs->world);
    GM_ConfigObjectLight(obj, work->f19FC);

    obj = &work->objects[1];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx + 530;
    pos.vy = pos_arg.vy + 100;
    pos.vz = pos_arg.vz - 50;
    rot = dir_arg;
    rot.vy = 0x400;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[1].objs->world);
    GM_ConfigObjectLight(obj, work->f1ABC);

    obj = &work->objects[2];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx + 530;
    pos.vy = pos_arg.vy + 1200;
    pos.vz = pos_arg.vz - 50;
    rot = dir_arg;
    rot.vy = 0x400;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[2].objs->world);
    GM_ConfigObjectLight(obj, work->f1A7C);

    obj = &work->objects[3];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx + 530;
    pos.vy = pos_arg.vy + 2000;
    pos.vz = pos_arg.vz - 50;
    rot = dir_arg;
    rot.vy = 0x400;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[3].objs->world);
    GM_ConfigObjectLight(obj, work->f1A3C);

    obj = &work->objects[13];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx + 500;
    pos.vy = pos_arg.vy + 100;
    pos.vz = pos_arg.vz + 520;
    rot = dir_arg;
    rot.vy = 0x200;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[13].objs->world);
    GM_ConfigObjectLight(obj, work->f1DBC);

    obj = &work->objects[14];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx + 500;
    pos.vy = pos_arg.vy + 1200;
    pos.vz = pos_arg.vz + 520;
    rot = dir_arg;
    rot.vy = 0x200;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[14].objs->world);
    GM_ConfigObjectLight(obj, work->f1D7C);

    obj = &work->objects[15];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx + 500;
    pos.vy = pos_arg.vy + 2000;
    pos.vz = pos_arg.vz + 520;
    rot = dir_arg;
    rot.vy = 0x200;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[15].objs->world);
    GM_ConfigObjectLight(obj, work->f1D3C);

    obj = &work->objects[4];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 20;
    pos.vy = pos_arg.vy + 100;
    pos.vz = pos_arg.vz + 510;
    rot = dir_arg;
    rot.vy = 0;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[4].objs->world);
    GM_ConfigObjectLight(obj, work->f1B7C);

    obj = &work->objects[5];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 20;
    pos.vy = pos_arg.vy + 1200;
    pos.vz = pos_arg.vz + 510;
    rot = dir_arg;
    rot.vy = 0;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[5].objs->world);
    GM_ConfigObjectLight(obj, work->f1B3C);

    obj = &work->objects[6];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 20;
    pos.vy = pos_arg.vy + 2000;
    pos.vz = pos_arg.vz + 510;
    rot = dir_arg;
    rot.vy = 0;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[6].objs->world);
    GM_ConfigObjectLight(obj, work->f1AFC);

    obj = &work->objects[19];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 520;
    pos.vy = pos_arg.vy + 100;
    pos.vz = pos_arg.vz + 520;
    rot = dir_arg;
    rot.vy = 0xE00;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[19].objs->world);
    GM_ConfigObjectLight(obj, work->f1F3C);

    obj = &work->objects[20];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 520;
    pos.vy = pos_arg.vy + 1200;
    pos.vz = pos_arg.vz + 520;
    rot = dir_arg;
    rot.vy = 0xE00;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[20].objs->world);
    GM_ConfigObjectLight(obj, work->f1EFC);

    obj = &work->objects[21];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 520;
    pos.vy = pos_arg.vy + 2000;
    pos.vz = pos_arg.vz + 520;
    rot = dir_arg;
    rot.vy = 0xE00;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[21].objs->world);
    GM_ConfigObjectLight(obj, work->f1EBC);

    obj = &work->objects[7];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 540;
    pos.vy = pos_arg.vy + 100;
    pos.vz = pos_arg.vz - 100;
    rot = dir_arg;
    rot.vy = 0xC00;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[7].objs->world);
    GM_ConfigObjectLight(obj, work->f1C3C);

    obj = &work->objects[8];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 540;
    pos.vy = pos_arg.vy + 1200;
    pos.vz = pos_arg.vz - 100;
    rot = dir_arg;
    rot.vy = 0xC00;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[8].objs->world);
    GM_ConfigObjectLight(obj, work->f1BFC);

    obj = &work->objects[9];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 540;
    pos.vy = pos_arg.vy + 2000;
    pos.vz = pos_arg.vz - 100;
    rot = dir_arg;
    rot.vy = 0xC00;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[9].objs->world);
    GM_ConfigObjectLight(obj, work->f1BBC);

    obj = &work->objects[22];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 520;
    pos.vy = pos_arg.vy + 100;
    pos.vz = pos_arg.vz - 540;
    rot = dir_arg;
    rot.vy = 0xA00;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[22].objs->world);
    GM_ConfigObjectLight(obj, work->f1FFC);

    obj = &work->objects[23];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 520;
    pos.vy = pos_arg.vy + 1200;
    pos.vz = pos_arg.vz - 540;
    rot = dir_arg;
    rot.vy = 0xA00;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[23].objs->world);
    GM_ConfigObjectLight(obj, work->f1FBC);

    obj = &work->objects[24];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 520;
    pos.vy = pos_arg.vy + 2000;
    pos.vz = pos_arg.vz - 540;
    rot = dir_arg;
    rot.vy = 0xA00;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[24].objs->world);
    GM_ConfigObjectLight(obj, work->f1F7C);

    obj = &work->objects[10];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 20;
    pos.vy = pos_arg.vy + 100;
    pos.vz = pos_arg.vz - 550;
    rot = dir_arg;
    rot.vy = 0x800;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[10].objs->world);
    GM_ConfigObjectLight(obj, work->f1CFC);

    obj = &work->objects[11];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 20;
    pos.vy = pos_arg.vy + 1200;
    pos.vz = pos_arg.vz - 550;
    rot = dir_arg;
    rot.vy = 0x800;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[11].objs->world);
    GM_ConfigObjectLight(obj, work->f1CBC);

    obj = &work->objects[12];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx - 20;
    pos.vy = pos_arg.vy + 2000;
    pos.vz = pos_arg.vz - 550;
    rot = dir_arg;
    rot.vy = 0x800;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[12].objs->world);
    GM_ConfigObjectLight(obj, work->f1C7C);

    obj = &work->objects[16];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx + 540;
    pos.vy = pos_arg.vy + 100;
    pos.vz = pos_arg.vz - 540;
    rot = dir_arg;
    rot.vy = 0x600;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[16].objs->world);
    GM_ConfigObjectLight(obj, work->f1FFC);

    obj = &work->objects[17];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx + 540;
    pos.vy = pos_arg.vy + 1200;
    pos.vz = pos_arg.vz - 540;
    rot = dir_arg;
    rot.vy = 0x600;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[17].objs->world);
    GM_ConfigObjectLight(obj, work->f1FBC);

    obj = &work->objects[18];
    GM_InitObject(obj, GV_StrCode("04b_c4"), 0x6D, 0);
    pos.vx = pos_arg.vx + 540;
    pos.vy = pos_arg.vy + 2000;
    pos.vz = pos_arg.vz - 540;
    rot = dir_arg;
    rot.vy = 0x600;
    DG_SetPos2(&pos, &rot);
    ReadRotMatrix(&work->objects[18].objs->world);
    GM_ConfigObjectLight(obj, work->f1F7C);

    work->f166C = 0;
    work->wire_cut = 0;
    work->map = map;
    work->f19F8 = 0;

    work->f20BC = pos_arg;
    work->f20C4 = pos_arg;

    work->f20D8.vx = -2500;
    work->f20D8.vy = 10000;
    work->f20D8.vz = 6000;

    work->f20CC = 0;

    work->f20BC.vy += 3000;
    work->f20C4.vy += 3000;

    if (wire_CreateTarget(work) < 0)
    {
        return -1;
    }

    if (wire_CreateTarget2(work) < 0)
    {
        return -1;
    }

    return 0;
}
int s04c_wire_800D3FA8(Work *work, int name, int map); // GetResources

void *NewWire(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "wire.c");

        if (s04c_wire_800D3FA8(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
    }

    return (void *)work;
}
