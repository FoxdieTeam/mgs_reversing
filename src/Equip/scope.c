#include "scope.h"
#include "Menu/menuman.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Thing/sight.h"
#include "chara/snake/sna_init.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "libgcl/hash.h"

extern OBJECT          *GM_PlayerBody_800ABA20;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern int              GV_PauseLevel_800AB928;
extern int              GV_Clock_800AB920;
extern int              DG_CurrentGroupID_800AB968;
extern int              dword_8009F604;
extern GV_PAD           GV_PadData_800B05C0[4];
extern GM_Camera        GM_Camera_800B77E8;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern CONTROL      *GM_PlayerControl_800AB9F4;
extern short            dword_800ABBDC;
extern short            dword_800ABBD4;

short scope_created_8009F2C4 = 0;

SVECTOR svecs_8009F2C8[2] = {{0, 0, 0, 0}, {0, 0, 3200, 0}};

// Can't give a better name for now.
void addLinePrimUnderCondition_80062320(void *ot, void *line)
{
    if ((GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000) == 0)
    {
        addPrim(ot, line);
    }
}

int scope_act_helper_helper_8006237C(ScopeWork *work)
{
    MATRIX *pMtx; // $a2
    DG_OBJS *objs; // $v0
    int bCalcLen; // $s2
    int vecLen; // $v0
    MATRIX mtx; // [sp+18h] [-30h] BYREF
    SVECTOR vecs[2]; // [sp+38h] [-10h] BYREF

    if ( GM_GameStatus_800AB3CC < 0 )
    {
        pMtx = &DG_Chanl(0)->field_30_eye;
    }
    else
    {
        objs = GM_PlayerBody_800ABA20->objs;
        pMtx = &mtx;
        mtx = GM_PlayerBody_800ABA20->objs->world;
        mtx.t[0] = gUnkCameraStruct_800B77B8.field_0.vx;
        mtx.t[1] = gUnkCameraStruct_800B77B8.field_0.vy;
        mtx.t[2] = gUnkCameraStruct_800B77B8.field_0.vz;
    }
    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(svecs_8009F2C8, vecs, 2);
    bCalcLen = 0;
    if ( sub_80028454(work->field_50_pMap->field_8_hzd, vecs, &vecs[1], 15, 129) )
    {
        sub_80028890(&vecs[1]);
        bCalcLen = 1;
    }

    vecLen = 3200;
    if ( bCalcLen != 0 )
    {
        GV_SubVec3_80016D40(&vecs[1], vecs, vecs);
        vecLen = GV_VecLen3_80016D80(vecs);
    }

    return vecLen;
}

void setSideLinesPairPosition_800624BC(LINE_F2 *lines, int x, int y)
{
    int offsetIndex;
    lines->x1 = x;
    lines->x0 = x;
    offsetIndex = 4;
    lines[offsetIndex].x1 = 320 - x;
    lines[offsetIndex].x0 = 320 - x;
    lines[offsetIndex].y0 = y;
    lines->y0 = y;
    lines[offsetIndex].y1 = 240 - y; // Bottom y.
    lines->y1 = 240 - y;
}

void drawSideLines_800624F4(LINE_F2 *lines, int param_2)
{
    int i;
    int x;
    int y;

    x = param_2 + 258;
    y = 66 - (param_2 * 9) / 15;

    for (i = 0; i < 4; i++)
    {
        setSideLinesPairPosition_800624BC(lines, x, y);
        lines++;
        x += 15;
        y -= 9;
    }
}

void scope_act_helper_8006258C(ScopeWork *work)
{
    int      iVar1;
    int      iVar3;
    int      temp;
    u_char  *ot;
    LINE_F2 *lines;
    int      i;

    temp = work->field_58;

    if (GV_PauseLevel_800AB928 == 0)
    {
        work->field_58++;
    }

    if (temp >= 6)
    {
        temp = 6;
        work->field_9C_flags |= 1 << GV_Clock_800AB920;
    }

    iVar1 = 12 * temp;
    iVar3 = 320 - iVar1;

    ot = DG_ChanlOTag(1);
    lines = work->field_74_sideLine_F2s[GV_Clock_800AB920];

    for (i = 0; i < 4; i++)
    {
        setSideLinesPairPosition_800624BC(lines, iVar3, 66 - (((iVar3 - 258) * 9) / 15));
        addLinePrimUnderCondition_80062320(ot, lines);
        addLinePrimUnderCondition_80062320(ot, lines + 4);

        iVar3 += iVar1 / 4;
        lines++;
    }
}

