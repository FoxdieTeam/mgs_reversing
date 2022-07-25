#include <sys/types.h>
#include <libgte.h>

void CopyVectorToScratchpad_800288BC(SVECTOR *vec_1, SVECTOR *vec_2)
{
    vec_2->vx = vec_1->vx;
    vec_2->vz = vec_1->vy;
    vec_2->vy = vec_1->vz;
}
