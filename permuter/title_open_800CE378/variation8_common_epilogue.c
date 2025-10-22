/**
 * Variation 8: Common Epilogue Pattern
 *
 * Hypothesis: Force shared exit with goto to match target's j 0x3D0 pattern
 *
 * Target Assembly Pattern:
 * - Case 0: Falls through to shared exit at 0x800CE3D0
 * - Case 1: j 0x800CE3D0 (jump to shared exit)
 * - Case 2: j 0x800CE3D0 (jump to shared exit)
 * - Shared exit: jr ra + sw zero,0x178(a0) (clear f178 in delay slot)
 *
 * Strategy: Use goto to force cases 0, 1, 2 to jump to common cleanup code
 */

void title_open_800CE378(OpenWork *work, int index)
{
    RGBElement *elem;
    int shade;

    // PATTERN 1: Pointer arithmetic instead of array indexing
    elem = (RGBElement *)((char *)work + 0x18C);
    elem += index;

    switch (work->fA8C)
    {
        case 0:
            if (work->f178 >= 0x80)
            {
                work->fA8C = 1;
                goto state_changed;  // Force jump to shared cleanup
            }
            break;

        case 1:
            // PATTERN 2: Descriptive variable name "shade" instead of "temp"
            shade = work->f178;
            elem->r = shade;
            elem->g = shade;
            elem->b = shade;
            // PATTERN 3: Re-read work->f178 instead of using cached shade
            if (work->f178 >= 0x80)
            {
                work->fA8C = 2;
                goto state_changed;  // Force jump to shared cleanup
            }
            break;

        case 2:
            shade = work->f178;
            shade = (shade * 4) + 0x80;
            elem->r = shade;
            elem->g = shade;
            elem->b = shade;
            // PATTERN 3: Re-read work->f178 instead of comparing modified shade
            if (work->f178 >= 0x1F)
            {
                work->fA8C = 3;
                goto state_changed;  // Force jump to shared cleanup
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
    return;

state_changed:
    work->f178 = 0;  // Shared cleanup for cases 0, 1, 2
    return;
}