void managePadInput_800626D0(ScopeWork *work, unsigned short pad_status)
{
    SVECTOR vec;
    int zoomLevel;
    int iVar5;
    int vx;
    int vy;
    int vxMin;
    int vxMax;
    CONTROL *pCtrl;
    short *pRectOffset; // (x, y) offset of the top left corner of the moving rectangle.

    zoomLevel = GM_Camera_800B77E8.field_20_zoomLevel;
    pRectOffset = work->field_84_rectOffset;

    if (GM_PlayerControl_800AB9F4)
    {
        vx = work->field_6C_turn_vec.vx;

        if (vx < dword_800ABBDC)
        {
            vx = dword_800ABBDC;
        }
        else if (vx > dword_800ABBD4)
        {
            vx = dword_800ABBD4;
        }

        work->field_6C_turn_vec.vx = vx;
    }

    if ((pad_status & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT)) != 0)
    {
        vx = work->field_6C_turn_vec.vx;
        vy = work->field_6C_turn_vec.vy;

        vec = work->field_64_vec;

        if (GM_PlayerControl_800AB9F4)
        {
            vec.vx = GM_PlayerControl_800AB9F4->field_4C_turn.vx;
        }

        if (zoomLevel <= 1023)
        {
            iVar5 = 16;
        }
        else
        {
            if (zoomLevel < 2048)
            {
                iVar5 = 4;
            }
            else
            {
                iVar5 = 1;
            }
        }

        vxMin = vec.vx - 512;
        vxMax = vec.vx + 512;

        if (GM_PlayerControl_800AB9F4)
        {
            if (vxMin < dword_800ABBDC)
            {
                vxMin = dword_800ABBDC;
            }

            if (vxMax > dword_800ABBD4)
            {
                vxMax = dword_800ABBD4;
            }
        }

        if ((pad_status & (PAD_UP | PAD_DOWN)) != 0)
        {
            if ((pad_status & PAD_UP) != 0)
            {
                vx -= iVar5;

                if (--pRectOffset[1] < -8)
                {
                    pRectOffset[1] = -8;
                }
            }
            else
            {
                vx += iVar5;

                if (++pRectOffset[1] > 8)
                {
                    pRectOffset[1] = 8;
                }
            }
        }

        if (vx < vxMin)
        {
            vx = vxMin;
        }

        if (vx > vxMax)
        {
            vx = vxMax;
        }

        if ((pad_status & (PAD_LEFT | PAD_RIGHT)) != 0)
        {
            if ((pad_status & PAD_RIGHT) != 0)
            {
                pRectOffset[0]++;

                vy = vy - iVar5;
                vy &= 0xfff;

                if (pRectOffset[0] > 8)
                {
                    pRectOffset[0] = 8;
                }
            }
            else
            {
                pRectOffset[0]--;

                vy = vy + iVar5;
                vy &= 0xfff;

                if (pRectOffset[0] < -8)
                {
                    pRectOffset[0] = -8;
                }
            }
        }

        work->field_6C_turn_vec.vx = vx;
        work->field_6C_turn_vec.vy = vy;
    }
    else if (GV_PauseLevel_800AB928 == 0)
    {
        if (pRectOffset[0] != 0)
        {
            iVar5 = (pRectOffset[0] > 0) ? -1 : 1;
            pRectOffset[0] += iVar5;
        }

        if (pRectOffset[1] != 0)
        {
            iVar5 = (pRectOffset[1] > 0) ? -1 : 1;
            pRectOffset[1] += iVar5;
        }
    }

    pCtrl = GM_PlayerControl_800AB9F4;

    if (pCtrl)
    {
        pCtrl->field_4C_turn = work->field_6C_turn_vec;
        pCtrl->field_8_rot = pCtrl->field_4C_turn;
    }
}

