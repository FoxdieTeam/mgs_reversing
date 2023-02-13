#include "jpegcam.h"
#include "psyq.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "Menu/menuman.h"
#include "libgcl/hash.h"

#pragma INCLUDE_ASM("asm/Equip/jpegcam_unk1_80063704.s") // 388 bytes

extern char aPHOTO[];    // "PHOTO %02d\n"
extern char aJpegcamC[]; // "jpegcam.c";
extern const char aGoggles[];

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int DG_CurrentGroupID_800AB968;
extern GM_Camera GM_Camera_800B77E8;
extern GM_Control *gSnaControl_800AB9F4;
extern int   dword_8009F604;
extern int GM_LoadRequest_800AB3D0;
extern int     GM_GameOverTimer_800AB3D4;

extern GV_PAD GV_PadData_800B05C0[4];
extern TMat8x8B gJpegcamMatrix1_8009F36C;
extern TMat8x8B gJpegcamMatrix2_800BDCD8;



extern UnkCameraStruct gUnkCameraStruct_800B77B8;
extern OBJECT         *dword_800ABA20;
extern SVECTOR         dword_8009F3AC;
extern int     GM_Photocode_800ABA04;
extern SVECTOR GM_PhotoViewPos_800ABA48;

extern const char aSinreiSyasinCh[]; // = "Sinrei Syasin Check Start\n"
extern const char aHereIsSinreiSp[]; // = "Here is Sinrei Spot!\n"
extern const char aGmPhotocodeD[];   // = "GM_Photocode = %d\n"
extern const char aPointCheck[];     // = "Point Check\n"
extern const char aResultD[];        // = "Result = %d\n"
extern const char aNotSinreiSpot[];  // = "Not Sinrei Spot!\n"

extern int   GV_PauseLevel_800AB928;
extern int   dword_800BDCC8;
extern int   dword_800BDCCC;
extern int   dword_800BDCD0;
extern int   DG_UnDrawFrameCount_800AB380;

extern menu_save_mode_data stru_8009F2D8;
extern const char aZoom4d[];
extern const char aAngle4d4d[];

extern UnkCameraStruct gUnkCameraStruct_800B77B8;

void jpegcam_unk2_80063888(char *param_1, int param_2)
{
    sprintf_8008E878(param_1, aPHOTO, *(char *)(param_2 + 6) - 0x40);
}

#pragma INCLUDE_ASM("asm/Equip/jpegcam_unk3_800638B4.s")                                      // 120 bytes

void jpegcam_act_helper2_helper_8006392C()
{
    // Copy matrix gJpegcamMatrix1_8009F36C transposed to gJpegcamMatrix2_800BDCD8

    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            gJpegcamMatrix2_800BDCD8[j][i] = gJpegcamMatrix1_8009F36C[i][j];
        }
    }
}

void jpegcam_act_helper3_helper_helper_helper3_80063988(unsigned short *param_1, char *param_2)
{
    int i;

    for (i = 0; i < 0x100; i++, param_2 += 4, param_1++)
    {
        param_2[2] = (*param_1 << 3) & 0xF8;
        param_2[1] = (*param_1 >> 2) & 0xF8;
        param_2[0] = (*param_1 >> 7) & 0xF8;
    }
}

void jpegcam_act_helper3_helper_helper_helper2_helper_800639E8(char *param_1, char *param_2, char *param_3,
                                                               char *param_4)
{
    int   val1;
    int   val2;
    int   val3;
    char *param_1_copy;
    int   iters;

    iters = 0;
    param_1_copy = param_1;
    do
    {
        val1 = (int)param_1_copy[1];
        val3 = (int)param_1_copy[2];
        val2 = (int)*param_1;
        *param_2 = (char)((val2 * 299 + val1 * 0x24b + val3 * 0x72) / 1000 + 0x80);

        *param_3 = (char)((val2 * -0x697 + val1 * -0xcf1 + val3 * 5000) / 10000);

        *param_4 = (char)((val2 * 5000 - val1 * 0x105b - val3 * 0x32d) / 10000);
        iters = iters + 1;
        param_1_copy = param_1_copy + 4;
        param_1 = param_1 + 4;
        param_2 = param_2 + 1;
        param_3 = param_3 + 1;
        param_4 = param_4 + 1;
    } while (iters < 0x100);
}

