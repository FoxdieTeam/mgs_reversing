#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "linkvar.h"
#include "strcode.h"
#include "anime/animconv/anime.h"
#include "bullet/blast.h"

#include "demo.h"
#include "kojo/m1e1.h"

#define BODY_FLAG ( DG_FLAG_SHADE | DG_FLAG_TRANS | DG_FLAG_TEXT )

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern BLAST_DATA       blast_data_8009F4B8[8];
extern GM_CAMERA        GM_Camera;

/*---------------------------------------------------------------------------*/

static int MakeChara(DemoWork *work, DMO_DATA_0x36 *data, ACTNODE *node);
static void RemoveType(DemoWork *work, int type);
static int demothrd_8007CDF8(DemoWork *work, DMO_DAT *data, ACTNODE *node);
static int demothrd_1_FrameRunDemo_helper4_8007CF14(DemoWork *work, DMO_DAT *data);
static int demothrd_8007CFE8(DemoWork *work, DMO_ADJ *adjust);
static void demothrd_m1e1_8007D404(DemoWork *work, DMO_ADJ *adjust, DMO_MDL *model_file, DEMO_MODEL *model);
static void demothrd_hind_8007D9C8(DemoWork *work, DMO_ADJ *adjust, DMO_MDL *model_file, DEMO_MODEL *model);

void AN_CaterpillerSmoke(SVECTOR *pos);
void demothrd_2_8007DA94(SVECTOR *pPosition, SVECTOR *pRotation);
void sub_8007DC24(SVECTOR *pPosition);
void sub_8007DD80(short param_1, SVECTOR *pPos);
void sub_8007DF10(SVECTOR *pRotation, SVECTOR *pTranslation);
void sub_8007E0AC(int y, SVECTOR *pPosition);

void InitChain(ACTNODE *root);
void InsertChain(ACTNODE *root, ACTNODE *node);
void RemoveChain(ACTNODE *root, ACTNODE *node);

void DemoScreenChanl(DG_CHANL *chanl, int idx);

/*---------------------------------------------------------------------------*/

