#if 0
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

// TODO: Move these to libgv.h
typedef struct {                /* long word type quaternion */
    long    x, y;
    long    z, w;
} QUAT;

typedef struct {                /* short word type quaternion */
    short   x, y;
    short   z, w;
} SQUAT;

// The functions below are based on code listings from the article
// "Rotating Objects Using Quaternions" by Nick Bobick.
// http://www.gamasutra.com/features/19980703/quaternions_01.htm
// This article originally appeared in the February 1998 issue of
// Game Developer Magazine.

void GV_MatToQuat( MATRIX *mat, SQUAT *quat )
{
    int     tr, s, q[4];
    int     i, j, k;

    int nxt[3] = {1, 2, 0};

    tr = mat->m[0][0] + mat->m[1][1] + mat->m[2][2];

    /* check the diagonal */
    if ( tr > 0 ) {

        s = SquareRoot12( tr + 4096 );
        quat->w = s / (2 * 4096);
        s = 2048 * 4096 / s;

        quat->x = ( mat->m[2][1] - mat->m[1][2] ) * s / 4096 ;
// clang-format off
        quat->y = ( mat->m[0][2] - mat->m[2][0] ) * s / 4096 ;
        quat->z = ( mat->m[1][0] - mat->m[0][1] ) * s / 4096 ;

    } else {

        /* diagonal is negative */
        i = 0;

        if ( mat->m[1][1] > mat->m[0][0] ) i = 1;
        if ( mat->m[2][2] > mat->m[i][i] ) i = 2;

        j = nxt[i];
        k = nxt[j];

        s = SquareRoot12( ( mat->m[i][i] - ( mat->m[j][j] + mat->m[k][k] ) ) + 4096 );

        q[i] = s / 2 ;

        if ( s != 0 ) s = 2048 * 4096 / s;

        q[3] = ( mat->m[k][j] - mat->m[j][k] ) * s / 4096 ;
        q[j] = ( mat->m[j][i] + mat->m[i][j] ) * s / 4096 ;
        q[k] = ( mat->m[k][i] + mat->m[i][k] ) * s / 4096 ;

        quat->x = q[0];
        quat->y = q[1];
        quat->z = q[2];
        quat->w = q[3];
    }

}

void GV_QuatSlerp( SQUAT *from, SQUAT *to, int t, SQUAT *res)
{
    int           to1[4];
    int          omega, cosom, sinom;
    int          scale0, scale1;

    /* calc cosine */
    cosom = ( from->x * to->x + from->y * to->y + from->z * to->z + from->w * to->w ) / 4096 ;

    /* adjust signs (if necessary) */
    if ( cosom < 0 ){
        cosom = -cosom;
        to1[0] = - to->x;
// clang-format on
        to1[1] = - to->y;
        to1[2] = - to->z;
        to1[3] = - to->w;
    } else {
        to1[0] = to->x;
        to1[1] = to->y;
        to1[2] = to->z;
        to1[3] = to->w;
    }

    /* calculate coefficients */

    if ( (4096 - cosom) > DELTA ) {     // FIXME: epsilon
        /* standard case (slerp) */
        omega = acos(cosom);            // FIXME: integer acos
        sinom = rsin(omega);
        scale0 = rsin((4096 - t) * omega) / sinom;
        scale1 = rsin(t * omega) / sinom;

    } else {
        /* "from" and "to" quaternions are very close   */
        /*  ... so we can do a linear interpolation     */
        scale0 = 4096 - t;
        scale1 = t;
    }
    /* calculate final values */
    res->x = scale0 * from->x + scale1 * to1[0];
    res->y = scale0 * from->y + scale1 * to1[0];
    res->z = scale0 * from->z + scale1 * to1[0];
    res->w = scale0 * from->w + scale1 * to1[0];
}
#endif
