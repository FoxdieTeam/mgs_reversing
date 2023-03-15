#include "linker.h"


const char SECTION(".rdata") aStartTaskSdint[] = "Start Task:SdInt\n"; // 800135D0
const char SECTION(".rdata") aBlankDataAddrX[] = "blank_data_addr=%x\n";
const char SECTION(".rdata") aSpuWaveStartPt[] = "spu_wave_start_ptr=%x\n";
const char SECTION(".rdata") aSpuBgmStartPtr[] = "spu_bgm_start_ptr_r=%x\n";
const char SECTION(".rdata") aSpuBufferOver[] = "SPU Buffer Over!!\n";
const char SECTION(".rdata") aSpuBgmStartPtr_0[] = "spu_bgm_start_ptr_l=%x\n";
const char SECTION(".rdata") aSpuReverbBuffe[] = "SPU Reverb Buffer Over!!\n";
const char SECTION(".rdata") aSoundErrorSpuO[] = "SOUND ERROR:SPU OFF ENV ON(STR_TRACK_R=%x)\n";
const char SECTION(".rdata") aSoundErrorSpuO_0[] = "SOUND ERROR:SPU OFF ENV ON(STR_TRACK_L=%x)\n";
const char SECTION(".rdata") aSngDataX[] = "sng_data %X\n";
const char SECTION(".rdata") aWaveHeaderX[] = "wave_header %X\n";
const char SECTION(".rdata") aVoiceTblX[] = "voice_tbl %X\n";
const char SECTION(".rdata") aSeHeaderX[] = "se_header %X\n";
const char SECTION(".rdata") aSeDataX[] = "se_data %X\n";
const char SECTION(".rdata") aCdloadBufXXX[] = "CDLOAD_BUF %X %X %X\n";
const char SECTION(".rdata") aStrHeaderX[] = "str_header %X\n";
const char SECTION(".rdata") aCanceledStrFad[] = "Canceled STR FadeOut(%x:%x:%x)";
const char SECTION(".rdata") aStreamFilePosE[] = "Stream:File Pos Error\n";
const char SECTION(".rdata") aStartstreamXVo[] = "StartStream(%x:vol=%x)\n";
const int  SECTION(".rdata") jpt_8001378C[] = {0x8008272C, 0x8008272C, 0x8008267C, 0x8008268C, 0x800826CC};
const char SECTION(".rdata") aSoundStreaming[] = "\nSOUND STREAMING ERROR:NO LAST LEFT DATA\n";
const char SECTION(".rdata") aStrUnplaySizeX[] = "str_unplay_size=%x\n";
const char SECTION(".rdata") asc_800137E0[] = "*";
const int  SECTION(".rdata") jpt_800137E4[] = {0x80082828, 0x80082A28, 0x80082BC8, 0x80082D20, 0x800832BC, 0x80083358};
const char SECTION(".rdata") aErrorSeFileAlr[] = "ERROR:SE File Already Opened.\n";
const char SECTION(".rdata") aLoadsefileFile[] = "LoadSeFile:File Open Error(%x)\n";
const char SECTION(".rdata") aErrorWaveFileA[] = "ERROR:Wave File Already Opened.\n";
const char SECTION(".rdata") aLoadwavefileFi[] = "LoadWaveFile:File Open Error(%x)\n";
const char SECTION(".rdata") aSupOffsetXSize[] = "SUP OFFSET=%x:SIZE=%x\n";
const char SECTION(".rdata") aSrcXDstX[] = "    SRC=%x:DST=%x\n";
const char SECTION(".rdata") aBinOffsetX[] = "BIN OFFSET=%x\n";
const char SECTION(".rdata") aSpuOffsetXSize[] = "SPU OFFSET=%x:SIZE=%x\n";
const char SECTION(".rdata") aCompleteLoadSe[] = "Complete Load Se:%x\n";
const char SECTION(".rdata") aSdSngdataloadi[] = "SD_SngDataLoadInit\n";
const char SECTION(".rdata") aLoadinitD[] = "LoadInit %d\n";
const char SECTION(".rdata") asc_80013914[] = "$";
const char SECTION(".rdata") aSdWavLoadBufOv[] = "!!! SD WAV LOAD BUF OVER !!!\n";
const char SECTION(".rdata") aUnloadD[] = "unload %d\n";


