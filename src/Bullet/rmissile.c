#include "Takabe/prim.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "Menu/menuman.h"
#include "Thing/sgtrect3.h"
#include "Thing/sight.h"
#include "libhzd/libhzd.h"
#include "blast.h"
#include "psyq.h"
#include "rmissile.h"
#include "Game/map.h"
#include "libgcl/hash.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

// nikita missile

extern MATRIX           DG_ZeroMatrix_8009D430;
extern SVECTOR          DG_ZeroVector_800AB39C;
extern GV_PAD           GV_PadData_800B05C0[4];
extern OBJECT *         GM_PlayerBody_800ABA20;
extern int              GM_GameOverTimer_800AB3D4;
extern SVECTOR          GM_PlayerPosition_800ABA10;
extern int              GV_Clock_800AB920;
extern Blast_Data       blast_data_8009F4B8[8];
extern int              GM_CurrentMap_800AB9B0;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern TARGET          *target_800BDF00;
extern int              dword_8009F604;
extern int              dword_800BDEF8[];
extern int              GM_GameStatus_800AB3CC;
extern CONTROL         *GM_PlayerControl_800AB9F4;
extern int              GM_CameraTrackSave_800AB42C;
extern SVECTOR          GM_CameraRotateSave_800AB430;
extern int              GM_event_camera_flag_800ABA9C;
extern GM_Camera        GM_Camera_800B77E8;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern CAMERA           GM_CameraList_800B7718[8];

int dword_8009F46C = 0; // FIXME: this is referenced as an array in several places
int dword_8009F470 = 0;
int dword_8009F474 = 0;
SVECTOR svector_8009F478 = {0, 0, 0, 0};
int dword_8009F480 = 0;
short Nik_Blast_8009F484 = 0;
SVECTOR svector_8009F488 = {100, 100, 100, 0};

void rmissile_loader_helper4_8006B800(RMissileWork *work)
{
    GV_CopyMemory_800160D8(&GM_Camera_800B77E8,           &work->field_17C_camera,  sizeof(work->field_17C_camera));
    GV_CopyMemory_800160D8(&gUnkCameraStruct_800B77B8,    &work->field_1F8,         sizeof(work->field_1F8));
    GV_CopyMemory_800160D8(GM_CameraList_800B7718,        &work->field_228_camera,  sizeof(work->field_228_camera));
    GV_CopyMemory_800160D8(&GM_CameraRotateSave_800AB430, &work->field_2CC_svector, sizeof(work->field_2CC_svector));

    work->field_2C8 = GM_CameraTrackSave_800AB42C;
    work->field_2D4 = GM_event_camera_flag_800ABA9C;
}

void rmissile_8006B888(RMissileWork *work)
{
    GV_CopyMemory_800160D8(&work->field_17C_camera,  &GM_Camera_800B77E8,           sizeof(work->field_17C_camera));
    GV_CopyMemory_800160D8(&work->field_1F8,         &gUnkCameraStruct_800B77B8,    sizeof(work->field_1F8));
    GV_CopyMemory_800160D8(&work->field_228_camera,  &GM_CameraList_800B7718,       sizeof(work->field_228_camera));
    GV_CopyMemory_800160D8(&work->field_2CC_svector, &GM_CameraRotateSave_800AB430, sizeof(work->field_2CC_svector));

    GM_CameraTrackSave_800AB42C = work->field_2C8;
    GM_event_camera_flag_800ABA9C = work->field_2D4;

    sub_800309B4(2, 30);
    GM_CameraEventReset_800309A8();
}

void rmissile_8006B924(RMissileWork *work)
{
    CONTROL *ctrl;

    ctrl = &work->field_20_ctrl;
    ctrl->field_55_skip_flag |= CTRL_SKIP_TRAP;

    rmissile_8006B888(work);
    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_07;
    sub_8002A258(ctrl->field_2C_map->field_8_hzd, &ctrl->field_10_events);

    ctrl = GM_PlayerControl_800AB9F4;

    if (ctrl)
    {
        HZD_ReExecEvent_8002A1F4(ctrl->field_2C_map->field_8_hzd, &ctrl->field_10_events, 0x102);
    }
}

