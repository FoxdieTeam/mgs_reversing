#include "over.h"
#include "unknown.h"
#include "Game/linkvarbuf.h"

extern const char aInit_0[];
extern const char aTitle[];

extern int        GM_GameOverTimer_800AB3D4;
extern int        GM_LoadRequest_800AB3D0;
extern int        GV_PauseLevel_800AB928;

//------------------------------------------------------------------------------

char * over_act_helper_80036A10(char *pBuffer, int x, int y, int texture_id, unsigned int color, unsigned int *pOt)
{
    DG_TEX *pTex = DG_GetTexture_8001D830(texture_id);
    SPRT *pSprt = (SPRT *)pBuffer;
    DR_TPAGE *pTpage = (DR_TPAGE *)(pBuffer + sizeof(SPRT));

    pSprt->x0 = x;
    pSprt->y0 = y;
    pSprt->u0 = pTex->field_8_offx;
    pSprt->v0 = pTex->field_9_offy;
    pSprt->w = pTex->field_A_width + 1;
    pSprt->h = pTex->field_B_height + 1;
    pSprt->clut = pTex->field_6_clut;
    LSTORE(color, &pSprt->r0);

    setSprt(pSprt);
    addPrim(pOt, pSprt);

    setDrawTPage(pTpage, 1, 0, pTex->field_4_tPage);
    addPrim(pOt, pTpage);

    return pBuffer + sizeof(SPRT) + sizeof(DR_TPAGE);
}

unsigned int over_act_helper_80036B40( int param_1, int param_2 )
{
    int          iVar1;
    unsigned int uVar2;
    int          iVar3;

    iVar1 = 0xff;
    if ( param_2 < 8 )
    {
        uVar2 = 0x80;
    }
    else
    {
        param_2 -= 8;
        iVar1 = param_2 - 8;
        if ( param_2 > 8 )
        {
            param_2 = 8;
        }
        iVar3 = ( 0xff - param_1 ) * param_2;
        uVar2 = 0x80 - ( param_2 * 0x10 );
        if ( iVar3 < 0 )
        {
            iVar3 = iVar3 + 7;
        }
        iVar1 = 0xff - ( iVar3 >> 3 );
    }
    return uVar2 | iVar1 << 8 | iVar1 << 0x10;
}

extern short game_over_lines_8009DEBC[];
extern int   GV_Clock_800AB920;

