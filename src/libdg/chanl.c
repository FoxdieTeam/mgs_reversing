#include "libdg.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libapi.h>
#include "common.h"

/*** data ***/

TChanl_Fn off_8009D35C[] = {
    DG_ScreenChanl,     // 0: DG_CHANL_SCREEN
    DG_BoundChanl,      // 1: DG_CHANL_BOUND
    DG_TransChanl,      // 2: DG_CHANL_TRANS
    DG_ShadeChanl,      // 3: DG_CHANL_SHADE
    DG_PrimChanl,       // 4: DG_CHANL_PRIM
    DG_DivideChanl,     // 5: DG_CHANL_DIVIDE
    DG_SortChanl        // 6: DG_CHANL_SORT
};

/*** $gp ***/
int DG_ObjectQueueVoided = 0;

// standard
int            SECTION(".sbss") dword_800AB974;
int            SECTION(".sbss") dword_800AB978;
unsigned char  SECTION(".sbss") DG_r_800AB97C;
unsigned char  SECTION(".sbss") DG_g_800AB97D;
unsigned char  SECTION(".sbss") DG_b_800AB97E;
short          SECTION(".sbss") N_ChanlPerfMax_800AB980;
short          SECTION(".sbss") word_800AB982;
unsigned short SECTION(".sbss") gCurrentRootCnt_800AB984;

/*** sbss ***/
extern int       DG_HikituriFlag;
extern int       DG_UnDrawFrameCount;

/*** bss ***/
extern DG_CHANL       DG_Chanls_800B1800[3];
extern int            dword_800B0630[68];
extern int            dword_800B0740[516];
extern int            dword_800B0F50[4];
extern DG_OBJS       *dword_800B0F60[8];
extern DG_OBJS       *dword_800B0F80[256];
extern DR_ENV         stru_800B1380[2];
extern unsigned int  *ptr_800B1400[256];
extern unsigned short gOldRootCnt_800B1DC8[32];

#define pow2(n) (1 << (n))

// gets value of root counter 1 which determines time taken to finished drawing
// sets it to word_800AB982
STATIC void DG_DrawSyncCallback( void )
{
    word_800AB982 = GetRCnt(RCntCNT1);
}

// guessed function name
STATIC void DG_SetChanlOrderingTable( DG_CHANL *chanl, unsigned char *pOtBuffer, unsigned int otLen,
                                      DG_OBJS **pQueue, short queueSize, short param_6, short param_7 )
{
    // TODO: Aligning the end ptr? Also not sure if type is correct
    unsigned char *pEnd = pOtBuffer + ((((1 << (otLen))) + 1) * 4);

    chanl->mOrderingTables[0] = pOtBuffer;
    chanl->mOrderingTables[1] = pEnd;
    chanl->mTotalObjectCount = 0;
    chanl->mQueue = pQueue;
    chanl->word_6BC374_8 = otLen;
    chanl->word_6BC37A_0_1EC_size = 0;
    chanl->mFreePrimCount = queueSize;
    chanl->mTotalQueueSize = queueSize;
    chanl->word_6BC376_16 = param_6;
    chanl->word_6BC378_1 = param_7;
}

// guessed function name
STATIC void DG_SetChanlDrawEnv( DG_CHANL *chanl, DRAWENV *pDrawEnv, int backround )
{
    int     x_off;
    DRAWENV drawEnv;

    drawEnv = *pDrawEnv;
    x_off = 0;

    if (chanl->word_6BC378_1)
    {
        x_off = dword_800AB978;
    }
    chanl->field_64_rect.x = drawEnv.clip.x - drawEnv.ofs[0];
    chanl->field_64_rect.y = drawEnv.clip.y - drawEnv.ofs[1];
    chanl->field_64_rect.w = drawEnv.clip.w;
    chanl->field_64_rect.h = drawEnv.clip.h;
    SetDrawEnv(chanl->field_16C_dr_env, &drawEnv);
    drawEnv.clip.x += x_off;
    drawEnv.ofs[0] += x_off;
    SetDrawEnv(&chanl->field_16C_dr_env[1], &drawEnv);

    if (backround)
    {
        drawEnv.isbg = 0;
        SetDrawEnv(&stru_800B1380[1], &drawEnv);
        drawEnv.clip.x -= x_off;
        drawEnv.ofs[0] -= x_off;
        SetDrawEnv(&stru_800B1380[0], &drawEnv);
    }
}

