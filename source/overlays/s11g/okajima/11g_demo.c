#include "linkvar.h"
#include "bullet/blast.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "mts/mts.h"
#include "okajima/blurpure.h"
#include "okajima/red_alrt.h"

typedef struct _Work
{
    /* 0x0000 */ GV_ACT   actor;
    /* 0x0020 */ int      name;
    /* 0x0024 */ int      map;
    /* 0x0028 */ DG_PRIM *prim;
    /* 0x002C */ SVECTOR  vertices[1152];
    /* 0x242C */ int      f242C[18];
    /* 0x2474 */ OBJECT   objects[18];
    /* 0x347C */ MATRIX   light[2];
    /* 0x34BC */ int      f34BC[18];
    /* 0x3504 */ SVECTOR  f3504[18];
    /* 0x3594 */ SVECTOR  f3594[18];
    /* 0x3624 */ int      f3624[18];
    /* 0x366C */ int      f366C[18];
    /* 0x36B4 */ int      f36B4[288];
    /* 0x3B34 */ SVECTOR  f3B34;
    /* 0x3B3C */ SVECTOR  f3B3C;
    /* 0x3B44 */ SVECTOR  f3B44;
    /* 0x3B4C */ SVECTOR  f3B4C;
    /* 0x3B54 */ SVECTOR  f3B54;
    /* 0x3B5C */ SVECTOR  f3B5C;
    /* 0x3B64 */ char     pad3B64[8];
    /* 0x3B6C */ int      f3B6C;
    /* 0x3B70 */ int      f3B70;
    /* 0x3B74 */ int      f3B74;
    /* 0x3B78 */ int      f3B78;
    /* 0x3B7C */ int      f3B7C;
    /* 0x3B80 */ char     pad3B80[8];
    /* 0x3B88 */ int      f3B88;
    /* 0x3B8C */ int      proc_id;
    /* 0x3B90 */ int      f3B90;
    /* 0x3B94 */ int      last_time;
    /* 0x3B98 */ int      f3B98;
} Work;

#define EXEC_LEVEL  4

#define BODY_DATA   GV_StrCode("stn_fr")
#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

VECTOR body_scale = {4096, 4096, 4096};

extern GM_CAMERA        GM_Camera;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

void  NewAnime_8005E774(SVECTOR *pos);
void *NewBlastLine(int arg0, int arg1, int arg2, SVECTOR *arg3, SVECTOR *arg4);

void s11g_11g_demo_800CB41C(Work *work, POLY_FT4 *packs, int n_packs, DG_TEX *tex)
{
    int *f36B4;

    f36B4 = work->f36B4;
    while (--n_packs >= 0)
    {
        *f36B4++ = 0;

        setPolyFT4(packs);
        setSemiTrans(packs, 1);
        setRGB0(packs, 0, 0, 0);
        DG_SetPacketTexture4(packs, tex);
        packs->tpage |= (1 << 5);
        packs++;
    }
}

void s11g_11g_demo_800CB4B4(Work *work)
{
    POLY_FT4 *packs;
    int       i;
    int       shade;

    packs = work->prim->packs[GV_Clock];
    for (i = 0; i < 288; i++)
    {
        if (work->f36B4[i] <= 0)
        {
            work->f36B4[i] = 0;
            shade = 0;
        }
        else
        {
            shade = (work->f36B4[i] * 255) / 16;
            work->f36B4[i]--;
        }

        setRGB0(packs, shade, shade, shade);
        packs++;
    }
}

int s11g_11g_demo_800CB534(Work *work)
{
    DG_TEX  *tex;
    DG_PRIM *prim;

    tex = DG_GetTexture(GV_StrCode("plasma"));
    if (!tex)
    {
        return -1;
    }

    work->prim = prim = GM_MakePrim(DG_PRIM_POLY_FT4, 288, work->vertices, NULL);
    if (!prim)
    {
        return -1;
    }

    prim->raise = 200;

    s11g_11g_demo_800CB41C(work, prim->packs[0], 288, tex);
    s11g_11g_demo_800CB41C(work, prim->packs[1], 288, tex);
    return 0;
}

void s11g_11g_demo_800CB600(SVECTOR *a, SVECTOR *b, SVECTOR *out)
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

void s11g_11g_demo_800CB67C(SVECTOR *vec, SVECTOR *pos, int len)
{
    vec->vx = (vec->vx * (len - 1) + pos->vx) / len;
    vec->vy = (vec->vy * (len - 1) + pos->vy) / len;
    vec->vz = (vec->vz * (len - 1) + pos->vz) / len;
}

