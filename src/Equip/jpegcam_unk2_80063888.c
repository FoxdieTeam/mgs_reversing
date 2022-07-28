extern char aPHOTO[]; // "PHOTO %02d\n"
extern int sprintf_8008E878(char *buffer, const char *format, ...);

void jpegcam_unk2_80063888(char *param_1, int param_2)
{
    sprintf_8008E878(param_1, aPHOTO, *(char *)(param_2 + 6) - 0x40);
}
