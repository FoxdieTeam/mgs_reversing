int font_get_buffer_size_80044F38(char* kcb)
{
    short val_1 = (kcb[2] + 0xc) * kcb[0] - kcb[2];
    int val_2 = (int)val_1 + 7;
    *(short*)(kcb + 0x1a) = val_1;
    if (val_2 < 0)
    {
        val_2 = (*(short*)(kcb + 0x1a)) + 14;
    }

    *(short*)(kcb + 0x18) = ((val_2>>3)<<2);
    *(short*)(kcb + 0x1c) = (kcb[3] + 12) * kcb[1] + 2;
    *(short*)(kcb + 0x10) = *(short*)(kcb + 0x18) / 2;
    *(short*)(kcb + 0x12) = *(short*)(kcb + 0x1c);

    return *(short*)(kcb + 0x18) * *(short*)(kcb + 0x1c) + 32;
}