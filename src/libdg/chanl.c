
#include "linker.h"
#include "dgd.h"


/**data************************/
/******************************/

/**gp***********************************************************************************************/
int             SECTION(".sbss") dword_800AB974;
int             SECTION(".sbss") dword_800AB978;
unsigned char   SECTION(".sbss") DG_r_800AB97C;
unsigned char   SECTION(".sbss") DG_b_800AB97D;
unsigned char   SECTION(".sbss") DG_g_800AB97E;
short           SECTION(".sbss") N_ChanlPerfMax_800AB980;
short           SECTION(".sbss") word_800AB982;
unsigned short  SECTION(".sbss") gCurrentRootCnt_800AB984;
/***************************************************************************************************/

/**sbss**********************************/
extern int GV_Clock_800AB920;
extern int GV_PauseLevel_800AB928;
extern int DG_HikituriFlagOld_8009D464;
/****************************************/

/**bss************************************************************************/
DG_CHNL         SECTION(".DG_Chanls_800B1800") DG_Chanls_800B1800[3];
int             SECTION(".dword_800B0630") dword_800B0630[68];
int             SECTION(".dword_800B0630") dword_800B0740[516];
int             SECTION(".dword_800B0630") dword_800B0F50[4];
DG_OBJS*        SECTION(".dword_800B0630") dword_800B0F60[8];
DG_OBJS*        SECTION(".dword_800B0630") dword_800B0F80[256];
DR_ENV          SECTION(".dword_800B0630") stru_800B1380[2];
unsigned short  SECTION(".gOldRootCnt_800B1DC8") gOldRootCnt_800B1DC8[32];
/****************************************************************************/

/**funcs************************************************************************************************************************/
extern void             DrawSyncCallback_8008F76C(void*);
unsigned int            GetRCnt_800996E8(unsigned int rcnt);
void                    DrawOTag_8008FE58(unsigned int *pOt);
extern void             SetDrawEnv_800906B0(DR_ENV *dr_env, DRAWENV *env);
extern void             DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2);
/*****************************************************************************************************************************/

//gets value of root counter 1 which determines time taken to finished drawing
//sets it to word_800AB982
void DG_DrawSyncCallback_80017984(void)
{
    word_800AB982 = GetRCnt_800996E8(0xf2000001);
}

//guessed function name
void DG_SetChanlOrderingTable_800179A8(DG_CHNL *pStruct, unsigned char *pOtBuffer, unsigned int otLen, void **pQueue, short queueSize, short param_6, short param_7)
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
    DG_SetChanlOrderingTable_800179A8(ptr, (unsigned char*)dword_800B0630, 5, (void**)dword_800B0F60, 8, -1, 1);
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.isbg = 1;
    DG_SetChanlDrawEnv_800179F4(ptr, &drawEnv, 1);
    DG_CopyChanlDrawEnv_80017B30(ptr, 0);
    DG_CopyChanlDrawEnv_80017B30(ptr, 1);

    ptr++;
    DG_SetChanlOrderingTable_800179A8(ptr, (unsigned char*)dword_800B0740, 8, (void**)dword_800B0F80, 256, 16, 1);
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    drawEnv.ofs[0] = 160;
    drawEnv.ofs[1] = 112;
    DG_SetChanlDrawEnv_800179F4(ptr, &drawEnv, 0);
    DG_CopyChanlDrawEnv_80017B30(ptr, 0);
    DG_CopyChanlDrawEnv_80017B30(ptr, 1);

    ptr->dword_6BC458 = stru_800B1380[0];
    ptr->dword_6BC498 = stru_800B1380[1];

    ptr++;
    DG_SetChanlOrderingTable_800179A8(ptr, (unsigned char*)dword_800B0F50, 0, 0, 0, 8, 1);
    DG_Init_DrawEnv_80018384(&drawEnv, 0, 0, 320, 224);
    DG_SetChanlDrawEnv_800179F4(ptr, &drawEnv, 0);
    DG_CopyChanlDrawEnv_80017B30(ptr, 0);
    DG_CopyChanlDrawEnv_80017B30(ptr, 1);

    ptr->dword_6BC458 = stru_800B1380[0];
    ptr->dword_6BC498 = stru_800B1380[1];
}

void DG_DrawOTag_80017E4C(int activeBuffer)
{
    gOldRootCnt_800B1DC8[0] = gCurrentRootCnt_800AB984;
    gCurrentRootCnt_800AB984 = GetRCnt_800996E8(0xF2000001);
    DrawOTag_8008FE58((unsigned int*)&DG_Chanls_800B1800[0].field_6C_dr_env[activeBuffer]);
}

/*
void DG_ClearChanlSystem_80017E9C( int which )
*/
