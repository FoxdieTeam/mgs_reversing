#include "gcl.h"

extern int          dword_800AB9E4;
extern int          dword_800ABA28;
extern int          game_state_flags_800AB3CC;

extern void         item_all_items_and_weapons_unknown2_80033500(void);
extern void         item_all_items_and_weapons_unknown_80033560(void);
extern unsigned int sub_8002CA48(void);
extern void         Menu_scale_80038E28(int);


int GCL_Command_menu_8002CAAC(void)
{
    if (GCL_GetParam_80020968('j'))
    {
        if (GCL_GetNextParamValue_80020AD4() & 1)
        {
            game_state_flags_800AB3CC |= 0x800000;
        }
        else 
        {
            game_state_flags_800AB3CC &= 0xff7fffff;
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
            game_state_flags_800AB3CC |= 0x80000;
        }
        else 
        {
            game_state_flags_800AB3CC &= 0xfff7ffff;
        }
    }

    
    if (GCL_GetParam_80020968('l'))
    {
        switch (GCL_GetNextParamValue_80020AD4())
        {
            case 0:
                game_state_flags_800AB3CC |= 0x20000;
                break;
            case 1:
            case 3:
                game_state_flags_800AB3CC &= 0xfffdffff;
                break;
            case 2:
                game_state_flags_800AB3CC |= 0x10000;
                break;
        }
    }
    
    if (GCL_GetParam_80020968('r'))
    {
        switch (GCL_GetNextParamValue_80020AD4())
        {
            case 0:
                game_state_flags_800AB3CC |= 0x400000;
                break;
            case 1:
                game_state_flags_800AB3CC &= 0xffbfffff;
                break;
            case 2:
                game_state_flags_800AB3CC |= 0x200000;
                break;
            case 3:
                game_state_flags_800AB3CC |= 0x100000;
                break;
        }
    }

    if (GCL_GetParam_80020968('p'))
    {
        if (GCL_GetNextParamValue_80020AD4() & 1)
        {
            game_state_flags_800AB3CC |= 0x4000;
        }
        else 
        {
            game_state_flags_800AB3CC &= 0xffffbfff;
        }
    }

    if (GCL_GetParam_80020968('s'))
    {
        Menu_scale_80038E28(GCL_GetNextParamValue_80020AD4());
    }

    if (GCL_GetParam_80020968('w'))
    {
        dword_800AB9E4 = sub_8002CA48();
    }

    if (GCL_GetParam_80020968('i'))
    {
        dword_800ABA28 = sub_8002CA48();
    }
    return 0;
}
