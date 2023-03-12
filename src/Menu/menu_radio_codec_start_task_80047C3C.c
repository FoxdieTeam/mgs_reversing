#include "linker.h"
#include "menuman.h"
#include "radio.h"
#include "mts/mts_new.h"

extern const char aNoMemoryForSta[];
extern const char aNoMemory[];

#define CODEC_TASK_STACK_SIZE 0x800

menu_chara_struct *SECTION(".sbss") dword_800ABB38;

void menu_radio_codec_start_task_80047C3C(void)
{
    int *pTaskStack;
    int *pStackEnd;

    pTaskStack = GV_AllocMemory_80015EB8(0, CODEC_TASK_STACK_SIZE);
    dword_800ABB38->field_28_pStack = pTaskStack;
    if (pTaskStack == 0)
    {
        mts_printf_8008BBA0(aNoMemoryForSta);
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
        mts_printf_8008BBA0(aNoMemory);
    }
    pMenuMan->field_218 = pAllocated;
    dword_800ABB38 = pAllocated;
    sub_80047CB4(pAllocated);
    pAllocated->field_38 = 0;
}
