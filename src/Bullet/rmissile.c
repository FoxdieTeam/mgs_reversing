#include "Equip/Takabe.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "Menu/menuman.h"
#include "Thing/sgtrect3.h"
#include "Thing/sight.h"
#include "libhzd/libhzd.h"
#include "blast.h"
#include "psyq.h"
#include "rmissile.h"
#include "map/map.h"
#include "libgcl/hash.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

// nikita missile

extern MATRIX           DG_ZeroMatrix_8009D430;
extern SVECTOR          DG_ZeroVector_800AB39C;
extern SVECTOR          svector_8009F488;
extern int              dword_8009F470;
extern GV_PAD           GV_PadData_800B05C0[4];
extern int              dword_8009F46C;
extern SVECTOR          svector_8009F478;
extern OBJECT *         dword_800ABA20;
extern int              GM_GameOverTimer_800AB3D4;
extern SVECTOR          svector_800ABA10;
extern int              GV_Clock_800AB920;
extern int              dword_8009F480;
extern Blast_Data       blast_data_8009F508;
extern Blast_Data       blast_data_8009F544;
extern int              GM_CurrentMap_800AB9B0;
extern int              dword_8009F474;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern GM_Target        *target_800BDF00;
extern short            Nik_Blast_8009F484;
extern int              dword_8009F604;
extern int              dword_800BDEF8[];
extern int              GM_GameStatus_800AB3CC;
extern GM_Control      *gSnaControl_800AB9F4;
extern int              GM_CameraTrackSave_800AB42C;
extern SVECTOR          GM_CameraRotateSave_800AB430;
extern int              GM_event_camera_flag_800ABA9C;
extern GM_Camera        GM_Camera_800B77E8;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern CAMERA           GM_CameraList_800B7718[8];

extern const char aEnemy[];     // = "ENEMY\n"
extern const char aD_4[];       // = "%d"
extern const char aSocomF[];    // = "socom_f"
extern const char rRmissileC[]; // = "rmissile.c"

void rmissile_loader_helper4_8006B800(Actor_rmissile *pActor)
{
    GV_CopyMemory_800160D8(&GM_Camera_800B77E8,           &pActor->field_17C_camera,  sizeof(pActor->field_17C_camera));
    GV_CopyMemory_800160D8(&gUnkCameraStruct_800B77B8,    &pActor->field_1F8,         sizeof(pActor->field_1F8));
    GV_CopyMemory_800160D8(GM_CameraList_800B7718,        &pActor->field_228_camera,  sizeof(pActor->field_228_camera));
    GV_CopyMemory_800160D8(&GM_CameraRotateSave_800AB430, &pActor->field_2CC_svector, sizeof(pActor->field_2CC_svector));

    pActor->field_2C8 = GM_CameraTrackSave_800AB42C;
    pActor->field_2D4 = GM_event_camera_flag_800ABA9C;
}

void rmissile_8006B888(Actor_rmissile *pActor)
{
    GV_CopyMemory_800160D8(&pActor->field_17C_camera,  &GM_Camera_800B77E8,           sizeof(pActor->field_17C_camera));
    GV_CopyMemory_800160D8(&pActor->field_1F8,         &gUnkCameraStruct_800B77B8,    sizeof(pActor->field_1F8));
    GV_CopyMemory_800160D8(&pActor->field_228_camera,  &GM_CameraList_800B7718,       sizeof(pActor->field_228_camera));
    GV_CopyMemory_800160D8(&pActor->field_2CC_svector, &GM_CameraRotateSave_800AB430, sizeof(pActor->field_2CC_svector));

    GM_CameraTrackSave_800AB42C = pActor->field_2C8;
    GM_event_camera_flag_800ABA9C = pActor->field_2D4;

    sub_800309B4(2, 30);
    GM_CameraEventReset_800309A8();
}

