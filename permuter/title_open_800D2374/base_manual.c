/* Manual mode test with PERM_GENERAL variations */

typedef struct _OpenWork
{
  char padding1[0x24AC];
  int f24AC;
  char padding2[(0x24B4 - 0x24AC) - 4];
  struct _OpenWork *f24B4;
  char padding3[(0x24BC - 0x24B4) - 4];
  int f24BC;
  char padding4[(0x24EC - 0x24BC) - 4];
  int f24EC;
} OpenWork;

extern void title_open_800C4AD0(OpenWork *work, int arg1, int arg2);

OpenWork *title_open_800D2374(OpenWork *work)
{
  PERM_GENERAL(int i, register int i, unsigned int i);

  for (i = 0; i < 24; i++)
  {
    title_open_800C4AD0(work, i, 0);
  }

  if (work->f24BC != 0)
  {
    return (OpenWork *) work->f24B4;
  }

  /* Try different ways to access f24AC and check f24EC */
  PERM_GENERAL(
    /* Variant 1: Load i before check (current best: 1655) */
    i = work->f24AC;
    if (work->f24EC != 0),

    /* Variant 2: Inline access in switch */
    if (work->f24EC != 0) PERM_RANDOMIZE(i = work->f24AC;),

    /* Variant 3: Use temp for work pointer */
    OpenWork *temp = work;
    i = temp->f24AC;
    if (temp->f24EC != 0)
  )
  {
    PERM_GENERAL(switch (i), switch (work->f24AC))
    {
      case 0:
        title_open_800C4AD0(work, 0, 0);
        break;

      PERM_GENERAL(
        /* Variant 1: Empty case 1 */
        case 1: break;,
        /* Variant 2: No case 1, goes to default */
      )

      case 2:
        PERM_GENERAL(
          /* Order 1: Original */
          title_open_800C4AD0(work, 1, 0x6739);
          title_open_800C4AD0(work, 2, 0);,
          
          /* Order 2: Swap calls */
          title_open_800C4AD0(work, 2, 0);
          title_open_800C4AD0(work, 1, 0x6739);
        )
        break;

      case 3:
        title_open_800C4AD0(work, 3, 0);
        break;

      case 4:
        return work;

      case 5:
        title_open_800C4AD0(work, 5, 0x6739);
        break;

      /* Collapse multiple returns */
      PERM_GENERAL(
        /* Variant 1: Separate cases */
        case 6: return work;
        case 7: return work;
        case 8: return work;
        case 9: return work;
        case 10: return work;,
        
        /* Variant 2: Fall-through */
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
          return work;
      )
    }
  }
  return work;
}