void jpegcam_act_helper3_helper_helper_helper2_helper2_80063B94(TMat16x16B *pSourceMat, TMat8x8B *pDestMat1,
                                                                TMat8x8B *pDestMat2, TMat8x8B *pDestMat3,
                                                                TMat8x8B *pDestMat4)
{
    // Given a "16 by 16B" matrix, copy its four quadrants
    // into four "4 by 4B" matricies

    int i, j;

    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            (*pDestMat1)[i][j] = (*pSourceMat)[i][j];
            (*pDestMat2)[i][j] = (*pSourceMat)[i][j + 8];
            (*pDestMat3)[i][j] = (*pSourceMat)[i + 8][j];
            (*pDestMat4)[i][j] = (*pSourceMat)[i + 8][j + 8];
        }
    }
}

#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper3_80063C10.s") // 192 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper4_80063CD0.s") // 268 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper5_80063DDC.s") // 212 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper6_80063EB0.s") // 420 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_80064054.s")         // 364 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_800641C0.s")                 // 440 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_80064378.s")                        // 220 bytes
int jpegcam_act_helper3_helper_80064378(Actor_jpegcam *pActor);

int jpegcam_act_helper2_helper2_80064454(Actor_jpegcam *pActor)
{

    MATRIX  mtx;
    SVECTOR vector1;
    SVECTOR vector2;
    int     retval;
    int     cond;

    if (GM_GameStatus_800AB3CC < 0)
    {
        retval = 3200;
    }
    else
    {
        mtx = dword_800ABA20->objs->world;
        mtx.t[0] = gUnkCameraStruct_800B77B8.field_0.vx;
        mtx.t[1] = gUnkCameraStruct_800B77B8.field_0.vy;
        mtx.t[2] = gUnkCameraStruct_800B77B8.field_0.vz;
        DG_SetPos_8001BC44(&mtx);

        DG_PutVector_8001BE48(&dword_8009F3AC, &vector1, 2);

        cond = 0;
        if (sub_80028454(pActor->field_6C_pMap->field_8_hzd, &vector1, &vector2, 0xf, 0x81) != 0)
        {
            sub_80028890(&vector2);
            cond = 1;
        }

        retval = 3200;
        if (cond != 0)
        {
            GV_SubVec3_80016D40(&vector2, &vector1, &vector1);
            retval = GV_VecLen3_80016D80(&vector1);
        }
    }
    return retval;
}

void jpegcam_act_helper2_80064588(Actor_jpegcam *pActor);
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper2_80064588.s")                               // 1132 bytes

// or: jpegcam_act_helper3_helper2_800649F4(Actor_jpegcam *pActor)
// with pActor unused
int jpegcam_act_helper3_helper2_800649F4()
{
    int retval;

    mts_printf_8008BBA0(aSinreiSyasinCh);
    if (GM_Photocode_800ABA04 != 0)
    {
        mts_printf_8008BBA0(aHereIsSinreiSp);
        mts_printf_8008BBA0(aGmPhotocodeD, GM_Photocode_800ABA04);

        retval = DG_PointCheckOne_8001C18C((DVECTOR *)&GM_PhotoViewPos_800ABA48);
        mts_printf_8008BBA0(aPointCheck);

        mts_printf_8008BBA0(aResultD, retval);
    }
    else
    {
        mts_printf_8008BBA0(aNotSinreiSpot);
        retval = 0;
    }
    return retval;
}

