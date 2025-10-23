
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
  int *new_var2;
  OpenWork *new_var;
  RGBElement *base = (RGBElement *) (((char *) work) + 0x18C);
  short temp;
  new_var = work;
  switch (new_var->fA8C)
  {
    case 0:
      RGBElement *elem = &base[index];
      if (new_var->f178 >= 0x80)
    {
      new_var->fA8C = (double) 1;
      new_var->f178 = 0;
    }
      break;

    new_var2 = &new_var->f178;
    case 1:
      temp = *new_var2;
      elem->r = temp;
      elem->g = temp;
      elem->b = temp;
      if (temp >= 0x80)
    {
      new_var->fA8C = 2;
    }
      break;

    case 2:
      temp = *new_var2;
      temp = 0x80 + (temp * 4);
      elem->r = temp;
      elem->g = temp;
      elem->b = temp;
      if ((*new_var2) >= 0x1F)
    {
      new_var->fA8C = 3;
    }
      break;

    case 3:
      temp = *new_var2;
      temp = 0xFF - ((temp * 4) / 3);
      elem->r = temp;
      elem->g = temp;
      elem->b = temp;
      if ((*new_var2) >= 0x60)
    {
      new_var->fA8C = 4;
      new_var->f178 = 0;
      elem->r = 0x80;
      elem->g = 0x80;
      elem->b = 0x80;
    }
      break;

    case 4:
      break;

  }

}
