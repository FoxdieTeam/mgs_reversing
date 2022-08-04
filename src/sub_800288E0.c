#include <SYS/TYPES.H>
#include <LIBGTE.H>

#define SCRPAD_ADDR 0x1f800000

typedef struct _SCRPAD
{
    char padding[0x14];
    SVECTOR vec1;
    SVECTOR vec2;
} SCRPAD;

void sub_800288E0(SVECTOR *vec, int delta)
{
    int iVar;
    short sVar;
    SVECTOR* vec_1  = (SVECTOR*)(SCRPAD_ADDR + 0x14);
    SVECTOR* vec_2 = (SVECTOR*)(SCRPAD_ADDR + 0x1c);

    iVar = vec->vx;
    
    sVar = iVar - delta;
    vec_1->vx = sVar;

    sVar = iVar + delta;
    vec_2->vx = sVar;

    iVar = vec->vy;
    sVar = iVar - delta;

    vec_1->vz = sVar;
    vec_2->vz = iVar + delta;
    
    iVar = vec->vz;
    vec_2->vy = iVar;
    vec_1->vy = iVar;
}
