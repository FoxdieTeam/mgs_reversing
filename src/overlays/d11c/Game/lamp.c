#include "lamp.h"

#include <stdio.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "strcode.h"
#include "lamp.h"

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct LampWork
{
    GV_ACT         actor;
    DG_PRIM       *field_20_prim;
    short          field_24;
    char           field_26;
    char           field_27;
    unsigned short field_28_name;
    short          loops;
    int            field_2C_rgb;
    int            field_30;
    unsigned char *field_34_gcl_nextStrPtr;
    unsigned char *field_38;
    unsigned char *field_3C;
    SVECTOR        field_40_children[0];
} LampWork;

extern unsigned char *GCL_NextStrPtr_800AB9A0;
extern int            GM_CurrentMap;

void d11c_800C326C(LampWork *work, int textureId)
{
    DG_PRIM  *prim;
    DG_TEX   *tex;
    POLY_FT4 *polyIter;
    int       offx, offy, width, height;
    int       i, j, k;

    prim = work->field_20_prim;
    if (textureId)
    {
        tex = DG_GetTexture(textureId);
        for (i = 0; i < 2; i++)
        {
            polyIter = &prim->packs[i]->poly_ft4;
            for (j = 0; j < work->field_27; j++)
            {
                for (k = 0; k < work->field_26; k++, polyIter++)
                {
                    setlen(polyIter, 9); // a part of setPolyFT4 macro
                    LSTORE(work->field_2C_rgb, &polyIter->r0);

                    width = tex->w + 1;
                    offx = tex->off_x;

                    polyIter->u0 = polyIter->u2 = offx + width * k / work->field_26;
                    polyIter->u1 = polyIter->u3 = offx + width * (k + 1) / work->field_26 - 1;

                    height = tex->h + 1;
                    offy = tex->off_y;

                    polyIter->v0 = polyIter->v1 = offy + height * j / work->field_27;
                    polyIter->v2 = polyIter->v3 = offy + height * (j + 1) / work->field_27 - 1;

                    polyIter->tpage = tex->tpage;
                    polyIter->clut = tex->clut;
                }
            }
        }
        DG_VisiblePrim(prim);
    }
    else
    {
        DG_InvisiblePrim(prim);
    }
}

unsigned char *d11c_800C34C4(LampWork *work, int arg1)
{
    unsigned char *strptr;

    strptr = work->field_34_gcl_nextStrPtr;
    while (strptr[0] == 'P')
    {
        if (strptr[1] == arg1)
        {
            return strptr + 3;
        }
        strptr = strptr + strptr[2] + 2;
    }
    return NULL;
}

void d11c_800C3518(LampWork *work, int arg1)
{
    unsigned char *temp_v0;

    temp_v0 = d11c_800C34C4(work, arg1);
    work->field_38 = temp_v0;
    work->field_3C = temp_v0;
    work->field_30 = 0;
    work->loops = -1;
}

void d11c_800C3550(LampWork *work)
{
    GV_MSG *message;
    int     message_result;

    message_result = GV_ReceiveMessage(work->field_28_name, &message);
    for (; message_result > 0; message_result--, message++)
    {
        switch (message->message[0])
        {
        case HASH_ON:
            d11c_800C326C(work, message->message[1]);
            work->field_3C = 0;
            break;

        case HASH_OFF:
            d11c_800C326C(work, 0);
            work->field_3C = 0;
            break;

        case 0xBCD2:
            d11c_800C3518(work, message->message[1]);
            break;
        }
    }
}

void d11c_800C361C(LampWork *work)
{
    int param1, param2, loops;
    int type;

    if (work->field_3C == NULL)
    {
        work->field_30 = -1;
        return;
    }
    GCL_SetArgTop(work->field_3C);

    while (GCL_GetParamResult())
    {
        type = GCL_StrToInt(GCL_GetParamResult());

        switch (type)
        {
        case 0xDD19:
            param1 = GCL_StrToInt(GCL_GetParamResult());
            param2 = GCL_StrToInt(GCL_GetParamResult());
            d11c_800C326C(work, param1);
            work->field_30 = param2;
            work->field_3C = GCL_GetParamResult();
            return;

        case HASH_LOOP:
            if (GCL_GetParamResult())
            {
                loops = GCL_StrToInt(GCL_GetParamResult());
            }
            else
            {
                loops = 0;
            }

            if (work->loops >= 0)
            {
                if (loops > 0)
                {
                    if (--work->loops < 2)
                    {
                        work->field_30 = -1;
                        work->field_3C = 0;
                        return;
                    }
                }
            }
            else
            {
                work->loops = loops;
            }

            GCL_SetArgTop(work->field_38);
            break;

        case 0x11F8:
            d11c_800C3518(work, GCL_StrToInt(GCL_GetParamResult()));
            GCL_SetArgTop(work->field_3C);

        default:
            printf("TEX:PARSE ERROR\n");
            break;
        }
    }
}

