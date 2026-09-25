#include "libgcl/libgcl.h"
#include "game/game.h"

/*----------------------------------------------------------------------------*/

#define MOTION_DATA GV_StrCode( "crow" )
#define BODY_DATA   GV_StrCode( "crow" )
#define TARGET_FLAG ( TARGET_POWER | TARGET_SEEK )
#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_IRTEXTURE )

typedef struct _CROW {
    TARGET        *target;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs[ 8 ];
    SVECTOR        rots[ 7 ];
    SVECTOR        adjust[ 7 ];
    MATRIX         light[ 2 ];
    SVECTOR        field_384;
    SVECTOR        field_38C;
    SVECTOR        field_394;
    SVECTOR        field_39C;
    SVECTOR        field_3A4;
    int            field_3AC;
    int            unused1;
    int            field_3B4;
    int            field_3B8;
    int            field_3BC;
    int            field_3C0;
    int            field_3C4;
    int            unused2;
    int            field_3CC;
    int            stuntime;
    int            stun;
    int            field_3D8;
    int            field_3DC;
} CROW;

typedef struct _Work {
    GV_ACT  actor;
    int     map;
    int     n_crows;
    int     n_voices;
    int     field_2C;
    int     field_30;
    SVECTOR field_34[ 2 ];
    SVECTOR field_44[ 32 ];
    int     field_144;
    SVECTOR field_148[ 2 ];
    SVECTOR field_158[ 2 ];
    SVECTOR field_168[ 2 ];
    int     field_178;
    int     unused;
    SVECTOR field_180[ 2 ];
    SVECTOR field_190[ 2 ];
    int     field_1A0;
    SVECTOR field_1A4;
    int     field_1AC;
    int     field_1B0;
    int     field_1B4;
    int     sound1;
    int     sound2;
    int     time1;
    int     time2;
    HOMING *hom;
    CROW    crow[ 0 ];
} Work;

/*----------------------------------------------------------------------------*/

static void SortVecXZ( SVECTOR *vec1, SVECTOR *vec2 )
{
    int tmp;

    if ( vec1->vx > vec2->vx )
    {
        tmp = vec1->vx;
        vec1->vx = vec2->vx;
        vec2->vx = tmp;
    }

    if ( vec1->vz > vec2->vz )
    {
        tmp = vec1->vz;
        vec1->vz = vec2->vz;
        vec2->vz = tmp;
    }
}

static void SortVecXYZ( SVECTOR *vec1, SVECTOR *vec2 )
{
    int tmp;

    if ( vec1->vx > vec2->vx )
    {
        tmp = vec1->vx;
        vec1->vx = vec2->vx;
        vec2->vx = tmp;
    }

    if ( vec1->vy > vec2->vy )
    {
        tmp = vec1->vy;
        vec1->vy = vec2->vy;
        vec2->vy = tmp;
    }

    if ( vec1->vz > vec2->vz )
    {
        tmp = vec1->vz;
        vec1->vz = vec2->vz;
        vec2->vz = tmp;
    }
}

static int FindCollision( Work *work, SVECTOR *vec )
{
    CONTROL **where;
    MAP *map;
    int name, i;

    work->field_1B4 = work->field_1B0;

    where = GM_WhereList;
    map = GM_GetMap( work->map );
    name = work->field_2C;
    for ( i = GM_N_WhereList; i > 0; i--, where++ )
    {
        if ( ( *where )->name != name ) continue;
        if ( ( *where )->map != map ) continue;

        if ( vec->vy != ( *where )->mov.vy )
        {
            work->field_1B0 = 1;
        }
        else
        {
            work->field_1B0 = 0;
        }

        *vec = ( *where )->mov;
        return 1;
    }

    return 0;
}

static void DirVecXY( SVECTOR *from, SVECTOR *to, SVECTOR *dir )
{
    SVECTOR diff;
    int dy;

    GV_SubVec3( to, from, &diff );
    dir->vy = ratan2( diff.vx, diff.vz ) & 4095;

    dy = diff.vy;
    diff.vy = 0;

    dir->vx = ( ratan2( GV_VecLen3( &diff ), dy ) & 4095 ) - 1024;
    dir->vz = 0;
}

