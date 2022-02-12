#include "linker.h"

const char SECTION(".rdata") aSlpm86248[] = "SLPM_862.48";
const char SECTION(".rdata") aSlpm86247[] = "SLPM_862.47";
const char SECTION(".rdata") aBislpm86247[] = "BISLPM-86247";
const char SECTION(".rdata") aDsreadycallbac[] = "DsReadyCallback %x\n";
const char SECTION(".rdata") aDsdatacallback[] = "DsDataCallback %x\n";
const char SECTION(".rdata") aHangupS[] = "HANGUP: %s\n";
const char SECTION(".rdata") aResidentTopX[] = "RESIDENT TOP %X\n";
const char SECTION(".rdata") aDumpactorsyste[] = "--DumpActorSystem--\n";
const char SECTION(".rdata") aLvDPauseDKillD[] = "Lv %d Pause %d Kill %d\n";
const char SECTION(".rdata") aLvD04d02d08xS[] = "Lv%d %04d.%02d %08X %s\n";
const char SECTION(".rdata") aIdConflict[] = "id conflict\n";
const char SECTION(".rdata") aAssertionFaile[] = "Assertion failed: %s, line %d\n";
const char SECTION(".rdata") aSystemD[] = "system %d ( ";
const char SECTION(".rdata") aDynamic[] = "dynamic ";
const char SECTION(".rdata") aAddr08x08xUnit[] = "  addr = %08x - %08x, units = %d\n";
const char SECTION(".rdata") aFreeDDVoidedDM[] = "  free = %d / %d, voided = %d, max_free = %d\n";
const char SECTION(".rdata") a8dBytesFrom08x[] = "---- %8d bytes ( from %08x free )\n";
const char SECTION(".rdata") a8dBytesFrom08x_0[] = "==== %8d bytes ( from %08x void )\n";
const char SECTION(".rdata") a8dBytesFrom08x_1[] = "++++ %8d bytes ( from %08x used )\n";
const char SECTION(".rdata") a8dBytesFrom08x_2[] = "**** %8d bytes ( from %08x user %08x )\n";
const char SECTION(".rdata") aResidentMemory[] = "Resident Memory Over !!\n";
const short SECTION(".rdata") asc_80010208[] = { 0x40, 0x0 };
const char SECTION(".rdata") aObjectQueueD[] = "Object Queue %d\n";
const char SECTION(".rdata") aPrimitiveQueue[] = "Primitive Queue %d\n";

// Smaller strings get put into .DATA ??
const char SECTION(".rdata") aDgdC[] = "dgd.c";

//const char SECTION(".rdata") aCommandNotFoun[] ="command not found\n";
//const char SECTION(".rdata") aProcXNotFound[] = "PROC %X NOT FOUND\n";
//const char SECTION(".rdata") aProcDCancel[] = "proc %d cancel\n";
//const char SECTION(".rdata") aTooManyArgsPro[] = "TOO MANY ARGS PROC\n";
//const char SECTION(".rdata") aScriptCommandE[] = "SCRIPT COMMAND ERROR %x\n";
//const char SECTION(".rdata") aErrorInScript[] ="ERROR in script\n";
//const char SECTION(".rdata") aNotScriptData[] = "NOT SCRIPT DATA !!\n";
