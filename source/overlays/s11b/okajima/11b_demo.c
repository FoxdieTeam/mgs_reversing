#include "bullet/blast.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "okajima/red_alrt.h"
#include "takabe/fadeio.h"

#define N_OBJECTS       16
#define N_SEGMENTS      40
#define N_PACKS         (N_OBJECTS * N_SEGMENTS)

typedef struct _Work
{
    /* 0x0000 */ GV_ACT   actor;
    /* 0x0020 */ int      name;
    /* 0x0024 */ int      map;
    /* 0x0028 */ DG_PRIM *prim;
    /* 0x002C */ SVECTOR  vertices[N_PACKS * 4];
    /* 0x502C */ int      trail_count[N_OBJECTS];
    /* 0x506C */ OBJECT   objects[N_OBJECTS];
    /* 0x5EAC */ MATRIX   light[2];
    /* 0x5EEC */ int      state[N_OBJECTS];
    /* 0x5F2C */ SVECTOR  pos[N_OBJECTS];
    /* 0x5FAC */ SVECTOR  speed[N_OBJECTS];
    /* 0x602C */ int      rot1[N_OBJECTS];
    /* 0x606C */ int      rot2[N_OBJECTS];
    /* 0x60AC */ int      shade[N_PACKS];
    /* 0x6AAC */ SVECTOR  start;
    /* 0x6AB4 */ SVECTOR  goal;
    /* 0x6ABC */ SVECTOR  eye_goal;
    /* 0x6AC4 */ SVECTOR  center_goal;
    /* 0x6ACC */ SVECTOR  eye;
    /* 0x6AD4 */ SVECTOR  center;
    /* 0x6ADC */ char     pad6ADC[8];
    /* 0x6AE4 */ int      mode;
    /* 0x6AE8 */ int      timer;
    /* 0x6AEC */ int      f6AEC;
    /* 0x6AF0 */ int      f6AF0;
    /* 0x6AF4 */ char     pad6AF4[8];
    /* 0x6AFC */ int      count;
    /* 0x6B00 */ int      proc_id;
    /* 0x6B04 */ int      vibration;
    /* 0x6B08 */ int      se_index;
} Work;

#define BODY_DATA   GV_StrCode("stn_fr")
#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

VECTOR body_scale = {4096, 4096, 4096, 0};

void  NewAnime_8005E774(SVECTOR *pos);
void *NewBlastLine(int arg0, int arg1, int arg2, SVECTOR *arg3, SVECTOR *arg4);

static void InitPacks(Work *work, POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    int *shade;

    shade = work->shade;
    while (--n_packs >= 0)
    {
        *shade++ = 0;

        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, 0, 0, 0);
        DG_SetPacketTexture4(packs, tex);
        packs->tpage |= (1 << 5);
        packs++;
    }
}
static void UpdateShade(Work *work)
{
    POLY_FT4 *packs;
    int       i;
    int       shade;

    packs = work->prim->packs[GV_Clock];
    for (i = 0; i < N_PACKS; i++)
    {
        if (work->shade[i] <= 0)
        {
            work->shade[i] = 0;
            shade = 0;
        }
        else
        {
            shade = (work->shade[i] * 255) / N_SEGMENTS;
            work->shade[i]--;
        }

        setRGB0(packs, shade, shade, shade);
        packs++;
    }
}
static int InitPrim(Work *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    tex = DG_GetTexture(GV_StrCode("plasma"));
    if (!tex)
    {
        return -1;
    }

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, N_PACKS, work->vertices, NULL);
    if (!prim)
    {
        return -1;
    }

    prim->raise = 200;

    InitPacks(work, prim->packs[0], N_PACKS, tex);
    InitPacks(work, prim->packs[1], N_PACKS, tex);
    return 0;
}
static void GetRotation(SVECTOR *a, SVECTOR *b, SVECTOR *out)
{
    SVECTOR diff;
    int     dy;

    GV_SubVec3(b, a, &diff);
    out->vy = ratan2(diff.vx, diff.vz) & 0xFFF;

    dy = diff.vy;
    diff.vy = 0;

    out->vx = ratan2(GV_VecLen3(&diff), dy) & 0xFFF;
    out->vz = 0;
}
static void Approach(SVECTOR *vec, SVECTOR *pos, int len)
{
    vec->vx = (vec->vx * (len - 1) + pos->vx) / len;
    vec->vy = (vec->vy * (len - 1) + pos->vy) / len;
    vec->vz = (vec->vz * (len - 1) + pos->vz) / len;
}
static void SetCamera(Work *work)
{
    DG_MakeCameraMatrix(DG_Chanl(0), &work->eye, &work->center, 320);
    GM_Camera.interp_mode = 0;
    GM_Camera.zoom = 320;
    gUnkCameraStruct2_800B7868.position = work->eye;
    gUnkCameraStruct2_800B7868.target = work->center;
}
static void RedAlert(void)
{
    SVECTOR col0;
    SVECTOR col1;

    setVector(&col0, 32, 32, 32);
    setVector(&col1, 8, 8, 8);

    NewRedAlert2(0, 1, &col0, &col1, 1, 15);
}
static void PlaySound(SVECTOR *pos, int se_id)
{
    GM_SeSetMode(pos, se_id, GM_SEMODE_BOMB);
}

