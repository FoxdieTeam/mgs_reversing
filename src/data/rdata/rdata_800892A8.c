#include "linker.h"

const char SECTION(".rdata") aTickCountD[] = "Tick count %d\n\n";
const char SECTION(".rdata") aCdinitInitFail[] = "CdInit: Init failed\n";
const int  SECTION(".rdata") dword_crap9[] = {0, 0};
const char SECTION(".rdata") aNone_0[] = "none";
const int  SECTION(".rdata") dword_crap10[] = {0, 0};
const char SECTION(".rdata") aCdlreads[] = "CdlReadS";
const char SECTION(".rdata") aCdlseekp[] = "CdlSeekP";
const char SECTION(".rdata") aCdlseekl[] = "CdlSeekL";
const char SECTION(".rdata") aCdlgettd[] = "CdlGetTD";
const char SECTION(".rdata") aCdlgettn[] = "CdlGetTN";
const char SECTION(".rdata") aCdlgetlocp[] = "CdlGetlocP";
const char SECTION(".rdata") aCdlgetlocl[] = "CdlGetlocL";
const int  SECTION(".rdata") dword_800141CC[] = {0x3F,       0x536C6443, 0x6F6D7465, 0x6564,
                                                 0x536C6443, 0x69667465, 0x7265746C, 0};
const char SECTION(".rdata") aCdldemute[] = "CdlDemute";
const char SECTION(".rdata") aCdlmute[] = "CdlMute";
const char SECTION(".rdata") aCdlreset[] = "CdlReset";
const char SECTION(".rdata") aCdlpause[] = "CdlPause";
const char SECTION(".rdata") aCdlstop[] = "CdlStop";
const char SECTION(".rdata") aCdlstandby[] = "CdlStandby";
const char SECTION(".rdata") aCdlreadn[] = "CdlReadN";
const char SECTION(".rdata") aCdlbackward[] = "CdlBackward";
const char SECTION(".rdata") aCdlforward[] = "CdlForward";
const char SECTION(".rdata") aCdlplay[] = "CdlPlay";
const char SECTION(".rdata") aCdlsetloc[] = "CdlSetloc";
const char SECTION(".rdata") aCdlnop[] = "CdlNop";
const char SECTION(".rdata") aCdlsync[] = "CdlSync";
const char SECTION(".rdata") aDiskerror_0[] = "DiskError";
const char SECTION(".rdata") aDataend[] = "DataEnd";
const char SECTION(".rdata") aAcknowledge[] = "Acknowledge";
const char SECTION(".rdata") aComplete_0[] = "Complete";
const char SECTION(".rdata") aDataready[] = "DataReady";
const char SECTION(".rdata") aNointr[] = "NoIntr";
const char SECTION(".rdata") aCdTimeout[] = "CD timeout: ";
const char SECTION(".rdata") aSSSyncSReadyS[] = "%s:(%s) Sync=%s, Ready=%s\n";
const char SECTION(".rdata") aDiskerror[] = "DiskError: ";
const char SECTION(".rdata") aComSCode02x02x[] = "com=%s,code=(%02x:%02x)\n";
const char SECTION(".rdata") aCdromUnknownIn[] = "CDROM: unknown intr";
const char SECTION(".rdata") aD_1[] = "(%d)\n";
const int  SECTION(".rdata") dword_crap11 = 0;
const int  SECTION(".rdata") jpt_80014328[] = {0x8008D290, 0x8008D244, 0x8008D144, 0x8008D310, 0x8008D390};
const char SECTION(".rdata") aCdSync[] = "CD_sync";
const char SECTION(".rdata") aCdReady[] = "CD_ready";
const char SECTION(".rdata") aS[] = "%s...\n";
const char SECTION(".rdata") aSNoParam[] = "%s: no param\n";
const char SECTION(".rdata") aCdCw[] = "CD_cw";
const char SECTION(".rdata") aIdBiosCV186199[] = "$Id: bios.c,v 1.86 1997/03/28 07:42:42 makoto Exp yos $";
const char SECTION(".rdata") aCdInit[] = "CD_init:";
const char SECTION(".rdata") aAddr08x[] = "addr=%08x\n";
const char SECTION(".rdata") aCdDatasync[] = "CD_datasync";
const int  SECTION(".rdata") dword_crap12[] = {0, 0, 0};
const char SECTION(".rdata") a0123456789abcd[] = "0123456789ABCDEF";
const char SECTION(".rdata") a0123456789abcd_0[] = "0123456789abcdef";
const int  SECTION(".rdata") jpt_80014400[] = {
     0x8008EB50, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000,
     0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008EE08, 0x8008F000, 0x8008F000, 0x8008F000,
     0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008EF20,
     0x8008EB7C, 0x8008F000, 0x8008F000, 0x8008F000, 0x8008EB38, 0x8008EB7C, 0x8008F000, 0x8008F000,
     0x8008EB44, 0x8008F000, 0x8008EFCC, 0x8008ECF4, 0x8008EDF4, 0x8008F000, 0x8008F000, 0x8008EF40,
     0x8008F000, 0x8008EBD4, 0x8008F000, 0x8008F000, 0x8008EE14, 0};
const char SECTION(".rdata") aNull_0[] = "<NULL>";
const int  SECTION(".rdata") dword_crap13[] = {0, 0};
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