int CreateDemo(DemoWork *work, DMO_DEF *header)
{
    DMO_MAP    *maps;
    DMO_MDL    *models;
    DMO_MAP    *map;
    int         i;
    DEMO_MODEL *model;
    DMO_MDL    *model_file;
    MATRIX     *light;

    work->old_screen = DG_SetChanlSystemUnits(DG_SCREEN_CHANL, DemoScreenChanl);
    work->old_game_status = GM_GameStatus;
    work->old_camera = GM_Camera;
    work->old_item = GM_CurrentItemId;
    work->old_weapon = GM_CurrentWeaponId;

    OFFSET_TO_PTR(header, &header->maps);
    OFFSET_TO_PTR(header, &header->models);

    InitChain(&work->chain);

    work->header = GV_Malloc(sizeof(DMO_DEF));
    if (!work->header)
    {
        return 0;
    }

    *work->header = *header;
    work->header->maps = NULL;
    work->header->models = NULL;    

    maps = GV_Malloc((sizeof(DMO_MAP) * header->n_maps) | 1);
    work->header->maps = maps;
    if (!maps)
    {
        return 0;
    }

    models = GV_Malloc((sizeof(DMO_MDL) * header->n_models) | 1);
    work->header->models = models;
    if (!models)
    {
        return 0;
    }

    memcpy(work->header->maps, header->maps, sizeof(DMO_MAP) * work->header->n_maps);
    memcpy(work->header->models, header->models, sizeof(DMO_MDL) * work->header->n_models);

    map = work->header->maps;
    for (i = 0; i < work->header->n_maps; i++)
    {
        if (!GV_GetCache(map->cache_id))
        {
            printf("Noload model ( Stage )\n");
            return 0;
        }

        map++;
    }

    work->models = GV_Malloc((sizeof(DEMO_MODEL) * work->header->n_models) | 1);
    if (!work->models)
    {
        return 0;
    }

    memset(work->models, 0, sizeof(DEMO_MODEL) * work->header->n_models);

    model_file = work->header->models;
    model = work->models;
    for (i = 0; i < work->header->n_models; i++, model_file++, model++)
    {
        if (!GV_GetCache(model_file->cache_id))
        {
            printf("Noload model ( Scene = No.%d )\n", i + 1);
            return 0;
        }

        if (GM_InitControl(&model->control, model_file->name, work->map) < 0)
        {
            printf("Error init control ( Scene = No.%d )\n", i + 1);
            return 0;
        }

        model->control.step_size = 0;
        model->control.interp = 0;

        if (model_file->flag & 0x1)
        {
            GM_InitObject(&model->object, model_file->filename, BODY_FLAG | DG_FLAG_ONEPIECE | DG_FLAG_PAINT, 0);
            continue;
        }

        if (model_file->filename == GV_StrCode("16d_o4a")
            || model_file->filename == GV_StrCode("16d_o5a")
            || model_file->filename == GV_StrCode("16d_o6a")
            || model_file->filename == GV_StrCode("16d_o7a")
            || model_file->filename == GV_StrCode("16d_o8a")
            || model_file->filename == GV_StrCode("16d_o9a")
            || model_file->filename == GV_StrCode("16d_o10a")
            || model_file->filename == GV_StrCode("16d_o4b")
            || model_file->filename == GV_StrCode("16d_o5b")
            || model_file->filename == GV_StrCode("16d_o6b")
            || model_file->filename == GV_StrCode("16d_o7b")
            || model_file->filename == GV_StrCode("16d_o8b")
            || model_file->filename == GV_StrCode("16d_o9b")
            || model_file->filename == GV_StrCode("16d_o10b")
            || model_file->filename == GV_StrCode("16d_o4c")
            || model_file->filename == GV_StrCode("16d_o5c")
            || model_file->filename == GV_StrCode("16d_o6c")
            || model_file->filename == GV_StrCode("16d_o7c")
            || model_file->filename == GV_StrCode("16d_o8c")
            || model_file->filename == GV_StrCode("16d_o9c")
            || model_file->filename == GV_StrCode("16d_o10c"))
        {
            GM_InitObject(&model->object, model_file->filename, BODY_FLAG & ~DG_FLAG_SHADE, 0);
        }
        else if (model_file->filename == GV_StrCode("02a_r8"))
        {
            model->light[0].t[0] = 100;
            model->light[0].t[1] = 110;
            model->light[0].t[2] = 110;

            GM_InitObject(&model->object, model_file->filename, BODY_FLAG | DG_FLAG_AMBIENT, 0);
        }
        else if (model_file->filename == GV_StrCode("mgrexw")
            || model_file->filename == GV_StrCode("mgrexll")
            || model_file->filename == GV_StrCode("mgrexrl")
            || model_file->filename == GV_StrCode("pit_t")
            || model_file->filename == GV_StrCode("pit_u")
            || model_file->filename == GV_StrCode("pit_liq")
            || model_file->filename == GV_StrCode("radar_f1")
            || model_file->filename == GV_StrCode("radar_f2")
            || model_file->filename == GV_StrCode("radar_f3")
            || model_file->filename == GV_StrCode("l_hatch1")
            || model_file->filename == GV_StrCode("l_hatch2")
            || model_file->filename == GV_StrCode("l_hatch3")
            || model_file->filename == GV_StrCode("l_hatch4")
            || model_file->filename == GV_StrCode("r_hatch1")
            || model_file->filename == GV_StrCode("r_hatch2")
            || model_file->filename == GV_StrCode("r_hatch3")
            || model_file->filename == GV_StrCode("r_hatch4"))
        {
            model->light[0].t[0] = 64;
            model->light[0].t[1] = 64;
            model->light[0].t[2] = 64;

            GM_InitObject(&model->object, model_file->filename, BODY_FLAG | DG_FLAG_AMBIENT, 0);
        }
        else
        {
            GM_InitObject(&model->object, model_file->filename, BODY_FLAG, 0);
        }

        light = model->light;
                
        GM_ConfigObjectJoint(&model->object);
        GM_ConfigObjectLight(&model->object, light);

        DG_InvisibleObjs(model->object.objs);

        if (model_file->filename == GV_StrCode("m1e1") || model_file->filename == GV_StrCode("m1e1demo"))
        {
            model->extra = GV_Malloc(sizeof(DEMO_M1E1));
            if (!model->extra)
            {
                return 0;
            }

            memset(model->extra, 0, sizeof(DEMO_M1E1));

            GM_InitObject(&model->extra->object[0][0], GV_StrCode("m1e1cl1"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&model->extra->object[0][1], GV_StrCode("m1e1cl2"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&model->extra->object[0][2], GV_StrCode("m1e1cl3"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&model->extra->object[1][0], GV_StrCode("m1e1cr1"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&model->extra->object[1][1], GV_StrCode("m1e1cr2"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);
            GM_InitObject(&model->extra->object[1][2], GV_StrCode("m1e1cr3"), BODY_FLAG | DG_FLAG_AMBIENT | DG_FLAG_GBOUND, 0);

            GM_ConfigObjectJoint(&model->extra->object[0][0]);
            GM_ConfigObjectJoint(&model->extra->object[0][1]);
            GM_ConfigObjectJoint(&model->extra->object[0][2]);
            GM_ConfigObjectJoint(&model->extra->object[1][0]);
            GM_ConfigObjectJoint(&model->extra->object[1][1]);
            GM_ConfigObjectJoint(&model->extra->object[1][2]);

            GM_ConfigObjectLight(&model->extra->object[0][0], light);
            GM_ConfigObjectLight(&model->extra->object[0][1], light);
            GM_ConfigObjectLight(&model->extra->object[0][2], light);
            GM_ConfigObjectLight(&model->extra->object[1][0], light);
            GM_ConfigObjectLight(&model->extra->object[1][1], light);
            GM_ConfigObjectLight(&model->extra->object[1][2], light);

            model->extra->field_560 = 83;
        }
        else if (model_file->filename == GV_StrCode("hind") || model_file->filename == GV_StrCode("hinddemo"))
        {
            model->extra = GV_Malloc(sizeof(DEMO_HIND));
            if (!model->extra)
            {
                return 0;
            }

            memset(model->extra, 0, sizeof(DEMO_HIND));
        }
    }

    if (!GV_GetCache(GV_CacheID2("null", 'k')))
    {
        printf("Noload model ( null.kmd )\n");
        return 0;
    }

    if (GM_InitControl(&work->control, 0, work->map) < 0)
    {
        printf("Error init control ( null.kmd )\n");
        return 0;
    }

    work->control.step_size = 0;
    work->control.interp = 0;

    GM_InitObject(&work->object, GV_StrCode("null"), BODY_FLAG, 0);

    GM_ConfigObjectJoint(&work->object);
    GM_ConfigObjectLight(&work->object, work->light);

    DG_InvisibleObjs(work->object.objs);

    GM_GameStatus |= STATE_DEMO;
    return 1;
}

int DestroyDemo(DemoWork *work)
{
    ACTNODE    *node;
    DMO_MDL    *model_file;
    DEMO_MODEL *model;
    int         i;

    if (work->flag & 0x2)
    {
        GM_GameStatus |= STATE_DEMO_VERBOSE;
    }

    for (node = work->chain.next; node != &work->chain; node = work->chain.next)
    {
        if (node->actor1)
        {
            GV_DestroyOtherActor(node->actor1);
        }

        if (node->actor2)
        {
            GV_DestroyOtherActor(node->actor2);
        }

        RemoveChain(&work->chain, node);
        GV_Free(node);
    }

    if (work->models)
    {
        model_file = work->header->models;
        model = work->models;
        for (i = 0; i < work->header->n_models; i++, model_file++, model++)
        {
            GM_FreeObject(&model->object);

            if (model->extra)
            {
                if (model_file->filename == GV_StrCode("m1e1") || model_file->filename == GV_StrCode("m1e1demo"))
                {
                    GM_FreeObject(&model->extra->object[0][0]);
                    GM_FreeObject(&model->extra->object[0][1]);
                    GM_FreeObject(&model->extra->object[0][2]);
                    GM_FreeObject(&model->extra->object[1][0]);
                    GM_FreeObject(&model->extra->object[1][1]);
                    GM_FreeObject(&model->extra->object[1][2]);
                }

                GV_Free(model->extra);
            }
        }

        GM_FreeControl(&model->control);
        GV_Free(work->models);
    }

    GM_FreeObject(&work->object);
    GM_FreeControl(&work->control);

    if (work->header)
    {
        if (work->header->maps)
        {
            GV_Free(work->header->maps);
        }

        if (work->header->models)
        {
            GV_Free(work->header->models);
        }

        GV_Free(work->header);
    }

    GM_GameStatus &= ~STATE_DEMO;
    DG_SetChanlSystemUnits(DG_SCREEN_CHANL, work->old_screen);
    GM_GameStatus = work->old_game_status;
    GM_Camera = work->old_camera;
    GM_CurrentItemId = work->old_item;
    GM_CurrentWeaponId = work->old_weapon;
    return 1;
}

int FrameRunDemo(DemoWork *work, DMO_DAT *data)
{
    SVECTOR   diff;
    SVECTOR   rot;
    VECTOR    trans;
    int       radius;
    ACTNODE  *node;
    DMO_CHA  *chara;
    int       i;
    ACTNODE  *iter;
    DMO_ADJ  *adjust;

    OFFSET_TO_PTR(data, &data->chara);
    OFFSET_TO_PTR(data, &data->adjust);

    work->control.mov.vx = data->eye_x;
    work->control.mov.vy = data->eye_y;
    work->control.mov.vz = data->eye_z;

    diff.vx = (data->center_x - data->eye_x) >> 2;
    diff.vx = (data->center_y - data->eye_y) >> 2;
    diff.vx = (data->center_z - data->eye_z) >> 2;

    radius = SquareRoot0(diff.vx  * diff.vx  + diff.vz * diff.vz);
    work->control.rot.vx = ratan2(diff.vy, radius);
    work->control.rot.vy = ratan2(diff.vx, diff.vz);
    work->control.rot.vz = data->roll;

    GM_ActControl(&work->control);
    GM_ActObject2(&work->object);
    DG_GetLightMatrix(&work->control.mov, work->light);

    work->field_268 = 0;
    work->field_26C = 0;

    for (node = work->chain.next; node != &work->chain; node = node->next)
    {
        node->used = 0;
    }

    chara = data->chara;
    for ( i = 0; i < data->n_charas; i++, chara++ )
    {
        node = work->chain.next;

        if ( node != &work->chain )
        {
            do
            {
                if (node->chara.field_0 == chara->field_0)
                {
                    node->used = 1;
                    break;
                }

                node = node->next;
            }
            while (node != &work->chain);

            if ( node->chara.field_0 == chara->field_0 )
            {
                continue;
            }
        }

        node = GV_Malloc(sizeof(ACTNODE));
        if ( !node )
        {
            return 1;
        }

        memset(node, 0, sizeof(ACTNODE));
        InsertChain(&work->chain, node);
        node->used = 1;

        node->chara = *chara;

        // This function uses offset 0x34 of chara despite it seemingly only being 0x34 bytes in size
        if ( !MakeChara(work, (DMO_DATA_0x36 *)chara, node) )
        {
            return 0;
        }
    }

    for ( iter = work->chain.next; iter != &work->chain; )
    {
        node = iter;
        iter = node->next;

        if ( node->used != 1 && !node->actor1 )
        {
            RemoveChain(&work->chain, node);
            GV_Free(node);
        }
    }

    for ( node = work->chain.next; node != &work->chain; node = node->next )
    {
        if ( !demothrd_8007CDF8(work, data, node) )
        {
            return 0;
        }
    }

    demothrd_1_FrameRunDemo_helper4_8007CF14(work, data);

    adjust = data->adjust;
    for ( i = 0; i < data->n_adjusts; i++, adjust++ )
    {
        if ( !demothrd_8007CFE8(work, adjust) )
        {
            return 0;
        }
    }

    gUnkCameraStruct2_800B7868.eye.vx = data->eye_x;
    gUnkCameraStruct2_800B7868.eye.vy = data->eye_y;
    gUnkCameraStruct2_800B7868.eye.vz = data->eye_z;

    gUnkCameraStruct2_800B7868.center.vx = data->center_x;
    gUnkCameraStruct2_800B7868.center.vy = data->center_y;
    gUnkCameraStruct2_800B7868.center.vz = data->center_z;

    DG_Chanl(0)->clip_distance = data->clip_dist;

    diff.vx = data->center_x - data->eye_x;
    diff.vy = data->center_y - data->eye_y;
    diff.vz = data->center_z - data->eye_z;

    radius = SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz);
    rot.vx = -ratan2(diff.vy, radius);
    rot.vy = ratan2(diff.vx, diff.vz);
    rot.vz = 2048;

    diff.vx = data->eye_x;
    diff.vy = data->eye_y;
    diff.vz = data->eye_z;

    DG_SetPos2(&diff, &rot);
    memset(&rot, 0, 8);

    rot.vz = data->roll;
    DG_RotatePos(&rot);
    ReadRotMatrix(&DG_Chanl(0)->eye);

    DG_TransposeMatrix(&DG_Chanl(0)->eye, &DG_Chanl(0)->eye_inv);

    trans.vx = -DG_Chanl(0)->eye.t[0];
    trans.vy = -DG_Chanl(0)->eye.t[1];
    trans.vz = -DG_Chanl(0)->eye.t[2];

    ApplyMatrixLV(&DG_Chanl(0)->eye_inv, &trans, (VECTOR *)DG_Chanl(0)->eye_inv.t);
    return 1;
}

static int MakeChara(DemoWork *work, DMO_DATA_0x36 *data, ACTNODE *node)
{
    // TODO: Some funcptr calls are first cast to VoidMakeChara. This is a hack
    // to prevent those cases from being merged (GCC "cross jump" optimization).
    typedef void (*VoidMakeChara)();

    int                        levels[2];
    GV_MSG                     msg;
    SVECTOR                    svec1, svec2, svec3, svec4;
    MATRIX                     mat1, mat2;
    ACTNODE *pIter;

    void *(*funcptr)();

    DMO_MDL  *pDmoModel;
    DEMO_MODEL *pModel;
    int              hzdret;
    int              i;

    svec1.vx = data->field_E_vec2.vx;
    svec1.vy = data->field_E_vec2.vy;
    svec1.vz = data->field_E_vec2.vz;
    svec2.vx = data->field_8_vec1.vx;
    svec2.vy = data->field_8_vec1.vy;
    svec2.vz = data->field_8_vec1.vz;

    DG_SetPos2(&svec1, &DG_ZeroVector);
    ReadRotMatrix(&mat1);
    DG_SetPos2(&svec1, &svec2);
    ReadRotMatrix(&mat2);

    switch (data->field_4_type)
    {
    case 0x1:
        funcptr = GM_GetCharaID(0x1);
        if (funcptr != NULL)
        {
            funcptr(&mat1, &blast_data_8009F4B8[3]);
        }
        break;

    case 0x2:
        funcptr = GM_GetCharaID(0x2);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x3:
    case 0x4:
        RemoveType(work, 4);

        switch (data->field_4_type)
        {
        case 0x3:
            funcptr = GM_GetCharaID(3);
            if (funcptr != NULL)
            {
                if (data->data.variant_0x3.field_18 == 0)
                {
                    funcptr(1, data->data.variant_0x3.field_14);
                }
                else
                {
                    funcptr(3, data->data.variant_0x3.field_14);
                }
            }
            break;

        case 0x4:
            funcptr = GM_GetCharaID(4);
            if (funcptr != NULL)
            {
                if (data->data.variant_0x4.field_18 == 0)
                {
                    node->actor1 = funcptr(0, data->data.variant_0x4.field_14);
                }
                else
                {
                    node->actor1 = funcptr(2, data->data.variant_0x4.field_14);
                }
            }
            break;
        }
        break;

    case 0x5:
        funcptr = GM_GetCharaID(5);
        if (funcptr != NULL)
        {
            funcptr(data->data.variant_0x5.field_18, data->data.variant_0x5.field_1A, 0, data->data.variant_0x5.field_14,
                    data->data.variant_0x5.field_1C);
        }
        break;

    case 0x6:
        funcptr = GM_GetCharaID(6);
        if (funcptr != NULL)
        {
            if (data->data.variant_0x6.field_14 == 0)
            {
                funcptr(&mat1, 2);
            }
            else
            {
                funcptr(&mat1, 0);
            }
        }
        break;

    case 0x7:
        funcptr = GM_GetCharaID(7);
        if (funcptr != NULL)
        {
            if (data->data.variant_0x7.field_14 == 0)
            {
                funcptr(&mat1, 3);
            }
            else
            {
                funcptr(&mat1, 1);
            }
        }
        break;

    case 0x8:
        funcptr = GM_GetCharaID(0x8);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x9:
        if (data->data.variant_0x9.field_14 != 4)
        {
            funcptr = GM_GetCharaID(9);
            if (funcptr != NULL)
            {
                funcptr(&mat2, data->data.variant_0x9.field_14);
            }
        }
        else
        {
            funcptr = GM_GetCharaID(0xA);
            if (funcptr != NULL)
            {
                funcptr(&mat2, 0xFF);
            }
        }
        break;
    case 0xA:
        funcptr = GM_GetCharaID(0xB);
        if (funcptr != NULL)
        {
            funcptr(data->data.variant_0xA.field_14, &mat2, data->data.variant_0xA.field_18,
                    data->data.variant_0xA.field_1A, data->data.variant_0xA.field_1C, data->data.variant_0xA.field_1E,
                    data->data.variant_0xA.field_20, data->data.variant_0xA.field_22, data->data.variant_0xA.field_24);
        }
        break;
    case 0xB:
        funcptr = GM_GetCharaID(0xC);
        if (funcptr != NULL)
        {
            funcptr(&mat2);
        }
        break;

    case 0xC:
        funcptr = GM_GetCharaID(0xD);
        if (funcptr != NULL)
        {
            if (data->data.variant_0xC.field_14 >= 4 && data->data.variant_0xC.field_14 <= 7)
            {
                funcptr(&svec1, data->data.variant_0xC.field_14, data->data.variant_0xC.field_18,
                        data->data.variant_0xC.field_1C);
            }
            else
            {
                node->actor1 = funcptr(&svec1, data->data.variant_0xC.field_14, data->data.variant_0xC.field_18,
                                                 data->data.variant_0xC.field_1C);
            }
        }
        break;

    case 0xD:
        funcptr = GM_GetCharaID(0xe);
        if (funcptr != NULL)
        {
            funcptr(&mat2);
        }
        break;

    case 0xE:
        pModel = work->models;
        pDmoModel = work->header->models;

        for (i = 0; i < work->header->n_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->type == data->data.variant_0xE.field_14)
            {
                break;
            }
        }

        if (i >= work->header->n_models)
        {
            break;
        }

        for (pIter = work->chain.next; pIter != &work->chain; pIter = pIter->next)
        {
            if (pIter->chara.field_4_type == 0xE && pIter->chara.field_14_type == data->data.variant_0xE.field_14)
            {
                if (pIter->actor1)
                {
                    GV_DestroyOtherActor(pIter->actor1);
                    pIter->actor1 = NULL;
                }
            }
        }

        if (data->data.variant_0xE.field_20 != 1)
        {
            funcptr = GM_GetCharaID(0xF);
            if (funcptr != NULL)
            {
                node->actor1 =
                    funcptr(&pModel->object, data->data.variant_0xE.field_18, &node->field_48, &node->field_4C,
                            data->data.variant_0xE.field_22 & 0xFF, data->data.variant_0xE.field_24 & 0xFF,
                            data->data.variant_0xE.field_26 & 0xFF);
            }
        }
        break;

    case 0xF:
        svec1.vy += 0x64;
        hzdret = HZD_LevelTestHazard(work->control.map->hzd, &svec1, 1);

        do {} while (0);
        HZD_LevelMinMaxHeights(levels);

        if (hzdret & 1)
        {
            svec1.vy = levels[0];
        }

        else if (hzdret & 2)
        {
            svec1.vy = levels[1];
        }
        else
        {
            svec1.vy = data->field_E_vec2.vy;
        }

        funcptr = GM_GetCharaID(0x10);
        if (funcptr != NULL)
        {
            node->actor1 = funcptr(&mat2, data->data.variant_0xF.field_14, svec1.vy);
        }
        break;

    case 0x10:
        memset(&msg, 0, sizeof(msg));
        msg.address = data->data.variant_0x10.address;
        msg.message[0] = data->data.variant_0x10.message[0];
        msg.message[1] = data->data.variant_0x10.message[1];
        msg.message[2] = data->data.variant_0x10.message[2];
        msg.message[3] = data->data.variant_0x10.message[3];
        msg.message[4] = data->data.variant_0x10.message[4];
        msg.message[5] = data->data.variant_0x10.message[5];
        msg.message[6] = data->data.variant_0x10.message[6];
        msg.message_len = 7;
        GV_SendMessage(&msg);
        break;

    case 0x11:
        funcptr = GM_GetCharaID(0x11);
        if (funcptr != NULL)
        {
            ((VoidMakeChara)funcptr)(&mat2);
        }
        break;

    case 0x12:
        if (data->data.variant_0x12.field_14 == 0)
        {
            funcptr = GM_GetCharaID(0x12);
            if (funcptr != NULL)
            {
                funcptr(&svec1, data->data.variant_0x12.field_20, data->data.variant_0x12.field_24, &work->field_26C,
                        data->data.variant_0x12.field_26, data->data.variant_0x12.field_28,
                        data->data.variant_0x12.field_2A);
            }
        }
        else if (data->data.variant_0x12.field_14 == 1)
        {
            svec3.vx = data->data.variant_0x12.field_16;
            svec3.vy = data->data.variant_0x12.field_18;
            svec3.vz = data->data.variant_0x12.field_1A;

            funcptr = GM_GetCharaID(0x13);
            if (funcptr != NULL)
            {
                funcptr(&svec1, &svec3, data->data.variant_0x12.field_1C, &work->field_26C,
                        data->data.variant_0x12.field_26, data->data.variant_0x12.field_28,
                        data->data.variant_0x12.field_2A);
            }
        }
        else
        {
            work->field_26C = 1;
        }
        break;

    case 0x13:
    case 0x14:
    case 0x15:
    case 0x1E:
        pIter = work->chain.next;
        while (pIter != &work->chain)
        {
            if (pIter->chara.field_4_type == 0x13 || pIter->chara.field_4_type == 0x14 || pIter->chara.field_4_type == 0x15 || pIter->chara.field_4_type == 0x1E)
            {
                if (pIter->actor1 != NULL)
                {
                    GV_DestroyOtherActor(pIter->actor1);
                    if (pIter->actor2 != NULL)
                    {
                        GV_DestroyOtherActor(pIter->actor2);
                    }
                    pIter->actor1 = NULL;
                    pIter->actor2 = NULL;
                }
            }
            pIter = pIter->next;
        }

        switch (data->field_4_type)
        {
        case 0x13:
            if (data->data.variant_0x13.field_14 != 1)
            {
                funcptr = GM_GetCharaID(0x14);
                if (funcptr != NULL)
                {
                    node->actor1 = funcptr(&work->control, &work->object, 0);
                }
            }
            break;

        case 0x14:
            if (data->data.variant_0x14.field_14 != 1)
            {
                funcptr = GM_GetCharaID(0x15);
                if (funcptr != NULL)
                {
                    node->actor1 = funcptr(&work->control, &work->object, 0);
                    if (data->data.variant_0x14.field_16 != 0)
                    {
                        funcptr = GM_GetCharaID(0x16);
                        if (funcptr != NULL)
                        {
                            node->actor2 = funcptr(5);
                        }
                    }
                }
            }
            break;

        case 0x15:
            if (data->data.variant_0x15.field_14 != 1)
            {
                funcptr = GM_GetCharaID(0x17);
                if (funcptr != NULL)
                {
                    node->actor1 = funcptr(&work->control, &work->object, 0);
                    if (data->data.variant_0x15.field_16 != 0)
                    {
                        funcptr = GM_GetCharaID(0x18);
                        if (funcptr != NULL)
                        {
                            node->actor2 = funcptr(6);
                        }
                    }
                }
            }
            break;

        case 0x1E:
            if (data->data.variant_0x1E.field_14 != 1)
            {
                funcptr = GM_GetCharaID(0x22);
                if (funcptr != NULL)
                {
                    node->actor1 = funcptr();
                }
            }
            break;
        }
        break;

    case 0x16:
        funcptr = GM_GetCharaID(0x19);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x17:
        pModel = work->models;
        pDmoModel = work->header->models;

        for (i = 0; i < work->header->n_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->type == data->data.variant_0x17.field_18)
            {
                break;
            }
        }

        if (i >= work->header->n_models)
        {
            break;
        }

        pIter = work->chain.next;
        while (pIter != &work->chain)
        {
            if ((pIter->chara.field_4_type == 0x17) && (pIter->chara.field_18_xy == data->data.variant_0x17.field_18))
            {
                if (pIter->actor1 != NULL)
                {
                    GV_DestroyOtherActor(pIter->actor1);
                    pIter->actor1 = NULL;
                }
            }
            pIter = pIter->next;
        }

        if (data->data.variant_0x17.field_14 != 1 && data->field_4_type == 0x17)
        {
            if (data->data.variant_0x17.field_1C == 0)
            {
                funcptr = GM_GetCharaID(0x1A);
                if (funcptr != NULL)
                {
                    node->actor1 = funcptr(&work->control, &pModel->object, 0);
                }
            }
            else
            {
                funcptr = GM_GetCharaID(0x1B);
                if (funcptr != NULL)
                {
                    node->actor1 = funcptr(&work->control, &pModel->object, 0);
                }
            }
        }
        break;
    case 0x18:
        pModel = work->models;
        pDmoModel = work->header->models;

        for (i = 0; i < work->header->n_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->type == data->data.variant_0x18.field_18)
            {
                break;
            }
        }

        if (i >= work->header->n_models)
        {
            break;
        }

        pIter = work->chain.next;
        while (pIter != &work->chain)
        {
            if ((pIter->chara.field_4_type == 0x18) && (pIter->chara.field_18_xy == data->data.variant_0x18.field_18))
            {
                if (pIter->actor1 != NULL)
                {
                    GV_DestroyOtherActor(pIter->actor1);
                    pIter->actor1 = NULL;
                }
            }
            pIter = pIter->next;
        }
        if (data->data.variant_0x18.field_14 == 0)
        {
            funcptr = GM_GetCharaID(0x1C);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr(&pModel->object, data->data.variant_0x18.field_1C);
            }
        }
        break;
    case 0x19:
        pModel = work->models;
        pDmoModel = work->header->models;

        for (i = 0; i < work->header->n_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->type == data->data.variant_0x19.field_14)
            {
                break;
            }
        }

        if (i >= work->header->n_models)
        {
            break;
        }

        funcptr = GM_GetCharaID(0x1D);
        if (funcptr != NULL)
        {
            funcptr(&pModel->object, data->data.variant_0x19.field_18, data->data.variant_0x19.field_1A,
                    data->data.variant_0x19.field_1C, data->data.variant_0x19.field_20);
        }
        break;
    case 0x1A:
        funcptr = GM_GetCharaID(0x1E);
        if (funcptr != NULL)
        {
            funcptr(&mat2, data->data.variant_0x1A.field_14);
        }
        break;
    case 0x1B:
        RemoveType(work, 0x1B);
        if (data->data.variant_0x1B.field_14 == 0)
        {
            funcptr = GM_GetCharaID(0x1F);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr(data->data.variant_0x1B.field_16, data->data.variant_0x1B.field_18,
                                                 data->data.variant_0x1B.field_1A);
            }
        }
        break;
    case 0x1C:
        pIter = work->chain.next;
        while (pIter != &work->chain && (pIter->chara.field_4_type != 0x1C || pIter->actor1 == NULL))
        {
            pIter = pIter->next;
        }
        svec1.vx = data->data.variant_0x1C.field_14;
        svec1.vy = data->data.variant_0x1C.field_16;
        svec1.vz = data->data.variant_0x1C.field_18;
        svec2.vx = data->data.variant_0x1C.field_1A;
        svec2.vy = data->data.variant_0x1C.field_1C;
        svec2.vz = data->data.variant_0x1C.field_1E;
        if (pIter == &work->chain)
        {
            funcptr = GM_GetCharaID(0x20);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr(&node->field_58);
                pIter = node;
            }
            else
            {
                break;
            }
        }
        DG_SetPos2(&svec1, &svec2);
        ReadRotMatrix(&pIter->field_58);

        break;
    case 0x1D:
        RemoveType(work, 0x1D);
        if (data->data.variant_0x1D.field_14 == 0)
        {
            funcptr = GM_GetCharaID(0x21);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr(data->data.variant_0x1D.field_18, data->data.variant_0x1D.field_1C);
            }
        }
        break;
    case 0x1F:
        pIter = work->chain.next;
        work->field_268 = 1;
        work->field_26C = 1;
        while (pIter != &work->chain)
        {
            if (pIter->actor1 != NULL)
            {
                GV_DestroyOtherActor(pIter->actor1);
                if (pIter->actor2 != NULL)
                {
                    GV_DestroyOtherActor(pIter->actor2);
                }
                pIter->actor1 = NULL;
                pIter->actor2 = NULL;
            }
            pIter = pIter->next;
        }
        break;
    case 0x20:
        if (data->data.variant_0x20.field_20 == 1)
        {
            pIter = work->chain.next;
            while (pIter != &work->chain)
            {
                if (pIter->chara.field_4_type == 0x20)
                {
                    if (pIter->actor1 != NULL)
                    {
                        GV_DestroyOtherActor(pIter->actor1);
                        pIter->actor1 = NULL;
                    }
                }
                pIter = pIter->next;
            }
        }
        else
        {
            funcptr = GM_GetCharaID(0x23);
            if (funcptr != NULL)
            {
                if (data->data.variant_0x20.field_14 >= 2 && data->data.variant_0x20.field_14 <= 5)
                {
                    funcptr(&svec1, data->data.variant_0x20.field_14 + 2, data->data.variant_0x20.field_18,
                            data->data.variant_0x20.field_1C);
                }
                else
                {
                    node->actor1 = funcptr(&svec1, data->data.variant_0x20.field_14 + 2,
                                                     data->data.variant_0x20.field_18, data->data.variant_0x20.field_1C);
                }
            }
        }
        break;
    case 0x21:
        svec3.vx = data->data.variant_0x21.field_14;
        svec3.vy = data->data.variant_0x21.field_16;
        svec3.vz = data->data.variant_0x21.field_18;
        funcptr = GM_GetCharaID(0x24);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec3, data->data.variant_0x21.field_1C);
        }
        break;
    case 0x22:
        RemoveType(work, 0x22);
        if (data->data.variant_0x22.field_14 == 0)
        {
            funcptr = GM_GetCharaID(0x25);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr(data->data.variant_0x22.field_16, data->data.variant_0x22.field_18,
                                                 data->data.variant_0x22.field_1A);
            }
        }
        break;
    case 0x23:
        svec3.vx = data->data.variant_0x23.field_14;
        svec3.vy = data->data.variant_0x23.field_16;
        svec3.vz = data->data.variant_0x23.field_18;
        if (data->data.variant_0x23.field_1A != 4)
        {
            funcptr = GM_GetCharaID(0x26);
            if (funcptr != NULL)
            {
                ((VoidMakeChara)funcptr)(&svec1, &svec3, data->data.variant_0x23.field_1A);
            }
        }
        else
        {
            funcptr = GM_GetCharaID(0x27);
            if (funcptr != NULL)
            {
                ((VoidMakeChara)funcptr)(&svec1, &svec3, data->data.variant_0x23.field_1C & 0xFF,
                                         data->data.variant_0x23.field_1E & 0xFF,
                                         data->data.variant_0x23.field_20 & 0xFF);
            }
        }
        break;
    case 0x24:
        RemoveType(work, 0x24);

        if (data->data.variant_0x24.field_14 == 0)
        {
            funcptr = GM_GetCharaID(0x28);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr();
            }
        }
        break;

    case 0x25:
        RemoveType(work, 0x25);

        if (data->data.variant_0x25.field_14 == 0)
        {
            funcptr = GM_GetCharaID(0x29);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr();
            }
        }
        break;

    case 0x26:
        pModel = work->models;
        pDmoModel = work->header->models;

        for (i = 0; i < work->header->n_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->filename == GV_StrCode("hind"))
            {
                break;
            }
            if (pDmoModel->filename == GV_StrCode("hinddemo"))
            {
                break;
            }
        }

        if (i >= work->header->n_models)
        {
            break;
        }

        pModel->extra->object[0][0].objs = data->data.variant_0x26.field_14;
        pModel->extra->object[0][0].flag = data->data.variant_0x26.field_18;

        break;
    case 0x27:
        funcptr = GM_GetCharaID(0x2a);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x28:
        funcptr = GM_GetCharaID(0x2B);
        if (funcptr != NULL)
        {
            if (data->data.variant_0x28.field_14 >= 0 && data->data.variant_0x28.field_14 <= 3)
            {
                funcptr(&svec1, data->data.variant_0x28.field_14 + 4, data->data.variant_0x28.field_18,
                        data->data.variant_0x28.field_1C);
            }
            else
            {
                node->actor1 = funcptr(&svec1, data->data.variant_0x28.field_14 + 4,
                                                 data->data.variant_0x28.field_18, data->data.variant_0x28.field_1C);
            }
        }
        break;

    case 0x29:
        pIter = work->chain.next;

        if (pIter != &work->chain)
        {
            while ((pIter->chara.field_4_type != 0x29) || !pIter->actor1)
            {
                pIter = pIter->next;

                if (pIter == &work->chain)
                {
                    break;
                }
            }
        }

        if (pIter == &work->chain)
        {
            if (data->data.variant_0x29.field_14 != 1)
            {
                funcptr = GM_GetCharaID(0x2C);
                if (funcptr != NULL)
                {
                    node->actor1 = funcptr(data->data.variant_0x29.field_1C, &data->data.variant_0x29.field_16);
                }
            }
        }
        else if (data->data.variant_0x29.field_14 != 0)
        {
            if (pIter->chara.field_1C_zpad != data->data.variant_0x29.field_1C)
            {
                GV_DestroyOtherActor(pIter->actor1);
                pIter->actor1 = NULL;
                funcptr = GM_GetCharaID(0x2C);
                if (funcptr != NULL)
                {
                    node->actor1 = funcptr(data->data.variant_0x29.field_1C, &data->data.variant_0x29.field_16);
                }
            }
            else
            {
                // TODO: I can't make sense of it (field_28 is used as an int in other places...)
                struct copier
                {
                    short a, b;
                };
                *(struct copier *)((char *)&pIter->chara.field_14_type + 2) = *(struct copier *)&data->data.variant_0x29.field_16;
            }
        }
        else
        {
            GV_DestroyOtherActor(pIter->actor1);
            pIter->actor1 = NULL;
        }
        break;

    case 0x2A:
        pModel = work->models;
        pDmoModel = work->header->models;

        for (i = 0; i < work->header->n_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->type == data->data.variant_0x2A.field_14)
            {
                break;
            }
        }

        if (i >= work->header->n_models)
        {
            break;
        }

        pIter = work->chain.next;
        while (pIter != &work->chain)
        {
            if ((pIter->chara.field_4_type == 0x2A) && (pIter->chara.field_14_type == data->data.variant_0x2A.field_14))
            {
                if (pIter->actor1 != NULL)
                {
                    GV_DestroyOtherActor(pIter->actor1);
                    pIter->actor1 = NULL;
                }
            }
            pIter = pIter->next;
        }
        if (data->data.variant_0x2A.field_18 != 1)
        {
            funcptr = GM_GetCharaID(0x2D);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr(&pModel->object.objs->objs[4]);
            }
        }
        break;

    case 0x2B:
        pIter = work->chain.next;

        while (pIter != &work->chain)
        {
            if (pIter->chara.field_4_type == 0x2B)
            {
                if (pIter->actor1 != NULL)
                {
                    GV_DestroyOtherActor(pIter->actor1);
                    pIter->actor1 = NULL;
                }
            }
            pIter = pIter->next;
        }

        if (data->data.variant_0x2B.field_14 == 0)
        {
            funcptr = GM_GetCharaID(0x2E);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr();
            }
        }
        break;

    case 0x2C:
        svec3.vx = data->data.variant_0x2C.field_14;
        svec3.vy = data->data.variant_0x2C.field_16;
        svec3.vz = data->data.variant_0x2C.field_18;
        funcptr = GM_GetCharaID(0x2F);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec3, data->data.variant_0x2C.field_1A, data->data.variant_0x2C.field_1C);
        }
        break;
    case 0x2D:
        svec3.vx = data->data.variant_0x2D.field_14;
        svec3.vy = data->data.variant_0x2D.field_16;
        svec3.vz = data->data.variant_0x2D.field_18;
        funcptr = GM_GetCharaID(0x30);
        if (funcptr != NULL)
        {
            funcptr(data->data.variant_0x2D.field_22, data->data.variant_0x2D.field_1C, data->data.variant_0x2D.field_20,
                    &svec1, &svec3);
        }
        break;

    case 0x2E:
        svec3.vx = data->data.variant_0x2E.field_14;
        svec3.vy = data->data.variant_0x2E.field_16;
        svec3.vz = data->data.variant_0x2E.field_18;
        svec4.vx = data->data.variant_0x2E.field_1A;
        svec4.vy = data->data.variant_0x2E.field_1C;
        svec4.vz = data->data.variant_0x2E.field_1E;
        funcptr = GM_GetCharaID(0x31);
        if (funcptr != NULL)
        {
            funcptr(data->data.variant_0x2E.field_26, data->data.variant_0x2E.field_20, data->data.variant_0x2E.field_24,
                    &svec1, &svec3, &svec4, data->data.variant_0x2E.field_28 & 0xFF,
                    data->data.variant_0x2E.field_2A & 0xFF, data->data.variant_0x2E.field_2C & 0xFF);
        }
        break;

    case 0x2F:
        funcptr = GM_GetCharaID(0x32);
        if (funcptr != NULL)
        {
            funcptr(data->data.variant_0x2F.field_14, &svec1, &svec2);
        }
        break;

    case 0x30:
        funcptr = GM_GetCharaID(0x33);
        if (funcptr != NULL)
        {
            funcptr(&svec2, &svec1);
        }
        break;

    case 0x31:
        funcptr = GM_GetCharaID(0x34);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x32:
        funcptr = GM_GetCharaID(0x35);
        if (funcptr != NULL)
        {
            funcptr(&mat2);
        }
        break;

    case 0x33:
        funcptr = GM_GetCharaID(0x36);
        if (funcptr != NULL)
        {
            funcptr(&svec1);
        }
        break;

    case 0x34:
        svec3.vx = data->data.variant_0x34.field_24;
        svec3.vy = data->data.variant_0x34.field_26;
        svec3.vz = data->data.variant_0x34.field_28;
        svec4.vx = data->data.variant_0x34.field_2A;
        svec4.vy = data->data.variant_0x34.field_2C;
        svec4.vz = data->data.variant_0x34.field_2E;
        if (data->data.variant_0x34.field_30 == 0)
        {
            funcptr = GM_GetCharaID(0x37);
            if (funcptr != NULL)
            {
                funcptr(data->data.variant_0x34.field_14, data->data.variant_0x34.field_18, &svec3, &svec4,
                        data->data.variant_0x34.field_1C, data->data.variant_0x34.field_20);
            }
        }
        else
        {
            memset(&msg, 0, sizeof(msg));
            msg.address = data->data.variant_0x34.field_14;
            msg.message[0] = HASH_KILL;
            msg.message_len = 1;

            GV_SendMessage(&msg);
        }
        break;

    case 0x35:
        funcptr = GM_GetCharaID(0x39);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec2, data->data.variant_0x35.field_18, data->data.variant_0x35.field_1C,
                    data->data.variant_0x35.field_1E, data->data.variant_0x35.field_20,
                    data->data.variant_0x35.field_22 & 0xFF, data->data.variant_0x35.field_24 & 0xFF,
                    data->data.variant_0x35.field_26 & 0xFF);
        }
        break;

    case 0x37:
        funcptr = GM_GetCharaID(0x3A);
        if (funcptr != NULL)
        {
            funcptr(data->data.variant_0x37.field_14, data->data.variant_0x37.field_18, data->data.variant_0x37.field_1C,
                    data->data.variant_0x37.field_1E, data->data.variant_0x37.field_20, data->data.variant_0x37.field_22,
                    &data->data.variant_0x37.field_24, &data->data.variant_0x37.field_28, data->data.variant_0x37.field_2C,
                    data->data.variant_0x37.field_2E, data->data.variant_0x37.field_30, data->data.variant_0x37.field_32);
        }
        break;

    case 0x38:
        funcptr = GM_GetCharaID(0x3B);
        if (funcptr != NULL)
        {
            ((VoidMakeChara)funcptr)(&svec1);
        }
        break;
    case 0x39:
        switch (data->data.variant_0x39.field_14)
        {
        case 0:
            funcptr = GM_GetCharaID(0x3C);
            if (funcptr != NULL)
            {
                ((VoidMakeChara)funcptr)(&mat2);
            }
            break;

        case 1:
            funcptr = GM_GetCharaID(0x3D);
            if (funcptr != 0)
            {
                funcptr(&mat2, 0);
            }
            break;

        case 2:
            funcptr = GM_GetCharaID(0x3D);
            if (funcptr != 0)
            {
                funcptr(&mat2, 1);
            }
            break;
        }
        break;
    case 0x3A:
        svec3.vx = data->data.variant_0x3A.field_14;
        svec3.vy = data->data.variant_0x3A.field_16;
        svec3.vz = data->data.variant_0x3A.field_18;
        funcptr = GM_GetCharaID(0x3E);
        if (funcptr != NULL)
        {
            funcptr(&svec1, &svec3);
        }
        break;
    case 0x3B:
        funcptr = GM_GetCharaID(0x3F);
        if (funcptr != NULL)
        {
            funcptr(&svec1, data->data.variant_0x3B.field_14, data->data.variant_0x3B.field_18,
                    data->data.variant_0x3B.field_1C, data->data.variant_0x3B.field_20, data->data.variant_0x3B.field_22,
                    data->data.variant_0x3B.field_24, data->data.variant_0x3B.field_26, data->data.variant_0x3B.field_28);
        }
        break;
    case 0x3C:
        funcptr = GM_GetCharaID(0x40);
        if (funcptr != NULL)
        {
            funcptr(data->data.variant_0x3C.field_14, data->data.variant_0x3C.field_18, data->data.variant_0x3C.field_1C,
                    data->data.variant_0x3C.field_1E, data->data.variant_0x3C.field_20, data->data.variant_0x3C.field_22,
                    data->data.variant_0x3C.field_24, &data->data.variant_0x3C.field_26, &data->data.variant_0x3C.field_2A,
                    data->data.variant_0x3C.field_2E, data->data.variant_0x3C.field_30, data->data.variant_0x3C.field_32,
                    data->data.variant_0x3C.field_34);
        }
        break;
    case 0x3D:
        pModel = work->models;
        pDmoModel = work->header->models;

        for (i = 0; i < work->header->n_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->type == data->data.variant_0x3D.field_18)
            {
                break;
            }
        }

        if (i >= work->header->n_models)
        {
            break;
        }

        funcptr = GM_GetCharaID(0x41);
        if (funcptr != NULL)
        {
            funcptr(&pModel->object.objs[6].world.m[1][1], data->data.variant_0x3D.field_14,
                    data->data.variant_0x3D.field_16);
        }
        break;
    case 0x3E:
        pIter = work->chain.next;

        if (pIter != &work->chain)
        {
            while ((pIter->chara.field_4_type != 0x3e) || !pIter->actor1)
            {
                pIter = pIter->next;

                if (pIter == &work->chain)
                {
                    break;
                }
            }
        }

        if (data->data.variant_0x3E.field_14 == 0)
        {
            if (pIter != &work->chain)
            {
                GV_DestroyOtherActor(pIter->actor1);
                pIter->actor1 = NULL;
            }

            funcptr = GM_GetCharaID(0x42);
            if (funcptr != NULL)
            {
                svec3.vx = data->data.variant_0x3E.field_16;
                svec3.vy = data->data.variant_0x3E.field_18;
                svec3.vz = data->data.variant_0x3E.field_1A;
                node->actor1 =
                    funcptr(&svec3, data->data.variant_0x3E.field_1E, data->data.variant_0x3E.field_1C + 1);
            }
        }
        else if (data->data.variant_0x3E.field_14 == 1)
        {
            if (pIter != &work->chain)
            {
                GV_DestroyOtherActor(pIter->actor1);
                pIter->actor1 = NULL;
            }
        }
        else if (data->data.variant_0x3E.field_14 == 2)
        {
            if (pIter != &work->chain)
            {
                memset(&msg, 0, sizeof(msg));
                msg.address = 0x3B8E;
                if (data->data.variant_0x3E.field_20 == 0)
                {
                    msg.message[0] = HASH_ON2;
                }
                else
                {
                    msg.message[0] = HASH_OFF2;
                }
                msg.message[1] = data->data.variant_0x3E.field_22;
                msg.message_len = 2;

                GV_SendMessage(&msg);
            }
        }
        break;

    case 0x3F:
        pModel = work->models;
        pDmoModel = work->header->models;

        for (i = 0; i < work->header->n_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->type == data->data.variant_0x3F.field_18)
            {
                break;
            }
        }

        if (i >= work->header->n_models)
        {
            break;
        }

        pIter = work->chain.next;
        while (pIter != &work->chain)
        {
            if ((pIter->chara.field_4_type == 0x3F) && (pIter->chara.field_18_xy == data->data.variant_0x3F.field_18))
            {
                if (pIter->actor1 != NULL)
                {
                    GV_DestroyOtherActor(pIter->actor1);
                    pIter->actor1 = NULL;
                }
            }
            pIter = pIter->next;
        }

        if (data->data.variant_0x3F.field_14 != 1)
        {
            funcptr = GM_GetCharaID(0x43);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr(&pModel->object, &pModel->control.rot);
            }
        }

        break;
    case 0x36:
    case 0x40:
        if (data->data.variant_0x36.field_14 != 0)
        {
            GM_PadVibration = 1;
        }
        if (data->data.variant_0x36.field_16 != 0)
        {
            GM_PadVibration2 = data->data.variant_0x36.field_18;
        }
        break;
    case 0x41:
        RemoveType(work, 0x41);
        if (data->data.variant_0x41.field_14 == 0)
        {
            funcptr = GM_GetCharaID(0x44);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr();
            }
        }
        break;

    case 0x42:
        DG_SetTmpLight(&svec1, data->data.variant_0x42.field_14, data->data.variant_0x42.field_16);
        break;

    case 0x43:
        pModel = work->models;
        pDmoModel = work->header->models;

        for (i = 0; i < work->header->n_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->type == data->data.variant_0x43.field_14)
            {
                break;
            }
        }

        if (i >= work->header->n_models)
        {
            break;
        }

        pIter = work->chain.next;

        while (pIter != &work->chain)
        {
            if ((pIter->chara.field_4_type == 0x43) && (pIter->chara.field_14_type == data->data.variant_0x43.field_14))
            {
                if (pIter->actor1 != NULL)
                {
                    GV_DestroyOtherActor(pIter->actor1);
                    pIter->actor1 = NULL;
                }
            }
            pIter = pIter->next;
        }

        if (data->data.variant_0x43.field_18 != 1)
        {
            funcptr = GM_GetCharaID(0x45);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr(pModel->object.objs + 1);
            }
        }
        break;
    case 0x44:
        pModel = work->models;
        pDmoModel = work->header->models;

        for (i = 0; i < work->header->n_models; i++, pDmoModel++, pModel++)
        {
            if (pDmoModel->type == data->data.variant_0x44.field_18)
            {
                break;
            }
        }

        if (i >= work->header->n_models)
        {
            break;
        }

        pIter = work->chain.next;

        if (pIter != &work->chain)
        {
            while ((pIter->chara.field_4_type != 0x44) || !pIter->actor1)
            {
                pIter = pIter->next;

                if (pIter == &work->chain)
                {
                    break;
                }
            }
        }

        if (pIter == &work->chain)
        {
            if (data->data.variant_0x44.field_14 != 1)
            {
                funcptr = GM_GetCharaID(0x46);

                if (funcptr != NULL)
                {
                    node->field_50 = data->data.variant_0x44.field_1E;
                    node->field_52 = data->data.variant_0x44.field_20;
                    node->field_54 = data->data.variant_0x44.field_22;

                    if (data->data.variant_0x44.field_1C == 0)
                    {
                        node->field_56 = 0;
                    }
                    else
                    {
                        node->field_56 = -1;
                    }

                    node->actor1 =
                        funcptr(pModel, &pModel->object, &node->field_50, pDmoModel->cache_id);
                }
            }
        }
        else if (data->data.variant_0x44.field_14 == 1)
        {
            GV_DestroyOtherActor(pIter->actor1);
            pIter->actor1 = NULL;
        }
        else
        {
            pIter->field_50 = data->data.variant_0x44.field_1E;
            pIter->field_52 = data->data.variant_0x44.field_20;
            pIter->field_54 = data->data.variant_0x44.field_22;
        }
        break;

    case 0x45:
        funcptr = GM_GetCharaID(0x47);
        if (funcptr != NULL)
        {
            node->actor1 = funcptr(&mat2, data->data.variant_0x45.field_14, data->data.variant_0x45.field_16,
                                             data->data.variant_0x45.field_18, data->data.variant_0x45.field_1A);
        }
        break;
    case 0x46:
        funcptr = GM_GetCharaID(0x48);
        if (funcptr != NULL)
        {
            funcptr(&svec1, data->data.variant_0x46.field_14, data->data.variant_0x46.field_16);
        }
        break;
    case 0x47:
        funcptr = GM_GetCharaID(0x49);
        if (funcptr != NULL)
        {
            funcptr(&mat2, 400, 400, 400, 10);
        }
        break;

    case 0x48:
        funcptr = GM_GetCharaID(0x4A);
        if (funcptr != NULL)
        {
            ((VoidMakeChara)funcptr)(&svec1);
        }
        break;

    case 0x49:
        pIter = work->chain.next;
        while (pIter != &work->chain)
        {
            if (pIter->chara.field_4_type == 0x49)
            {
                if (pIter->actor1 != NULL)
                {
                    GV_DestroyOtherActor(pIter->actor1);
                    pIter->actor1 = NULL;
                }
            }
            pIter = pIter->next;
        }

        if (data->data.variant_0x49.field_14 == 0)
        {
            funcptr = GM_GetCharaID(0x4B);
            if (funcptr != NULL)
            {
                node->actor1 = funcptr();
            }
        }
        break;

    case 0x4A:
        funcptr = GM_GetCharaID(0x4C);

        if (funcptr != NULL)
        {
            funcptr(data->data.variant_0x4A.field_18, data->data.variant_0x4A.field_1A, 0,
                    data->data.variant_0x4A.field_14, data->data.variant_0x4A.field_1C, data->data.variant_0x4A.field_20);
        }
        break;
    }

    return 1;
}