void rmissile_8006B924(Actor_rmissile *pActor)
{
    GM_Control *ctrl;

    ctrl = &pActor->field_20_ctrl;
    ctrl->field_55_flags |= CONTROL_FLAG_UNK2;

    rmissile_8006B888(pActor);
    GM_GameStatus_800AB3CC &= ~0x40;
    sub_8002A258(ctrl->field_2C_map->field_8_hzd, &ctrl->field_10_pStruct_hzd_unknown);

    ctrl = gSnaControl_800AB9F4;

    if (ctrl)
    {
        HZD_ReExecEvent_8002A1F4(ctrl->field_2C_map->field_8_hzd, &ctrl->field_10_pStruct_hzd_unknown, 0x102);
    }
}

void rmissile_act_helper_helper_8006B9B0(Actor_rmissile *pActor)
{
    Nik_Blast_8009F484 = 1;

    if (dword_8009F604 != SGT_NIKITA)
    {
        NewSight_80071CDC(SGT_NIKITA, SGT_NIKITA, &Nik_Blast_8009F484, 1, 0);
    }

    GM_Camera_800B77E8.field_22 = 1;

    if (pActor->field_113 == 0)
    {
        pActor->field_113 = 1;
        dword_800BDEF8[0] = 0x5A875D;
        dword_800BDEF8[1] = 0xC1A80;
        sgtrect3_init_80071010(&Nik_Blast_8009F484, 1, dword_800BDEF8, 0);
        GM_Sound_80032968(0, 0x3F, 0x15);
    }
}

void rmissile_act_helper_helper_8006BA70(Actor_rmissile *pActor)
{
    if (!target_800BDF00)
    {
        pActor->field_168 = 0;
        return;
    }

    pActor->field_168++;

    if (pActor->field_168 <= 16)
    {
        return;

    }

    if (pActor->field_168 == 32)
    {
        pActor->field_168 = 0;
    }

    if (!(GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000))
    {
        menu_Color_80038B4C(158, 184, 138);
        menu_Text_XY_Flags_80038B34(116, 98, 0);
        menu_Text_80038C38(aEnemy);
        menu_Text_Init_80038B98();
    }
}

void rmissile_act_helper_helper_8006BB10(Actor_rmissile *pActor)
{
    int var_a1;
    unsigned int *pOt;
    POLY_F4 *pPoly;
    GM_Control ctrl;

    var_a1 = ((1000 - pActor->field_118) * 60) / 1000;

    pOt = (unsigned int *)DG_Chanl(1)->mOrderingTables[GV_Clock_800AB920];
    pPoly = pActor->field_174_polys_2Array[GV_Clock_800AB920];

    if (var_a1 > 60)
    {
        var_a1 = 60;
    }

    pPoly->x3 = var_a1 + 31;
    pPoly->x1 = var_a1 + 31;

    if (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000)
    {
        return;
    }

    if (var_a1 < 15)
    {
        pPoly->r0 = 212;
        pPoly->g0 = 78;
        pPoly->b0 = 78;

        if (!(pActor->field_118 % 15))
        {
            GM_Sound_80032968(0, 63, 116);
        }
    }

    addPrim(pOt, pPoly);
    ctrl = pActor->field_20_ctrl;

    menu_Text_XY_Flags_80038B34(8, 136, 0);
    menu_Text_80038C38(aD_4, ctrl.field_0_position.vx);

    menu_Text_XY_Flags_80038B34(8, 144, 0);
    menu_Text_80038C38(aD_4, ctrl.field_0_position.vy);

    menu_Text_XY_Flags_80038B34(8, 152, 0);
    menu_Text_80038C38(aD_4, ctrl.field_0_position.vz);

    menu_Text_Init_80038B98();
}

