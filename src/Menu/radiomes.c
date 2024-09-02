#include "linker.h"
#include "mts/pad/pad.h"
#include "mts/taskid.h"
#include "menuman.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "libgcl/hash.h"
#include "psyq.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "SD/g_sound.h"
#include "radio.h"

#define MakeVoxCode(x) \
    ((unsigned int)x[0] << 24) | ((unsigned int)x[1] << 16) | ((unsigned int)x[2] << 8) | ((unsigned int)x[3])

#define load_big_endian_int(addr) ((int)((addr[0] << 24) | (addr[1] << 16) | (addr[2] << 8) | addr[3]))
#define load_big_endian_short_1(addr) ((short)((addr[0] << 8) | addr[1]))
#define load_big_endian_short_2(addr) (((addr)[1] | ((addr)[0] << 8)))

#define CODEC_TASK_STACK_SIZE 0x800

void radio_anim_with_subtitles_800471AC(menu_chara_struct *unk, unsigned char *pScript)
{
    int            faceCharaCode;
    int            faceImageName;
    int            faceUnk;
    unsigned char *ptr;
    int            isSnake;

    ptr = menu_gcl_read_word_80047098(&faceCharaCode, pScript);
    ptr = menu_gcl_read_word_80047098(&faceImageName, ptr);
    ptr = menu_gcl_read_word_80047098(&faceUnk, ptr);
    isSnake = faceCharaCode == CHARA_SNAKE;
    unk->field_C_pScript = ptr;
    printf("set chara code %d\n", faceCharaCode);
    if (faceUnk >= 1)
    {
        menu_800470B4(isSnake, unk, faceCharaCode, faceImageName, faceUnk, 1);
        mts_slp_tsk_8008A400();
    }
    else
    {
        menu_800470B4(isSnake, unk, faceCharaCode, faceImageName, faceUnk, 0);
    }
    unk->field_0_state = 1;
    mts_slp_tsk_8008A400();
}

void radio_anim_face_80047280(menu_chara_struct *unk, unsigned char *pScript)
{
    int faceCharaCode;
    int faceImageName;
    int faceUnk;
    int faceUnk_cond;

    pScript = menu_gcl_read_word_80047098(&faceCharaCode, pScript);
    pScript = menu_gcl_read_word_80047098(&faceImageName, pScript);
    pScript = menu_gcl_read_word_80047098(&faceUnk, pScript);
    if (faceUnk < 0x101)
    {
        faceUnk_cond = 1;
    }
    else
    {
        faceUnk_cond = 0;
        faceUnk -= 0x100;
    }
    menu_800470B4(faceCharaCode == CHARA_SNAKE, unk, faceCharaCode, faceImageName, faceUnk, faceUnk_cond);
    if (faceUnk_cond)
    {
        mts_slp_tsk_8008A400();
    }
    printf("ANIME CHARA %d CODE %d\n", faceCharaCode, faceImageName);
}

void radio_voice_80047330(menu_chara_struct *unk, unsigned char *pScript)
{
    unsigned int voxCode = MakeVoxCode(pScript);

    pScript += sizeof(unsigned int);
    printf("voxcode %X\n", voxCode);
    if ((unk->field_18 & 0x100) == 0)
    {
        SwEnterCriticalSection();
        sub_80037EE0(voxCode, 0);
        SwExitCriticalSection();
        unk->field_14_bInExecBlock = 1;
        menu_gcl_exec_block_800478B4(unk, pScript);
        unk->field_14_bInExecBlock = 0;
        while (GM_StreamStatus_80037CD8() != -1) // wait vox finish ?
        {
            mts_wait_vbl_800895F4(2);
        }
    }
    else
    {
        menu_gcl_exec_block_800478B4(unk, pScript);
    }
}

