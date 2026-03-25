#include "libdg.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libapi.h>
#include "common.h"

/*** data ***/

STATIC DG_CHANLFUNC DG_ChanlUnits[] = {
    DG_ScreenChanl,     // 0: DG_SCREEN_CHANL
    DG_BoundChanl,      // 1: DG_BOUND_CHANL
    DG_TransChanl,      // 2: DG_TRANS_CHANL
    DG_ShadeChanl,      // 3: DG_SHADE_CHANL
    DG_PrimChanl,       // 4: DG_PRIM_CHANL
    DG_DivideChanl,     // 5: DG_DIVIDE_CHANEL
    DG_SortChanl        // 6: DG_SORT_CHANL
};

/*** $gp ***/
STATIC int DG_ObjectQueueVoided = FALSE;

// standard
STATIC int SECTION(".sbss") dword_800AB974;
STATIC int SECTION(".sbss") dword_800AB978;

STATIC CVECTOR SECTION(".sbss") DG_BackGroundColor;

short          SECTION(".sbss") N_ChanlPerfMax;
short          SECTION(".sbss") word_800AB982;
unsigned short SECTION(".sbss") gCurrentRootCnt_800AB984;

/*** bss ***/
extern DG_CHANL DG_Chanls[3];

extern u_long ot_background[68];
extern u_long ot_primitive[516];
extern u_long ot_overlay[4];

extern void *obj_queue_background[8];
extern void *obj_queue_primitive[256];

extern DR_ENV bg_drawenv[2];

extern u_long *ptr_800B1400[256];
extern u_short gOldRootCnt_800B1DC8[32];

// gets value of root counter 1 which determines time taken to finished drawing
// sets it to word_800AB982
STATIC void DG_DrawSyncCallback( void )
{
    word_800AB982 = GetRCnt(RCntCNT1);
}

// guessed function name
STATIC void DG_SetChanlOrderingTable( DG_CHANL *chanl, u_long *ot, int ot_size, void **queue, short queue_size, short link, short dblbuf )
{
    int size;

    size = (1 << ot_size) + 1;

    chanl->ot[0] = ot;
    chanl->ot[1] = &ot[size];
    chanl->objs_index = 0;
    chanl->queue = (DG_OBJS **)queue;
    chanl->ot_size = ot_size;
    chanl->dirty = 0;
    chanl->prim_index = queue_size;
    chanl->queue_size = queue_size;
    chanl->link = link;
    chanl->dblbuf = dblbuf;
}

// guessed function name
STATIC void DG_SetChanlDrawEnv( DG_CHANL *chanl, DRAWENV *env, int backround )
{
    DRAWENV dr_env;
    int     width;

    dr_env = *env;
    width = chanl->dblbuf ? dword_800AB978 : 0;

    chanl->new_clip_rect.x = dr_env.clip.x - dr_env.ofs[0];
    chanl->new_clip_rect.y = dr_env.clip.y - dr_env.ofs[1];
    chanl->new_clip_rect.w = dr_env.clip.w;
    chanl->new_clip_rect.h = dr_env.clip.h;
    SetDrawEnv(chanl->new_env, &dr_env);

    dr_env.clip.x += width;
    dr_env.ofs[0] += width;
    SetDrawEnv(&chanl->new_env[1], &dr_env);

    if (backround)
    {
        dr_env.isbg = 0;
        SetDrawEnv(&bg_drawenv[1], &dr_env);

        dr_env.clip.x -= width;
        dr_env.ofs[0] -= width;
        SetDrawEnv(&bg_drawenv[0], &dr_env);
    }
}

// guessed function name
STATIC void DG_CopyChanlDrawEnv( DG_CHANL *chanl, int idx )
{
    chanl->clip_rect = chanl->new_clip_rect;
    chanl->env1[idx] = chanl->new_env[idx];
}

