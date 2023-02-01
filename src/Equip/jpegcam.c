#include "jpegcam.h"
#include "psyq.h"
#include "Game/camera.h"
#include "Game/object.h"

#pragma INCLUDE_ASM("asm/Equip/jpegcam_unk1_80063704.s") // 388 bytes

extern char aPHOTO[];    // "PHOTO %02d\n"
extern char aJpegcamC[]; // "jpegcam.c";

extern GV_PAD GV_PadData_800B05C0[4];

void jpegcam_unk2_80063888(char *param_1, int param_2)
{
    sprintf_8008E878(param_1, aPHOTO, *(char *)(param_2 + 6) - 0x40);
}

#pragma INCLUDE_ASM("asm/Equip/jpegcam_unk3_800638B4.s")                                      // 120 bytes

extern TMat8x8B gJpegcamMatrix1_8009F36C;
extern TMat8x8B gJpegcamMatrix2_800BDCD8;

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

#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_helper_helper_helper2_helper_800639E8.s")  // 428 bytes

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

extern UnkCameraStruct gUnkCameraStruct_800B77B8;
extern OBJECT         *dword_800ABA20;
extern SVECTOR         dword_8009F3AC;

int jpegcam_act_helper2_helper2_80064454(void *param_1)
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
        if (sub_80028454(*(void **)(*(int *)(param_1 + 0x6c) + 8), &vector1, &vector2, 0xf, 0x81) != 0)
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

#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper2_80064588.s")                               // 1132 bytes

extern int     GM_Photocode_800ABA04;
extern SVECTOR GM_PhotoViewPos_800ABA48;

extern const char aSinreiSyasinCh[]; // = "Sinrei Syasin Check Start\n"
extern const char aHereIsSinreiSp[]; // = "Here is Sinrei Spot!\n"
extern const char aGmPhotocodeD[];   // = "GM_Photocode = %d\n"
extern const char aPointCheck[];     // = "Point Check\n"
extern const char aResultD[];        // = "Result = %d\n"
extern const char aNotSinreiSpot[];  // = "Not Sinrei Spot!\n"

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

#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_helper3_80064A94.s")                               // 444 bytes
#pragma INCLUDE_ASM("asm/Equip/jpegcam_act_80064C50.s")                                       // 952 bytes

extern GM_Camera       GM_Camera_800B77E8;
extern UnkCameraStruct gUnkCameraStruct_800B77B8;

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