void rmissile_act_helper_helper_8006B9B0(RMissileWork *work)
{
    Nik_Blast_8009F484 = 1;

    if (dword_8009F604 != SGT_NIKITA)
    {
        NewSight_80071CDC(SGT_NIKITA, SGT_NIKITA, &Nik_Blast_8009F484, 1, 0);
    }

    GM_Camera_800B77E8.field_22 = 1;

    if (work->field_113 == 0)
    {
        work->field_113 = 1;
        dword_800BDEF8[0] = 0x5A875D;
        dword_800BDEF8[1] = 0xC1A80;
        sgtrect3_init_80071010(&Nik_Blast_8009F484, 1, dword_800BDEF8, 0);
        GM_SeSet2_80032968(0, 0x3F, 0x15);
    }
}

void rmissile_act_helper_helper_8006BA70(RMissileWork *work)
{
    if (!target_800BDF00)
    {
        work->field_168 = 0;
        return;
    }

    work->field_168++;

    if (work->field_168 <= 16)
    {
        return;

    }

    if (work->field_168 == 32)
    {
        work->field_168 = 0;
    }

    if (!(GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000))
    {
        menu_Color_80038B4C(158, 184, 138);
        menu_Text_XY_Flags_80038B34(116, 98, 0);
        menu_Text_80038C38("ENEMY\n");
        menu_Text_Init_80038B98();
    }
}

void rmissile_act_helper_helper_8006BB10(RMissileWork *work)
{
    int var_a1;
    unsigned int *pOt;
    POLY_F4 *pPoly;
    CONTROL ctrl;

    var_a1 = ((1000 - work->field_118) * 60) / 1000;

    pOt = (unsigned int *)DG_ChanlOTag(1);
    pPoly = work->field_174_polys_2Array[GV_Clock_800AB920];

    if (var_a1 > 60)
    {
        var_a1 = 60;
    }

    pPoly->x3 = var_a1 + 31;
    pPoly->x1 = var_a1 + 31;

    if (GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000)
    {
        return;
    }

    if (var_a1 < 15)
    {
        pPoly->r0 = 212;
        pPoly->g0 = 78;
        pPoly->b0 = 78;

        if (!(work->field_118 % 15))
        {
            GM_SeSet2_80032968(0, 63, 116);
        }
    }

    addPrim(pOt, pPoly);
    ctrl = work->field_20_ctrl;

    menu_Text_XY_Flags_80038B34(8, 136, 0);
    menu_Text_80038C38("%d", ctrl.field_0_mov.vx);

    menu_Text_XY_Flags_80038B34(8, 144, 0);
    menu_Text_80038C38("%d", ctrl.field_0_mov.vy);

    menu_Text_XY_Flags_80038B34(8, 152, 0);
    menu_Text_80038C38("%d", ctrl.field_0_mov.vz);

    menu_Text_Init_80038B98();
}

void rmissile_act_helper_8006BD24(RMissileWork *work, int arg1)
{
    if (work->field_112 || work->field_117 || work->field_110)
    {
        return;
    }

    if (arg1 & 0x10)
    {
        rmissile_act_helper_helper_8006B9B0(work);

        gUnkCameraStruct_800B77B8.field_28.vx = 0;
        gUnkCameraStruct_800B77B8.field_28.vy = work->field_20_ctrl.field_8_rot.vy;
        gUnkCameraStruct_800B77B8.field_28.vz = 0;

        DG_InvisibleObjs(work->field_9C_kmd.objs);

        work->field_11C = -2;

        if (work->field_114 < 16)
        {
            work->field_114++;
            return;
        }

        rmissile_act_helper_helper_8006BB10(work);
        rmissile_act_helper_helper_8006BA70(work);
        return;
    }

    if (work->field_113 != 0)
    {
        work->field_115 = 5;
    }

    work->field_114 = 0;
    work->field_113 = 0;

    GM_Camera_800B77E8.field_22 = 0;
    Nik_Blast_8009F484 = 0;

    if (work->field_115)
    {
        work->field_115--;

        if (!work->field_115)
        {
            DG_VisibleObjs(work->field_9C_kmd.objs);
        }
    }
}