static void AddTrail(Work *work, SVECTOR *pos, int index)
{
    SVECTOR *verts;
    SVECTOR *prev;
    int      count;
    int      i;
    int      j;

    count = work->trail_count[index];
    i = index * N_SEGMENTS + count;
    work->shade[i] = N_SEGMENTS;
    j = i * 4;
    verts = &work->vertices[j];

    if (count == 0)
    {
        j = ((index + 1) * N_SEGMENTS - 1) * 4;
    }
    else
    {
        j -= 4;
    }

    prev = &work->vertices[j];

    if (++work->trail_count[index] >= N_SEGMENTS)
    {
        work->trail_count[index] = 0;
    }

    *verts++ = *pos;
    *verts++ = *prev;
    *verts = *pos;
    verts->vy -= 100;
    prev += 2;
    verts[1] = *prev;
}

static void Act(Work *work)
{
    SVECTOR  vec;
    SVECTOR  rot;
    SVECTOR  color;
    SVECTOR  rot2;
    SVECTOR  pos2;
    SVECTOR *pos;
    SVECTOR *speed;
    OBJECT  *body;
    int     *state;
    int     *rot1;
    int     *rot2p;
    int      i;
    int      temp;
    int      temp2;

    GM_CurrentMap = work->map;

    switch (work->mode)
    {
    case 0:
        GM_SeSet2(0, 63, 42);
        work->timer = 40;

        work->eye_goal.vx = 4045;
        work->eye_goal.vy = 1117;
        work->eye_goal.vz = 26881;

        work->center_goal.vx = -6287;
        work->center_goal.vy = 8057;
        work->center_goal.vz = 15429;

        work->mode = 1;

        work->eye = gUnkCameraStruct2_800B7868.position;
        work->center = gUnkCameraStruct2_800B7868.target;

        PlaySound(&work->center_goal, 190);
        /* fallthrough */
    case 1:
        if (work->timer > 20)
        {
            GM_PadVibration = GV_RandU(2);
            GM_PadVibration2 = (work->timer - 20) * 12;
        }

        if (GV_RandU(128) == 0)
        {
            PlaySound(&work->center_goal, 189);
        }

        Approach(&work->eye, &work->eye_goal, 8);
        Approach(&work->center, &work->center_goal, 8);

        if (work->timer < 0)
        {
            PlaySound(&work->center_goal, 190);

            work->mode = 2;
            work->timer = 90;

            work->center_goal.vx = -10418;
            work->center_goal.vy = 13712;
            work->center_goal.vz = 15869;

            work->eye_goal.vx = -11662;
            work->eye_goal.vy = 15703;
            work->eye_goal.vz = 29801;
        }
        break;

    case 2:
        if (GV_RandU(128) == 0)
        {
            PlaySound(&work->center_goal, 189);
        }

        Approach(&work->eye, &work->eye_goal, 16);
        Approach(&work->center, &work->center_goal, 16);

        work->eye_goal.vx -= 30;
        work->center_goal.vx += 50;
        work->eye_goal.vy -= 35;
        work->center_goal.vy -= 40;
        work->eye_goal.vz -= 100;
        work->center_goal.vz -= 100;

        if (work->timer < 0)
        {
            PlaySound(&work->center_goal, 190);

            work->mode = 3;
            work->timer = 41;

            work->center_goal = GM_PlayerPosition;

            work->eye_goal.vx = 9200;
            work->eye_goal.vy = 4000;
            work->eye_goal.vz = 29000;

            color.vx = 255;
            color.vy = 255;
            color.vz = 255;

            NewFadeInOut(2, 40);
        }
        break;

    case 3:
        Approach(&work->eye, &work->eye_goal, 16);
        Approach(&work->center, &work->center_goal, 8);

        if (work->timer < 0)
        {
            GV_DestroyActor(&work->actor);
        }
        break;
    }

    pos = work->pos;
    speed = work->speed;
    body = work->objects;
    state = work->state;
    rot1 = work->rot1;
    rot2p = work->rot2;

    rot = DG_ZeroVector;

    for (i = 0; i < N_OBJECTS;)
    {
        switch (*state)
        {
        case 0:
            DG_InvisibleObjs(body->objs);

            if (GV_RandU(32) == 0 || work->mode >= 3)
            {
                *state = 1;
                PlaySound(pos, 180);
                work->trail_count[i] = 0;

                switch (work->se_index)
                {
                case 0:
                    PlaySound(&work->center_goal, 188);
                    work->se_index++;
                    break;
                case 1:
                    PlaySound(&work->center_goal, 193);
                    work->se_index++;
                    break;
                case 2:
                    PlaySound(&work->center_goal, 194);
                    work->se_index = 0;
                    break;
                }
            }
            break;

        case 1:
            DG_VisibleObjs(body->objs);

            rot.vz = *rot1 + *rot2p;

            temp = i / 2 + 10;
            *rot1 += temp;

            temp2 = i + 25;
            *rot2p += temp2;

            pos->vx += speed->vx;
            pos->vy += speed->vy;
            pos->vz += speed->vz;

            pos2 = *pos;
            pos2.vx += speed->vx;
            pos2.vy += speed->vy;
            pos2.vz += speed->vz;

            vec.vx = i * 10 + 60;
            vec.vy = 0;
            vec.vz = 0;

            DG_SetPos2(pos, &rot);
            DG_PutVector(&vec, pos, 1);
            NewAnime_8005E774(pos);

            rot.vz = *rot1 + *rot2p;

            DG_SetPos2(&pos2, &rot);
            DG_PutVector(&vec, &pos2, 1);

            pos2.vy -= 50;

            GetRotation(&pos2, pos, &rot2);

            DG_SetPos2(&pos2, &rot2);
            GM_ActObject2(body);

            if (GV_RandU(2) != 0)
            {
                body->objs->light->t[0] = 255;
                body->objs->light->t[1] = 255;
                body->objs->light->t[2] = 255;
            }
            else
            {
                body->objs->light->t[0] = 128;
                body->objs->light->t[1] = 128;
                body->objs->light->t[2] = 128;
            }

            ScaleMatrix(&body->objs->world, &body_scale);
            AddTrail(work, pos, i);

            if (pos->vz < 6800 && pos->vx < 3000 && pos->vx > -5000)
            {
                *state = 2;

                RedAlert();
                DG_InvisibleObjs(body->objs);

                vec.vx = ((i * 1348) % 2048) + 4000;
                vec.vy = ((i * 1933) % 2048) + 4000;
                vec.vz = 0;

                rot.vy = (i * 1633) % 4096;

                DG_SetPos2(&DG_ZeroVector, &rot);
                DG_PutVector(&vec, &vec, 1);

                DG_SetPos2(pos, &rot2);
                DG_PutVector(&vec, &vec, 1);

                vec.vy -= 3000;
                NewBlastLine(4, 16, 3000, pos, &vec);

                work->vibration = GV_RandU(16) + 20;

                PlaySound(pos, 192);
                PlaySound(pos, 41);
            }
            else if (pos->vz < 6800)
            {
                *state = 2;

                RedAlert();
                DG_InvisibleObjs(body->objs);

                vec.vx = ((i * 1433) % 1024) - 512;
                vec.vy = ((i * 1133) % 1024) - 512;
                vec.vz = 0;

                rot.vy = (i * 1933) % 4096;

                DG_SetPos2(pos, &rot);
                DG_PutVector(&vec, &vec, 1);
                AN_Blast_Single(&vec);
            }
            break;

        case 2:
            DG_InvisibleObjs(body->objs);

            if (GV_RandU(64) == 0)
            {
                GM_SeSet2(0, 255, 187);
            }

            if (GV_RandU(128) == 0)
            {
                GM_SeSet2(0, 255, 39);
            }

            if (GV_RandU(256) == 0)
            {
                GM_SeSet2(0, 255, 40);
            }
            break;
        }

        i++;
        pos++;
        body++;
        speed++;
        state++;
        rot1++;
        rot2p++;
    }

    UpdateShade(work);

    if (work->vibration > 0)
    {
        work->vibration--;

        GM_PadVibration = GV_RandU(2);
        GM_PadVibration2 = (work->vibration * 255) / 42;
    }

    SetCamera(work);

    work->count++;
    work->timer--;
}
static void Die(Work *work)
{
    int i;

    GM_FreePrim(work->prim);

    for (i = 0; i < N_OBJECTS; i++)
    {
        GM_FreeObject(&work->objects[i]);
    }

    GM_GameStatus &= ~STATE_PADRELEASE;
    GCL_ForceExecProc(work->proc_id, NULL);
}
static int GetResources(Work *work, int name, int map)
{
    SVECTOR  goal;
    SVECTOR  verts[4];
    SVECTOR *vert;
    SVECTOR *pos;
    OBJECT  *body;
    SVECTOR *speed;
    int     *state;
    int     *rot1;
    int     *rot2;
    int     *shade;
    int      i, j;
    char    *opt;

    vert = work->vertices;
    pos = work->pos;
    speed = work->speed;
    body = work->objects;
    state = work->state;
    rot1 = work->rot1;
    rot2 = work->rot2;
    shade = work->shade;

    GM_CurrentMap = map;

    work->start.vx = -18000;
    work->start.vz = 26000;

    work->goal.vx = -3000;
    work->goal.vy = 4000;

    work->name = name;
    work->map = map;

    work->goal.vz = 5000;

    for (i = 0; i < N_OBJECTS;)
    {
        GM_InitObject(body, BODY_DATA, BODY_FLAG, 0);
        GM_ConfigObjectJoint(body);
        GM_ConfigObjectLight(body, work->light);

        *state = 0;
        *rot1 = (i * 633) % 4096;
        *rot2 = (i * 733) % 4096;
        *shade = 0;

        work->start.vx += i * 50;
        work->start.vy = ((i * 1433) % 4096) + 17000;

        *pos = work->start;

        goal = work->goal;
        goal.vx += (i * 1223) % 4096;
        goal.vx -= 2048;

        goal.vy += i * 512;

        goal.vz += (i * 1493) % 4096;
        goal.vz -= 2048;

        speed->vx = (goal.vx - pos->vx) / (i + 50);
        speed->vy = (goal.vy - pos->vy) / (i + 50);
        speed->vz = (goal.vz - pos->vz) / (i + 50);

        verts[0] = work->start;
        verts[1] = work->start;

        verts[2] = work->start;
        verts[2].vy -= 100;

        verts[3] = work->start;
        verts[3].vy -= 100;

        for (j = 0; j < N_SEGMENTS; j++)
        {
            *vert++ = verts[0];
            *vert++ = verts[1];
            *vert++ = verts[2];
            *vert++ = verts[3];
        }

        i++;
        pos++;
        speed++;
        body++;
        state++;
        rot1++;
        shade++;

        // BUG: missing increment
        // rot2++;
    }

    work->goal.vz = -30000;

    opt = GCL_GetOption('p');
    if (opt)
    {
        work->proc_id = GCL_StrToInt(opt);
    }

    work->count = 0;
    work->mode = 0;
    work->timer = 0;
    work->f6AEC = 0;
    work->f6AF0 = 0;
    work->vibration = 0;

    GM_GameStatus |= STATE_PADRELEASE;
    GM_GameStatus |= STATE_RADAR_OFF | STATE_MENU_DISABLE | STATE_LIFE_OFF;

    if (InitPrim(work) < 0)
    {
        return -1;
    }

    if (GM_Item == IT_Scope  ||
        GM_Item == IT_Camera ||
        GM_Item == IT_NVG    ||
        GM_Item == IT_ThermG)
    {
        GM_Item = IT_None;
    }

    if (GM_Weapon == WP_Rifle ||
        GM_Weapon == WP_Stinger)
    {
        GM_Weapon = WP_None;
    }

    work->se_index = 0;
    return 0;
}
void *NewStage11BDemo(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(work, Act, Die, "11b_demo.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

