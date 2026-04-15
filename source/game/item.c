#include "item.h"

#include <stdio.h>
#include <kernel.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "sound/g_sound.h"
#include "strcode.h"

extern unsigned short GM_ItemTypes[];

/*---------------------------------------------------------------------------*/

typedef struct ItemWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS body;
    char           unused[8];
    MATRIX         light[2];
    int            map;
    short          spin;         // y-axis spin per frame (4096 = 1.0)
    short          alive_time;   // item disappears once alive_time is 0, -1 = never disappears
    short          text_counter; // controls text position
    u_char         state;
    u_char         type;         // 0 = add item, 1 = add weapon, 2 = add ammo
    short          id;           // weapon or item ID
    short          num;          // number of items or bullets to add
    const char    *message;
    const char    *message_full;
    int            end_proc;
    LINE_F4        text_line[2]; // lines around the item text
    DG_PRIM       *shadow;
    SVECTOR        shadow_verts[4];
} ItemWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE \
                        | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

/*---------------------------------------------------------------------------*/

static int add_weapon(int id, int num)
{
    if (GM_Weapons[id] < 0)
    {
        GM_Weapons[id] = 0;
    }

    if (GM_Weapons[id] >= GM_WeaponsMax[id])
    {
        return 0;
    }

    GM_Weapons[id] += num;
    if (GM_Weapons[id] > GM_WeaponsMax[id])
    {
        GM_Weapons[id] = GM_WeaponsMax[id];
    }

    return 1;
}

static int add_ammo(int id, int num)
{
    if (GM_Weapons[id] < 0)
    {
        return 2;
    }

    if (GM_Weapons[id] >= GM_WeaponsMax[id])
    {
        return 0;
    }

    GM_Weapons[id] += num;
    if (GM_Weapons[id] > GM_WeaponsMax[id])
    {
        GM_Weapons[id] = GM_WeaponsMax[id];
    }

    return 1;
}

#define SET_ITEM_BIT(id, num) do { GM_Items[(id)] |= (1 << (num)); } while (0)

static int add_item(int id, int num)
{
    int max;

    if (id == 0xff)
    {
        enable_equipment();
        return 1;
    }

    if (GM_ItemTypes[id + 1] & ITEMTYPE_BITMASK)
    {
        SET_ITEM_BIT(id, num - 1);
        return 1;
    }

    if (GM_ItemTypes[id + 1] & ITEMTYPE_CONSUMABLE)
    {
        max = GM_Items[id + 11];

        if (GM_Items[id] >= max)
        {
            return 0;
        }

        if (GM_Items[id] < 0)
        {
            GM_Items[id] = 0;
        }

        GM_Items[id] += num;
        if (GM_Items[id] > max)
        {
            *(&GM_Items[id]) = max;
        }

        return 1;
    }

    GM_Items[id] = num;
    return 1;
}

void disable_equipment(void)
{
    int i;

    for (i = 0; i < IT_Max; i++)
    {
        GM_Items[i] |= ITEMTYPE_DISABLED;
    }

    for (i = 0; i < WP_Max; i++)
    {
        GM_Weapons[i] |= ITEMTYPE_DISABLED;
    }
}

void enable_equipment(void)
{
    int i;

    for (i = 0; i < IT_Max; i++)
    {
        if (GM_Items[i] != -1)
        {
            GM_Items[i] &= ~ITEMTYPE_DISABLED;
        }
    }

    for (i = 0; i < WP_Max; i++)
    {
        if (GM_Weapons[i] != -1)
        {
            GM_Weapons[i] &= ~ITEMTYPE_DISABLED;
        }
    }
}

static int in_pickup_range(ItemWork *work)
{
    SVECTOR vec;
    int     diff;

    if (!(work->map & GM_PlayerMap))
    {
        return 0;
    }

    vec = GM_PlayerPosition;

    diff = work->control.mov.vy - vec.vy;
    if (diff < 0)
    {
        diff = -diff;
    }

    if (diff > 1000)
    {
        return 0;
    }

    vec.vy = work->control.mov.vy;

    diff = work->control.mov.vx - vec.vx;
    if (abs(diff) > 500)
    {
        return 0;
    }

    diff = work->control.mov.vz - vec.vz;
    if (abs(diff) > 500)
    {
        return 0;
    }

    return 1;
}

static void init_pack(POLY_FT4 *poly, DG_TEX *tex)
{
    setPolyFT4(poly);
    setSemiTrans(poly, 1);
    DG_SetPacketTexture4(poly, tex);
}

static int world_to_screen(SVECTOR *out, SVECTOR *in)
{
    long z;

    gte_SetRotMatrix(&DG_Chanl(0)->eye_inv);
    gte_SetTransMatrix(&DG_Chanl(0)->eye_inv);

    gte_ldv0(in);
    gte_rtps();
    gte_stsxy(out);
    gte_stsz(&z);

    return z > 0;
}