static int GetSVector( char *opt, SVECTOR *data )
{
    int count;
    char *str;

    count = 0;
    while ( ( str = GCL_NextStr() ) != NULL )
    {
        GCL_StrToSV( str, (short *)data );
        data++;
        count++;
    }
    return count;
}

static void SetAction( CROW *crow, int action, int stuntime )
{
    if ( crow->field_3C0 != action )
    {
        crow->field_3C0 = action;
        GM_ConfigObjectAction( &crow->body, action, 0, 4 );
        return;
    }

    if ( crow->body.is_end == 1 )
    {
        crow->stuntime = stuntime;
    }
}

static int CheckPos( SVECTOR *pos, SVECTOR *min, SVECTOR *max )
{
    if ( pos->vx < min->vx || pos->vx > max->vx ||
         pos->vz < min->vz || pos->vz > max->vz )
    {
        return -1;
    }

    return 1;
}

static void InterpRand( SVECTOR *from, SVECTOR *to, SVECTOR *out )
{
    VECTOR tmp;
    int x, y, z;

    x = GV_RandU( 64 );
    y = GV_RandU( 64 );
    z = GV_RandU( 64 );
    tmp.vx = ( ( to->vx - from->vx ) * x ) >> 6;
    tmp.vy = ( ( to->vy - from->vy ) * y ) >> 6;
    tmp.vz = ( ( to->vz - from->vz ) * z ) >> 6;
    out->vx = from->vx + tmp.vx;
    out->vy = from->vy + tmp.vy;
    out->vz = from->vz + tmp.vz;
}

static void UpdateMovement( CROW *crow )
{
    DirVecXY( &crow->control.mov, &crow->field_384, &crow->control.turn );
    DG_SetPos2( &DG_ZeroVector, &crow->control.turn );
    DG_PutVector( &crow->field_39C, &crow->field_3A4, 1 );
    GV_AddVec3( &crow->control.mov, &crow->field_3A4, &crow->control.mov );
}

static void UpdateSound( Work *work )
{
    int id;

    if ( GV_RandU( 4096 ) % work->n_crows >= work->n_voices ) return;

    if ( work->time1-- < 0 )
    {
        work->time1 = GV_RandU( 32 ) + 20;

        id = GV_RandU( 4096 ) % 3;
        if ( work->sound1 != id )
        {
            work->sound1 = id;
        }
        else
        {
            work->sound1 = id + 1;
            if ( work->sound1 > 2 ) work->sound1 = 0;
        }

        GM_SeSet2( GV_RandS( 32 ) & 255, 63, work->sound1 + 181 );
    }

    if ( work->time2-- < 0 )
    {
        work->time2 = GV_RandU( 16 ) + 15;

        id = GV_RandU( 4 );
        if ( work->sound2 != id )
        {
            work->sound2 = id;
        }
        else
        {
            work->sound2 = id + 1;
            if ( work->sound2 > 3 ) work->sound2 = 0;
        }

        GM_SeSet2( GV_RandS( 32 ) & 255, 63, work->sound2 + 185 );
    }
}

static void UpdateStun( CROW *crow )
{
    if ( ( GM_GameStatus & STATE_STUN ) && crow->stun != 1 )
    {
        crow->stun = 1;
        crow->stuntime = 36;
    }
}

