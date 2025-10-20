// title_open_800CDBF8 - Baseline conservative decompilation
// This is a first attempt to understand the function structure
// Assembly suggests complex struct manipulation and conditional branching

typedef struct {
    char padding1[0x178];
    int f178;
    char padding2[(0xA8C - 0x178) - 4];
    int fA8C;
} OpenWork;

typedef struct {
    char padding[4];
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char padding_end[33];
} RGBElement;

// Assembly analysis hints:
// - Loads from offset 0xA7C (state field check)
// - Branches at 0x0460007C (conditional)
// - Multiple function calls suggesting function dispatch
// - Memory access patterns suggest struct field updates
// - Repeated patterns suggest loop or switch cases

void title_open_800CDBF8(OpenWork *work, int index)
{
    // Conservative approach - structure similar to adjacent functions
    // but without assuming exact same pattern
    RGBElement *elem;
    int shade;

    elem = (RGBElement *)((char *)work + 0x18C);
    elem += index;

    switch (work->fA8C)
    {
        case 0:
            if (work->f178 >= 0x80)
            {
                work->fA8C = 1;
                work->f178 = 0;
            }
            break;
        case 1:
            shade = work->f178;
            elem->r = shade;
            elem->g = shade;
            elem->b = shade;
            if (work->f178 >= 0x80)
            {
                work->fA8C = 2;
            }
            break;
        case 2:
            shade = work->f178;
            shade = (shade * 4) + 0x80;
            elem->r = shade;
            elem->g = shade;
            elem->b = shade;
            if (work->f178 >= 0x1F)
            {
                work->fA8C = 3;
            }
            break;
        case 3:
            break;
    }
}
