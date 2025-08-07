#ifndef __MGS_GAME_JIMCTRL_H__
#define __MGS_GAME_JIMCTRL_H__

#define array_800B933C_SIZE 7

#include "libgv/libgv.h"

typedef struct
{
    u_short       field_0;
    char          field_2;
    unsigned char field_3;
} array_800B933C_child;

typedef struct
{
    u_long dword_800B9358;
    u_long dword_800B935C;
} dword_800B9358_struct;

// GV_ACT used for subtitles.
typedef struct
{
    GV_ACT actor;
    int   field_20;
    short field_24;
    char  field_26;
    char  field_27;
    int   field_28;
    int   field_2C;
    int   field_30;
    int  *field_34;
    char *field_38; // Pointer to data used to update Codec portraits, mainly by 80038070().
    int   field_3C;
    int   field_40;
    // Pointer to subtitles, mainly used by 80038070():
    // - @ 0x80038240 (R): reads the current subtitle; if disabled, the subtitles no longer update.
    // - @ 0x80038340 (W): updates the pointer; if disabled, all the subtitles play in one go.
    int  *field_44_subtitles;
    int   field_48;
    int   field_4C;
    char  field_50_buffer[4090];
} JimakuCtrlWork;

typedef struct
{
    char *field_0;
    int  *field_4;
    short data_offset;
    short subtitle_offset;
    int   font_offset;
} SubtitleHeader;

unsigned int jimctrl_helper_80037F68(unsigned int);

void *NewJimakuControl(u_long flags);

int                   jimctrl_80038688(void);
array_800B933C_child *jimctrl_80038698(void);

#endif // __MGS_GAME_JIMCTRL_H__
