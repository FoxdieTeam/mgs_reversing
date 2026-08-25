/**
 * @file    libfs.h
 * @brief   File System library header
 */

#ifndef __MGS_LIBFS_H__
#define __MGS_LIBFS_H__

#include <sys/types.h>
#include "cdbios.h"
#include "datacnf.h"

#define FS_SECTOR_SIZE     2048    // x1 CD-ROM sector
#define FS_CDLOAD_BUF_SIZE ( FS_SECTOR_SIZE * 48 )

// private to cdstage.c
typedef struct {
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

typedef struct {
    const char *name;
    u_int pos;
} FS_FILE_INFO;

typedef struct {
    u_short id;
    u_short frame;
    int pos;
} FS_MOVIE_FILE;

// private to memfile.c
typedef struct {
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

// NOTE: fs_file_info actually has FS_FILE_MAX+1 elements,
// but the last is a dummy entry to denote the end of the table.

enum {
    FS_FILE_STAGE,  // STAGE.DIR
    FS_FILE_RADIO,  // RADIO.DAT
    FS_FILE_FACE,   // FACE.DAT
    FS_FILE_MOVIE,  // ZMOVIE.STR
    FS_FILE_VOX,    // VOX.DAT
    FS_FILE_DEMO,   // DEMO.DAT
    FS_FILE_BRF,    // BRF.DAT
    FS_FILE_MAX,
};

int  FS_ResetCdFilePosition(void *buffer);
void FS_CdInit(void);
void FS_LoadFileRequest(int fileno, int offset, int size, void *buffer);
int  FS_LoadFileSync(void);
void MakeFullPath(char *name, char *full);

/* srchfile.c */
int  FS_CdMakePositionTable(char *buffer, FS_FILE_INFO *finfo);

/* cdstage.c */
void FS_CdStageFileInit(void *buffer, int pos);
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
void FS_StreamTaskStart(int sector);
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
void *FS_StreamGetData(int target_type);
int  FS_StreamGetSize(void *stream);
void FS_StreamUngetData(void *stream);
void FS_StreamClear(void *stream);
void FS_StreamClearType( void *stream, int target_type );
int  FS_StreamGetEndFlag(void);
int  FS_StreamIsForceStop(void);
void FS_StreamTickStart(void);
void FS_StreamSoundMode(void);
int  FS_StreamGetTick(void);

#endif // __MGS_LIBFS_H__