void s11g_11g_demo_800CB764(Work *work)
{    
    DG_LookAt(DG_Chanl(0), &work->f3B54, &work->f3B5C, 320);
    GM_Camera.field_2A = 0;
    GM_Camera.zoom = 320;
    gUnkCameraStruct2_800B7868.eye = work->f3B54;
    gUnkCameraStruct2_800B7868.center = work->f3B5C;
}

void s11g_11g_demo_800CB7FC(void)
{
    SVECTOR col0;
    SVECTOR col1;

    setVector(&col0, 64, 64, 64);
    setVector(&col1, 8, 8, 8);

    NewRedAlert2(0, 1, &col0, &col1, 1, 2);
}

void s11g_11g_demo_800CB858(SVECTOR *pos, int se_id)
{
    GM_SeSetMode(pos, se_id, GM_SEMODE_BOMB);
}

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_11g_demo_800CB878.s")
void s11g_11g_demo_800CB878(Work *, SVECTOR *, int);

void s11g_11g_demo_800CB994(Work *work)
{
    SVECTOR  sp18;
    SVECTOR  sp20;
    SVECTOR  sp28;
    SVECTOR  sp30;
    SVECTOR *var_s3;
    SVECTOR *sp38;
    OBJECT  *body;
    int     *sp3C;
    int     *sp40;
    int     *sp44;    
    int      i;
    int      temp;
    int      temp2;
    
    GM_CurrentMap = work->map;

    GM_GameStatus |= 0x4A0040;
    GM_GameStatus |= 0x10000000;

    if ((GV_Time % 16) == 0)
    {
        switch (work->f3B98)
        {
        case 0:
            s11g_11g_demo_800CB858(&work->f3B4C, 188);
            work->f3B98++;
            break;
        case 1:
            s11g_11g_demo_800CB858(&work->f3B4C, 193);
            work->f3B98++;
            break;
        case 2:
            s11g_11g_demo_800CB858(&work->f3B4C, 194);
            work->f3B98 = 0;
            break;
        }
    }

    switch (work->f3B6C)
    {
    case 0:
        work->f3B6C = 1;
        work->f3B70 = 150;

        work->f3B44.vx = 8000;
        work->f3B44.vy = 0;
        work->f3B44.vz = 8000;
        work->f3B4C.vx = -2000;
        work->f3B4C.vy = 1000;
        work->f3B4C.vz = 25500;
        work->f3B54.vx = 29000;
        work->f3B54.vy = 8000;
        work->f3B54.vz = 9000;

        work->f3B5C = work->f3B4C;

        s11g_11g_demo_800CB858(&work->f3B4C, 188);
        s11g_11g_demo_800CB858(&work->f3B4C, 190);
        /* fallthrough */
    case 1:
        if (work->f3B70 > 20)
        {
            GM_PadVibration = GV_RandU(2);
            GM_PadVibration2 = (work->f3B70 - 20) * 12;
        }

        if (((work->f3B70 % 4) == 0) && (work->f3B7C < 18))
        {
            work->f34BC[work->f3B7C] = 1;

            if (GV_RandU(4) == 0)
            {
                s11g_11g_demo_800CB858(&work->f3504[work->f3B7C], 180);
            }

            work->f242C[work->f3B7C] = 0;
            work->f3B7C++;
        }

        if (GV_RandU(128) == 0)
        {
            s11g_11g_demo_800CB858(&work->f3B4C, 189);
        }

        s11g_11g_demo_800CB67C(&work->f3B54, &work->f3B44, 32);
        s11g_11g_demo_800CB67C(&work->f3B5C, &work->f3B4C, 32);
        s11g_11g_demo_800CB764(work);
        
        if (work->f3B70 < 0)
        {
            work->f3B6C = 2;
            work->f3B70 = 50;
        }
        break;
    case 2:
        if (work->f3B70 > 20)
        {
            GM_PadVibration = GV_RandU(2);
            GM_PadVibration2 = (work->f3B70 - 20) * 12;
        }

        if (((work->f3B70 % 10) == 0) && (work->f3B7C < 18))
        {                    
            work->f34BC[work->f3B7C] = 1;
            s11g_11g_demo_800CB858(&work->f3504[work->f3B7C], 180);
            work->f242C[work->f3B7C] = 0;
            work->f3B7C++;
        }

        if (GV_RandU(128) == 0)
        {
            s11g_11g_demo_800CB858(&work->f3B4C, 189);
        }
        break;
    }

    var_s3 = work->f3504;
    sp38 = work->f3594;
    body = work->objects;
    sp3C = work->f34BC;
    sp40 = work->f3624;
    sp44 = work->f366C;

    sp20 = DG_ZeroVector;

    for (i = 0; i < 18;)
    {
        switch (*sp3C)
        {
        case 0:
            DG_InvisibleObjs(body->objs);
            break;
        case 1:
            DG_VisibleObjs(body->objs);
            
            sp20.vz = *sp40 + *sp44;

            temp = i / 2 + 10;
            *sp40 += temp;

            temp2 = i + 25;
            *sp44 += temp2;

            var_s3->vx += sp38->vx;
            var_s3->vy += sp38->vy;
            var_s3->vz += sp38->vz;

            sp30 = *var_s3;
            sp30.vx += sp38->vx;
            sp30.vy += sp38->vy;
            sp30.vz += sp38->vz;

            sp18.vx = (i * 10) + 60;
            sp18.vy = 0;
            sp18.vz = 0;

            DG_SetPos2(var_s3, &sp20);
            DG_PutVector(&sp18, var_s3, 1);
            NewAnime_8005E774(var_s3);

            sp20.vz = *sp40 + *sp44;

            DG_SetPos2(&sp30, &sp20);
            DG_PutVector(&sp18, &sp30, 1);

            sp30.vy -= 50;

            s11g_11g_demo_800CB600(&sp30, var_s3, &sp28);

            DG_SetPos2(&sp30, &sp28);
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
            s11g_11g_demo_800CB878(work, var_s3, i);

            if ((var_s3->vz < 27000) && ((var_s3->vy < 0) || (var_s3->vx < 0)))
            {
                *sp3C = 2;

                s11g_11g_demo_800CB7FC();
                GM_SeSet2(0, 63, 187);
                DG_InvisibleObjs(body->objs);
                                
                sp18.vx = ((i * 333) % 1024) - 512;
                sp18.vy = ((i * 433) % 2048) + 4000;
                sp18.vz = (i * 533) % 1024;

                sp20.vy = (i * 433) % 4096;

                DG_SetPos2(var_s3, &sp20);
                DG_PutVector(&sp18, (SVECTOR* ) &sp18, 1);
                NewBlastLine(4, 16, 4000, var_s3, &sp18);

                work->f3B90 = GV_RandU(16) + 20;
            }
            else if (var_s3->vx < -3000)
            {
                *sp3C = 2;

                s11g_11g_demo_800CB7FC();
                DG_InvisibleObjs(body->objs);

                sp18.vx = ((i * 483) % 1024) - 512;
                sp18.vy = ((i * 1983) % 1024) - 512;
                sp18.vz = 0;

                sp20.vy = (i * 483) % 4096;

                DG_SetPos2(var_s3, &sp20);
                DG_PutVector(&sp18, &sp18, 1);
                AN_Blast_Single(&sp18);
            }
            break;
        case 2:
            DG_InvisibleObjs(body->objs);
            
            if (GV_RandU(64) == 0)
            {
                GM_SeSet2(0, 63, 187);
            }
                
            if (GV_RandU(64) == 0)
            {
                GM_SeSet2(0, 63, 207);
            }
                
            if (GV_RandU(64) == 0)
            {
                GM_SeSet2(0, 63, 208);
            }

            if (GV_RandU(64) == 0)
            {
                GM_SeSet2(0, 63, 209);
            }

            if (GV_RandU(64) == 0)
            {
                GM_SeSet2(0, 63, 210);
            }

            if (GV_RandU(128) == 0)
            {
                GM_SeSet2(0, 63, SE_REB01);
            }

            if (GV_RandU(256) == 0)
            {
                GM_SeSet2(0, 63, SE_REBDRM01);
            }
            break;
        }

        i++;
        var_s3++;
        body++;
        sp38++;
        sp3C++;
        sp40++;
        sp44++;
    }

    s11g_11g_demo_800CB4B4(work);

    if (work->f3B90 > 0)
    {
        work->f3B90--;

        GM_PadVibration = GV_RandU(2);
        GM_PadVibration2 = (work->f3B90 * 255) / 42;
    }

    work->f3B88++;
    work->f3B70--;

    if ((mts_get_tick_count() - work->last_time) >= 8)
    {
        work->last_time = mts_get_tick_count();
        GM_SeSetMode(&work->f3B34, 181, 1);
    }
}

