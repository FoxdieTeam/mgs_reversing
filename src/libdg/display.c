#include "linker.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "inline_n.h"
#include "dgd.h" //need to switch to libdg.h

/**data************************/
extern VECTOR vector_8009D34C;
/******************************/

/**gp***********************************************************************************************/
extern int DG_UnDrawFrameCount_800AB380;
int SECTION(".sdata") DG_UnDrawFrameCount_800AB380;

extern int dword_800AB384;
int SECTION(".sdata") dword_800AB384;

int             SECTION(".sbss") gClipHeights_800AB960[2];
int             SECTION(".sbss") DG_CurrentGroupID_800AB968;
short           SECTION(".sbss") DG_ClipMin_800AB96C[2];
short           SECTION(".sbss") DG_ClipMax_800AB970[2];
/***************************************************************************************************/

/**sbss**********************************/
extern int GV_Clock_800AB920;
extern int GV_PauseLevel_800AB928;
extern int DG_HikituriFlagOld_8009D464;
/****************************************/

/**bss************************************************************************/
DISPENV         SECTION(".gDispEnv_800B0600") gDispEnv_800B0600;
VECTOR          SECTION(".gUnknownVector_800B0620") gUnknownVector_800B0620;

extern DG_CHNL  DG_Chanls_800B1800[3];
/****************************************************************************/

/**funcs************************************************************************************************************************/
extern void             DG_ClearChanlSystem_80017E9C(int bufferIdx);
extern void             DG_RenderPipeline_80018028(int bufferIdx);
DISPENV*                PutDispEnv_80090094(DISPENV *env);
extern void             DG_DrawOTag_80017E4C(int activeBuffer);
extern void             MENU_ResetSystem_80038A88();
extern void             DG_ClearTmpLight_8001A0E4();
extern void             GV_ClearMemorySystem_80015B4C( int which );
extern void             PutDrawEnv_8008FEC8(DRAWENV*);
extern unsigned short   GetTPage_80092418( int tp, int abr, int x, int y );
extern void             DrawPrim_8008FDFC( void *p );
extern unsigned int     GetRCnt_800996E8(unsigned int rcnt);
extern void             DG_TransposeMatrix_8001EAD8(MATRIX *in, MATRIX *out);
extern void             VectorNormal_80092838(VECTOR *v0, VECTOR *v1);
extern void             OuterProduct12_800933AC(VECTOR *v0, VECTOR *v1, VECTOR *v2);
extern VECTOR*          ApplyMatrixLV_80092C48(MATRIX *m, VECTOR *v0, VECTOR *v1);
extern void             DG_Init_DrawEnv_80018384(DRAWENV *pDrawEnv, short clipX1, short clipY1, short clipX2, short clipY2);
/*****************************************************************************************************************************/


void DG_InitDispEnv_800170F0(int x, short y, short w, short h, int clipH)
{
    DISPENV *pDispEnv = &gDispEnv_800B0600;
    RECT *pDispRect;
    RECT *pScreenRect;

    pDispRect = &pDispEnv->disp;
    pScreenRect = &pDispEnv->screen;

    setRECT(pDispRect, x, y, w, h);
    setRECT(pScreenRect, 0, 0, 256, 240);

    pDispEnv->isinter = 0;
    pDispEnv->isrgb24 = 0;

    // For some reason lets overwrite what we already setup
    pDispEnv->screen.y = 8;
    pDispEnv->screen.h = 224;

    gClipHeights_800AB960[0] = x;
    gClipHeights_800AB960[1] = x + clipH;
}

void DG_ChangeReso_80017154(void)
{
}

void DG_RenderPipeline_Init_8001715C(void)
{
    DG_ClearChanlSystem_80017E9C(0);
    DG_ClearChanlSystem_80017E9C(1);
    DG_RenderPipeline_80018028(0);
    DG_RenderPipeline_80018028(1);
}

