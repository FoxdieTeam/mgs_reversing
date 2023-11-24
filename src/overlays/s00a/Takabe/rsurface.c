#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/control.h"

typedef struct RSurfaceElem
{
    short    field_0;
    short    field_2;
    CONTROL *field_4;
    SVECTOR  field_8;
} RSurfaceElem;

typedef struct RSurfaceWork
{
    GV_ACT       actor;
    int          field_20;
    int          field_24;
    RSurfaceElem field_30[4];
    SVECTOR      field_68;
    SVECTOR      field_70;
    SVECTOR      field_78;
    short        field_80;
    short        field_82;
    short        field_84;
    short        field_86;
} RSurfaceWork;

extern SVECTOR  DG_ZeroVector_800AB39C;
extern int      GM_CurrentMap_800AB9B0;
extern MATRIX   DG_ZeroMatrix_8009D430;
extern CONTROL *GM_WhereList_800B56D0[96];
extern int      gControlCount_800AB9B4;

void *NewRipple_800D7F30(MATRIX *, int);
void  s00a_rsurface_800D82E0(RSurfaceWork *work);

void RippleSurfaceAct_800D7FC4(RSurfaceWork *work)
{
    MATRIX        mat;
    int           i;
    RSurfaceElem *elem;
    SVECTOR      *field_4;

    GM_CurrentMap_800AB9B0 = work->field_20;

    s00a_rsurface_800D82E0(work);

    elem = work->field_30;
    for (i = 0; i < work->field_80; i++)
    {
        field_4 = &elem->field_4->field_0_mov;

        if (elem->field_2 == 0)
        {
            mat = DG_ZeroMatrix_8009D430;
            mat.t[0] = field_4->vx;
            mat.t[1] = work->field_84;
            mat.t[2] = field_4->vz;

            NewRipple_800D7F30(&mat, work->field_86);

            elem->field_2 = 30;
        }
        else
        {
            if (elem->field_2 >= 9 &&
                (elem->field_8.vx != field_4->vx || elem->field_8.vy != field_4->vy || elem->field_8.vz != field_4->vz))
            {
                work->field_82 = 8;
            }

            elem->field_2--;
        }

        elem->field_8 = *field_4;
        elem++;
    }
}

void RippleSurfaceDie_800D8140(RSurfaceWork *work)
{
}

int RippleSurfaceGetResources_800D8148(RSurfaceWork *work, int name, int where)
{
    GM_CurrentMap_800AB9B0 = where;
    if (GCL_GetOption_80020968('p'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->field_68);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->field_70);
    }
    work->field_86 = 0x1000;
    work->field_84 = (work->field_68.vy + work->field_70.vy) / 2;
    if (GCL_GetOption_80020968('h'))
    {
        work->field_84 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    if (GCL_GetOption_80020968('s'))
    {
        work->field_86 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    work->field_82 = 0;
    work->field_78 = DG_ZeroVector_800AB39C;
    return 0;
}

GV_ACT *NewRippleSurface_800D8244(int name, int where, int argc, char **argv)
{
    RSurfaceWork *work;

    work = (RSurfaceWork *)GV_NewActor_800150E4(5, sizeof(RSurfaceWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)RippleSurfaceAct_800D7FC4,
                                  (TActorFunction)RippleSurfaceDie_800D8140, "rsurface.c");
        if (RippleSurfaceGetResources_800D8148(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        work->field_20 = where;
        work->field_24 = name;
    }
    return &work->actor;
}

static inline int s00a_rsurface_800D82E0_helper(RSurfaceWork *work, CONTROL *ctrl)
{
    int height;
    height = ctrl->field_32_height;

    if (ctrl->field_0_mov.vx < work->field_68.vx && work->field_70.vx < ctrl->field_0_mov.vx &&
        ctrl->field_0_mov.vy < work->field_68.vy && work->field_70.vy < ctrl->field_0_mov.vy &&
        ctrl->field_0_mov.vz < work->field_68.vz && work->field_70.vz < ctrl->field_0_mov.vz)
    {
        return ctrl->field_0_mov.vy - height < work->field_84 + 100;
    }

    return 0;
}

void s00a_rsurface_800D82E0(RSurfaceWork *work)
{
    CONTROL     **wherelistIter;
    CONTROL      *ctrl;
    RSurfaceElem *elems;
    RSurfaceElem *elemsIter2;
    RSurfaceElem *elemIter;
    int           i, j;

    elems = work->field_30;

    for (i = 0, elemIter = elems; i < work->field_80; i++)
    {
        if (!s00a_rsurface_800D82E0_helper(work, elems[i].field_4))
        {
            work->field_80--;
            elems[i] = elemIter[work->field_80];
            i -= 1;
        }
    }

    if (work->field_80 == 4)
    {
        return;
    }

    wherelistIter = GM_WhereList_800B56D0;
    i = gControlCount_800AB9B4;
    elemIter = &work->field_30[work->field_80];

    for (; i > 0; i--, wherelistIter++)
    {
        ctrl = *wherelistIter;

        if (ctrl->field_55_skip_flag & 2)
        {
            continue;
        }
        if (!s00a_rsurface_800D82E0_helper(work, ctrl))
        {
            continue;
        }

        for (elemsIter2 = work->field_30, j = 0; j < work->field_80; elemsIter2++, j++)
        {
            if (elemsIter2->field_4 == *wherelistIter)
            {
                goto skip_iter;
            }
        }

        elemIter->field_4 = *wherelistIter;
        elemIter->field_8 = (*wherelistIter)->field_0_mov;
        elemIter->field_0 = (*wherelistIter)->field_30_scriptData;
        elemIter->field_2 = 0;

        work->field_80++;
        elemIter += 1;

        if (work->field_80 == 4)
        {
            return;
        }

    skip_iter:
    }
}
