#ifndef _LIBFS_H_
#define _LIBFS_H_

#include <sys/types.h>
#include "cdbios.h"
#include "datacnf.h"

#define FS_SECTOR_SIZE  2048    // x1 CD-ROM sector

typedef struct _FS_STAGE_INFO   // private to stageld.c
{
    int           mode;
    CDBIOS_TASK  *task;
    void         *buffer;
    DATACNF      *datacnf;
    void         *tags;
    DATACNF_TAG  *tag_start1;   // todo: rename this
    DATACNF_TAG  *tag_end1;     // todo: rename this
    DATACNF_TAG  *tag_start2;   // todo: rename this
    DATACNF_TAG  *tag_end2;     // todo: rename this
    int           size;
    int           field_28;
    DATACNF_TAG  *tag;
    void         *current_ptr;
    int           remaining;
} FS_STAGE_INFO;

typedef struct _FS_FILE_INFO
{
    const char *name;
    u_int       pos;
} FS_FILE_INFO;

typedef struct _FS_MOVIE_FILE
{
    unsigned short id;
    unsigned short frame;
    int            pos;
} FS_MOVIE_FILE;

typedef struct _FS_MEMFILE
{
    int id;
    int *ptr;
    int size;
} FS_MEMFILE;

typedef char * (*TFsCallback)(char *);
typedef void (*TFsSoundCallback)(void);

/* select.c */
void FS_StartDaemon(void);
void FS_CdStageProgBinFix(void);

/* fscd.c */
extern FS_FILE_INFO fs_file_info[]; /* in file.cnf */

// NOTE: fs_file_info actually has FS_MAX_FILEID+1 elements,
// but the last is a dummy entry to denote the end of the table.

#define FS_FILEID_STAGE         (0)     // STAGE.DIR
#define FS_FILEID_RADIO         (1)     // RADIO.DAT
#define FS_FILEID_FACE          (2)     // FACE.DAT
#define FS_FILEID_ZMOVIE        (3)     // ZMOVIE.STR
#define FS_FILEID_VOX           (4)     // VOX.DAT
#define FS_FILEID_DEMO          (5)     // DEMO.DAT
#define FS_FILEID_BRF           (6)     // BRF.DAT
#define FS_MAX_FILEID           (7)

int  FS_ResetCdFilePosition(void *buffer);
void FS_CDInit(void);
void FS_LoadFileRequest(int fileno, int offset, int size, void *buffer);
int  FS_LoadFileSync(void);
void MakeFullPath(int, char *);

/* srchfile.c */
int  FS_CdMakePositionTable(char *buffer, FS_FILE_INFO *finfo);

/* cdstage.c */
void FS_CdStageFileInit(void *buffer, int sector);
int  FS_CdGetStageFileTop(char *filename);

/* stageld.c */
void *FS_LoadStageRequest(const char *dirname);
int  FS_LoadStageSync(void *info);
void FS_LoadStageComplete(void *info);

/* movie.c */
void FS_MovieFileInit(void *buffer, int sector);
FS_MOVIE_FILE *FS_GetMovieInfo( unsigned int to_find );

/* memfile.c */
void FS_EnableMemfile( int read, int write );
void FS_ClearMemfile( void );
int FS_WriteMemfile( int id, int **buf_ptr, int size );
int FS_ReadMemfile( int id, int **buf_ptr );

/* stream.c */
void FS_StreamTaskStart(int);
int  FS_StreamTaskState(void);
void FS_StreamTaskInit(void);
int  FS_StreamSync(void);
void FS_StreamCD(void);
int  FS_StreamGetTop(int is_demo);
int  FS_StreamInit(void *pHeap, int heapSize);
void FS_StreamStop(void);
void FS_StreamOpen(void);
void FS_StreamClose(void);
int  FS_StreamIsEnd(void);
void *FS_StreamGetData(int);
int  FS_StreamGetSize(int *ptr);
void FS_StreamUngetData(int addr);
void FS_StreamClear(void *stream);
void FS_StreamClearType( void *stream, int find );
int  FS_StreamGetEndFlag(void);
int  FS_StreamIsForceStop(void);
void FS_StreamTickStart(void);
void FS_StreamSoundMode(void);
int  FS_StreamGetTick(void);

#endif // _LIBFS_H_
