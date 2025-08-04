#include "mts/mts.h"
#include "game/camera.h"
#include "linkvar.h"
#include "wolf2.h"

extern int              dword_8009F46C[];
extern SVECTOR          svector_8009F478;
extern GV_PAD           GV_PadData_800B05C0[4];
extern GM_Camera        GM_Camera_800B77E8;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

RECT        wolf2_800C3490 = {0, 0, 2, 2};
extern char wolf2_800DD6B8[5];

void  AN_Breath(MATRIX *world);

void *NewCinemaScreen( int, int );
void *NewCinemaScreenClose( void *addr );

void s12a_wolf2_800CED18(Wolf2Work *work);
void s12a_wolf2_800CED38(Wolf2Work *work);
void s12a_wolf2_800D1EBC(Wolf2Work *work);
void s12a_wolf2_800D2E0C(Wolf2Work *work);

#define EXEC_LEVEL      GV_ACTOR_LEVEL4

#define MOTION_DATA     GV_StrCode("sniper")
#define BODY_DATA       GV_StrCode("sniper")
#define BODY_DATA2      GV_StrCode("snp_cold")
#define WEAPON_DATA     GV_StrCode("rifle")

#define TARGET_FLAG     (TARGET_SEEK)
#define BODY_FLAG       (DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_IRTEXTURE)
#define WEAPON_FLAG     (DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE | DG_FLAG_ONEPIECE)

void wolf2_ExecProcC(Wolf2Work *work)
{
    GCL_ARGS args;
    u_long   data[3];

    if (work->f9C0 >= 0)
    {
        args.argc = 3;
        args.argv = data;

        data[0] = GM_PlayerPosition.vx;
        data[1] = GM_PlayerPosition.vy;
        data[2] = GM_PlayerPosition.vz;

        GCL_ExecProc(work->f9C0, &args);
    }
}

void wolf2_ExecProcJ(Wolf2Work *work)
{
    GCL_ARGS args;
    u_long   data[5];

    data[0] = work->control.mov.vx;
    data[1] = work->control.mov.vy;
    data[2] = work->control.mov.vz;
    data[3] = work->control.rot.vy;
    data[4] = work->f6FC;

    args.argc = 5;
    args.argv = data;

    GCL_ForceExecProc(work->f9E4, &args);
}

void wolf2_SetTileShade(TILE *tile, int shade)
{
    setRGB0(tile, shade, shade / 4, shade / 4);
}

void wolf2_InitTiles(TILE *tile)
{
    int i;

    for (i = 2; i > 0; i--)
    {
        setTile(tile);
        setRGB0(tile, 255, 63, 63);
        setWH(tile, 2, 2);
        tile++;
    }
}

void wolf2_InitTexcoords(POLY_FT4 *poly, DG_TEX *tex, int y)
{
    int x;
    int i;

    x = tex->off_x;
    y = tex->off_y + (y & 0x3F);

    for (i = 8; i > 0; i--)
    {
        setUVWH(poly, x, y, 7, 0);
        x += 8;
        poly++;
    }
}

void wolf2_InitTexpacks(POLY_FT4 *poly, DG_TEX *tex)
{
    int i;

    for (i = 8; i > 0; i--)
    {
        setPolyFT4(poly);
        setSemiTrans(poly, 1);
        setRGB0(poly, 20, 20, 20);
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        poly++;
    }
}

int wolf2_GetSvecs(char *opt, SVECTOR *out)
{
    int count;

    count = 0;
    while ((opt = GCL_GetParamResult()))
    {
        GCL_StrToSV(opt, out);
        out++;
        count++;
    }

    return count;
}

void wolf2_GetSvec(char *opt, SVECTOR *out)
{
    opt = GCL_GetParamResult();
    if (opt)
    {
        GCL_StrToSV(opt, out);
    }
}

void wolf2_DrawLifebar(Wolf2Work *work)
{
    int cur;
    int life;
    int rest;
    int now;

    if (work->fA68 != 0)
    {
        return;
    }

    cur = MAX((work->fA40 / 8) * 8, 0);
    life = work->fA44;
    rest = life;
    now = cur;

    if (cur > life)
    {
        rest = cur;
        life = cur;
    }

    if (work->f9BC == 1 && life == cur)
    {
        if (work->fA50 >= 30)
        {
            return;
        }

        work->fA50++;
    }

    MENU_DrawBar(16, 28, rest, now, &work->lifebar);

    if (cur < life)
    {
        work->fA44 -= 8;
    }
}

