#include "menuman.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"

extern UnkJimakuStruct gUnkJimakuStruct_800BDA70;
extern int GV_PauseLevel_800AB928;

void NewJimaku_800495A8()
{
    const char *str;

    str = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
    gUnkJimakuStruct_800BDA70.field_40 = (int)GCL_Get_Param_Result_80020AA4();
    menu_JimakuWrite_800494E8(str, -1);

    if (GCL_GetParam_80020968('e'))
    {
        gUnkJimakuStruct_800BDA70.field_3C = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    else
    {
        gUnkJimakuStruct_800BDA70.field_3C = -1;
    }

    GV_PauseLevel_800AB928 |= 1;
    DG_FreeObjectQueue_800183D4();
}
