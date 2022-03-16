#include "linker.h"
#include "libdg.h"
#include "dgd.h"
#include "libgv.h"

// force gp
extern unsigned short gOldRootCnt_800B1DC8[];
unsigned short SECTION(".gOldRootCnt_800B1DC8") gOldRootCnt_800B1DC8[32];

// force gp
extern int              gObjectQueueVoided_800AB388;
int SECTION(".sdata")   gObjectQueueVoided_800AB388;

unsigned char SECTION(".byte_800B1400") byte_800B1400[1024];

extern TChanl_Fn off_8009D35C[];

extern int DG_HikituriFlag_8009D460;

extern DG_CHNL DG_Chanls_800B1800[];

extern short N_ChanlPerfMax_800AB980;
short SECTION(".sbss") N_ChanlPerfMax_800AB980;

unsigned int                    GetRCnt_800996E8(unsigned int rcnt);


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
