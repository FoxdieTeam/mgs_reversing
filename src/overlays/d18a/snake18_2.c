#include "common.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/vibrate.h"

typedef struct 
{
    char* str;
    char* str2;
} Type;

typedef struct 
{
    GV_ACT  actor;
    CONTROL control;
    OBJECT  body;    //0x9C

    char pad[4];
    SVECTOR unk184;
    int unk18C;
    char padding1[0x19C - 0x18C - sizeof(int)]; 
    SVECTOR unk19C;
    char padding2[0x1A4 - 0x19C - sizeof(SVECTOR)]; 
    int unk1A4;
    char padding3[0x1B0 - 0x1A4 - sizeof(int)]; 
    short unk1B0;
    char padding4[0x1C0 - 0x1B0 - sizeof(short)]; 
    int unk1C0;
    char padding5[0x7E4 - 0x1C0 - sizeof(int)]; 
    int unk7E4;
    char padding6[0x854 - 0x7E4 - sizeof(int)]; 
    int unk854;
    char padding7[0x858 - 0x854 - sizeof(int)]; 
    int unk858;
    char padding8[0x85C - 0x858 - sizeof(int)]; 
    int unk85C;
    char padding9[0x868 - 0x85C - sizeof(int)]; 
    int unk868;
    char padding10[0x86C - 0x868 - sizeof(int)]; 
    short unk86C;
    short unk86E;
    char padding11[(0x8A4 - 0x86E) - sizeof(short*)];
    short *unk8A4;
    Type *unk8A8;
    char padding12[(0x90C - 0x8A8) - sizeof(short*)]; 
    char unk90C;
    char unk90D;
    char unk90E;
} Snake18Work;

//short d18a_dword_800B77E0;    // bss?
extern int d18a_dword_800DAEF0;
extern int GM_PlayerStatus_800ABA50;
extern SVECTOR d18a_dword_800C3850;
extern SVECTOR d18a_dword_800C3858;
extern char d18a_dword_800C3864[];
extern char d18a_dword_800C3860[];

extern void GM_ConfigObjectAction(OBJECT *obj, int action_flag, int motion, int interp);
extern GV_ACT *NewBlood_80072728(MATRIX *arg0, int count);
extern VibrateWork *NewPadVibration_8005D58C(unsigned char *pData, int flags);

/*
void Snake18_800CB514(Snake18Work* work) 
{
    MATRIX sp10;
    MATRIX sp30;
    SVECTOR sp50;
    MATRIX* temp_s1;
    int var_v1;

    temp_s1 = &work->body.objs->objs[6].world;
    
    ReadRotMatrix(&sp10);
    DG_TransposeMatrix(&sp10, &sp30);
    MulMatrix0(&sp30, temp_s1, &sp30);
    DG_MatrixRotZYX(&sp30, &sp50);
    SetRotMatrix(&sp10);
    
    var_v1 = sp50.vx;
    if (var_v1 < 0) 
    {
        var_v1 += 0xF;
    }

    var_v1 &= 0xFFF0;
    
    d18a_dword_800B77E0 = var_v1;
}
*/

void Snake18_800CB59C(Snake18Work* work) 
{
    short temp_s0;
    
    if (d18a_dword_800DAEF0 >= 0) 
    {
        temp_s0 = work->control.turn.vy;
        
        if (GV_DiffDirS(temp_s0, d18a_dword_800DAEF0) != 0) 
        {
            work->control.turn.vy = GV_NearSpeed(GV_NearPhase(temp_s0, d18a_dword_800DAEF0), d18a_dword_800DAEF0, 0x40);
        }
    }
}

void Snake18_800CB60C(Snake18Work* work) 
{
    int temp_s1;
    int temp_v0;
    int diff;
    int x;

    temp_s1 = work->control.turn.vy;
    diff = GV_DiffDirS(temp_s1, d18a_dword_800DAEF0);

    if (diff == 0)
    {
        GM_PlayerStatus_800ABA50 &= ~0x10;
        temp_v0 = work->unk8A8->str[1];
        
        if (work->body.action_flag != temp_v0) 
        {
            GM_ConfigObjectAction(&work->body, temp_v0, 0, 4);
        }
        return;
    }
    else if (diff < 0)
    {
        x = work->unk8A8->str2[0xA];
    }
    else
    {
        x = work->unk8A8->str2[0xB];
    }

    if (work->body.action_flag != x) 
    {
        GM_ConfigObjectAction(&work->body, x, 0, 4);
    }
    
    temp_s1 = GV_NearPhase(temp_s1, d18a_dword_800DAEF0);
    work->control.turn.vy = GV_NearSpeed(temp_s1, d18a_dword_800DAEF0, 0x40);
}

int Snake18_800CB710(Snake18Work* work, int a1) 
{
    SVECTOR* vec = (a1 == 1) ? &work->unk184 : &work->unk19C;
    int val = (a1 == 1) ? work->body.action_flag : work->body.field_10;

    if ((vec->vx + vec->vy) == 1)
    {
        return val;
    }

    return -1;
}

void Snake18_800CB760(Snake18Work* work, int arg1) 
{
    if (arg1 != work->unk18C) 
    {
        work->unk1A4 = (int) ~arg1;
        work->unk18C = arg1;
        
        if ((arg1 == 0xFFFF) && (Snake18_800CB710(work, 2) >= 0)) 
        {
            work->unk1C0 = 4;
            work->unk1B0 = 2;
        }
    }
}

void Snake18_800CB7BC(Snake18Work* work, int arg1) 
{
    work->unk854 = arg1;
    work->unk858 = 0;
    work->unk86E = 0;
    work->unk86C = 0;
}

void Snake18_800CB7D0(Snake18Work* work, int arg1) 
{
    MATRIX* mat;
    MATRIX sp10;
    
    mat = &work->body.objs->objs[arg1].world;

    DG_SetPos(mat);
    DG_MovePos(&d18a_dword_800C3850);
    DG_RotatePos(&d18a_dword_800C3858);
    ReadRotMatrix(&sp10);
    NewBlood_80072728(&sp10, 1);
}

void Snake18_800CB838(Snake18Work* work) 
{
    if (!(work->unk868 & 4) && (GM_PlayerStatus_800ABA50 & 0x800) && (work->unk86C != 3)) 
    {
        work->unk85C = (int) (work->unk85C | 9);
    }
}

void Snake18_800CB888(Snake18Work* work) 
{
    if (work->unk90C != 0) 
    {
        NewPadVibration_8005D58C(d18a_dword_800C3860, 1);
        work->unk90C = (unsigned char) (work->unk90C - 1);
    }
    
    if (work->unk90D != 0) 
    {
        NewPadVibration_8005D58C(d18a_dword_800C3864, 2);
        work->unk90D = (unsigned char) (work->unk90D - 1);
        return;
    }
    
    work->unk90E = 0;
}