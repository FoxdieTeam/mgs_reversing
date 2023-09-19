#include "radio.h"
#include "linker.h"
#include "menuman.h"
#include "Game/game.h"
#include "mts/mts_new.h"
#include "libfs/libfs.h"
#include "libgv/libgv.h"
#include "Game/linkvarbuf.h"


extern const char aNoMemoryForSta[];
extern const char aNoMemory[];

#define CODEC_TASK_STACK_SIZE 0x800

menu_chara_struct *SECTION(".sbss") dword_800ABB38;

extern const char aNoMemoryForFac[]; // = "NO MEMORY FOR FACE %d\n";
extern const char aFaceDataNumD[];   // = "face data num %d\n";

#define load_big_endian_int(addr) ((int)((addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | addr[3]))
#define load_big_endian_short_1(addr) ((short)((addr[0] << 8) | addr[1]))
#define load_big_endian_short_2(addr) (((addr)[1] | ((addr)[0] << 8)))

//alloc mem for face dat file
void menu_radio_codec_task_proc_80047AA0()
{
    int      field_18;
    unsigned sectorAndSize;
    char    *radioDatIter;
    unsigned startSector;

    faces_group *pFacesGroup;
    unsigned     pFacesGroupSize;

    unsigned fontAddrOffset;

    mts_set_vsync_task_800892B8();
    radioDatIter = dword_800ABB38->field_8_radioDatFragment;
    radioDatIter += 2;

    sectorAndSize = load_big_endian_int(radioDatIter);
    radioDatIter += 4;

    field_18 = load_big_endian_short_1(radioDatIter);
    radioDatIter += 2;

    while (FS_StreamTaskState_80023E0C())
    {
        mts_wait_vbl_800895F4(2);
    }

    pFacesGroupSize = (sectorAndSize / 16777216) * 2048;
    sectorAndSize &= 0xFFFFFF; // % 16777216
    startSector = sectorAndSize;

    dword_800ABB38->field_20_pFacesGroup = GV_AllocMemory_80015EB8(0, pFacesGroupSize);
    if (dword_800ABB38->field_20_pFacesGroup == NULL)
    {
        printf(aNoMemoryForFac, pFacesGroupSize);
    }

    // pFacesGroup is parsed in menu_radio_codec_task_proc_helper_80046F3C
    pFacesGroup = dword_800ABB38->field_20_pFacesGroup;

    // At the start of the game if you manually call
    // after the initial call, pFacesGroup is 0x25800 bytes
    // large and it is read from FACE.DAT offset 0x13a800.
    FS_LoadFileRequest_80021F0C(2, startSector, pFacesGroupSize, pFacesGroup);
    while (FS_LoadFileSync_80021F48() > 0)
    {
        mts_wait_vbl_800895F4(1);
    }

    menu_radio_codec_task_proc_helper_80046F3C(dword_800ABB38, pFacesGroup);
    printf(aFaceDataNumD, dword_800ABB38->field_30_face_count);

    dword_800ABB38->field_14_bInExecBlock = 0;
    field_18 &= ~0x1;
    dword_800ABB38->field_18 = field_18;

    fontAddrOffset = load_big_endian_short_2(radioDatIter + 1) + 1;
    font_set_font_addr_80044BC0(1, radioDatIter + fontAddrOffset);

    dword_800ABB38->field_0_state = 0;
    menu_gcl_exec_block_800478B4(dword_800ABB38, radioDatIter);
    dword_800ABB38->field_0_state = 2;

    mts_8008B51C();
}


void menu_radio_codec_start_task_80047C3C(void)
{
    int *pTaskStack;
    int *pStackEnd;

    pTaskStack = GV_AllocMemory_80015EB8(0, CODEC_TASK_STACK_SIZE);
    dword_800ABB38->field_28_pStack = pTaskStack;
    if (pTaskStack == 0)
    {
        printf(aNoMemoryForSta);
    }
    dword_800ABB38->field_0_state = 5;
    pStackEnd = dword_800ABB38->field_28_pStack + (CODEC_TASK_STACK_SIZE / sizeof(int));
    mts_set_stack_check_8008B648(6, pStackEnd, CODEC_TASK_STACK_SIZE);
    mts_sta_tsk_8008B47C(6, menu_radio_codec_task_proc_80047AA0, pStackEnd);
}

void sub_80047CB4(menu_chara_struct *unknown)
{
    GV_ZeroMemory_8001619C(unknown, sizeof(menu_chara_struct));
    unknown->field_3C[0].field_0_animState = 0;
    unknown->field_3C[1].field_0_animState = 0;
}

void menu_radio_codec_create_state_80047CE4(Actor_MenuMan *pMenuMan)
{
    menu_chara_struct *pAllocated = GV_AllocMemory_80015EB8(0, sizeof(menu_chara_struct));
    if (!pAllocated)
    {
        printf(aNoMemory);
    }
    pMenuMan->field_218 = pAllocated;
    dword_800ABB38 = pAllocated;
    sub_80047CB4(pAllocated);
    pAllocated->field_38 = 0;
}

void menu_radio_update_helper6_80047D40(Actor_MenuMan *pActor)
{
    GV_FreeMemory_80015FD0(0, pActor->field_218);
    pActor->field_218 = NULL;
}

