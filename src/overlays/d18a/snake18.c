#include <sys/types.h>

typedef struct 
{
    char padding[0x7E4]; // Padding to match the offset
    int unk7E4;
    char padding2[0xC0 - sizeof(short*)]; // Padding to match the offset
    short* unk8A4;
} arg0_t;

void Snake18_800CABEC(arg0_t* arg0) 
{
    int var_v1;
    unsigned char* var_a1;
    short* temp_a1;

    temp_a1 = arg0->unk8A4;
    arg0->unk7E4 &= ~0x4000;
    
    if ((temp_a1[0xA / sizeof(short)] != 0) && (((ushort)temp_a1[0] & 0xF000) != 0)) 
    {
        var_a1 = (char*)temp_a1 + 0xC;

        for (var_v1 = 0; var_v1 < 4; ++var_v1)
        {
            if ((*var_a1 - 0x50) >= 0x61U) 
            {
                arg0->unk7E4 |= 0x4000;
                return;
            }
            var_a1 += 1;
        }
    }
}

int Snake18_800CAC68(int arg0, int arg1) 
{
    int temp_v1;

    if (arg1 < 0) 
        return 0;

    temp_v1 = (arg1 - arg0) & 0xFFF;
    
    if (temp_v1 < 0x800) 
    {
        if (temp_v1 < 0x100) 
            return 1;

        if (temp_v1 >= 0x501) 
            return 3;

        return 4;
    }
    
    if (temp_v1 >= 0xF01)
        return 1;

    if (temp_v1 < 0xB00)
        return 3;

    return 2;
}