const char SECTION(".rdata") aSngcodeX[] = "SngCode=%x\n";
const char SECTION(".rdata") aSongpauseon[] = "SongPauseOn\n";
const char SECTION(".rdata") aSongpauseoff[] = "SongPauseOff\n";
const char SECTION(".rdata") aSongfadein[] = "SongFadein\n";
const char SECTION(".rdata") aSongfadeoutPau[] = "SongFadeout&Pause\n";
const char SECTION(".rdata") aSongfadeoutSto[] = "SongFadeout&Stop\n";
const char SECTION(".rdata") aSongkaihimode[] = "SongKaihiMode\n";
const char SECTION(".rdata") aSongsyukanmode[] = "SongSyukanMode On\n";
const char SECTION(".rdata") aSongsyukanmode_0[] = "SongSyukanMode Off\n";
const char SECTION(".rdata") aSongstop[] = "SongStop\n";
const char SECTION(".rdata") aErrorSngPlayCo[] = "ERROR:SNG PLAY CODE(%x/%x)\n";
const char SECTION(".rdata") aSngStatusX[] = "sng_status=%x\n";
const char SECTION(".rdata") aSamesonghasalr[] = "SameSongHasAlreadyPlayed\n";
const char SECTION(".rdata") aSoundWorkIsBro[] = "*** SOUND WORK IS BROKEN !!! ***\n";
const char SECTION(".rdata") aSongEndXX[] = "*** song_end:%x -> %x        ***\n";
const char SECTION(".rdata") aSngFadeoutStar[] = "SNG FADEOUT START(status=%x)\n";
const char SECTION(".rdata") aSngFadeoutCanc[] = "SNG FADEOUT CANCELED(status=%x)\n";
const char SECTION(".rdata") aLoadsngdataFil[] = "LoadSngData:File Open Error(%x)\n";
const char SECTION(".rdata") aCompletedloads[] = "CompletedLoadSong(%x)\n";
const char SECTION(".rdata") aXaSoundStart[] = "***XA Sound Start***\n";
const char SECTION(".rdata") aXaSoundStop[] = "***XA Sound Stop***\n";
const char SECTION(".rdata") aSdcodeX[] = "SdCode=%x\n";
const char SECTION(".rdata") aToomuchbgmsoun[] = "***TooMuchBGMSoundCode(%x)***\n";
const char SECTION(".rdata") aSdsetLastStrea[] = "SdSet:Last Stream Not Terminated.(status=%x)\n";
const char SECTION(".rdata") aSdsetSameStrea[] = "SdSet:Same Stream is Already Played.(code=%x)\n";
const char SECTION(".rdata") aStrFoS[] = "*** STR FO(S) ***\n";
const char SECTION(".rdata") aStrFoM[] = "*** STR FO(M) ***\n";
const char SECTION(".rdata") aStrFoL[] = "*** STR FO(L) ***\n";
const char SECTION(".rdata") aStrFoLl[] = "*** STR FO(LL) ***\n";
const char SECTION(".rdata") aStrFiMAtNextSt[] = "*** STR FI(M) at Next STR ***\n";
const char SECTION(".rdata") aStrFiMStart[] = "*** STR FI(M) Start ***\n";
const char SECTION(".rdata") aErrStrFiM[] = "*** ERR:STR FI(M) ***\n";
const char SECTION(".rdata") aStrFiLAtNextSt[] = "*** STR FI(L) at Next STR***\n";
const char SECTION(".rdata") aStrFiLStart[] = "*** STR FI(L) Start ***\n";
const char SECTION(".rdata") aErrStrFiL[] = "*** ERR:STR FI(L) ***\n";
const char SECTION(".rdata") aStrFoSStop[] = "*** STR FO(S)+STOP ***\n";
const char SECTION(".rdata") aStrFoMStop[] = "*** STR FO(M)+STOP ***\n";
const char SECTION(".rdata") aStrFoLStop[] = "*** STR FO(L)+STOP ***\n";
const char SECTION(".rdata") aStrFoLlStop[] = "*** STR FO(LL)+STOP ***\n";
// EUC_JP: オ－バ－フロ－コプロ予約命令
// Overflow copro reservation command
const int  SECTION(".rdata") dword_80013D10[] = {0x3F3F3F,   0xDDA1AAA5, 0xDDA1D0A5, 0xEDA5D5A5, 0xDDA1,
                                                 0xD7A5B3A5, 0xEDA5,     0xF3CCBDCD, 0xE1CEBFCC, 0,
                                                 0xECA5D6A5, 0xAFA5DDA1, 0xA4A5DDA5, 0xC8A5F3A5, 0};
// EUC_JP: システムコ－ルデ－タバスエラ－
// System call data bus error
const int  SECTION(".rdata") dword_80013D4C[] = {0xB9A5B7A5, 0xE0A5C6A5, 0xDDA1B3A5, 0xEBA5, 0xDDA1C7A5,
                                                 0xD0A5BFA5, 0xA8A5B9A5, 0xDDA1E9A5, 0};
// EUC_JP: 命令バスエラ－ストア時アドレスエラ－ロ－ド時アドレスエラ－TLBS
// Instruction bus error - address error when storing - address error when loading - TLBS
const int  SECTION(".rdata") dword_80013D70[] = {0xE1CEBFCC, 0xB9A5D0A5, 0xE9A5A8A5, 0xDDA1, 0xC8A5B9A5, 0xFEBBA2A5,
                                                 0xC9A5A2A5, 0xB9A5ECA5, 0xE9A5A8A5, 0xDDA1, 0xDDA1EDA5, 0xFEBBC9A5,
                                                 0xC9A5A2A5, 0xB9A5ECA5, 0xE9A5A8A5, 0xDDA1, 0x53424C54, 0};
const char SECTION(".rdata") aTlbl[] = "TLBL";
// EUC_JP: Mod外部割り込み
// Mod external interrupt
const int  SECTION(".rdata") dword_80013DC0[] = {0x646F4D, 0xF4C9B0B3, 0xEAA4E4B3, 0xDFA4FEB9, 0};
