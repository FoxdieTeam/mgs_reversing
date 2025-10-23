
typedef struct _OpenWork OpenWork;
extern void title_open_800C4AD0(OpenWork *work, int arg1, int arg2);
void title_open_800D2374(OpenWork *work)
{
  int i;
  for (i = 0; i < 24; i++)
  {
    title_open_800C4AD0(work, i, 0);
  }

  if (work->f24BC != 0)
  {
    ;
    title_open_800C4AD0((OpenWork *) work->f24B4, 1, 0x6739);
    return;
  }
  if (((OpenWork *) work->f24B4)->f24EC != 0)
  {
    switch (((OpenWork *) work->f24B4)->f24AC)
    {
      case 0:
        title_open_800C4AD0((OpenWork *) work->f24B4, 0, 0);
        break;

      case 1:
        break;

      case 2:
        title_open_800C4AD0((OpenWork *) work->f24B4, 2, 0);
        break;

      case 3:
        title_open_800C4AD0((OpenWork *) work->f24B4, 3, 0);
        break;

      case 4:
        return;

      case 5:
        title_open_800C4AD0((OpenWork *) work->f24B4, 5, 0x6739);
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
