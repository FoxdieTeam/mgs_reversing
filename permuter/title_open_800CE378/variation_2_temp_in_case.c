
typedef struct
{
  char padding1[0x178];
  int f178;
  char padding2[(0xA8C - 0x178) - 4];
  int fA8C;
} OpenWork;

typedef struct
{
  char padding[4];
  unsigned char r;
  unsigned char g;
  unsigned char b;
  char padding_end[33];
} RGBElement;

void title_open_800CE378(OpenWork *work, int index)
{
  // VARIATION 2: temp declared in each case where needed
  RGBElement *base = (RGBElement *)((char *)work + 0x18C);
  RGBElement *elem = &base[index];

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
    {
      int temp = work->f178;
      elem->r = temp;
      elem->g = temp;
      elem->b = temp;
      if (temp >= 0x80)
      {
        work->fA8C = 2;
      }
    }
      break;

    case 2:
    {
      int temp = work->f178;
      temp = (temp * 4) + 0x80;
      elem->r = temp;
      elem->g = temp;
      elem->b = temp;
      if (work->f178 >= 0x1F)
      {
        work->fA8C = 3;
      }
    }
      break;

    case 3:
    {
      int temp = work->f178;
      temp = 0xFF - ((temp * 4) / 3);
      elem->r = temp;
      elem->g = temp;
      elem->b = temp;
      if (work->f178 >= 0x60)
      {
        work->fA8C = 4;
        work->f178 = 0;
        elem->r = 0x80;
        elem->g = 0x80;
        elem->b = 0x80;
      }
    }
      break;

    case 4:
      break;
  }
}
