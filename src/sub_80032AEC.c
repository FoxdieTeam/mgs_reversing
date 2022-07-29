extern int GM_GameStatus_800AB3CC;
extern void sd_set_cli_800887EC(int code, int unused);

void sub_80032AEC(int byte_2, int byte_1, int byte_0)
{
    int lowest_byte;
    if (GM_GameStatus_800AB3CC > -1)
    {
        byte_2 &= 0xff;
        byte_1 &= 0xff;
        if (0x3f < byte_1)
        {
            byte_1 = 0x3f;
        }
        lowest_byte = byte_0 & 0xff;
        sd_set_cli_800887EC(byte_2 << 0x10 | byte_1 << 8 | lowest_byte, 0);
    }
}
