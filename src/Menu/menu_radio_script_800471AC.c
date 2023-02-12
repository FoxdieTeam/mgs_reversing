#include "linker.h"
#include "mts/mts_new.h"
#include "menuman.h"
#include "libgcl/gcl.h"
#include "libgcl/hash.h"
#include "psyq.h"
#include "Game/game.h"
#include "radio.h"
#include "unknown.h"

extern const char aSetCharaCodeD[];
extern const char aAnimeCharaDCod[];
extern const char aVoxcodeX[];
extern const char aIllegalCodeX[];
extern const char aSetDS[];
extern const char aBlockExecError[];

#define MakeVoxCode(x)                                                                                                 \
    ((unsigned int)x[0] << 0x18) | ((unsigned int)x[1] << 0x10) | ((unsigned int)x[2] << 8) | ((unsigned int)x[3])

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
    mts_printf_8008BBA0(aSetCharaCodeD, faceCharaCode);
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
    mts_printf_8008BBA0(aAnimeCharaDCod, faceCharaCode, faceImageName);
}

void radio_voice_80047330(menu_chara_struct *unk, unsigned char *pScript)
{
    unsigned int voxCode = MakeVoxCode(pScript);

    pScript += sizeof(unsigned int);
    mts_printf_8008BBA0(aVoxcodeX, voxCode);
    if ((unk->field_18 & 0x100) == 0)
    {
        SwEnterCriticalSection_8009954C();
        sub_80037EE0(voxCode, 0);
        SwExitCriticalSection_8009956C();
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

    return GCL_GetNextValue_8002069C(pScript, &code, retValue);
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
                    mts_printf_8008BBA0(aIllegalCodeX, *pScript);
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
            mts_printf_8008BBA0(aIllegalCodeX, code);
        }
    }
}

void radio_randSwitch_80047660(menu_chara_struct *unk, unsigned char *pScript)
{
    int randValue;
    int caseValue;
    int code;

    pScript = menu_gcl_read_word_80047098(&randValue, pScript);
    randValue = rand_8008E6B8() % randValue;
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
            mts_printf_8008BBA0(aIllegalCodeX, code);
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
    mts_printf_8008BBA0(aSetDS, contact_freq, pScript);
    menu_SetRadioMemory_8004E110(contact_freq, pScript);
}

void radio_memsave_800477B0(menu_chara_struct *unk, unsigned char *pScript)
{
    int stageIndex = GCL_GetNextInt_800209E8(pScript);

    unk->field_0_state = 3;
    unk->field_C_pScript = GCL_Get_Param_Result_80020AA4();
    unk->field_1A = stageIndex;
    mts_slp_tsk_8008A400();
    unk->field_18 &= ~0x100;
}

void radio_prompt_8004780C(menu_chara_struct *unk, unsigned char *pScript)
{
    unk->field_0_state = 4;
    unk->field_C_pScript = pScript;
    unk->field_1A = 0;
    mts_slp_tsk_8008A400();
}

void radio_varsave_80047838(menu_chara_struct *unk, unsigned char *pScript)
{
    while (*pScript)
    {
        pScript = GCL_VarSaveBuffer_800217F0(pScript);
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
                mts_printf_8008BBA0(aBlockExecError);
                break;
            }
            ptr += size - sizeof(short);
        }
        else
        {
            mts_printf_8008BBA0(aIllegalCodeX, *ptr);
        }
    }
    return totalSize + 1 + pScript;
}
