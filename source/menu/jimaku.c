#include "menuman.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "linkvar.h"

void *SECTION(".sbss") MENU_JimakuTextBody;

extern UnkJimakuStruct gUnkJimakuStruct_800BDA70;

signed char dword_8009E76C[] = {-1, 0, 1, 0, 0, 1, 0, -1};

void menu_jimaku_act( MenuWork *work, unsigned int *pOt )
{
    TextConfig config;
    int        i;
    SPRT      *pSprt;
    SPRT      *pSprt2;
    TILE      *pTile;
    DR_TPAGE  *pTpage;
    int        y;
    KCB       *pFont;

    if ( work->field_2B & 0xFE )
    {
        gUnkJimakuStruct_800BDA70.field_38_str = NULL;
        gUnkJimakuStruct_800BDA70.field_0_active = 0;
        return;
    }

    if ( gUnkJimakuStruct_800BDA70.field_0_active == 1 )
    {
        if ( (gUnkJimakuStruct_800BDA70.field_1_type != 0) ||
            !(GM_OptionFlag & OPTION_CAPTION_OFF) )
        {
            NEW_PRIM(pSprt, work);
            LSTORE(0x808080, &pSprt->r0);
            LCOPY(&gUnkJimakuStruct_800BDA70.field_4_x, &pSprt->x0);
            LCOPY(&gUnkJimakuStruct_800BDA70.field_8_w, &pSprt->w);
            setClut(pSprt, 960, 510);
            pSprt->u0 = 0;
            pSprt->v0 = 0;
            setSprt(pSprt);
            addPrim(pOt, pSprt);

            for (i = 0; i < 8; i += 2)
            {
                NEW_PRIM(pSprt2, work);
                *pSprt2 = *pSprt;
                LSTORE(0x64000000, &pSprt2->r0);
                pSprt2->x0 += dword_8009E76C[i];
                pSprt2->y0 += dword_8009E76C[i + 1];
                addPrim(pOt, pSprt2);
            }
        }

        if ( gUnkJimakuStruct_800BDA70.field_1_type == 1 )
        {
            config.colour = 0x64C8C8C8;
            config.flags = 0x12;
            config.xpos = 160;
            config.ypos = 80;

            _menu_number_draw_string2( work->field_20_otBuf, &config, "PAUSE" );
            pTile = menu_render_rect_8003DB2C( work->field_20_otBuf, 0, 0, 320, 224, 0 );
            setSemiTrans(pTile, 1);
        }

        NEW_PRIM(pTpage, work);
        setDrawTPage(pTpage, 1, 0, getTPage(0, 0, 960, 256));
        addPrim(pOt, pTpage);

        if ( gUnkJimakuStruct_800BDA70.field_2_timer == -1 )
        {
            if ( GV_PadData[0].press & PAD_CIRCLE )
            {
                gUnkJimakuStruct_800BDA70.field_0_active = 0;

                if ( gUnkJimakuStruct_800BDA70.field_40 != 0 )
                {
                    gUnkJimakuStruct_800BDA70.field_38_str = GCL_ReadString( gUnkJimakuStruct_800BDA70.field_40 );
                    gUnkJimakuStruct_800BDA70.field_40 = GCL_GetParamResult();
                    return;
                }

                GV_PauseLevel &= ~1;
                DG_RestartMainChanlSystem();
                gUnkJimakuStruct_800BDA70.field_2_timer = 1;

                if ( gUnkJimakuStruct_800BDA70.field_3C != -1 )
                {
                    GCL_ExecProc( gUnkJimakuStruct_800BDA70.field_3C, 0 );
                }
            }
        }
        else if ((gUnkJimakuStruct_800BDA70.field_2_timer > 0) && (--gUnkJimakuStruct_800BDA70.field_2_timer <= 0))
        {
            gUnkJimakuStruct_800BDA70.field_0_active = 0;
        }
    }

    if ( gUnkJimakuStruct_800BDA70.field_38_str != NULL )
    {
        y = (gUnkJimakuStruct_800BDA70.field_1_type == 1 ) ? 112 : 204;
        pFont = &gUnkJimakuStruct_800BDA70.field_C_font;

        font_print_string( pFont, gUnkJimakuStruct_800BDA70.field_38_str );
        font_update( pFont );
        font_clut_update( pFont );

        gUnkJimakuStruct_800BDA70.field_8_w = 256;
        gUnkJimakuStruct_800BDA70.field_38_str = NULL;
        gUnkJimakuStruct_800BDA70.field_0_active = 1;
        gUnkJimakuStruct_800BDA70.field_4_x = (320 - pFont->max_width) / 2;
        gUnkJimakuStruct_800BDA70.field_A_h = pFont->short3;
        gUnkJimakuStruct_800BDA70.field_6_y = y - (pFont->short3 / 2);
    }
}

STATIC void menu_jimaku_init_helper(KCB *kcb)
{
    RECT rect;
    setRECT(&rect, 960, 256, 64, 38);

    font_init_kcb(kcb, &rect, 960, 510);
    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);
    printf("jimaku_font_buffer_size %d\n", font_get_buffer_size(kcb));
    MENU_JimakuTextBody = GV_AllocResidentMemory(font_get_buffer_size(kcb));
    font_set_buffer(kcb, MENU_JimakuTextBody);
    font_set_color(kcb, 0, 0x6739, 0);
    font_clut_update(kcb);
}

void menu_jimaku_init(MenuWork *work)
{
    menu_jimaku_init_helper(&gUnkJimakuStruct_800BDA70.field_C_font);
}

void MENU_JimakuWrite(char *str, int frames)
{
    gUnkJimakuStruct_800BDA70.field_0_active = 0;
    gUnkJimakuStruct_800BDA70.field_2_timer = frames;
    gUnkJimakuStruct_800BDA70.field_38_str = str;

    if (frames > 10000)
    {
        gUnkJimakuStruct_800BDA70.field_1_type = 2;
    }
    else
    {
        gUnkJimakuStruct_800BDA70.field_1_type = 0;
    }
}

void MENU_JimakuClear(void)
{
    gUnkJimakuStruct_800BDA70.field_0_active = 0;
    gUnkJimakuStruct_800BDA70.field_C_font.flag &= ~0x80;
}

void MENU_AreaNameWrite(char *areaName)
{
    MENU_JimakuWrite(areaName, 0);
    gUnkJimakuStruct_800BDA70.field_1_type = 1;
}

void NewJimakuStr(char *str, int int_1)
{
    MENU_JimakuWrite(str, -1);
    GV_PauseLevel |= 1;
    gUnkJimakuStruct_800BDA70.field_3C = int_1;
    DG_FreeObjectQueue();
}

void NewJimaku(void)
{
    char *str;

    str = GCL_ReadString(GCL_GetParamResult());
    gUnkJimakuStruct_800BDA70.field_40 = GCL_GetParamResult();
    MENU_JimakuWrite(str, -1);

    if (GCL_GetOption('e'))
    {
        gUnkJimakuStruct_800BDA70.field_3C = GCL_StrToInt(GCL_GetParamResult());
    }

    else
    {
        gUnkJimakuStruct_800BDA70.field_3C = -1;
    }

    GV_PauseLevel |= 1;
    DG_FreeObjectQueue();
}