void scope_act_helper_80062998(ScopeWork *work, u_char *pOt, int pad_status)
{
    short    zoomLineLength;
    int      iVar3;
    int      zoomLevel;
    int      maxZoomLevel;
    LINE_F2 *pSideLine_f2;
    LINE_F3 *pZoomLevelLine_F3;
    int      i;
    int      temp;

    zoomLevel = GM_Camera_800B77E8.field_20_zoomLevel;
    pSideLine_f2 = work->field_74_sideLine_F2s[GV_Clock_800AB920];
    pZoomLevelLine_F3 = work->field_90_zoomLevelLine_F3s[GV_Clock_800AB920];

    maxZoomLevel = 3200;

    if (pad_status & (PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT | PAD_CROSS | PAD_CIRCLE))
    {
        temp = scope_act_helper_helper_8006237C(work);

        if (temp < 3200)
        {
            maxZoomLevel = temp;
        }

        if (temp < 320)
        {
            maxZoomLevel = 320;
        }

        if (maxZoomLevel < zoomLevel)
        {
            zoomLevel = maxZoomLevel;
        }
    }

    iVar3 = work->field_62;

    if ((((pad_status & PAD_CIRCLE) != 0) && (zoomLevel != maxZoomLevel)) || (((pad_status & PAD_CROSS) != 0) && (zoomLevel != 320)))
    {
        if (((pad_status & PAD_CIRCLE) != 0) && (zoomLevel != maxZoomLevel))
        {
            zoomLevel += zoomLevel / 32;

            if (zoomLevel >= maxZoomLevel)
            {
                zoomLevel = maxZoomLevel;
            }
            else
            {
                iVar3++;
            }

            if (iVar3 == 15)
            {
                iVar3 = 0;
            }
        }
        else
        {
            zoomLevel -= zoomLevel / 32;

            if (zoomLevel <= 320)
            {
                zoomLevel = 320;
            }
            else
            {
                iVar3--;
            }

            if (iVar3 == -1)
            {
                iVar3 = 14;
            }
        }

        drawSideLines_800624F4(pSideLine_f2, iVar3);
        work->field_62 = iVar3;
        work->field_60 = 1;

        if (GV_PauseLevel_800AB928 == 0)
        {
            if ((work->field_98_zoomSoundCounter & 3U) == 0) // When field is 0, 4, 8, 12...
            {
                GM_SeSet2_80032968(0, 0x3F, 0x24); // Scope zoom in/out sound.
            }

            work->field_98_zoomSoundCounter++;
        }
    }
    else
    {
        drawSideLines_800624F4(pSideLine_f2, iVar3);
        work->field_60 = 0;
        work->field_98_zoomSoundCounter = 0;
    }

    if (zoomLevel < 320)
    {
        zoomLevel = 320;
    }

    zoomLineLength = ((zoomLevel - 320) / 16) + 48;

    pZoomLevelLine_F3->x2 = zoomLineLength;
    pZoomLevelLine_F3->x1 = zoomLineLength;
    addLinePrimUnderCondition_80062320(pOt, pZoomLevelLine_F3);
    for (i = 0; i < 8; i++)
    {
        addLinePrimUnderCondition_80062320(pOt, pSideLine_f2);
        pSideLine_f2++;
    }

    GM_Camera_800B77E8.field_20_zoomLevel = zoomLevel;
}

