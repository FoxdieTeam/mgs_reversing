#include "linker.h"
#include "libdg.h"
#include "dgd.h"
#include "psyq.h"


/**data************************/
/******************************/

/**gp***********************************************************************************************/
//forced
extern int              gObjectQueueVoided_800AB388;
int SECTION(".sdata")   gObjectQueueVoided_800AB388;
//standard
int             SECTION(".sbss") dword_800AB974;
int             SECTION(".sbss") dword_800AB978;
unsigned char   SECTION(".sbss") DG_r_800AB97C;
unsigned char   SECTION(".sbss") DG_b_800AB97D;
unsigned char   SECTION(".sbss") DG_g_800AB97E;
short           SECTION(".sbss") N_ChanlPerfMax_800AB980;
short           SECTION(".sbss") word_800AB982;
unsigned short  SECTION(".sbss") gCurrentRootCnt_800AB984;
/***************************************************************************************************/

/**sbss*******************************************/
extern TChanl_Fn    off_8009D35C[];
extern int          DG_HikituriFlag_8009D460;
extern int          DG_UnDrawFrameCount_800AB380;
/*************************************************/

/**bss************************************************************************/
DG_CHNL         SECTION(".DG_Chanls_800B1800")   DG_Chanls_800B1800[3];
int             SECTION(".dword_800B0630")       dword_800B0630[68];
int             SECTION(".dword_800B0630")       dword_800B0740[516];
int             SECTION(".dword_800B0630")       dword_800B0F50[4];
DG_OBJS*        SECTION(".dword_800B0630")       dword_800B0F60[8];
DG_OBJS*        SECTION(".dword_800B0630")       dword_800B0F80[256];
DR_ENV          SECTION(".dword_800B0630")       stru_800B1380[2];
unsigned char   SECTION(".byte_800B1400")        byte_800B1400[1024];
unsigned short  SECTION(".gOldRootCnt_800B1DC8") gOldRootCnt_800B1DC8[32];
/****************************************************************************/

#define pow2(n) \
        1 << n

//gets value of root counter 1 which determines time taken to finished drawing
//sets it to word_800AB982
void DG_DrawSyncCallback_80017984(void)
{
    word_800AB982 = GetRCnt_800996E8(0xf2000001);
}

//guessed function name
void DG_SetChanlOrderingTable_800179A8(DG_CHNL *pStruct, unsigned char *pOtBuffer, unsigned int otLen, DG_OBJS **pQueue, short queueSize, short param_6, short param_7)
{
    unsigned char* pEnd = pOtBuffer + ((((1 << (otLen))) + 1) * 4); // TODO: Aligning the end ptr? Also not sure if type is correct
    pStruct->mOrderingTables[0] = pOtBuffer;
    pStruct->mOrderingTables[1] = pEnd;
    pStruct->mTotalObjectCount = 0;
    pStruct->mQueue = pQueue;
    pStruct->word_6BC374_8 = otLen;
    pStruct->word_6BC37A_0_1EC_size = 0;
    pStruct->mFreePrimCount = queueSize;
    pStruct->mTotalQueueSize = queueSize;
    pStruct->word_6BC376_16 = param_6;
    pStruct->word_6BC378_1 = param_7;
}

//guessed function name
void DG_SetChanlDrawEnv_800179F4(DG_CHNL *pOt, DRAWENV *pDrawEnv, int a3)
{
    int x_off;
    DRAWENV drawEnv;

    drawEnv = *pDrawEnv;
    x_off = 0;
    
    if ( pOt->word_6BC378_1 )
    {
        x_off = dword_800AB978;
    }
    pOt->field_64_rect.x = drawEnv.clip.x - drawEnv.ofs[0];
    pOt->field_64_rect.y = drawEnv.clip.y - drawEnv.ofs[1];
    pOt->field_64_rect.w = drawEnv.clip.w;
    pOt->field_64_rect.h = drawEnv.clip.h;
    SetDrawEnv_800906B0(pOt->field_16C_dr_env, &drawEnv);
    drawEnv.clip.x += x_off;
    drawEnv.ofs[0] += x_off;
    SetDrawEnv_800906B0(&pOt->field_16C_dr_env[1], &drawEnv);
    if ( a3 )
    {
        drawEnv.isbg = 0;
        SetDrawEnv_800906B0(&stru_800B1380[1], &drawEnv);
        drawEnv.clip.x -= x_off;
        drawEnv.ofs[0] -= x_off;
        SetDrawEnv_800906B0(&stru_800B1380[0], &drawEnv);
    }
}

