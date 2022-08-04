#include "libgcl/gcl.h"

extern int          GM_DisableWeapon_800AB9E4;
extern int          GM_DisableItem_800ABA28;
extern int          GM_GameStatus_800AB3CC;

void         item_all_items_and_weapons_unknown2_80033500(void);
void         item_all_items_and_weapons_unknown_80033560(void);
unsigned int GCL_Command_menu_helper_8002CA48(void);
void         MENU_SetRadarScale_80038E28(int);


int GCL_Command_menu_8002CAAC(void)
{
    if (GCL_GetParam_80020968('j'))
    {
        if (GCL_GetNextParamValue_80020AD4() & 1)
        {
            GM_GameStatus_800AB3CC |= 0x800000;
        }
        else 
        {
            GM_GameStatus_800AB3CC &= 0xff7fffff;
        }
    }

    if (GCL_GetParam_80020968('n'))
    {
        if (GCL_GetNextParamValue_80020AD4() & 1)
        {
            item_all_items_and_weapons_unknown2_80033500();
        }
        else 
        {
            item_all_items_and_weapons_unknown_80033560();
        }
    }

    if (GCL_GetParam_80020968('m'))
    {
        if (!(GCL_GetNextParamValue_80020AD4() & 1))
        {
            GM_GameStatus_800AB3CC |= 0x80000;
        }
        else 
        {
            GM_GameStatus_800AB3CC &= 0xfff7ffff;
        }
    }

    
    if (GCL_GetParam_80020968('l'))
    {
        switch (GCL_GetNextParamValue_80020AD4())
        {
            case 0:
                GM_GameStatus_800AB3CC |= 0x20000;
                break;
            case 1:
            case 3:
                GM_GameStatus_800AB3CC &= 0xfffdffff;
                break;
            case 2:
                GM_GameStatus_800AB3CC |= 0x10000;
                break;
        }
    }
    
    if (GCL_GetParam_80020968('r'))
    {
        switch (GCL_GetNextParamValue_80020AD4())
        {
            case 0:
                GM_GameStatus_800AB3CC |= 0x400000;
                break;
            case 1:
                GM_GameStatus_800AB3CC &= 0xffbfffff;
                break;
            case 2:
                GM_GameStatus_800AB3CC |= 0x200000;
                break;
            case 3:
                GM_GameStatus_800AB3CC |= 0x100000;
                break;
        }
    }

    if (GCL_GetParam_80020968('p'))
    {
        if (GCL_GetNextParamValue_80020AD4() & 1)
        {
            GM_GameStatus_800AB3CC |= 0x4000;
        }
        else 
        {
            GM_GameStatus_800AB3CC &= 0xffffbfff;
        }
    }

    if (GCL_GetParam_80020968('s'))
    {
        MENU_SetRadarScale_80038E28(GCL_GetNextParamValue_80020AD4());
    }

    if (GCL_GetParam_80020968('w')) // weapon
    {
        GM_DisableWeapon_800AB9E4 = GCL_Command_menu_helper_8002CA48();
    }

    if (GCL_GetParam_80020968('i')) // item
    {
        GM_DisableItem_800ABA28 = GCL_Command_menu_helper_8002CA48();
    }
    return 0;
}