void DG_80017194()
{
    int activeBuffer = GV_Clock_800AB920;
    if ((GV_PauseLevel_800AB928 & 8) != 0 || DG_UnDrawFrameCount_800AB380 > 0)
    {
        if (dword_800AB384 < 0)
        {
            dword_800AB384 = activeBuffer;
        }
        if ((GV_PauseLevel_800AB928 & 8) == 0)
        {
            --DG_UnDrawFrameCount_800AB380;
        }
    }
    else if (dword_800AB384 < 0 || activeBuffer != dword_800AB384)
    {

        DISPENV *p = &gDispEnv_800B0600;
        p->disp.x = gClipHeights_800AB960[activeBuffer ];

        PutDispEnv_80090094(&gDispEnv_800B0600);
        if (!DG_HikituriFlagOld_8009D464)
        {
            DG_DrawOTag_80017E4C(1 - activeBuffer);
        }
        dword_800AB384 = -1;
    }
    GV_ClearMemorySystem_80015B4C(activeBuffer);
    if (!DG_HikituriFlagOld_8009D464)
    {
        GV_ClearMemorySystem_80015B4C(2);
    }
    MENU_ResetSystem_80038A88();
    DG_ClearChanlSystem_80017E9C(activeBuffer);
    DG_ClearTmpLight_8001A0E4();
}

void DG_RenderPipeline_800172A8(void)
{
    DG_RenderPipeline_80018028(GV_Clock_800AB920);
}

void DG_800172D0 ( DG_CHNL* chnl, SVECTOR* svec, SVECTOR* svec2, short camera_property ) 
{
    VECTOR  vec;
    VECTOR  empty_vec_2;
    VECTOR  empty_vec;
    MATRIX* chnl_matrix;

    
    chnl->word_6BC3BC = camera_property ;
    chnl_matrix = &chnl->dword_6BC39C;

    chnl_matrix->t[0] = svec->vx ;
    chnl_matrix->t[1] = svec->vy ;
    chnl_matrix->t[2] = svec->vz ;

    vec.vx = (signed short)( ( (unsigned short)svec2->vx - (unsigned short)svec->vx ) );
    vec.vy = (signed short)( ( (unsigned short)svec2->vy - (unsigned short)svec->vy ) );
    vec.vz = (signed short)( ( (unsigned short)svec2->vz - (unsigned short)svec->vz ) );

    OuterProduct12_800933AC( &vector_8009D34C, &vec, &empty_vec ) ;

    if ( !empty_vec.vx && !empty_vec.vy && !empty_vec.vz )
    {
        empty_vec = gUnknownVector_800B0620;
    }
    else
    {
        gUnknownVector_800B0620 = empty_vec;
    }

    VectorNormal_80092838( &empty_vec, &empty_vec ) ;
    VectorNormal_80092838( &vec, &vec ) ;

    OuterProduct12_800933AC( &vec, &empty_vec, &empty_vec_2 ) ;

    chnl_matrix->m[0][0] = empty_vec.vx;
    chnl_matrix->m[0][1] = empty_vec_2.vx;
    chnl_matrix->m[0][2] = vec.vx;

    chnl_matrix->m[1][0] = empty_vec.vy;
    chnl_matrix->m[1][1] = empty_vec_2.vy;
    chnl_matrix->m[1][2] = vec.vy;

    chnl_matrix->m[2][0] = empty_vec.vz;
    chnl_matrix->m[2][1] = empty_vec_2.vz;
    chnl_matrix->m[2][2] = vec.vz;

    DG_TransposeMatrix_8001EAD8( chnl_matrix, &chnl->field_10_matrix ) ;

    vec.vx = -chnl_matrix->t[0];
    vec.vy = -chnl_matrix->t[1];
    vec.vz = -chnl_matrix->t[2];

    ApplyMatrixLV_80092C48( &chnl->field_10_matrix, &vec, (VECTOR*)(&chnl->field_10_matrix.t[0]) ) ;
}

void DG_800174DC( MATRIX* matrix )
{
    int check;

    //probably some division or something
    check = matrix->m[1][0] * 0x3A;

    if (check < 0)
    {
        check = check + 0x3f;
    }

    matrix->m[1][0] = check >> 6;
    check = matrix->m[1][1] * 0x3A;

    if (check < 0)
    {
        check = check + 0x3f;
    }

    matrix->m[1][1] = check >> 6;
    check = matrix->m[1][2] * 0x3A;

    if (check < 0)
    {
        check = check + 0x3f;
    }

    matrix->m[1][2] = check >> 6;
    check =  matrix->t[1] * 0x3A;

    if (check < 0)
    {
        check = check + 0x3f;
    }

    matrix->t[1] = check >> 6;
}

