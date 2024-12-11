#include "common.h"
#include "Game/control.h"

typedef struct 
{
    char* str;
} Type;

typedef struct 
{
    GV_ACT  actor;
    CONTROL control;
    char padding1[0x7E4 - (sizeof(GV_ACT) + sizeof(CONTROL))]; 
    int unk7E4;
    char padding2[(0x8A4 - 0x7E4) - sizeof(short*)];
    short *unk8A4;
    Type *unk8A8;
} Snake18Work;

// @todo(Voxel): Cleanup: Merge structs? Differenet structs? Some overlap?
typedef struct 
{
    char pad[8];
    HZD_HDL* unk8;
} Unk2C;

typedef struct 
{
    char padding7;
    short unk2;
    char padding4[(0x2C - 0x2) - sizeof(short)]; 
    Unk2C* unk2C;
    char padding5[(0x7A - 0x2C) - sizeof(Unk2C*)];
    short unk7A;
} Snake18Work_Temp;

extern int d18a_dword_800DAF0C;
extern SVECTOR* d18a_dword_800DAEF8;
extern char *d18a_dword_800DAEFC;
extern int d18a_dword_800DAEF4;
extern int d18a_dword_800DAF08;
extern int d18a_dword_800DAEF0;

extern HZD_FLR *d18a_dword_800DAF00[2];
extern HZD_FLR *d18a_dword_800DAF10;
extern int GM_PlayerStatus_800ABA50;

void Snake18_800CABEC(Snake18Work *arg0) 
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

void Snake18_800CACD0(Snake18Work *work) 
{
    int ang;
    int f58;
    int slope;
    int diff;

    d18a_dword_800DAEF8 = NULL;
    d18a_dword_800DAEF4 = -1;
    d18a_dword_800DAF0C = 0;
    d18a_dword_800DAF10 = 0;
    d18a_dword_800DAF08 = 0;

    ang = d18a_dword_800DAEF0 = work->unk8A4[4];
    
    d18a_dword_800DAF00[1] = NULL;
    d18a_dword_800DAF00[0] = NULL;

    if (work->control.field_36 != -2) 
    {
        HZD_800298C0(d18a_dword_800DAF00);

        if (d18a_dword_800DAF00[0] != NULL) 
        {
            d18a_dword_800DAF08 = d18a_dword_800DAF00[0]->p4.h; // flags
        }
    }

    f58 = work->control.field_58;
    if (f58 <= 0) 
    {
        return; 
    }
    
    d18a_dword_800DAEF8 = &work->control.field_60_vecs_ary[0];
    d18a_dword_800DAEFC = work->control.field_5A;
    d18a_dword_800DAEF4 = GV_VecDir2(&work->control.field_60_vecs_ary[0]);
    d18a_dword_800DAF10 = work->control.field_70[0];
    
    if (ang >= 0) 
    {
        if (f58 != 1) 
        {
            slope = GV_VecDir2(&work->control.field_60_vecs_ary[1]);

            if (GV_DiffDirAbs(ang, d18a_dword_800DAEF4) > GV_DiffDirAbs(ang, slope)) 
            {
                d18a_dword_800DAEF8 = &work->control.field_60_vecs_ary[1];
                d18a_dword_800DAEF4 = slope;
                d18a_dword_800DAF10 = work->control.field_70[1];
                d18a_dword_800DAEFC += 1;
            }
        }

        if (!(*d18a_dword_800DAEFC & 0x40))
        {
            diff = GV_DiffDirS(ang, d18a_dword_800DAEF4);

            if (diff >= -896 && diff <= 896)
            {
                d18a_dword_800DAF0C = 1;

                if (diff >= 0) 
                {
                    if (diff > 256) 
                    {
                        d18a_dword_800DAF0C = 4;
                    }
                }
                else
                {
                    if (diff < -256) 
                    {
                        d18a_dword_800DAF0C = 2;
                    }
                }
            }
        }
    }
}

int Snake18_800CAEC0(int arg1, int arg2) // unused var?
{
    int temp_a0;
    int var_a1;

    var_a1 = arg2;
    if (*d18a_dword_800DAEFC & 0x40)
    {
        return var_a1;
    }
    
    if (d18a_dword_800DAEF4 >= 0) 
    {
        temp_a0 = (var_a1 - d18a_dword_800DAEF4) & 0xFFF;
        
        if (temp_a0 < 0x400) 
        {
            var_a1 = d18a_dword_800DAEF4 + 0x400;
        }
        
        if (temp_a0 >= 0xC01) 
        {
            var_a1 = d18a_dword_800DAEF4 - 0x400;
        }
    }
    
    return var_a1;
}

int Snake18_800CAF20(int arg0) 
{
    HZD_VEC sp10;    // sp14
    SVECTOR sp18;
    Snake18Work_Temp* temp_s1;
    int temp;

    temp_s1 = (Snake18Work_Temp*)(arg0 + 0x20);  // @todo(Voxel): 
    if ((temp_s1->unk7A - temp_s1->unk2) >= 0x5DC) 
    {
        sp18.vy = 0;       // sp1A
        sp18.vx = 0;       // sp18
        sp18.vz = 0xC8;    // sp1C
        
        DG_PutVector(&sp18, &sp18, 1);
        sp10.long_access[0] = 0;
        temp = 0x7FFF;
        sp10.long_access[1] = temp;
        HZD_800296C4(temp_s1->unk2C->unk8, &sp18, 3);
        HZD_800298DC(&sp10);

        if ((sp10.long_access[1] - sp18.vy) >= 0x5DC) 
        {
            sp18.vy = 0;
            sp18.vx = 0;
            sp18.vz = -0x3E8;    // @todo: 
            
            DG_PutVector(&sp18, &sp18, 1);
            sp10.long_access[0] = 0;
            sp10.long_access[1] = temp;
            HZD_800296C4(temp_s1->unk2C->unk8, &sp18, 3);
            HZD_800298DC(&sp10);
            
            return (sp10.long_access[1] - sp18.vy) < 0x5DC;
        }
    }
    
    return 1;
}