void rmissile_act_helper_8006BE50(RMissileWork *work, int arg1)
{
    if (GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF)
    {
        return;
    }

    if (arg1 >= 0 && work->field_20_ctrl.field_4C_turn.vy != arg1)
    {
        work->field_111 = 30;
        work->field_20_ctrl.field_4C_turn.vy = arg1;
    }
}

void rmissile_act_helper_8006BE90(RMissileWork *work, int arg1)
{
    if (GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF)
    {
        return;
    }

    if (arg1 & 0x8000)
    {
        work->field_111 = 30;
        work->field_20_ctrl.field_4C_turn.vy += 64;
        work->field_20_ctrl.field_4C_turn.vy &= 0xFFF;
    }

    if (arg1 & 0x2000)
    {
        work->field_111 = 30;
        work->field_20_ctrl.field_4C_turn.vy -= 64;
        work->field_20_ctrl.field_4C_turn.vy &= 0xFFF;
    }
}

void rmissile_act_helper_8006BEEC(RMissileWork *work)
{
    if (work->field_117)
    {
        return;
    }

    if (GM_PlayerStatus_800ABA50 & 0x2100 || dword_8009F474 == 1 || GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_01 | GAME_FLAG_BIT_24))
    {
        work->field_117 = 1;
        work->field_16A = 15;
        work->field_16C_svector = work->field_20_ctrl.field_0_mov;
        work->field_113 = 0;

        GM_Camera_800B77E8.field_22 = 0;
        Nik_Blast_8009F484 = 0;

        if (!work->field_112)
        {
            DG_VisibleObjs(work->field_9C_kmd.objs);
        }

        dword_8009F474 = 0;
        rmissile_8006B924(work);
    }
}

void rmissile_act_helper_8006BFD4(RMissileWork *work)
{
    if (work->field_111)
    {
        work->field_111--;

        if (!work->field_111)
        {
            GM_SeSet2_80032968(0, 63, 77);
            work->field_116 = 12;
        }

        work->field_11A = 50;

        if (!work->field_112)
        {
            work->field_11C = 0;
        }
    }
    else
    {
        if (work->field_116)
        {
            work->field_116--;
            gUnkCameraStruct_800B77B8.field_0.vy += GV_RandS_800170BC(512) * work->field_116 / 32;
        }

        work->field_11A = 200;

        if (!work->field_112)
        {
            work->field_11C = 8;
        }
    }
}

int rmissile_act_helper_helper_8006C0A4(void)
{
    GV_MSG *message;
    int length;

    length = GV_ReceiveMessage_80016620(0x15A9, &message);

    if (length > 0)
    {
        for (length--; length >= 0; message++, length--)
        {
            if (message->message[0] == HASH_KILL)
            {
                return 1;
            }
        }
    }

    return 0;
}

void rmissile_act_helper_8006C114(RMissileWork *work)
{
    SVECTOR *pPosition;
    int found;
    MATRIX rotation;
    Blast_Data *pBlastData;

    if (work->field_112)
    {
        return;
    }

    pPosition = &work->field_20_ctrl.field_0_mov;
    found = rmissile_act_helper_helper_8006C0A4();

    if (work->field_20_ctrl.field_58 <= 0 && !(work->field_20_ctrl.field_57 & 2))
    {
        if (pPosition->vy - work->field_108_svector.vy < 200)
        {
            if (++work->field_118 != 1000 && !sub_8002D7DC(&work->field_120_target) && !dword_8009F480 && !found)
            {
                if (!sub_80029098(work->field_20_ctrl.field_2C_map->field_8_hzd, pPosition, 250, 15, 8))
                {
                    if (abs(pPosition->vx) <= 30000 && abs(pPosition->vy) <= 30000 && abs(pPosition->vz) <= 30000)
                    {
                        return;
                    }
                }
            }
        }
    }

    if (GM_Camera_800B77E8.field_22 && !work->field_117)
    {
        GM_Camera_800B77E8.field_22 = 0;
        Nik_Blast_8009F484 = 0;
    }

    work->field_113 = 0;
    dword_8009F480 = 0;
    work->field_112 = 1U;
    work->field_118 = found ? 28 : 0;
    work->field_20_ctrl.field_44_step = DG_ZeroVector_800AB39C;
    DG_InvisibleObjs(work->field_9C_kmd.objs);
    work->field_9C_kmd.objs->group_id = 0;
    work->field_11C = -2;

    if (!found)
    {
        DG_SetPos2_8001BC8C(pPosition, &work->field_20_ctrl.field_8_rot);
        ReadRotMatrix(&rotation);

        GM_CurrentMap_800AB9B0 = work->field_20_ctrl.field_2C_map->field_0_map_index_bit;

        if (GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31 | GAME_FLAG_BIT_32))
        {
            pBlastData = &blast_data_8009F4B8[7];
        #ifdef VR_EXE
            if ((GM_GameStatus_800AB3CC & GAME_FLAG_BIT_31) &&
                !(GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF) &&
                !(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_29))
            {
                pBlastData = &blast_data_8009F4B8[4];
            }
        #endif
        }
        else
        {
            pBlastData = &blast_data_8009F4B8[4];
        }
        NewBlast_8006DFDC(&rotation, pBlastData);
    }
}

