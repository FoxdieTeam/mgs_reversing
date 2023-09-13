#include "libgcl/libgcl.h"


extern int dword_800ABB8C;
int        dword_800ABB8C;

extern int dword_800ABB90;
int        dword_800ABB90;

extern int dword_800ABB48;
int        dword_800ABB48;

extern char aAtEUC[];   // = "@";
extern char aNoPlace[]; // = "NO PLACE";
extern char aCodeD[];   // = "code %d\n";

void sub_8004CF20(int code, char **param_2, char **param_3)
{
    int i;

    if (code == 0)
    {
        *param_2 = aNoPlace;
        *param_3 = aAtEUC;
    }
    GCL_SetArgTop_80020690((char *)dword_800ABB8C);
    printf(aCodeD, code);
    for (i = 0; i < code; i++) {
        if (GCL_Get_Param_Result_80020AA4() == 0)
        {
            return;
        }
        *param_2 = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
        if (dword_800ABB90 > 0 && dword_800ABB48 == 0)
        {
            *param_3 = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
        }
    }
}