void radio_sound_80047414(menu_chara_struct *unk, unsigned char *pScript)
{
    unsigned char *ptr;
    int            val;
    int            i;

    switch (*pScript)
    {
    case 0x00:
        ptr = pScript;
        ptr++;
        GM_Sound_80032C48(MakeVoxCode(ptr), 0);
        break;

    case 0x01:
        val = pScript[1];
        i = (signed short int)(pScript[3] | (pScript[2] << 8));
        for (; i > 0; i--)
        {
            if (val > 0)
            {
                mts_set_pad_vibration_8008C408(1, 2);
                mts_set_pad_vibration2_8008C454(1, val);
            }
            mts_wait_vbl_800895F4(1);
        }
        break;
    }
}

unsigned char *radio_getNextValue_800474EC(int *retValue, unsigned char *pScript)
{
    int code;

    return GCL_GetNextValue(pScript, &code, retValue);
}

void radio_if_80047514(menu_chara_struct *unk, unsigned char *pScript)
{
    int expr_result;
    int code;

    for (;;)
    {
        pScript = radio_getNextValue_800474EC(&expr_result, pScript);
        for (;;)
        {
            if (expr_result)
            {
                menu_gcl_exec_block_800478B4(unk, pScript);
                return;
            }
            pScript = radio_moveToNext_80047880(unk, pScript);
            if (*pScript == RDCODE_ENDLINE)
            {
                code = pScript[1];
                pScript += 2;
                if (code == RDCODE_ELSEIF)
                {
                    break;
                }
                else if (code != RDCODE_ELSE)
                {
                    return;
                }
                expr_result = 1;
            }
            else
            {
                if (*pScript)
                {
                    printf("illegal code %x\n", *pScript);
                }
                return;
            }
        }
    }
}

void radio_switch_800475B8(menu_chara_struct *unk, unsigned char *pScript)
{
    int switchValue;
    int caseValue;
    int code;

    pScript = radio_getNextValue_800474EC(&switchValue, pScript);
    for (;;)
    {
        code = *pScript;
        pScript++;
        if (code == RDCODE_SWITCH_CASE)
        {
            pScript = menu_gcl_read_word_80047098(&caseValue, pScript);
            if (switchValue == caseValue)
            {
                menu_gcl_exec_block_800478B4(unk, pScript);
                return;
            }
            else
            {
                pScript = radio_moveToNext_80047880(unk, pScript);
            }
        }
        else if (code == RDCODE_SWITCH_DEFAULT)
        {
            menu_gcl_exec_block_800478B4(unk, pScript);
            return;
        }
        else if (code == RDCODE_NULL)
        {
            return;
        }
        else
        {
            printf("illegal code %x\n", code);
        }
    }
}

void radio_randSwitch_80047660(menu_chara_struct *unk, unsigned char *pScript)
{
    int randValue;
    int caseValue;
    int code;

    pScript = menu_gcl_read_word_80047098(&randValue, pScript);
    randValue = rand() % randValue;
    for (;;)
    {
        code = *pScript;
        pScript++;
        if (code == RDCODE_RANDSWITCH_CASE)
        {
            pScript = menu_gcl_read_word_80047098(&caseValue, pScript);
            randValue -= caseValue;
            if (randValue < 1)
            {
                menu_gcl_exec_block_800478B4(unk, pScript);
                return;
            }
            pScript = radio_moveToNext_80047880(unk, pScript);
        }
        else
        {
            if (code == RDCODE_NULL)
            {
                return;
            }
            printf("illegal code %x\n", code);
        }
    }
}

void radio_eval_80047748(menu_chara_struct *unk, unsigned char *pScript)
{
    int value;

    radio_getNextValue_800474EC(&value, pScript);
}

void radio_add_contact_80047768(menu_chara_struct *unk, unsigned char *pScript)
{
    int contact_freq;

    pScript = menu_gcl_read_word_80047098(&contact_freq, pScript);
    printf("set %d %s\n", contact_freq, pScript);
    MENU_SetRadioMemory_8004E110(contact_freq, pScript);
}

void radio_memsave_800477B0(menu_chara_struct *unk, unsigned char *pScript)
{
    int stageIndex = GCL_StrToInt(pScript);

    unk->field_0_state = 3;
    unk->field_C_pScript = GCL_GetParamResult();
    unk->field_1A_index = stageIndex;
    mts_slp_tsk_8008A400();
    unk->field_18 &= ~0x100;
}