void wolf2_SetLifebar(Wolf2Work *work)
{
    MENU_BAR_CONF *lifebar;

    work->fA44 = (work->fA40 / 8) * 8;

    memcpy(wolf2_800DD6B8, "WOLF", sizeof(wolf2_800DD6B8));
    lifebar = &work->lifebar;
    lifebar->name = wolf2_800DD6B8;
    lifebar->left[0] = 16;
    lifebar->left[1] = 111;
    lifebar->left[2] = 159;
    lifebar->right[0] = 31;
    lifebar->right[1] = 223;
    lifebar->right[2] = 127;
}

void wolf2_SetCamera(Wolf2Work *work)
{
    SVECTOR eye;
    SVECTOR center;
    SVECTOR pos;

    pos = GM_PlayerPosition;
    pos.vy = 2500;

    eye.vx = GM_PlayerPosition.vx / 2;
    eye.vy = 4000;
    eye.vz = GM_PlayerPosition.vz + 2000 + ABS(work->control.mov.vx - GM_PlayerPosition.vx) / 4;

    center.vx = (eye.vx * 15 + pos.vx) / 16;
    center.vy = (eye.vy * 15 + pos.vy) / 16;
    center.vz = (eye.vz * 15 + pos.vz) / 16;

    DG_LookAt(DG_Chanl(0), &eye, &center, 320);

    GM_Camera_800B77E8.field_2A = 0;
    GM_Camera_800B77E8.zoom = 320;
    gUnkCameraStruct2_800B7868.eye = eye;
    gUnkCameraStruct2_800B7868.center = center;
}

void wolf2_Act(Wolf2Work *work)
{
    SVECTOR  pos;
    CONTROL *control;
    int      yoff;
    int      shade;

    if (GM_GameOverTimer != 0 && work->fA58 == 0)
    {
        work->fA58 = 1;
        GM_StreamPlayStop();
    }

    if (work->fA58 == 0 && GM_StreamStatus() == 1)
    {
        GM_StreamPlayStop();
    }

    if (work->fA0C == 2)
    {
        wolf2_DrawLifebar(work);
    }

    if (work->fA0C == 1)
    {
        work->fA0C = 2;
        wolf2_SetLifebar(work);
        wolf2_DrawLifebar(work);
    }

    if (work->fA68 != 0)
    {
        work->control.mov.vx = 4201;
        work->control.mov.vz = -16766;
        work->control.rot.vy = 2048;
        work->control.turn.vy = 2048;
    }

    control = &work->control;
    if (work->f99C == 0)
    {
        control->step.vz = 0;
    }

    GM_ActControl(control);
    GM_ActObject2(&work->body);
    GM_ActObject2(&work->weapon);

    if (GM_CurrentItemId == IT_ThermG)
    {
        DG_AmbientObjs(work->body.objs);
    }
    else
    {
        DG_UnAmbientObjs(work->body.objs);
    }

    DG_GetLightMatrix2(&control->mov, work->light);

    if ((GV_Time % 64) == 0)
    {
        work->f7D8 = GV_RandU(2) + 1;
    }

    yoff = work->f7DC += work->f7D8;
    wolf2_InitTexcoords(&work->lsight_prim->packs[0]->poly_ft4, work->lsight_tex, yoff);
    wolf2_InitTexcoords(&work->lsight_prim->packs[1]->poly_ft4, work->lsight_tex, yoff);

    shade = work->body.objs->objs[4].screen.m[2][1] / 16;
    shade = MAX(shade, 1);
    shade = MIN(shade, 255);

    wolf2_SetTileShade(&work->f7E0->packs[0]->tiles, shade);
    wolf2_SetTileShade(&work->f7E0->packs[1]->tiles, shade);

    if (work->fA28 == 1 && GM_SnakeCurrentHealth != 0 && GM_GameOverTimer == 0)
    {
        GM_GameStatus |= STATE_PADRELEASE;

        wolf2_SetCamera(work);

        if (work->control.mov.vx > GM_PlayerPosition.vx)
        {
            GV_DemoPadStatus[0] = 0x2000;
        }
        else
        {
            GV_DemoPadStatus[0] = 0x8000;
        }
    }

    if (work->f9BC == 1)
    {
        if (work->f99C != 0)
        {
            if (GM_PlayerPosition.vz < -14000 && work->fA28 == 0)
            {
                GM_CurrentWeaponId = WP_None;
                GM_GameStatus |= (STATE_RADAR_OFF | STATE_MENU_OFF | STATE_LIFEBAR_OFF);

                if (GM_CurrentItemId != IT_Box1 &&
                    GM_CurrentItemId != IT_Box2 &&
                    GM_CurrentItemId != IT_Box3)
                {
                    GM_CurrentItemId = IT_None;
                }

                work->cinema_screen = NewCinemaScreen(2000000000, 0);
                work->fA28 = 1;

                if (work->control.mov.vx > GM_PlayerPosition.vx)
                {
                    work->f9D8 = 1;
                    work->f9DC = 1;
                }
                else
                {
                    work->f9D8 = -1;
                    work->f9DC = -1;
                }
            }
        }

        if (GV_DiffVec3(&work->control.mov, &GM_PlayerPosition) < work->f9D4 ||
            (work->f9DC == -1 && work->control.mov.vx > GM_PlayerPosition.vx) ||
            (work->f9DC == 1 && work->control.mov.vx <= GM_PlayerPosition.vx))
        {
            GM_GameStatus &= ~STATE_PADRELEASE;
            NewCinemaScreenClose(work->cinema_screen);
            work->cinema_screen = NULL;
            GV_DestroyActor(work);
        }
    }
    else
    {
        s12a_wolf2_800CED38(work);
    }

    if ((GV_Time % 128) == 0)
    {
        AN_Breath(&work->body.objs->objs[6].world);

        if (work->f6FC <= 0 && dword_8009F46C[0] == 1 && (GV_PadData_800B05C0[2].status & PAD_TRIANGLE))
        {
            pos.vx = (work->control.mov.vx - svector_8009F478.vx) / 3;
            pos.vy = 0;
            pos.vz = (work->control.mov.vz - svector_8009F478.vz) / 3;

            pos.vx = svector_8009F478.vx + pos.vx;
            pos.vy = svector_8009F478.vy + pos.vy;
            pos.vz = svector_8009F478.vz + pos.vz;

            GM_SeSet(&pos, 132);
        }
    }
}

