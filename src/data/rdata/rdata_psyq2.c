#include "linker.h"

/*
// puts()
const char SECTION(".rdata") aNull_0[] = "<NULL>";

// puts() alignment ?
*/
//const int  SECTION(".rdata") dword_crap13[] = {0, 0};


const char SECTION(".rdata") aIdSysCV1140199[] = "$Id: sys.c,v 1.140 1998/01/12 07:52:27 noda Exp yos $";
const char SECTION(".rdata") aResetgraphJtb0[] = "ResetGraph:jtb=%08x,env=%08x\n";
const char SECTION(".rdata") aResetgraphD[] = "ResetGraph(%d)...\n";
const char SECTION(".rdata") aSetgraphdebugL[] = "SetGraphDebug:level:%d,type:%d reverse:%d\n";
const char SECTION(".rdata") aSetgrapqueD[] = "SetGrapQue(%d)...\n";
const char SECTION(".rdata") aDrawsynccallba[] = "DrawSyncCallback(%08x)...\n";
const char SECTION(".rdata") aSetdispmaskD[] = "SetDispMask(%d)...\n";
const char SECTION(".rdata") aDrawsyncD[] = "DrawSync(%d)...\n";
const char SECTION(".rdata") aSBadRect[] = "%s:bad RECT";
const char SECTION(".rdata") aDDDD[] = "(%d,%d)-(%d,%d)\n";
const char SECTION(".rdata") aS_0[] = "%s:";
const char SECTION(".rdata") aClearimage[] = "ClearImage";
const char SECTION(".rdata") aClearimage2[] = "ClearImage2";
const char SECTION(".rdata") aLoadimage[] = "LoadImage";
const char SECTION(".rdata") aStoreimage[] = "StoreImage";
const char SECTION(".rdata") aMoveimage[] = "MoveImage";
const char SECTION(".rdata") aClearotag08xD[] = "ClearOTag(%08x,%d)...\n";
const char SECTION(".rdata") aClearotagr08xD[] = "ClearOTagR(%08x,%d)...\n";
const char SECTION(".rdata") aDrawotag08x[] = "DrawOTag(%08x)...\n";
const char SECTION(".rdata") aPutdrawenv08x[] = "PutDrawEnv(%08x)...\n";
const char SECTION(".rdata") aDrawotagenv08x[] = "DrawOTagEnv(%08x,&08x)...\n";
const char SECTION(".rdata") aPutdispenv08x[] = "PutDispEnv(%08x)...\n";
const char SECTION(".rdata") aGpuTimeoutQueD[] = "GPU timeout:que=%d,stat=%08x,chcr=%08x,madr=%08x\n";
const char SECTION(".rdata") aLoadimage2[] = "LoadImage2";
const char SECTION(".rdata") aSpuTOS[] = "SPU:T/O [%s]\n";
const char SECTION(".rdata") aWaitReset[] = "wait (reset)";
const char SECTION(".rdata") aWaitWrdyHL[] = "wait (wrdy H -> L)";
const char SECTION(".rdata") aWaitDmafClearW[] = "wait (dmaf clear/W)";
const int  SECTION(".rdata") dword_crap14[] = {0, 0};
const char SECTION(".rdata") aSpuTOS_0[] = "SPU:T/O [%s]\n";
const char SECTION(".rdata") aWaitIrqOn[] = "wait (IRQ/ON)";
const char SECTION(".rdata") aWaitIrqOff[] = "wait (IRQ/OFF)";
const int  SECTION(".rdata") jpt_80014768[] = {0x800970C8, 0x80097090, 0x80097098, 0x800970A0,
                                               0x800970A8, 0x800970B0, 0x800970B8, 0x800970C0};
const int  SECTION(".rdata") jpt_80014788[] = {0x80097188, 0x80097150, 0x80097158, 0x80097160,
                                               0x80097168, 0x80097170, 0x80097178, 0x80097180};
const int  SECTION(".rdata") jpt_800147A8[] = {0x80097654, 0x8009765C, 0x80097664, 0x8009766C,
                                               0x80097674, 0x8009767C, 0x80097684, 0};
const int  SECTION(".rdata") jpt_800147C8[] = {0x80097734, 0x8009773C, 0x80097744, 0x8009774C,
                                               0x80097754, 0x8009775C, 0x80097764, 0};
const char SECTION(".rdata") aVsyncTimeout[] = "VSync: timeout\n";
const char SECTION(".rdata") aIdIntrCV175199[] = "$Id: intr.c,v 1.75 1997/02/07 09:00:36 makoto Exp $";
const char SECTION(".rdata") aUnexpectedInte[] = "unexpected interrupt(%04x)\n";
const char SECTION(".rdata") aIntrTimeout04x[] = "intr timeout(%04x:%04x)\n";
const int  SECTION(".rdata") dword_crap15 = 0;
const char SECTION(".rdata") aDmaBusErrorCod[] = "DMA bus error: code=%08x\n";
const char SECTION(".rdata") aMadrD08x[] = "MADR[%d]=%08x\n";
const int  SECTION(".rdata") dword_crap16 = 0;
const int  SECTION(".rdata") jpt_80014898[] = {0x8009A4FC, 0x8009A508, 0x8009A514, 0x8009A520, 0x8009A52C, 0, 0, 0};
