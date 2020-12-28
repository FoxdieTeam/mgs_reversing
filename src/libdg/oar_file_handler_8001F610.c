typedef struct OarFile
{
    unsigned char *deep;
    unsigned int recordSize;
    unsigned int count;
    unsigned char *start;
    char oarData[0];
} OarFile;

int oar_file_handler_8001F610(unsigned char *pFileData, int fileNameHashed)
{
    OarFile *oar = (OarFile *)pFileData;
    oar->deep = oar->oarData + 2 * ((oar->recordSize + 2) * oar->count);
    oar->start = oar->oarData;
    return 1;
}