void jpegcam_act_helper3_80064A94(Actor_jpegcam *pActor)
{
    int state = pActor->field_64_state;    

    if (state < 3)
    {
        return;
    }

    if (state == 3)
    {
        GM_Sound_80032968(0, 63, 17);   
    }
    else if (state == 4)
    {
        GV_PauseLevel_800AB928 &= ~0x4;
        GV_PauseLevel_800AB928 |= 0x1;
        DG_FreeObjectQueue_800183D4();
        GV_SetPacketTempMemory_80014C28();
        DG_UnDrawFrameCount_800AB380 = 1;
    }
    else if (state < 9)
    {
        DG_ClipDispEnv_800177EC(256, (state - 4) * 56);
        DG_UnDrawFrameCount_800AB380 = 1;
    }
    else if (state == 9)
    {
        jpegcam_act_helper3_helper_80064378(pActor);
      
        if (jpegcam_act_helper3_helper2_800649F4(pActor) == 1)
        {
            dword_800BDCD0 = GM_Photocode_800ABA04;
        }
        else
        {
            dword_800BDCD0 = 0;
        }

        menu_radio_8004D2FC(&stru_8009F2D8);
        DG_UnDrawFrameCount_800AB380 = 1;
        dword_800BDCC8 = pActor->field_88;
        dword_800BDCCC = pActor->field_8C;
    }
    else if (state == 10)
    {
        if (!menu_radio_8004D334(pActor->field_50_pInput))
        {
            --pActor->field_64_state;
        }
    }
    else if (state == 11)
    {
        pActor->field_70 = 0;
        menu_radio_8004D35C();
        GM_GameStatus_800AB3CC &= ~0x400;
        GV_ResetPacketMemory_80014BD8();
        GV_PauseLevel_800AB928 &= ~0x1;
        DG_8001844C();
        pActor->field_64_state = 0;
        pActor->field_90_pSight = NewSight_80071CDC(SIGHT_CAMERA_2, SIGHT_CAMERA, &GM_CurrentItemId, 12, 0);
    }
}

void jpegcam_act_80064C50(Actor_jpegcam* pActor)
{
    OBJECT* pParent;
    OBJECT* new_var;
    if ((GM_PlayerStatus_800ABA50 & 0x8000000) != 0)
    {
        pActor->field_50_pInput = &GV_PadData_800B05C0[3];
    }
    else
    {
        pActor->field_50_pInput = &GV_PadData_800B05C0[2];
    }

    if (pActor->field_98 < 16)
    {
        pActor->field_98++;
    }

    if (!pActor->field_94_bMakeVisible)
    {
        pParent = pActor->field_24_pObj;
        if (pParent->objs->flag & DG_FLAG_INVISIBLE)
        {
            new_var = (OBJECT*) (&pActor->field_28_obj);
            GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS*) new_var, GV_StrCode_80016CCC(aGoggles), 109, 0);
            if (pActor->field_28_obj.objs)
            {
                GM_ConfigObjectRoot_80034C5C(new_var, pParent, 6);
                GM_ConfigObjectLight_80034C44(new_var, pParent->light);
                EQ_InvisibleHead_80060D5C(pParent, &pActor->field_4c_head_saved_packs, &pActor->field_4e_head_saved_raise);
                pActor->field_94_bMakeVisible = 1;
            }
        }
    }

    if (pActor->field_94_bMakeVisible)
    {
        GM_SetCurrentMap(pActor->field_20_pCtrl->field_2C_map->field_0_map_index_bit);

        DG_GroupObjs(pActor->field_28_obj.objs, DG_CurrentGroupID_800AB968);

        if (GM_PlayerStatus_800ABA50 & 0x4000000)
        {
            if ( !(pActor->field_24_pObj->objs->flag & DG_FLAG_INVISIBLE) )
            {
                DG_VisibleObjs(pActor->field_28_obj.objs);
            }
            GM_Camera_800B77E8.field_20 = 320;
            return;
        }

        DG_InvisibleObjs(pActor->field_28_obj.objs);
    }

    if (GM_LoadRequest_800AB3D0)
    {
        if ((pActor->field_70 == 1) && (pActor->field_64_state < 4))
        {
            GV_PauseLevel_800AB928 &= ~4u;
        }
        GV_DestroyActor_800151C8(&pActor->field_0_actor);
    }
    else
    {
        if (GM_GameOverTimer_800AB3D4)
        {
            return;
        }

        switch (pActor->field_70)
        {
            case 0:
                if (GV_PauseLevel_800AB928)
                {
                    return;
                }
                jpegcam_act_helper2_80064588(pActor);
                if (dword_8009F604 != SIGHT_CAMERA)
                {
                    NewSight_80071CDC(SIGHT_CAMERA, SIGHT_CAMERA, &GM_CurrentItemId, 12, 0);
                    pActor->field_90_pSight = NewSight_80071CDC(SIGHT_CAMERA_2, SIGHT_CAMERA, &GM_CurrentItemId, 12, 0);
                    GM_Sound_80032968(0, 63, 0x15u);
                }
                if ( !(GM_PlayerStatus_800ABA50 & 0x4000000) )
                {
                    menu_Text_XY_Flags_80038B34(200, 25, 0);
                    menu_Color_80038B4C(192, 144, 128);
                    menu_Text_80038C38(aZoom4d, GM_Camera_800B77E8.field_20);
                    menu_Text_80038C38(aAngle4d4d, -pActor->field_5C_ang.vx, pActor->field_5C_ang.vy);
                }
                break;

            case 1:
                if ((pActor->field_64_state < 5) && (GV_PauseLevel_800AB928 & 1))
                {
                    pActor->field_64_state = 0;
                    return;
                }
                jpegcam_act_helper3_80064A94(pActor);
                break;
        }

        pActor->field_64_state++;
        gSnaControl_800AB9F4->field_8_rotator = pActor->field_5C_ang;
        gSnaControl_800AB9F4->field_4C_turn_vec = pActor->field_5C_ang;
    }
}