//guessed function name
void DG_CopyChanlDrawEnv_80017B30(DG_CHNL *pChanl, int idx)
{
    pChanl->field_5C_rect = pChanl->field_64_rect;
    pChanl->field_6C_dr_env[idx] = pChanl->field_16C_dr_env[idx];
}

//guessed function name
void DG_InitChanlSystem_80017B98(int width)
{
    DRAWENV drawEnv;
    DG_CHNL* ptr;

    DrawSyncCallback_8008F76C(DG_DrawSyncCallback_80017984);
    dword_800AB978 = width;
    ptr = DG_Chanls_800B1800;
    DG_SetChanlOrderingTable_800179A8(ptr, (unsigned char*)dword_800B0630, 5, (DG_OBJS **)dword_800B0F60, 8, -1, 1);
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.isbg = 1;
    DG_SetChanlDrawEnv_800179F4(ptr, &drawEnv, 1);
    DG_CopyChanlDrawEnv_80017B30(ptr, 0);
    DG_CopyChanlDrawEnv_80017B30(ptr, 1);

    ptr++;
    DG_SetChanlOrderingTable_800179A8(ptr, (unsigned char*)dword_800B0740, 8, (DG_OBJS **)dword_800B0F80, 256, 16, 1);
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.ofs[0] = 160;
    drawEnv.ofs[1] = 112;
    DG_SetChanlDrawEnv_800179F4(ptr, &drawEnv, 0);
    DG_CopyChanlDrawEnv_80017B30(ptr, 0);
    DG_CopyChanlDrawEnv_80017B30(ptr, 1);

    ptr->field_EC_dr_env[0] = stru_800B1380[0];
    ptr->field_EC_dr_env[1] = stru_800B1380[1];

    ptr++;
    DG_SetChanlOrderingTable_800179A8(ptr, (unsigned char*)dword_800B0F50, 0, 0, 0, 8, 1);
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    DG_SetChanlDrawEnv_800179F4(ptr, &drawEnv, 0);
    DG_CopyChanlDrawEnv_80017B30(ptr, 0);
    DG_CopyChanlDrawEnv_80017B30(ptr, 1);

    ptr->field_EC_dr_env[0] = stru_800B1380[0];
    ptr->field_EC_dr_env[1] = stru_800B1380[1];
}

void DG_DrawOTag_80017E4C(int activeBuffer)
{
    gOldRootCnt_800B1DC8[0] = gCurrentRootCnt_800AB984;
    gCurrentRootCnt_800AB984 = GetRCnt_800996E8(0xF2000001);
    DrawOTag_8008FE58((unsigned int*)&DG_Chanls_800B1800[0].field_6C_dr_env[activeBuffer]);
}

