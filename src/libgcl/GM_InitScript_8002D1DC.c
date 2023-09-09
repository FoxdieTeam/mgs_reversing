#include "hash.h"
#include "libgcl.h"

GCL_COMMANDLIST Commands_8009D5CC[] = {
    {HASH_CMD_mesg, GCL_Command_mesg_8002C138},
    {HASH_CMD_trap, GCL_Command_trap_8002BD34},
    {HASH_CMD_chara, (TGCL_CommandFn)GCL_Command_chara_8002C1B0}, // TODO: Why does this one have a different signature?
    {HASH_CMD_map, GCL_Command_map_8002BB44},
    {HASH_CMD_hzd, GCL_Command_hzd_8002BD04},
    {HASH_CMD_camera, GCL_Command_camera_8002B8F0},
    {HASH_CMD_light, GCL_Command_light_8002B854},
    {HASH_CMD_start, GCL_Command_start_8002C22C},
    {HASH_CMD_load, GCL_Command_load_8002C308},
    {HASH_CMD_radio, GCL_Command_radio_8002C4A8},
    {HASH_CMD_str_status, GCL_Command_strstatus_8002C6A4},
    {HASH_CMD_demo, GCL_Command_demo_8002C890},
    {HASH_CMD_ntrap, GCL_Command_ntrap_8002BE20},
    {HASH_CMD_delay, GCL_Command_delay_8002C074},
    {HASH_CMD_pad, GCL_Command_pad_8002C988},
    {HASH_CMD_varsave, GCL_Command_varsave_8002C72C},
    {HASH_CMD_system, GCL_Command_system_8002C7C8},
    {HASH_CMD_sound, GCL_Command_sound_8002CA28},
    {HASH_CMD_menu, GCL_Command_menu_8002CAAC},
    {HASH_CMD_rand, GCL_Command_rand_8002CD94},
    {HASH_CMD_unk1, GCL_Command_unknown1_8002CDF4}, // ??
    {HASH_CMD_unk2, GCL_Command_unknown2_8002CFBC}, // ?? not in pc ver, demo thread related ??
    {HASH_CMD_print, GCL_Command_print_8002D0E4},
    {HASH_CMD_jimaku, GCL_Command_jimaku_8002D188}};

GCL_COMMANDDEF script_commands_8009D68C = {0, COUNTOF(Commands_8009D5CC), Commands_8009D5CC};

void GM_InitScript_8002D1DC(void)
{
    GCL_BindsInit_8002D1A8();
    GCL_AddCommMulti_8001FD2C(&script_commands_8009D68C);
}
