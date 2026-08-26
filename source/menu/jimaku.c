#include "menuman.h"

#include <stdio.h>
#include "common.h"
#include "linkvar.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "game/game.h"

// here or jimctl.h?
typedef struct {
    char field_0_active; // if true, display on screen and count down timer
    char field_1_type; // 0, 1, 2? - 1: pause
    short field_2_timer; // how many frames to be active
    short field_4_x; // location on screen
    short field_6_y;
    short field_8_w;
    short field_A_h;
    KCB field_C_font;
    char *field_38_str; // the string to display
    int field_3C; // hashed proc name used as first arg to GCL_ExecProc
    char *field_40; // char * gcl string?
    // int field_44 // padding?
} JimakuState;

static JimakuState JimState;

void *SECTION(".sbss") MENU_JimakuTextBody;

signed char dword_8009E76C[] = {-1, 0, 1, 0, 0, 1, 0, -1};

void menu_jimaku_act( MenuWork *work, u_long *ot )
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
        JimState.field_38_str = NULL;
        JimState.field_0_active = 0;
        return;
    }

    if ( JimState.field_0_active == 1 )
    {
        if ( (JimState.field_1_type != 0) ||
            !(GM_Configuration & GM_CONFIG_CAPTION_OFF) )
        {
            NEW_PRIM(pSprt, work);
            LSTORE(0x808080, &pSprt->r0);
            LCOPY(&JimState.field_4_x, &pSprt->x0);
            LCOPY(&JimState.field_8_w, &pSprt->w);
            setClut(pSprt, 960, 510);
            setUV0(pSprt, 0, 0);
            setSprt(pSprt);
            addPrim(ot, pSprt);

            for (i = 0; i < 8; i += 2)
            {
                NEW_PRIM(pSprt2, work);
                *pSprt2 = *pSprt;
                LSTORE(0x64000000, &pSprt2->r0);
                pSprt2->x0 += dword_8009E76C[i];
                pSprt2->y0 += dword_8009E76C[i + 1];
                addPrim(ot, pSprt2);
            }
        }

        if ( JimState.field_1_type == 1 )
        {
            config.color = 0x64C8C8C8;
            config.flags = 0x12;
            config.xpos = 160;
            config.ypos = 80;

            _menu_number_draw_string2( work->prim, &config, "PAUSE" );
            pTile = menu_render_rect_8003DB2C( work->prim, 0, 0, FRAME_WIDTH, FRAME_HEIGHT, 0 );
            setSemiTrans(pTile, 1);
        }

        NEW_PRIM(pTpage, work);
        setDrawTPage(pTpage, 1, 0, getTPage(0, 0, 960, 256));
        addPrim(ot, pTpage);

        if ( JimState.field_2_timer == -1 )
        {
            if ( GV_PadData[0].press & PAD_CIRCLE )
            {
                JimState.field_0_active = 0;

                if ( JimState.field_40 != 0 )
                {
                    JimState.field_38_str = GCL_GetString( JimState.field_40 );
                    JimState.field_40 = GCL_NextStr();
                    return;
                }

                GV_PauseLevel &= ~GV_PAUSE_STOP;
                DG_RestartMainChanlSystem();
                JimState.field_2_timer = 1;

                if ( JimState.field_3C != -1 )
                {
                    GCL_ExecProc( JimState.field_3C, 0 );
                }
            }
        }
        else if ((JimState.field_2_timer > 0) && (--JimState.field_2_timer <= 0))
        {
            JimState.field_0_active = 0;
        }
    }

    if ( JimState.field_38_str != NULL )
    {
        y = (JimState.field_1_type == 1 ) ? 112 : 204;
        pFont = &JimState.field_C_font;

        font_print_string( pFont, JimState.field_38_str );
        font_update( pFont );
        font_clut_update( pFont );

        JimState.field_8_w = 256;
        JimState.field_38_str = NULL;
        JimState.field_0_active = 1;
        JimState.field_4_x = (FRAME_WIDTH - pFont->max_width) / 2;
        JimState.field_A_h = pFont->max_height;
        JimState.field_6_y = y - (pFont->max_height / 2);
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
    menu_jimaku_init_helper(&JimState.field_C_font);
}

void MENU_JimakuWrite(char *str, int frames)
{
    JimState.field_0_active = 0;
    JimState.field_2_timer = frames;
    JimState.field_38_str = str;

    if (frames > 10000)
    {
        JimState.field_1_type = 2;
    }
    else
    {
        JimState.field_1_type = 0;
    }
}

void MENU_JimakuClear(void)
{
    JimState.field_0_active = 0;
    JimState.field_C_font.flag &= ~0x80;
}

void MENU_AreaNameWrite(char *areaName)
{
    MENU_JimakuWrite(areaName, 0);
    JimState.field_1_type = 1;
}

void NewJimakuStr(char *str, int int_1)
{
    MENU_JimakuWrite(str, -1);
    GV_PauseLevel |= GV_PAUSE_STOP;
    JimState.field_3C = int_1;
    DG_StopMainChanlSystem();
}

void NewJimaku(void)
{
    char *str;

    str = GCL_GetString(GCL_NextStr());
    JimState.field_40 = GCL_NextStr();
    MENU_JimakuWrite(str, -1);

    if (GCL_GetOption('e'))
    {
        JimState.field_3C = GCL_StrToInt(GCL_NextStr());
    }

    else
    {
        JimState.field_3C = -1;
    }

    GV_PauseLevel |= GV_PAUSE_STOP;
    DG_StopMainChanlSystem();
}