void rmissile_act_helper_8006C37C(RMissileWork *work)
{
    SVECTOR   vecs[8];
    POLY_FT4 *pPoly;
    DG_TEX   *pTex;
    int i;
    int inc;
    int offx;
    int offy;
    int width;
    int height;
    int y;
    int rand1;
    int rand2;

    if (work->field_11C > 0)
    {
        inc = 80;
        y = 120;
    }
    else
    {
        inc = 64;
        y = 120;
    }

    pPoly = &work->field_2D8_prim->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;

    for (i = 0; i < 8; i++, pPoly++)
    {
        if (work->field_11C && (i == 0))
        {
            pPoly->tpage &= ~0x60;
            pPoly->tpage |= 0x20;
        }
        else
        {
            pPoly->tpage |= 0x60;
        }

        vecs[i].vx = 0;

        if (work->field_11C)
        {
            vecs[i].vy = 150 + i * inc;
        }
        else
        {
            vecs[i].vy = 250 + i * inc;
        }

        vecs[i].vz = 0;

        work->field_2E4_svector_8Array[i].pad = y;
        y = 15 * y / 16;


        rand1 = GV_RandU_80017090(4) & 1;
        rand2 = GV_RandU_80017090(4);

        pTex = work->field_2DC_tex;

        offx = work->field_2DC_tex->field_8_offx;
        width = work->field_2DC_tex->field_A_width + 1;

        pPoly->u3 = offx + (width << rand1) / 2 - 1;
        pPoly->u1 = offx + (width << rand1) / 2 - 1;

        pPoly->u2 = offx + ((width * rand1) >> 1);
        pPoly->u0 = offx + ((width * rand1) >> 1);


        offy = work->field_2DC_tex->field_9_offy;
        height = work->field_2DC_tex->field_B_height + 1;

        pPoly->v1 = offy + (height * (rand2 / 2)) / 2;
        pPoly->v0 = offy + (height * (rand2 / 2)) / 2;

        pPoly->v3 = offy + (height * (rand2 / 2 + 1)) / 2 - 1;
        pPoly->v2 = offy + (height * (rand2 / 2 + 1)) / 2 - 1;

        pPoly->r0 = 128u - i * 16;
        pPoly->g0 = 128u - i * 16;
        pPoly->b0 = 128u - i * 16;
    }

    DG_SetPos2_8001BC8C(&work->field_20_ctrl.field_0_mov, &work->field_20_ctrl.field_8_rot);
    DG_PutVector_8001BE48(vecs, work->field_2E4_svector_8Array, 8);
}

