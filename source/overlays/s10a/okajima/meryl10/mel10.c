#include <stdio.h>
#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "linkvar.h"
#include "menu/menuman.h"
#include "takabe/fadeio.h"

// Bloody Meryl (after Wolf shot her). The work layout follows Wolf2Work up
// to the targets, so the wolf action code (okajima/wolf/action.c) drives her.
typedef struct _Work
{
    GV_ACT         actor;
    int            map;          /* 0x20 */
    CONTROL        control;      /* 0x24 */
    OBJECT         body;         /* 0xA0 */
    char           pad184[0xE4]; /* 0x184 (weapon in Wolf2Work) */
    MOTION_CONTROL m_ctrl;       /* 0x268 */
    MOTION_SEGMENT m_segs[17];   /* 0x2B8 */
    SVECTOR        rots[16];     /* 0x51C */
    SVECTOR        adjust[16];   /* 0x59C */
    MATRIX         light[2];     /* 0x61C */
    TARGET        *target;       /* 0x65C */
    TARGET        *target2;      /* 0x660 */
    HOMING        *hom;          /* 0x664 */
    MATRIX         hom_mat;      /* 0x668 */
    int            f688;         /* 0x688 */
    int            fall;         /* 0x68C */
    int            f690;         /* 0x690 */
    char           pad694[0x8];
    int            fade;         /* 0x69C */
    int            f6A0;         /* 0x6A0 */
    int            f6A4;         /* 0x6A4 */
    int            f6A8;         /* 0x6A8 */
    int            f6AC;         /* 0x6AC */
    int            f6B0;         /* 0x6B0 */
    SVECTOR        shadow_verts[4]; /* 0x6B4 */
    DG_PRIM       *shadow_prim;  /* 0x6D4 */
    char           pad6D8[0x14];
    int            voices[33];   /* 0x6EC */
    int            f770;         /* 0x770 */
    int            f774;         /* 0x774 */
    int            state;        /* 0x778 */
    int            timer;        /* 0x77C */
    int            f780;         /* 0x780 */
    int            f784;         /* 0x784 */
    int            f788;         /* 0x788 */
    int            f78C;         /* 0x78C */
    MENU_BAR_CONF  lifebar;      /* 0x790 */
    int            life_rest;    /* 0x79C */
    int            life;         /* 0x7A0 */
    int            life_ratio;   /* 0x7A4 */
    int            f7A8;         /* 0x7A8 */
    int            f7AC;         /* 0x7AC */
    int            stream_stop;  /* 0x7B0 */
    int            f7B4;         /* 0x7B4 */
} Work;

// in okajima/wolf/action.c (they take a Wolf2Work)
void s12a_wolf2_800D37A8( Work *work );
void wolf2_800D3D54( Work *work );

SVECTOR mel10_shadow_offsets[2] = {
    {  500, 0, 1000, 0 },
    { -500, 0, 1000, 0 }
};

SVECTOR mel10_target_size = { 500, 500, 500, 0 };

static char SECTION(".bss") mel10_name[16];

int s10a_mel10_800DC488( char *opt, SVECTOR *out )
{
    int   count;
    char *res;

    count = 0;

    while ( ( res = GCL_NextStr() ) != NULL )
    {
        GCL_StrToSV( res, (short *)out );
        out++;
        count++;
    }

    return count;
}

void s10a_mel10_800DC4DC( char *opt, int *out )
{
    char *res;

    while ( ( res = GCL_NextStr() ) != NULL )
    {
        *out = GCL_StrToInt( res );
        out++;
    }
}

void s10a_mel10_800DC520( Work *work )
{
    SVECTOR  diff;
    SVECTOR  rot;
    SVECTOR  pos;
    SVECTOR  offsets[2];
    SVECTOR *verts;

    rot = work->control.rot;
    rot.vy -= 512;

    pos = DG_ZeroVector;
    pos.vz = -150;

    DG_SetPos2( &DG_ZeroVector, &rot );
    DG_PutVector( mel10_shadow_offsets, offsets, 2 );
    DG_PutVector( &pos, &pos, 1 );
    verts = work->shadow_verts;
    GV_SubVec3( &work->control.mov, &pos, &diff );

    verts[0].vx = diff.vx + offsets[0].vx;
    verts[3].vx = diff.vx - offsets[0].vx;
    verts[0].vz = diff.vz + offsets[0].vz;
    verts[3].vz = diff.vz - offsets[0].vz;
    verts[1].vx = diff.vx + offsets[1].vx;
    verts[2].vx = diff.vx - offsets[1].vx;
    verts[1].vz = diff.vz + offsets[1].vz;
    verts[2].vz = diff.vz - offsets[1].vz;

    verts[0].vy = verts[1].vy = verts[2].vy = verts[3].vy = diff.vy - work->control.height;
}

void s10a_mel10_800DC6AC( POLY_FT4 *poly, DG_TEX *tex )
{
    setPolyFT4( poly );
    setSemiTrans( poly, 1 );
    DG_SetPacketTexture4( poly, tex );
}

