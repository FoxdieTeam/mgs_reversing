#include "linker.h"
#include "menuman.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/linkvarbuf.h"

extern void *MENU_JimakuTextBody_800ABB40;
void        *SECTION(".sbss") MENU_JimakuTextBody_800ABB40;

extern int             GV_PauseLevel_800AB928;
extern UnkJimakuStruct gUnkJimakuStruct_800BDA70;
extern GV_PAD          GV_PadData_800B05C0[4];

signed char dword_8009E76C[] = {-1, 0, 1, 0, 0, 1, 0, -1};

void menu_jimaku_act_80048FD4( MenuWork *work, unsigned int *pOt )
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
        if ( (gUnkJimakuStruct_800BDA70.field_1_type != 0) || !(GM_GameStatusFlag & 0x4000) )
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

            _menu_number_draw_string2_80043220( work->field_20_otBuf, &config, "PAUSE" );
            pTile = menu_render_rect_8003DB2C( work->field_20_otBuf, 0, 0, 320, 224, 0 );
            setSemiTrans(pTile, 1);
        }

        NEW_PRIM(pTpage, work);
        setDrawTPage(pTpage, 1, 0, getTPage(0, 0, 960, 256));
        addPrim(pOt, pTpage);

        if ( gUnkJimakuStruct_800BDA70.field_2_timer == -1 )
        {
            if ( GV_PadData_800B05C0[0].press & PAD_CIRCLE )
            {
                gUnkJimakuStruct_800BDA70.field_0_active = 0;

                if ( gUnkJimakuStruct_800BDA70.field_40 != 0 )
                {
                    gUnkJimakuStruct_800BDA70.field_38_str = GCL_ReadString( gUnkJimakuStruct_800BDA70.field_40 );
                    gUnkJimakuStruct_800BDA70.field_40 = GCL_GetParamResult();
                    return;
                }

                GV_PauseLevel_800AB928 &= ~1;
                DG_ResetObjectQueue();
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

        font_print_string_800469A4( pFont, gUnkJimakuStruct_800BDA70.field_38_str );
        font_update_8004695C( pFont );
        font_clut_update_80046980( pFont );

        gUnkJimakuStruct_800BDA70.field_8_w = 256;
        gUnkJimakuStruct_800BDA70.field_38_str = NULL;
        gUnkJimakuStruct_800BDA70.field_0_active = 1;
        gUnkJimakuStruct_800BDA70.field_4_x = (320 - pFont->char_arr[ 7 ]) / 2;
        gUnkJimakuStruct_800BDA70.field_A_h = pFont->short3;
        gUnkJimakuStruct_800BDA70.field_6_y = y - (pFont->short3 / 2);
    }
}

void menu_jimaku_init_helper_800493F8(KCB *kcb)
{
    RECT rect;
    setRECT(&rect, 960, 256, 64, 38);

    font_init_kcb_80044BE0(kcb, &rect, 960, 510);
    font_set_kcb_80044C90(kcb, -1, -1, 0, 6, 2, 0);
    printf("jimaku_font_buffer_size %d\n", font_get_buffer_size_80044F38(kcb));
    MENU_JimakuTextBody_800ABB40 = GV_AllocResidentMemory(font_get_buffer_size_80044F38(kcb));
    font_set_buffer_80044FD8(kcb, MENU_JimakuTextBody_800ABB40);
    font_set_color_80044DC4(kcb, 0, 0x6739, 0);
    font_clut_update_80046980(kcb);
}

void menu_jimaku_init_800494C4()
{
    menu_jimaku_init_helper_800493F8(&gUnkJimakuStruct_800BDA70.field_C_font);
}

void MENU_JimakuWrite_800494E8(char *str, int frames)
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

void MENU_JimakuClear_80049518(void)
{
    gUnkJimakuStruct_800BDA70.field_0_active = 0;
    gUnkJimakuStruct_800BDA70.field_C_font.char_arr[6] &= ~0x80;
}

void MENU_AreaNameWrite_80049534(char *areaName)
{
    MENU_JimakuWrite_800494E8(areaName, 0);
    gUnkJimakuStruct_800BDA70.field_1_type = 1;
}

void NewJimakuStr_8004955C(char *str, int int_1)
{
  MENU_JimakuWrite_800494E8(str, -1);
  GV_PauseLevel_800AB928 |= 1;
  gUnkJimakuStruct_800BDA70.field_3C = int_1;
  DG_FreeObjectQueue();
}

void NewJimaku_800495A8()
{
    char *str;

    str = GCL_ReadString(GCL_GetParamResult());
    gUnkJimakuStruct_800BDA70.field_40 = GCL_GetParamResult();
    MENU_JimakuWrite_800494E8(str, -1);

    if (GCL_GetOption('e'))
    {
        gUnkJimakuStruct_800BDA70.field_3C = GCL_StrToInt(GCL_GetParamResult());
    }

    else
    {
        gUnkJimakuStruct_800BDA70.field_3C = -1;
    }

    GV_PauseLevel_800AB928 |= 1;
    DG_FreeObjectQueue();
}
