#include "linker.h"
#include "Script_tbl_map_8002BB44.h"
#include "gcl.h"
#include "libgv.h"

extern int gBinds_800ABA60;
int SECTION(".sbss") gBinds_800ABA60;

int GV_SendMessage_80016504(GV_MSG *);

int GCL_Command_mesg_8002C138(int argc, char **argv)
{
    unsigned char *uParm1;
    int iVar1;
    int ret;
    short *pMsgDst;
    GV_MSG mesg;
    int count;

    mesg.address = GCL_GetNextParamValue_80020AD4();
    pMsgDst = &mesg.message[0];
    count = 0;
    while (uParm1 = GCL_Get_Param_Result_80020AA4(), uParm1 != 0x0)
    {
        int iVar2 = GCL_GetNextInt_800209E8(uParm1);
        *pMsgDst = (short)iVar2;
        pMsgDst++;
        count++;
    }
    mesg.message_len = count;
    iVar1 = GV_SendMessage_80016504(&mesg);
    ret = 0;
    if (iVar1 < 0)
    {
        ret = -1;
    }
    return ret;
}