// guessed function name
STATIC void DG_CopyChanlDrawEnv( DG_CHANL *chanl, int idx )
{
    chanl->field_5C_clip_rect = chanl->field_64_rect;
    chanl->field_6C_dr_env[idx] = chanl->field_16C_dr_env[idx];
}

// guessed function name
void DG_InitChanlSystem( int width )
{
    DRAWENV drawEnv;
    DG_CHANL *chanl;

    DrawSyncCallback(DG_DrawSyncCallback);
    dword_800AB978 = width;

    chanl = DG_Chanls_800B1800;
    DG_SetChanlOrderingTable(chanl, (unsigned char *)dword_800B0630, 5, (DG_OBJS **)dword_800B0F60, 8, -1, 1);
    DG_InitDrawEnv(&drawEnv, 0, 0, 320, 224);
    drawEnv.isbg = 1;
    DG_SetChanlDrawEnv(chanl, &drawEnv, 1);
    DG_CopyChanlDrawEnv(chanl, 0);
    DG_CopyChanlDrawEnv(chanl, 1);

    chanl++;
    DG_SetChanlOrderingTable(chanl, (unsigned char *)dword_800B0740, 8, (DG_OBJS **)dword_800B0F80, 256, 16, 1);
    DG_InitDrawEnv(&drawEnv, 0, 0, 320, 224);
    drawEnv.ofs[0] = 160;
    drawEnv.ofs[1] = 112;
    DG_SetChanlDrawEnv(chanl, &drawEnv, 0);
    DG_CopyChanlDrawEnv(chanl, 0);
    DG_CopyChanlDrawEnv(chanl, 1);

    chanl->field_EC_dr_env[0] = stru_800B1380[0];
    chanl->field_EC_dr_env[1] = stru_800B1380[1];

    chanl++;
    DG_SetChanlOrderingTable(chanl, (unsigned char *)dword_800B0F50, 0, 0, 0, 8, 1);
    DG_InitDrawEnv(&drawEnv, 0, 0, 320, 224);
    DG_SetChanlDrawEnv(chanl, &drawEnv, 0);
    DG_CopyChanlDrawEnv(chanl, 0);
    DG_CopyChanlDrawEnv(chanl, 1);

    chanl->field_EC_dr_env[0] = stru_800B1380[0];
    chanl->field_EC_dr_env[1] = stru_800B1380[1];
}

void DG_DrawOTag( int activeBuffer )
{
    gOldRootCnt_800B1DC8[0] = gCurrentRootCnt_800AB984;
    gCurrentRootCnt_800AB984 = GetRCnt(RCntCNT1);
    DrawOTag((u_long *)&DG_Chanls_800B1800[0].field_6C_dr_env[activeBuffer]);
}

// not correct, revisit;
void DG_ClearChanlSystem( int which )
{
    int            i, n_ot;
    unsigned int   s4;
    unsigned long *ot;
    unsigned long  v0, v1;
    DR_ENV        *draw_env;
    DR_ENV        *draw_env2;
    DG_CHANL      *chanl;

    int v2;

    unsigned long *ots;
    chanl = DG_Chanls_800B1800;

    for (i = 3; i > 0; --i)
    {
        // loc_80017EF8
        ots = (unsigned long *)chanl->mOrderingTables[which];
        ot = ots;
        n_ot = pow2(chanl->word_6BC374_8);
        s4 = (unsigned int)&ot[n_ot];

        ClearOTagR(ot, n_ot + 1);

        if (chanl->word_6BC37A_0_1EC_size > 0)
        {
            // loc_80017F30
            DG_CopyChanlDrawEnv(chanl, which);
            --chanl->word_6BC37A_0_1EC_size;
        }

        // loc_80017F50
        draw_env = &chanl->field_6C_dr_env[which];
        draw_env2 = &chanl->field_EC_dr_env[which];

        // addPrims(s4, draw_env2, draw_env); //should do the below
        v2 = s4 & 0x00FFFFFF;
        draw_env->tag = (draw_env->tag & 0xFF000000) | v2;

        v1 = ot[0];
        v1 = v1 & 0xFF000000;
        v0 = (unsigned int)draw_env2 & 0x00FFFFFF;

        ot[0] = v1 | v0;

        if (chanl->word_6BC376_16 >= 0)
        {
            // loc_80017F94
            ot = (unsigned long *)DG_Chanls_800B1800[0].mOrderingTables[which];
            ot = &ot[chanl->word_6BC376_16];

            // addPrims(ot, draw_env, draw_env2); //should do the below
            draw_env2->tag = (draw_env2->tag & 0xFF000000) | (ot[0] & 0x00FFFFFF);

            ot[0] = (ot[0] & 0xFF000000) | ((unsigned int)draw_env & 0x00FFFFFF);
        }
        else
        {
            // loc_80017FD8
            termPrim(draw_env2); // should do below

            // bottom 2 lines provide fake match
            draw_env2->tag |= 0x00FFFFFF; // shouldn't be here
            v1 = ot[0];                   // shouldn't be here
        }
        chanl++;
    }
}