void rmissile_act_helper_8006BD24(Actor_rmissile *pActor, int arg1)
{
    if (pActor->field_112 || pActor->field_117 || pActor->field_110)
    {
        return;
    }

    if (arg1 & 0x10)
    {
        rmissile_act_helper_helper_8006B9B0(pActor);

        gUnkCameraStruct_800B77B8.field_28.vx = 0;
        gUnkCameraStruct_800B77B8.field_28.vy = pActor->field_20_ctrl.field_8_rotator.vy;
        gUnkCameraStruct_800B77B8.field_28.vz = 0;

        DG_InvisibleObjs(pActor->field_9C_kmd.objs);

        pActor->field_11C = -2;

        if (pActor->field_114 < 16)
        {
            pActor->field_114++;
            return;
        }

        rmissile_act_helper_helper_8006BB10(pActor);
        rmissile_act_helper_helper_8006BA70(pActor);
        return;
    }

    if (pActor->field_113 != 0)
    {
        pActor->field_115 = 5;
    }

    pActor->field_114 = 0;
    pActor->field_113 = 0;

    GM_Camera_800B77E8.field_22 = 0;
    Nik_Blast_8009F484 = 0;

    if (pActor->field_115)
    {
        pActor->field_115--;

        if (!pActor->field_115)
        {
            DG_VisibleObjs(pActor->field_9C_kmd.objs);
        }
    }
}

void rmissile_act_helper_8006BE50(Actor_rmissile *pActor, int arg1)
{
    if (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK20000000)
    {
        return;
    }

    if (arg1 >= 0 && pActor->field_20_ctrl.field_4C_turn_vec.vy != arg1)
    {
        pActor->field_111 = 30;
        pActor->field_20_ctrl.field_4C_turn_vec.vy = arg1;
    }
}

void rmissile_act_helper_8006BE90(Actor_rmissile *pActor, int arg1)
{
    if (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK20000000)
    {
        return;
    }

    if (arg1 & 0x8000)
    {
        pActor->field_111 = 30;
        pActor->field_20_ctrl.field_4C_turn_vec.vy += 64;
        pActor->field_20_ctrl.field_4C_turn_vec.vy &= 0xFFF;
    }

    if (arg1 & 0x2000)
    {
        pActor->field_111 = 30;
        pActor->field_20_ctrl.field_4C_turn_vec.vy -= 64;
        pActor->field_20_ctrl.field_4C_turn_vec.vy &= 0xFFF;
    }
}

void rmissile_act_helper_8006BEEC(Actor_rmissile *pActor)
{
    if (pActor->field_117)
    {
        return;
    }

    if (GM_PlayerStatus_800ABA50 & 0x2100 || dword_8009F474 == 1 || GM_GameStatus_800AB3CC & 0x800001)
    {
        pActor->field_117 = 1;
        pActor->field_16A = 15;
        pActor->field_16C_svector = pActor->field_20_ctrl.field_0_position;
        pActor->field_113 = 0;

        GM_Camera_800B77E8.field_22 = 0;
        Nik_Blast_8009F484 = 0;

        if (!pActor->field_112)
        {
            DG_VisibleObjs(pActor->field_9C_kmd.objs);
        }

        dword_8009F474 = 0;
        rmissile_8006B924(pActor);
    }
}

void rmissile_act_helper_8006BFD4(Actor_rmissile *pActor)
{
    if (pActor->field_111)
    {
        pActor->field_111--;

        if (!pActor->field_111)
        {
            GM_Sound_80032968(0, 63, 77);
            pActor->field_116 = 12;
        }

        pActor->field_11A = 50;

        if (!pActor->field_112)
        {
            pActor->field_11C = 0;
        }
    }
    else
    {
        if (pActor->field_116)
        {
            pActor->field_116--;
            gUnkCameraStruct_800B77B8.field_0.vy += GV_RandS_800170BC(512) * pActor->field_116 / 32;
        }

        pActor->field_11A = 200;

        if (!pActor->field_112)
        {
            pActor->field_11C = 8;
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
            if (message->message[0] == 0x3223)
            {
                return 1;
            }
        }
    }

    return 0;
}

