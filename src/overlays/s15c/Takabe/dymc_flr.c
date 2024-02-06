#include "libgcl/libgcl.h"
#include "libgv/libgv.h"

typedef struct DymcFloorWork
{
    GV_ACT actor;
    int name;
    int where;
    HZD_HDL *hdl;
    HZD_FLR flr;
} DymcFloorWork;

unsigned short dymc_flr_msgs_800C3630[2] = {0xD182, 0x006B};

extern int GM_CurrentMap_800AB9B0;

int THING_Msg_CheckMessage(unsigned short name, int hash_count, unsigned short *hashes);
int THING_Gcl_GetInt(char param);

void s15c_dymc_flr_800E18BC(HZD_FLR *flr, SVECTOR *svec)
{
    VECTOR vec1, vec2;

    HZD_VEC *hzdvecIter;
    SVECTOR *vecIter;

    int xmin, ymin, zmin;
    int xmax, ymax, zmax;

    int i;

    zmax = -32000;
    ymax = -32000;
    xmax = -32000;

    zmin = 32000;
    ymin = 32000;
    xmin = 32000;

    vecIter = svec;
    hzdvecIter = &flr->p1;
    for (i = 4; i > 0; vecIter++, hzdvecIter++, i--)
    {
        hzdvecIter->x = vecIter->vx;
        hzdvecIter->y = vecIter->vy;
        hzdvecIter->z = vecIter->vz;

        if (xmax < vecIter->vx)
        {
            xmax = vecIter->vx;
        }
        if (vecIter->vx < xmin)
        {
            xmin = vecIter->vx;
        }

        if (ymax < vecIter->vy)
        {
            ymax = vecIter->vy;
        }
        if (vecIter->vy < ymin)
        {
            ymin = vecIter->vy;
        }

        if (zmax < vecIter->vz)
        {
            zmax = vecIter->vz;
        }
        if (vecIter->vz < zmin)
        {
            zmin = vecIter->vz;
        }
    }

    flr->b1.x = xmin;
    flr->b1.y = ymin;
    flr->b1.z = zmin;
    flr->b2.x = xmax;
    flr->b2.y = ymax;
    flr->b2.z = zmax;

    vec1.vx = (svec[1].vx - svec[0].vx) / 4;
    vec1.vy = (svec[1].vy - svec[0].vy) / 4;
    vec1.vz = (svec[1].vz - svec[0].vz) / 4;

    vec2.vx = (svec[2].vx - svec[1].vx) / 4;
    vec2.vy = (svec[2].vy - svec[1].vy) / 4;
    vec2.vz = (svec[2].vz - svec[1].vz) / 4;

    VectorNormal(&vec1, &vec1);
    VectorNormal(&vec2, &vec2);
    OuterProduct12(&vec1, &vec2, &vec1);
    flr->p1.h = vec1.vx >> 4;
    flr->p3.h = vec1.vy >> 4;
    flr->p2.h = vec1.vz >> 4;
}

void s15c_dymc_flr_800E1B00(DymcFloorWork *work)
{
    GM_CurrentMap_800AB9B0 = work->name;
    if (THING_Msg_CheckMessage(work->where, 2, dymc_flr_msgs_800C3630) == 1)
    {
        GV_DestroyActor_800151C8(&work->actor);
    }
}

void s15c_dymc_flr_800E1B54(DymcFloorWork *work)
{
    HZD_DequeueDynamicFloor_8006FFE8(work->hdl, &work->flr);
}


int s15c_dymc_flr_800E1B7C(DymcFloorWork *work, int name, int where)
{
    SVECTOR svecs[4];
    int h;

    GM_CurrentMap_800AB9B0 = where;
    work->name = where;
    work->where = name;

    if (GCL_GetOption_80020968('p'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &svecs[0]);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &svecs[1]);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &svecs[2]);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &svecs[3]);
    }
    h = THING_Gcl_GetInt('s');

    s15c_dymc_flr_800E18BC(&work->flr, svecs);
    work->hdl = Map_FromId_800314C0(where)->field_8_hzd;
    HZD_QueueDynamicFloor_8006FF9C(work->hdl, &work->flr);
    work->flr.b1.h |= h << 8;
    return 0;
}

GV_ACT *s15c_dymc_flr_800E1C70(int name, int where, int argc, char **argv)
{
    DymcFloorWork *work;

    work = (DymcFloorWork *)GV_NewActor_800150E4(5, sizeof(DymcFloorWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s15c_dymc_flr_800E1B00, (TActorFunction)s15c_dymc_flr_800E1B54, "dymc_flr.c");
        if (s15c_dymc_flr_800E1B7C(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}

