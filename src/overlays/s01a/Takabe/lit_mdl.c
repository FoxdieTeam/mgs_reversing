#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/object.h"

typedef struct LitMdlWork
{
    GV_ACT         actor;
    int            field_20;
    OBJECT_NO_ROTS field_24_obj;
    MATRIX         field_48_light;
    short          field_68;
    short          field_6A;
    short          field_6C;
    short          field_6E;
    int            field_70;
    short          field_74;
    short          field_76;
    int            field_78;
    int            field_7C;
    int            field_80;
    int            field_84;
    MATRIX         field_88_root;
    MATRIX        *field_A8;
    int            field_AC;
    int            field_B0;
    int            field_B4;
    int            field_B8;
    int            field_BC;
    int            field_C0;
    int            field_C4;

    DG_DEF field_C8;
    DG_MDL field_E8;

    SVECTOR        field_140_vertexIndexOffsets[49];
    unsigned char  field_2C8_faceIndexOffsets[144];
    SVECTOR        field_358_normalIndexOffsets[7];
    unsigned char  field_390_normalFaceOffsets[144];
    unsigned char  field_420_uvOffsets[288];
    unsigned short field_540_materialOffsets[36];
} LitMdlWork;

DG_DEF litmdl_dg_def =
{
    1, 1,
    {-32000, -32000, -32000},
    {32000, 32000, 32000},
    {
        {
            1027, 36,
            {-32000, -32000, -32000},
            {32000, 32000, 32000},
            {0, 0, 0},
            -1, -1, 49,
            NULL, NULL, 6, NULL,
            NULL, NULL, NULL, 0
        }
    }
};

extern MATRIX  DG_ZeroMatrix_8009D430;
extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_CurrentMap_800AB9B0;
extern int     GV_PauseLevel_800AB928;
extern DG_CHNL DG_Chanls_800B1800[3];

void s01a_lit_mdl_800E26EC(LitMdlWork *work)
{
    int      scale;
    DG_MDL  *mdl;
    SVECTOR *vertexIndexOffsets;
    SVECTOR *vertexIndexOffsetsIter;
    int     *scratch;
    int      sinval1, sinval2, cosval;
    int      inc;
    int      vertexIndexOffsetVal;
    int      angle;
    int      i, j;

    vertexIndexOffsets = work->field_140_vertexIndexOffsets;
    scratch = (int *)0x1F800000;

    inc = work->field_BC;
    scale = work->field_B0;
    angle = work->field_C0 - (inc * 3);

    for (i = 7; i > 0; i--)
    {
        vertexIndexOffsetsIter = vertexIndexOffsets;

        sinval1 = rsin(angle);
        cosval = rcos(angle);

        if (cosval != 0)
        {
            *scratch = 0x01000000 / cosval;
            vertexIndexOffsetVal = 0x01000000 / cosval;
        }
        else
        {
            *scratch = 0x01000000;
            vertexIndexOffsetVal = 0x01000000;
        }

        vertexIndexOffsetVal = (((scale * sinval1) >> 12) * vertexIndexOffsetVal) >> 12;
        for (j = 7; j > 0; j--)
        {
            vertexIndexOffsetsIter->vz = vertexIndexOffsetVal;
            vertexIndexOffsetsIter++;
        }

        angle += inc;
        vertexIndexOffsets += 7;
        scratch++;
    }
    vertexIndexOffsets = work->field_140_vertexIndexOffsets;

    inc = work->field_BC;
    angle = -(inc * 6) / 2;
    scale = work->field_B0;

    for (i = 7; i > 0; i--)
    {
        sinval2 = rsin(angle);
        cosval = rcos(angle);
        scratch = (int *)0x1F800000;
        vertexIndexOffsetsIter = vertexIndexOffsets;
        vertexIndexOffsetVal = (scale * sinval2) / cosval;
        for (j = 7; j > 0; j--)
        {
            vertexIndexOffsetsIter->vx = ((vertexIndexOffsetVal * *scratch) >> 12);
            scratch++;
            vertexIndexOffsetsIter += 7;
        }
        angle += inc;
        vertexIndexOffsets++;
    }
    mdl = &work->field_E8;
    mdl->min.vy = 0;
    mdl->max.vy = 1;
    mdl->min.vz = work->field_140_vertexIndexOffsets[0].vz;
    mdl->max.vz = work->field_140_vertexIndexOffsets[42].vz;
    mdl->min.vx = work->field_140_vertexIndexOffsets[42].vx;
    mdl->max.vx = work->field_140_vertexIndexOffsets[48].vx;
}