int wolf2_GetResources2(Wolf2Work *work, int name, int where)
{
    SVECTOR     sp20[2];
    CONTROL    *control;
    char       *opt;
    int         i;
    OBJECT     *body;
    OBJECT     *weapon;
    DG_PRIM    *prim;
    DG_TEX     *tex;
    Wolf2Alloc *alloc;

    control = &work->control;

    work->f7D8 = 1;
    work->f7DC = 0;
    work->f7D4 = 1000;

    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlAttribute(control, RADAR_SIGHT | RADAR_VISIBLE);
    GM_ConfigControlHazard(control, -1, -1, -1);
    GM_ConfigControlInterp(control, 4);

    opt = GCL_GetOption('u');
    if (opt)
    {
        work->f7FC = GCL_StrToInt(opt);
    }
    else
    {
        work->f7FC = 1;
    }

    opt = GCL_GetOption('p');
    if (opt)
    {
        for (i = 0; i < work->f7FC; i++)
        {
            wolf2_GetSvec(opt, &work->f888[i]);
        }
    }
    else
    {
        for (i = 0; i < work->f7FC; i++)
        {
            work->f888[i] = DG_ZeroVector;
        }
    }

    opt = GCL_GetOption('m');
    if (opt)
    {
        for (i = 0; i < work->f7FC; i++)
        {
            opt = GCL_GetParamResult();
            if (opt)
            {
                work->f800[i] = GCL_StrToInt(opt);
            }
        }
    }
    else
    {
        for (i = 0; i < work->f7FC; i++)
        {
            work->f800[i] = 0;
        }
    }

    work->f724 = 300000;
    work->f6E0 = 5;

    opt = GCL_GetOption('h');
    if (opt)
    {
        work->f700 = GCL_StrToInt(opt);
    }
    else
    {
        work->f700 = 5;
    }

    work->f6FC = work->f700;
    if (work->f700 == -1)
    {
        work->fA68 = 1;
    }
    else
    {
        work->fA68 = 0;
    }

    work->fA6C = 0;

    body = &work->body;
    weapon = &work->weapon;

    opt = GCL_GetOption('k');
    if (opt)
    {
        work->f99C = GCL_StrToInt(opt);
    }
    else
    {
        work->f99C = 0;
    }

    if (work->f99C == 0)
    {
        GM_InitObject(body, BODY_DATA, BODY_FLAG, MOTION_DATA);
    }
    else
    {
        GM_InitObject(body, BODY_DATA2, BODY_FLAG, MOTION_DATA);
    }

    opt = GCL_GetOption('o');
    if (opt)
    {
        work->f9D0 = GCL_StrToInt(opt);
    }
    else
    {
        work->f9D0 = 17250;
    }

    opt = GCL_GetOption('c');
    if (opt)
    {
        work->f9C0 = GCL_StrToInt(opt);
        work->f9C4 = 1;
    }
    else
    {
        work->f9C0 = -1;
        work->f9C4 = 0;
    }

    opt = GCL_GetOption('j');
    if (opt)
    {
        work->f9E4 = GCL_StrToInt(opt);
    }
    else
    {
        work->f9E4 = -1;
    }

    opt = GCL_GetOption('r');
    if (opt)
    {
        wolf2_GetSvecs(opt, sp20);

        if (sp20[1].vy == 0)
        {
            work->control.mov = sp20[0];
            work->control.rot.vx = 0;
            work->control.rot.vy = sp20[1].vx;
            work->control.rot.vz = 0;
            work->control.turn = work->control.rot;
            work->f9BC = 1;
        }
        else
        {
            work->f6FC = sp20[1].vy;
        }
    }

    work->f9C8 = -1;
    work->fA48 = (1024 / work->f700) + 1;

    opt = GCL_GetOption('d');
    if (opt)
    {
        work->f9C8 = GCL_StrToInt(opt);
    }
    else
    {
        work->f9C8 = -1;
    }

    opt = GCL_GetOption('i');
    if (opt)
    {
        work->f9E0 = GCL_StrToInt(opt);
    }
    else
    {
        work->f9E0 = -1;
    }

    opt = GCL_GetOption('e');
    if (opt)
    {
        work->fA4C = GCL_StrToInt(opt);
    }
    else
    {
        work->fA4C = -1;
    }

    opt = GCL_GetOption('g');
    if (opt)
    {
        work->f9D4 = GCL_StrToInt(opt);
    }
    else
    {
        work->f9D4 = 5000;
    }

    opt = GCL_GetOption('q');
    if (opt)
    {
        work->f9E8 = GCL_StrToInt(opt);
    }
    else
    {
        work->f9E8 = 0;
    }

    GM_ConfigObjectJoint(body);
    GM_ConfigMotionControl(body, &work->m_ctrl, MOTION_DATA, work->m_segs, NULL, control, work->rots);
    GM_ConfigObjectLight(body, work->light);

    GM_InitObject(weapon, WEAPON_DATA, WEAPON_FLAG, 0);
    GM_ConfigObjectLight(weapon, work->light);
    GM_ConfigObjectRoot(weapon, body, 4);

    s12a_wolf2_800CED18(work);

    work->lsight_prim = prim = DG_GetPrim(DG_PRIM_LINE_FT2, 8, 0, work->lsight_verts, NULL);
    if (!prim)
    {
        return -1;
    }

    prim->field_2E_k500 = 2000;

    work->lsight_tex = tex = DG_GetTexture(GV_StrCode("lsight"));
    if (!tex)
    {
        return -1;
    }

    wolf2_InitTexpacks(&prim->packs[0]->poly_ft4, tex);
    wolf2_InitTexpacks(&prim->packs[1]->poly_ft4, tex);

    for (i = 16; i > 0; i--)
    {
        work->lsight_verts[i].vx = 0;
        work->lsight_verts[i].vy = -215;
        work->lsight_verts[i].vz = 32;
    }

    work->lsight_prim->n_prims = 8;

    work->f7E0 = prim = DG_GetPrim(DG_PRIM_OFFSET | DG_PRIM_TILE, 2, 0, work->f7E4, &wolf2_800C3490);
    if (!prim)
    {
        return -1;
    }

    wolf2_InitTiles(&prim->packs[0]->tiles);
    wolf2_InitTiles(&prim->packs[1]->tiles);

    prim->field_2E_k500 = 100;
    DG_VisiblePrim(prim);

    work->alloc = alloc = GV_Malloc(sizeof(Wolf2Alloc));
    if (!alloc)
    {
        return -1;
    }

    setDrawTPage(&alloc->tpage[0], 0, 1, getTPage(0, 1, 0, 0));
    setDrawTPage(&alloc->tpage[1], 0, 1, getTPage(0, 1, 0, 0));

    setTile(&alloc->tile[0]);
    setSemiTrans(&alloc->tile[0], 1);
    setXY0(&alloc->tile[0], -160, -112);
    setWH(&alloc->tile[0], 320, 224);

    alloc->tile[1] = alloc->tile[0];

    setRGB0(&alloc->tile[0], 0, 0, 0);
    setRGB0(&alloc->tile[1], 0, 0, 0);

    work->fA10 = DG_ZeroVector;

    if (work->fA68 != 0)
    {
        work->f9C0 = -1;
        work->f9E4 = -1;
        work->f9C8 = -1;
        work->fA4C = -1;
        work->f9E0 = -1;
    }

    return 0;
}