void rmissile_act_8006C5C4(RMissileWork *work)
{
    GV_PAD *pPad;
    Blast_Data *pBlastData;
    SVECTOR vector;
    SVECTOR vector2;
    MATRIX rotation;

    pPad = &GV_PadData_800B05C0[0];

    if ((GM_PlayerStatus_800ABA50 & 0x8000000) != 0)
    {
        pPad = &GV_PadData_800B05C0[1];
    }

    if ((work->field_324-- > 0) || (work->field_11C < 0 && work->field_11C > -3))
    {
        DG_InvisiblePrim(work->field_2D8_prim);
    }
    else
    {
        DG_VisiblePrim(work->field_2D8_prim);
        rmissile_act_helper_8006C37C(work);
    }

    if (work->field_110 && !work->field_112)
    {
        if (--work->field_110 != 0)
        {
            if (work->field_118 != 0)
            {
                vector2 = work->field_20_ctrl.field_0_mov;
                GV_NearExp2V_8002667C(&vector2.vx, &work->field_100_svector.vx, 3);
                GV_SubVec3_80016D40(&vector2, &work->field_20_ctrl.field_0_mov, &work->field_20_ctrl.field_44_step);
            }
        }
        else
        {
            DG_VisibleObjs(work->field_9C_kmd.objs);
            work->field_120_target.field_2_side = 0;
            GV_SubVec3_80016D40(&work->field_100_svector, &work->field_20_ctrl.field_0_mov, &work->field_20_ctrl.field_44_step);
        }
    }

    if (GM_CurrentWeaponId != 3)
    {
        if (!work->field_112)
        {
            GM_CurrentMap_800AB9B0 = work->field_20_ctrl.field_2C_map->field_0_map_index_bit;
            DG_SetPos2_8001BC8C(&work->field_20_ctrl.field_0_mov, &work->field_20_ctrl.field_8_rot);
            ReadRotMatrix(&rotation);

            if (GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31 | GAME_FLAG_BIT_32)
                || !GM_SnakeCurrentHealth || GM_GameOverTimer_800AB3D4)
            {
                pBlastData = &blast_data_8009F4B8[7];
            #ifdef VR_EXE
                if ((GM_GameStatus_800AB3CC & GAME_FLAG_BIT_31) &&
                    !(GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF) &&
                    !(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_29))
                {
                    pBlastData = &blast_data_8009F4B8[4];
                }
            #endif
            }
            else
            {
                pBlastData = &blast_data_8009F4B8[4];
            }

            NewBlast_8006DFDC(&rotation, pBlastData);
        }

        dword_8009F480 = 0;

        if (GM_Camera_800B77E8.field_22 && GM_PlayerBody_800ABA20)
        {
            DG_InvisibleObjs(GM_PlayerBody_800ABA20->objs);
        }

        work->field_11C = -1;
        GV_DestroyActor_800151C8(&work->field_0_actor);
    }
    else
    {
        rmissile_act_helper_8006BEEC(work);
        rmissile_act_helper_8006C114(work);

        if (!work->field_117)
        {
            gUnkCameraStruct_800B77B8.field_0 = work->field_20_ctrl.field_0_mov;
        }
        else
        {
            vector = work->field_16C_svector;
            GV_NearTimeSV_800268AC(&work->field_16C_svector.vx, &GM_PlayerPosition_800ABA10.vx, work->field_16A, 3);
            gUnkCameraStruct_800B77B8.field_0 = work->field_16C_svector;

            if (work->field_16A > 0)
            {
                work->field_16A--;
            }
        }

        dword_8009F46C = !work->field_117;

        if (work->field_112)
        {
            if (++work->field_118 == 30)
            {
                GV_DestroyActor_800151C8(&work->field_0_actor);
            }
        }
        else
        {
            GM_SetNoise(5, 2, &work->field_20_ctrl.field_0_mov);
            work->field_108_svector = work->field_20_ctrl.field_0_mov;

            GM_ActControl_80025A7C(&work->field_20_ctrl);
            svector_8009F478 = vector2 = work->field_20_ctrl.field_0_mov;

            GM_ActObject2_80034B88((OBJECT *)&work->field_9C_kmd);
            DG_GetLightMatrix2_8001A5D8(&vector2, work->field_C0_light_matrices);

            if (!work->field_117 && !work->field_110)
            {
                if (GM_PlayerBody_800ABA20)
                {
                    DG_VisibleObjs(GM_PlayerBody_800ABA20->objs);
                }

                if (!work->field_113)
                {
                    rmissile_act_helper_8006BE50(work, pPad->dir);
                }
                else
                {
                    rmissile_act_helper_8006BE90(work, pPad->status);
                }
            }

            rmissile_act_helper_8006BFD4(work);

            if (1000 - work->field_118 < 100)
            {
                work->field_20_ctrl.field_8_rot.vy += GV_RandS_800170BC(32) * (work->field_118 - 900) / 32;
                work->field_11C = GV_RandU_80017090(2);
            }

            if (work->field_117 == 1)
            {
                work->field_20_ctrl.field_8_rot.vy += GV_RandS_800170BC(128);
            }

            GV_DirVec2_80016F24(work->field_20_ctrl.field_8_rot.vy, work->field_11A, &work->field_20_ctrl.field_44_step);
            rmissile_act_helper_8006BD24(work, pPad->status);
            GM_Target_SetVector_8002D500(&work->field_120_target, &vector2);
        }
    }
}