void rmissile_act_helper_8006C114(Actor_rmissile *pActor)
{
    SVECTOR *pPosition;
    int found;
    MATRIX rotation;
    Blast_Data *pBlastData;

    if (pActor->field_112)
    {
        return;
    }

    pPosition = &pActor->field_20_ctrl.field_0_position;
    found = rmissile_act_helper_helper_8006C0A4();

    if (pActor->field_20_ctrl.field_58 <= 0 && !(pActor->field_20_ctrl.field_57 & 2))
    {
        if (pPosition->vy - pActor->field_108_svector.vy < 200)
        {
            if (++pActor->field_118 != 1000 && !sub_8002D7DC(&pActor->field_120_target) && !dword_8009F480 && !found)
            {
                if (!sub_80029098(pActor->field_20_ctrl.field_2C_map->field_8_hzd, pPosition, 250, 15, 8))
                {
                    if (abs(pPosition->vx) <= 30000 && abs(pPosition->vy) <= 30000 && abs(pPosition->vz) <= 30000)
                    {
                        return;
                    }
                }
            }
        }
    }

    if (GM_Camera_800B77E8.field_22 && !pActor->field_117)
    {
        GM_Camera_800B77E8.field_22 = 0;
        Nik_Blast_8009F484 = 0;
    }

    pActor->field_113 = 0;
    dword_8009F480 = 0;
    pActor->field_112 = 1U;
    pActor->field_118 = found ? 28 : 0;
    pActor->field_20_ctrl.field_44_movementVector = DG_ZeroVector_800AB39C;
    DG_InvisibleObjs(pActor->field_9C_kmd.objs);
    pActor->field_9C_kmd.objs->group_id = 0;
    pActor->field_11C = -2;

    if (!found)
    {
        DG_SetPos2_8001BC8C(pPosition, &pActor->field_20_ctrl.field_8_rotator);
        ReadRotMatrix_80092DD8(&rotation);

        GM_CurrentMap_800AB9B0 = pActor->field_20_ctrl.field_2C_map->field_0_map_index_bit;

        pBlastData = (GM_GameStatus_800AB3CC & 0xd0000000) ? &blast_data_8009F544 : &blast_data_8009F508;
        NewBlast_8006DFDC(&rotation, pBlastData);
    }
}

void rmissile_act_helper_8006C37C(Actor_rmissile *pActor)
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

    if (pActor->field_11C > 0)
    {
        inc = 80;
        y = 120;
    }
    else
    {
        inc = 64;
        y = 120;
    }

    pPoly = &pActor->field_2D8_prim->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;

    for (i = 0; i < 8; i++, pPoly++)
    {
        if (pActor->field_11C && (i == 0))
        {
            pPoly->tpage &= ~0x60;
            pPoly->tpage |= 0x20;
        }
        else
        {
            pPoly->tpage |= 0x60;
        }

        vecs[i].vx = 0;

        if (pActor->field_11C)
        {
            vecs[i].vy = 150 + i * inc;
        }
        else
        {
            vecs[i].vy = 250 + i * inc;
        }

        vecs[i].vz = 0;

        pActor->field_2E4_svector_8Array[i].pad = y;
        y = 15 * y / 16;


        rand1 = GV_RandU_80017090(4) & 1;
        rand2 = GV_RandU_80017090(4);

        pTex = pActor->field_2DC_tex;

        offx = pActor->field_2DC_tex->field_8_offx;
        width = pActor->field_2DC_tex->field_A_width + 1;

        pPoly->u3 = offx + (width << rand1) / 2 - 1;
        pPoly->u1 = offx + (width << rand1) / 2 - 1;

        pPoly->u2 = offx + ((width * rand1) >> 1);
        pPoly->u0 = offx + ((width * rand1) >> 1);


        offy = pActor->field_2DC_tex->field_9_offy;
        height = pActor->field_2DC_tex->field_B_height + 1;

        pPoly->v1 = offy + (height * (rand2 / 2)) / 2;
        pPoly->v0 = offy + (height * (rand2 / 2)) / 2;

        pPoly->v3 = offy + (height * (rand2 / 2 + 1)) / 2 - 1;
        pPoly->v2 = offy + (height * (rand2 / 2 + 1)) / 2 - 1;

        pPoly->r0 = 128u - i * 16;
        pPoly->g0 = 128u - i * 16;
        pPoly->b0 = 128u - i * 16;
    }

    DG_SetPos2_8001BC8C(&pActor->field_20_ctrl.field_0_position, &pActor->field_20_ctrl.field_8_rotator);
    DG_PutVector_8001BE48(vecs, pActor->field_2E4_svector_8Array, 8);
}

