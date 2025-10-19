
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
inline int inline_fn(OpenWork *arg0)
{
  return arg0->f24BC;
}

void title_open_800D2374(OpenWork *work)
{
  int i;
  int new_var2;
  OpenWork *new_var;
  for (i = 0; i < 24; i++)
  {
    title_open_800C4AD0(work, i, 0);
  }

  if (inline_fn(work) != 0)
  {
    return;
  }
  new_var = work;
  i = 0;
  if (new_var->f24EC != 0)
  {
    new_var2 = 0;
    switch (work->f24AC)
    {
      case 0:
        title_open_800C4AD0(work, 0, new_var2);
        break;

      case 1:
        title_open_800C4AD0(work, 1, 0x6739);
        break;

      case 2:
        title_open_800C4AD0(work, 2, new_var2);
        break;

      case 3:
        title_open_800C4AD0(work, 3, i);
        break;

      case 4:
        return;

      case 5:
        title_open_800C4AD0(work, 5, 0x6739);
        break;

      case 6:
        return;

      case 7:
        return;

      case 8:
        return;

      case 9:

      case 10:
        return;

      return;
    }

  }
}
