#include <sys/types.h>
#include <libgte.h>

void GV_AddVec3_80016D00(SVECTOR* vec1, SVECTOR* vec2, SVECTOR* dst)
{
    dst->vx = vec1->vx + vec2->vx;
    dst->vy = vec1->vy + vec2->vy;
    dst->vz = vec1->vz + vec2->vz;
}