// guessed function name
void DG_InitChanlSystem( int width )
{
    DRAWENV drawEnv;
    DG_CHANL *chanl;

    DrawSyncCallback(DG_DrawSyncCallback);
    dword_800AB978 = width;

    /* channel 0 */
    chanl = DG_Chanls;
    DG_SetChanlOrderingTable(chanl, ot_background, 5, obj_queue_background, 8, -1, 1);
    DG_InitDrawEnv(&drawEnv, 0, 0, FRAME_WIDTH, FRAME_HEIGHT);
    drawEnv.isbg = 1;
    DG_SetChanlDrawEnv(chanl, &drawEnv, 1);
    DG_CopyChanlDrawEnv(chanl, 0);
    DG_CopyChanlDrawEnv(chanl, 1);

    /* channel 1 */
    chanl++;
    DG_SetChanlOrderingTable(chanl, ot_primitive, 8, obj_queue_primitive, 256, 16, 1);
    DG_InitDrawEnv(&drawEnv, 0, 0, FRAME_WIDTH, FRAME_HEIGHT);
    drawEnv.ofs[0] = 160;
    drawEnv.ofs[1] = 112;
    DG_SetChanlDrawEnv(chanl, &drawEnv, 0);
    DG_CopyChanlDrawEnv(chanl, 0);
    DG_CopyChanlDrawEnv(chanl, 1);

    chanl->env2[0] = bg_drawenv[0];
    chanl->env2[1] = bg_drawenv[1];

    /* channel 2 */
    chanl++;
    DG_SetChanlOrderingTable(chanl, ot_overlay, 0, NULL, 0, 8, 1);
    DG_InitDrawEnv(&drawEnv, 0, 0, FRAME_WIDTH, FRAME_HEIGHT);
    DG_SetChanlDrawEnv(chanl, &drawEnv, 0);
    DG_CopyChanlDrawEnv(chanl, 0);
    DG_CopyChanlDrawEnv(chanl, 1);

    chanl->env2[0] = bg_drawenv[0];
    chanl->env2[1] = bg_drawenv[1];
}

void DG_DrawOTag( int which )
{
    gOldRootCnt_800B1DC8[0] = gCurrentRootCnt_800AB984;
    gCurrentRootCnt_800AB984 = GetRCnt(RCntCNT1);

    /* channels 1 and 2 are linked into channel 0 */
    DrawOTag(&DG_Chanls[0].env1[which].tag);
}

void DG_ClearChanlSystem( int which )
{
    DG_CHANL *chanl;
    int       i;
    int       size;
    u_long   *ot;
    u_long   *ot_end;
    DR_ENV   *env1;
    DR_ENV   *env2;
    u_long   *chain;

    chanl = DG_Chanls;
    for (i = 3 ; i > 0; i--)
    {
        size = (1 << chanl->ot_size) + 1;

        ot = chanl->ot[which];
        ot_end = &ot[size - 1];

        /* the ot is in reverse order */
        ClearOTagR(ot, size);

        if (chanl->dirty > 0)
        {
            DG_CopyChanlDrawEnv(chanl, which);
            chanl->dirty--;
        }

        env1 = &chanl->env1[which];
        env2 = &chanl->env2[which];

        /* execute the channel in the order env1 -> ot -> env2 */
        catPrim(env1, ot_end);
        catPrim(ot, env2);

        if (chanl->link >= 0)
        {
            /* link this channel into the background channel */
            chain = DG_Chanls[0].ot[which];
            chain += chanl->link;
            addPrims(chain, env1, env2);
        }
        else
        {
            termPrim(env2);
        }

        chanl++;
    }
}

void DG_RenderPipeline( int idx )
{
    unsigned short *pPerfArrayIter;
    DG_CHANLFUNC   *chanlfunc;
    int             start_idx;
    int             i;

    pPerfArrayIter = &gOldRootCnt_800B1DC8[1];
    if (DG_ObjectQueueVoided)
    {
        // Store the counter and set as 2 valid items
        *pPerfArrayIter = GetRCnt(0xF2000001);
        N_ChanlPerfMax = 2;
    }
    else
    {
        GV_ZeroMemory(ptr_800B1400, sizeof(ptr_800B1400));
        chanlfunc = DG_ChanlUnits;

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
            (*chanlfunc)(&DG_Chanls[1], idx);
            chanlfunc++;
        }
        *pPerfArrayIter++ = GetRCnt(RCntCNT1);
        N_ChanlPerfMax = (pPerfArrayIter) - &gOldRootCnt_800B1DC8[0];
    }
}

