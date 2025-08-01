#ifndef _STRCTRL_H_
#define _STRCTRL_H_

#include "libgv/libgv.h"

// TODO: might be bigger if the jimctrl actually uses this
typedef struct  StreamCtrlWork
{
    GV_ACT      actor;
    short       field_20_state;
    short       field_22_sub_state;
    short       field_24;
    short       field_26_flags;
    int         field_28;
    int         map;
    int         field_30_voxStream;
    int         *field_34_pStreamData;
    int         field_38_proc;
    int         field_3C;
} StreamCtrlWork;

/* strctrl.c */
void *NewStreamControl( int stream_code, int gcl_proc, int flags );

int GM_StreamStatus( void );
void GM_StreamPlayStart( void );
void GM_StreamPlayStop( void );
void GM_StreamCancelCallback( void );
int GM_StreamGetLastCode( void );

void *GM_DemoStream( int base_sector, int gcl_proc );
void *GM_VoxStream( int vox_code, int proc );
void *sub_80037EE0( int vox_stream, int gcl_proc );

#endif // _STRCTRL_H_