void s01a_lit_mdl_800E2928(LitMdlWork *work)
{
    int mat1;
    int mat2;
    int mat3;
    int field_C4;

    GM_CurrentMap_800AB9B0 = work->field_20;
    work->field_88_root = DG_ZeroMatrix_8009D430;

    mat1 = work->field_A8->m[0][2];
    mat2 = work->field_A8->m[2][2];
    mat3 = work->field_A8->m[1][2];

    work->field_C4 = field_C4 = ratan2(mat1, mat2);
    work->field_C0 = ratan2(mat3, SquareRoot0(mat1 * mat1 + mat2 * mat2)) + 1024;

    RotMatrixY(field_C4, &work->field_88_root);

    work->field_88_root.t[0] = work->field_A8->t[0];
    work->field_88_root.t[1] = work->field_AC;
    work->field_88_root.t[2] = work->field_A8->t[2];

    work->field_B0 = work->field_A8->t[1] - work->field_AC;

    if (GV_PauseLevel_800AB928 == 0)
    {
        s01a_lit_mdl_800E26EC(work);
    }

    if (DG_Chanls_800B1800[1].field_30_eye.t[1] > work->field_AC)
    {
        DG_VisibleObjs(work->field_24_obj.objs);
    }
    else
    {
        DG_InvisibleObjs(work->field_24_obj.objs);
    }
}

void s01a_lit_mdl_800E2ABC(LitMdlWork *work)
{
    GM_FreeObject((OBJECT *)&work->field_24_obj);
}

void s01a_lit_mdl_800E2D64(LitMdlWork *, SVECTOR *);

int s01a_lit_mdl_800E2ADC(LitMdlWork *work, MATRIX *arg2, int arg3, int arg4, int raise)
{
    OBJECT_NO_ROTS *obj;
    short           map;

    memcpy(&work->field_C8, &litmdl_dg_def, sizeof(DG_DEF) + sizeof(DG_MDL));
    s01a_lit_mdl_800E2D64(work, &DG_ZeroVector_800AB39C);

    obj = &work->field_24_obj;
    obj->flag = 0x15D;
    obj->light = &work->field_48_light;
    obj->map_name = GM_CurrentMap_800AB9B0;
    obj->objs = DG_MakeObjs(&work->field_C8, obj->flag, 0);
    DG_QueueObjs(obj->objs);

    map = obj->map_name;
    work->field_24_obj.objs->group_id = map;
    work->field_24_obj.objs->root = &work->field_88_root;
    work->field_24_obj.objs->light = &work->field_48_light;
    work->field_24_obj.objs->objs[0].raise = raise;
    work->field_20 = GM_CurrentMap_800AB9B0;
    work->field_88_root = DG_ZeroMatrix_8009D430;
    work->field_B0 = 1;
    work->field_A8 = arg2;
    work->field_AC = arg3;
    work->field_B4 = arg4;
    work->field_B8 = arg4 / 6;
    work->field_BC = arg4 / 6;
    return 0;
}

