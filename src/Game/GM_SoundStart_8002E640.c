#include "game.h"

extern int           GM_AlertMode_800ABA00;
extern int           dword_800ABA78[2];

extern int           dword_800ABA70;
int dword_800ABA70;

void GM_SoundStart_8002E640(void)
{
    if (dword_800ABA70 == 0)
    {
        sub_8002E508(dword_800ABA78[GM_AlertMode_800ABA00 != 0]);
    }
}