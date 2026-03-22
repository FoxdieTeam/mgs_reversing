// clang-format off
#if 0
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
        to1[0] =
#endif
// clang-format on
