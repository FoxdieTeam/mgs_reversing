#ifndef _STRCTRL_H_
#define _STRCTRL_H_

#include "libgv/libgv.h"

// TODO: might be bigger if the jimctrl actually uses this
typedef struct  Actor_strctrl
{
  GV_ACT         field_0_actor;
  short         field_20_state;
  short         field_22_sub_state;
  short         field_24;
  short         field_26_flags;
  int           field_28;
  int           field_2C_map;
  int           field_30_voxStream;
  int           *field_34_pStreamData;
  int           field_38_proc;
  int           field_3C;
} Actor_strctrl;

// TODO: rename
Actor_strctrl   *GCL_Command_demo_helper_80037DD8(int base_sector, int gcl_proc);

//------------------------------------------------------------------------------
// strctrl.c

void            strctrl_act_helper_800377EC( Actor_strctrl *work );
void            strctrl_act_80037820( Actor_strctrl *actor );
void            strctrl_kill_80037AE4( Actor_strctrl *work );
Actor_strctrl   *strctrl_init_80037B64( int stream_code, int gcl_proc, int flags );
int             GM_StreamStatus_80037CD8( void );
void            GM_StreamPlayStart_80037D1C();
void            GM_StreamPlayStop_80037D64();
void            GM_StreamCancelCallback_80037DB8( void );
int             GM_StreamGetLastCode_80037DC8( void );
Actor_strctrl   *GCL_Command_demo_helper_80037DD8( int base_sector, int gcl_proc );
Actor_strctrl   *GM_VoxStream_80037E40( int vox_code, int proc );
Actor_strctrl   *sub_80037EE0(int vox_stream, int gcl_proc);

#endif // _STRCTRL_H_
