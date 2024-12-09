#ifndef _DATACNF_H_
#define _DATACNF_H_

#include <sys/types.h>

typedef struct _DATACNF_TAG
{
    u_short     id;         // basename strcode
    char        mode;       // memory region
    char        ext;        // filename extension
    int         size;       // size in bytes
} DATACNF_TAG;

typedef struct _DATACNF
{
    char        version;    // always 0x01
    char        pad;        //
    short       size;       // entire stage block (in number of CD-ROM sectors)
    DATACNF_TAG tags[0];
} DATACNF;

typedef struct _DARFILE_TAG
{
    u_short     id;         // basename strcode
    short       ext;        // filename extension
    int         size;       // size in bytes
} DARFILE_TAG;

#endif // _DATACNF_H_
