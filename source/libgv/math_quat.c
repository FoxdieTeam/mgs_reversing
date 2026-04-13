#include "inline_n.h"
#include "libgv/libgv.h"

// The functions below are based on code listings from the article
// "Rotating Objects Using Quaternions" by Nick Bobick.
// http://www.gamasutra.com/features/19980703/quaternions_01.htm
// This article originally appeared in the February 1998 issue of
// Game Developer Magazine.

void GV_QuatToMat( SQUAT *quat, MATRIX *mat )
{
    int wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

    /* calculate coefficients */
    x2 = quat->x + quat->x;
    y2 = quat->y + quat->y;
    z2 = quat->z + quat->z;
    xx = quat->x * x2; xy = quat->x * y2; xz = quat->x * z2;
    yy = quat->y * y2; yz = quat->y * z2; zz = quat->z * z2;
    wx = quat->w * x2; wy = quat->w * y2; wz = quat->w * z2;

    mat->m[0][0] = ( 4096 * 4096 - (yy + zz) ) / 4096 ;
    mat->m[0][1] = (xy - wz) / 4096 ;
    mat->m[0][2] = (xz + wy) / 4096 ;

    mat->m[1][0] = (xy + wz) / 4096 ;
    mat->m[1][1] = ( 4096 * 4096 - (xx + zz) ) / 4096 ;
    mat->m[1][2] = (yz - wx) / 4096 ;

    mat->m[2][0] = (xz - wy) / 4096 ;
    mat->m[2][1] = (yz + wx) / 4096 ;
    mat->m[2][2] = ( 4096 * 4096 - (xx + yy) ) / 4096 ;

    mat->t[0] = 0;
    mat->t[1] = 0;
    mat->t[2] = 0;
}

void GV_EulerToQuat( SVECTOR *rot, SQUAT *quat )
{
    int cr, cp, cy, sr, sp, sy, cpcy, spsy;

    cr = rcos(rot->vx / 2);
    cp = rcos(rot->vy / 2);
    cy = rcos(rot->vz / 2);

    sr = rsin(rot->vx / 2);
    sp = rsin(rot->vy / 2);
    sy = rsin(rot->vz / 2);

    cpcy = (cp * cy) / 32;
    spsy = (sp * sy) / 32;

    quat->w = (cr * cpcy + sr * spsy) / (4096 * 4096 / 32);
    quat->x = (sr * cpcy - cr * spsy) / (4096 * 4096 / 32);
    quat->y = (cr * sp / 32 * cy + sr * cp / 32 * sy) / (4096 * 4096 / 32);
    quat->z = (cr * cp / 32 * sy - sr * sp / 32 * cy) / (4096 * 4096 / 32);
}

void GV_MatToQuat( MATRIX *mat, SQUAT *quat )
{
    int     tr, s, q[4];
    int     i, j, k;

    static int nxt[3] = {1, 2, 0};

    tr = mat->m[0][0] + mat->m[1][1] + mat->m[2][2];

    /* check the diagonal */
    if ( tr > 0 ) {
        s = SquareRoot12( tr + 4096 );
        quat->w = s / 2;
        s = 2048 * 4096 / s;

        quat->x = ( mat->m[2][1] - mat->m[1][2] ) * s / 4096 ;
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
        to1[0] = -to->x;
        to1[1] = -to->y;
        to1[2] = -to->z;
        to1[3] = -to->w;
    } else {
        to1[0] = to->x;
        to1[1] = to->y;
        to1[2] = to->z;
        to1[3] = to->w;
    }

    /* calculate coefficients */
    if ( (4096 - cosom) > 0 ){
        /* standard case (slerp) */
        sinom = SquareRoot12(4096 - ( cosom * cosom ) / 4096);
        omega = ratan2(sinom, cosom);
        sinom = 4096 * 4096 / sinom;
        scale0 = (rsin(((4096 - t) * omega) / 4096) * sinom) >> 12;
        scale1 = (rsin((t * omega) / 4096) * sinom) >> 12;
    } else {
        /* "from" and "to" quaternions are very close   */
        /*  ... so we can do a linear interpolation     */
        scale0 = 4096 - t;
        scale1 = t;
    }

    /* calculate final values */
    res->x = ( scale0 * from->x + scale1 * to1[0] ) / 4096 ;
    res->y = ( scale0 * from->y + scale1 * to1[1] ) / 4096 ;
    res->z = ( scale0 * from->z + scale1 * to1[2] ) / 4096 ;
    res->w = ( scale0 * from->w + scale1 * to1[3] ) / 4096 ;
}

void GV_QuatNormalize( SQUAT *quat )
{
    VECTOR vec;
    int    ww, len;

    gte_ldsv(quat);
    gte_sqr0();
    ww = quat->w * quat->w;
    gte_stlvnl(&vec);

    len = ww;
    len += vec.vx + vec.vy + vec.vz;

    len = SquareRoot0(len);
    if ( len > 0 )
    {
        len = 4096 * 4096 / len;
        quat->x = ( quat->x * len ) >> 12 ;
        quat->y = ( quat->y * len ) >> 12 ;
        quat->z = ( quat->z * len ) >> 12 ;
        quat->w = ( quat->w * len ) >> 12 ;
    }
}

void GV_QuatMul( SQUAT *q1, SQUAT *q2, SQUAT *res )
{
    res->x = ( q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y ) / 4096 ;
    res->y = ( q1->w * q2->y + q1->y * q2->w + q1->z * q2->x - q1->x * q2->z ) / 4096 ;
    res->z = ( q1->w * q2->z + q1->z * q2->w + q1->x * q2->y - q1->y * q2->x ) / 4096 ;
    res->w = ( q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z ) / 4096 ;

    GV_QuatNormalize( res );
}
