#include "linker.h"

const char SECTION(".RDATA") aSlpm86248[] = "SLPM_862.48";
const char SECTION(".RDATA") aSlpm86247[] = "SLPM_862.47";
const char SECTION(".RDATA") aBislpm86247[] = "BISLPM-86247";
const char SECTION(".RDATA") aDsreadycallbac[] = "DsReadyCallback %x\n";
const char SECTION(".RDATA") aDsdatacallback[] = "DsDataCallback %x\n";
const char SECTION(".RDATA") aHangupS[] = "HANGUP: %s\n";
const char SECTION(".RDATA") aResidentTopX[] = "RESIDENT TOP %X\n";
const char SECTION(".RDATA") aDumpactorsyste[] = "--DumpActorSystem--\n";
const char SECTION(".RDATA") aLvDPauseDKillD[] = "Lv %d Pause %d Kill %d\n";
const char SECTION(".RDATA") aLvD04d02d08xS[] = "Lv%d %04d.%02d %08X %s\n";
const char SECTION(".RDATA") aIdConflict[] = "id conflict\n";
const char SECTION(".RDATA") aAssertionFaile[] = "Assertion failed: %s, line %d\n";
const char SECTION(".RDATA") aSystemD[] = "system %d ( ";
const char SECTION(".RDATA") aDynamic[] = "dynamic ";
const char SECTION(".RDATA") aAddr08x08xUnit[] = "  addr = %08x - %08x, units = %d\n";
const char SECTION(".RDATA") aFreeDDVoidedDM[] = "  free = %d / %d, voided = %d, max_free = %d\n";
const char SECTION(".RDATA") a8dBytesFrom08x[] = "---- %8d bytes ( from %08x free )\n";
const char SECTION(".RDATA") a8dBytesFrom08x_0[] = "==== %8d bytes ( from %08x void )\n";
const char SECTION(".RDATA") a8dBytesFrom08x_1[] = "++++ %8d bytes ( from %08x used )\n";
const char SECTION(".RDATA") a8dBytesFrom08x_2[] = "**** %8d bytes ( from %08x user %08x )\n";
const char SECTION(".RDATA") aResidentMemory[] = "Resident Memory Over !!\n";
const short SECTION(".RDATA") asc_80010208[] = { 0x40, 0x0 };
const char SECTION(".RDATA") aObjectQueueD[] = "Object Queue %d\n";
const char SECTION(".RDATA") aPrimitiveQueue[] = "Primitive Queue %d\n";

// Smaller strings get put into .DATA ??
const char SECTION(".RDATA") aDgdC[] = "dgd.c";

const char SECTION(".RDATA") aCommandNotFoun[] ="command not found\n";
const char SECTION(".RDATA") aProcXNotFound[] = "PROC %X NOT FOUND\n";
const char SECTION(".RDATA") aProcDCancel[] = "proc %d cancel\n";
const char SECTION(".RDATA") aTooManyArgsPro[] = "TOO MANY ARGS PROC\n";
const char SECTION(".RDATA") aScriptCommandE[] = "SCRIPT COMMAND ERROR %x\n";
const char SECTION(".RDATA") aErrorInScript[] ="ERROR in script\n";
const char SECTION(".RDATA") aNotScriptData[] = "NOT SCRIPT DATA !!\n";

const unsigned int SECTION(".RDATA") jpt_80020454[] =
{
    0x8002045C,
	0x80020464,
	0x8002046C,
	0x80020474,
	0x8002047C,
	0x80020484,
	0x80020494,
	0x800204C8,
	0x800204FC,
	0x80020508,
	0x80020514,
	0x8002051C,
	0x80020528,
	0x80020530,
	0x8002053C,
	0x80020544,
	0x8002054C,
	0x80020554,
	0x8002056C
};

const char SECTION(".RDATA") aGclWrongCodeX[] = "GCL:WRONG CODE %x\n\x0\x0"; // TODO: Alignment ??

const unsigned int SECTION(".RDATA") jpt_80020704[] =
{
	0x8002070C, 0x80020714, 0x80020788, 0x80020788, 0x80020788,
	0x8002083C, 0x8002076C, 0x80020798, 0x8002076C, 0x80020738,
	0x80020738, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x800207AC, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x800207F0, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x800207C8,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002080C
};

const char SECTION(".RDATA") aSaveDataVersio[] = "SAVE DATA VERSION ERROR!!\n";

const char SECTION(".RDATA") aCrcError[] = "CRC ERROR !!\n\x0\x0\x0"; // TODO: Alignment ??

const unsigned int SECTION(".RDATA") jpt_800216BC[] =
{
	0x800216C4,
	0x800216E8,
	0x800216E8,
	0x800216F4,
	0x80021714,
	0x800216C4,
	0x80021714,
	0x800216C4
};


const unsigned int SECTION(".RDATA") jpt_800217A0[] =  
{
	0x800217A8,
	0x800217B0,
	0x800217B0,
	0x800217B8,
	0x800217E8,
	0x800217A8,
	0x800217E8,
	0x800217A8
};

const unsigned int SECTION(".RDATA") jpt_80021894[] =
{
	0x8002189C,
	0x800218A8,
	0x800218A8,
	0x800218B4,
	0x800218EC,
	0x8002189C,
	0x800218EC,
	0x8002189C
};

const char SECTION(".RDATA") aWarningOldVers[] = "Warning:old version hzm\n";

const char SECTION(".RDATA") aBrfDat[] = "BRF.DAT";
const char SECTION(".RDATA") aDemoDat[] = "DEMO.DAT";
const char SECTION(".RDATA") aVoxDat[] ="VOX.DAT";
const char SECTION(".RDATA") aZmovieStr[] = "ZMOVIE.STR";
const char SECTION(".RDATA") aFaceDat[] = "FACE.DAT";
const char SECTION(".RDATA") aRadioDat[] = "RADIO.DAT";
const char SECTION(".RDATA") aStageDir[] = "STAGE.DIR";

const char SECTION(".RDATA") aPositionEnd[] = "Position end\n";
const char SECTION(".RDATA") aDiskD[] = "DISK %d\n";
const char SECTION(".RDATA") aIllegalDisk[] = "illegal DISK\n";

const char SECTION(".RDATA") aCdfsSkipErrorD[] = "CDFS: skip error %d %d %d\n";

const char SECTION(".RDATA") asc_800105B4[] = "[T]";
const char SECTION(".RDATA") asc_800105B8[] = ".";
const char SECTION(".RDATA") aD[] ="[%d]";
const char SECTION(".RDATA") aFileSTopDSizeD[] = "FILE %s : top %d size %d set %d\n";
const char SECTION(".RDATA") aPlaystation[] = "PLAYSTATION";
const char SECTION(".RDATA") aMgs[] = "MGS";
const char SECTION(".RDATA") aMgsReadSectorD[] = "MGS read_sector %d\n";
