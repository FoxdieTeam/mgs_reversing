#include "menuman.h"
#include "radio.h"
#include "Game/game.h"
#include "libdg/libdg.h"

extern GV_Heap MemorySystems_800AD2F0[ 3 ];
extern int     GV_Clock_800AB920;
extern DG_TEX  gTextureRecs_800B1F50[512];

extern unsigned char menu_current_debug_screen_800ABB20;
unsigned char        SECTION(".sbss") menu_current_debug_screen_800ABB20;

extern short word_800ABB22;
short        SECTION(".sbss") word_800ABB22;

extern DG_TEX *dword_800ABB24;
DG_TEX        *SECTION(".sbss") dword_800ABB24;

int menu_draw_mem_debug_80043678(Actor_MenuMan *work, unsigned int *pOt)
{
    GV_Heap             *pHeap;
    LINE_F2             *pLine;
    int                  i;
    GV_MemoryAllocation *pAlloc;
    int                  heap_size;
    char                *alloc_start;
    LINE_G4             *pLine2;
    int                  alloc_len;
    int                  alloc_len2;
    int                  used;
    int                  units;
    int                  color;
    int                  allocated;
    int                  size;
    int                  x1;

    pHeap = MemorySystems_800AD2F0;

    NEW_PRIM(pLine, work);
    setXY2(pLine, 272, 120, 272, 168);

    LSTORE(0xFF0000, &pLine->r0);

    setLineF2(pLine);
    addPrim(pOt, pLine);

    used = 1;
    for (i = 0; i < 3; i++, pHeap++)
    {
        size = pHeap->mEndAddr - pHeap->mStartAddr;
        pAlloc = pHeap->mAllocs;
        heap_size = size;

        if (heap_size == 0)
        {
            continue;
        }

        allocated = 0;

        for (units = pHeap->mUnitsCount; units > 0; units--, pAlloc++)
        {
            alloc_start = pAlloc->mPDataStart;

            if (pAlloc->mAllocType == 0)
            {
                continue;
            }

            if (pAlloc->mAllocType == 1)
            {
                color = 0xFFFFFF;

                while (pAlloc[1].mAllocType == 1 && units > 2)
                {
                    pAlloc++;
                    units--;
                }
            }
            else
            {
                color = 0xFF00;

                while (pAlloc[1].mAllocType >= 2 && units > 2)
                {
                    pAlloc++;
                    units--;
                }
            }

            alloc_len = (alloc_start - (char *)pHeap->mStartAddr) * 240;
            alloc_len = (alloc_len / heap_size) + 32;

            x1 = 120 + i * 16;

            size = (char *)pAlloc[1].mPDataStart - alloc_start;

            alloc_len2 = ((char *)pAlloc[1].mPDataStart - (char *)pHeap->mStartAddr) * 240;
            alloc_len2 = (alloc_len2 / heap_size) + 32;

            if (used < 256)
            {
                NEW_PRIM(pLine2, work);
                setXY4(pLine2, alloc_len, x1, alloc_len2, x1, alloc_len2, 134 + i * 16, alloc_len, 134 + i * 16);
                LSTORE(0, &pLine2->r0);
                LSTORE(color, &pLine2->r1);
                LSTORE(color, &pLine2->r2);
                LSTORE(0, &pLine2->r3);

                setLineG4(pLine2);
                addPrim(pOt, pLine2);
            }

            allocated += size;
            used++;
        }

        menu_number_draw_80042F78(work, pOt, 300, 168 - ((3 - i) * 12), (allocated * 100) / heap_size, 1);
    }

    return used;
}

short word_800AB660 = 0;
short word_800AB662 = 0;
int   dword_800AB664 = 0;
int   dword_800AB668 = 0;
short word_800AB66C = 0;
short word_800AB66E = 0;
int   dword_800AB670 = 0;

extern short          N_ChanlPerfMax_800AB980;
extern unsigned short word_800AB982;

extern GV_PAD GV_PadData_800B05C0[4];

extern unsigned short gOldRootCnt_800B1DC8[32];