typedef struct 
{
    char pad1[0x6C];
    short unk6C;
    char pad2[0x98 - 0x6C - (sizeof(short))];
    short unk98;
    char pad3[0x8FE - 0x98 - (sizeof(short))];
    short unk8FE;
    char pad4[0x902 - 0x8FE - (sizeof(short))];
    short unk902;
} Arg0;

void Snake18_800CB030(Arg0* arg0) 
{
    SVECTOR vec;
    SVECTOR sp18;
    short temp_s1;
    int temp_v0;
    int var_v1;
    HZD_FLR* temp_a1;   // @todo(Voxel): Var re-names etc.

    temp_s1 = arg0->unk8FE;
    if (temp_s1 != 2) 
    {
        arg0->unk902 = 0;
        return;
    }
    
    vec.vy = 0;
    vec.vx = 0;
    vec.vz = 0x2EE;
    DG_PutVector(&vec, &vec, 1);
    
    temp_a1 = d18a_dword_800DAF00[0];
    
    if ((temp_a1 == NULL) || (temp_a1->b1.h == temp_s1)) 
    {
        arg0->unk902 = 0;
        if (!(GM_PlayerStatus_800ABA50 & 1)) 
        {
            arg0->unk6C = 0;
        }
    } 
    else 
    {
        temp_v0 = HZD_SlopeFloorLevel(&vec, (SVECTOR*)temp_a1) - arg0->unk98;   // @todo(Voxel): Cleanup
        sp18.vx = temp_v0;
        sp18.vz = SquareRoot0(0x89544 - (temp_v0 * temp_v0));
        var_v1 = -GV_VecDir2(&sp18);
        
        if (var_v1 < -0x800) 
        {
            var_v1 += 0x1000;
        }
        
        arg0->unk902 = var_v1;
        
        if (!(GM_PlayerStatus_800ABA50 & 1)) 
        {
            arg0->unk6C = var_v1;
        }
    }
}

int Snake18_800CB134(Snake18Work* work) 
{
    int temp_s0;
    int temp_s0_2;
    int temp_s0_3;
    
    if (work->control.field_58 < 2)
    {
        return 0;
    }
    
    temp_s0 = GV_VecDir2(&work->control.field_60_vecs_ary[0]);
    temp_s0_2 = GV_VecDir2(&work->control.field_60_vecs_ary[1]);
    temp_s0_3 = GV_DiffDirAbs(d18a_dword_800DAEF0, temp_s0);
    
    if (((GV_DiffDirAbs(d18a_dword_800DAEF0, temp_s0_2) + 0x380) < 0x701U))
    {
        if (((temp_s0_3 + 0x380) < 0x701U))
        {
            return 1;
        }
    }
    
    return 0;
}

int Snake18_800CB1C8(Snake18Work* work) 
{
    int temp_v1;

    if (*d18a_dword_800DAEFC & 0x90) 
    {
        return  0; 
    }
    
    temp_v1 = d18a_dword_800DAF10->b1.y + d18a_dword_800DAF10->b1.h;
    
    if (d18a_dword_800DAF10->b1.y < work->control.mov.vy)
    {
        if (temp_v1 > work->control.mov.vy)
            return 1;
    }
    
    return 0;
}

void Snake18_800CB228(Snake18Work* work, int arg1) 
{
    int var_v1;

    var_v1 = GV_DiffDirS(arg1, work->control.rot.vy);
    
    if (var_v1 >= 0x81) 
    {
        var_v1 = 0x80;
    }
    else if (var_v1 < -0x80) 
    {
        var_v1 = -0x80;
    }
    
    work->control.turn.vz = var_v1;
}

short Snake18_800CB280(Snake18Work* work, int arg1) 
{
    if (arg1 == 0) 
        return work->unk8A8->str[0];
    else if (arg1 == 1) 
        return work->unk8A8->str[2];
    else if (arg1 == 2)
        return work->unk8A8->str[3];

    return -1;
}

// Todo:        d18a_snake18_800CB2EC   https://decomp.me/scratch/UVAkx (M2C_ERROR)
//      Done:        d18a_snake18_800CB34C   https://decomp.me/scratch/9w98i
//      Done:        d18a_snake18_800CB34C   https://decomp.me/scratch/Yq7dc
// Todo:        d18a_snake18_800CB378   https://decomp.me/scratch/T45AR (M2C_ERROR)
// Todo:        d18a_snake18_800CB3E8   https://decomp.me/scratch/VuutT 
// Todo:        d18a_snake18_800CB42C   https://decomp.me/scratch/Menij
// Todo:        d18a_snake18_800CB470   https://decomp.me/scratch/YLL1m
// Todo:        d18a_snake18_800CB514   https://decomp.me/scratch/jVQmU 
//      Done:   d18a_snake18_800CB59C        https://decomp.me/scratch/LA1cM
// Todo:        d18a_snake18_800CB60C   https://decomp.me/scratch/D94DB