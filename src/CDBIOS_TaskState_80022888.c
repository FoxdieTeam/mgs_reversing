#include "linker.h"

int SECTION(".int_800B4E58") cd_bios_task_state_800B4E58;

int CDBIOS_TaskState_80022888(void)
{
    return cd_bios_task_state_800B4E58;
}

void CDFS_ParseFileName_80022898(char *pOutput, char *pInput, int input_len)
{
    while ( input_len > 0 )
    {
        *pOutput++ = *pInput++;
        if ( !*pInput )
        {
            break;
        }
        
        --input_len;
        if ( *pInput == ';' )
        {
            break;
        }
    }
    *pOutput = 0;
}