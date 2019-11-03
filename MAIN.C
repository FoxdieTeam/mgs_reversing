#include <sys/types.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>

#define SECTION(x) __attribute__((section(x)))

extern const char aSlpm86247[];
extern const char aSlpm86248[];

int dword_8009D2DC[] = { 0x21CA, 0x8005B650, 0x8767, 0x800344F8, 0xB997, 0x8006FD00, 0, 0 };

const char* off_8009D2FC[] = { aSlpm86247, aSlpm86248, 0};

int dword_8009D308[] = { 0x70000, 0x70000, 0x40009, 0x40009, 0x4000F, 0x4000F, 0x4000F, 0x40009, 0x70000 };

int dword_8009D32C[] = { 0x8000000, 0x6000400, 0, 0x200, 0xA000C00, 0, 0xE00, 0 };

int dword_8009D34C[] = { 0, 0xFFFFF000, 0, 0 };

int off_8009D35C[] = 
{
	0x8001CEE0,
	0x800189A4,
	0x8001E3C0,
	0x8001D324,
	0x8001B66C,
	0x80019D44,
	0x8001D5C8
};

int dword_8009D37[] = { 0, 0, 0 };
int dword_8009D38 =  0;

int dword_8009D388 = 0x1000;

int dword_8009D38C = 0;
int dword_8009D390 = 0;

// ======================================================================================================

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

static void SECTION(".0x800148B8") sub_800148B8( void )
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
	GV_StartDaemon();
	
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
	sub_8008b47c(5,SdMain, SdStack + sizeof(SdStack));

	while( !SdIntReady() )
	{
		mts_wait_vbl( 1 );
	}
	
	mg_printf( aGm );
	GM_StartDaemon();
	
	mg_printf( aStart );
	
	for (;;)
	{
		GV_ExecActorSystem();
	}
}


int SECTION(".0x80014a40") _main()
{
	static unsigned char SECTION(".0x800ABBF0") unk_800ABBF0[2048] ;
	__main();
	sub_8008AAC4(3, sub_800148B8, unk_800ABBF0+sizeof(unk_800ABBF0), sizeof(unk_800ABBF0));
}
