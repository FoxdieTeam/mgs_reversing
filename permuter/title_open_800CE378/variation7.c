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

void title_open_800CE378(OpenWork *work, int index)
{
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
                return;  // KEY CHANGE: return instead of goto/break
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
                return;  // KEY CHANGE: return instead of goto/break
            }
            break;
        case 3:
            shade = work->f178;
            shade = 0xFF - ((shade * 4) / 3);
            elem->r = shade;
            elem->g = shade;
            elem->b = shade;
            if (work->f178 >= 0x60)
            {
                work->fA8C = 4;
                work->f178 = 0;
                elem->r = 0x80;
                elem->g = 0x80;
                elem->b = 0x80;
            }
            break;
        case 4:
            break;
    }
}
