
extern unsigned char *  GCL_Get_Param_Result_80020AA4(void);
extern int              GCL_GetNextValue_800209E8(unsigned char *uParm1);

int GCL_GetNextParamValue_80020AD4(void)
{
    return GCL_GetNextValue_800209E8(GCL_Get_Param_Result_80020AA4());
}
