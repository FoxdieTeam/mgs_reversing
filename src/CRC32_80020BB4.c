#include "linker.h"

// Used for save files
unsigned int crc32_80020BB4(int len, unsigned char* pData)
{
  unsigned int crc;
  int counter;
  unsigned char dataByte;
  
  crc = 0xffffffff;
  if (len != 0) {
    do {
      dataByte = *pData;
      crc ^=  dataByte; // crc = v0
      pData++;

      counter = 8;

      do {
        if ((crc & 1) != 0) 
        {
          crc = crc >> 1 ^ 0xedb88320;
        }
        else 
        {
          crc = crc >> 1;
        }
        counter--;
      } while (counter != 0);
      len--;
    } while (len != 0);
  }
  return ~crc;
}