void DG_RenderPipeline( int idx )
{
    unsigned short *pPerfArrayIter;
    TChanl_Fn      *pRenderFns;
    int             start_idx;
    int             i;

    pPerfArrayIter = &gOldRootCnt_800B1DC8[1];
    if (DG_ObjectQueueVoided)
    {
        // Store the counter and set as 2 valid items
        *pPerfArrayIter = GetRCnt(0xF2000001);
        N_ChanlPerfMax_800AB980 = 2;
    }
    else
    {
        GV_ZeroMemory(ptr_800B1400, sizeof(ptr_800B1400));
        pRenderFns = off_8009D35C;

        if (!DG_HikituriFlag)
        {
            start_idx = 7;
        }
        else
        {
            start_idx = 1;
        }

        for (i = start_idx; i > 0; --i)
        {
            *pPerfArrayIter++ = GetRCnt(RCntCNT1);
            // Call the render func, saving the time of the previous pass
            (*pRenderFns)(&DG_Chanls_800B1800[1], idx);
            pRenderFns++;
        }
        *pPerfArrayIter++ = GetRCnt(RCntCNT1);
        N_ChanlPerfMax_800AB980 = (pPerfArrayIter) - &gOldRootCnt_800B1DC8[0];
    }
}

void DG_SetRenderChanlDrawEnv( int idx, DRAWENV *pDrawEnv )
{
    DG_CHANL *chanl = &DG_Chanls_800B1800[idx + 1];
    DG_SetChanlDrawEnv(chanl, pDrawEnv, 0);
    chanl->word_6BC37A_0_1EC_size = 2;
}

int DG_QueueObjs( DG_OBJS *objs )
{
    DG_CHANL *chanl;
    int       n_chanl, n_objs;

    n_chanl = objs->chanl + 1;
    chanl = &DG_Chanls_800B1800[n_chanl];

    n_objs = chanl->mTotalObjectCount;

    if (n_objs >= chanl->mFreePrimCount)
    {
        return -1;
    }
    else
    {
        chanl->mQueue[n_objs++] = objs;
        chanl->mTotalObjectCount = n_objs;
        return 0;
    }
}

void DG_DequeueObjs( DG_OBJS *objs )
{
    DG_CHANL *chanl;
    int       n_chanl, n_objs, i;
    DG_OBJS **chanl_objs;

    n_chanl = objs->chanl + 1;
    chanl = &DG_Chanls_800B1800[n_chanl];

    n_objs = chanl->mTotalObjectCount;
    chanl_objs = chanl->mQueue;

    for (i = n_objs; i > 0; --i)
    {
        if (*chanl_objs == objs)
            goto END;
        chanl_objs++;
    }
    return;

END:
    --i;
    for (; i > 0; --i)
    {
        chanl_objs[0] = chanl_objs[1];
        chanl_objs++;
    }

    n_objs--;
    chanl->mTotalObjectCount = n_objs;
}