void DG_SetRenderChanlDrawEnv( int idx, DRAWENV *pDrawEnv )
{
    DG_CHANL *chanl = &DG_Chanls[idx + 1];
    DG_SetChanlDrawEnv(chanl, pDrawEnv, 0);
    chanl->dirty = 2;
}

int DG_QueueObjs( DG_OBJS *objs )
{
    DG_CHANL *chanl;
    int       n_chanl, n_objs;

    n_chanl = objs->chanl + 1;
    chanl = &DG_Chanls[n_chanl];

    n_objs = chanl->objs_index;

    if (n_objs >= chanl->prim_index)
    {
        return -1;
    }
    else
    {
        chanl->queue[n_objs++] = objs;
        chanl->objs_index = n_objs;
        return 0;
    }
}

void DG_DequeueObjs( DG_OBJS *objs )
{
    DG_CHANL *chanl;
    int       n_chanl, n_objs, i;
    DG_OBJS **chanl_objs;

    n_chanl = objs->chanl + 1;
    chanl = &DG_Chanls[n_chanl];

    n_objs = chanl->objs_index;
    chanl_objs = chanl->queue;

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
    chanl->objs_index = n_objs;
}

int DG_QueuePrim( DG_PRIM *prim )
{
    int       t = prim->chanl + 1;
    DG_CHANL *chanl = &DG_Chanls[t];
    int       idx = chanl->prim_index;

    if (idx <= chanl->objs_index)
    {
        return -1;
    }
    idx = idx - 1;
    chanl->queue[idx] = (DG_OBJS *)prim; // 58
    chanl->prim_index = idx;
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
    chanl = &DG_Chanls[group];

    n_free_prims = chanl->prim_index;
    queue_size = chanl->queue_size;

    chanl_objs = &chanl->queue[queue_size];
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
    chanl->prim_index = n_free_prims;
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

    chanl = &DG_Chanls[1];
    queue = (DG_OBJS **)chanl->queue;

    DG_ObjectQueueVoided = TRUE;

    for (i = chanl->objs_index; i > 0; i--)
    {
        objs = *queue++;
        DG_FreeObjsPacket(objs, 0);
        DG_FreeObjsPacket(objs, 1);
    }
}

void DG_RestartMainChanlSystem( void )
{
    DG_ObjectQueueVoided = FALSE;
    DG_UnDrawFrameCount = 1;
}

void DG_SetBackgroundRGB( int r, int g, int b )
{
    DRAWENV drawEnv;
    DG_CHANL *chanl = &DG_Chanls[0];

    DG_InitDrawEnv(&drawEnv, 0, 0, FRAME_WIDTH, FRAME_HEIGHT);
    drawEnv.isbg = 1;
    setRGB0(&drawEnv, r, g, b);
    DG_SetChanlDrawEnv(chanl, &drawEnv, 1);
    chanl->dirty = 2;
}

void DG_SetRGB( int r, int g, int b )
{
    DG_BackGroundColor.r = r;
    DG_BackGroundColor.b = b;
    DG_BackGroundColor.g = g;

    DG_SetBackgroundRGB(r, g, b);
}

void DG_BackGroundBlack( void )
{
    DG_SetBackgroundRGB(0, 0, 0);
}

void DG_BackGroundNormal( void )
{
    DG_SetBackgroundRGB(
        DG_BackGroundColor.r,
        DG_BackGroundColor.g,
        DG_BackGroundColor.b);
}

void DG_SetBackGroundTile( TILE *tile )
{
    tile->r0 = DG_BackGroundColor.r;
    tile->g0 = DG_BackGroundColor.g;
    tile->b0 = DG_BackGroundColor.b;
}

DG_CHANLFUNC DG_SetChanlSystemUnits( int idx, DG_CHANLFUNC newfunc )
{
    DG_CHANLFUNC oldfunc = DG_ChanlUnits[idx];
    DG_ChanlUnits[idx] = newfunc;
    return oldfunc;
}