void d11c_800C37A4(LampWork *work)
{
    d11c_800C3550(work);
    if (work->field_30 >= 0)
    {
        if (work->field_30 > 0)
        {
            work->field_30--;
            return;
        }
        d11c_800C361C(work);
    }
}

void d11c_800C37F0(LampWork *work)
{
    DG_PRIM *prim;

    prim = work->field_20_prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

void d11c_800C382C(SVECTOR *vecs, int arg1, int arg2, int len2, int len1)
{
    SVECTOR *vecsIter;
    int      i, j;
    int      quot1, quot2;
    int      vx, vy;

    vecsIter = vecs;
    vy = arg2 / 2;
    quot1 = arg1 / len2;
    quot2 = arg2 / len1;

    for (i = 0; i < len1; i++)
    {
        vx = -arg1 / 2;

        for (j = 0; j < len2; vecsIter += 4, j++)
        {
            int vx2 = vx + quot1;
            vecsIter[0].vx = vx;
            vecsIter[2].vx = vx;
            vx = vx2;
            vecsIter[1].vx = vx2;
            vecsIter[3].vx = vx2;

            vecsIter[0].vy = vy;
            vecsIter[1].vy = vy;
            vecsIter[2].vy = vy - quot2;
            vecsIter[3].vy = vy - quot2;
        }

        vy -= quot2;
    }
}

int LampGetResources_800C3914(LampWork *work, int map, int name, int a3, int a4)
{
    MATRIX   mat;
    SVECTOR  svec1;
    SVECTOR  svec2;
    int      param1;
    DG_PRIM *prim;
    SVECTOR *field_40_children;
    int      param2;
    int      prim_count;
    int      param3;
    int      primType;
    int      param4;
    int      param5;

    GM_CurrentMap = map;
    GCL_StrToSV(GCL_GetParamResult(), &svec1);
    GCL_StrToSV(GCL_GetParamResult(), &svec2);
    param1 = GCL_GetNextParamValue();
    param2 = GCL_GetNextParamValue();
    param3 = GCL_GetNextParamValue();
    work->field_28_name = name;
    work->field_38 = 0;
    work->field_3C = 0;
    work->field_30 = -1;
    work->field_34_gcl_nextStrPtr = GCL_NextStrPtr_800AB9A0;

    if (GCL_GetOption('I'))
    {
        param4 = GCL_GetNextParamValue();
        primType = 0x1012;
    }
    else
    {
        param4 = 0;
        primType = 0x1012;
    }

    if (GCL_GetOption('T'))
    {
        primType = 0x12;
    }

    if (GCL_GetOption('R'))
    {
        param5 = GCL_GetNextParamValue();
    }
    else
    {
        param5 = 0x01808080;
    }

    work->field_2C_rgb = param5 | 0x2C000000;
    if (GCL_GetOption('S'))
    {
        work->field_2C_rgb |= 0x02000000;
    }

    prim_count = a3 * a4;
    field_40_children = work->field_40_children;

    prim = DG_GetPrim(primType, prim_count, 0, field_40_children, NULL);

    work->field_20_prim = prim;
    work->field_24 = prim_count;

    if (prim == NULL)
    {
        return 0;
    }

    RotMatrix(&svec2, &mat);

    mat.t[0] = svec1.vx;
    mat.t[1] = svec1.vy;
    mat.t[2] = svec1.vz;

    DG_SetPos(&mat);
    DG_PutPrim(&prim->world);

    prim->field_2E_k500 = param3;
    work->field_26 = a3;
    work->field_27 = a4;

    d11c_800C326C(work, param4);
    d11c_800C382C(field_40_children, param1, param2, a3, a4);

    return 1;
}

GV_ACT *NewLamp_800C3B34(int name, int where, int argc, char **argv)
{
    LampWork      *work;
    unsigned char *nextStrPtr;
    int            param1, param2;

    nextStrPtr = GCL_NextStrPtr_800AB9A0;

    if (GCL_GetOption('D'))
    {
        param1 = GCL_GetNextParamValue();
        param2 = GCL_GetNextParamValue();
    }
    else
    {
        param2 = 1;
        param1 = 1;
    }

    GCL_NextStrPtr_800AB9A0 = nextStrPtr;

    work = (LampWork *)GV_NewActor(EXEC_LEVEL, ((param1 * param2) * sizeof(SVECTOR) * 4) + sizeof(LampWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)d11c_800C37A4, (GV_ACTFUNC)d11c_800C37F0, "lamp.c");
        if (LampGetResources_800C3914(work, where, name, param1, param2) == 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