void drawMovingRectangle_80062BDC(ScopeWork *work, u_char *pOt)
{
    LINE_F4 *pRect; // Top, right and bottom border.
    LINE_F2 *pLeftBorder;
    short    xy; // Left x, then top y.
    short    xRight;
    short    y0;

    pRect = work->field_7C_rect[GV_Clock_800AB920];
    pLeftBorder = (LINE_F2 *)(pRect + 1);

    xy = work->field_84_rectOffset[0] + 130;
    xRight = work->field_84_rectOffset[0] + 189;
    y0 = work->field_84_rectOffset[1];

    pLeftBorder->x1 = xy; // Bottom point.
    pLeftBorder->x0 = xy; // Top point.
    pRect->x3 = xy; // Bottom left corner.
    pRect->x0 = xy; // Top left corner.

    xy = y0 + 102; // x -> y swap.
    y0 = y0 + 137; // Top y -> bottom y.

    pRect->x2 = xRight; // Bottom right corner.
    pRect->x1 = xRight; // Top right corner.
    pLeftBorder->y0 = xy; // Top point.
    pRect->y1 = xy; // Top right corner.
    pRect->y0 = xy; // Top left corner.
    pLeftBorder->y1 = y0; // Bottom point.
    pRect->y3 = y0; // Bottom left corner.
    pRect->y2 = y0; // Bottom right corner.

    addLinePrimUnderCondition_80062320(pOt, pRect);
    addLinePrimUnderCondition_80062320(pOt, pLeftBorder);
}

void drawMovingVerticalLines_80062C7C(ScopeWork *work, u_char *pOt)
{
    short    lineHeight;
    int      primCount;
    int      i;
    LINE_F3 *pLine_F3;
    u_char  *otMin;
    u_char  *chnlOt;
    u_char  *curPrim;
    int      numOTEntries;

    pLine_F3 = work->field_88_movingLine_F3s[GV_Clock_800AB920];
    chnlOt = DG_Chanl(0)->mOrderingTables[1 - GV_Clock_800AB920];

    numOTEntries = DG_Chanl(0)->word_6BC374_8 - 4;
    for (i = 0; i < 16; i++)
    {
        otMin = chnlOt + ((i << numOTEntries) * 4);
        for (curPrim = chnlOt + (((i + 1) << numOTEntries) * 4), primCount = 0; (otMin < curPrim) || (curPrim < chnlOt);
             curPrim = nextPrim(curPrim))
        {
            if (getlen(curPrim) != 0)
            {
                primCount++;
            }

            if (primCount == 0x128)
            {
                break;
            }
        }

        primCount /= 2;
        lineHeight = 178 - primCount;
        pLine_F3->y1 = lineHeight;
        pLine_F3->y0 = lineHeight;
        addLinePrimUnderCondition_80062320(pOt, pLine_F3);
        pLine_F3++;
    }
}

void scope_draw_text_80062DA8(ScopeWork *work)
{
    if ( (GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000) == 0 )
    {
        menu_Text_XY_Flags_80038B34(20, 34, 0);
        menu_Color_80038B4C(127, 166, 97);
        menu_Text_80038C38("- ZOOM LEVEL - - %d -", 100 * (GM_Camera_800B77E8.field_20_zoomLevel / 320));
        menu_Color_80038B4C(101, 133, 77);
        menu_Text_XY_Flags_80038B34(32, 101, 1);
        menu_Text_80038C38("%d", -work->field_6C_turn_vec.vx);
        menu_Text_Init_80038B98();
    }
}