void rmissile_kill_8006CB40(RMissileWork *work)
{
    DG_PRIM *prim;

    GM_FreeControl_800260CC(&work->field_20_ctrl);
    GM_FreeObject_80034BF8((OBJECT *)&work->field_9C_kmd);

    if (work->field_174_polys_2Array[0])
    {
        GV_DelayedFree_80016254(work->field_174_polys_2Array[0]);
        dword_8009F46C = 0;
    }
    else
    {
        dword_8009F46C = 0;
    }

    dword_8009F470 = 0;
    Nik_Blast_8009F484 = 0;

    prim = work->field_2D8_prim;

    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    if (!work->field_117)
    {
        rmissile_8006B924(work);
    }
}

int rmissile_loader_helper3_8006CBD8(RMissileWork *work, int whichSide)
{
    TARGET *target = &work->field_120_target;

    GM_SetTarget_8002DC74(target, 0x4, whichSide, &svector_8009F488);
    GM_Target_8002DCCC(target, 0, -1, 1, 0, &DG_ZeroVector_800AB39C);
    GM_Target_SetVector_8002D500(target, &work->field_20_ctrl.field_0_mov);
    return 0;
}

int rmissile_loader_helper2_8006CC50(RMissileWork *work)
{
    POLY_F4 *poly;
    POLY_F4 *poly2;

    work->field_174_polys_2Array[0] = poly = GV_Malloc_8001620C(sizeof(POLY_F4) * 2);

    if (!poly)
    {
        return -1;
    }

    work->field_174_polys_2Array[1] = poly + 1;

    LSTORE(0x8AB89E, &poly[0].r0);
    LSTORE(0x8AB89E, &poly[1].r0);

    poly2 = poly + 1;

    SetPolyF4(poly);
    SetPolyF4(poly2);
    SetSemiTrans(poly, 1);
    SetSemiTrans(poly2, 1);

    poly2->x2 = 31;
    poly2->x0 = 31;
    poly->x2 = 31;
    poly->x0 = 31;
    poly2->y1 = 39;
    poly2->y0 = 39;
    poly->y1 = 39;
    poly->y0 = 39;
    poly2->y3 = 49;
    poly2->y2 = 49;
    poly->y3 = 49;
    poly->y2 = 49;

    return 0;
}

static inline void rmissile_loader_helper_helper_8006CD1C_set_poly(POLY_FT4 *pPoly, DG_TEX *pTex)
{
    int u, v, w, h;

    setPolyFT4(pPoly);
    setSemiTrans(pPoly, 1);

    u = pTex->field_8_offx;
    w = (pTex->field_A_width + 1) / 2;
    pPoly->u2 = u;
    pPoly->u0 = u;
    u += w;
    pPoly->u3 = u - 1;
    pPoly->u1 = u - 1;

    v = pTex->field_9_offy;
    h = (pTex->field_B_height + 1) / 2;
    pPoly->v1 = v;
    pPoly->v0 = v;
    v += h;
    pPoly->v3 = v - 1;
    pPoly->v2 = v - 1;

    pPoly->tpage = pTex->field_4_tPage;
    pPoly->clut = pTex->field_6_clut;
}

void rmissile_loader_helper_helper_8006CD1C(POLY_FT4 *pPoly, DG_TEX *pTex, int primCount)
{
    rmissile_loader_helper_helper_8006CD1C_set_poly(pPoly, pTex);
    pPoly->tpage = (pPoly->tpage & 0xff9f) | 0x20;

    pPoly->r0 = 0;
    pPoly->g0 = 0;
    pPoly->b0 = 0;

    pPoly++;
    primCount--;

    while (primCount-- != 0)
    {
        rmissile_loader_helper_helper_8006CD1C_set_poly(pPoly, pTex);
        pPoly->tpage = pPoly->tpage | 0x60;

        pPoly->r0 = 0;
        pPoly->g0 = 0;
        pPoly->b0 = 0;

        pPoly++;
    }
}