void radio_prompt_8004780C(menu_chara_struct *unk, unsigned char *pScript)
{
    unk->field_0_state = 4;
    unk->field_C_pScript = pScript;
    unk->field_1A_index = 0;
    mts_slp_tsk_8008A400();
}

void radio_varsave_80047838(menu_chara_struct *unk, unsigned char *pScript)
{
    while (*pScript)
    {
        pScript = GCL_VarSaveBuffer(pScript);
    }
}

unsigned char *radio_moveToNext_80047880(menu_chara_struct *unk, unsigned char *pScript)
{
    int size;

    pScript++;
    menu_gcl_read_word_80047098(&size, pScript);
    return pScript + size;
}

unsigned char *menu_gcl_exec_block_800478B4(menu_chara_struct *unk, unsigned char *pScript)
{
    const int      totalSize = ((pScript[1] << 8) | (pScript[2]));
    unsigned char *ptr = pScript + 3;
    int            code;
    int            size;

    while (*ptr)
    {
        if (*ptr == RDCODE_ENDLINE)
        {
            code = ptr[1];
            ptr = menu_gcl_read_word_80047098(&size, ptr + 2);
            switch (code)
            {
            case RDCODE_TALK:
                radio_anim_with_subtitles_800471AC(unk, ptr);
                break;

            case RDCODE_VOICE:
                radio_voice_80047330(unk, ptr);
                break;

            case RDCODE_ANIM:
                radio_anim_face_80047280(unk, ptr);
                break;

            case RDCODE_ADD_CONTACT:
                radio_add_contact_80047768(unk, ptr);
                break;

            case RDCODE_MEMSAVE:
                radio_memsave_800477B0(unk, ptr);
                break;

            case RDCODE_SOUND:
                radio_sound_80047414(unk, ptr);
                break;

            case RDCODE_PROMPT:
                radio_prompt_8004780C(unk, ptr);
                break;

            case RDCODE_VARSAVE:
                radio_varsave_80047838(unk, ptr);
                break;

            case RDCODE_IF:
                radio_if_80047514(unk, ptr);
                break;

            case RDCODE_SWITCH: // not seen yet
                radio_switch_800475B8(unk, ptr);
                break;

            case RDCODE_RANDSWITCH:
                radio_randSwitch_80047660(unk, ptr);
                break;

            case RDCODE_EVAL:
                radio_eval_80047748(unk, ptr);
                break;

            default:
                printf("block exec error\n");
                break;
            }
            ptr += size - sizeof(short);
        }
        else
        {
            printf("illegal code %x\n", *ptr);
        }
    }
    return totalSize + 1 + pScript;
}

menu_chara_struct *SECTION(".sbss") dword_800ABB38;

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

    pFacesGroupSize = (sectorAndSize / 0x1000000) * 2048;
    sectorAndSize &= 0xFFFFFF; // % 0x1000000
    startSector = sectorAndSize;

    dword_800ABB38->field_20_pFacesGroup = GV_AllocMemory(0, pFacesGroupSize);
    if (dword_800ABB38->field_20_pFacesGroup == NULL)
    {
        printf("NO MEMORY FOR FACE %d\n", pFacesGroupSize);
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
    printf("face data num %d\n", dword_800ABB38->field_30_face_count);

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

    pTaskStack = GV_AllocMemory(0, CODEC_TASK_STACK_SIZE);
    dword_800ABB38->field_28_pStack = pTaskStack;
    if (pTaskStack == 0)
    {
        printf("NO MEMORY FOR STACK\n");
    }
    dword_800ABB38->field_0_state = 5;
    pStackEnd = dword_800ABB38->field_28_pStack + (CODEC_TASK_STACK_SIZE / sizeof(int));
    mts_set_stack_check_8008B648(MTSID_CD_READ, pStackEnd, CODEC_TASK_STACK_SIZE);
    mts_sta_tsk_8008B47C(MTSID_CD_READ, menu_radio_codec_task_proc_80047AA0, pStackEnd);
}

