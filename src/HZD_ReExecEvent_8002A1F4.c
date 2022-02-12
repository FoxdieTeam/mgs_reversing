

extern void sub_8002A090(int param_1, unsigned short *param_2, unsigned int param_3, unsigned int param_4);

void HZD_ReExecEvent_8002A1F4(int param_1, unsigned short *param_2, unsigned int param_3)

{
    if ((param_3 & 0x200) != 0)
    {
        sub_8002A090(param_1, param_2, param_3, 0xd5cc);
    }
    if ((param_3 & 0x100) != 0)
    {
        sub_8002A090(param_1, param_2, param_3, 0xdd2);
    }
    return;
}