static void RemoveType(DemoWork *work, int type)
{
    ACTNODE *pSubIter; // $s0
    ACTNODE *pCur; // $a0
    ACTNODE *pCur_; // $s1
    GV_ACT *pPrevious; // $a0
    GV_ACT *pNext; // $a0

    pSubIter = work->chain.next;
    pCur = &work->chain;
    if ( pSubIter != pCur )
    {
        pCur_ = pCur;
        do
        {
            if ( pSubIter->chara.field_4_type == type )
            {
                pPrevious = pSubIter->actor1;
                if ( pPrevious )
                {
                    GV_DestroyOtherActor(pPrevious);
                    pNext = pSubIter->actor2;
                    if ( pNext )
                    {
                        GV_DestroyOtherActor(pNext);
                    }
                    pSubIter->actor1 = 0;
                    pSubIter->actor2 = 0;
                }
            }
            pSubIter = pSubIter->next;
        }
        while ( pSubIter != pCur_ );
    }
}

static int demothrd_8007CDF8(DemoWork *work, DMO_DAT *data, ACTNODE *node)
{
    DMO_ADJ *adjust;
    int idx;
    HZD_VEC vec2;
    SVECTOR vecPos;
    if (node->chara.field_4_type == 14)
    {
        adjust = data->adjust;
        {
            for (idx = 0; idx < data->n_adjusts; idx++)
            {
                if (adjust->type == node->chara.field_14_type)
                {
                    break;
                }
                ++adjust;
            }

            if (idx < data->n_adjusts)
            {
                vecPos.vx = adjust->pos_x;
                vecPos.vy = adjust->pos_y;
                vecPos.vz = adjust->pos_z;
                idx = HZD_LevelTestHazard(work->control.map->hzd, &vecPos, 1);
                HZD_LevelMinMaxHeights((int *)&vec2);
                node->field_48 = adjust->rot_y;
                if ((idx & 1) != 0)
                {
                    node->field_4C = vec2.x + 50;
                }
                else if ((idx & 2) != 0)
                {
                    node->field_4C = vec2.y + 50;
                }
                else
                {
                    node->field_4C = adjust->pos_y + 50;
                }

            }
        }
    }
    return 1;
}