int menu_draw_pow_debug_80043A24(Actor_MenuMan *work, unsigned int *pOt)
{
    int             prims_used, left, right, bottom, idx, i;
    unsigned short *pCount;
    unsigned        first_count;
    LINE_G4        *pLine;
    unsigned short  delta;
    LINE_G2        *pLine2;

    prims_used = 0;

    pCount = gOldRootCnt_800B1DC8;
    first_count = *pCount++;

    left = 0;
    bottom = 136;

    for (idx = N_ChanlPerfMax_800AB980 - 1; idx > 0; idx--)
    {
        right = (*pCount++ - first_count) & 0xFFFF;

        if (right > 511)
        {
            right = 511;
        }
        right = right * 240 / 512;

        // Draw top blue bar
        NEW_PRIM(pLine, work);

        setXY4(pLine, left + 32, bottom, right + 32, 136, right + 32, 150, left + 32, bottom + 14);

        LSTORE(0, &pLine->r0);
        LSTORE(0xFF0000, &pLine->r1);
        LSTORE(0xFF0000, &pLine->r2);
        LSTORE(0, &pLine->r3);

        setLineG4(pLine);
        addPrim(pOt, pLine);
        prims_used++;

        bottom = 136; // to get a match
        left = right;
    }

    if (GV_PadData_800B05C0[1].press & PAD_L1)
    {
        dword_800AB668 = (dword_800AB668 + 1) % N_ChanlPerfMax_800AB980;
        dword_800AB664 = 0;
        word_800AB660 = 0;
    }

    if (dword_800AB668 == 0)
    {
        delta = gOldRootCnt_800B1DC8[N_ChanlPerfMax_800AB980 - 1] - gOldRootCnt_800B1DC8[1];
    }
    else
    {
        delta = gOldRootCnt_800B1DC8[dword_800AB668] - gOldRootCnt_800B1DC8[dword_800AB668 - 1];
        menu_number_draw_80042F78(work, pOt, 270, 168, dword_800AB668, 1);
    }

    dword_800AB664 += delta;
    if (++word_800AB660 >= 128)
    {
        word_800AB662 = dword_800AB664 / word_800AB660;
        word_800AB660 = 0;
        dword_800AB664 = 0;
    }

    menu_number_draw_80042F78(work, pOt, 300, 168, word_800AB662, 1);
    dword_800AB670 += (unsigned short)(gOldRootCnt_800B1DC8[N_ChanlPerfMax_800AB980 - 1] - first_count);

    if (++word_800AB66C >= 128)
    {
        word_800AB66E = dword_800AB670 / word_800AB66C;
        word_800AB66C = 0;
        dword_800AB670 = 0;
    }

    menu_number_draw_80042F78(work, pOt, 240, 168, word_800AB66E, 1);
    menu_number_draw_80042F78(work, pOt, 300, 144,
                              (unsigned short)(gOldRootCnt_800B1DC8[N_ChanlPerfMax_800AB980 - 1] - first_count), 1);

    right = (unsigned short)(word_800AB982 - first_count);
    if (right > 511)
    {
        right = 511;
    }
    right = right * 240 / 512;

    bottom = 152; // to get a match
    i = 32;       // to get a match
    right += 32;

    // Draw bottom red bar
    NEW_PRIM(pLine, work);

    setXY4(pLine, 32, 152, right, 152, right, 166, 32, 166);

    LSTORE(0, &pLine->r0);
    LSTORE(0xFF, &pLine->r1);
    LSTORE(0xFF, &pLine->r2);
    LSTORE(0, &pLine->r3);

    setLineG4(pLine);
    addPrim(pOt, pLine);
    prims_used++;

    menu_number_draw_80042F78(work, pOt, 300, 156, (unsigned short)(word_800AB982 - first_count), 1);

    // Draw vertical bars
    for (i = 0; i <= 240; i += 24)
    {
        NEW_PRIM(pLine2, work);
        bottom = 132; // to get a match

        setXY2(pLine2, i + 32, 132, i + 32, 164);

        // Red for centre bar otherwise green
        if (i == 120)
        {
            LSTORE(0xFF, &pLine2->r0);
        }
        else
        {
            LSTORE(0xFF00, &pLine2->r0);
        }
        LSTORE(0, &pLine2->r1);

        setLineG2(pLine2);
        addPrim(pOt, pLine2);
        prims_used++;
    }

    return prims_used;
}