void over_act_helper_80036BA4(Actor_Over *pActor, int *pOt)
{
    int       x0, y0;
    int       x1, y1;
    int       width, height;
    int       seq_anim;
    int       count;
    int       color1, color2, color3, color4, color5;
    DR_TPAGE *pTpage;
    short    *game_over_lines_iter;
    int       flag;
    void     *field_2c_polys;
    DVECTOR  *directions;
    POLY_G4  *pPoly;
    LINE_G2  *pLine;

    seq_anim = pActor->field_20_seq_anim;

    game_over_lines_iter = game_over_lines_8009DEBC;
    count = game_over_lines_iter[0];

    directions = pActor->field_168c_directions;
    pLine = pActor->field_38c_lines[GV_Clock_800AB920];
    pPoly = pActor->field_2c_polys[GV_Clock_800AB920];

    game_over_lines_iter++;

    if (seq_anim > 0)
    {
        if (seq_anim < count + 16)
        {
            pActor->field_20_seq_anim = seq_anim + 2;
        }
        else
        {
            pActor->field_20_seq_anim = 0;
        }
    }

    flag = 1;
    if (seq_anim == 0)
    {
        flag = 0;
        seq_anim = 16;
    }

    for (; count > 0; game_over_lines_iter += 4, directions++, count--)
    {
        height = 0;
        width = 0;
        if (flag)
        {
            if (seq_anim < 8)
            {
                width = directions->vx >> seq_anim;
                height = directions->vy >> seq_anim;
                if (count % 4 == 2)
                {
                    width = -width;
                    height = -height;
                }
            }
            seq_anim = seq_anim - 1;
            if (seq_anim < 0)
            {
                break;
            }
        }

        x0 = game_over_lines_iter[0];
        x1 = game_over_lines_iter[2];
        x0 += width;
        color1 = x0 - 160;
        x1 += width * 2;
        color2 = x1 - 160;
        y0 = game_over_lines_iter[1] + height;
        y1 = game_over_lines_iter[3] + height * 2;

        pLine->x0 = x0;
        pLine->y0 = y0;
        pLine->x1 = x1;
        pLine->y1 = y1;

        if (color1 < 0)
        {
            color1 = -color1;
        }
        if (color2 < 0)
        {
            color2 = -color2;
        }

        color1 = 255 - color1;
        color2 = 255 - color2;

        if (color1 > 255)
        {
            color1 = 255;
        }
        if (color2 > 255)
        {
            color2 = 255;
        }

        LSTORE(over_act_helper_80036B40(color1, seq_anim), &pLine->r0);
        LSTORE(over_act_helper_80036B40(color2, seq_anim), &pLine->r1);

        setLineG2(pLine);
        addPrim(pOt, pLine);
        pLine++;

        if (seq_anim >= 8 && seq_anim <= 13)
        {
            width = -(directions->vy >> (seq_anim - 6));
            height = directions->vx >> (seq_anim - 6);

            pPoly->x0 = x1 - width;
            pPoly->y0 = y1 - height;
            pPoly->x1 = x0 - width;
            pPoly->y1 = y0 - height;
            pPoly->x2 = (x0 + x1) / 2;
            pPoly->y2 = (y0 + y1) / 2;
            pPoly->x3 = x0 + width;
            pPoly->y3 = y0 + height;

            LSTORE(0, &pPoly->r0);
            LSTORE(0, &pPoly->r1);
            LSTORE(0x804000, &pPoly->r2);
            LSTORE(0, &pPoly->r3);

            setPolyG4(pPoly);
            setSemiTrans(pPoly, 1);
            addPrim(pOt, pPoly);
            pPoly++;

            pPoly->x0 = x1 - width;
            pPoly->y0 = y1 - height;
            pPoly->x1 = x1 + width;
            pPoly->y1 = y1 + height;
            pPoly->x2 = (x0 + x1) / 2;
            pPoly->y2 = (y0 + y1) / 2;
            pPoly->x3 = x0 + width;
            pPoly->y3 = y0 + height;

            LSTORE(0, &pPoly->r0);
            LSTORE(0, &pPoly->r1);
            LSTORE(0x804000, &pPoly->r2);
            LSTORE(0, &pPoly->r3);

            setPolyG4(pPoly);
            setSemiTrans(pPoly, 1);
            addPrim(pOt, pPoly);
            pPoly++;
        }
    }

    pTpage = &pActor->field_164c_tpages[GV_Clock_800AB920];
    setDrawTPage(pTpage, 1, 1, getTPage(0, 1, 0, 0));
    addPrim(pOt, pTpage);

    if (pActor->field_20_seq_anim == 0)
    {
        if (pActor->field_26_gradient > 32)
        {
            color3 = 48 + (64 - pActor->field_26_gradient) * 4;
        }
        else
        {
            color3 = 48 + pActor->field_26_gradient * 4;
        }

        field_2c_polys = pActor->field_2c_polys[GV_Clock_800AB920];

        if (pActor->field_28_can_continue)
        {
            if (pActor->field_24_option == 0)
            {
                color4 = color3 << 8 | color3 << 16;
                color5 = 0x303000;
            }
            else
            {
                color4 = 0x303000;
                color5 = color3 << 8 | color3 << 16;
            }

            field_2c_polys = over_act_helper_80036A10(field_2c_polys, 70, 126, 0x669D, color4, pOt);
            over_act_helper_80036A10(field_2c_polys, 199, 126, 0x4D9A, color5, pOt);
        }
        else
        {
            pActor->field_24_option = 1;
            color5 = color3 << 8 | color3 << 16;
            over_act_helper_80036A10(field_2c_polys, 128, 126, 0x4D9A, color5, pOt);
        }
    }
}