void wolf2_Die(Wolf2Work *work)
{
    Wolf2Alloc *alloc;

    GM_GameStatus &= ~STATE_PADRELEASE;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeObject(&work->weapon);
    GM_FreeTarget(work->f65C);
    GM_FreeTarget(work->f660);
    GM_FreePrim(work->lsight_prim);
    GM_FreePrim(work->f7E0);

    alloc = work->alloc;
    if (alloc)
    {
        GV_DelayedFree(alloc);
    }

    if (work->f9BC == 1 && work->f9C4 == work->f9BC)
    {
        wolf2_ExecProcC(work);
        return;
    }

    if (work->f9E4 != -1)
    {
        wolf2_ExecProcJ(work);
    }
}

int wolf2_CreateTargets(Wolf2Work *work)
{
    SVECTOR size;
    TARGET *target;

    size.vx = 250;
    size.vy = 1000;
    size.vz = 250;

    target = work->f65C = GM_AllocTarget();
    if (!target)
    {
        return -1;
    }

    GM_SetTarget(target, TARGET_FLAG, ENEMY_SIDE, &size);
    target->class |= TARGET_NO_LOCKON;

    work->f660 = target = GM_AllocTarget();
    if (!target)
    {
        return -1;
    }

    GM_SetTarget(target, TARGET_FLAG, ENEMY_SIDE, &size);
    target->class |= TARGET_NO_LOCKON;

    work->fA40 = 1024;
    return 0;
}