void jpegcam_kill_80065008(Actor_jpegcam *pActor)
{
    GM_Camera_800B77E8.field_20 = 320;
    gUnkCameraStruct_800B77B8.field_28 = pActor->field_54_vec;

    GM_GameStatus_800AB3CC &= ~0x800;
    GM_GameStatus_800AB3CC &= ~0x400;

    if (pActor->field_94_bMakeVisible != 0)
    {
        EQ_VisibleHead_80060DF0(pActor->field_24_pObj, &pActor->field_4c_head_saved_packs,
                                &pActor->field_4e_head_saved_raise);
        GM_FreeObject_80034BF8((OBJECT *)&pActor->field_28_obj);
    }
}

int jpegcam_loader_80065098(Actor_jpegcam *pActor, GM_Control *pCtrl, OBJECT *pParent)
{
  pActor->field_24_pObj = pParent;
  pActor->field_50_pInput = &GV_PadData_800B05C0[2];
  pActor->field_54_vec = pCtrl->field_8_rotator;
  pActor->field_5C_ang = pActor->field_54_vec;
  pActor->field_64_state = 0;
  pActor->field_68 = 0;
  pActor->field_6C_pMap = pCtrl->field_2C_map;
  pActor->field_70 = 0;
  pActor->field_98 = 0;
  GM_GameStatus_800AB3CC |= 0x800;
  return 0;
}

Actor_jpegcam *NewJpegcam_80065118(GM_Control *pCtrl, OBJECT *pParent)
{
    Actor_jpegcam *pActor;

    pActor = (Actor_jpegcam *)GV_NewActor_800150E4(1, sizeof(Actor_jpegcam));
    if (pActor != NULL)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)jpegcam_act_80064C50,
                                  (TActorFunction)jpegcam_kill_80065008, aJpegcamC);
        if (jpegcam_loader_80065098(pActor, pCtrl, pParent) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return NULL;
        }
        pActor->field_20_pCtrl = pCtrl;
    }
    return pActor;
}
