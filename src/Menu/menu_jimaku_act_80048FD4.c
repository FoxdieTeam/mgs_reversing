#include "menuman.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/linkvarbuf.h"

extern signed char     dword_8009E76C[];
extern int             GV_PauseLevel_800AB928;
extern UnkJimakuStruct gUnkJimakuStruct_800BDA70;
extern GV_PAD          GV_PadData_800B05C0[4];

extern const char aPause[]; // = "PAUSE"

void menu_jimaku_act_80048FD4( Actor_MenuMan *pActor, unsigned int *pOt )
{
    TextConfig config;
    int        i;
    SPRT      *pSprt;
    SPRT      *pSprt2;
    TILE      *pTile;
    DR_TPAGE  *pTpage;
    int        y;
    KCB       *pFont;

    if ( pActor->field_2B & 0xFE )
    {
        gUnkJimakuStruct_800BDA70.field_38_str = NULL;
        gUnkJimakuStruct_800BDA70.field_0_active = 0;
        return;
    }

    if ( gUnkJimakuStruct_800BDA70.field_0_active == 1 )
    {
        if ( (gUnkJimakuStruct_800BDA70.field_1_type != 0) || !(GM_GameStatusFlag & 0x4000) )
        {
            NEW_PRIM(pSprt, pActor);
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
                NEW_PRIM(pSprt2, pActor);
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

            menu_number_draw_string2_80043220( pActor->field_20_otBuf, &config, aPause );
            pTile = menu_render_rect_8003DB2C( pActor->field_20_otBuf, 0, 0, 320, 224, 0 );
            setSemiTrans(pTile, 1);
        }

        NEW_PRIM(pTpage, pActor);
        setDrawTPage(pTpage, 1, 0, getTPage(0, 0, 960, 256));
        addPrim(pOt, pTpage);

        if ( gUnkJimakuStruct_800BDA70.field_2_timer == -1 )
        {
            if ( GV_PadData_800B05C0[0].press & PAD_CIRCLE )
            {
                gUnkJimakuStruct_800BDA70.field_0_active = 0;

                if ( gUnkJimakuStruct_800BDA70.field_40 != 0 )
                {
                    gUnkJimakuStruct_800BDA70.field_38_str = GCL_Read_String_80020A70( gUnkJimakuStruct_800BDA70.field_40 );
                    gUnkJimakuStruct_800BDA70.field_40 = GCL_Get_Param_Result_80020AA4();
                    return;
                }

                GV_PauseLevel_800AB928 &= ~0x1;
                DG_8001844C();
                gUnkJimakuStruct_800BDA70.field_2_timer = 1;

                if ( gUnkJimakuStruct_800BDA70.field_3C != -1 )
                {
                    GCL_ExecProc_8001FF2C( gUnkJimakuStruct_800BDA70.field_3C, 0 );
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

        sub_800469A4( pFont, gUnkJimakuStruct_800BDA70.field_38_str );
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