int menu_draw_ply_debug_80043FD0(Actor_MenuMan *pMenuMan, unsigned int *pOt)
{
    u_char       *chnlOt;
    int           numOTEntries;
    u_char       *otMin;
    u_char       *curPrim;
    int           primCount;
    int           totalprimCount;

    LINE_F2      *lineF2;
    LINE_G4      *lineG4;
    int           x_0_1;
    int           y_0_1;
    int           x_2_3;
    int           y_2_3;

    int           i;

    int           returnVal;

    totalprimCount = 0;
    returnVal = 0;
    y_0_1 = 0xa8;
    y_2_3 = 0xa8;

    chnlOt = DG_Chanl(0)->mOrderingTables[1 - GV_Clock_800AB920];
    numOTEntries = DG_Chanl(0)->word_6BC374_8 - 4;

    NEW_PRIM(lineF2, pMenuMan);

    setXY2(lineF2, 0x20, 0x76, 0x110, 0x76);
    LSTORE(0x800000, &lineF2->r0);
    setLineF2(lineF2);
    addPrim(pOt, lineF2);

    for (i = 0; i < 16; i++)
    {
        otMin = chnlOt + ((i << numOTEntries) * 4);
        for (curPrim = chnlOt + (((i + 1) << numOTEntries) * 4), primCount = 0;
             (otMin < curPrim) || (curPrim < chnlOt); curPrim = nextPrim(curPrim))
        {
            if (getlen(curPrim) != 0)
            {
                primCount++;
            }
        }

        totalprimCount += primCount;
        x_0_1 = i * 15;
        x_2_3 = x_0_1 + 13;
        x_0_1 += 32;
        x_2_3 += 32;

        if (primCount > 0)
        {
            primCount = primCount / 2;

            if (primCount > 176)
            {
                primCount = 176;
            }

            NEW_PRIM(lineG4, pMenuMan);
            setXY4(lineG4, x_0_1, y_0_1, x_0_1, y_0_1 - primCount, x_2_3, y_2_3 - primCount, x_2_3, y_2_3);
            LSTORE(0, &lineG4->r0);
            LSTORE(0xff00, &lineG4->r1);
            returnVal++;
            LSTORE(0xff00, &lineG4->r2);
            LSTORE(0, &lineG4->r3);
            setLineG4(lineG4);
            addPrim(pOt, lineG4);
        }
        else
        {
            NEW_PRIM(lineG4, pMenuMan);
            setXY4(lineG4, x_0_1, y_0_1, x_0_1, y_0_1, x_2_3, y_2_3, x_2_3, y_2_3);
            LSTORE(0, &lineG4->r0);
            LSTORE(0xff0000, &lineG4->r1);
            LSTORE(0xff0000, &lineG4->r2);
            LSTORE(0, &lineG4->r3);
            setLineG4(lineG4);
            addPrim(pOt, lineG4);
        }
    }

    menu_number_draw_80042F78(pMenuMan, pOt, 0x110, 0x9c, totalprimCount, 1);

    return returnVal;
}

