#include <sys/types.h>
#include <libgte.h>

void AssignXY_8003D1A8(SVECTOR *vec, short vx, short vy)
{
    vec->vx = vx;
    vec->vy = vy;
    vec->pad = 0;
}
