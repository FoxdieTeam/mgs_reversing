#include <sys/types.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>
#include "linker.h"
#include "actor.h"
#include "gvd.h"
#include "mts_new.h"


extern void __main_80098F14(void);


extern void SetDispMask_8008F7CC(int);
extern void InitGeom_80092680(void);

extern void SdMain_80081A18(void);

extern void mg_printf_8008BBA0(const char*, ...);

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


extern int SdIntReady_800886C4();


extern void MC_StartDaemon_80024E48(void);

extern void FS_StartDaemon_80014A7C(void);
extern void DG_StartDaemon_8001F284(void);
extern void GCL_StartDaemon_8001FCDC(void);
extern void HZD_StartDaemon_80021900(void);
extern void GM_StartDaemon_8002B77C(void);


static void task_main_800148B8( void )
{
	RECT rect;
	static unsigned char SECTION(".0x800AC3F0") sdStack_800AC3F0[2048];
	
	ResetGraph( 0 );
	SetGraphDebug( 0 );
	CdInit();
	SetDispMask_8008F7CC( 0 );
	
	setRECT( &rect, 0, 0, 1024, 511 );
	ClearImage( &rect, 0, 0, 0 );
	
	DrawSync( 0 );
	SetDispMask_8008F7CC( 1 );
	InitGeom_80092680();
	
	mts_init_vsync_800895AC();
	mts_set_vsync_task_800892B8();
	
	mg_printf_8008BBA0( aMem );
	MC_StartDaemon_80024E48();
	
	mg_printf_8008BBA0( aPad );
	mts_init_controller_8008C098();
	
	mg_printf_8008BBA0( aGv );
	GV_StartDaemon_80014d18();
	
	mg_printf_8008BBA0( aFs );
	FS_StartDaemon_80014A7C();
	
	mg_printf_8008BBA0( aDg );
	DG_StartDaemon_8001F284();
	
	mg_printf_8008BBA0( aGcl );
	GCL_StartDaemon_8001FCDC();
	
	mg_printf_8008BBA0( aHzd );
	HZD_StartDaemon_80021900();
	
	mg_printf_8008BBA0( aSound );

	mts_set_stack_check_8008B648(5, mts_stack_end(sdStack_800AC3F0), sizeof(sdStack_800AC3F0));
	mts_sta_tsk_8008B47C(5, SdMain_80081A18, mts_stack_end(sdStack_800AC3F0));

	while( !SdIntReady_800886C4() )
	{
		mts_wait_vbl_800895F4( 1 );
	}
	
	mg_printf_8008BBA0( aGm );
	GM_StartDaemon_8002B77C();
	
	mg_printf_8008BBA0( aStart );
	
	for (;;)
	{
		GV_ExecActorSystem_80014F88();
	}
}

void _main()
{
	static unsigned char SECTION(".0x800ABBF0") main_task_stack_800ABBF0[2048] ;
	__main_80098F14();
	mts_boot_task_8008AAC4(3, task_main_800148B8, mts_stack_end(main_task_stack_800ABBF0), sizeof(main_task_stack_800ABBF0));
}
