#include "bss.h"
#include "linker.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/GM_Control.h"
#include "Game/game.h"
#include "chara/snake/sna_init.h"
#include "memcard/memcard.h"
#include "map/map.h"
#include "Game/jimctrl.h"
#include "mts/mts_new.h"
#include "Game/homing_target.h"
#include "Bullet/jirai.h"
#include "Kojo/demothrd.h"

// please separate different SECTIONs by newlines

// TODO: script that sorts these by address and adds comments for all the missing gaps with sizes
// and detect overlaps

unsigned char SECTION(".bss") main_task_stack_800ABBF0[2048]; // 800ABBEC

unsigned int SECTION(".bss") sdStack_800AC3F0[512]; // 800AC3F0

int SECTION(".bss") gDiskNum_800ACBF0;
int SECTION(".bss") pad_800ACBF4;

struct Actor SECTION(".bss") gGVActor_800acbf8;

int SECTION(".dword_800B05A8") dword_800B05A8[6];

DG_CHNL SECTION(".DG_Chanls_800B1800") DG_Chanls_800B1800[3];

unsigned char SECTION(".byte_800B1400") byte_800B1400[1024];

char SECTION(".byte_801FFF00") byte_801FFF00[240];

unsigned char SECTION(".byte_800C0DB8") byte_800C0DB8[512];

unsigned char SECTION(".byte_800C0DB8") dword_800C0FB8[1024];

unsigned char SECTION(".byte_800B7A50") byte_800B7A50[2016];

UnkCameraStruct SECTION(".gUnkCameraStruct_800B77B8") gUnkCameraStruct_800B77B8;

signed char SECTION(".byte_800C0C10") byte_800C0C10[32];

int SECTION(".gMts_active_task_idx_800C13C0") gMts_active_task_idx_800C13C0;

mts_msg SECTION(".gMtsMsgs_800C13D0") gMtsMsgs_800C13D0[8];

DISPENV SECTION(".gDispEnv_800B0600") gDispEnv_800B0600;

VECTOR SECTION(".gUnknownVector_800B0620") gUnknownVector_800B0620;

GM_Control *SECTION(".GM_WhereList_800B56D0") GM_WhereList_800B56D0[96];

GM_Control SECTION(".gDefaultControl_800B5650") gDefaultControl_800B5650;

int SECTION(".dword_800BDFA8") dword_800BDFA8;

int SECTION(".dword_800B7800") dword_800B7800;

unsigned short SECTION(".gOldRootCnt_800B1DC8") gOldRootCnt_800B1DC8[32];

unsigned char SECTION(".gMtsPadRecvBuffers_800C1480") gMtsPadRecvBuffers_800C1480[2][36];

int SECTION(".gMtsPadInitStates_800C14F0") gMtsPadInitStates_800C14F0[2];

unsigned char SECTION(".gMtsPadSendBuffers_800C14D0") gMtsPadSendBuffers_800C14D0[2][8];

long                     SECTION(".gMemoryCardFiles_800B52C8") gHardware_end_io_800B52C8;
long                     SECTION(".gMemoryCardFiles_800B52C8") gHardware_end_write_800B52CC;
long                     SECTION(".gMemoryCardFiles_800B52C8") gHardware_timeout_800B52D0;
long                     SECTION(".gMemoryCardFiles_800B52C8") gHardware_new_device_800B52D4;
long                     SECTION(".gMemoryCardFiles_800B52C8") gSoftware_end_io_800B52D8;
long                     SECTION(".gMemoryCardFiles_800B52C8") gSoftware_end_write_800B52DC;
long                     SECTION(".gMemoryCardFiles_800B52C8") gSoftware_timeout_800B52E0;
long                     SECTION(".gMemoryCardFiles_800B52C8") gSoftware_new_device_800B52E4;
TMemCardFunc             SECTION(".gMemoryCardFiles_800B52C8") gHwCard_do_op_800B52E8;
TMemCardFunc             SECTION(".gMemoryCardFiles_800B52C8") gSwCard_do_op_800B52EC;
volatile TMemCardSetFunc SECTION(".gMemoryCardFiles_800B52C8") gSwCardLastOp_800B52F0;
volatile TMemCardSetFunc SECTION(".gMemoryCardFiles_800B52C8") gHwCardLastOp_800B52F4;
struct mem_card          SECTION(".gMemoryCardFiles_800B52C8") gMemCards_800B52F8[2];
volatile long            SECTION(".gMemoryCardFiles_800B52C8") gMemCard_io_size_800B5648;

