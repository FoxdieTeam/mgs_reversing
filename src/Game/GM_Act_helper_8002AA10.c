#include "linker.h"

extern int GM_AlertLevel_800ABA18;
int SECTION(".sbss") GM_AlertLevel_800ABA18;

extern int GM_AlertMax_800AB9E0;
int SECTION(".sbss") GM_AlertMax_800AB9E0;

extern int GM_NoiseLength_800ABA30;
int SECTION(".sbss") GM_NoiseLength_800ABA30;

extern int GM_NoisePower_800ABA24;
int SECTION(".sbss") GM_NoisePower_800ABA24;

void GM_Act_helper_8002AA10()
{
    int length;
    int max;

    // isn't this one of the inlines?
    length = GM_NoiseLength_800ABA30;
    if ( GM_NoiseLength_800ABA30 > 0 )
    {
        length = GM_NoiseLength_800ABA30 - 1;
    }
    if ( !length )
    {
        GM_NoisePower_800ABA24 = 0;
    }
    
    max = GM_AlertMax_800AB9E0;
    GM_NoiseLength_800ABA30 = length;
    GM_AlertMax_800AB9E0 = 0;
    GM_AlertLevel_800ABA18 = max;
}
