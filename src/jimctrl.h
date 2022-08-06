#ifndef JIMCTRL_H
#define JIMCTRL_H

#define array_800B933C_SIZE 7

#include "libgv/libgv.h"
#include "util/idaTypes.h"

typedef struct
{
    WORD field_0;
    char field_2;
    char field_3;
} array_800B933C_child;

typedef struct
{
    DWORD dword_800B9358;
    DWORD dword_800B935C;
} dword_800B9358_struct;

typedef struct
{
    Actor field_0_base;
    DWORD field_20;
    WORD  field_24;
    BYTE  field_26;
    BYTE  field_27;
    DWORD field_28;
    DWORD field_2C;
    DWORD field_30;
    DWORD field_34;
    int   field_38;
    BYTE  field_3C_pad[8];
    int   field_44;
} Actor_JimCtrl;

void jimctrl_init_helper_clear_80037FB8(void);
void jimctrl_kill_helper_clear_80038004(Actor_JimCtrl *pJimCtrl);
void jimctrl_kill_8003853C(Actor_JimCtrl *pJimCtrl);
void sub_80037FE0(int index, WORD value);
void jimctrl_act_80038070(void);
unsigned int jimctrl_helper_80037F68(unsigned int);

#endif // JIMCTRL_H
