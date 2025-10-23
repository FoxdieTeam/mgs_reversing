
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
void title_open_800D2374(OpenWork *work)
{
  int i;
  OpenWork *new_var;
  for (i = 0; i < 24; i++)
  {
    title_open_800C4AD0(work, i, 0);
  }

  if (work->f24BC != 0)
  {
    return;
  }
  if (work->f24EC != 0)
  {
    new_var = work;
    switch (new_var->f24AC)
    {
      case 0:
        title_open_800C4AD0(new_var, 0, 0);
        break;

      case 1:
        title_open_800C4AD0(new_var, 1, 0x6739);
        break;

      case 2:
        title_open_800C4AD0(new_var, 2, 0);
        break;

      case 3:
        title_open_800C4AD0(new_var, 3, 0);
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
        return;

      case 10:
        return;

    }

  }
}