void s10a_mel10_800DC70C( Work *work )
{
    int now;
    int rest;

    work->life = ( GM_VitalityMax * work->life_ratio ) / 256;

    now = ( work->life / 8 ) * 8;
    if ( now < 0 )
    {
        now = 0;
    }

    rest = work->life_rest;
    if ( rest < now )
    {
        rest = now;
    }

    MENU_DrawBar2( 40, rest, now, GM_VitalityMax, &work->lifebar );

    if ( now < rest )
    {
        work->life_rest -= 8;
    }
}

void s10a_mel10_800DC7D4( Work *work )
{
    MENU_BAR_CONF *lifebar;

    strcpy( mel10_name, "MERYL" );
    lifebar = &work->lifebar;
    lifebar->name = mel10_name;
    lifebar->left[0] = 31;
    lifebar->left[1] = 191;
    lifebar->left[2] = 95;
    lifebar->right[0] = 31;
    lifebar->right[1] = 191;
    lifebar->right[2] = 95;
    lifebar->height = 1;
}

void s10a_mel10_800DD1AC( Work *work );

void s10a_mel10_800DC844( Work *work )
{
    CONTROL *control;

    if ( work->voices[0] != -1 )
    {
        if ( GM_GameOverTimer != 0 && work->stream_stop == 0 )
        {
            work->stream_stop = 1;
            GM_StreamPlayStop();
        }

        if ( work->stream_stop == 0 && GM_StreamStatus() == 1 )
        {
            GM_StreamPlayStop();
        }
    }

    control = &work->control;
    GM_CurrentMap = work->map;
    s10a_mel10_800DC70C( work );

    if ( work->fade <= 256 - work->life_ratio )
    {
        work->fade++;

        if ( work->f7A8 != 0 )
        {
            work->fade = 255;
            work->life_rest = work->life = ( GM_VitalityMax * work->life_ratio ) / 256;
            work->target->vital = 0x400;
        }
        else
        {
            work->life = ( GM_VitalityMax * ( 256 - work->fade ) ) / 256;
            work->target->vital = 0x400;
        }
    }

    s10a_mel10_800DD1AC( work );
    s10a_mel10_800DC520( work );

    if ( work->state == 0 )
    {
        GM_ActControl( control );
        GM_ActObject2( &work->body );

        if ( GM_Item == IT_ThermG )
        {
            DG_AmbientObjs( work->body.objs );
        }
        else
        {
            DG_UnAmbientObjs( work->body.objs );
        }

        DG_GetLightMatrix2( &control->mov, work->light );
    }

    if ( work->state == 1 )
    {
        work->state = 2;
    }

    if ( work->state == 2 )
    {
        work->state = 3;
        work->timer = 30;
        NewFadeInOut( 0, 20 );
    }

    if ( work->state == 3 && work->timer-- < 0 )
    {
        GV_DestroyActor(work);
    }
}

void s10a_mel10_800DD18C( Work *work );

int s10a_mel10_800DCA7C( Work *work, int name, int where )
{
    CONTROL *control;
    OBJECT  *body;
    char    *opt;
    DG_PRIM *prim;
    DG_TEX  *tex;

    control = &work->control;

    work->map = where;
    GM_CurrentMap = where;
    work->f7B4 = 0;

    if ( GM_InitControl( control, name, where ) < 0 )
    {
        return -1;
    }

    GM_ConfigControlAttribute( control, 5 );
    GM_ConfigControlHazard( control, -1, -2, -1 );
    GM_ConfigControlInterp( control, 4 );

    opt = GCL_GetOption( 'm' );
    if ( opt )
    {
        work->f7A8 = GCL_StrToInt( opt );
    }
    else
    {
        work->f7A8 = 0;
    }

    opt = GCL_GetOption( 'h' );
    if ( opt )
    {
        work->life_ratio = GCL_StrToInt( opt );
    }
    else
    {
        work->life_ratio = 128;
    }

    opt = GCL_GetOption( 'c' );
    if ( opt )
    {
        work->f7AC = GCL_StrToInt( opt );
    }
    else
    {
        work->f7AC = 10;
    }

    opt = GCL_GetOption( 'p' );
    if ( opt )
    {
        s10a_mel10_800DC488( opt, &work->control.mov );
    }

    opt = GCL_GetOption( 'd' );
    if ( opt )
    {
        s10a_mel10_800DC488( opt, &work->control.turn );
        work->control.rot = work->control.turn;
    }

    opt = GCL_GetOption( 'v' );
    if ( opt )
    {
        s10a_mel10_800DC4DC( opt, work->voices );
    }
    else
    {
        work->voices[0] = -1;
    }

    opt = GCL_GetOption( 'n' );
    if ( opt )
    {
        work->f780 = GCL_StrToInt( opt );
    }

    opt = GCL_GetOption( 'o' );
    if ( opt )
    {
        work->f784 = GCL_StrToInt( opt );
    }
    else
    {
        work->f784 = -1;
    }

    opt = GCL_GetOption( 'a' );
    if ( opt )
    {
        work->f788 = GCL_StrToInt( opt );
    }
    else
    {
        work->f788 = -1;
    }

    opt = GCL_GetOption( 'b' );
    if ( opt )
    {
        work->f78C = GCL_StrToInt( opt );
    }
    else
    {
        work->f78C = -1;
    }

    body = &work->body;
    GM_InitObject( body, GV_StrCode( "mel_wlf" ), 0x22D, GV_StrCode( "mel10ad" ) );
    GM_ConfigObjectJoint( body );
    GM_ConfigMotionControl( body, &work->m_ctrl, GV_StrCode( "mel10ad" ), work->m_segs, NULL, control, work->rots );
    GM_ConfigObjectLight( body, work->light );

    s10a_mel10_800DD18C( work );
    s10a_mel10_800DC520( work );

    prim = DG_MakePrim( DG_PRIM_POLY_FT4, 1, 0, work->shadow_verts, NULL );
    if ( prim != NULL )
    {
        DG_QueuePrim( prim );
        DG_GroupPrim( prim, GM_CurrentMap );
    }

    work->shadow_prim = prim;
    if ( prim == NULL )
    {
        return -1;
    }

    tex = DG_GetTexture( GV_StrCode( "shadow" ) );
    if ( tex == NULL )
    {
        return -1;
    }

    s10a_mel10_800DC6AC( prim->packs[0], tex );
    s10a_mel10_800DC6AC( prim->packs[1], tex );

    setRGB0( (POLY_FT4 *)prim->packs[0], 50, 50, 50 );
    setRGB0( (POLY_FT4 *)prim->packs[1], 50, 50, 50 );

    NewFadeInOut( 1, 20 );

    work->state = 0;
    work->timer = 0;
    work->f770 = 0;
    work->f774 = 0;
    work->f6B0 = 0;

    work->hom = GM_SetHomingTarget( &work->hom_mat, control );
    work->hom->flag = 1;
    work->stream_stop = 0;
    return 0;
}