int wolf2_GetResources(Wolf2Work *work, int name, int where)
{
    int ticks;
    int i;

    ticks = mts_get_tick_count() % 256;
    for (i = 0; i < ticks; i++)
    {
        GV_RandU(4096);
    }

    work->f9AC = 0;
    work->f9AE = 0;
    work->f9B0 = 0;
    work->f9F0 = 0;
    work->fA58 = 0;

    if (wolf2_GetResources2(work, name, where) < 0)
    {
        return -1;
    }

    return 0;
}

void *NewWolf2(int name, int where)
{
    Wolf2Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Wolf2Work));
    if (work)
    {
        GV_SetNamedActor(work, wolf2_Act, wolf2_Die, "wolf2.c");

        if (wolf2_GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        if (wolf2_CreateTargets(work) < 0)
        {
            return NULL;
        }

    }

    return work;
}

void s12a_wolf2_800CECB4(Wolf2Work *work)
{
    CONTROL *control;

    work->f65C->class = TARGET_SEEK | TARGET_POWER | TARGET_AVAIL;
    work->f660->class = TARGET_SEEK | TARGET_POWER | TARGET_AVAIL;

    control = &work->control;
    control->height = work->body.height;

    if (work->f6BC < 0 && control->level_flag != 0)
    {
        work->f6BC = 0;
    }

    work->f6BC -= 16;
    control->step.vy = work->f6BC;
}

void s12a_wolf2_800CED18(Wolf2Work *work)
{
    s12a_wolf2_800D2E0C(work);
}

void s12a_wolf2_800CED38(Wolf2Work *work)
{
    s12a_wolf2_800D1EBC(work);
    s12a_wolf2_800CECB4(work);
}
