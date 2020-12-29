typedef struct NFile
{
    unsigned int unknown0;
    unsigned char *unknown1;
} NFile;

int n_file_handler_8001F5F8(unsigned char *pFileData, int fileNameHashed)
{
  NFile *n = (NFile *)pFileData;
  n->unknown1 = (unsigned char *)n + (unsigned int)n->unknown1;
  return 1;
}