void scope_act_80062E8C(ScopeWork *work)
{
    int             model;
    OBJECT         *parent_obj;
    OBJECT_NO_ROTS *obj;
    unsigned char  *pOt;
    unsigned short  pad_status;

    if (!(work->field_9C_flags & 0x8000))
    {
        parent_obj = work->field_24_pParent;

        if (work->field_24_pParent->objs->n_models >= 7 && (work->field_24_pParent->objs->flag & DG_FLAG_INVISIBLE))
        {
            obj = &work->field_28_obj;
            model = GV_StrCode_80016CCC("goggles");

            GM_InitObjectNoRots_800349B0(obj, model, 0x6d, 0);

            if (work->field_28_obj.objs)
            {
                GM_ConfigObjectRoot_80034C5C((OBJECT *)obj, parent_obj, 6);
                GM_ConfigObjectLight_80034C44((OBJECT *)obj, parent_obj->light);
                EQ_InvisibleHead_80060D5C(parent_obj, &work->field_4C_saved_packs, &work->field_4E_saved_raise);
                work->field_9C_flags |= 0x8000;
            }
        }
    }


    if (work->field_9C_flags & 0x8000)
    {
        GM_CurrentMap_800AB9B0 = work->field_20_ctrl->field_2C_map->field_0_map_index_bit;
        DG_GroupObjs(work->field_28_obj.objs, DG_CurrentGroupID_800AB968);

        if ((GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000) != 0)
        {
            if (!(work->field_24_pParent->objs->flag & DG_FLAG_INVISIBLE))
            {
                DG_VisibleObjs(work->field_28_obj.objs);
            }

            GM_Camera_800B77E8.field_20_zoomLevel = 320;
            return;
        }

        DG_InvisibleObjs(work->field_28_obj.objs);
    }

    // Add some delay before showing the HUD of the scope (don't know why it is needed).
    if (work->field_5C_hudDelay > 0)
    {
        if (GV_PauseLevel_800AB928 == 0)
        {
            work->field_5C_hudDelay--;
        }

        return;
    }


    if (dword_8009F604 != SGT_SCOPE)
    {
        NewSight_80071CDC(SGT_SCOPE, SGT_SCOPE, &GM_CurrentItemId, 1, 0);
        GM_SeSet2_80032968(0, 63, 21);
    }


    if ((work->field_9C_flags & 3) != 3)
    {
        scope_act_helper_8006258C(work);
        return;
    }


    if ((GM_PlayerStatus_800ABA50 & PLAYER_USING_CONTROLLER_PORT_2) != 0)
    {
        work->field_54_pOldPad = &GV_PadData_800B05C0[3];
    }
    else
    {
        work->field_54_pOldPad = &GV_PadData_800B05C0[2];
    }

    pad_status = work->field_54_pOldPad->status;
    GM_CheckShukanReverse_8004FBF8(&pad_status);

    if ((GV_PauseLevel_800AB928 != 0) || (GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF) ||
        (GM_GameStatus_800AB3CC < 0))
    {
        pad_status = 0;
    }

    pOt = DG_ChanlOTag(1);

    managePadInput_800626D0(work, pad_status);
    scope_act_helper_80062998(work, pOt, pad_status);
    drawMovingRectangle_80062BDC(work, pOt);
    drawMovingVerticalLines_80062C7C(work, pOt);
    scope_draw_text_80062DA8(work);
}

void scope_kill_8006317C(ScopeWork *work)
{
    if ( work->field_74_sideLine_F2s[0] )
    {
        GV_DelayedFree_80016254(work->field_74_sideLine_F2s[0]);
    }

    if ( work->field_7C_rect[0] )
    {
        GV_DelayedFree_80016254(work->field_7C_rect[0]);
    }

    if ( work->field_88_movingLine_F3s[0] )
    {
        GV_DelayedFree_80016254(work->field_88_movingLine_F3s[0]);
    }

    if ( work->field_90_zoomLevelLine_F3s[0] )
    {
        GV_DelayedFree_80016254(work->field_90_zoomLevelLine_F3s[0]);
    }

    GM_Camera_800B77E8.field_20_zoomLevel = 320;

    if ( (work->field_9C_flags & 0x8000) != 0 )
    {
        EQ_VisibleHead_80060DF0(work->field_24_pParent, &work->field_4C_saved_packs, &work->field_4E_saved_raise);
        GM_FreeObject_80034BF8((OBJECT *)&work->field_28_obj);
    }

    scope_created_8009F2C4 = 0;
}

void initSideLines_80063238(LINE_F2 *pLines)
{
    int i;

    for (i = 0; i < 16; i++)
    {
        LSTORE(0x41412e, &pLines->r0);
        setLineF2(pLines);
        setSemiTrans(pLines, 1);
        pLines++;
    }
}

void initMovingRectangle_80063274(LINE_F4 *pLines)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        LSTORE(0x68b187, &pLines->r0); // Top, right and bottom borders.
        setLineF4(pLines);
        pLines++;

        LSTORE(0x68b187, &pLines->r0); // Left border.
        setLineF2(pLines);
        pLines++;
    }
}

void initMovingVerticalLines_800632D4(ScopeWork *work)
{
    LINE_F3 *pLine;
    int i, j;

    pLine = work->field_88_movingLine_F3s[0];
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 16; j++)
        {
            pLine->x0 = 68 + j * 12;
            pLine->x2 = 76 + j * 12;
            pLine->x1 = 76 + j * 12;

            LSTORE(0x287147, &pLine->r0);

            setLineF3(pLine);
            setSemiTrans(pLine, 1);

            pLine->y2 = 178;
            pLine++;
        }
    }
}

