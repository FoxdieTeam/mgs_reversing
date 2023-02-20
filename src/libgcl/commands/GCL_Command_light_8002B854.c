#include "libgcl/libgcl.h"
#include "libdg/libdg.h"

int GCL_Command_light_8002B854(int argc, char **argv)
{
    int   light_dir;
    int   light_col;
    int   light_ambient;
    SVECTOR vec;

    if ((light_dir = GCL_GetParam_80020968('d')))
    {
        GCL_GetSV_80020A14((unsigned char *)light_dir, &vec);
        DG_SetMainLightDir_80019FF8(vec.vx, vec.vy, vec.vz);
    }
    if ((light_col = GCL_GetParam_80020968('c')))
    {
        GCL_GetSV_80020A14((unsigned char *)light_col, &vec);
        DG_SetMainLightCol_8001A048(vec.vx, vec.vy, vec.vz);
    }
    if ((light_ambient = GCL_GetParam_80020968('a')))
    {
        GCL_GetSV_80020A14((unsigned char *)light_ambient, &vec);
        DG_SetAmbient_80019F80(vec.vx, vec.vy, vec.vz);
    }
    return 0;
}
