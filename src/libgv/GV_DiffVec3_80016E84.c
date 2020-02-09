#include <sys/types.h>
#include <libgte.h>

void Square0_80093340(VECTOR* vec1, VECTOR* vec2);
int SquareRoot0_80092708(int input);

int GV_DiffVec3_80016E84(SVECTOR* vec1, SVECTOR* vec2)
{
    VECTOR diff;
    diff.vx = vec1->vx - vec2->vx;
    diff.vy = vec1->vy - vec2->vy;
    diff.vz = vec1->vz - vec2->vz;
    
    Square0_80093340(&diff, &diff);
    return SquareRoot0_80092708(diff.vx + diff.vy + diff.vz);
}