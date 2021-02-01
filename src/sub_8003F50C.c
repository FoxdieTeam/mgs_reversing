

extern int  game_state_flags_800AB3CC;

int sub_8003F50C(void)
{
    int temp_v0;

    temp_v0 = game_state_flags_800AB3CC & 0xFFFF7FFF;
    game_state_flags_800AB3CC = temp_v0;
    return temp_v0;
}
