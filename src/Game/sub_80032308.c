#include "libgv/libgv.h"
#include "libdg/libdg.h"

int sub_80032308(SVECTOR *pos, int param_2, DVECTOR *out)
{
    int     vecdir;
    int     diffvec;
    int     vy;
    SVECTOR vec, vec2;
    int     vecdirsub;

    sub_8003214C(&vec2, &vecdirsub);
    diffvec = GV_DiffVec3_80016E84(&vec2, pos) - param_2;
    if (diffvec < 0)
    {
        diffvec = 0;
        vy = 63;
    }
    else
    {
        vy = 63;
    }

    if (diffvec < 9500)
    {
        vy = 63 - diffvec / 150;
    }
    else
    {
        diffvec = 9500;
        vy = 0;
    }

    diffvec *= 4;
    if (diffvec > 9500)
    {
        diffvec = 9500;
    }

    GV_SubVec3_80016D40(pos, &vec2, &vec);
    vecdir = GV_VecDir2_80016EF8(&vec) + 1024;

    out->vx = sub_800321AC(vecdir - vecdirsub, diffvec * 31 / 9500);
    out->vy = vy;

    if (vy <= 0)
    {
        return -1;
    }
    return 0;
}
