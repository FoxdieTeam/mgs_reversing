#include <sys/types.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>
#include "linker.h"
#include "actor.h"
#include "gvd.h"

extern void sub_8008AAC4( int tasknr, void (*procedure)(void), void *stack_pointer, long stack_size );

extern void __main(void);


extern void SetDispMask(int);
extern void InitGeom(void);

extern void SdMain(void);

extern void mg_printf(const char*, ...);

extern const char aMem[];
extern const char aPad[];
extern const char aGv[];
extern const char aFs[];
extern const char aDg[];
extern const char aGcl[];
extern const char aHzd[];
extern const char aSound[];
extern const char aGm[];
extern const char aStart[];

extern int SdIntReady();
extern void mts_wait_vbl(int);

extern void mts_init_vsync(void);
extern void mts_set_vsync_task(void);

extern void MC_StartDaemon(void);
extern void mts_init_controller(void);

extern void FS_StartDaemon(void);
extern void DG_StartDaemon(void);
extern void GCL_StartDaemon(void);
extern void HZD_StartDaemon(void);
extern void GM_StartDaemon(void);

extern void sub_8008B648(int, void*, long);
extern void sub_8008B47C(int ,void*, void*);


static void sub_800148B8( void )
{
	RECT rect;
	static unsigned char SECTION(".0x800AC3F0") SdStack[2048];
	
	ResetGraph( 0 );
	SetGraphDebug( 0 );
	CdInit();
	SetDispMask( 0 );
	
	setRECT( &rect, 0, 0, 1024, 511 ); // 0x400, 0x1FF
	ClearImage( &rect, 0, 0, 0 );
	
	DrawSync( 0 );
	SetDispMask( 1 );
	InitGeom();
	
	mts_init_vsync();
	mts_set_vsync_task();
	
	mg_printf( aMem );
	MC_StartDaemon();
	
	mg_printf( aPad );
	mts_init_controller();
	
	mg_printf( aGv );
	GV_StartDaemon_80014d18();
	
	mg_printf( aFs );
	FS_StartDaemon();
	
	mg_printf( aDg );
	DG_StartDaemon();
	
	mg_printf( aGcl );
	GCL_StartDaemon();
	
	mg_printf( aHzd );
	HZD_StartDaemon();
	
	mg_printf( aSound );

	sub_8008B648(5, SdStack + sizeof(SdStack), sizeof(SdStack));
	sub_8008B47C(5,SdMain, SdStack + sizeof(SdStack));

	while( !SdIntReady() )
	{
		mts_wait_vbl( 1 );
	}
	
	mg_printf( aGm );
	GM_StartDaemon();
	
	mg_printf( aStart );
	
	for (;;)
	{
		GV_ExecActorSystem_80014F88();
	}
}

void _main()
{
	static unsigned char SECTION(".0x800ABBF0") unk_800ABBF0[2048] ;
	__main();
	sub_8008AAC4(3, sub_800148B8, unk_800ABBF0+sizeof(unk_800ABBF0), sizeof(unk_800ABBF0));
}