void DG_Clip_80017594(RECT *pClipRect, int dist)
{
    int xTmp;
    int yTmp;
    gte_SetGeomScreen(dist);
    xTmp = pClipRect->x;
    DG_ClipMin_800AB96C[0] = xTmp;
    DG_ClipMax_800AB970[0] = pClipRect->w + xTmp - 1;
    yTmp = pClipRect->y;
    DG_ClipMin_800AB96C[1] = yTmp;
    DG_ClipMax_800AB970[1] = pClipRect->h + yTmp - 1;
}

void sub_800175E0( MATRIX* matrix, MATRIX* matrix2 )
{
  MATRIX matrix3;

  gte_SetRotMatrix( matrix );
  gte_ldclmv( matrix2 );
  gte_rtir();

  gte_stclmv( &matrix3 );
  gte_ldclmv( &matrix2->m[0][1] );
  gte_rtir();

  gte_stclmv( &matrix3.m[0][1] );
  gte_ldclmv( &matrix2->m[0][2] );
  gte_rtir();

  gte_stclmv( &matrix3.m[0][2] );
  gte_SetTransMatrix( matrix );
  gte_ldlv0( matrix2->t );

  gte_mvmva(1,0,0,0,0);
  gte_stlvnl( matrix3.t );

  DG_800174DC( &matrix3 );
  gte_SetRotMatrix( &matrix3 );
  gte_SetTransMatrix( &matrix3 );
}

void DG_OffsetDispEnv_80017784(int offset)
{
    gDispEnv_800B0600.screen.y += offset;
    gDispEnv_800B0600.screen.h -= offset;
    PutDispEnv_80090094(&gDispEnv_800B0600);
    gDispEnv_800B0600.screen.y -= offset;
    gDispEnv_800B0600.screen.h += offset;
}

void DG_ClipDispEnv_800177EC(int x, int y)
{
    RECT screen; // [sp+10h] [-8h]

    screen = gDispEnv_800B0600.screen;
    gDispEnv_800B0600.screen.x = 128 - x / 2;
    gDispEnv_800B0600.screen.w = x;
    gDispEnv_800B0600.screen.y = 120 - y / 2;
    gDispEnv_800B0600.screen.h = y;
    PutDispEnv_80090094(&gDispEnv_800B0600);
    gDispEnv_800B0600.screen = screen;
}

void DG_PutDrawEnv_From_DispEnv_80017890(void)
{
    DRAWENV drawEnv;
    DG_Init_DrawEnv_80018384(&drawEnv, gDispEnv_800B0600.disp.x, gDispEnv_800B0600.disp.y, gDispEnv_800B0600.disp.w, gDispEnv_800B0600.disp.h);
    PutDrawEnv_8008FEC8(&drawEnv);
}

//Need to find Prims that these structs correlate to
typedef struct {
    char field_00;
    char field_01;
    char field_02;
    char field_03;
    long field_04;
} PRIM1;

typedef struct {
    char  field_00;
    char  field_01;
    char  field_02;
    char  field_03;
    long  field_04;
    short field_08;
    short field_0A;
    short field_0C;
    short field_0E;
} PRIM2;

void DG_800178D8( int a0 )
{
    unsigned short val;
    PRIM1 prim;
    PRIM2 prim2;

    DG_PutDrawEnv_From_DispEnv_80017890() ;

    prim.field_03 = 1;
    val = GetTPage_80092418( 0, 2, 0, 0 ) ;
    
    prim.field_04 = (val & 0x09FF) | 0xE1000600 ;
    DrawPrim_8008FDFC( &prim );

    prim2.field_0C = 0x140;
    prim2.field_0E = 0xE0;

    prim2.field_04 = ( ( a0 << 16 ) | ( a0 << 8 ) ) | a0;
    prim2.field_03 = 3;
    prim2.field_08 = 0;
    prim2.field_0A = 0;

    *((char*)(&prim2.field_04) + 3) = 0x62;

    DrawPrim_8008FDFC( &prim2 );
}

//guessed function name
DISPENV* DG_GetDisplayEnv_80017978( void )
{
    return &gDispEnv_800B0600;
}