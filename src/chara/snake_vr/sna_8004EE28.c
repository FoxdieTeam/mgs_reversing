#include "chara/snake/sna_init.h"
#include "Game/camera.h"

extern UnkCameraStruct gUnkCameraStruct_800B77B8;

// TODO: Replace argument with Actor_SnaVRInit
void sna_8004EE28(Actor_SnaInit *snake)
{
    MATRIX  mat1;
    MATRIX  mat2;
    SVECTOR vec;
    int     vx;
    MATRIX *world = &snake->field_9C_obj.objs->objs[6].world;

    ReadRotMatrix(&mat1);
    DG_TransposeMatrix_8001EAD8(&mat1, &mat2);
    MulMatrix0(&mat2, world, &mat2);
    DG_MatrixRotZYX_8001E92C(&mat2, &vec);
    SetRotMatrix(&mat1);
    vx = vec.vx;
    if (vx < 0)
    {
        vx += 0xf;
    }
    vx &= 0xfff0;
    gUnkCameraStruct_800B77B8.field_28.vx = vx;
}
