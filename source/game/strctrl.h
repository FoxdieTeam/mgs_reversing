#ifndef __MGS_GAME_STRCTRL_H__
#define __MGS_GAME_STRCTRL_H__

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

#endif // __MGS_GAME_STRCTRL_H__
