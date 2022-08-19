
char GM_NoiseSound_800B76E0[4][3];

char GM_GetNoiseSound_8002E614(int arg0, int arg1)
{
    return GM_NoiseSound_800B76E0[arg0 >> 8 & 3][arg1];
}