void rmissile_act_8006C5C4(Actor_rmissile *pActor)
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

    if ((pActor->field_324-- > 0) || (pActor->field_11C < 0 && pActor->field_11C > -3))
    {
        DG_InvisiblePrim(pActor->field_2D8_prim);
    }
    else
    {
        DG_VisiblePrim(pActor->field_2D8_prim);
        rmissile_act_helper_8006C37C(pActor);
    }

    if (pActor->field_110 && !pActor->field_112)
    {
        if (--pActor->field_110 != 0)
        {
            if (pActor->field_118 != 0)
            {
                vector2 = pActor->field_20_ctrl.field_0_position;
                GV_NearExp2V_8002667C(&vector2.vx, &pActor->field_100_svector.vx, 3);
                GV_SubVec3_80016D40(&vector2, &pActor->field_20_ctrl.field_0_position, &pActor->field_20_ctrl.field_44_movementVector);
            }
        }
        else
        {
            DG_VisibleObjs(pActor->field_9C_kmd.objs);
            pActor->field_120_target.field_2_side = 0;
            GV_SubVec3_80016D40(&pActor->field_100_svector, &pActor->field_20_ctrl.field_0_position, &pActor->field_20_ctrl.field_44_movementVector);
        }
    }

    if (GM_CurrentWeaponId != 3)
    {
        if (!pActor->field_112)
        {
            GM_CurrentMap_800AB9B0 = pActor->field_20_ctrl.field_2C_map->field_0_map_index_bit;
            DG_SetPos2_8001BC8C(&pActor->field_20_ctrl.field_0_position, &pActor->field_20_ctrl.field_8_rotator);
            ReadRotMatrix_80092DD8(&rotation);

            if (GM_GameStatus_800AB3CC & 0xd0000000 || !GM_SnakeCurrentHealth || GM_GameOverTimer_800AB3D4)
            {
                pBlastData = &blast_data_8009F544;
            }
            else
            {
                pBlastData = &blast_data_8009F508;
            }

            NewBlast_8006DFDC(&rotation, pBlastData);
        }

        dword_8009F480 = 0;

        if (GM_Camera_800B77E8.field_22 && dword_800ABA20)
        {
            DG_InvisibleObjs(dword_800ABA20->objs);
        }

        pActor->field_11C = -1;
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }
    else
    {
        rmissile_act_helper_8006BEEC(pActor);
        rmissile_act_helper_8006C114(pActor);

        if (!pActor->field_117)
        {
            gUnkCameraStruct_800B77B8.field_0 = pActor->field_20_ctrl.field_0_position;
        }
        else
        {
            vector = pActor->field_16C_svector;
            GV_NearTimeSV_800268AC(&pActor->field_16C_svector.vx, &svector_800ABA10.vx, pActor->field_16A, 3);
            gUnkCameraStruct_800B77B8.field_0 = pActor->field_16C_svector;

            if (pActor->field_16A > 0)
            {
                pActor->field_16A--;
            }
        }

        dword_8009F46C = !pActor->field_117;

        if (pActor->field_112)
        {
            if (++pActor->field_118 == 30)
            {
                GV_DestroyActor_800151C8(&pActor->field_0_actor);
            }
        }
        else
        {
            GM_SetNoise(5, 2, &pActor->field_20_ctrl.field_0_position);
            pActor->field_108_svector = pActor->field_20_ctrl.field_0_position;

            GM_ActControl_80025A7C(&pActor->field_20_ctrl);
            svector_8009F478 = vector2 = pActor->field_20_ctrl.field_0_position;

            GM_ActObject2_80034B88(&pActor->field_9C_kmd);
            DG_GetLightMatrix2_8001A5D8(&vector2, pActor->field_C0_light_matrices);

            if (!pActor->field_117 && !pActor->field_110)
            {
                if (dword_800ABA20)
                {
                    DG_VisibleObjs(dword_800ABA20->objs);
                }

                if (!pActor->field_113)
                {
                    rmissile_act_helper_8006BE50(pActor, pPad->dir);
                }
                else
                {
                    rmissile_act_helper_8006BE90(pActor, pPad->status);
                }
            }

            rmissile_act_helper_8006BFD4(pActor);

            if (1000 - pActor->field_118 < 100)
            {
                pActor->field_20_ctrl.field_8_rotator.vy += GV_RandS_800170BC(32) * (pActor->field_118 - 900) / 32;
                pActor->field_11C = GV_RandU_80017090(2);
            }

            if (pActor->field_117 == 1)
            {
                pActor->field_20_ctrl.field_8_rotator.vy += GV_RandS_800170BC(128);
            }

            GV_DirVec2_80016F24(pActor->field_20_ctrl.field_8_rotator.vy, pActor->field_11A, &pActor->field_20_ctrl.field_44_movementVector);
            rmissile_act_helper_8006BD24(pActor, pPad->status);
            GM_Target_SetVector_8002D500(&pActor->field_120_target, &vector2);
        }
    }
}

