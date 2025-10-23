
typedef struct _OpenWork OpenWork;
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
    work = (OpenWork *) work->f24B4;
    title_open_800C4AD0(work, 1, 0x6739);
    return;
  }
  new_var = work;
  if (work->f24EC != 0)
  {
    switch (new_var->f24AC)
    {
      case 0:
        title_open_800C4AD0(work, 0, 0);
        break;

      case 1:
        break;

      case 2:
        title_open_800C4AD0(new_var, 2, 0);
        break;

      case 3:
        title_open_800C4AD0(work, 3, 0);
        break;

      case 4:

      return;
      case 5:
        title_open_800C4AD0(new_var, 5, 0x6739);
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