void initZoomLevelLine_80063368(LINE_F3 *pZoomLevelLine)
{
    int i;

    for (i = 0; i < 2; i++)
    {
        LSTORE(0x287147, &pZoomLevelLine->r0);
        setLineF3(pZoomLevelLine);
        pZoomLevelLine->x0 = pZoomLevelLine->x1 = pZoomLevelLine->x2 = 48;
        pZoomLevelLine->y0 = pZoomLevelLine->y1 = 46;
        pZoomLevelLine->y2 = 52;
        pZoomLevelLine++;
    }
}

int scope_loader_800633D4(ScopeWork *work, CONTROL *pCtrl, OBJECT *pParent)
{
    MAP *pMap;

    work->field_74_sideLine_F2s[0] = GV_Malloc_8001620C(sizeof(LINE_F2) * 16);
    if (!work->field_74_sideLine_F2s[0])
    {
        return -1;
    }

    work->field_74_sideLine_F2s[1] = work->field_74_sideLine_F2s[0] + 8;

    work->field_7C_rect[0] = GV_Malloc_8001620C(sizeof(LINE_F4) * 4);
    if (!work->field_7C_rect[0])
    {
        return -1;
    }

    work->field_7C_rect[1] = work->field_7C_rect[0] + 2;

    work->field_88_movingLine_F3s[0] = GV_Malloc_8001620C(sizeof(LINE_F3) * 32);

    if (!work->field_88_movingLine_F3s[0])
    {
        return -1;
    }

    work->field_88_movingLine_F3s[1] = work->field_88_movingLine_F3s[0] + 16;

    work->field_90_zoomLevelLine_F3s[0] = GV_Malloc_8001620C(sizeof(LINE_F3) * 2);
    if (!work->field_90_zoomLevelLine_F3s[0])
    {
        return -1;
    }

    work->field_90_zoomLevelLine_F3s[1] = work->field_90_zoomLevelLine_F3s[0] + 1;

    initSideLines_80063238(work->field_74_sideLine_F2s[0]);
    initMovingRectangle_80063274(work->field_7C_rect[0]);
    initMovingVerticalLines_800632D4(work);
    initZoomLevelLine_80063368(work->field_90_zoomLevelLine_F3s[0]);

    work->field_54_pOldPad = &GV_PadData_800B05C0[2];
    work->field_5C_hudDelay = 16;
    work->field_58 = 0;
    work->field_5E = 2;
    work->field_60 = 0;
    work->field_62 = 0;

    work->field_6C_turn_vec.vy = work->field_64_vec.vy = pCtrl->field_4C_turn.vy;
    work->field_6C_turn_vec.vx = work->field_64_vec.vx = pCtrl->field_4C_turn.vx;

    work->field_64_vec.vz = 0;
    work->field_6C_turn_vec.vz = 0;

    work->field_84_rectOffset[1] = 0;
    work->field_84_rectOffset[0] = 0;

    pMap = pCtrl->field_2C_map;

    work->field_9C_flags = 0;
    work->field_20_ctrl = pCtrl;
    work->field_24_pParent = pParent;
    work->field_50_pMap = pMap;
    return 0;
}

GV_ACT * NewScope_80063508(CONTROL *pCtrl, OBJECT *pParent, int unused)
{
    ScopeWork *work; // $s0

    if ( scope_created_8009F2C4 )
    {
        return 0;
    }

    work = (ScopeWork *)GV_NewActor_800150E4(7, sizeof(ScopeWork));
    if ( work )
    {
        GV_SetNamedActor_8001514C(&work->field_0_scope, (TActorFunction)scope_act_80062E8C, (TActorFunction)scope_kill_8006317C, "scope.c");
        if ( scope_loader_800633D4(work, pCtrl, pParent) < 0 )
        {
            GV_DestroyActor_800151C8(&work->field_0_scope);
            return 0;
        }
        scope_created_8009F2C4 = 1;
    }

    return &work->field_0_scope;
}