void rmissile_kill_8006CB40(Actor_rmissile *pActor)
{
    DG_PRIM *prim;

    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_kmd);

    if (pActor->field_174_polys_2Array[0])
    {
        GV_DelayedFree_80016254(pActor->field_174_polys_2Array[0]);
        dword_8009F46C = 0;
    }
    else
    {
        dword_8009F46C = 0;
    }

    dword_8009F470 = 0;
    Nik_Blast_8009F484 = 0;

    prim = pActor->field_2D8_prim;

    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    if (!pActor->field_117)
    {
        rmissile_8006B924(pActor);
    }
}

int rmissile_loader_helper3_8006CBD8(Actor_rmissile *pActor, int whichSide)
{
    GM_Target *target = &pActor->field_120_target;

    GM_SetTarget_8002DC74(target, 0x4, whichSide, &svector_8009F488);
    GM_Target_8002DCCC(target, 0, -1, 1, 0, &DG_ZeroVector_800AB39C);
    GM_Target_SetVector_8002D500(target, &pActor->field_20_ctrl.field_0_position);
    return 0;
}

int rmissile_loader_helper2_8006CC50(Actor_rmissile *pActor)
{
    POLY_F4 *poly;
    POLY_F4 *poly2;

    pActor->field_174_polys_2Array[0] = poly = GV_Malloc_8001620C(sizeof(POLY_F4) * 2);

    if (!poly)
    {
        return -1;
    }

    pActor->field_174_polys_2Array[1] = poly + 1;

    LSTORE(0x8AB89E, &poly[0].r0);
    LSTORE(0x8AB89E, &poly[1].r0);

    poly2 = poly + 1;

    SetPolyF4_80092488(poly);
    SetPolyF4_80092488(poly2);
    SetSemiTrans_80092458(poly, 1);
    SetSemiTrans_80092458(poly2, 1);

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

void rmissile_loader_helper_8006CE54(Actor_rmissile *pActor)
{
    int hash;
    DG_TEX *tex;
    SVECTOR *vec;
    DG_PRIM *prim;
    int count;

    hash = GV_StrCode_80016CCC(aSocomF);
    tex = DG_GetTexture_8001D830(hash);

    pActor->field_2DC_tex = tex;
    prim = pActor->field_2D8_prim  = Takabe_MakeIndividualRect3DPrim_800793E8(8, pActor->field_2E4_svector_8Array);

    rmissile_loader_helper_helper_8006CD1C(&prim->field_40_pBuffers[0]->poly_ft4, tex, 8);
    rmissile_loader_helper_helper_8006CD1C(&prim->field_40_pBuffers[1]->poly_ft4, tex, 8);

    prim->world = DG_ZeroMatrix_8009D430;
    prim->field_2E_k500 = 100;

    vec = pActor->field_2E4_svector_8Array;

    for (count = 8; count > 0; count--)
    {
        (vec++)->pad = 0;
    }
}

static inline int rmissile_loader_8006CF44_get_field_59(void)
{
    return 8;
}

int rmissile_loader_8006CF44(Actor_rmissile *pActor, MATRIX *pMtx, int whichSide)
{
    GM_Control *ctrl;
    OBJECT *kmd;

    dword_8009F46C = 1;
    dword_8009F470 = 1;

    rmissile_loader_helper4_8006B800(pActor);

    ctrl = &pActor->field_20_ctrl;

    if (Res_Control_init_loader_8002599C(ctrl, 0x50AE, 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlMatrix_80026154(ctrl, pMtx);

    pActor->field_100_svector = ctrl->field_0_position;
    pActor->field_110 = 8;
    ctrl->field_0_position = svector_800ABA10;
    pActor->field_108_svector = svector_800ABA10;
    svector_8009F478 = svector_800ABA10;

    GM_ConfigControlHazard_8002622C(ctrl, 400, 0xC8, 0xC8);
    ctrl->field_59 = rmissile_loader_8006CF44_get_field_59();
    GM_ConfigControlTrapCheck_80026308(ctrl);

    kmd = &pActor->field_9C_kmd;
    ctrl->field_4C_turn_vec.vz = 0;
    ctrl->field_8_rotator.vz = 0;
    ctrl->field_55_flags |= 4;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)kmd, 0x9A90, 0x36D, 0);

    if (!kmd->objs)
    {
        return -1;
    }

    GM_ConfigObjectLight_80034C44(kmd, pActor->field_C0_light_matrices);

    if (rmissile_loader_helper3_8006CBD8(pActor, whichSide) < 0)
    {
        return -1;
    }

    if (rmissile_loader_helper2_8006CC50(pActor) < 0)
    {
        return -1;
    }

    DG_InvisibleObjs(pActor->field_9C_kmd.objs);
    pActor->field_11C = -1;
    pActor->field_324 = 10;
    rmissile_loader_helper_8006CE54(pActor);
    return 0;
}

Actor_rmissile * NewRMissile_8006D124(MATRIX *pMtx, int whichSide)
{
    Actor_rmissile *actor;

    actor = (Actor_rmissile *)GV_NewActor_800150E4(6, sizeof(Actor_rmissile));

    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)&rmissile_act_8006C5C4,
                                  (TActorFunction)&rmissile_kill_8006CB40, rRmissileC);

        if (rmissile_loader_8006CF44(actor, pMtx, whichSide) < 0)
        {
            GV_DestroyActor_800151C8(&actor->field_0_actor);
            return 0;
        }

        actor->field_111 = 30;
        actor->field_112 = 0;
        actor->field_113 = 0;
        actor->field_117 = 0;
        actor->field_114 = 0;
        actor->field_115 = 0;
        actor->field_116 = 0;
        dword_8009F480 = 0;
        actor->field_118 = 0;
        actor->field_11A = 0;
        actor->field_11C = 0;
        actor->field_168 = 0;
        Nik_Blast_8009F484 = 0;
    }

    return actor;
}