static int demothrd_1_FrameRunDemo_helper4_8007CF14(DemoWork *work, DMO_DAT *data)
{
    DMO_CHA *pIter;
    int i;
    ACTNODE *pNext;
    ACTNODE *new_var;
    ACTNODE *new_var2;
    ACTNODE *root;
    pIter = data->chara;
    for (i = 0; i < data->n_charas; ++pIter)
    {
        ++i;
        if (pIter->field_4_type == 28)
        {
            return 1;
        }
    }

    pNext = work->chain.next;
    new_var = &work->chain;
    if (pNext != new_var)
    {
        if (pNext->chara.field_4_type != 28)
        {
            new_var2 = new_var;
            root = &work->chain;
            while (1)
            {
                pNext = pNext->next;
                if (pNext == new_var2)
                {
                    break;
                }
                if (pNext->chara.field_4_type == 28)
                {
                    root = &work->chain;
                    break;
                }
            }

        }
    }
    if (pNext != (&work->chain))
    {
        GV_DestroyOtherActor(pNext->actor1);
        root = &work->chain;
        pNext->actor1 = 0;
        RemoveChain(root, pNext);
        GV_Free(pNext);
    }
    return 1;
}

static int demothrd_8007CFE8(DemoWork *work, DMO_ADJ *adjust)
{
    DMO_MDL    *model_file;
    DEMO_MODEL *model;
    int         i;
    short      *rots;

    OFFSET_TO_PTR(adjust, &adjust->rots);

    model_file = work->header->models;
    model = work->models;
    for (i = 0; i < work->header->n_models; i++, model_file++, model++)
    {
        if (model_file->type == adjust->type)
        {
            break;
        }
    }

    if (i >= work->header->n_models)
    {
        return 0;
    }

    if (!adjust->visible)
    {
        DG_InvisibleObjs(model->object.objs);

        if (model_file->filename == GV_StrCode("m1e1") || model_file->filename == GV_StrCode("m1e1demo"))
        {
            DG_InvisibleObjs(model->extra->object[0][0].objs);
            DG_InvisibleObjs(model->extra->object[0][1].objs);
            DG_InvisibleObjs(model->extra->object[0][2].objs);
            DG_InvisibleObjs(model->extra->object[1][0].objs);
            DG_InvisibleObjs(model->extra->object[1][1].objs);
            DG_InvisibleObjs(model->extra->object[1][2].objs);
        }
    }
    else
    {
        DG_VisibleObjs(model->object.objs);

        if (model_file->filename == GV_StrCode("m1e1") || model_file->filename == GV_StrCode("m1e1demo"))
        {
            DG_VisibleObjs(model->extra->object[0][model->extra->field_558_idx[0]].objs);
            DG_VisibleObjs(model->extra->object[1][model->extra->field_558_idx[1]].objs);
        }

        model->control.mov.vx = adjust->pos_x;
        model->control.mov.vy = adjust->pos_y;
        model->control.mov.vz = adjust->pos_z;
        model->control.rot.vx = adjust->rot_x;
        model->control.rot.vy = adjust->rot_y;
        model->control.rot.vz = adjust->rot_z;

        if (model_file->flag & 0x1)
        {
            GM_ActControl(&model->control);
            GM_ActObject2(&model->object);
        }
        else
        {
            rots = adjust->rots;
            for (i = 0; i < adjust->n_rots; i++, rots += 3)
            {
                model->object.rots[i].vx = rots[0];
                model->object.rots[i].vy = rots[1];
                model->object.rots[i].vz = rots[2];
            }

            if (model_file->filename == GV_StrCode("m1e1") || model_file->filename == GV_StrCode("m1e1demo"))
            {
                demothrd_m1e1_8007D404(work, adjust, model_file, model);
            }
            else if (model_file->filename == GV_StrCode("hind") || model_file->filename == GV_StrCode("hinddemo"))
            {
                demothrd_hind_8007D9C8(work, adjust, model_file, model);
            }

            GM_ActMotion(&model->object);
            GM_ActControl(&model->control);
            GM_ActObject(&model->object);
            DG_GetLightMatrix(&model->control.mov, model->light);
        }
    }

    return 1;
}