void sub_80047CB4(menu_chara_struct *unknown)
{
    GV_ZeroMemory(unknown, sizeof(menu_chara_struct));
    unknown->field_3C[0].field_0_animState = 0;
    unknown->field_3C[1].field_0_animState = 0;
}

void menu_radio_codec_create_state_80047CE4(MenuWork *work)
{
    menu_chara_struct *pAllocated = GV_AllocMemory(0, sizeof(menu_chara_struct));
    if (!pAllocated)
    {
        printf("no memory\n");
    }
    work->field_218 = pAllocated;
    dword_800ABB38 = pAllocated;
    sub_80047CB4(pAllocated);
    pAllocated->field_38 = 0;
}

void menu_radio_update_helper6_80047D40(MenuWork *work)
{
    GV_FreeMemory(0, work->field_218);
    work->field_218 = NULL;
}

//init from face dat file
void sub_80047D70(MenuWork *work, int param_2, int pRadioCode)
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
        size = ((pRadioCode >> 16) & 0xff) * 2048;
        startSector = startSector + ((unsigned int)pRadioCode / 0x1000000);
    }
    else
    {
        size = ((unsigned int)pRadioCode / 0x1000000) * 2048;
    }

    // At the start of the game if you manually call
    // after the initial call, radioDatFragment is 0x800 bytes
    // large and it is read from RADIO.DAT offset 0x1f1000.
    radioDatFragment = GV_AllocMemory(0, size);
    if (radioDatFragment == NULL)
    {
        printf("no memory\n");
    }

    pCharaStruct = work->field_218;

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

    pCharaStruct->field_24_pImgData256 = GV_AllocMemory(0, 0x200);
    if (pCharaStruct->field_24_pImgData256 == NULL)
    {
        printf("no memory\n");
    }

    pImgData256Iter = (short *)pCharaStruct->field_24_pImgData256;
    for (i2 = 0; i2 < 0x100; i2++)
    {
        tmpRgb1 = (i2 % 6) * 4 + 2;
        tmpRgb2 = tmpRgb1 * 0x30;
        while (0);
        rgb = tmpRgb1 << 10;
        tmpRgb2 &= 0x3E0;
        tmpRgb2 |= ~0x7FFF;
        rgb |= tmpRgb2;
        rgb |= tmpRgb1;
        pImgData256Iter[i2] = rgb;
    }
}

void menu_radio_codec_helper_helper10_80047EFC(MenuWork *work, int param_2)
{
    int                    i;
    menu_chara_struct     *pStru;
    menu_chara_struct_sub *pSub;

    pStru = work->field_218;
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

void menu_radio_codec_helper_helper3_80047F44(MenuWork *work, int param_2)
{
    int                    i;
    menu_chara_struct     *pStru;
    menu_chara_struct_sub *pSub;

    pStru = work->field_218;

    for (i = 0; i < 2; i++)
    {
        pSub = &pStru->field_3C[i];
        if (pSub->field_0_animState != 0)
        {
            pSub->field_0_animState = 4;
            if (param_2 != 0)
            {
                pSub->field_6 = -1;
                GM_SeSet2_80032968(0, 63, SE_RADIO_DISCONNECT);
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
    if (mts_get_task_status_8008B618(MTSID_CD_READ))
    {
        mts_wup_tsk_8008A540(MTSID_CD_READ);
        dword_800ABB38->field_0_state = 0;
    }
}

extern void menu_radio_codec_helper_helper7_helper_80046A98(menu_chara_struct *pStru);

//free memory for face dat
void menu_radio_codec_helper_helper7_80048080()
{
    menu_radio_codec_helper_helper7_helper_80046A98(dword_800ABB38);
    GV_FreeMemory(0, dword_800ABB38->field_24_pImgData256);
    GV_FreeMemory(0, dword_800ABB38->field_28_pStack);
    GV_FreeMemory(0, dword_800ABB38->field_20_pFacesGroup);
    GV_FreeMemory(0, dword_800ABB38->field_1C_radioDatFragment);
    dword_800ABB38->field_1C_radioDatFragment = NULL;
}

void menu_radio_codec_helper__helper6_80048100(void)
{
    sub_80047CB4(dword_800ABB38);
}
