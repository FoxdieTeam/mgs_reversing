#ifndef __MGS_FONT_H__
#define __MGS_FONT_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct _KCB
{
    char  c_width;
    char  c_height;
    char  c_skip;
    char  l_skip;
    char  t_skip;
    char  color;
    char  flag;
    char  max_width;
    RECT *rect_ptr;
    RECT  rect;
    void *buffer;
    short row;
    short width;
    short height;
    short max_height;
    RECT  crect;
    void *cbuffer;
} KCB;

#define FONT_NO_ORIKAESHI   0x01    // No line break
#define FONT_NO_KINSOKU     0x02    // No line break control
#define FONT_CLEAN          0x10

#define TOP_KINSOKU_MASK    0x4000
#define BACK_KINSOKU_MASK   0x2000

#define CODE( a ) ( (a) | 0x8000 )
#define IS_HANKAKU( a ) ( (a) < 0x8100 )

/* font.c */
void  font_resident_load_set( void );
void  font_set_top_addr( int type, void *addr );
void  font_free( void );
int   font_init_kcb( KCB *kcb, RECT *rect, int x, int y );
int   font_set_kcb( KCB *kcb, int width, int height, int c_skip, int l_skip, int t_skip, int flag );
void  font_set_color( KCB *kcb, int code, int fore, int back );
int   font_get_buffer_size( KCB *kcb );
void  font_set_buffer( KCB *kcb, void *buf );
void *font_get_buffer_ptr( KCB *kcb );
void  font_set_rubi_display_mode( int flag );
long  font_draw_string( KCB *kcb, long xtop, long ytop, const char *string, long color );
void  font_clear( KCB *kcb );
void  font_update( KCB *kcb );
void  font_clut_update( KCB *kcb );
void  font_print_string( KCB *kcb, const char *string );

#endif // __MGS_FONT_H__
