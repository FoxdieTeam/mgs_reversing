extern int GV_CacheID_800152DC(int hashedFileName, int param_2);
extern int GV_StrCode_80016CCC(const char* string );

//takes the file name to create strcode which is used
//to call cacheID along with the ext id.
int GV_CacheID2_800152FC(const char* fileName, int extID)
{
  int hashedFileName = GV_StrCode_80016CCC(fileName);
  return GV_CacheID_800152DC(hashedFileName, extID);
}
