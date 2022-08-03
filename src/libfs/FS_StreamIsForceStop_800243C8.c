

extern int fs_stream_is_force_stop_8009D518;
extern int fs_stream_tick_start_8009D510;
extern int dword_8009D514;

int VSync_80098108(int);

int FS_StreamIsForceStop_800243C8(void)
{
    return fs_stream_is_force_stop_8009D518;
}

// TODO: the var might be part of a struct and the code
// takes a ptr to that struct, unknown currently
static inline int* GetTicksPtr(void)
{
    return &fs_stream_tick_start_8009D510;
}

void FS_StreamTickStart_800243D8()
{
    *GetTicksPtr() = VSync_80098108(-1);    
}

// for some reason no ptr access here
void FS_StreamSoundMode_80024404()
{
    fs_stream_tick_start_8009D510 = -1;
    dword_8009D514 = 1;
}