GCL_Vars SECTION(".gGcl_memVars_800b4588") gGcl_memVars_800b4588;

RadioMemory   SECTION(".gRadioMemory_800BDB38") gRadioMemory_800BDB38[RADIO_MEMORY_COUNT] = {};
unsigned char SECTION(".gRadioMemory_800BDB38") gBulNames_800BDC78[64];

Actor SECTION(".gDgdActor2_800B3750") gDgdActor2_800B3750;
Actor SECTION(".gDgdActor2_800B3750") gDgdActor1_800B3770;
int   SECTION(".gDgdActor2_800B3750") dword_800B3790;

DG_TEX SECTION(".gTextureRecs_800B1F50") gTextureRecs_800B1F50[512];

unsigned char SECTION(".gPcxBuffer_800B3798") pcxBuffer_800B3798[128];

GCL_FileData SECTION(".gGCL_fileData_800B3C18") gGCL_fileData_800B3C18;

map_record SECTION(".gMapRecs_800B7910") gMapRecs_800B7910[16];

MenuMan_Inventory_14h_Unk SECTION(".gMenuRightItems_800BD888") gMenuRightItems_800BD888[MENU_ITEMS_RIGHT_COUNT];

MenuMan_Inventory_14h_Unk SECTION(".stru_800BD4B0")
    stru_800BD4B0[6]; // TODO: Based on gItemInfos_8009E484 field_4 this could be up to 30?
                      //
MenuMan_Inventory_14h_Unk SECTION(".gMenuMan_800BD5A0") dword_800BD5A0;

Actor_MenuMan SECTION(".gMenuMan_800BD360") gMenuMan_800BD360;

unsigned int SECTION(".gStuff_800B52C0") fs_stream_task_state_800B52C0;

unsigned char SECTION(".gPrimBackingBuffers_800B9360") gPrimBackingBuffers_800B9360[2][8192];

struct Loader_Record *SECTION(".gLoaderRec_800B5288") gLoaderRec_800B5288;
int                   SECTION(".gLoaderRec_800B5288") gLoaderStartTime_800B528C;
int                   SECTION(".gLoaderRec_800B5288") gOverlayBinSize_800B5290;
int                   SECTION(".gLoaderRec_800B5288") gSaveCache_800B5294;

GameState_800B4D98 SECTION(".gGcl_gameStateVars_800B44C8") gGcl_gameStateVars_800B44C8;

int SECTION(".gTaskIdx_800C0DB0") gTaskIdx_800C0DB0;

mts_task SECTION(".gTasks_800C0C30") gTasks_800C0C30[12];

int SECTION(".gMts_bits_800C0DB4") gMts_bits_800C0DB4;

CAMERA SECTION(".GM_CameraList_800B7718") GM_CameraList_800B7718[8];

CAMERA SECTION(".gCamera_param_a_800B780C") gCamera_param_a_800B780C;

GCL_Vars SECTION(".gGcl_vars_800B3CC8") gGcl_vars_800B3CC8;

array_800B933C_child  SECTION(".gStuff_800B933C") array_800B933C[array_800B933C_SIZE]; // todo figure out
dword_800B9358_struct SECTION(".gStuff_800B933C") array_800B9358[2];                   // todo figure out real size

char SECTION(".gStageName_800B4D88") gStageName_800B4D88[16];

DG_TEX SECTION(".gMenuTextureRec_800B58B0") gMenuTextureRec_800B58B0;