static void Act(ItemWork *work)
{
    SVECTOR     screen_pos;
    SVECTOR     position;
    const char *message;
    CONTROL    *control;
    int         shake;
    int         state;
    int         dx, dy, dz;
    u_long     *ot;
    LINE_F4    *line;
    int         x, y;

    GM_SetCurrentMap(work->map);

    if (work->message_full)
    {
        if (world_to_screen(&screen_pos, &work->control.mov))
        {
            if (work->text_counter < 45)
            {
                message = work->message;
            }
            else
            {
                message = work->message_full;
            }

            if (work->text_counter < 16)
            {
                screen_pos.vy -= work->text_counter;
            }
            else
            {
                screen_pos.vy -= 16;
            }

            if (work->message_full != work->message)
            {
                MENU_Color(255, 48, 48);
            }
            else
            {
                MENU_Color(200, 200, 200);
            }

            MENU_Locate(screen_pos.vx + 160, screen_pos.vy + 104, 0x12);
            MENU_Printf(message);

            MENU_Color(1, 1, 1);
            MENU_Locate(screen_pos.vx + 161, screen_pos.vy + 105, 0x12);
            MENU_Printf(message);

            MENU_ResetText();
        }

        if (work->text_counter > 90)
        {
            if (work->state == 2)
            {
                GV_DestroyActor(&work->actor);
            }
            else if (in_pickup_range(work))
            {
                work->text_counter = 50;
            }
            else
            {
                work->message_full = NULL;
            }
        }

        work->text_counter++;

        if (work->state == 2)
        {
            return;
        }
    }

    if ((work->state == 0) && (work->body.objs->bound_mode == 0) && (work->alive_time <= 0))
    {
        return;
    }

    if (work->alive_time > 0)
    {
        /* blink once time left is low */
        if (--work->alive_time < 90)
        {
            if ((work->alive_time % 8) < 2)
            {
                DG_InvisibleObjs(work->body.objs);
            }
            else
            {
                DG_VisibleObjs(work->body.objs);
            }
        }

        if (work->alive_time == 0)
        {
            GV_DestroyActor(&work->actor);
            return;
        }
    }

    control = &work->control;

    if (work->spin > 73)
    {
        work->spin -= 10;
    }

    control->turn.vy += work->spin;
    control->turn.vy &= 4095;

    if (work->state == 1)
    {
        if ((control->level_flag != 0) && (control->step.vy < 0))
        {
            control->step.vy = -control->step.vy / 16;

            if (control->step.vy < 16)
            {
                GM_ConfigControlHazard(control, -1, -2, -1);
                control->step = DG_ZeroVector;
                work->state = 0;
            }
        }
        else
        {
            control->step.vy -= 16;
        }

        GM_ActControl(control);
    }
    else
    {
        GM_SetCurrentMap(control->map->index);

        if (work->message_full)
        {
            position = control->mov;
            shake = (90 - work->text_counter) * 8;

            if (shake > 80)
            {
                shake = 80;
            }

            if (GV_Clock & 1)
            {
                shake = -shake;
            }

            position.vx += shake;
            DG_SetPos2(&position, &control->turn);
        }
        else
        {
            DG_SetPos2(&control->mov, &control->turn);
        }
    }

    GM_ActObject2((OBJECT *)&work->body);
    DG_GetLightMatrix2(&control->mov, work->light);

    if (in_pickup_range(work) && (work->state != 1))
    {
        switch (work->type)
        {
        case 0:
            state = add_item(work->id, work->num);
            break;

        case 1:
            state = add_weapon(work->id, work->num);
            break;

        case 2:
            state = add_ammo(work->id, work->num);
            break;
        }

        switch (state)
        {
        case 1:
            DG_InvisibleObjs(work->body.objs);

            if (work->shadow)
            {
                DG_InvisiblePrim(work->shadow);
            }

            work->state = 2;
            work->text_counter = 0;
            work->message_full = work->message;

            GM_SeSet2(0, 63, SE_ITEM_GET);
            return;

        case 0:
            if (!work->message_full)
            {
                work->message_full = "FULL";
                work->text_counter = 0;
                GM_SeSet2(0, 63, SE_ITEM_FULL);
            }
            break;

        case 2:
            if (!work->message_full)
            {
                work->message_full = "GET WEAPON FIRST";
                work->text_counter = 0;
                GM_SeSet2(0, 63, SE_ITEM_FULL);
            }
            break;
        }
    }

    if (!work->message || work->message_full)
    {
        return;
    }

    if (!(GM_PlayerStatus & (PLAYER_INTRUDE | PLAYER_WATCH)) || (GM_GameStatus & (STATE_PADRELEASE | STATE_DEMO)))
    {
        work->text_counter = 0;
        return;
    }

    dx = GM_PlayerControl->mov.vx - control->mov.vx;
    if (dx < 0)
    {
        dx = -dx;
    }

    dy = GM_PlayerControl->mov.vy - control->mov.vy;
    if (dy < 0)
    {
        dy = -dy;
    }

    dz = GM_PlayerControl->mov.vz - control->mov.vz;
    if (dz < 0)
    {
        dz = -dz;
    }

    if ( (dx >= 2000) || (dy >= 2000) || (dz >= 2000) )
    {
        return;
    }

    if ((work->text_counter++ % 60) <= 20)
    {
        return;
    }

    ot = DG_ChanlOTag(1);
    line = &work->text_line[GV_Clock];

    if (!world_to_screen(&position, &control->mov))
    {
        return;
    }

    x = position.vx + 160;
    y = position.vy + 104;

    if ((y < -32) || (y > 300))
    {
        return;
    }

    if (y < 32)
    {
        y = 32;
    }

    if (y > FRAME_HEIGHT)
    {
        y = FRAME_HEIGHT;
    }

    line->x0 = x;
    line->x1 = x + 16;
    line->x2 = x + 16;

    line->y0 = y;
    line->y1 = y - 16;
    line->y2 = y - 16;
    line->y3 = y - 23;

    addPrim(ot, line);

    MENU_Color(200, 200, 200);
    MENU_Locate(line->x1 + 5, line->y1 - 8, 0x10);
    MENU_Printf("%s", work->message);

    MENU_Color(1, 1, 1);
    MENU_Locate(line->x1 + 6, line->y1 - 7, 0x10);
    line->x2 = line->x3 = MENU_Printf("%s", work->message) + 3;
}

