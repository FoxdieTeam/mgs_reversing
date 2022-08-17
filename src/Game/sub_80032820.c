#include "game.h"

int sub_80032820(Point *out, SVECTOR *pos)
{
  if (sub_80032308(pos, 0, out) < 0)
  {
      return -1;
  }
  return 0;
}
