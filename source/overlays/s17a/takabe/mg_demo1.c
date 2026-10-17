#include "mgstype.h"
#include "linkvar.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/camera.h"
#include "takabe/thing.h"

/* First person view from the Metal Gear REX cockpit (Snake piloting REX) */

typedef struct _Work
{
    GV_ACT         actor;
    int            where;           // 0x20
    int            name;            // 0x24
    int            time;            // 0x28
    int            time2;           // 0x2C
    int            pad_30[2];
    int            se_timer;        // 0x38
    int            voice;           // 0x3C
    int            status;          // 0x40
    int            dx;              // 0x44
    int            dy;              // 0x48
    int            rot;             // 0x4C
    int            yaw;             // 0x50
    int            item;            // 0x54
    int            weapon;          // 0x58
    CONTROL        control;         // 0x5C
    OBJECT         body;            // 0xD8
    MOTION_CONTROL m_ctrl;          // 0x1BC
    MOTION_SEGMENT m_segs[17];      // 0x20C
    SVECTOR        rots[17];        // 0x470
    MATRIX         light[2];        // 0x4F8
    TARGET        *target;          // 0x538
    int            proc;            // 0x53C
} Work;

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

extern CONTROL *tenage_ctrls_800BDD30[16];
extern int      tenage_ctrls_count_800BDD70;
extern int      DG_UnDrawFrameCount;

void GM_CheckShukanReverse(unsigned short *pInput);
void GM_CheckShukanReverseAnalog(unsigned char *pInput);
int  GM_StreamStatus(void);
void Voicesys_800CE2D0(void);
void Voicesys_800CE310(void);

/* vulcan sound effects, the last entry is the one played last */
unsigned char mg_demo1_se_table1[4] = {0x88, 0x89, 0x8A, 0x00};
unsigned char mg_demo1_se_table2[4] = {0x84, 0x85, 0x87, 0x00};
SVECTOR       mg_demo1_target_size = {500, 500, 500};

static void ReadPad(Work *work)
{
    int status;
    int dy;
    int dx;

    dy = 0;
    status = GV_PadData[0].status;
    dx = 0;

    if (GV_PadData[0].analog == 2)
    {
        dy = GV_PadData[0].left_dy;
        dx = GV_PadData[0].left_dx;

        if (dx >= 128)
        {
            dx -= 192;
            if (dx < 0)
            {
                dx = 0;
            }
        }
        else
        {
            dx -= 64;
            if (dx > 0)
            {
                dx = 0;
            }
        }

        if (dy >= 128)
        {
            dy -= 192;
            if (dy < 0)
            {
                dy = 0;
            }
        }
        else
        {
            dy -= 64;
            if (dy > 0)
            {
                dy = 0;
            }
        }

        dx *= 2;
        dy *= 2;
    }

    if (dx == 0 && dy == 0)
    {
        if (status & PAD_LEFT)
        {
            dx = -128;
        }

        if (status & PAD_RIGHT)
        {
            dx = 127;
        }

        if (status & PAD_UP)
        {
            dy = -128;
        }

        if (status & PAD_DOWN)
        {
            dy = 127;
        }
    }

    if (GM_PlayerStatus & 1)
    {
        GM_CheckShukanReverse((unsigned short *)&status);
        dy += 128;
        GM_CheckShukanReverseAnalog((unsigned char *)&dy);
        dy -= 128;
    }

    work->dx = dx;
    work->status = status;
    work->dy = dy;
}

