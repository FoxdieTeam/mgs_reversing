#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "rank.h"

void rank_800CDFC8(MenuPrim *prim, SELECT_INFO *info)
{
    int        i;
    int        xpos, ypos;
    TextConfig textConfig;

    textConfig.flags = 0x12;
    if (info->field_14 != 0)
    {
        textConfig.color = 0x66748956;
    }
    else
    {
        textConfig.color = 0x663d482e;
    }
    textConfig.xpos = info->field_0_xpos;
    textConfig.ypos = info->field_2_ypos;
    _menu_number_draw_string2(prim, &textConfig, info->message);
    if (info->max_num == 1)
    {
        xpos = info->field_0_xpos;
    }
    else
    {
        xpos = info->field_0_xpos - info->field_10 / 2;
    }
    for (i = 0; i < info->max_num; i++, xpos += info->field_10)
    {
        textConfig.xpos = xpos;
        ypos = info->field_2_ypos;
        textConfig.ypos = ypos + 12;

        if (i == info->current_index)
        {
            textConfig.color = 0x66748956;
            if (info->field_14 != 0)
            {
                ypos += 16;
                rank_800CD8F0(textConfig.xpos, ypos, info->field_12, 12, 2);
            }
        }
        else
        {
            textConfig.color = 0x663d482e;
        }
        _menu_number_draw_string2(prim, &textConfig, info->menu[i].mes);
    }
}
