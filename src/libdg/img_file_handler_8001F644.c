typedef struct ImgFile
{
    unsigned int unknown0;
    unsigned int unknown1;
    unsigned char *unknown2;
    unsigned char *unknown3;
    unsigned char *unknown4;
} ImgFile;

int img_file_handler_8001F644(unsigned char *pFileData, int fileNameHashed)
{
  ImgFile *img = (ImgFile *)pFileData;
  img->unknown2 = (unsigned char *)img + (unsigned int)img->unknown2;
  img->unknown3 = (unsigned char *)img + (unsigned int)img->unknown3;
  img->unknown4 = (unsigned char *)img + (unsigned int)img->unknown4;
  return 1;
}