//init from face dat file
void sub_80047D70(Actor_MenuMan *pActor, int param_2, int pRadioCode)
{
    menu_chara_struct_sub *pCharaStructSub;
    menu_chara_struct     *pCharaStruct;

    int   startSector, size;
    void *radioDatFragment;

    int i, i2;

    short  *pImgData256Iter;
    int     rgb;
    int     tmpRgb1, tmpRgb2;

    char pad[8]; // unused stack...

    startSector = pRadioCode & 0xffff;
    if (GM_GameStatusFlag & 0x100)
    {
        size = ((pRadioCode >> 0x10) & 0xff) * 2048;
        startSector = startSector + ((unsigned int)pRadioCode / 16777216);
    }
    else
    {
        size = ((unsigned int)pRadioCode / 16777216) * 2048;
    }

    // At the start of the game if you manually call
    // after the initial call, radioDatFragment is 0x800 bytes
    // large and it is read from RADIO.DAT offset 0x1f1000.
    radioDatFragment = GV_AllocMemory_80015EB8(0, size);
    if (radioDatFragment == NULL)
    {
        printf(aNoMemory);
    }

    pCharaStruct = pActor->field_218;

    sub_80048124();
    sub_800469F0(pCharaStruct);
    pCharaStruct->field_1C_radioDatFragment = radioDatFragment;
    pCharaStruct->field_8_radioDatFragment = radioDatFragment;
    pCharaStruct->field_C_pScript = NULL;
    pCharaStruct->field_4 = param_2;
    pCharaStruct->field_0_state = 0;
    pCharaStruct->field_38 = 0;

    for (i = 0; i < 2; i++)
    {
        pCharaStructSub = &pCharaStruct->field_3C[i];
        pCharaStructSub->field_0_animState = 0;
        pCharaStructSub->field_4 = 0;
    }

    // radioDatFragment is parsed in menu_radio_codec_task_proc_80047AA0()
    FS_LoadFileRequest_80021F0C(1, startSector, size, radioDatFragment);

    pCharaStruct->field_24_pImgData256 = GV_AllocMemory_80015EB8(0, 0x200);
    if (pCharaStruct->field_24_pImgData256 == NULL)
    {
        printf(aNoMemory);
    }

    pImgData256Iter = (short *)pCharaStruct->field_24_pImgData256;
    for (i2 = 0; i2 < 0x100; i2++)
    {
        tmpRgb1 = (i2 % 6) * 4 + 2;
        tmpRgb2 = tmpRgb1 * 0x30;
        while (0);
        rgb = tmpRgb1 << 0xA;
        tmpRgb2 &= 0x3E0;
        tmpRgb2 |= ~0x7FFF;
        rgb |= tmpRgb2;
        rgb |= tmpRgb1;
        pImgData256Iter[i2] = rgb;
    }
}

void menu_radio_codec_helper_helper10_80047EFC(Actor_MenuMan *pActor, int param_2)
{
    int                    i;
    menu_chara_struct     *pStru;
    menu_chara_struct_sub *pSub;

    pStru = pActor->field_218;
    pStru->field_38 = 1;

    for (i = 0; i < 2; i++)
    {
        pSub = &pStru->field_3C[i];
        if (param_2 != 0)
        {
            pSub->field_6 = 1;
        }
        else
        {
            pSub->field_6 = 10;
        }
    }
}

void menu_radio_codec_helper_helper3_80047F44(Actor_MenuMan *pActor, int param_2)
{
    int                    i;
    menu_chara_struct     *pStru;
    menu_chara_struct_sub *pSub;

    pStru = pActor->field_218;

    for (i = 0; i < 2; i++)
    {
        pSub = &pStru->field_3C[i];
        if (pSub->field_0_animState != 0)
        {
            pSub->field_0_animState = 4;
            if (param_2 != 0)
            {
                pSub->field_6 = -1;
                GM_SeSet2_80032968(0, 63, 87);
            }
            else
            {
                pSub->field_4 = 0;
            }
        }
    }
}

int menu_radio_codec_helper_helper9_80047FF4()
{
    int iVar1;

    iVar1 = FS_LoadFileSync_80021F48();
    if (iVar1 >= 1)
    {
        return iVar1;
    }

    return 0;
}

void menu_radio_codec_state_2_helper_80048024(void)
{
    menu_radio_codec_start_task_80047C3C();
}

void menu_radio_codec_helper_helper8_80048044(void)
{
    if (mts_get_task_status_8008B618(6))
    {
        mts_wup_tsk_8008A540(6);
        dword_800ABB38->field_0_state = 0;
    }
}

extern void menu_radio_codec_helper_helper7_helper_80046A98(menu_chara_struct *pStru);

//free memory for face dat
void menu_radio_codec_helper_helper7_80048080()
{
    menu_radio_codec_helper_helper7_helper_80046A98(dword_800ABB38);
    GV_FreeMemory_80015FD0(0, dword_800ABB38->field_24_pImgData256);
    GV_FreeMemory_80015FD0(0, dword_800ABB38->field_28_pStack);
    GV_FreeMemory_80015FD0(0, dword_800ABB38->field_20_pFacesGroup);
    GV_FreeMemory_80015FD0(0, dword_800ABB38->field_1C_radioDatFragment);
    dword_800ABB38->field_1C_radioDatFragment = NULL;
}

void menu_radio_codec_helper__helper6_80048100(void)
{
    sub_80047CB4(dword_800ABB38);
}
