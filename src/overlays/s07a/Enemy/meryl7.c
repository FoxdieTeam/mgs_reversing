#include "../../s00a/Enemy/enemy.h"
#include "chara/snake/shadow.h"
#include "libgcl/hash.h"
#include "Game/camera.h"

extern ENEMY_COMMAND EnemyCommand_800E0D98;
extern SVECTOR       ENEMY_TARGET_SIZE_800C35A4;
extern SVECTOR       ENEMY_TARGET_FORCE_800C35AC;
extern SVECTOR       ENEMY_ATTACK_SIZE_800C35B4;
extern SVECTOR       ENEMY_ATTACK_FORCE_800C35BC;
extern SVECTOR       ENEMY_TOUCH_SIZE_800C35C4;
extern SVECTOR       ENEMY_TOUCH_FORCE_800C35CC;
extern SVECTOR       COM_NO_POINT_800C35D4;
extern int           COM_EYE_LENGTH_800E0D8C;

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D50F8.s")

// Identical to s00a_watcher_800C409C
void s07a_meryl7_800D528C( WatcherWork* work )
{
    if ( GM_GameStatus_800AB3CC & STATE_ENEMY_OFF )
    {
        if ( work->faseout == 0 )
        {
            work->hom->flag = 0 ;
            work->alert_level = 0 ;
            GM_ConfigControlAttribute_8002623C( &(work->control), 0 ) ;
            work->visible = 0 ;
            work->target->class = TARGET_AVAIL;

            work->faseout = 1 ;
            work->act_status = EN_FASEOUT ;
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D52FC.s")

// Identical to s00a_watcher_800C4138
void s07a_meryl7_800D5328( DG_OBJS* objs, DG_DEF* def )
{
    int i;
    DG_OBJ *obj;
    DG_FreeObjsPacket_8001ABA8( objs, 0 );
    DG_FreeObjsPacket_8001ABA8( objs, 1 );

    objs->def = def;
    obj = objs->objs;
    for ( i = 0 ; i < 16 ; i++ )
    {
        obj->model   = &def->model[ i ];
        obj->n_packs =  def->model[ i ].numFaces_4;
        obj++;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D53A4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D54DC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5520.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5564.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D55A8.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5614.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5638.s")

// Identical to InitTarget_800C444C
void s07a_meryl7_800D5780( WatcherWork *work )
{
    TARGET *target;
    TARGET *target2;
    int life;
    int faint;

    target = work->target;
    life   = work->param_life;
    faint  = work->param_faint;

    GM_SetTarget_8002DC74( target, ( TARGET_FLAG | TARGET_AVAIL ), ENEMY_SIDE, &ENEMY_TARGET_SIZE_800C35A4 );
    GM_Target_8002DCCC( target, 1, -1, life, faint, &ENEMY_TARGET_FORCE_800C35AC );
    GM_Target_8002DCB4( target, -1, faint, NULL, NULL);

    sub_8002DD14( target, &( work->body.objs->objs[1].world ) );

    target2 = &work->field_904;
    GM_SetTarget_8002DC74( target2, TARGET_POWER, PLAYER_SIDE, &ENEMY_ATTACK_SIZE_800C35B4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 3, &ENEMY_ATTACK_FORCE_800C35BC );

    target2 = &work->field_94C;
    GM_SetTarget_8002DC74( target2, ( TARGET_TOUCH ), ENEMY_SIDE, &ENEMY_TOUCH_SIZE_800C35C4 );
    GM_Target_8002DCCC( target2, 7, 5, 0, 0, &ENEMY_TOUCH_FORCE_800C35CC );
}

// Identical to s00a_watcher_800C4578
void s07a_meryl7_800D58AC( WatcherWork* work )
{
    WatcherUnk *s;
    s = (WatcherUnk*)&work->field_8C8;

    GV_ZeroMemory_8001619C(s, 0x24);
    s->field_00 = 0;
    s->field_1C = 0x1C2;
    s->field_1E = 1;

    work->action = 0;
    work->action2 = 0;
    work->time = 0;
    work->time2 = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5908.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5B28.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5B90.s")

// Identical to ReadNodes_800C489C
int s07a_meryl7_800D5BB0( WatcherWork* work )
{
    int i;
    HZD_PAT *patrol;
    HZD_PTP *points;

    patrol = work->control.field_2C_map->field_8_hzd->f00_header->routes;
    patrol = &patrol[ work->field_B7D ];

    work->field_9E8 = patrol->n_points;

    if ( work->field_9E8 <= 0 ) return -1;

    points = patrol->points;
    for ( i = 0 ; i < work->field_9E8 ; i++ )
    {
        work->nodes[i].vx = points->x;
        work->nodes[i].vy = points->y;
        work->nodes[i].vz = points->z;
        work->nodes[i].pad = points->command;
        points++;
    }
    return 0;
}

// Identical to s00a_watcher_800C4990
int s07a_meryl7_800D5C4C( int opt, short* s )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_Get_Param_Result_80020AA4() ) ; i++ )
    {
        *s = GCL_StrToInt_800209E8( res );
         s++;
    }

    return i;
}

// Identical to s00a_watcher_800C49E8
int s07a_meryl7_800D5CA4( int opt, int* l )
{
    int i;
    unsigned char *res;

    for ( i = 0 ; ( res = GCL_Get_Param_Result_80020AA4() ) ; i++ )
    {
        *l = GCL_StrToInt_800209E8( res );
         l++;
    }

    return i;
}

#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5CFC.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5DD4.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5E34.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D5F24.s")
#pragma INCLUDE_ASM("asm/overlays/s07a/s07a_meryl7_800D63A4.s")
