
#define SECTION(x) __attribute__((section(x)))

extern void sub_8008AAC4( int tasknr, void (*procedure)(void), void *stack_pointer, long stack_size );
extern void sub_800148B8(void);

extern void __main();

int SECTION(".main") _main()
{
	static unsigned char SECTION(".static_800ABBF0") unk_800ABBF0[2048] ;
	__main();
	sub_8008AAC4(3, sub_800148B8, unk_800ABBF0+sizeof(unk_800ABBF0), sizeof(unk_800ABBF0));
}