int menu_draw_obj_debug_800442E4(Actor_MenuMan *work, unsigned int *pOt)
{
    DG_OBJS **ppQueue;
    DG_OBJS  *pObjs;
    DG_OBJ   *pObj;
    LINE_G2  *pLine;
    LINE_G4  *pLine2;
    int       object_count;
    int       num_models;
    int       total;
    int       clip;

    unsigned int color;
    int          lhs;
    int          rhs;
    int          returnVal;
    int          last_color;

    int bottom, top;

    rhs = 0;
    lhs = 0;

    top = 152;
    last_color = 0;
    returnVal = 0;

    clip = 0;
    total = 0;

    object_count = DG_Chanl(0)->mTotalObjectCount;
    ppQueue = DG_Chanl(0)->mQueue;

    for (; object_count > 0; object_count--)
    {
        pObjs = *ppQueue++;

        NEW_PRIM(pLine, work);
        setXY2(pLine, rhs + 32, top - 6, rhs + 32, top + 19);

        LSTORE(0xFF0000, &pLine->r0);
        LSTORE(0, &pLine->r1);

        setLineG2(pLine);
        addPrim(pOt, pLine);

        pObj = pObjs->objs;
        for (num_models = pObjs->n_models; num_models > 0; num_models--)
        {
            rhs++;

            color = 0xFF00;

            if (pObj->bound_mode == 0)
            {
                color = 0xFF;
                clip++;
            }

            if (last_color == 0)
            {
                last_color = color;
            }

            bottom = 152;

            if (color != last_color)
            {
                NEW_PRIM(pLine2, work);

                setXY4(pLine2, lhs + 32, top, rhs + 32, bottom, rhs + 32, 165, lhs + 32, top + 13);
                top = bottom;

                LSTORE(0, &pLine2->r0);
                LSTORE(last_color, &pLine2->r1);
                LSTORE(last_color, &pLine2->r2);
                LSTORE(0, &pLine2->r3);

                setLineG4(pLine2);
                addPrim(pOt, pLine2);

                returnVal++;
                lhs = rhs;
                last_color = color;
            }

            pObj++;
            total++;
        }
    }

    bottom = 152;

    if (lhs != rhs)
    {
        NEW_PRIM(pLine2, work);
        returnVal++;

        setXY4(pLine2, lhs + 32, top, rhs + 32, bottom, rhs + 32, 165, (bottom = lhs + 32) /* to get a match */,
               top + 13);

        LSTORE(0, &pLine2->r0);
        LSTORE(last_color, &pLine2->r1);
        LSTORE(last_color, &pLine2->r2);
        LSTORE(0, &pLine2->r3);

        setLineG4(pLine2);
        addPrim(pOt, pLine2);
    }

    menu_Text_XY_Flags_80038B34(300, 128, 0x1);
    menu_Text_80038C38("TOTAL %d\n", total);
    menu_Text_80038C38("CLIP %d\n", clip);

    return returnVal;
}

extern GV_PAD GV_PadData_800B05C0[4];

int menu_draw_tex_debug_800445F8(Actor_MenuMan *work, unsigned int *pOt)
{
    const int textureRecsCount = sizeof(gTextureRecs_800B1F50) / sizeof(gTextureRecs_800B1F50[0]);
    short     x0, y0;
    int       i;
    DG_TEX   *iterTex;
    POLY_FT4 *pPoly;
    int       width, height;
    int       offx, offy;
    int       direction;

    iterTex = dword_800ABB24;
    direction = 0;
    if (GV_PadData_800B05C0[0].status & PAD_RIGHT)
    {
        direction = 1;
    }
    else if (GV_PadData_800B05C0[0].status & PAD_LEFT)
    {
        direction = -1;
    }
    else
    {
        word_800ABB22 = -1;
    }
    if (direction != 0)
    {
        if (word_800ABB22 <= 0)
        {
            for (i = textureRecsCount; i > 0; i--)
            {
                iterTex += direction;
                if (iterTex == &gTextureRecs_800B1F50[textureRecsCount])
                {
                    iterTex -= textureRecsCount;
                }
                if (iterTex < &gTextureRecs_800B1F50[0])
                {
                    iterTex = &gTextureRecs_800B1F50[textureRecsCount - 1];
                }
                if (iterTex->field_0_hash != 0)
                {
                    break;
                }
            }
            if (word_800ABB22 < 0)
            {
                word_800ABB22 = 10;
            }
            else if (word_800ABB22 == 0)
            {
                word_800ABB22 = 2;
            }
        }
        word_800ABB22--;
    }

    if (iterTex->field_0_hash == 0)
    {
        return 0;
    }

    dword_800ABB24 = iterTex;

    menu_Text_XY_Flags_80038B34(300, 128, 1);
    menu_Text_80038C38("No %d\n", iterTex - gTextureRecs_800B1F50);
    menu_Text_80038C38("ID %d\n", iterTex->field_0_hash);
    menu_Text_80038C38("COL %d\n", iterTex->field_2_bUsed.c[1]);
    menu_Text_80038C38("x %d y %d\n", iterTex->field_8_offx, iterTex->field_9_offy);
    menu_Text_80038C38("w %d h %d\n", iterTex->field_A_width + 1, iterTex->field_B_height + 1);

    NEW_PRIM(pPoly, work);

    LSTORE(0x808080, &pPoly->r0);

    setPolyFT4(pPoly);

    pPoly->clut = iterTex->field_6_clut;
    pPoly->tpage = iterTex->field_4_tPage;

    width = iterTex->field_A_width;
    height = iterTex->field_B_height;
    offx = iterTex->field_8_offx;
    offy = iterTex->field_9_offy;

    x0 = (319 - width) / 2;
    y0 = (239 - height) / 2;

    pPoly->x0 = x0;
    pPoly->y0 = y0;
    pPoly->y1 = y0;
    pPoly->x1 = x0 + width;
    pPoly->x2 = x0;
    pPoly->y2 = y0 + height;
    pPoly->y3 = y0 + height;
    pPoly->x3 = x0 + width;
    pPoly->u0 = offx;
    pPoly->v0 = offy;
    pPoly->u1 = offx + width;
    pPoly->v1 = offy;
    pPoly->u2 = offx;
    pPoly->v2 = offy + height;
    pPoly->u3 = offx + width;
    pPoly->v3 = offy + height;

    addPrim(pOt, pPoly);
    return 1;
}

