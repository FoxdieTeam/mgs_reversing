int GCL_GetNextParamValue_80020AD4();                /* extern */
int GCL_Get_Param_Result_80020AA4();                /* extern */

char GM_NoiseSound_800B76E0[4][3];

void GM_set_noise_sound_8002E588(int arg0)
{
    int i;
    
    for (i = 1; i < 4; i++)
    {
        GM_NoiseSound_800B76E0[i][arg0] = GCL_GetNextParamValue_80020AD4();
    }
    
    if (GCL_Get_Param_Result_80020AA4())
    {
        GM_NoiseSound_800B76E0[0][arg0] = GCL_GetNextParamValue_80020AD4();
    }
}