int GV_FileNameHashed_800152DC(int param_1,int param_2)
{
  param_2 -= 0x61;
  if (param_2 > 0x19) {
    param_2 = param_2 + 0x20;
  }
  return param_1 + param_2 * 0x10000;
}
