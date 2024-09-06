#ifndef _LIBFS_H_
#define _LIBFS_H_

#include "cdbios.h"
#include "Game/loader.h"

typedef struct _FS_FILE_INFO
{
    const char *name;
    int         sector;
} FS_FILE_INFO;

// TODO: This is a stage file
typedef struct _FS_FILE {
    char    name[8];
    int     offset;
} FS_FILE;

typedef struct _FS_FILE_TABLE {
    int      start;
    int      size;
    int      count;
    FS_FILE *files;
} FS_FILE_TABLE;

typedef struct _FS_MOVIE_FILE
{
    unsigned short id;
    unsigned short frame;
    int            pos;
} FS_MOVIE_FILE;

typedef struct _FS_MOVIE_FILE_TABLE
{
    int           tablenum;
    FS_MOVIE_FILE files[8];
} FS_MOVIE_FILE_TABLE;

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

// CdlCB CdReadCallback( CdlCB func );
// CdlCB CdReadMode( CdlCB func );
// void DsReadyCallback( void (*func)(u_char, u_char*) );
// void DsDataCallback( void (*func)(u_char, u_char*) );

// int PCinit(void);
// int PCopen(const char *name, int flags, int perms);
// int PCread(int fd, char *buff, int len);
// int PCclose(int fd);

/* fscd.c */
extern FS_FILE_INFO fs_file_info[];

#define FILEID_STAGE    0   // "cdrom:\\MGS\\STAGE.DIR;1"
#define FILEID_RADIO    1   // "cdrom:\\MGS\\RADIO.DAT;1"
#define FILEID_FACE     2   // "cdrom:\\MGS\\FACE.DAT;1"
#define FILEID_ZMOVIE   3   // "cdrom:\\MGS\\ZMOVIE.STR;1"
#define FILEID_VOX      4   // "cdrom:\\MGS\\VOX.DAT;1"
#define FILEID_DEMO     5   // "cdrom:\\MGS\\DEMO.DAT;1"
#define FILEID_BRF      6   // "cdrom:\\MGS\\BRF.DAT;1"

int  FS_ResetCdFilePosition(void *pHeap);
void FS_CDInit(void);
void FS_LoadFileRequest(int dirFile, int startSector, int sectorSize, void *pBuffer);
int  FS_LoadFileSync(void);

/* cdbios.c */
void MakeFullPath(int, char *);
int  CDBIOS_Reset(void);
void CDBIOS_Stop(void);
void CDBIOS_Error(void);
void CDBIOS_SyncCallback(u_char status, u_char *result);
void CDBIOS_ReadyCallback(u_char status, u_char *result);
void CDBIOS_Main(void);
void CDBIOS_TaskStart(void);
void CDBIOS_ReadRequest(void *pHeap, unsigned int startSector, unsigned int sectorSize, void *fnCallBack);
int  CDBIOS_ReadSync(void);
void CDBIOS_ForceStop(void);
int  CDBIOS_TaskState(void);
int  FS_CdMakePositionTable(char *pHeap, FS_FILE_INFO *file_info);

/* cdstage.c */
void FS_CdStageFileInit(void *pHeap, int startSector);
int  FS_CdGetStageFileTop(char *filename);

/* hdstage.c */
STAGE_FILE *FS_LoadStageRequest(const char *filename);
int  FS_LoadStageSync(STAGE_FILE *stage_file);
void FS_LoadStageComplete(STAGE_FILE *stage_file);

/* movie.c */
void FS_MovieFileInit(void *pHeap, int startSector);
FS_MOVIE_FILE *FS_GetMovieInfo( unsigned int toFind );

/* stream.c */
void FS_StreamTaskStart(int);
int  FS_StreamTaskState(void);
void FS_StreamTaskInit(void);
int  FS_StreamSync(void);
void FS_StreamCD(void);
int  FS_StreamGetTop(int is_movie);
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

/* memfile.c */
void FS_EnableMemfile( int read, int write );
void FS_ClearMemfile( void );
int FS_WriteMemfile( int id, int **buf_ptr, int size );
int FS_ReadMemfile( int id, int **buf_ptr );

#endif // _LIBFS_H_
