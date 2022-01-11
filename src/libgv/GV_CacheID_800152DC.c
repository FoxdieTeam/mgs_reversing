
//returns a file's cache id using the file id and ext id.
int GV_CacheID_800152DC(int hashedFileName,int param_2)
{
  param_2 -= 0x61;
  if (param_2 > 0x19) {
    param_2 = param_2 + 0x20;
  }
  return hashedFileName + param_2 * 0x10000;
}