void s10a_mel10_800DCE18( Work *work )
{
    DG_PRIM *prim;

    GM_FreeControl( &work->control );
    GM_FreeObject( &work->body );

    prim = work->shadow_prim;
    if ( prim )
    {
        DG_DequeuePrim( prim );
        DG_FreePrim( prim );
    }

    GM_FreeTarget( work->target );
    GM_FreeTarget( work->target2 );
    GM_ResetHomingTarget( work->hom );
}

int s10a_mel10_800DCE94( Work *work )
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;
    if ( target == NULL )
    {
        return -1;
    }

    GM_SetTarget( target, TARGET_AVAIL | TARGET_POWER | TARGET_SEEK, PLAYER_SIDE, &mel10_target_size );
    GM_SetPowerTarget( target, POWER_DECREASE, -1, GM_VitalityMax, 255, &DG_ZeroVector );
    GM_MoveTarget( target, &work->control.mov );

    target = GM_AllocTarget();
    work->target2 = target;
    if ( target == NULL )
    {
        return -1;
    }

    GM_SetTarget( target, TARGET_AVAIL | TARGET_POWER | TARGET_SEEK, ENEMY_SIDE, &mel10_target_size );
    GM_SetPowerTarget( target, POWER_DECREASE, -1, GM_VitalityMax, 255, &DG_ZeroVector );
    GM_MoveTarget( target, &work->control.mov );
    return 0;
}

int s10a_mel10_800DCFAC( Work *work, int name, int where )
{
    if ( s10a_mel10_800DCA7C( work, name, where ) < 0 )
    {
        return -1;
    }

    return 0;
}

void *NewBloodyMeryl( int name, int where, int argc, char **argv )
{
    SVECTOR pos;
    Work   *work;

    work = GV_NewActor( GV_ACTOR_PREV, sizeof( Work ) );
    if ( work != NULL )
    {
        GV_SetNamedActor( &work->actor, s10a_mel10_800DC844, s10a_mel10_800DCE18, "mel10.c" );

        if ( s10a_mel10_800DCFAC( work, name, where ) < 0 )
        {
            GV_DestroyActor(work);
            return NULL;
        }

        if ( s10a_mel10_800DCE94( work ) < 0 )
        {
            return NULL;
        }

        pos = work->target->center;
        pos.vy += 300;
        DG_SetPos2( &pos, &DG_ZeroVector );
        ReadRotMatrix( &work->hom_mat );

        if ( work->f7A8 == 0 )
        {
            work->life_rest = GM_VitalityMax;
        }

        s10a_mel10_800DC7D4( work );
        s10a_mel10_800DC70C( work );
    }

    return (void *)work;
}

void s10a_mel10_800DD0FC( Work *work )
{
    CONTROL *control;

    work->target->class = TARGET_AVAIL | TARGET_POWER | TARGET_SEEK;

    control = &work->control;
    control->height = work->body.height;
    control->r_sphere = GV_NearExp2( control->r_sphere, 450 );

    if ( work->fall < 0 && control->grounded != 0 )
    {
        work->fall = 0;
    }

    work->fall -= 16;
    control->step.vy = work->fall;
}

void s10a_mel10_800DD18C( Work *work )
{
    wolf2_800D3D54( work );
}

void s10a_mel10_800DD1AC( Work *work )
{
    s12a_wolf2_800D37A8( work );
    s10a_mel10_800DD0FC( work );
}
