#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct DG_PcxFile {
    unsigned char signature;
    unsigned char version;
    unsigned char encoding;
    unsigned char bpp;
    unsigned short int xMin;
    unsigned short int yMin;
    unsigned short int xMax;
    unsigned short int yMax;
    unsigned short hDpi;
    unsigned short vDpi;
    unsigned char palette[48];
    unsigned char reserved0;
    unsigned char channels;
    unsigned short int bytesPerLine;
    unsigned short int paletteMode;
    unsigned short int hres;
    unsigned short int vres;

    // extensions (54 bytes)
    unsigned short int unused0;
    unsigned short int flags;
    unsigned short int ax;
    unsigned short int ay;
    unsigned short int bx;
    unsigned short int by;
    unsigned short int bw;
    unsigned char unused1[40];

    // image data
    unsigned char data[0];
} DG_PcxFile;

typedef struct DG_Image {
    RECT dim;
    unsigned char data[512];
} DG_Image;

extern int gActiveBuffer_800AB920;

extern unsigned char* pcx_file_handler_helper_8001F6BC(unsigned char *, unsigned char *, int);
extern void pcx_file_handler_helper_8001F71C(unsigned char *, unsigned char *, unsigned short int, int, int);
extern void pcx_file_handler_helper_8001F89C(unsigned char *, unsigned char *, short int);
extern void LoadImage_8008FB10(RECT *, unsigned char *);
extern void System_void_allocation_80016078(unsigned int, void *);
extern unsigned int sub_80015ED8(unsigned int, int, DG_Image **);
extern void sub_8001D880(unsigned short int, unsigned short int, unsigned short int, DG_Image *, DG_Image *, short int);

int pcx_file_handler_8001F920(unsigned char *pFileData, int fileNameHashed)
{
    DG_PcxFile *pcx = (DG_PcxFile *)pFileData;
    unsigned short int flags = pcx->flags;

    int xMin;
    int yMin;
    int width;
    int height;
    DG_Image *images;

    xMin = pcx->xMin - 1;
    yMin = pcx->yMin - 1;
    width = pcx->xMax - xMin;
    height = pcx->yMax - yMin;
    if (!(flags & 1))
    {
        width /= 2;
    }

    if (sub_80015ED8(gActiveBuffer_800AB920, width * height + 528, &images))
    {
        DG_Image *imageA;
        DG_Image *imageB;
        unsigned char *palette;

        imageB = images;
        imageB->dim.x = pcx->bx;
        imageB->dim.y = pcx->by;
        imageB->dim.w = pcx->bw;
        imageB->dim.h = 1;

        imageA = images + 1;
        imageA->dim.x = pcx->ax;
        imageA->dim.y = pcx->ay;
        imageA->dim.w = width / 2;
        imageA->dim.h = height;

        if (flags & 1)
        {
            palette = pcx_file_handler_helper_8001F6BC(pcx->data, imageA->data, width * height) + 1;
        }
        else
        {
            pcx_file_handler_helper_8001F71C(pcx->data, imageA->data, pcx->bytesPerLine, width, height);
            palette = pcx->palette;
        }

        pcx_file_handler_helper_8001F89C(palette, imageB->data, imageB->dim.w);
        LoadImage_8008FB10(&imageB->dim, imageB->data);
        LoadImage_8008FB10(&imageA->dim, imageA->data);
        System_void_allocation_80016078(gActiveBuffer_800AB920, &images);

        if (fileNameHashed)
        {
            sub_8001D880((unsigned short int)fileNameHashed, flags & 1, (flags & 0x30) >> 4, imageA, imageB, imageB->dim.w);
        }
        return 1;
    }

    return 0;
}
