#include "meryl72.h"

extern int   GV_Time;
extern int   GM_PlayerMap_800ABA0C ;
extern void  AN_Breath_800C3AA8( MATRIX * ) ;
extern void  AN_Fog_800CA618( SVECTOR *pos ) ;
extern void  NewBlood_80072728( MATRIX *, int ) ;
extern void *AN_Unknown_800CA1EC( MATRIX* mat, int mark );

extern GV_ACT *bullet_init_80076584(MATRIX *pMtx, int whichSide, int a3, int noiseLen);

SVECTOR s07c_dword_800C3394 = { 0, 0, 100, 0 };
SVECTOR s07c_dword_800C339C = { -1024, 0, 0 };

void ML72_PutBlood_800CB2EC( Meryl72Work* work, int obj_idx, int count )
{
    MATRIX mat;
    DG_SetPos( &work->body.objs->objs[ obj_idx ].world );
    DG_MovePos( &s07c_dword_800C3394 );
    DG_RotatePos( &s07c_dword_800C339C );
    ReadRotMatrix( &mat );
    NewBlood_80072728( &mat, count );
}

SVECTOR s07c_dword_800C33A4 = { 0, 0, 100, 0 };
SVECTOR s07c_dword_800C33AC = { -1024, 0, 0 };

void ML72_PutBreath_800CB35C( Meryl72Work *work )
{
    MATRIX mat;
    SVECTOR svec;

    DG_SetPos( &work->body.objs->objs[1].world );
    DG_MovePos( &s07c_dword_800C33A4 );
    DG_RotatePos( &s07c_dword_800C33AC );
    ReadRotMatrix( &mat );

    svec.vx = mat.t[ 0 ];
    svec.vy = mat.t[ 1 ];
    svec.vz = mat.t[ 2 ];

    AN_Fog_800CA618( &svec );
}

void ML72_PutMark_800CB3C0( Meryl72Work* work, int mark )
{
    if ( work->control.map->index & GM_PlayerMap_800ABA0C )
    {
        AN_Unknown_800CA1EC( &work->body.objs->objs[6].world , mark );
    }
}

void ML72_Put_800CB404( Meryl72Work *work ) {}

void ML72_Put_800CB40C( Meryl72Work *work ) {}

void ML72_PutBreath_800CB414( Meryl72Work* work )
{
    if ( ( GV_Time % 64 ) == ( work->param.fAF8 * 16 ) )
    {
        AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
    }
}

void ML72_PutSound_800CB468( Meryl72Work *work )
{
    int t0;
    int a2;
    int sd1;
    int sd2;

    t0 = work->f8BC.field_18;
    a2 = work->m_ctrl.info1.frame;
    sd1 = 0xC0;

    if( work->fB94 == 0 )
    {
        sd1 = 3;
        sd2 = 2;
    }
    else
    {
        sd2 = 0xBF;
    }

    if ( t0 == 1 )
    {
        if ( a2 == 10 )
        {
            GM_SeSet( &work->control.mov, sd1 );
        }
        else if ( a2 == 1 )
        {
            sd1 = sd2;
            GM_SeSet( &work->control.mov, sd1 );
        }
    }
    else if ( t0 == 2 )
    {
        if ( a2 == 10 )
        {
            GM_SeSet( &work->control.mov, sd1 );
        }
        else if ( a2 == 1 )
        {
            sd1 = sd2;
            GM_SeSet( &work->control.mov, sd1 );
        }
    }
}

void ML72_PutBullet_800CB4F0( Meryl72Work *work );

PUTFUNC ML72_PutFuncs[5] = {
    ML72_Put_800CB404,
    ML72_Put_800CB40C,
    ML72_PutSound_800CB468,
    ML72_PutBullet_800CB4F0,
    ML72_PutBreath_800CB414
};

SVECTOR s07c_dword_800C33C8 = { 5, -500, 80, 0 };

void ML72_PutBullet_800CB4F0( Meryl72Work *work )
{
    MATRIX* mat;
    MATRIX local_mat;

    mat = &work->body.objs->objs[4].world;
    DG_SetPos( mat );
    DG_MovePos( &s07c_dword_800C33C8 );
    ReadRotMatrix( &local_mat );
    bullet_init_80076584( &local_mat, 2, 1, 0 );
    GM_SeSet( &work->control.mov, SE_ENEMY_SHOT );
    NewAnime_8005D6BC( mat, 0 );
    NewAnime_8005D604( &local_mat );

    ML72_ClearPutChar_800CB5CC( work, ML72_PutBullet_800CB4F0 ) ;
}

int ML72_SetPutChar_800CB584( Meryl72Work *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->fA9C[ i ] == NULL )
        {
            work->fA9C[ i ] = ML72_PutFuncs[ idx ];
            return 1;
        }
    }
    return 0;
}

int ML72_ClearPutChar_800CB5CC( Meryl72Work *work, void *func )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->fA9C[ i ] == func )
        {
            work->fA9C[ i ] = 0;
            return 1;
        }
    }
    return 0;
}

void ML72_ExecPutChar_800CB600( Meryl72Work* work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->fA9C[ i ] )
        {
            PUTFUNC func = work->fA9C[ i ];
            func( work );
        }
    }
}