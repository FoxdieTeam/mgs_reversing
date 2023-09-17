#include "menuman.h"
#include "radio.h"
#include "psyq.h"
#include "libdg/libdg.h"

extern int GV_Time_800AB330;
extern int GV_Clock_800AB920;

extern Menu_Triangle triangle_8009EBD0;
extern Menu_Triangle triangle_8009EBE0;

extern menu_save_mode_data *dword_800ABB4C;
menu_save_mode_data        *dword_800ABB4C;

extern mem_card      *mcd_last_file_800ABB68[2];
extern Stru_800ABB74 *dword_800ABB74;
Stru_800ABB74        *dword_800ABB74;

extern int dword_800AB6FC;
int        dword_800AB6FC;

extern const char  aNewFileNeedDBl[];         // = "NEW FILE [ NEED %d BLOCK%s ]"
extern const char  aFreeDBlockS[];            // = "FREE: %d BLOCK%s"
extern const char  aS_1[];                    // = "S"
extern const char  aNull[];                   // = ""
extern const char  aDiscD[];                  //  = "DISC %d"
extern const char  aTime[];                   // = "TIME"
extern const char  aVe[];                     // = "VE"
extern const char *difficulty_str_8009EBF0[]; // = {"EZ", "NM", "HD", "EX"}

extern const int aClear_0[];

void menu_draw_triangle_800435EC(MenuPrim *pGlue, Menu_Triangle *pTriangle);
void menu_number_draw_string2_80043220(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str);