extern int GM_PlayerStatus_800ABA50;
extern int GV_PauseLevel_800AB928;

TUnkRadioFn menu_debug_screens_8009E730[] = {
    menu_draw_mem_debug_80043678,
    menu_draw_pow_debug_80043A24,
    menu_draw_ply_debug_80043FD0,
    menu_draw_obj_debug_800442E4,
    menu_draw_tex_debug_800445F8
};

int MENU_PrimUse_800AB68C = 0;

char *menu_debug_screen_labels_8009E744[] = {
    "",
    "mem",
    "pow",
    "ply",
    "obj",
    "tex",
};

void menu_draw_debug_screen_800448C0(Actor_MenuMan *work, unsigned int *pOt)
{
    mts_read_pad_8008C25C(2);
    if (GM_GameStatus_800AB3CC & GAME_FLAG_BIT_25)
    {
        menu_draw_pow_debug_80043A24(work, pOt);
        return;
    }
    if (!(GM_PlayerStatus_800ABA50 & PLAYER_PREVENT_WEAPON_ITEM_SWITCH) && GV_PauseLevel_800AB928 != 0 &&
        (GV_PadData_800B05C0[0].press & PAD_L1))
    {
        if (menu_current_debug_screen_800ABB20 == 5)
        {
            GV_PauseLevel_800AB928 &= ~4;
        }
        menu_current_debug_screen_800ABB20++;
        if (menu_current_debug_screen_800ABB20 == 6)
        {
            menu_current_debug_screen_800ABB20 = 0;
        }
        if (menu_current_debug_screen_800ABB20 == 5)
        {
            GV_PauseLevel_800AB928 |= 4;
        }
    }
    else if (menu_current_debug_screen_800ABB20 != 0)
    {
        menu_Text_XY_Flags_80038B34(300, 8, 1);
        menu_draw_num_80038D10(MENU_PrimUse_800AB68C * 100 / 8192);
        menu_Text_XY_Flags_80038B34(300, 112, 1);
        menu_Text_80038C38(menu_debug_screen_labels_8009E744[menu_current_debug_screen_800ABB20]);
        menu_debug_screens_8009E730[menu_current_debug_screen_800ABB20 - 1](work, pOt);
    }
}

void menu_viewer_init_80044A70(Actor_MenuMan *param_1)
{
    menu_current_debug_screen_800ABB20 = 0;
    dword_800ABB24 = gTextureRecs_800B1F50;
    word_800ABB22 = -1;
}

void menu_viewer_kill_80044A90(Actor_MenuMan *work)
{
    menu_current_debug_screen_800ABB20 = 0;
    return;
}