void rmissile_loader_helper_8006CE54(RMissileWork *work)
{
    int hash;
    DG_TEX *tex;
    SVECTOR *vec;
    DG_PRIM *prim;
    int count;

    hash = GV_StrCode_80016CCC("socom_f");
    tex = DG_GetTexture_8001D830(hash);

    work->field_2DC_tex = tex;
    prim = work->field_2D8_prim  = Takabe_MakeIndividualRect3DPrim_800793E8(8, work->field_2E4_svector_8Array);

    rmissile_loader_helper_helper_8006CD1C(&prim->field_40_pBuffers[0]->poly_ft4, tex, 8);
    rmissile_loader_helper_helper_8006CD1C(&prim->field_40_pBuffers[1]->poly_ft4, tex, 8);

    prim->world = DG_ZeroMatrix_8009D430;
    prim->field_2E_k500 = 100;

    vec = work->field_2E4_svector_8Array;

    for (count = 8; count > 0; count--)
    {
        (vec++)->pad = 0;
    }
}

static inline int rmissile_loader_8006CF44_get_field_59(void)
{
    return 8;
}

int rmissile_loader_8006CF44(RMissileWork *work, MATRIX *pMtx, int whichSide)
{
    CONTROL        *ctrl;
    OBJECT_NO_ROTS *kmd;

    dword_8009F46C = 1;
    dword_8009F470 = 1;

    rmissile_loader_helper4_8006B800(work);

    ctrl = &work->field_20_ctrl;

    if (GM_InitLoader_8002599C(ctrl, 0x50AE, 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlMatrix_80026154(ctrl, pMtx);

    work->field_100_svector = ctrl->field_0_mov;
    work->field_110 = 8;
    ctrl->field_0_mov = GM_PlayerPosition_800ABA10;
    work->field_108_svector = GM_PlayerPosition_800ABA10;
    svector_8009F478 = GM_PlayerPosition_800ABA10;

    GM_ConfigControlHazard_8002622C(ctrl, 400, 0xC8, 0xC8);
    ctrl->field_59 = rmissile_loader_8006CF44_get_field_59();
    GM_ConfigControlTrapCheck_80026308(ctrl);

    kmd = &work->field_9C_kmd;
    ctrl->field_4C_turn.vz = 0;
    ctrl->field_8_rot.vz = 0;
    ctrl->field_55_skip_flag |= CTRL_SKIP_NEAR_CHECK;

    GM_InitObjectNoRots_800349B0(kmd, 0x9A90, 0x36D, 0);

    if (!kmd->objs)
    {
        return -1;
    }

    GM_ConfigObjectLight_80034C44((OBJECT *)kmd, work->field_C0_light_matrices);

    if (rmissile_loader_helper3_8006CBD8(work, whichSide) < 0)
    {
        return -1;
    }

    if (rmissile_loader_helper2_8006CC50(work) < 0)
    {
        return -1;
    }

    DG_InvisibleObjs(work->field_9C_kmd.objs);
    work->field_11C = -1;
    work->field_324 = 10;
    rmissile_loader_helper_8006CE54(work);
    return 0;
}

GV_ACT *NewRMissile_8006D124(MATRIX *pMtx, int whichSide)
{
    RMissileWork *work;

    work = (RMissileWork *)GV_NewActor_800150E4(6, sizeof(RMissileWork));

    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)&rmissile_act_8006C5C4,
                                  (TActorFunction)&rmissile_kill_8006CB40, "rmissile.c");

        if (rmissile_loader_8006CF44(work, pMtx, whichSide) < 0)
        {
            GV_DestroyActor_800151C8(&work->field_0_actor);
            return 0;
        }

        work->field_111 = 30;
        work->field_112 = 0;
        work->field_113 = 0;
        work->field_117 = 0;
        work->field_114 = 0;
        work->field_115 = 0;
        work->field_116 = 0;
        dword_8009F480 = 0;
        work->field_118 = 0;
        work->field_11A = 0;
        work->field_11C = 0;
        work->field_168 = 0;
        Nik_Blast_8009F484 = 0;
    }

    return &work->field_0_actor;
}