void over_act_helper_80037128(Actor_Over *pActor, unsigned int *pOt, int shade)
{
    TILE *pTile;
    DR_TPAGE *pTpage;

    if (shade > 0xff)
    {
        shade = 0xff;
    }

    pTile = &pActor->field_165c_tiles[GV_Clock_800AB920];
    LSTORE(shade << 16 | shade << 8 | shade, &pTile->r0);
    setTile(pTile);
    setSemiTrans(pTile, 1);
    pTile->y0 = pTile->x0 = 0;
    pTile->w = 320;
    pTile->h = 240;
    addPrim(pOt, pTile);

    pTpage = &pActor->field_167c_tpages[GV_Clock_800AB920];
    setDrawTPage(pTpage, 1, 1, getTPage(0, 2, 0, 0));
    addPrim(pOt, pTpage);
}

extern int               DG_FrameRate_8009D45C;
extern int               GM_GameStatus_800AB3CC;

extern int               GM_GameOverVox_800AB45C;
int SECTION(".sbss")     GM_GameOverVox_800AB45C;

extern GV_PAD           *GM_CurrentPadData_800AB91C;
GV_PAD *SECTION(".sbss") GM_CurrentPadData_800AB91C;

static inline unsigned char * DG_ChanlOTag(int index)
{
    return DG_Chanl(index)->mOrderingTables[GV_Clock_800AB920];
}

void over_act_8003721C(Actor_Over *pActor)
{
    unsigned int *pOt = (unsigned int *)DG_ChanlOTag(1);
    GV_PAD *pPad;
    unsigned short press;
    int shade;

    if (GV_PauseLevel_800AB928 & 8)
    {
        return;
    }

    if (pActor->field_22_seq < 0x100)
    {
        over_act_helper_80036BA4(pActor, pOt);
        over_act_helper_80037128(pActor, pOt, pActor->field_22_seq * 2);

        if (pActor->field_22_seq == 120)
        {
            if (GM_GameOverVox_800AB45C >= 0)
            {
                GM_StreamPlayStart_80037D1C();
            }

            DG_ReloadPalette_8001FC58();
        }

        pActor->field_22_seq += 3;

        if (pActor->field_22_seq >= 0x100)
        {
            if (pActor->field_20_seq_anim > 0)
            {
                pActor->field_22_seq = 0xff;
                return;
            }

            GV_PauseLevel_800AB928 |= 0x1;
            DG_FreeObjectQueue_800183D4();
            DG_ReloadPalette_8001FC58();
            DG_Set_RGB_800184F4(0, 0, 0);
            DG_FrameRate_8009D45C = 2;
            pActor->field_22_seq = 0x100;
            GM_GameStatus_800AB3CC |= 0x4a6000;
        }
    }
    else if (pActor->field_22_seq == 0x100)
    {
        pPad = &GM_CurrentPadData_800AB91C[2];
        over_act_helper_80036BA4(pActor, pOt);
        GM_GameStatus_800AB3CC &= 0xa7ffffff;
        press = pPad->press;

        if (press & (PAD_START | PAD_CIRCLE))
        {
            pActor->field_22_seq = 0x101;
            pActor->field_26_gradient = 0x20;

            if (pActor->field_24_option == OVER_CONTINUE)
            {
                sub_80032AEC(0, 0x3f, 0x66);
            }
            else
            {
                sub_80032AEC(0, 0x3f, 0x21);
            }

            return;
        }

        if (pActor->field_28_can_continue)
        {
            if ((pActor->field_24_option == OVER_CONTINUE) && (press & PAD_RIGHT))
            {
                sub_80032AEC(0, 0x3f, 0x1f);
                pActor->field_24_option = OVER_EXIT;
                pActor->field_26_gradient = 0;
            }
            else if ((pActor->field_24_option == OVER_EXIT) && (press & PAD_LEFT))
            {
                sub_80032AEC(0, 0x3f, 0x1f);
                pActor->field_24_option = OVER_CONTINUE;
                pActor->field_26_gradient = 0;
            }
        }

        pActor->field_26_gradient = (pActor->field_26_gradient + 1) % 64;
    }
    else
    {
        shade = pActor->field_22_seq - 0x100;

        if (shade > 0xff)
        {
            shade = 0xff;
        }

        over_act_helper_80037128(pActor, pOt, shade);
        over_act_helper_80036BA4(pActor, pOt);

        pActor->field_22_seq += 4;

        if (pActor->field_22_seq > 0x21e)
        {
            pActor->field_22_seq = 0x21e;

            if (GM_StreamStatus_80037CD8() == -1)
            {
                GV_DestroyActor_800151C8(&pActor->field_0_actor);
            }
        }
    }
}