//not correct, revisit;
void DG_ClearChanlSystem_80017E9C( int which )
{
    int i, n_ot;
    unsigned int s4;
    unsigned long* ot;
    unsigned long v0, v1;
    DR_ENV* draw_env;
    DR_ENV* draw_env2;
    DG_CHNL* chnl;

    int v2;

    unsigned long *ots;
    chnl = DG_Chanls_800B1800;
    
    
    for ( i = 3 ; i > 0; -- i )
    {
        //loc_80017EF8
        ots = (unsigned long*)chnl->mOrderingTables[which];
        ot = ots;
        n_ot = pow2(chnl->word_6BC374_8);
        s4 =  (unsigned int)&ot[n_ot];

        ClearOTagR_8008FD50( ot, n_ot + 1 );

        if ( chnl->word_6BC37A_0_1EC_size > 0 )
        {
            //loc_80017F30
            DG_CopyChanlDrawEnv_80017B30( chnl, which );
            --chnl->word_6BC37A_0_1EC_size;
        }

        //loc_80017F50
        draw_env = &chnl->field_6C_dr_env[ which ];
        draw_env2 = &chnl->field_EC_dr_env[ which ];

        //addPrims(s4, draw_env2, draw_env); //should do the below
        v2 = s4 & 0x00FFFFFF;
        draw_env->tag = (draw_env->tag & 0xFF000000) | v2;

        v1 = ot[0];
        v1 = v1 & 0xFF000000;
        v0 = (unsigned int)draw_env2 & 0x00FFFFFF;

        ot[0] = v1 | v0;


        if (chnl->word_6BC376_16 >= 0)
        {
            //loc_80017F94
            ot = (unsigned long*)DG_Chanls_800B1800[0].mOrderingTables[which];
            ot = &ot[ chnl->word_6BC376_16 ];

            //addPrims(ot, draw_env, draw_env2); //should do the below            
            draw_env2->tag = (draw_env2->tag & 0xFF000000) | (ot[0] & 0x00FFFFFF);
            
            ot[0] = (ot[0] & 0xFF000000) | ((unsigned int)draw_env & 0x00FFFFFF);
        }
        else
        {
            //loc_80017FD8
            termPrim(draw_env2); //should do below
            
            //bottom 2 lines provide fake match
            draw_env2->tag |= 0x00FFFFFF; //shouldn't be here
            v1 = ot[0]; //shouldn't be here
        }
        chnl++;   
    }
}

void DG_RenderPipeline_80018028(int idx)
{
    unsigned short *pPerfArrayIter;
    TChanl_Fn *pRenderFns;
    int start_idx;
    int i;

    pPerfArrayIter = &gOldRootCnt_800B1DC8[1];
    if ( gObjectQueueVoided_800AB388 )
    {
        // Store the counter and set as 2 valid items
        *pPerfArrayIter = GetRCnt_800996E8(0xF2000001);
        N_ChanlPerfMax_800AB980 = 2;
    }
    else
    {
        GV_ZeroMemory_8001619C(byte_800B1400, 1024);
        pRenderFns = off_8009D35C;

        if ( !DG_HikituriFlag_8009D460 )
        {
            start_idx = 7;
        }
        else
        {
            start_idx = 1;
        }

        for ( i = start_idx; i > 0; --i )
        {
            *pPerfArrayIter++ = GetRCnt_800996E8(0xF2000001);
            // Call the render func, saving the time of the previous pass
            (*pRenderFns)(&DG_Chanls_800B1800[1], idx);
            pRenderFns++;
        }
        *pPerfArrayIter++ = GetRCnt_800996E8(0xF2000001);
        N_ChanlPerfMax_800AB980 = (pPerfArrayIter) - &gOldRootCnt_800B1DC8[0];
    }
}

void DG_80018128(int chanl, DRAWENV *pDrawEnv)
{
    DG_CHNL *pOt = &DG_Chanls_800B1800[chanl + 1];
    DG_SetChanlDrawEnv_800179F4(pOt, pDrawEnv, 0);
    pOt->word_6BC37A_0_1EC_size = 2;
}

static inline DG_CHNL *DG_GetChanl(int idx)
{
    return &DG_Chanls_800B1800[idx];
}

int DG_QueueObjs_80018178(DG_OBJS *pPrim)
{
    DG_CHNL *pOt = DG_GetChanl(pPrim->chanl + 1);
    int mTotalObjectCount = pOt->mTotalObjectCount;
    if (mTotalObjectCount >= pOt->mFreePrimCount)
    {
        return -1;
    }
    else
    {
        pOt->mQueue[mTotalObjectCount++] = pPrim;
        pOt->mTotalObjectCount = mTotalObjectCount;
        return 0;
    }
}

void DG_DequeueObjs_800181E4(DG_OBJS *objs)
{
    DG_CHNL* chnl;
    int n_chanl, n_objs, i;
    DG_OBJS** chnl_objs;
    
    n_chanl     = objs->chanl + 1;
    chnl        = &DG_Chanls_800B1800[ n_chanl ];

    n_objs   = chnl->mTotalObjectCount;
    chnl_objs   = chnl->mQueue;

    for ( i = n_objs ; i > 0; --i )
    {   
        if (*chnl_objs == objs) goto END;
        chnl_objs++;
    }
    return;

END:
    --i;
    for (; i > 0 ; --i) 
    {
        chnl_objs[0] = chnl_objs[1];
        chnl_objs++;
    }
    
    n_objs--;
    chnl->mTotalObjectCount = n_objs; 
}