static void Act( Work *work )
{
    SVECTOR sp10, sp18, sp20, sp28, sp30, sp38;
    int i, v0, v1, id, x, z;
    CROW *crow;

    GM_CurrentMap = work->map;
    UpdateSound( work );

    if ( work->field_30 != 1 )
    {
        FindCollision( work, &work->field_1A4 );
    }

    sp28.vx = 0;
    sp28.vy = 0;

    sp18.vx = 0;
    sp18.vz = 0;

    if ( work->field_1AC == 0 )
    {
        work->field_1AC = 1;
        sp10.vx = ABS( work->field_34[ 0 ].vx - work->field_34[ 1 ].vx ) / 2;
        sp10.vy = ABS( work->field_34[ 0 ].vz - work->field_34[ 1 ].vz ) / 2;

        for ( i = 0; i < work->n_crows; i++ )
        {
            crow = &work->crow[ i ];

            if ( work->field_1A0 == 0 || work->field_1A0 == 2 )
            {
                if ( GV_RandU( 2 ) != 0 )
                {
                    v0 = GV_RandU( 4096 ) % work->field_144;
                    if ( v0 < ( work->field_144 - 1 ) )
                    {
                        v1 = v0;
                        v0++;
                    }
                    else
                    {
                        v1 = 0;
                    }

                    InterpRand( &work->field_44[ v0 ], &work->field_44[ v1 ], &crow->field_394 );
                    GV_AddVec3( &crow->field_394, &work->field_1A4, &crow->control.mov );
                    DirVecXY( &crow->control.mov, &work->field_1A4, &crow->control.turn );
                    crow->stuntime = 4;
                }
                else
                {
                    InterpRand( &work->field_34[ 0 ], &work->field_34[ 1 ], &crow->field_394 );
                    GV_AddVec3( &crow->field_394, &work->field_1A4, &crow->control.mov );

                    sp18.vy = GV_RandU( 2048 );
                    sp18.vy += 1000;

                    GV_AddVec3( &crow->control.mov, &sp18, &crow->control.mov );
                    crow->stuntime = 8;
                }
            }

            if ( work->field_1A0 == 1 )
            {
                InterpRand( &work->field_180[ 0 ],
                            &work->field_180[ 1 ],
                            &crow->control.mov );
                crow->stuntime = 14;
            }

            if ( work->field_1A0 == 3 )
            {
                InterpRand( &work->field_148[ 0 ], &work->field_148[ 1 ], &crow->control.mov );
                crow->control.mov.vy += GV_RandU( 2048 ) + 1000;
                crow->stuntime = 8;
            }
        }
    }

    sp20.vx = 0;
    sp20.vz = 0;

    for ( i = 0; i < work->n_crows; i++ )
    {
        crow = &work->crow[ i ];
        crow->field_3B4--;
        crow->field_3B8--;
        crow->field_3BC++;

        if ( crow->stun == 0 )
        {
            if ( crow->field_3CC == 0 )
            {
                GM_MoveTarget( crow->target, &crow->control.mov );
                if ( crow->target->damaged & TARGET_POWER )
                {
                    GM_ConfigControlHazard( &crow->control, 50, 50, 50 );
                    work->n_voices--;
                    crow->field_39C = crow->target->force;
                    crow->field_39C.vx = GV_RandS( 64 );
                    crow->field_39C.vy = GV_RandU( 32 ) + 32;
                    crow->field_39C.vz = GV_RandU( 64 );
                    crow->field_3CC = 1;
                    crow->stuntime = 29;
                }
            }
        }
        else
        {
            crow->target->damaged |= ~TARGET_POWER;
        }

        switch( crow->stuntime )
        {
        case 0:
            DG_InvisibleObjs( crow->body.objs );
            crow->field_3B4 = GV_RandU( 256 );
            crow->stuntime = 1;
            /* fallthrough */
        case 1:
            if ( crow->field_3B4 < 0 )
            {
                crow->stuntime = 2;
                DG_VisibleObjs( crow->body.objs );
            }
            break;
        case 2:
            crow->body.m_ctrl = &crow->m_ctrl;

            v0 = GV_RandU( 4096 ) % work->field_144;
            if ( v0 < ( work->field_144 - 1 ) )
            {
                v1 = v0;
                v0++;
            }
            else
            {
                v1 = 0;
            }

            if ( work->field_1B0 == 1 || work->field_30 == 1 )
            {
                InterpRand( &work->field_44[ v0 ], &work->field_44[ v1 ], &crow->field_394 );
                if ( GV_DiffVec3( &crow->control.mov, &crow->field_394 ) > 4000 )
                {
                    crow->stuntime = 8;
                    break;
                }
            }
            else
            {
                crow->stuntime = 8;
                break;
            }

            crow->field_39C.vz = GV_RandU( 64 ) + 100;
            crow->stuntime = 3;
            /* fallthrough */
        case 3:
            if ( work->field_1B0 != 1 && work->field_30 != 1 )
            {
                crow->stuntime = 8;
            }

            if ( GV_DiffVec3( &crow->control.mov, &crow->field_384 ) < 2000 )
            {
                crow->stuntime = 4;
                crow->field_3A4 = DG_ZeroVector;
            }

            GV_AddVec3( &crow->field_394, &work->field_1A4, &crow->field_384 );
            UpdateMovement( crow );
            break;
        case 4:
            if ( work->field_1B0 != 1 && work->field_30 != 1 )
            {
                crow->stuntime = 8;
            }

            GV_AddVec3( &crow->field_394, &work->field_1A4, &crow->field_384 );
            crow->control.mov.vx = ( crow->control.mov.vx * 15 + crow->field_384.vx ) >> 4;
            crow->control.mov.vy = ( crow->control.mov.vy * 15 + crow->field_384.vy ) >> 4;
            crow->control.mov.vz = ( crow->control.mov.vz * 15 + crow->field_384.vz ) >> 4;
            SetAction( crow, 9, 5 );
            break;
        case 5:
            crow->stuntime = 6;
            crow->body.m_ctrl = NULL;
            crow->field_3B4 = GV_RandU( 256 ) + 30;
            DirVecXY( &crow->control.mov, &work->field_1A4, &crow->control.turn );
            /* fallthrough */
        case 6:
            if ( ( work->field_1B0 == 1 || work->field_30 == 1 ) && crow->field_3B4 >= 0 )
            {
                GV_AddVec3( &crow->field_394, &work->field_1A4, &crow->control.mov );
            }
            else
            {
                crow->stuntime = 8;

                if ( crow->field_3B4 < 0 && GV_RandU( 64 ) == 0 )
                {
                    crow->body.m_ctrl = &crow->m_ctrl;
                    crow->stuntime = 4;
                }
                else
                {
                    GV_AddVec3( &crow->field_394, &work->field_1A4, &crow->control.mov );
                }
            }
            break;
        case 8:
            crow->field_3B8 = GV_RandU( 256 ) + 30;
            DirVecXY( &crow->control.mov, &work->field_1A4, &crow->control.turn );
            /* fallthrough */
        case 9:
            if ( work->field_1B0 == 1 || work->field_30 == 1 )
            {
                if ( crow->field_3B8 < 0 )
                {
                    if ( work->field_1A0 == 2 )
                    {
                        crow->stuntime = 14;
                    }
                    else
                    {
                        crow->stuntime = 2;
                    }
                    break;
                }

                GV_AddVec3( &work->field_34[ 0 ], &work->field_1A4, &sp30 );
                GV_AddVec3( &work->field_34[ 1 ], &work->field_1A4, &sp38 );
                crow->field_3C4 = 6;
            }
            else
            {
                if ( work->field_1A0 == 3 || work->field_1A0 == 0 )
                {
                    sp30 = work->field_148[ 0 ];
                    sp38 = work->field_148[ 1 ];
                }
                else if ( work->field_1A0 == 4 )
                {
                    sp30 = work->field_158[ 0 ];
                    sp38 = work->field_158[ 1 ];
                }

                if ( work->field_1B4 != 1 )
                {
                    switch ( GV_RandU( 8 ) )
                    {
                    case 0:
                        crow->field_3C4 = 7;
                        break;
                    case 1:
                    case 2:
                    case 3:
                        crow->field_3C4 = 5;
                        break;
                    default:
                        crow->field_3C4 = 6;
                        break;
                    }
                }
                else
                {
                    crow->field_3C4 = 10;
                }
            }

            crow->body.m_ctrl = &crow->m_ctrl;
            crow->stuntime = 10;

            sp28.vz = GV_RandU( 4096 );
            sp28.vz += 2000;

            DG_SetPos2( &crow->control.mov, &crow->control.turn );
            DG_PutVector( &sp28, &crow->field_394, 1 );

            if ( CheckPos( &crow->field_394, &sp30, &sp38 ) == -1 )
            {
                sp28.vz = 1000;
                DG_SetPos2( &crow->control.mov, &crow->control.turn );
                DG_PutVector( &sp28, &crow->field_394, 1 );
            }

            crow->field_394.vy = crow->control.mov.vy + GV_RandS( 2048 );

            if ( crow->field_394.vy < sp30.vy + 500 )
            {
                crow->field_394.vy = sp30.vy + 600;
            }

            if ( crow->field_394.vy > sp30.vy + 2000 )
            {
                crow->field_394.vy = sp30.vy + 2000;
            }

            sp20.vy = crow->control.turn.vy;
            if ( crow->field_3AC == 0 )
            {
                sp20.vy += 1024;
            }
            else
            {
                sp20.vy -= 1024;
            }

            sp28.vz = GV_RandU( 2048 );
            sp28.vz += 1000;

            DG_SetPos2( &crow->field_394, &sp20 );
            DG_PutVector( &sp28, &crow->field_38C, 1 );

            if ( CheckPos( &crow->field_38C, &sp30, &sp38 ) == -1 )
            {
                sp28.vz = 1000;
                DG_SetPos2( &crow->field_394, &sp20 );
                DG_PutVector( &sp28, &crow->field_38C, 1 );
            }
            else if ( GV_DiffVec3( &crow->control.mov, &work->field_1A4 ) < 3500 )
            {
                crow->field_3AC = 1 - crow->field_3AC;
            }

            crow->field_39C.vz = GV_RandU( 64 ) + 100;
            /* fallthrough */
        case 10:
            if ( GV_DiffVec3( &crow->control.mov, &crow->field_38C ) < 1000 )
            {
                crow->stuntime = 9;
            }

            crow->field_384.vx = ( crow->field_394.vx * 7 + crow->field_38C.vx ) >> 3;
            crow->field_384.vy = ( crow->field_394.vy * 7 + crow->field_38C.vy ) >> 3;
            crow->field_384.vz = ( crow->field_394.vz * 7 + crow->field_38C.vz ) >> 3;
            crow->field_394 = crow->field_384;

            UpdateMovement( crow );
            SetAction( crow, crow->field_3C4, 10 );
            UpdateStun( crow );
            break;
        case 14:
            InterpRand( &work->field_190[ 0 ], &work->field_190[ 1 ], &crow->field_394 );
            crow->field_39C.vz = GV_RandU( 64 ) + 100;
            crow->stuntime = 15;
            /* fallthrough */
        case 15:
            GV_AddVec3( &crow->field_394, &work->field_1A4, &crow->field_384 );
            UpdateMovement( crow );

            if ( work->field_1A0 == 1 && crow->control.mov.vy > work->field_1A4.vy )
            {
                DirVecXY( &crow->control.mov, &work->field_1A4, &crow->control.turn );
            }

            SetAction( crow, 6, 15 );

            if ( GV_DiffVec3( &crow->control.mov, &crow->field_384 ) >= 300 )
            {
                break;
            }

            if ( work->field_1A0 == 2 )
            {
                crow->stuntime = 19;
                break;
            }

            crow->stuntime = 8;
            break;
        case 19:
            InterpRand( &work->field_180[ 0 ], &work->field_180[ 1 ], &crow->field_384 );
            DirVecXY( &crow->control.mov, &crow->field_384, &crow->control.turn );
            crow->field_39C.vz = GV_RandU( 64 ) + 100;
            crow->stuntime = 20;
            /* fallthrough */
        case 20:
            UpdateMovement( crow );
            crow->control.turn.vx += 1024;
            SetAction( crow, 6, 20 );
            if ( GV_DiffVec3( &crow->control.mov, &crow->field_384 ) < 300 )
            {
                crow->stuntime = 21;
            }
            break;
        case 21:
            DG_InvisibleObjs( crow->body.objs );
            break;
        case 29:
            crow->stuntime = 30;
            GM_ConfigControlHazard( &crow->control, 50, 50, 50 );
            crow->field_3D8 = 1;
            GM_SeSet2( 0, 63, 184 );
            work->time1 = 0;
            work->time2 = 0;
            break;
        case 30:
            GV_AddVec3( &work->field_34[ 0 ], &work->field_1A4, &sp30 );
            GV_AddVec3( &work->field_34[ 1 ], &work->field_1A4, &sp38 );
            GV_AddVec3( &crow->control.mov, &crow->field_39C, &crow->control.mov );

            crow->control.turn.vx += 164;
            crow->control.turn.vy += 284;
            crow->control.turn.vz += 394;

            crow->field_39C.vx = crow->field_39C.vx * 15 / 16;
            crow->field_39C.vy -= 3;
            crow->field_39C.vz = crow->field_39C.vz * 15 / 16;

            SetAction( crow, 4, 30 );

            if ( work->time1-- < 0 )
            {
                work->time1 = GV_RandU( 4 ) + 4;
                id = GV_RandU( 4 );

                if (work->sound1 != id )
                {
                    work->sound1 = id;
                }
                else
                {
                    work->sound1 = id + 1;
                    if ( work->sound1 > 3 ) work->sound1 = 0;
                }

                GM_SeSet2( GV_RandS( 32 ), 63, work->sound1 + 181 );
            }

            if ( work->time2-- < 0 )
            {
                work->time2 = GV_RandU( 4 ) + 4;
                id = GV_RandU( 4 );

                if ( work->sound2 != id )
                {
                    work->sound2 = id;
                }
                else
                {
                    work->sound2 = id + 1;
                    if ( work->sound2 > 3 ) work->sound2 = 0;
                }

                GM_SeSet2( 0, 63, work->sound2 + 185 );
            }

            if ( crow->control.grounded != 0 || crow->control.mov.vy < -20000 )
            {
                crow->stuntime = 31;
            }
            break;
        case 31:
            crow->field_3B8 = 60;
            crow->stuntime = 32;
            GCL_ExecProc( work->field_178, NULL );
            crow->control.turn.vx = 0;
            crow->control.turn.vz = 0;
            /* fallthrough */
        case 32:
            if ( ( crow->field_3B8 % 4 ) < 2 )
            {
                DG_InvisibleObjs( crow->body.objs );
            }
            else
            {
                DG_VisibleObjs( crow->body.objs );
            }

            if ( crow->field_3B8 < 0 )
            {
                crow->stuntime = 33;
            }
            break;
        case 33:
            GM_ConfigControlHazard( &crow->control, -1, -2, -1 );
            DG_InvisibleObjs( crow->body.objs );
            crow->stuntime = 34;
            break;
        case 34:
            crow->stuntime = 35;
            break;
        case 36:
            crow->stuntime = 37;
            GM_ConfigControlHazard( &crow->control, 50, 50, 50 );
            crow->field_39C.vy = GV_RandU( 64 ) + 4;
            work->time1 = 0;
            work->time2 = 0;
            /* fallthrough */
        case 37:
            GV_AddVec3( work->field_34, &work->field_1A4, &sp30 );
            GV_AddVec3( work->field_34 + 1, &work->field_1A4, &sp38 );
            GV_AddVec3( &crow->control.mov, &crow->field_39C, &crow->control.mov );

            crow->control.turn.vx += 164;
            crow->control.turn.vy += 284;
            crow->control.turn.vz += 394;

            crow->field_39C.vx = crow->field_39C.vx * 15 / 16;
            crow->field_39C.vy -= 3;
            crow->field_39C.vz = crow->field_39C.vz * 15 / 16;

            SetAction( crow, 4, 37 );

            if ( work->time1-- < 0 )
            {
                work->time1 = GV_RandU( 8 ) + 10;
                id = GV_RandU( 4 );

                if ( work->sound1 != id )
                {
                    work->sound1 = id;
                }
                else
                {
                    work->sound1 = id + 1;
                    if ( work->sound1 > 3 ) work->sound1 = 0;
                }

                GM_SeSet2( GV_RandS( 32 ), 63, work->sound1 + 181 );
            }

            if ( work->time2-- < 0 )
            {
                work->time2 = GV_RandU( 4 ) + 4;
                id = GV_RandU( 4 );

                if ( work->sound2 != id )
                {
                    work->sound2 = id;
                }
                else
                {
                    work->sound2 = id + 1;
                    if ( work->sound2 > 3 ) work->sound2 = 0;
                }

                GM_SeSet2( GV_RandS( 32 ), 63, work->sound2 + 185 );
            }

            if ( crow->control.grounded != 0 || crow->control.mov.vy < -20000 )
            {
                crow->control.grounded = 0;
                GM_ConfigControlHazard( &crow->control, -1, -2, -1 );
                crow->stuntime = 38;
                crow->field_3B8 = GV_RandU( 128 ) + 60;
                crow->control.turn.vx = 0;
                crow->control.turn.vz = 0;
            }
            break;
        case 38:
            SetAction( crow, 9, 38 );
            if ( crow->field_3B8 < 0 && !( GM_GameStatus & STATE_STUN ) )
            {
                crow->stun = 0;
                crow->stuntime = 8;
                crow->field_39C = DG_ZeroVector;
            }
            break;
        }

        if ( crow->stuntime != 35 )
        {
            GM_ActControl( &crow->control );
            GM_ActObject2( &crow->body );

            if ( GM_Item == IT_ThermG )
            {
                DG_AmbientObjs( crow->body.objs );
            }
            else
            {
                DG_UnAmbientObjs( crow->body.objs );
            }

            DG_GetLightMatrix2( &crow->control.mov, crow->light );
        }

        x = ABS( crow->field_384.vx - GM_PlayerPosition.vx );
        z = ABS( crow->field_384.vz - GM_PlayerPosition.vz );
        if ( crow->field_3D8 == 0 && x < 5000 && z < 5000 )
        {
            crow->field_3DC = x * x + z * z;
        }
        else
        {
            crow->field_3DC = 999999999;
        }
    }

    x = 999999999;
    z = -1;

    for ( i = 0; i < work->n_crows; i++ )
    {
        crow = &work->crow[ i ];
        if ( crow->field_3DC < x )
        {
            x = crow->field_3DC;
            z = i;
        }
    }

    if ( z != -1 )
    {
        crow = &work->crow[ z ];

        if ( work->hom != NULL )
        {
            GM_ResetHomingTarget( work->hom );
        }

        work->hom = GM_SetHomingTarget( &crow->body.objs->objs[ 0 ].world, &crow->control );
        if ( work->hom != NULL )
        {
            work->hom->flag = 1;
        }
    }
    else if ( work->hom != NULL )
    {
        work->hom->flag = 0;
    }
}

