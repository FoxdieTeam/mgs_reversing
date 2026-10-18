// vrsave: score table accessors for the VR mission index.

#include "mgstype.h"

int vrsave_800C9A68(int *table, unsigned int mission)
{
    if (mission < 30)
    {
        return table[0];
    }
    if (mission >= 30 && mission < 70)
    {
        return table[1];
    }
    return table[2];
}

int vrsave_800C9AA4(int *table, int mission)
{
    if (mission < 30)
    {
        if (mission >= 0 && mission < 15)
        {
            return table[3];
        }
        return table[4];
    }

    if (mission >= 70)
    {
        mission -= 40;
    }

    if (mission >= 30 && mission < 35)
    {
        return table[4];
    }
    if (mission >= 35 && mission < 40)
    {
        return table[5];
    }
    if (mission >= 40 && mission < 45)
    {
        return table[6];
    }
    if (mission >= 45 && mission < 50)
    {
        return table[7];
    }
    if (mission >= 50 && mission < 55)
    {
        return table[8];
    }
    if (mission >= 55 && mission < 60)
    {
        return table[9];
    }
    if (mission >= 60 && mission < 65)
    {
        return table[10];
    }
    return table[11];
}

int vrsave_800C9B8C(int *table, int mission)
{
    int idx;

    if (mission >= 0 && mission < 30)
    {
        return table[12 + mission % 15];
    }
    idx = mission % 10;
    return table[(mission % 10 < 5) ? idx + 12 : idx + 7];
}
