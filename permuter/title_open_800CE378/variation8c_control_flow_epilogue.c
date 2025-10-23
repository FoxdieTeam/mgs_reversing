/**
 * Variation 8c: Control Flow Epilogue Placement
 *
 * Hypothesis: Restructure to place shared exit immediately after case 0
 * This matches target assembly where case 0 falls through to exit at 0x58
 *
 * Key insight from target assembly:
 * - Case 0 code ends, then shared exit (jr ra + sw zero,0x178)
 * - Cases 1 and 2 jump to that shared exit with "j 58"
 * - Case 3 and 4 come after the shared exit
 *
 * Strategy: Let case 0 flow into shared cleanup naturally, then continue
 * with remaining cases. This should place cleanup at correct location.
 */

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

    /* PATTERN 1: Pointer arithmetic instead of array indexing */
    elem = (RGBElement *)((char *)work + 0x18C);
    elem += index;

    switch (work->fA8C)
    {
        case 0:
            if (work->f178 >= 0x80)
            {
                work->fA8C = 1;
                goto state_changed;  /* Jump to shared cleanup placed after case 0 */
            }
            break;

        /* Shared cleanup placed immediately after case 0, before remaining cases */
        state_changed:
            work->f178 = 0;
            return;

        case 1:
            /* PATTERN 2: Descriptive variable name "shade" instead of "temp" */
            shade = work->f178;
            elem->r = shade;
            elem->g = shade;
            elem->b = shade;
            /* PATTERN 3: Re-read work->f178 instead of using cached shade */
            if (work->f178 >= 0x80)
            {
                work->fA8C = 2;
                goto state_changed;
            }
            break;

        case 2:
            shade = work->f178;
            shade = (shade * 4) + 0x80;
            elem->r = shade;
            elem->g = shade;
            elem->b = shade;
            /* PATTERN 3: Re-read work->f178 instead of comparing modified shade */
            if (work->f178 >= 0x1F)
            {
                work->fA8C = 3;
                goto state_changed;
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