int DG_QueuePrim_80018274(DG_OBJS *pPrim)
{
    int t = (short)pPrim->group_id + 1;
    DG_CHNL *pOt = &DG_Chanls_800B1800[t];
    int idx = pOt->mFreePrimCount;
    if (idx <= pOt->mTotalObjectCount)
    {
        return -1;
    }
    idx = idx - 1;
    pOt->mQueue[idx] = pPrim; // 58
    pOt->mFreePrimCount = idx;
    return 0;
}

void DG_DequeuePrim_800182E0(DG_OBJS *objs)
{
    int i;
    int group;
    int queue_size;
    int n_free_prims;
    
    DG_CHNL* chnl;
    DG_OBJS** chnl_objs;
    
    group       = (short)objs->group_id + 1;
    chnl        = &DG_Chanls_800B1800[ group ];
    
    n_free_prims = chnl->mFreePrimCount;
    queue_size   = chnl->mTotalQueueSize;
   
    chnl_objs = &chnl->mQueue[ queue_size ];
    i = queue_size - n_free_prims;
    
    for (; i > 0; --i )
    {   
        --chnl_objs;
        if (*chnl_objs == objs) goto END;
    }
    return;

END:
    --i;
    for (; i > 0 ; --i) 
    {
        chnl_objs[0] = chnl_objs[-1];
        chnl_objs--;
    }
    
    n_free_prims++;
    chnl->mFreePrimCount = n_free_prims; 
}

void DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2)
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

void DG_FreeObjectQueue_800183D4()
{
    DG_CHNL *pChan;
    DG_OBJS **mQueue;
    DG_OBJS *pItem;
    int     i;

    pChan = &DG_Chanls_800B1800[1];
    mQueue = (DG_OBJS**)pChan->mQueue;

    gObjectQueueVoided_800AB388 = 1;

    for (i = pChan->mTotalObjectCount; i > 0; i--)
    {
        pItem = *mQueue++;
        DG_FreeObjsPacket_8001ABA8(pItem, 0);
        DG_FreeObjsPacket_8001ABA8(pItem, 1);
    }
}

void DG_8001844C()
{
    gObjectQueueVoided_800AB388 = 0;
    DG_UnDrawFrameCount_800AB380 = 1;
}

void DG_SetBackgroundRGB_80018464(int r, int g, int b)
{
    DRAWENV drawEnv;
    DG_CHNL *pStruct = &DG_Chanls_800B1800[0];
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.isbg = 1;
    setRGB0(&drawEnv, r, g, b);
    DG_SetChanlDrawEnv_800179F4(pStruct, &drawEnv, 1);
    pStruct->word_6BC37A_0_1EC_size = 2;
}

void DG_Set_RGB_800184F4(int r,int b, int g)
{
    DG_r_800AB97C = r;
    DG_g_800AB97E = g;
    DG_b_800AB97D = b;
    DG_SetBackgroundRGB_80018464(r, b, g);
}

void DG_BackGroundBlack_80018520(void)
{
  DG_SetBackgroundRGB_80018464(0, 0, 0);
}
void DG_BackGroundNormal_80018548()
{
  DG_SetBackgroundRGB_80018464(DG_r_800AB97C, DG_b_800AB97D, DG_g_800AB97E);
}

void sub_80018574(unsigned char *a1)
{
  // TODO: Structure
  a1[4] = DG_r_800AB97C;
  a1[5] = DG_b_800AB97D;
  a1[6] = DG_g_800AB97E;
}

TChanl_Fn DG_SetChanlSystemUnits_80018598(int idx, TChanl_Fn newFunc)
{
  TChanl_Fn oldFunc = off_8009D35C[idx];
  off_8009D35C[idx] = newFunc;
  return oldFunc;
}