/*---------------------------------------------------------------------------*/

static void Die(ItemWork *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->body);
    GM_FreePrim(work->shadow);

    if (work->state == 2 && work->end_proc != 0)
    {
        if (work->end_proc < 0)
        {
            GCL_ExecBlock((u_char *)work->end_proc, NULL);
        }
        else
        {
            GCL_ExecProc(work->end_proc, NULL);
        }
    }
}

/*---------------------------------------------------------------------------*/

static int check_type( ItemWork *work, int type )
{
    int id;

    id = work->id;
    if ( id == 0xff )
    {
        return 1;
    }

    work->type = 0;
    switch ( type )
    {
    case 2:
    case 3:
        if ( (GM_DifficultyFlag == DIFFICULTY_VERY_EASY) && (id == WP_Famas) )
        {
            return 0;
        }

        if ( id >= WP_Max )
        {
            return 0;
        }

        work->type = 2;
        break;

    case 0:
        if ( id >= WP_Max )
        {
            return 0;
        }

        work->type = 1;
        break;

    case 4:
        if ( id != IT_Ration )
        {
            return 0;
        }
        break;

    case 1:
    case 5:
        if ( id >= IT_Max )
        {
            return 0;
        }
        break;
    }

    return 1;
}

static int GetResources(ItemWork *work, int name, int where)
{
    CONTROL        *control;
    char           *pos;
    char           *dir;
    int             type;
    char           *opt;
    int             height;
    int             code;
    int             value;
    OBJECT_NO_ROTS *body;
    int             i;
    SVECTOR        *verts;
    DG_PRIM        *shadow;
    int             raise;
    DG_TEX         *tex;

    GM_SetCurrentMap(where);
    work->map = where;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);

    pos = GCL_GetOption('p');
    dir = GCL_GetOption('d');
    GM_ConfigControlString(control, pos, dir);

    control->step = DG_ZeroVector;
    control->skip_flag = CTRL_SKIP_TRAP | CTRL_SKIP_MESSAGE;

    opt = GCL_GetOption('b');
    if (opt)
    {
        type = GCL_StrToInt(opt);
    }
    else
    {
        type = 0;
    }

    opt = GCL_GetOption('i');
    if (!opt)
    {
        printf("NO ID ITEM\n");
        return -1;
    }

    work->id = GCL_StrToInt(opt);

    opt = GCL_GetOption('n');
    if (opt)
    {
        work->num = GCL_StrToInt(opt);
    }
    else
    {
        work->num = 1;
    }

    opt = GCL_GetOption('m');
    if (opt)
    {
        work->message = GCL_ReadString(opt);
    }

    work->message_full = NULL;

    height = 450;
    opt = GCL_GetOption('h');
    if (opt)
    {
        height = GCL_StrToInt(opt);
    }

    work->end_proc = 0;
    if (GCL_GetOption('e'))
    {
        work->end_proc = GCL_StrToInt(GCL_GetParamResult());
    }
    else if (GCL_GetOption('x'))
    {
        GCL_GetNextValue(GCL_GetParamResult(), &code, &value);
        work->end_proc = value;
    }

    if (!check_type(work, type))
    {
        return 0;
    }

    if ((GM_DifficultyFlag == DIFFICULTY_EXTREME) && (type == 4) && (work->id == IT_Ration))
    {
        return 0;
    }

    GV_ZeroMemory(work->unused, 8);

    body = &work->body;
    GM_InitObjectNoRots(body, KMD_BOX_01 + type, BODY_FLAG, 0);
    GM_ConfigObjectJoint((OBJECT *)body);
    GM_ConfigObjectLight((OBJECT *)body, work->light);
    GM_ConfigObjectStep((OBJECT *)body, &work->control.step);

    if (GCL_GetOption('v'))
    {
        work->body.objs[2].world.m[1][1] = -10000;
    }

    for (i = 0; i < 2; i++)
    {
        setLineF4(&work->text_line[i]);
        setRGB0(&work->text_line[i], 255, 255, 255);
    }

    if (height >= 0)
    {
        raise = 500;

        verts = work->shadow_verts;
        verts[0].vy = verts[1].vy = verts[2].vy = verts[3].vy = control->mov.vy;
        verts[0].vx = verts[2].vx = control->mov.vx + 256;
        verts[0].vz = verts[1].vz = control->mov.vz + 256;
        verts[1].vx = verts[3].vx = control->mov.vx - 256;
        verts[2].vz = verts[3].vz = control->mov.vz - 256;

        control->mov.vy += height;

        shadow = GM_MakePrim(DG_PRIM_ONEFACE | DG_PRIM_POLY_FT4, 1, work->shadow_verts, NULL);
        work->shadow = shadow;
        if (!shadow)
        {
            return -1;
        }

        shadow->raise = raise;

        tex = DG_GetTexture(GV_StrCode("shadow"));
        if (!tex)
        {
            return -1;
        }

        init_pack(shadow->packs[0], tex);
        init_pack(shadow->packs[1], tex);

        setRGB0((POLY_FT4 *)shadow->packs[0], 80, 80, 80);
        setRGB0((POLY_FT4 *)shadow->packs[1], 80, 80, 80);
    }
    else
    {
        work->shadow = NULL;
    }

    GM_ActControl(control);
    GM_ActObject2((OBJECT *)body);
    return 1;
}

