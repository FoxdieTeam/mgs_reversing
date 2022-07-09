extern int dword_8009E544[];

int *sub_8003D6A8(int a1, int a2, int a3)
{

  int *v4;
  a2 = a2 * 7;
  v4 = &dword_8009E544[a2];
  *((int *) (a1 + 8)) = (int)v4;
  v4[6] = a3;
  return dword_8009E544;
}
