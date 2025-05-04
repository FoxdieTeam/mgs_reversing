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
 * @param dst Pointer to the destination vector where the result will be stored.
 */
void GV_AddVec3(SVECTOR *vec1, SVECTOR *vec2, SVECTOR *dst)
{
    dst->vx = vec1->vx + vec2->vx;
    dst->vy = vec1->vy + vec2->vy;
    dst->vz = vec1->vz + vec2->vz;
}

/**
 * @brief Subtracts one 3D vector from another.
 *
 * This function subtracts the components of the second vector from the first
 * vector and stores the result in the destination vector.
 *
 * @param vec1 Pointer to the first vector.
 * @param vec2 Pointer to the second vector.
 * @param dst Pointer to the destination vector where the result will be stored.
 */
void GV_SubVec3(SVECTOR *vec1, SVECTOR *vec2, SVECTOR *dst)
{
    dst->vx = vec1->vx - vec2->vx;
    dst->vy = vec1->vy - vec2->vy;
    dst->vz = vec1->vz - vec2->vz;
}

/**
 * @brief Calculates the length of a 3D vector.
 *
 * This function calculates the Euclidean length (magnitude) of a 3D vector.
 *
 * @param vec Pointer to the vector.
 * @return The length of the vector.
 */
int GV_VecLen3(SVECTOR *vec)
{
    int    length;
    VECTOR vec2;

    vec2.vx = vec->vx;
    vec2.vy = vec->vy;
    vec2.vz = vec->vz;
    Square0(&vec2, &vec2);
    length = SquareRoot0(vec2.vx + vec2.vy + vec2.vz);
    return length;
}

/**
 * @brief Scales a 3D vector by a ratio.
 *
 * This function scales the components of a 3D vector by a ratio defined by the
 * numerator and denominator.
 *
 * @param in Pointer to the input vector.
 * @param out Pointer to the output vector where the result will be stored.
 * @param denom The denominator of the scaling ratio.
 * @param num The numerator of the scaling ratio.
 */
void GV_LenVec3(SVECTOR *in, SVECTOR *out, int denom, int num)
{
    int ratio;

    ratio = num * 4096;

    if (denom == 0)
    {
        denom = 1;
    }

    ratio /= denom;

    out->vx = in->vx * ratio / 4096;
    out->vy = in->vy * ratio / 4096;
    out->vz = in->vz * ratio / 4096;
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
int GV_DiffVec3(SVECTOR *vec1, SVECTOR *vec2)
{
    VECTOR diff;

    diff.vx = vec1->vx - vec2->vx;
    diff.vy = vec1->vy - vec2->vy;
    diff.vz = vec1->vz - vec2->vz;

    Square0(&diff, &diff);
    return SquareRoot0(diff.vx + diff.vy + diff.vz);
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
int GV_VecDir2(SVECTOR *vec)
{
    return ratan2(vec->vx, vec->vz) & (4096 - 1);
}

/**
 * @brief Creates a 2D vector from an angle and radius.
 *
 * This function creates a 2D vector in the x-z plane from a given angle
 * and radius.
 *
 * @param angle The angle in the x-z plane.
 * @param radius The radius (length) of the vector.
 * @param out Pointer to the output vector where the result will be stored.
 */
void GV_DirVec2(int angle, int radius, SVECTOR *out)
{
    out->vx = radius * rsin(angle) / 4096;
    out->vy = 0;
    out->vz = radius * rcos(angle) / 4096;
}

/**
 * @brief Creates a 3D vector from angles and length.
 *
 * This function creates a 3D vector from given angles and length using a
 * rotation matrix.
 *
 * @param angle Pointer to the vector containing the angles.
 * @param length The length of the vector.
 * @param out Pointer to the output vector where the result will be stored.
 */
void GV_DirVec3(SVECTOR *angle, int length, SVECTOR *out)
{
    MATRIX matrix;

    RotMatrixYXZ(angle, &matrix);
    out->vx = length * matrix.m[0][2] / 4096;
    out->vy = length * matrix.m[1][2] / 4096;
    out->vz = length * matrix.m[2][2] / 4096;
}

unsigned int GV_DiffDirU(int from, int to)
{
    return (to - from) & 0xfff;
}

int GV_DiffDirS(int from, int to)
{
    int result = (to - from) & (4096 - 1);
    if (result > (4096 / 2))
    {
        result -= 4096;
    }
    return result;
}

int GV_DiffDirAbs(int from, int to)
{
    int diff = (to - from) & 4095;

    if (diff <= 2048)
    {
        return diff;
    }
    else
    {
        return 4096 - diff;
    }
}

/**
 * @brief Generates a random unsigned integer within a range [0, input).
 *
 * @param input The upper bound of the range.
 * @return The random unsigned integer.
 */
int GV_RandU(unsigned int input)
{
    return (input - 1) & rand();
}

/**
 * @brief Generates a random signed integer within a range [-input, input).
 *
 * @param input The -lower/upper bound of the range.
 * @return The random signed integer.
 */
int GV_RandS(int input)
{
    return (((input * 2) - 1) & rand()) - input;
}
