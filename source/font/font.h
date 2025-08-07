#ifndef __MGS_FONT_H__
#define __MGS_FONT_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct _KCB
{
    char  field_00;
    char  field_01;
    char  xtop;
    char  ytop;
    char  field_04;
    char  color;
    char  flag;
    char  max_width;
    RECT *rect_data;
    RECT  font_rect;
    void *font_buffer;
    short width_info;
    short short1;
    short height_info;
    short short3;
    RECT  font_clut_rect;
    void *font_clut_buffer;
} KCB;

// This struct describes the structure of
// "rubi.res" file.
//
// Note that 'r' (0x72) can be either a ".rar",
// ".res" or ".rpk" file. It looks like different
// ".res" files could have different data structure,
// for example "rubi.res" file has a different structure
// and it is not the same as ResHeader in menu/.
//
typedef struct RubiRes
{
    char field_0;
    char field_1[9];
} RubiRes;

/* font.c */
void  font_load(void);
void  font_set_font_addr(int arg1, void *data);
void  font_free(void);
int   font_init_kcb(KCB *kcb, RECT *rect_data, int x, int y);
int   font_set_kcb(KCB *kcb, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
void  font_set_color(KCB *kcb, int code, int fore, int back);
int   font_get_buffer_size(KCB *kcb);
void  font_set_buffer(KCB *kcb, void *buffer);
void *font_get_buffer_ptr(KCB *kcb);
void  font_set_rubi_display_mode(int display_flag);
long  font_draw_string(KCB *kcb, long xtop, long ytop, const char *string, long color);
void  font_clear(KCB *kcb);
void  font_update(KCB *kcb);
void  font_clut_update(KCB *kcb);
void  font_print_string(KCB *kcb, const char *string);

#endif // __MGS_FONT_H__