static int GetOptions( Work *work, int name, int where )
{
    SVECTOR size;
    char *opt;
    int i;
    CROW *crow;
    TARGET *trg;

    GM_GetMap( work->map );

    opt = GCL_GetOption( 'o' );
    if ( opt != NULL )
    {
        work->field_2C = GCL_StrToInt( GCL_NextStr() );
        work->field_30 = 0;
    } else
    {
        work->field_30 = 1;
    }

    opt = GCL_GetOption( 'p' );
    if ( opt != NULL )
    {
        if ( GetSVector( opt, work->field_34 ) == 2 )
        {
            SortVecXZ( &work->field_34[ 0 ], &work->field_34[ 1 ] );
        }
    }

    i = 0;

    opt = GCL_GetOption( 'q' );
    if ( opt != NULL )
    {
        work->field_144 = GetSVector( opt, work->field_44 );
    }

    if ( work->field_30 != 1 )
    {
        opt = GCL_GetOption( 'r' );
        if ( opt != NULL )
        {
            i = GetSVector( opt, work->field_148 );
        }

        if ( i == 2 )
        {
            SortVecXZ( &work->field_148[ 0 ], &work->field_148[ 1 ] );
        }

        i = 0;
        opt = GCL_GetOption( 's' );
        if ( opt != NULL )
        {
            i = GetSVector( opt, work->field_158 );
        }

        if ( i == 2 )
        {
            SortVecXZ( &work->field_158[ 0 ], &work->field_158[ 1 ] );
        }

        opt = GCL_GetOption( 't' );
        if ( opt != NULL )
        {
            if ( GetSVector( opt, work->field_168 ) == 2 )
            {
                SortVecXZ( &work->field_168[ 0 ], &work->field_168[ 1 ] );
            }
        }
    }
    else
    {
        work->field_1A4 = DG_ZeroVector;
        work->field_1B0 = 1;
    }

    opt = GCL_GetOption( 'i' );
    if ( opt != NULL )
    {
        work->field_178 = GCL_StrToInt( opt );
    }

    opt = GCL_GetOption( 'x' );
    if ( opt != NULL )
    {
        if ( GetSVector( opt, work->field_180 ) == 2 )
        {
            SortVecXYZ( &work->field_180[ 0 ], &work->field_180[ 1 ] );
        }
    }

    opt = GCL_GetOption( 'y' );
    if ( opt != NULL )
    {
        if ( GetSVector( opt, work->field_190 ) == 2 )
        {
            SortVecXYZ( &work->field_190[ 0 ], &work->field_190[ 1 ] );
        }
    }

    opt = GCL_GetOption( 'w' );
    if ( opt != NULL )
    {
        work->field_1A0 = GCL_StrToInt( opt );
    }
    else
    {
        work->field_1A0 = 0;
    }

    for ( i = 0; i < work->n_crows; i++ )
    {
        crow = &work->crow[ i ];

        trg = crow->target = GM_AllocTarget();
        if ( trg != NULL )
        {
            setVector( &size, 50, 50, 50 );
            GM_SetTarget( trg, TARGET_FLAG, ENEMY_SIDE, &size );
        }

        crow->field_3D8 = 0;
        crow->field_3CC = 0;
        crow->field_3AC = GV_RandU( 2 );
        crow->field_39C = DG_ZeroVector;
    }

    work->field_1AC = 0;
    return 0;
}

