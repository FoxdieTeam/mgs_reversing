#ifndef __MGS_OVERLAYS_D18A_ANIMAL_SNAKE18_H__
#define __MGS_OVERLAYS_D18A_ANIMAL_SNAKE18_H__

typedef struct _Snake18Work
{
    char  pad0[0x854];
    int   f854;
    int   f858;
    char  pad1[0x86C - 0x858 - sizeof(int)];
    short f86C;
    short f86E;
} Snake18Work;

#endif // __MGS_OVERLAYS_D18A_ANIMAL_SNAKE18_H__