void over_kill_80037514( Actor_Over *pActor )
{
    char *stage_name;

    GV_PauseLevel_800AB928 &= ~1;
    DG_8001844C();
    GM_StreamPlayStop_80037D64();
    GM_GameOverTimer_800AB3D4 = 0;
    if ( pActor->field_24_option == OVER_CONTINUE )
    {
        GM_ContinueStart_8002B62C();
        return;
    }
    if ( ( GM_GameStatusFlag & 0x20 ) || ( GM_DifficultyFlag == DIFFICULTY_VERY_EASY ) )
    {
        GV_ResidentHeapReset_800163B0();
        GV_InitCacheSystem_80015458();
        DG_ClearResidentTexture_8001DB10();
        stage_name = (char *)aInit_0;
        GM_GameStatusFlag &= 0xFFDF;
    }
    else
    {
        stage_name = (char *)aTitle;
    }
    GM_SetArea_8002A7D8( GV_StrCode_80016CCC( stage_name ), stage_name );
    GM_LoadRequest_800AB3D0 = 0x81;
}

void over_loader_80037600(Actor_Over *pActor)
{
    int i;
    short *pLines;
    DVECTOR *pDirections;
    SVECTOR *pScratchpad;

    ((SVECTOR *)getScratchAddr(0))->vz = 0;

    i = game_over_lines_8009DEBC[0];
    pLines = &game_over_lines_8009DEBC[1];
    pDirections = pActor->field_168c_directions;

    for (; i > 0; pLines += 4, pDirections++, i--)
    {
        pScratchpad = (SVECTOR *)getScratchAddr(0);
        pScratchpad[0].vx = pLines[0] - pLines[2];
        pScratchpad[0].vy = pLines[1] - pLines[3];

        VectorNormalSS_80092868(&pScratchpad[0], &pScratchpad[1]);

        pDirections->vx = -pScratchpad[1].vx / 8;
        pDirections->vy = -pScratchpad[1].vy / 8;
    }
}

extern const char    aOverC[]; // = "over.c"

Actor_Over * over_init_800376F8(int can_continue)
{
    Actor_Over *pActor = (Actor_Over *)GV_NewActor_800150E4(0, sizeof(Actor_Over));

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)&over_act_8003721C,
                                  (TActorFunction)&over_kill_80037514, aOverC);

        pActor->field_20_seq_anim = 1;
        pActor->field_22_seq = 0;
        pActor->field_28_can_continue = can_continue;

        over_loader_80037600(pActor);

        if (GM_GameOverVox_800AB45C >= 0)
        {
            GM_VoxStream_80037E40(GM_GameOverVox_800AB45C, 0x40000000);
        }
    }

    GM_Sound_80032C48(0xff000008, 0);
    GM_Sound_80032C48(0xff0000fe, 0);
    GM_Sound_80032C48(0x1ffff0b, 0);

    sub_80032AEC(0, 63, 15);

    DG_FrameRate_8009D45C = 3;
    GM_GameStatus_800AB3CC |= 0x4000000;

    return pActor;
}
