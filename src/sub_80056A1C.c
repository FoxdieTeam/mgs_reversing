extern void sub_80050668(void);

void sub_80056A1C(int param_1)
{
  unsigned short* unk;
    
  unk = *(unsigned short **)(param_1 + 0x9b0);
  if (unk[1]) {
    sub_80050668();
  }
  return;
}
