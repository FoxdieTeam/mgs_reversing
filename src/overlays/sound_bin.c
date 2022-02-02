#include "linker.h"
#include "gcl.h"


// Overlay chara used only in sound.bin
GCL_ActorTableEntry SECTION(".gProgramBottom_800C3208") OverlayCharas[] =
	{
		{0x4EFC, (TGCL_ActorCreateFn)0x800C3594}, // soundtst
		{0, 0}};


// Test code
void Map_FreeKmds_80031028();

void SECTION(".olay") OverlayTesting2()
{

}

void SECTION(".olay")  OverlayTesting1()
{
	Map_FreeKmds_80031028();
}

void SECTION(".olay")  OverlayTesting3()
{

}
