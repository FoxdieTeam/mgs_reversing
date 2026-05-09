#include "libgv.h"

#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

/**
 * @brief Adds two 3D vectors.
 *
 * This function adds the components of two 3D vectors and stores the result
 * in the destination vector.
 *
 * @param vec1 Pointer to the first vector.
 * @param vec2 Pointer to the second vector.
 * @param vec3 Pointer to the destination vector where the result will be stored.
 */
void GV_AddVec3( SVECTOR *vec1, SVECTOR *vec2, SVECTOR *vec3 )
{
    vec3->vx = vec1->vx + vec2->vx;
    vec3->vy = vec1->vy + vec2->vy;
    vec3->vz = vec1->vz + vec2->vz;
}

/**
 * @brief Subtracts one 3D vector from another.
 *
 * This function subtracts the components of the second vector from the first
 * vector and stores the result in the destination vector.
 *
 * @param vec1 Pointer to the first vector.
 * @param vec2 Pointer to the second vector.
 * @param vec3 Pointer to the destination vector where the result will be stored.
 */
void GV_SubVec3( SVECTOR *vec1, SVECTOR *vec2, SVECTOR *vec3 )
{
    vec3->vx = vec1->vx - vec2->vx;
    vec3->vy = vec1->vy - vec2->vy;
    vec3->vz = vec1->vz - vec2->vz;
}

/**
 * @brief Calculates the length of a 3D vector.
 *
 * This function calculates the Euclidean length (magnitude) of a 3D vector.
 *
 * @param vec Pointer to the vector.
 * @return The length of the vector.
 */
int GV_VecLen3( SVECTOR *vec )
{
    VECTOR tmp;
    int    len;

    tmp.vx = vec->vx;
    tmp.vy = vec->vy;
    tmp.vz = vec->vz;
    Square0( &tmp, &tmp );
    len = SquareRoot0( tmp.vx + tmp.vy + tmp.vz );
    return len;
}

/**
 * @brief Scales a 3D vector by a ratio.
 *
 * This function scales the components of a 3D vector by a ratio defined by the
 * numerator and denominator.
 *
 * @param vec1 Pointer to the input vector.
 * @param vec2 Pointer to the output vector where the result will be stored.
 * @param len1 The denominator of the scaling ratio.
 * @param len2 The numerator of the scaling ratio.
 */
void GV_LenVec3( SVECTOR *vec1, SVECTOR *vec2, int len1, int len2 )
{
    int len;

    len = len2 * 4096;
    if ( len1 == 0 ) len1 = 1;
    len /= len1;
    vec2->vx = vec1->vx * len / 4096;
    vec2->vy = vec1->vy * len / 4096;
    vec2->vz = vec1->vz * len / 4096;
}

/**
 * @brief Calculates the difference between two 3D vectors.
 *
 * This function calculates the Euclidean distance between two 3D vectors.
 *
 * @param vec1 Pointer to the first vector.
 * @param vec2 Pointer to the second vector.
 * @return The distance between the two vectors.
 */
int GV_DiffVec3( SVECTOR *vec1, SVECTOR *vec2 )
{
    VECTOR tmp;

    tmp.vx = vec1->vx - vec2->vx;
    tmp.vy = vec1->vy - vec2->vy;
    tmp.vz = vec1->vz - vec2->vz;

    Square0( &tmp, &tmp );
    return SquareRoot0( tmp.vx + tmp.vy + tmp.vz );
}

/**
 * @brief Calculates the direction of a 2D vector.
 *
 * This function calculates the direction (angle) of a 2D vector in
 * the x-z plane.
 *
 * @param vec Pointer to the vector.
 * @return The direction of the vector in the x-z plane.
 */
int GV_VecDir2( SVECTOR *vec )
{
    return 4095 & ratan2( vec->vx, vec->vz );
}

/**
 * @brief Creates a 2D vector from an angle and radius.
 *
 * This function creates a 2D vector in the x-z plane from a given angle
 * and radius.
 *
 * @param dir The angle in the x-z plane.
 * @param len The radius (length) of the vector.
 * @param vec Pointer to the output vector where the result will be stored.
 */
void GV_DirVec2( int dir, int len, SVECTOR *vec )
{
    vec->vx = len * rsin( dir ) / 4096;
    vec->vy = 0;
    vec->vz = len * rcos( dir ) / 4096;
}

/**
 * @brief Creates a 3D vector from angles and length.
 *
 * This function creates a 3D vector from given angles and length using a
 * rotation matrix.
 *
 * @param dir Pointer to the vector containing the angles.
 * @param len The length of the vector.
 * @param vec Pointer to the output vector where the result will be stored.
 */
void GV_DirVec3( SVECTOR *dir, int len, SVECTOR *vec )
{
    MATRIX m0;

    RotMatrixYXZ( dir, &m0 );
    vec->vx = len * m0.m[ 0 ][ 2 ] / 4096;
    vec->vy = len * m0.m[ 1 ][ 2 ] / 4096;
    vec->vz = len * m0.m[ 2 ][ 2 ] / 4096;
}

int GV_DiffDirU( int from, int to )
{
    return 4095 & ( to - from );
}

int GV_DiffDirS( int from, int to )
{
    int diff;

    diff = 4095 & ( to - from );
    return ( diff <= 2048 ) ? diff : diff - 4096;
}

int GV_DiffDirAbs( int from, int to )
{
    int diff;

    diff = 4095 & ( to - from );
    return ( diff <= 2048 ) ? diff : 4096 - diff;
}

/**
 * @brief Generates a random unsigned integer within a range [0, input).
 *
 * @param input The upper bound of the range.
 * @return The random unsigned integer.
 */
int GV_RandU( int input )
{
    return ( input - 1 ) & rand();
}

/**
 * @brief Generates a random signed integer within a range [-input, input).
 *
 * @param input The -lower/upper bound of the range.
 * @return The random signed integer.
 */
int GV_RandS( int input )
{
    return ( ( input * 2 - 1 ) & rand() ) - input;
}