/*---------------------------------------------------------------------------*/

void *NewItem(int name, int where, int argc, char **argv)
{
    ItemWork *work;
    int       inited;

    work = GV_NewActor(EXEC_LEVEL, sizeof(ItemWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "item.c");
        work->state = 0;

        inited = GetResources(work, name, where);
        if (inited > 0)
        {
            work->alive_time = -1;
            work->map = where;
            fprintf(1, "Item map = %d\n", where);
            work->spin = 64;
        }
        else
        {
            GV_DestroyActor(&work->actor);

            if (inited == 0)
            {
                return work;
            }
            else
            {
                return NULL;
            }
        }
    }

    return work;
}

/*---------------------------------------------------------------------------*/

static int GetResourcesPut(ItemWork *work, SVECTOR *pos, SVECTOR *step, Item_Info *info, int where)
{
    int      type;
    CONTROL *control;
    int      i;

    type = info->type;

    work->id = info->id;
    work->num = info->num;
    work->message = info->message;
    work->end_proc = 0;

    if (!check_type(work, type))
    {
        return -1;
    }

    control = &work->control;
    if (GM_InitControl(control, HASH_ITEM, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, 100, 500, 500);
    GM_ConfigControlInterp(control, 0);

    control->skip_flag = CTRL_SKIP_TRAP | CTRL_SKIP_MESSAGE;
    control->step = *step;
    control->step.vy = 160;
    control->mov = *pos;

    GM_InitObjectNoRots(&work->body, KMD_BOX_01 + type, BODY_FLAG, 0);
    GM_ConfigObjectJoint((OBJECT *)&work->body);
    GM_ConfigObjectLight((OBJECT *)&work->body, work->light);
    GM_ConfigObjectStep((OBJECT *)&work->body, &control->step);

    for (i = 0; i < 2; i++)
    {
        setLineF4(&work->text_line[i]);
        setRGB0(&work->text_line[i], 255, 255, 255);
    }

    return 0;
}

void *NewItemPut(SVECTOR *pos, SVECTOR *step, Item_Info *info)
{
    ItemWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(ItemWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "item.c");

        if (GetResourcesPut(work, pos, step, info, GM_CurrentMap) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->alive_time = info->time;
        work->map = GM_CurrentMap;
        work->state = 1;
        work->spin = 512;

        GM_SeSet2(0, 63, SE_SPAWN_ITEM);
    }

    return work;
}
