#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "gcl.h"

extern int gBinds_800ABA60;
int SECTION(".sbss") gBinds_800ABA60;

typedef struct LibGV_Msg
{
    short field_0_res_hash;
    short field_2_num_same_messages;
    short field_4_action_hash_or_ptr;
    short field_6_hash;
    short field_8_min1;
    short field_A_min1;
    short field_C_min1;
    short field_E;
    short field_10;
    short field_12_num_valid_fields;
} LibGV_Msg;

int GV_SendMessage_80016504(LibGV_Msg *);

int GCL_Command_mesg_8002C138(unsigned char *pScript)
{
    unsigned char *uParm1;
    int iVar1;
    int ret;
    short *pMsgDst;
    LibGV_Msg mesg;
    int count;

    mesg.field_0_res_hash = GCL_GetNextParamValue_80020AD4();
    pMsgDst = &mesg.field_4_action_hash_or_ptr;
    count = 0;
    while (uParm1 = GCL_Get_Param_Result_80020AA4(), uParm1 != 0x0)
    {
        int iVar2 = GCL_GetNextInt_800209E8(uParm1);
        *pMsgDst = (short)iVar2;
        pMsgDst++;
        count++;
    }
    mesg.field_12_num_valid_fields = count;
    iVar1 = GV_SendMessage_80016504(&mesg);
    ret = 0;
    if (iVar1 < 0)
    {
        ret = -1;
    }
    return ret;
}
