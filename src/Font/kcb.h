#ifndef _KCB_H_
#define _KCB_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct _KCB
{
    char char_arr[8];
	RECT* rect_data;
	RECT font_rect;
	unsigned int* font_buffer;
	short width_info;
	short short1;
	short height_info;
	short short3;
	RECT font_clut_rect;
	unsigned int* font_clut_buffer;
} KCB;

#endif // _KCB_H_