void menu_radio_do_file_mode_save_memcard_8004B0A0(Actor_MenuMan *pActor, char *pOt, Stru_800ABB74 *pStru)
{
    TextConfig config;

    char saveid[16];
    char discnum[16];
    char newfile[32];
    char freeblocks[32];

    LINE_F2  *pLine;
    SPRT     *pSprt;
    TILE     *pTile;
    POLY_FT4 *pPoly;
    DR_TPAGE *pTpage;

    int                  sp88;
    int                  blocks_req;
    int                  difficulty;
    int                  sp8C;
    int                  sp90;
    int                  sp94;
    int                  sp98;
    int                  sp9C;
    int                  spA0;
    Stru_800ABB74_child *temp_s1;
    MenuPrim            *pOtBuf;

    int var_a2;
    int var_s5;
    int i;
    int var_s0;
    int var_t0;

    int mult;
    int mult2;

    unsigned int s8;
    unsigned int s6;

    int new_var;
    int new_var2, new_var3;

    do
    {
    } while (0);

    pOtBuf = pActor->field_20_otBuf;
    s8 = 0;

    if (pStru->field_8 == 0)
    {
        return;
    }

    sp90 = pStru->field_6;
    sp8C = pStru->field_8 - pStru->field_6;

    s6 = 200;
    if (sp8C > 6)
    {
        sp8C = 6;
    }
    sp94 = 0;
    sp98 = 274;

    var_s5 = 80;

    mult = 52;
    mult2 = 18;

    new_var2 = 18;
    if (pStru->field_16 > 0)
    {
        if (--pStru->field_16 >= 5)
        {
            return;
        }

        sp9C = (4 - pStru->field_16) * mult;
    }
    else
    {
        sp9C = s6 + 10;
    }

    if (pStru->field_18 > 0)
    {
        spA0 = --pStru->field_18 * (mult2 / 4);
    }
    else if (pStru->field_18 == 0)
    {
        spA0 = 0;
    }
    else
    {
        spA0 = 18;
    }

    new_var3 = 210;
    for (sp88 = 0; sp88 < sp8C; sp88++)
    {
        new_var = 'A' - 1;

        _NEW_PRIM(pTile, pOtBuf);
        LSTORE(0, &pTile->r0);

        setXY0(pTile, s8, s6);
        setWH(pTile, new_var3, new_var2);

        setTile(pTile);
        addPrim(pOtBuf->mPrimBuf.mOt, pTile);

        var_a2 = 293;
        if (GV_Clock_800AB920 == 0)
        {
            var_a2 = 288;
        }

        _NEW_PRIM(pPoly, pOtBuf);
        LSTORE(0x80808080, &pPoly->r0);

        if ((sp90 + sp88) == pStru->field_4)
        {
            var_s0 = 18;
        }
        else
        {
            var_s0 = spA0;
        }

        pPoly->x0 = 160 - (sp9C / 2);
        pPoly->y0 = var_s5;

        pPoly->x1 = 160 - (sp9C / 2) + sp9C;
        pPoly->y1 = var_s5;

        pPoly->x2 = 160 - (sp9C / 2);
        pPoly->y2 = var_s5 + var_s0;

        pPoly->x3 = 160 - (sp9C / 2) + sp9C;
        pPoly->y3 = var_s5 + var_s0;

        setUVWH(pPoly, s8, s6, 210, 18);

        pPoly->tpage = var_a2;

        setPolyFT4(pPoly);
        setSemiTrans(pPoly, 1);

        addPrim(pOtBuf->mPrimBuf.mOt, pPoly);

        if (((sp90 + sp88) == pStru->field_4) && (pStru->field_14 != 0))
        {
            do
            {
                sub_8004ABF0(160, var_s5 + 9, pStru->field_12, 16, 2);
            } while (0);
        }

        config.colour = 0x66748956;
        config.flags = 0;
        var_s5 += var_s0;

        if ((pStru->field_24[sp90 + sp88].field_20 >= 0) && (pStru->field_24[sp90 + sp88].field_20 < 16))
        {
            temp_s1 = &pStru->field_24[sp90 + sp88];

            if (temp_s1->field_0_name[0] == 'G')
            {
                config.xpos = s8 + 178;
                config.ypos = s6 + 3;
                sprintf(discnum, aDiscD, ((temp_s1->field_0_name[5] - new_var) >> 3) + 1);
                menu_number_draw_string_80042BF4(pOtBuf, &config, discnum);
            }
            else
            {
                config.xpos = s8 + 178;
                config.ypos = s6 + 3;
                menu_number_draw_string_80042BF4(pOtBuf, &config, aTime);
            }

            if (temp_s1->field_0_name[0] == 'G')
            {
                difficulty = ((temp_s1->field_0_name[3] & 0x40) >> 5) | ((temp_s1->field_0_name[4] & 0x40) >> 6);

                config.xpos = s8 + 164;
                config.ypos = s6 + 10;

                if (temp_s1->field_0_name[1] & 0x40)
                {
                    menu_number_draw_string_80042BF4(pOtBuf, &config, aVe);
                }
                else
                {
                    menu_number_draw_string_80042BF4(pOtBuf, &config, difficulty_str_8009EBF0[difficulty]);
                }
            }

            config.xpos = s8 + 180;
            config.ypos = s6 + 10;

            saveid[0] = temp_s1->field_0_name[1];
            saveid[1] = temp_s1->field_0_name[2];
            saveid[2] = ':';
            saveid[3] = temp_s1->field_0_name[3] & 0x3F;
            saveid[4] = temp_s1->field_0_name[4] & 0x3F;

            saveid[0] = saveid[0] & 0x3F;

            if (saveid[0] == ':')
            {
                memcpy(saveid, aClear_0, 6);
            }

            saveid[5] = 0;
            menu_number_draw_string_80042BF4(pOtBuf, &config, saveid);
        }
        else
        {
            const char   *msg;
            char         *dst = newfile;
            const char   *ptr;
            unsigned char field3;
            long          new_var4;
            config.ypos = s6 + 8;
            config.flags = 0x2;
            config.xpos = s8 + (sp9C / 2);
            msg = aNewFileNeedDBl;
            field3 = dword_800ABB4C->field_3;
            new_var4 = field3;
            if (new_var4 >= 2)
                ptr = aS_1;
            else
                ptr = aNull;

            sprintf(dst, msg, field3, ptr);

            menu_number_draw_string2_80043220(pOtBuf, &config, newfile);
        }

        if (sp88 == 4)
        {
            sp94 = 128;
            sp98 = 274;
        }

        _NEW_PRIM(pSprt, pOtBuf);
        menu_init_sprt_8004AE14(pSprt);

        pSprt->u0 = sp94;
        pSprt->v0 = sp98;

        pSprt->w = 128;
        pSprt->h = 14;
        pSprt->x0 = s8;
        pSprt->y0 = s6 + 2;

        addPrim(pOt, pSprt);

        _NEW_PRIM(pTpage, pOtBuf);
        setDrawTPage(pTpage, 0, 1, getTPage(0, 1, 960, 256));
        addPrim(pOtBuf->mPrimBuf.mOt, pTpage);

        sp98 += 14;
    }

    var_t0 = -(sp9C + 10) / 2;

    for (i = 0; i < 2; i++)
    {
        _NEW_PRIM(pLine, pOtBuf);

        pLine->x0 = pLine->x1 = var_t0 + 160;
        pLine->y0 = 78;
        pLine->y1 = var_s5 + 4;

        LSTORE(0x748956, &pLine->r0);

        setLineF2(pLine);
        setSemiTrans(pLine, 1);
        addPrim(pOtBuf->mPrimBuf.mOt, pLine);

        var_t0 += 10 + sp9C;
    }

    if (pStru->field_18 >= 0)
    {
        return;
    }

    blocks_req = mcd_last_file_800ABB68[dword_800AB6FC]->field_3_free_blocks;

    if (dword_800ABB74->field_8 == 1)
    {
        config.xpos = 160;
    }
    else if (dword_800AB6FC == 0)
    {
        config.xpos = 96;
    }
    else
    {
        config.xpos = 224;
    }

    config.ypos = 68;
    config.flags = 0x2;
    config.colour = 0x66748956;

    sprintf(freeblocks, aFreeDBlockS, blocks_req, (blocks_req > 1) ? aS_1 : aNull);
    menu_number_draw_string2_80043220(pOtBuf, &config, freeblocks);

    if ((GV_Time_800AB330 % 32) > 10)
    {
        if (sp90 > 0)
        {
            menu_draw_triangle_800435EC(pActor->field_20_otBuf, &triangle_8009EBD0);
        }

        if ((sp90 + 6) < pStru->field_8)
        {
            menu_draw_triangle_800435EC(pActor->field_20_otBuf, &triangle_8009EBE0);
        }
    }
}
