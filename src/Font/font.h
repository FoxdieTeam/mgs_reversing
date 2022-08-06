#ifndef _FONT_H_
#define _FONT_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

typedef struct _KCB
{
    char  char_arr[8];
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

void font_set_font_addr_80044BC0(int arg1, void *data);
void font_update_8004695C(KCB *kcb);
void font_clear_800468FC(KCB *kcb);
int font_get_buffer_size_80044F38(KCB *kcb);
int font_init_kcb_80044BE0(KCB *kcb, RECT *rect_data, short x, short y);
void font_set_buffer_80044FD8(KCB *kcb, void *buffer);
void  font_set_color_80044DC4(KCB *kcb, int arg1, int arg2, int arg3);
int font_set_kcb_80044C90(KCB *kcb, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
void font_clut_update_80046980(KCB *kcb);
void font_load_80044A9C(void);

#endif // _FONT_H_
