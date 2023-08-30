#include "libgcl/libgcl.h"
#include "Game/delay.h"

void sub_80029AEC(BindStruct *pBind, Res_Control_unknown *pSubCtrl, int a3, int a4)
{
    int f_4; // $v1
    int msg_type; // $a0
    int x; // $t0
    int y; // $t1
    int z; // $a1
    int f_10; // $v0
    GCL_ARGS gclArgs; // [sp+10h] [-28h] BYREF
    long args[8]; // [sp+18h] [-20h] BYREF

    f_4 = pSubCtrl->field_4_trigger_Hash_Name_or_camera_w;
    msg_type = pSubCtrl->field_0_scriptData_orHashedName;
    x = pSubCtrl->field_14_vec.vx;
    y = pSubCtrl->field_14_vec.vy;
    z= pSubCtrl->field_14_vec.vz;
    gclArgs.argc = 7;
    gclArgs.argv = args;
    f_10 = pBind->field_10_every;
    args[2] = a3;
    args[6] = a4;
    args[0] = f_4;
    args[1] = msg_type;
    args[3] = x;
    args[4] = y;
    args[5] = z;
    if ( f_10 )
    {
        GM_DelayedExecCommand_80033230(pBind->field_14_proc_and_block, &gclArgs, f_10);
    }
    else if ( (pBind->field_B_param_e & 0x80) != 0 )
    {
        GCL_ExecProc_8001FF2C(pBind->field_14_proc_and_block, &gclArgs);
    }
    else
    {
        GCL_ExecBlock_80020118((unsigned char *)pBind->field_14_proc_and_block, &gclArgs);
    }
}
