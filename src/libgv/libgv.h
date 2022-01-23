#ifndef LIBGV_H_
#define LIBGV_H_

#include "linker.h"

typedef struct
{
    int mId;
    void* mFileBuffer;
} LibGV_FileRecord;


typedef	struct	{
	unsigned short		address ;		 
	unsigned short		_len ;		 
	unsigned short		message[ 7  ] ;	 
	unsigned short		message_len;	 
} GV_MSG ; // from mem leak

#endif // LIBGV_H