int DG_QueuePrim( DG_PRIM *prim )
{
    int       t = prim->chanl + 1;
    DG_CHANL *chanl = &DG_Chanls_800B1800[t];
    int       idx = chanl->mFreePrimCount;

    if (idx <= chanl->mTotalObjectCount)
    {
        return -1;
    }
    idx = idx - 1;
    chanl->mQueue[idx] = (DG_OBJS *)prim; // 58
    chanl->mFreePrimCount = idx;
    return 0;
}

void DG_DequeuePrim( DG_PRIM *prim )
{
    int i;
    int group;
    int queue_size;
    int n_free_prims;

    DG_CHANL *chanl;
    DG_OBJS **chanl_objs;

    group = prim->chanl + 1;
    chanl = &DG_Chanls_800B1800[group];

    n_free_prims = chanl->mFreePrimCount;
    queue_size = chanl->mTotalQueueSize;

    chanl_objs = &chanl->mQueue[queue_size];
    i = queue_size - n_free_prims;

    for (; i > 0; --i)
    {
        --chanl_objs;
        if (*chanl_objs == (DG_OBJS *)prim)
            goto END;
    }
    return;

END:
    --i;
    for (; i > 0; --i)
    {
        chanl_objs[0] = chanl_objs[-1];
        chanl_objs--;
    }

    n_free_prims++;
    chanl->mFreePrimCount = n_free_prims;
}

void DG_InitDrawEnv( DRAWENV *pDrawEnv, int clipX1, int clipY1, int clipX2, int clipY2 )
{
    setRECT(&pDrawEnv->clip, clipX1, clipY1, clipX2, clipY2);
    pDrawEnv->ofs[0] = clipX1;
    pDrawEnv->ofs[1] = clipY1;
    pDrawEnv->dtd = 1;
    pDrawEnv->dfe = 0;
    setRECT(&pDrawEnv->tw, 0, 0, 0, 0);
    setRGB0(pDrawEnv, 0, 0, 0);
    pDrawEnv->tpage = 0;
    pDrawEnv->isbg = 0;
}

void DG_FreeObjectQueue( void )
{
    DG_CHANL *chanl;
    DG_OBJS **queue;
    DG_OBJS  *objs;
    int       i;

    chanl = &DG_Chanls_800B1800[1];
    queue = (DG_OBJS **)chanl->mQueue;

    DG_ObjectQueueVoided = 1;

    for (i = chanl->mTotalObjectCount; i > 0; i--)
    {
        objs = *queue++;
        DG_FreeObjsPacket(objs, 0);
        DG_FreeObjsPacket(objs, 1);
    }
}

void DG_ResetObjectQueue( void )
{
    DG_ObjectQueueVoided = 0;
    DG_UnDrawFrameCount = 1;
}

void DG_SetBackgroundRGB( int r, int g, int b )
{
    DRAWENV drawEnv;
    DG_CHANL *chanl = &DG_Chanls_800B1800[0];

    DG_InitDrawEnv(&drawEnv, 0, 0, 320, 224);
    drawEnv.isbg = 1;
    setRGB0(&drawEnv, r, g, b);
    DG_SetChanlDrawEnv(chanl, &drawEnv, 1);
    chanl->word_6BC37A_0_1EC_size = 2;
}

void DG_SetRGB( int r, int g, int b )
{
    DG_r_800AB97C = r;
    DG_b_800AB97E = b;
    DG_g_800AB97D = g;
    DG_SetBackgroundRGB(r, g, b);
}

void DG_BackGroundBlack( void )
{
    DG_SetBackgroundRGB(0, 0, 0);
}

void DG_BackGroundNormal( void )
{
    DG_SetBackgroundRGB(DG_r_800AB97C, DG_g_800AB97D, DG_b_800AB97E);
}

void DG_InitBackgroundTile( TILE *tile )
{
    tile->r0 = DG_r_800AB97C;
    tile->g0 = DG_g_800AB97D;
    tile->b0 = DG_b_800AB97E;
}

TChanl_Fn DG_SetChanlSystemUnits( int idx, TChanl_Fn newFunc )
{
    TChanl_Fn oldFunc = off_8009D35C[idx];
    off_8009D35C[idx] = newFunc;
    return oldFunc;
}