static void Act(Work *work)
{
    int se;
    int stream;
    int pitch;
    int yaw;

    se = 0;
    ReadPad(work);

    work->time++;
    work->time2++;

    pitch = GM_PlayerControl->turn.vx;
    pitch += work->dy / 4;
    if (pitch > -100)
    {
        pitch = -100;
    }
    if (pitch < -400)
    {
        pitch = -400;
    }
    GM_PlayerControl->turn.vx = pitch;

    yaw = work->yaw;
    yaw -= work->dx / 4;
    if (yaw > 150)
    {
        yaw = 150;
    }
    if (yaw < -150)
    {
        yaw = -150;
    }
    work->yaw = yaw;

    GM_PlayerControl->turn.vy = work->rot + work->yaw;

    stream = GM_StreamStatus();
    if (stream == 2)
    {
        if ((GV_PadData[0].release & PAD_SQUARE) && work->se_timer == 0)
        {
            if (GM_StingerFlag <= 0)
            {
                switch (GV_RandU(2))
                {
                case 0:
                    se = mg_demo1_se_table1[0];
                    mg_demo1_se_table1[0] = mg_demo1_se_table1[3];
                    mg_demo1_se_table1[3] = se;
                    break;

                case 1:
                    se = mg_demo1_se_table1[1];
                    mg_demo1_se_table1[1] = mg_demo1_se_table1[3];
                    mg_demo1_se_table1[3] = se;
                    break;
                }
            }
            else
            {
                switch (GV_RandU(2))
                {
                case 0:
                    se = mg_demo1_se_table2[0];
                    mg_demo1_se_table2[0] = mg_demo1_se_table2[3];
                    mg_demo1_se_table2[3] = se;
                    break;

                case 1:
                    se = mg_demo1_se_table2[1];
                    mg_demo1_se_table2[1] = mg_demo1_se_table2[3];
                    mg_demo1_se_table2[3] = se;
                    break;
                }
            }

            GM_SeSet(NULL, se);
            work->se_timer = 60;
        }
    }
    else if (work->time < 30)
    {
        if (work->time == 20)
        {
            GV_PadMask = 0xF080;
            GM_PlayerStatus |= 0x20000000;
        }

        if (work->time < 5)
        {
            GM_PlayerControl->rot.vy = work->rot;
            GM_PlayerControl->turn.vy = work->rot;
            DG_InvisibleObjs(GM_PlayerBody->objs);
            GM_NoisePower = 0;
            GM_NoiseLength = 0;
        }

        if (work->time == 3)
        {
            GV_PadMask = 0;
            GM_GameStatus = (GM_GameStatus & ~(STATE_PAUSE_ONLY | STATE_PADRELEASE)) | STATE_PADMASK | 0x1000;
            work->weapon = GM_Weapon;
            GM_Weapon = 4;
            work->item = GM_Item;
            GM_Item = -1;
        }
    }
    else if (work->voice == 0 && stream == 1)
    {
        Voicesys_800CE2D0();
        work->voice = stream;
        GM_GameStatus &= ~STATE_DEMO;
    }
    else if (work->voice == 1 && stream == -1 && work->proc != 0)
    {
        GV_PadMask = 0;
        DG_UnDrawFrameCount = 8;
        GM_Item = work->item;
        GM_PlayerStatus &= ~0x20000000;
        GM_Weapon = work->weapon;
        GM_GameStatus &= ~0x1000;
        GCL_ExecProc(work->proc, NULL);
        GV_PadData[0].status = 0;
        GV_PadData[0].press = 0;
        GV_PadData[0].release = 0;
        Voicesys_800CE310();
        GV_DestroyActor(work);
        return;
    }

    if (work->se_timer != 0)
    {
        work->se_timer--;
    }

    DG_GetLightMatrix2(&work->control.mov, work->light);
    GM_ActMotion(&work->body);
}

static void Die(Work *work)
{
    GM_FreeTarget(work->target);
    GM_FreeObject(&work->body);
    GM_FreeControl(&work->control);
}

static int GetResources(Work *work, int name, int where)
{
    CONTROL  *control;
    OBJECT   *body;
    TARGET   *target;
    CONTROL **tenage;
    int       i;

    if (GCL_GetOption('e'))
    {
        work->proc = GCL_StrToInt(GCL_NextStr());
    }

    GM_PlayerStatus = 0;
    GV_PadMask = 0;
    GV_PadData[0].release = 0;
    GV_PadData[0].press = 0;
    GM_PlayerStance = 0;
    GV_PadData[0].status = 0;
    GM_GameStatus |= (STATE_PAUSE_ONLY | STATE_PADRELEASE | STATE_PADMASK);
    GM_Camera.first_person = 2;

    work->rot = THING_Gcl_GetInt('r');

    control = &work->control;
    GM_InitControl(control, 1, where);
    GM_ConfigControlHazard(control, 0, -2, 0);

    if (GCL_GetOption('n'))
    {
        GCL_StrToSV(GCL_NextStr(), (short *)&control->mov);
        GCL_StrToSV(GCL_NextStr(), (short *)&control->turn);
        control->rot = control->turn;
    }

    body = &work->body;

    GM_InitObject(body, 0x7571, BODY_FLAG, 0);
    GM_ConfigMotionControl(body, &work->m_ctrl, 0xC2C9, work->m_segs, work->m_segs, control, work->rots);
    GM_ConfigObjectLight(body, work->light);
    GM_ConfigObjectAction(body, 0, 0, 0);
    GM_ActMotion(body);

    control->mov.vy += body->height;
    GM_ActControl(control);
    GM_ActObject(body);

    target = GM_AllocTarget();
    work->target = target;
    GM_SetTarget(target, TARGET_POWER, ENEMY_SIDE, &mg_demo1_target_size);
    GM_MoveTarget(target, &control->mov);

    if (tenage_ctrls_count_800BDD70 != 0)
    {
        tenage = tenage_ctrls_800BDD30;
        for (i = 16; i > 0; i--)
        {
            if (*tenage)
            {
                (*tenage)->mov.pad = 1;
            }
            tenage++;
        }
    }

    GM_NoisePower = 0;
    GM_NoiseLength = 0;
    return 0;
}

void *NewMgDemo1(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "mg_demo1.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        work->where = where;
        work->name = name;
    }

    return (void *)work;
}
