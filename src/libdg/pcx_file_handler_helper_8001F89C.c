void pcx_file_handler_helper_8001F89C(unsigned char *pcxPalette, unsigned char *imageData, int width)
{
    unsigned short int *imagePalette = (unsigned short int *)imageData;
    int remaining = width - 1;
    while (remaining >= 0)
    {
        unsigned char r = *pcxPalette;
        unsigned char g = *(pcxPalette + 1);
        unsigned char b = *(pcxPalette + 2);
        unsigned short int color = !!((r | g | b) & 7) << 5;
        if (r || g || b) {
            color |= b >> 3;
            color <<= 5;
            color |= g >> 3;
            color <<= 5;
            color |= r >> 3;
        }
        *imagePalette++ = color;
        pcxPalette += 3;
        --remaining;
    }
}
