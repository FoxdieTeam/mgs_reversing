#include <util/idaTypes.h>
#include <sys/types.h>
#include <libgte.h>

void GV_SubVec3_80016D40(SVECTOR* vec1, SVECTOR* vec2, SVECTOR* dst)
{
    dst->vx = vec1->vx - vec2->vx;
    dst->vy = vec1->vy - vec2->vy;
    dst->vz = vec1->vz - vec2->vz;
}