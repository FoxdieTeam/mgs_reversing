#define PCX_RLE_THRESHOLD 0xC0

unsigned char *pcx_file_handler_helper_8001F6BC(unsigned char *pcxData, unsigned char *imageData, int imageSize)
{
    unsigned char *palette;
    do
    {
        char maybeRunLength = *pcxData++;
        if (maybeRunLength <= PCX_RLE_THRESHOLD)
        {
            --imageSize;
            *imageData++ = maybeRunLength;
        }
        else
        {
            int runLength = maybeRunLength - PCX_RLE_THRESHOLD;
            char color = *pcxData++;
            imageSize -= runLength;
            while (--runLength >= 0)
            {
                *imageData++ = color;
            }
        }
        palette = pcxData;
    }
    while (imageSize > 0);
    return palette;
}
