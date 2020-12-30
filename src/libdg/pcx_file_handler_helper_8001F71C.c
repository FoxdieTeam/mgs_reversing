#include "linker.h"

#define PCX_RLE_THRESHOLD 0xC0

// The size of this buffer is just a guess based on the next address of a
// variable that IDA knows about.
unsigned char SECTION(".gPcxBuffer_800B3798") pcxBuffer[128];

unsigned char *pcx_file_handler_helper_8001F71C(
        unsigned char *pcxData, unsigned char *imageData, int bytesPerLine,
        int width, int height)
{
    int i = height;
    while (--i >= 0)
    {
        unsigned char *rp;
        unsigned char *gp;
        unsigned char *bp;
        unsigned char *ap;
        int lineRemaining;

        unsigned char *pos = pcxBuffer;
        lineRemaining = 4 * bytesPerLine;
        do
        {
            char maybeRunLength = *pcxData++;
            if (maybeRunLength <= PCX_RLE_THRESHOLD)
            {
                --lineRemaining;
                *pos++ = maybeRunLength;
            }
            else
            {
                int runLength = maybeRunLength - PCX_RLE_THRESHOLD;
                unsigned char color = *pcxData++;
                lineRemaining -= runLength;
                while (--runLength >= 0)
                {
                    *pos++ = color;
                }
            }
        }
        while (lineRemaining > 0);

        rp = pcxBuffer;
        gp = rp + bytesPerLine;
        bp = gp + bytesPerLine;
        ap = bp + bytesPerLine;
        for (lineRemaining = width; lineRemaining > 0; lineRemaining -= 4)
        {
            int r = *rp++;
            int g = *gp++;
            int b = *bp++;
            int a = *ap++;
            int shift = 128;
            int shiftEnd = 8 * (lineRemaining < 4);
            do
            {
                unsigned char color = 0;

                if (shift & r) color |= 1u;
                if (shift & g) color |= 2u;
                if (shift & b) color |= 4u;
                if (shift & a) color |= 8u;
                shift >>= 1;

                if (shift & r) color |= 0x10u;
                if (shift & g) color |= 0x20u;
                if (shift & b) color |= 0x40u;
                if (shift & a) color |= 0x80u;

                *imageData++ = color;
                shift >>= 1;
            }
            while (shift != shiftEnd);
        }
    }
    return pcxData;
}