BindStruct SECTION(".gBindsArray_800b58e0") gBindsArray_800b58e0[128];

Actor_JimCtrl SECTION(".gJimCtrlActor_800B82F0") jimCtrlActor_800B82F0;

GV_Messages SECTION(".gMessageQueue_800B0320") gMessageQueue_800B0320[2];

GM_Target SECTION(".gTargets_800B64E0") gTargets_800B64E0[64];

CacheSystems SECTION(".CacheSystems_800ACEF0") GV_CacheSystem_800ACEF0;

TFileExtHandler SECTION(".gFileExtHandlers_800ACE80") gFileExtHandlers_800ACE80[MAX_FILE_HANDLERS];

GameState_800B4D98 SECTION(".gGameState_800B4D98") gGameState_800B4D98;

Homing_Target SECTION(".gHomingTargets_800B8230") gHomingTargets_800B8230[8];

AreaHistory     SECTION(".gAreaHistory_800B5850") gAreaHistory_800B5850;
char            SECTION(".gAreaHistory_800B5850") exe_name_800B5860[32];
Actor_GM_Daemon SECTION(".gAreaHistory_800B5850") GM_Daemon_800B5880;

void SECTION(".pfn_800BDFB0") (*pfn_800BDFB0)();

int SECTION(".argstack_800B3C28") argstack_800B3C28[32];

unsigned char *SECTION(".commandlines_800B3CA8") commandlines_800B3CA8[8];

unsigned short SECTION(".pfn_800BDFB4") (*pfn_800BDFB4)(unsigned short);

u_long SECTION(".image_data_800B3818") image_data_800B3818[256];

GV_PAD SECTION(".GV_PadData_800B05C0") GV_PadData_800B05C0[4];

GV_Heap SECTION(".MemorySystems_800AD2F0") MemorySystems_800AD2F0[3];

unsigned char SECTION(".heap_80182000") heap_80182000[0x5E000];

unsigned char SECTION(".heap_80117000") heap_80117000[0x6b000];

struct ActorList SECTION(".0x800ACC18") gActorsList_800ACC18[ACTOR_LIST_COUNT];

DG_OBJS *SECTION(".StageObjs_800B7890") StageObjs_800B7890[32];

int SECTION(".int_800B4E74") int_800B4E74;

mts_msg *SECTION(".D_800C0C00") D_800C0C00;
mts_msg *SECTION(".D_800C0C00") D_800C0C04;

int SECTION(".int_800B5298") fs_stream_ref_count_800B5298;

void *SECTION(".fs_stream_heap_800B52A4") fs_stream_heap_800B52A4;
void *SECTION(".fs_stream_heap_800B52A4") fs_stream_heap_end_800B52A8;
int   SECTION(".fs_stream_heap_800B52A4") fs_stream_heapSize_800B52AC;

int SECTION(".int_800B4E58") cd_bios_task_state_800B4E58;

DG_FixedLight SECTION(".bss_800B1E08") gFixedLights_800B1E08[8];

int      SECTION(".dword_800B0630") dword_800B0630[68];
int      SECTION(".dword_800B0630") dword_800B0740[516];
int      SECTION(".dword_800B0630") dword_800B0F50[4];
DG_OBJS *SECTION(".dword_800B0630") dword_800B0F60[8];
DG_OBJS *SECTION(".dword_800B0630") dword_800B0F80[256];
DR_ENV   SECTION(".dword_800B0630") stru_800B1380[2];

GM_Control *SECTION(".tenage_ctrls_800BDD30") tenage_ctrls_800BDD30[16];
int         SECTION(".tenage_ctrls_800BDD30") tenage_ctrls_count_800BDD70;

Jirai_unknown SECTION(".stru_800BDD78") stru_800BDD78[16];

Jirai_unknown SECTION(".stru_800BDE78") stru_800BDE78[8];

UnkCameraStruct2 SECTION(".word_800B77E8") gUnkCameraStruct2_800B77E8;
