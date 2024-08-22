#include "over.h"
#include "unknown.h"
#include "Game/linkvarbuf.h"

extern int DG_FrameRate_8009D45C;
extern int GM_LoadRequest_800AB3D0;
extern int GM_GameOverTimer_800AB3D4;
extern int GM_GameStatus_800AB3CC;
extern int GV_Clock_800AB920;
extern int GV_PauseLevel_800AB928;

extern GV_PAD           *GM_CurrentPadData_800AB91C;
GV_PAD *SECTION(".sbss") GM_CurrentPadData_800AB91C;

int GM_GameOverVox_800AB45C = -1;

//------------------------------------------------------------------------------

short game_over_lines_8009DEBC[] = {
    120, // table length
    37,  88,  25,  104, 25,  104, 31,  121, 31,  121, 40,  121, 40,  121, 32,  135,
    32,  135, 42,  135, 69,  88,  37,  88,  64,  96,  41,  96,  41,  96,  35,  104,
    35,  104, 38,  113, 38,  113, 45,  113, 62,  100, 45,  100, 45,  100, 40,  108,
    40,  108, 48,  108, 48,  108, 45,  113, 69,  88,  64,  96,  55,  121, 65,  121,
    74,  88,  84,  88,  67,  100, 85,  100, 69,  96,  85,  96,  67,  100, 55,  121,
    69,  96,  74,  88,  84,  88,  85,  96,  85,  100, 87,  121, 87,  121, 78,  121,
    73,  108, 77,  108, 78,  121, 77,  108, 73,  108, 65,  121, 62,  100, 42,  135,
    89,  121, 98,  121, 97,  88,  108, 88,  118, 88,  130, 88,  122, 121, 113, 121,
    113, 121, 117, 104, 117, 104, 108, 121, 108, 121, 103, 121, 103, 121, 102, 104,
    102, 104, 98,  121, 95,  96,  108, 96,  114, 96,  128, 96,  94,  100, 108, 100,
    112, 100, 127, 100, 97,  88,  95,  96,  94,  100, 89,  121, 108, 88,  108, 96,
    108, 100, 108, 108, 112, 100, 108, 108, 114, 96,  118, 88,  127, 100, 122, 121,
    128, 96,  130, 88,  134, 88,  156, 88,  126, 121, 148, 121, 132, 96,  154, 96,
    131, 100, 153, 100, 138, 107, 151, 107, 138, 107, 137, 113, 150, 113, 137, 113,
    134, 88,  132, 96,  131, 100, 126, 121, 150, 113, 148, 121, 151, 107, 153, 100,
    154, 96,  156, 88,  173, 121, 199, 121, 181, 88,  207, 88,  179, 96,  205, 96,
    187, 100, 184, 113, 184, 113, 192, 113, 195, 100, 192, 113, 207, 88,  205, 96,
    204, 100, 199, 121, 181, 88,  179, 96,  178, 100, 173, 121, 178, 100, 187, 100,
    195, 100, 204, 100, 213, 121, 224, 121, 241, 88,  231, 88,  210, 88,  219, 88,
    211, 96,  220, 96,  211, 100, 220, 100, 225, 100, 235, 100, 227, 96,  237, 96,
    225, 100, 221, 108, 231, 88,  227, 96,  235, 100, 224, 121, 237, 96,  241, 88,
    211, 100, 213, 121, 210, 88,  211, 96,  219, 88,  220, 96,  220, 100, 221, 108,
    244, 88,  266, 88,  236, 121, 258, 121, 242, 96,  264, 96,  241, 100, 263, 100,
    247, 113, 260, 113, 248, 108, 261, 108, 248, 108, 247, 113, 244, 88,  242, 96,
    241, 100, 236, 121, 263, 100, 261, 108, 260, 113, 258, 121, 266, 88,  264, 96,
    270, 88,  292, 88,  268, 96,  286, 96,  292, 88,  295, 97,  267, 100, 282, 100,
    275, 107, 277, 107, 262, 121, 272, 121, 275, 107, 272, 121, 277, 107, 285, 135,
    285, 135, 295, 135, 286, 106, 295, 135, 286, 106, 288, 106, 288, 106, 295, 97,
    282, 100, 286, 96,  267, 100, 262, 121, 268, 96,  270, 88,  67,  100, 55,  121,
    53,  125, 47,  135, 53,  125, 279, 125, 282, 135, 47,  135, 282, 135, 279, 125};

//------------------------------------------------------------------------------

