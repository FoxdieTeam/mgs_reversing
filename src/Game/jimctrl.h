#ifndef JIMCTRL_H
#define JIMCTRL_H

#define array_800B933C_SIZE 7

#include "libgv/libgv.h"

typedef struct
{
    u_short field_0;
    char field_2;
    char field_3;
} array_800B933C_child;

typedef struct
{
    u_long dword_800B9358;
    u_long dword_800B935C;
} dword_800B9358_struct;

// Actor used for subtitles.
typedef struct
{
    Actor field_0_base;
    int   field_20;
    short field_24;
    char  field_26;
    char  field_27;
    int   field_28;
    int   field_2C;
    int   field_30;
    void *field_34;
    void *field_38; // Pointer to data used to update Codec portraits, mainly by 80038070().
    int   field_3C;
    int   field_40;
    // Pointer to subtitles, mainly used by 80038070():
    // - @ 0x80038240 (R): reads the current subtitle; if disabled, the subtitles no longer update.
    // - @ 0x80038340 (W): updates the pointer; if disabled, all the subtitles play in one go.
    void *field_44_subtitles;
} Actor_JimCtrl;

void         jimctrl_init_helper_clear_80037FB8(void);
void         jimctrl_kill_helper_clear_80038004(Actor_JimCtrl *pJimCtrl);
void         jimctrl_kill_8003853C(Actor_JimCtrl *pJimCtrl);
void         sub_80037FE0(int index, u_short value);
void         jimctrl_act_80038070(void);
unsigned int jimctrl_helper_80037F68(unsigned int);

#endif // JIMCTRL_H
