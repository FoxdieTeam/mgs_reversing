#include <util/idaTypes.h>
#include <sys/types.h>
#include <libgte.h>

extern DWORD Square0_80093340(VECTOR*, VECTOR*); //TODO type?
extern DWORD SquareRoot0_80092708(int);

DWORD GV_VecLen3_80016D80(SVECTOR* vec)
{
    DWORD length;
    VECTOR vec2;

    vec2.vx = vec->vx;
    vec2.vy = vec->vy;
    vec2.vz = vec->vz;
    Square0_80093340(&vec2,&vec2);
    length = SquareRoot0_80092708(vec2.vx + vec2.vy + vec2.vz);
    return length;
}
