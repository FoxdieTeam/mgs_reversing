#include "linker.h"
#include <sys\types.h>
#include <libgte.h>

void DG_8001EAD8(MATRIX *a1, MATRIX *a2)
{
    short v2;
    short v3;
    short v4;

    v2 = a1->m[1][0];
    a2->m[1][0] = a1->m[0][1];
    a2->m[0][1] = v2;

    v3 = a1->m[2][0];
    a2->m[2][0] = a1->m[0][2];
    a2->m[0][2] = v3;

    v4 = a1->m[2][1];
    a2->m[2][1] = a1->m[1][2];
    a2->m[1][2] = v4;


    if ( a1 != a2 )
    {
        a2->m[0][0] = a1->m[0][0];
        a2->m[1][1] = a1->m[1][1];
        a2->m[2][2] = a1->m[2][2];
    }
}
