extern int GV_FileNameHashed_800152DC(int hashedFileName, int param_2);
extern int GV_StrCode_80016CCC(const char* string );

void GV_HashFileName_800152FC(const char* fileName, int param_2)
{
  int hashedFileName = GV_StrCode_80016CCC(fileName);
  GV_FileNameHashed_800152DC(hashedFileName, param_2);
}