static int GetResources( Work *work, int name, int where )
{
    int i;
    CROW *crow;
    CONTROL *ctrl;
    OBJECT *body;

    work->map = where;

    for ( i = 0; i < work->n_crows; i++ )
    {
        crow = &work->crow[ i ];
        ctrl = &crow->control;

        if ( GM_InitControl( ctrl, name, where ) < 0 ) return -1;
        GM_ConfigControlAttribute( ctrl, 0 );
        GM_ConfigControlHazard( ctrl, -1, -2, -1 );
        GM_ConfigControlInterp( ctrl, 4 );
        ctrl->step = DG_ZeroVector;

        body = &crow->body;
        GM_InitObject( body, BODY_DATA, BODY_FLAG, MOTION_DATA );
        GM_ConfigObjectJoint( body );
        GM_ConfigObjectLight( body, crow->light );

        DG_VisibleObjs( work->crow[ i ].body.objs );

        GM_ConfigMotionControl( body, &crow->m_ctrl, MOTION_DATA, crow->m_segs, NULL, ctrl, crow->rots );
        GM_ConfigObjectAction( body, 0, 0, 0 );

        work->crow[ i ].field_3BC = GV_RandU( 4096 );
        work->crow[ i ].stun = 0;
    }

    work->sound1 = 0;
    work->sound2 = GV_RandU( 4 );
    work->time1 = GV_RandU( 64 ) + 20;
    work->time2 = GV_RandU( 64 ) + 20;
    return 0;
}

static void Die( Work *work )
{
    int i;

    for ( i = 0; i < work->n_crows; i++ )
    {
        GM_FreeObject( &work->crow[ i ].body );
        GM_FreeControl( &work->crow[ i ].control );
        GM_FreeTarget( work->crow[ i ].target );
    }

    if ( work->hom != NULL )
    {
        GM_ResetHomingTarget( work->hom );
    }
}

void *NewElevatorCrow( int name, int where )
{
    char *opt;
    int num;
    Work *work;

    opt = GCL_GetOption( 'n' );
    if ( opt != NULL )
    {
        num = GCL_StrToInt( opt );
        if ( num > 24 ) num = 24;
    }
    else
    {
        num = 1;
    }

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) + sizeof(CROW) * num );
    if ( work != NULL )
    {
        work->n_crows = num;
        work->n_voices = num;
        GV_SetNamedActor( work, Act, Die, "ele_crow.c" );
        if ( GetResources( work, name, where ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
        if ( GetOptions( work, name, where ) < 0 )
        {
            GV_DestroyActor( work );
            return NULL;
        }
    }
    return (void *)work;
}