static void Die(Work *work)
{
    int i;

    GM_FreePrim(work->prim);

    for (i = 0; i < 18; i++)
    {
        GM_FreeObject(&work->objects[i]);
    }

    GM_GameStatus &= ~STATE_PADRELEASE;

    if (work->proc_id != -1)
    {
        GCL_ForceExecProc(work->proc_id, NULL);
    }
}

static int GetResources(Work *work, int name, int map)
{
    SVECTOR  sp10;
    SVECTOR  sp18[4];
    OBJECT  *body;
    int      i, j;
    SVECTOR *sp40;
    SVECTOR *sp44;
    int     *sp48;
    int     *sp4C;
    int     *sp50;
    int     *sp54;
    SVECTOR *var_s0;
    char    *opt;

    var_s0 = work->vertices;

    sp40 = work->f3504;
    sp44 = work->f3594;

    body = work->objects;

    sp48 = work->f34BC;
    sp4C = work->f3624;
    sp50 = work->f366C;
    sp54 = work->f36B4;

    GM_CurrentMap = map;

    work->name = name;
    work->map = map;

    work->f3B34.vx = 29000;
    work->f3B34.vy = 8000;
    work->f3B34.vz = 19000;

    work->f3B3C.vx = 0;
    work->f3B3C.vy = 2000;
    work->f3B3C.vz = 25500;

    for (i = 0; i < 18;)
    {
        GM_InitObject(body, BODY_DATA, BODY_FLAG, 0);
        GM_ConfigObjectJoint(body);
        GM_ConfigObjectLight(body, work->light);

        sp48[0] = 0;
        sp4C[0] = (i * 2345) % 4096;
        sp50[0] = (i * 3345) % 4096;
        sp54[0] = 0;

        *sp40 = work->f3B34;
        sp40->vx += (i * 345) % 256;
        sp40->vy += (i * 445) % 256;
        sp40->vz += (i * 545) % 256;

        work->f3B3C.vx += 444;
        work->f3B3C.vz -= 555;

        sp10 = work->f3B3C;

        sp10.vx += (i * 645) % 1024;
        sp10.vx -= 512;

        sp10.vy += (i * 645) % 1024;
        sp10.vy -= 512;

        sp10.vz += (i * 645) % 1024;
        sp10.vz -= 512;

        sp44->vx = (sp10.vx - sp40->vx) / (i + 50);
        sp44->vy = (sp10.vy - sp40->vy) / (i + 50);
        sp44->vz = (sp10.vz - sp40->vz) / (i + 50);

        sp18[0] = work->f3B34;
        sp18[1] = work->f3B34;

        sp18[2] = work->f3B34;
        sp18[2].vy -= 100;

        sp18[3] = work->f3B34;
        sp18[3].vy -= 100;

        for (j = 0; j < 16; j++)
        {
            *var_s0++ = sp18[0];
            *var_s0++ = sp18[1];
            *var_s0++ = sp18[2];
            *var_s0++ = sp18[3];
        }

        i++;
        sp40++;
        sp44++;
        body++;
        sp48++;
        sp4C++;
        sp54++;

        // BUG: missing increment
        // sp50++;
    }

    opt = GCL_GetOption('p');
    if (opt)
    {
        work->proc_id = GCL_StrToInt(opt);
    }
    else
    {
        work->proc_id = -1;
    }

    work->f3B88 = 0;
    work->f3B6C = 0;
    work->f3B70 = 0;
    work->f3B74 = 0;
    work->f3B78 = 0;
    work->f3B7C = 0;
    work->f3B90 = 0;

    GM_GameStatus |= STATE_PADRELEASE;

    GV_DemoPadStatus[0] = 0;
    GV_DemoPadStatus[1] = 0;

    GM_GameStatus |= ( STATE_RADAR_OFF | STATE_MENU_OFF | STATE_LIFEBAR_OFF | 0x40 );

    if (s11g_11g_demo_800CB534(work) < 0)
    {
        return -1;
    }

    NewBlurPure();

    if (GM_CurrentItemId == IT_Scope  ||
        GM_CurrentItemId == IT_Camera ||
        GM_CurrentItemId == IT_NVG    ||
        GM_CurrentItemId == IT_ThermG)
    {
        GM_CurrentItemId = IT_None;
    }

    if (GM_CurrentWeaponId == WP_Rifle ||
        GM_CurrentWeaponId == WP_Stinger)
    {
        GM_CurrentWeaponId = WP_None;
    }

    work->f3B98 = 0;

    s11g_11g_demo_800CB858(&work->f3B4C, 188);
    work->f3B98++;

    return 0;
}

void *NewStage11GDemo(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(work, s11g_11g_demo_800CB994, Die, "11g_demo.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
