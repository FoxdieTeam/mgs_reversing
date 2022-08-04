#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "linker.h"

typedef struct DG_PcxFile
{
    unsigned char signature;
    unsigned char version;
    unsigned char encoding;
    unsigned char bpp;
    unsigned short xMin, yMin;
    unsigned short xMax, yMax;
    unsigned short hDpi, vDpi;
    unsigned char palette[48];
    unsigned char reserved0;
    unsigned char channels;
    unsigned short bytesPerLine;
    unsigned short paletteMode;
    unsigned short hres, vres;
    // Unused 54 bytes in official PCX file format
    // MGS HEADER
    unsigned short mgsMagic; // always 1234
    unsigned short flags;
    unsigned short px, py; // pixels
    unsigned short cx, cy; // clut
    unsigned short n_colors;
    unsigned char unused1[40];
    // Image data
    unsigned char data[0];
} DG_PcxFile;

typedef struct DG_Image
{
    RECT dim;
    unsigned char data[512];
} DG_Image;

extern int GV_Clock_800AB920;

void LoadImage_8008FB10(RECT *, unsigned char *);
void GV_FreeMemory2_80016078(unsigned int, void **);
void *GV_AllocMemory2_80015ED8(int which, int size, void **type);
void DG_LoadInitPcx_helper_8001D880(unsigned short param_1, unsigned short param_2, unsigned short param_3,
                                    DG_Image *param_4, DG_Image *param_5, short param_6);

#define PCX_RLE_THRESHOLD 0xC0

unsigned char *pcx_file_read_8BPP_8001F6BC(unsigned char *pcxData, unsigned char *imageData, int imageSize)
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
    } while (imageSize > 0);
    return palette;
}

// The size of this buffer is just a guess based on the next address of a
// variable that IDA knows about.
unsigned char SECTION(".gPcxBuffer_800B3798") pcxBuffer[128];

unsigned char *pcx_file_read_4BPP_8001F71C(unsigned char *pcxData, unsigned char *imageData, int bytesPerLine,
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
        } while (lineRemaining > 0);

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

                if (shift & r)
                    color |= 1u;
                if (shift & g)
                    color |= 2u;
                if (shift & b)
                    color |= 4u;
                if (shift & a)
                    color |= 8u;
                shift >>= 1;

                if (shift & r)
                    color |= 0x10u;
                if (shift & g)
                    color |= 0x20u;
                if (shift & b)
                    color |= 0x40u;
                if (shift & a)
                    color |= 0x80u;

                *imageData++ = color;
                shift >>= 1;
            } while (shift != shiftEnd);
        }
    }
    return pcxData;
}

void pcx_file_read_palette_8001F89C(unsigned char *pcxPalette, unsigned char *imageData, int width)
{
    unsigned short *imagePalette;
    int remaining;
    unsigned char r, g, b;
    unsigned short color;

    imagePalette = (unsigned short *)imageData;
    remaining = width;
    while (--remaining >= 0)
    {
        r = *pcxPalette;
        g = *(pcxPalette + 1);
        b = *(pcxPalette + 2);
        color = !!((r | g | b) & 7) << 5;
        if (r || g || b)
        {
            color |= b >> 3;
            color <<= 5;
            color |= g >> 3;
            color <<= 5;
            color |= r >> 3;
        }
        *imagePalette++ = color;
        pcxPalette += 3;
    }
}

int DG_LoadInitPcx_8001F920(unsigned char *pFileData, int fileNameHashed)
{
    DG_PcxFile *pcx;
    unsigned short flags;
    int xMin, yMin;
    int width, height;
    DG_Image *images;

    pcx = (DG_PcxFile *)pFileData;
    flags = pcx->flags;

    xMin = pcx->xMin - 1;
    yMin = pcx->yMin - 1;
    width = pcx->xMax - xMin;
    height = pcx->yMax - yMin;
    if (!(flags & 1))
    {
        width /= 2;
    }

    if (GV_AllocMemory2_80015ED8(GV_Clock_800AB920, width * height + 528, (void **)&images))
    {
        DG_Image *imageA;
        DG_Image *imageB;
        unsigned char *palette;

        imageB = images;
        imageB->dim.x = pcx->cx;
        imageB->dim.y = pcx->cy;
        imageB->dim.w = pcx->n_colors;
        imageB->dim.h = 1;

        imageA = images + 1;
        imageA->dim.x = pcx->px;
        imageA->dim.y = pcx->py;
        imageA->dim.w = width / 2;
        imageA->dim.h = height;

        if (flags & 1)
        {
            palette = pcx_file_read_8BPP_8001F6BC(pcx->data, imageA->data, width * height) + 1;
        }
        else
        {
            pcx_file_read_4BPP_8001F71C(pcx->data, imageA->data, pcx->bytesPerLine, width, height);
            palette = pcx->palette;
        }

        pcx_file_read_palette_8001F89C(palette, imageB->data, imageB->dim.w);
        LoadImage_8008FB10(&imageB->dim, imageB->data);
        LoadImage_8008FB10(&imageA->dim, imageA->data);
        GV_FreeMemory2_80016078(GV_Clock_800AB920, (void **)&images);

        if (fileNameHashed)
        {
            DG_LoadInitPcx_helper_8001D880((unsigned short)fileNameHashed, flags & 1, (flags & 0x30) >> 4, imageA,
                                           imageB, imageB->dim.w);
        }
        return 1;
    }

    return 0;
}