char * over_act_helper_80036A10(char *pBuffer, int x, int y, int texture_id, unsigned int color, unsigned int *pOt)
{
    DG_TEX *pTex = DG_GetTexture_8001D830(texture_id);
    SPRT *pSprt = (SPRT *)pBuffer;
    DR_TPAGE *pTpage = (DR_TPAGE *)(pBuffer + sizeof(SPRT));

    pSprt->x0 = x;
    pSprt->y0 = y;
    pSprt->u0 = pTex->off_x;
    pSprt->v0 = pTex->off_y;
    pSprt->w = pTex->w + 1;
    pSprt->h = pTex->h + 1;
    pSprt->clut = pTex->clut;
    LSTORE(color, &pSprt->r0);

    setSprt(pSprt);
    addPrim(pOt, pSprt);

    setDrawTPage(pTpage, 1, 0, pTex->tpage);
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
    return uVar2 | iVar1 << 8 | iVar1 << 16;
}

void over_act_helper_80036BA4(OverWork *work, int *pOt)
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

    seq_anim = work->field_20_seq_anim;

    game_over_lines_iter = game_over_lines_8009DEBC;
    count = game_over_lines_iter[0];

    directions = work->field_168c_directions;
    pLine = work->field_38c_lines[GV_Clock_800AB920];
    pPoly = work->field_2c_polys[GV_Clock_800AB920];

    game_over_lines_iter++;

    if (seq_anim > 0)
    {
        if (seq_anim < count + 16)
        {
            work->field_20_seq_anim = seq_anim + 2;
        }
        else
        {
            work->field_20_seq_anim = 0;
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

    pTpage = &work->field_164c_tpages[GV_Clock_800AB920];
    setDrawTPage(pTpage, 1, 1, getTPage(0, 1, 0, 0));
    addPrim(pOt, pTpage);

    if (work->field_20_seq_anim == 0)
    {
        if (work->field_26_gradient > 32)
        {
            color3 = 48 + (64 - work->field_26_gradient) * 4;
        }
        else
        {
            color3 = 48 + work->field_26_gradient * 4;
        }

        field_2c_polys = work->field_2c_polys[GV_Clock_800AB920];

        if (work->field_28_can_continue)
        {
            if (work->field_24_option == 0)
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
            work->field_24_option = 1;
            color5 = color3 << 8 | color3 << 16;
            over_act_helper_80036A10(field_2c_polys, 128, 126, 0x4D9A, color5, pOt);
        }
    }
}

void over_act_helper_80037128(OverWork *work, unsigned int *pOt, int shade)
{
    TILE *pTile;
    DR_TPAGE *pTpage;

    if (shade > 0xff)
    {
        shade = 0xff;
    }

    pTile = &work->field_165c_tiles[GV_Clock_800AB920];
    LSTORE(shade << 16 | shade << 8 | shade, &pTile->r0);
    setTile(pTile);
    setSemiTrans(pTile, 1);
    pTile->y0 = pTile->x0 = 0;
    pTile->w = 320;
    pTile->h = 240;
    addPrim(pOt, pTile);

    pTpage = &work->field_167c_tpages[GV_Clock_800AB920];
    setDrawTPage(pTpage, 1, 1, getTPage(0, 2, 0, 0));
    addPrim(pOt, pTpage);
}

void over_act_8003721C(OverWork *work)
{
    unsigned int *pOt = (unsigned int *)DG_ChanlOTag(1);
    GV_PAD *pPad;
    unsigned short press;
    int shade;

    if (GV_PauseLevel_800AB928 & 8)
    {
        return;
    }

    if (work->field_22_seq < 0x100)
    {
        over_act_helper_80036BA4(work, pOt);
        over_act_helper_80037128(work, pOt, work->field_22_seq * 2);

        if (work->field_22_seq == 120)
        {
            if (GM_GameOverVox_800AB45C >= 0)
            {
                GM_StreamPlayStart_80037D1C();
            }

            DG_ReloadPalette_8001FC58();
        }

        work->field_22_seq += 3;

        if (work->field_22_seq >= 0x100)
        {
            if (work->field_20_seq_anim > 0)
            {
                work->field_22_seq = 0xff;
                return;
            }

            GV_PauseLevel_800AB928 |= 1;
            DG_FreeObjectQueue_800183D4();
            DG_ReloadPalette_8001FC58();
            DG_Set_RGB_800184F4(0, 0, 0);
            DG_FrameRate_8009D45C = 2;
            work->field_22_seq = 0x100;
            GM_GameStatus_800AB3CC |= (GAME_FLAG_BIT_14 | GAME_FLAG_BIT_15 | GAME_FLAG_BIT_18 | GAME_FLAG_BIT_20 | GAME_FLAG_BIT_23);
        }
    }
    else if (work->field_22_seq == 0x100)
    {
        pPad = &GM_CurrentPadData_800AB91C[2];
        over_act_helper_80036BA4(work, pOt);
        GM_GameStatus_800AB3CC &= ~(GAME_FLAG_BIT_28 | GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31);
        press = pPad->press;

        if (press & (PAD_START | PAD_CIRCLE))
        {
            work->field_22_seq = 0x101;
            work->field_26_gradient = 0x20;

            if (work->field_24_option == OVER_CONTINUE)
            {
                sub_80032AEC(0, 0x3f, 0x66);
            }
            else
            {
                sub_80032AEC(0, 0x3f, 0x21);
            }

            return;
        }

        if (work->field_28_can_continue)
        {
            if ((work->field_24_option == OVER_CONTINUE) && (press & PAD_RIGHT))
            {
                sub_80032AEC(0, 0x3f, 0x1f);
                work->field_24_option = OVER_EXIT;
                work->field_26_gradient = 0;
            }
            else if ((work->field_24_option == OVER_EXIT) && (press & PAD_LEFT))
            {
                sub_80032AEC(0, 0x3f, 0x1f);
                work->field_24_option = OVER_CONTINUE;
                work->field_26_gradient = 0;
            }
        }

        work->field_26_gradient = (work->field_26_gradient + 1) % 64;
    }
    else
    {
        shade = work->field_22_seq - 0x100;

        if (shade > 0xff)
        {
            shade = 0xff;
        }

        over_act_helper_80037128(work, pOt, shade);
        over_act_helper_80036BA4(work, pOt);

        work->field_22_seq += 4;

        if (work->field_22_seq > 0x21e)
        {
            work->field_22_seq = 0x21e;

            if (GM_StreamStatus_80037CD8() == -1)
            {
                GV_DestroyActor_800151C8(&work->field_0_actor);
            }
        }
    }
}

void over_kill_80037514( OverWork *work )
{
    char *stage_name;

    GV_PauseLevel_800AB928 &= ~1;
    DG_ResetObjectQueue_8001844C();
    GM_StreamPlayStop_80037D64();
    GM_GameOverTimer_800AB3D4 = 0;
    if ( work->field_24_option == OVER_CONTINUE )
    {
        GM_ContinueStart_8002B62C();
        return;
    }
    if ( ( GM_GameStatusFlag & 0x20 ) || ( GM_DifficultyFlag == DIFFICULTY_VERY_EASY ) )
    {
        GV_ResidentHeapReset_800163B0();
        GV_InitCacheSystem_80015458();
        DG_ClearResidentTexture_8001DB10();
        stage_name = "init";
        GM_GameStatusFlag &= ~0x20;
    }
    else
    {
        stage_name = "title";
    }
    GM_SetArea_8002A7D8( GV_StrCode_80016CCC( stage_name ), stage_name );
    GM_LoadRequest_800AB3D0 = 0x81;
}

void over_loader_80037600(OverWork *work)
{
    int i;
    short *pLines;
    DVECTOR *pDirections;
    SVECTOR *pScratchpad;

    ((SVECTOR *)getScratchAddr(0))->vz = 0;

    i = game_over_lines_8009DEBC[0];
    pLines = &game_over_lines_8009DEBC[1];
    pDirections = work->field_168c_directions;

    for (; i > 0; pLines += 4, pDirections++, i--)
    {
        pScratchpad = (SVECTOR *)getScratchAddr(0);
        pScratchpad[0].vx = pLines[0] - pLines[2];
        pScratchpad[0].vy = pLines[1] - pLines[3];

        VectorNormalSS(&pScratchpad[0], &pScratchpad[1]);

        pDirections->vx = -pScratchpad[1].vx / 8;
        pDirections->vy = -pScratchpad[1].vy / 8;
    }
}

OverWork * over_init_800376F8(int can_continue)
{
    OverWork *work = (OverWork *)GV_NewActor_800150E4(0, sizeof(OverWork));

    if (work)
    {
        GV_SetNamedActor_8001514C(&work->field_0_actor, (TActorFunction)&over_act_8003721C,
                                  (TActorFunction)&over_kill_80037514, "over.c");

        work->field_20_seq_anim = 1;
        work->field_22_seq = 0;
        work->field_28_can_continue = can_continue;

        over_loader_80037600(work);

        if (GM_GameOverVox_800AB45C >= 0)
        {
            GM_VoxStream_80037E40(GM_GameOverVox_800AB45C, 0x40000000);
        }
    }

    GM_Sound_80032C48(0xff000008, 0);
    GM_Sound_80032C48(0xff0000fe, 0);
    GM_Sound_80032C48(0x01ffff0b, 0);

    sub_80032AEC(0, 63, 15);

    DG_FrameRate_8009D45C = 3;
    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_27;

    return work;
}