static inline int magic_calc(SVECTOR* vecTmp, DEMO_MODEL *model)
{
    int distance1 = SquareRoot0(((vecTmp->vx * vecTmp->vx) + (vecTmp->vy * vecTmp->vy)) + (vecTmp->vz * vecTmp->vz));

    int rTan1 = ratan2(vecTmp->vx, vecTmp->vz);
    int tmp4 = rTan1;
    tmp4 -= model->control.rot.vy + model->object.rots[0].vy;
    tmp4 = abs(tmp4);
    return (distance1 * (1024 - tmp4)) / 1024;
}

static void demothrd_m1e1_8007D404(DemoWork *work, DMO_ADJ *adjust, DMO_MDL *model_file, DEMO_MODEL *model)
{
    DEMO_M1E1 *data;
    int tmp1;
    int i;
    SVECTOR vec;
    SVECTOR vecTmp;
    SVECTOR smokeVecs[10];

    data = model->extra;
    for (i = 0; i < 3; i++)
    {
        GM_ActMotion(&data->object[0][i]);
        GM_ActMotion(&data->object[1][i]);
    }

    DG_SetPos2(&model->control.mov, &model->control.rot);
    DG_RotatePos(model->object.rots);

    M1E1GetCaterpillerVertex(&model->extra->object[0][0], &model->extra->object[1][0], smokeVecs, 1);
    for (i = 0; i < 10; i++)
    {
        smokeVecs[i].vy = smokeVecs[i].vy + 300;
    }

    DG_PutVector(smokeVecs, smokeVecs, 10);

    memset(&vec, 0, sizeof(SVECTOR));
    vec.vx = data->object[1][0].objs->objs[0].model->min.vx + ((data->object[1][0].objs->objs[0].model->max.vx - data->object[1][0].objs->objs[0].model->min.vx) / 2);
    DG_PutVector(&vec, &vec, 1);

    vecTmp.vx = vec.vx - data->field_564[0].vx;
    vecTmp.vy = vec.vy - data->field_564[0].vy;
    vecTmp.vz = vec.vz - data->field_564[0].vz;

    tmp1 = magic_calc(&vecTmp, model);

    if (abs(tmp1) >= data->field_560)
    {
        AN_CaterpillerSmoke(&smokeVecs[rand() % 5]);
        DG_InvisibleObjs(data->object[0][data->field_558_idx[0]].objs);
        if (tmp1 > 0)
        {
            data->field_558_idx[0]++;
        }
        else
        {
            data->field_558_idx[0]--;
        }
        if (data->field_558_idx[0] < 0)
        {
            data->field_558_idx[0] = 2;
        }
        if (data->field_558_idx[0] >= 3)
        {
            data->field_558_idx[0] = 0;
        }
        DG_VisibleObjs(data->object[0][data->field_558_idx[0]].objs);
        data->field_564[0] = vec;
    }


    memset(&vec, 0, sizeof(SVECTOR));
    vec.vx = data->object[1][0].objs->objs[0].model->min.vx + ((data->object[1][0].objs->objs[0].model->max.vx - data->object[1][0].objs->objs[0].model->min.vx) / 2);
    DG_SetPos2(&model->control.mov, &model->control.rot);

    DG_PutVector(&vec, &vec, 1);
    vecTmp.vx = vec.vx - data->field_564[1].vx;
    vecTmp.vy = vec.vy - data->field_564[1].vy;
    vecTmp.vz = vec.vz - data->field_564[1].vz;

    tmp1 = magic_calc(&vecTmp, model);

    if (abs(tmp1) >= data->field_560)
    {
        AN_CaterpillerSmoke(&smokeVecs[(rand() % 5) + 5]);
        DG_InvisibleObjs(data->object[1][data->field_558_idx[1]].objs);
        if (tmp1 > 0)
        {
            data->field_558_idx[1]++;
        }
        else
        {
            data->field_558_idx[1]--;
        }
        if (data->field_558_idx[1] < 0)
        {
            data->field_558_idx[1] = 2;
        }
        if (data->field_558_idx[1] >= 3)
        {
            data->field_558_idx[1] = 0;
        }
        DG_VisibleObjs(data->object[1][data->field_558_idx[1]].objs);
        data->field_564[1] = vec;
    }
    DG_SetPos2(&model->control.mov, &model->control.rot);
    DG_RotatePos(model->object.rots);
    for (i = 0; i < 3; i++)
    {
        GM_ActObject(&data->object[0][i]);
        GM_ActObject(&data->object[1][i]);
    }
}

static void demothrd_hind_8007D9C8(DemoWork *work, DMO_ADJ *adjust, DMO_MDL *model_file, DEMO_MODEL *model)
{
    DEMO_HIND *pTmp = (DEMO_HIND *)model->extra; // TODO: Would be cleaner as a union

    pTmp->field_8 = pTmp->field_8 - pTmp->field_0;
    if ( pTmp->field_8 < 0 )
    {
        pTmp->field_8 = pTmp->field_8 + 4096;
    }

    pTmp->field_C = pTmp->field_C - pTmp->field_4;
    if ( pTmp->field_C < 0 )
    {
        pTmp->field_C = pTmp->field_C + 4096;
    }

    model->object.rots[1].vy = pTmp->field_8;
    model->object.rots[2].vx = pTmp->field_C;
}