GV_ACT *s01a_lit_mdl_800E2C88(MATRIX *arg0, int arg1, int arg2, int arg3)
{
    LitMdlWork *work;

    work = (LitMdlWork *)GV_NewActor(7, sizeof(LitMdlWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)s01a_lit_mdl_800E2928,
                         (TActorFunction)s01a_lit_mdl_800E2ABC, "lit_mdl.c");
        if (s01a_lit_mdl_800E2ADC(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}

void s01a_lit_mdl_800E2D3C(LitMdlWork *work, int ang)
{
    work->field_B4 = ang;
    work->field_B8 = ang / 6;
    work->field_BC = ang / 6;
}

void s01a_lit_mdl_800E2D64(LitMdlWork *work, SVECTOR *unused)
{
    DG_MDL        *mdl;
    int            i, j;
    unsigned char *faceIndexOffsetIter;
    int            curFaceIndexOffset;
    char          *uvOffsetIter;
    SVECTOR       *vertexIndexOffsetIter;
    short         *materialOffsetIter;
    SVECTOR       *normalIndexOffsetIter;
    char          *normalFaceOffsetIter;
    int            uvOff1, uvOff2, uvOff3, uvOff4;
    short          hash;

    mdl = &work->field_E8;
    mdl->vertices = work->field_140_vertexIndexOffsets;
    mdl->normals = work->field_358_normalIndexOffsets;
    mdl->normal_indices = work->field_390_normalFaceOffsets;
    mdl->texcoords = work->field_420_uvOffsets;
    faceIndexOffsetIter = mdl->vertex_indices = work->field_2C8_faceIndexOffsets;
    mdl->materials = work->field_540_materialOffsets;

    for (j = 0; j < 6; j++)
    {
        curFaceIndexOffset = j * 7;
        for (i = 6; i > 0; curFaceIndexOffset++, i--)
        {
            *faceIndexOffsetIter++ = curFaceIndexOffset;
            *faceIndexOffsetIter++ = curFaceIndexOffset + 7;
            *faceIndexOffsetIter++ = curFaceIndexOffset + 8;
            *faceIndexOffsetIter++ = curFaceIndexOffset + 1;
        }
    }

    vertexIndexOffsetIter = work->field_140_vertexIndexOffsets;
    for (i = 49; i > 0; vertexIndexOffsetIter++, i--)
    {
        LSTORE(0, &vertexIndexOffsetIter->vx);
        LSTORE(0, &vertexIndexOffsetIter->vz);
    }

    hash = 0x59FC;
    DG_GetTexture(hash);

    materialOffsetIter = work->field_540_materialOffsets;
    for (i = 36; i > 0; materialOffsetIter++, i--)
    {
        *materialOffsetIter = hash;
    }

    uvOffsetIter = work->field_420_uvOffsets;
    uvOff3 = 0;
    for (j = 0; j < 6; j++)
    {
        uvOff1 = uvOff3;
        uvOff3 = (j + 1) * 255 / 6;
        uvOff3 *= 2;

        if (uvOff3 > 255)
        {
            uvOff3 = 511 - uvOff3;
        }

        uvOff4 = 0;
        for (i = 0; i < 6; i++)
        {
            uvOff2 = uvOff4;
            uvOff4 = (i + 1) * 255 / 6;
            uvOff4 *= 2;

            if (uvOff4 > 255)
            {
                uvOff4 = 511 - uvOff4;
            }

            uvOffsetIter[0] = uvOff1;
            uvOffsetIter[1] = uvOff2;
            uvOffsetIter[2] = uvOff3;
            uvOffsetIter[3] = uvOff2;
            uvOffsetIter[4] = uvOff3;
            uvOffsetIter[5] = uvOff4;
            uvOffsetIter[6] = uvOff1;
            uvOffsetIter[7] = uvOff4;
            uvOffsetIter += 8;
        }
    }

    normalFaceOffsetIter = work->field_390_normalFaceOffsets;
    for (j = 0; j < 6; j++)
    {
        for (i = 6; i > 0; i--)
        {
            *normalFaceOffsetIter++ = 0;
            *normalFaceOffsetIter++ = 0;
            *normalFaceOffsetIter++ = 0;
            *normalFaceOffsetIter++ = 0;
        }
    }

    normalIndexOffsetIter = work->field_358_normalIndexOffsets;
    for (i = 6; i > 0; normalIndexOffsetIter++, i--)
    {
        normalIndexOffsetIter->vx = 0;
        normalIndexOffsetIter->vy = 0;
    }

    work->field_48_light.m[0][0] = 0;
    work->field_48_light.m[0][1] = 0;
    work->field_48_light.m[0][2] = 0;

    work->field_68 = 0;
    work->field_6E = 0;
    work->field_74 = 0;

    work->field_48_light.t[0] = 56;
    work->field_48_light.t[1] = 71;
    work->field_48_light.t[2] = 47;
}
