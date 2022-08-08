#include "libgv/libgv.h"
#include "game.h"

void sub_8002FC58(short *param_1, short *param_2, SVECTOR *param_3, int *param_4)
{
    SVECTOR vec;
    GV_DirVec3_80016FA0(param_3, *param_4, &vec);
    sub_8002EC8C(param_1, &vec.vx, param_2);
}
