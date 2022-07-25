#include <sys/types.h>
#include <libgte.h>

void AssignXYFromVec_8003D1B8(SVECTOR *vec_1, SVECTOR *vec_2)
{
    vec_1->vx = vec_2->vx;
    vec_1->vy = vec_2->vy;
    vec_1->pad = 1;
    vec_1->vz = 0;
}
