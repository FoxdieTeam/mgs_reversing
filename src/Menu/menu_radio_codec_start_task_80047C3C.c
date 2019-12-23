#include "linker.h"
#include "menuMan.h"
#include "mts_new.h"

void* System_2_Alloc_80015EB8(int idx, int size);

extern const char aNoMemoryForSta[];

#define CODEC_TASK_STACK_SIZE 0x800

void menu_radio_codec_task_proc_80047AA0(void);

typedef struct Struct_800ABB38
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int* field_28_pStack;
} Struct_800ABB38;

Struct_800ABB38* SECTION(".sbss") dword_800ABB38;

void menu_radio_codec_start_task_80047C3C(void)
{
    int* pTaskStack;
    int *pStackEnd;

    pTaskStack = System_2_Alloc_80015EB8(0, CODEC_TASK_STACK_SIZE);
    dword_800ABB38->field_28_pStack = pTaskStack;
    if (pTaskStack == 0)
    {
        mts_printf_8008BBA0(aNoMemoryForSta);
    }
    dword_800ABB38->field_0 = 5;
    pStackEnd =  dword_800ABB38->field_28_pStack + (CODEC_TASK_STACK_SIZE / sizeof(int));
    mts_set_stack_check_8008B648(6, pStackEnd, CODEC_TASK_STACK_SIZE);
    mts_sta_tsk_8008B47C(6, menu_radio_codec_task_proc_80047AA0, pStackEnd);
}
