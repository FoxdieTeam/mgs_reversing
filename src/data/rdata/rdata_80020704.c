#include "linker.h"

const char SECTION(".rdata") aGclWrongCodeX[] = "GCL:WRONG CODE %x\n\x0\x0"; // TODO: Alignment ??

const unsigned int SECTION(".rdata") jpt_80020704[] =
{
	0x8002070C, 0x80020714, 0x80020788, 0x80020788, 0x80020788,
	0x8002083C, 0x8002076C, 0x80020798, 0x8002076C, 0x80020738,
	0x80020738, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x800207AC, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x800207F0, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x800207C8,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C, 0x8002083C,
	0x8002080C
};

const char SECTION(".rdata") aSaveDataVersio[] = "SAVE DATA VERSION ERROR!!\n";

const char SECTION(".rdata") aCrcError[] = "CRC ERROR !!\n\x0\x0\x0"; // TODO: Alignment ??

const unsigned int SECTION(".rdata") jpt_800216BC[] =
{
	0x800216C4,
	0x800216E8,
	0x800216E8,
	0x800216F4,
	0x80021714,
	0x800216C4,
	0x80021714,
	0x800216C4
};


const unsigned int SECTION(".rdata") jpt_800217A0[] =  
{
	0x800217A8,
	0x800217B0,
	0x800217B0,
	0x800217B8,
	0x800217E8,
	0x800217A8,
	0x800217E8,
	0x800217A8
};

const unsigned int SECTION(".rdata") jpt_80021894[] =
{
	0x8002189C,
	0x800218A8,
	0x800218A8,
	0x800218B4,
	0x800218EC,
	0x8002189C,
	0x800218EC,
	0x8002189C
};

const char SECTION(".rdata") aWarningOldVers[] = "Warning:old version hzm\n";

const char SECTION(".rdata") aBrfDat[] = "BRF.DAT";
const char SECTION(".rdata") aDemoDat[] = "DEMO.DAT";
const char SECTION(".rdata") aVoxDat[] ="VOX.DAT";
const char SECTION(".rdata") aZmovieStr[] = "ZMOVIE.STR";
const char SECTION(".rdata") aFaceDat[] = "FACE.DAT";
const char SECTION(".rdata") aRadioDat[] = "RADIO.DAT";
const char SECTION(".rdata") aStageDir[] = "STAGE.DIR";

const char SECTION(".rdata") aPositionEnd[] = "Position end\n";
const char SECTION(".rdata") aDiskD[] = "DISK %d\n";
const char SECTION(".rdata") aIllegalDisk[] = "illegal DISK\n";

const char SECTION(".rdata") aCdfsSkipErrorD[] = "CDFS: skip error %d %d %d\n";

const char SECTION(".rdata") asc_800105B4[] = "[T]";
const char SECTION(".rdata") asc_800105B8[] = ".";
const char SECTION(".rdata") aD[] ="[%d]";
const char SECTION(".rdata") aFileSTopDSizeD[] = "FILE %s : top %d size %d set %d\n";
const char SECTION(".rdata") aPlaystation[] = "PLAYSTATION";
const char SECTION(".rdata") aMgs[] = "MGS";
const char SECTION(".rdata") aMgsReadSectorD[] = "MGS read_sector %d\n";
const char SECTION(".rdata") aXXD[] = "%X %X %d\n";
const char SECTION(".rdata") aDCCD[] = "%d %c %c %d\n";
const char SECTION(".rdata") aHere[] = "HERE !!\n";
const char SECTION(".rdata") aWrongMode02xC[] = "WRONG mode %02X (%c)\n";
const char SECTION(".rdata") aWrongD[] = "!!! WRONG %d !!!\n";
const char SECTION(".rdata") aNtagXSizeD[] = "ntag %X size %d\n";
const char SECTION(".rdata") aLimitX[] = "limit = %X\n";
const char SECTION(".rdata") aDataXCNowX[] = "data %X %c, now %X\n";
const char SECTION(".rdata") aInitXCNowX[] = "init %X %c, now %X\n";
const char SECTION(".rdata") aLoadS[] = "load %s\n";
const char SECTION(".rdata") aNotFoundS[] = "NOT FOUND %s\n";
const char SECTION(".rdata") aNo2[] = "no_mem\n";
const char SECTION(".rdata") aLoadCompleteTi[] = "load complete time %d\n";
const char SECTION(".rdata") aMovieFileIsWro[] = "movie file is wrong\n";
const char SECTION(".rdata") aMovieNumD[] = "MOVIE NUM %d\n";
const char SECTION(".rdata") aTablenumDSizeD[] = "tablenum %d size %d\n";
const char SECTION(".rdata") aIdDFrameDPosD[] = "id %d frame %d pos %d\n";
const char SECTION(".rdata") aStreamInitXX[] = "stream init %X %X\n";
const char SECTION(".rdata") aClearX[] = "clear %X\n";
const char SECTION(".rdata") aNowDataTopXLoa[] = "now_data_top %X loaded_header %X\n";
const char SECTION(".rdata") aTickD[] = "Tick %d\n";
const char SECTION(".rdata") a08xTypeXSizeDT[] = "%08X TYPE %X size %d time %d\n";
const char SECTION(".rdata") a08xTypeXSizeD[] = "%08X TYPE %X size %d\n";
int SECTION(".rdata") dword_800107C4 = 0x5D525B;
const char SECTION(".rdata") aAccessWait[] = "ACCESS WAIT..\n";
const char SECTION(".rdata") aHwCardError[] = "*** hw card error\n";
const char SECTION(".rdata") aCHTO[] = "[C.H.T.O]";
const char SECTION(".rdata") aHwCardNew[] = "*** hw card new\n";
const char SECTION(".rdata") aSwCardError[] = "*** sw card error\n";
const char SECTION(".rdata") aCSTO[] = "[C.S.T.O]";
const char SECTION(".rdata") aSwCardNew[] = "*** sw card new\n";
const char SECTION(".rdata") aEasyFormatTest[] = "easy_format_test\n";
const char SECTION(".rdata") aCardError[] = "card_error\n";
const char SECTION(".rdata") aCardNormal[] = "card_normal\n";
const char SECTION(".rdata") aCardUnformat[] = "card_unformat\n";
const char SECTION(".rdata") aBu02x[] = "bu%02X:*";
const char SECTION(".rdata") aLoadDirSStart[] = "load_dir %s start\n";
const char SECTION(".rdata") aTotalDFilesUse[] = "TOTAL %d FILES used %d block\n";
const char SECTION(".rdata") aNoFile[] = "NO FILE\n";
const char SECTION(".rdata") aMemcardRetryOv[] = "MEMCARD:RETRY OVER!!\n";
const char SECTION(".rdata") aRetryNew[] = "RETRY(new)\n";
const char SECTION(".rdata") aRetry[] = "RETRY\n";
const char SECTION(".rdata") aBu02xS[] = "bu%02X:%s";
const char SECTION(".rdata") aDeletedFileS[] = "Deleted File %s";
const char SECTION(".rdata") aErrorCanTDelet[] = "ERROR : can't delete %s\n";
const char SECTION(".rdata") aMemcardReadWri[] = "MEMCARD READ/WRITE end\n";
const char SECTION(".rdata") aErrorMemcardRe[] = "ERROR : MEMCARD READ/WRITE\n";
const char SECTION(".rdata") aWarningMemcard[] = "Warning : MEMCARD create error ... overwrite\n";
const char SECTION(".rdata") aMemcardWriteEr[] = "MEMCARD WRITE ERROR FD %d\n";
const char SECTION(".rdata") aMemcardWriteSF[] = "MEMCARD WRITE %s FD %d SIZE %d\n";
const char SECTION(".rdata") aWritingFileS[] = "WRITING FILE %s...\n";
const char SECTION(".rdata") aBu02xS_0[] = "bu%02x:%s";
const char SECTION(".rdata") aMemcardReadErr[] = "MEMCARD READ ERROR FD %d\n";
const char SECTION(".rdata") aMemcardReadSFd[] = "MEMCARD READ %s FD %d SIZE %d\n";
const char SECTION(".rdata") aReadingFileS[] = "READING FILE %s...\n";
const char SECTION(".rdata") aBu02x_0[] = "bu%02x:";
const char SECTION(".rdata") aFormatedD[] = "FORMATED %d\n";
const char SECTION(".rdata") aErrorMemcardFo[] = "ERROR : MEMCARD FORMAT\n";
const char SECTION(".rdata") aErrorMemcardFo_0[] = "ERROR : MEMCARD FORMATED CARD\n";
const char SECTION(".rdata") aInitcontrolNoM[] = "InitControl : no map %X\n";
const char SECTION(".rdata") aExecScenario[] = "exec scenario\n";
const char SECTION(".rdata") aEndScenario[] = "end scenario\n";
const char SECTION(".rdata") aCdromMgsS1[] = "cdrom:\\MGS\\%s;1";
const char SECTION(".rdata") aLoadS_0[] = "load %s\n";
const char SECTION(".rdata") aStrStatusDIrqX[] = "str_status %d irq %x %X %X\n";
const char SECTION(".rdata") aKey08x[] = "key %08X\n";
const char SECTION(".rdata") aTooLargeStageB[] = "TOO LARGE STAGE BINARY!!\n";
const char SECTION(".rdata") aSetCameraD[] = "set camera %d\n";
const char SECTION(".rdata") aBindsOver[] = "binds over\n";
const char SECTION(".rdata") aNtrapCanTSetEv[] = "ntrap:can't set every\n";
const char SECTION(".rdata") aNtrapCanTSetPr[] = "ntrap:can't set proc and block\n";
const char SECTION(".rdata") aBind08x[] = "BIND %08X\n";
const char SECTION(".rdata") aMenuInitEnd[] = "MENU INIT END\n";
const char SECTION(".rdata") aWrongCodeForRa[] = "Wrong Code for radio over\n";
const char SECTION(".rdata") aVarsaveNotVar[] = "VARSAVE: NOT VAR !!\n";
const char SECTION(".rdata") aSystemCChangeP[] = "SYSTEM:%c:change proc name\n";
const char SECTION(".rdata") aDemoNoCode[] = "DEMO:NO CODE\n";
const char SECTION(".rdata") aDemoNoDataOnCd[] = "DEMO ( no data on CD )";
const char SECTION(".rdata") aErrorDemoThrea[] = "Error demo thread\n";
const char SECTION(".rdata") aLoadend[] = "LoadEnd\n";
const char SECTION(".rdata") aLoadreq[] = "LoadReq\n";
const char SECTION(".rdata") aNotFoundStageS[] = "NOT FOUND STAGE %s\n";
const char SECTION(".rdata") aLoaderC[] = "loader.c";
int SECTION(".rdata") dword_80010C60[] = {0, 0x1E0001, 0x1E0002, 0x1E0003, 0x140003, 0xA0003, 0x50003, 0x30003, 0x5D64255B, 0x206D6163, 0x2074756F, 0xA6425, 0x5D64255B, 0x206D6163, 0x25206E69, 0xA64};
const char SECTION(".rdata") aDChangeCameraD[] = "[%d]change camera %d\n";
const char SECTION(".rdata") aCameraC[] = "camera.c";
const char SECTION(".rdata") aSetMapD[] = "set map %d\n";
const char SECTION(".rdata") aAddMapD[] = "add map %d\n";
const char SECTION(".rdata") aAddmapNotFound[] = "addmap : not found map %d\n";
const char SECTION(".rdata") aDelMapD[] = "del map %d\n";
const char SECTION(".rdata") aDelmapNotFound[] = "delmap: not found map %d\n";
const char SECTION(".rdata") aReshadeNullMap[] = "Reshade NULL map\n";
const char SECTION(".rdata") aHomingTargetOv[] = "Homing target over !!!\n";
const char SECTION(".rdata") aFull[] = "FULL";
const char SECTION(".rdata") aGetWeaponFirst[] = "GET WEAPON FIRST";
int SECTION(".rdata") dword_80010D68 = 0x7325;
int SECTION(".rdata") dword_80010D6C[] = {0x80034090, 0x800340B8, 0x80034060, 0x80034060, 0x800340A4, 0x800340B8};
const char SECTION(".rdata") aNoIdItem[] = "NO ID ITEM\n";
const char SECTION(".rdata") aShadow[] = "shadow";
const char SECTION(".rdata") aItemC[] = "item.c";
const char SECTION(".rdata") aItemMapD[] = "Item map = %d\n";
const char SECTION(".rdata") aDoublePcm[] = "Double Pcm !!\n";
const char SECTION(".rdata") aWrongTypeHeade[] = "??? WRONG TYPE HEADER!!\n";
const char SECTION(".rdata") aStreamplayEnd[] = "StreamPlay end\n";
const char SECTION(".rdata") aNewstreamD[] = "NewStream %d\n";
const char SECTION(".rdata") aPend[] = "pend!!\n";
const char SECTION(".rdata") aStrctrlC[] = "strctrl.c";
const char SECTION(".rdata") aStreamIsNotRea[] = "stream is not ready\n";
const char SECTION(".rdata") aGmStreamplayst[] = "GM_StreamPlayStop\n";
const char SECTION(".rdata") aVoxstreamD[] = "VoxStream %d\n";
const char SECTION(".rdata") aKutipakuEnd[] = "KUTIPAKU END\n";
int SECTION(".rdata") jpt_800383D8[] = {0x800383E0, 0x80038400, 0x80038428, 0x800384D8, 0x80038458, 0x80038464, 0x8003849C};
const char SECTION(".rdata") aJimctrlC[] = "jimctrl.c";
const char SECTION(".rdata") aMenumanC[] = "menuman.c";
const char SECTION(".rdata") aMenuPrimOver[] = "!!!! MENU PRIM OVER !!!!\n";
int SECTION(".rdata") dword_crap4[] = {0x158214B0, 0x4C823782, 0x158223C2, 0x15D006D0, 0x1D827C80, 0x138206D0, 0x34824082, 0x28821982, 0xF2904B82, 0x2E814990, 0x37821582, 0x23C24C82, 0x6D01582, 0x1D8203D0, 0x138206D0, 0x34824082, 0x28821982, 0x2E814B82, 0x8C907E90, 0x5281F390, 0x881F490, 0x3D04B81, 0, 0x2F8214B0, 0xB825382, 0x15D02182, 0x19827C80, 0x4822A82, 0x6D03182, 0x6827FC0, 0x35824B82, 0x2F822E81, 0xB825382, 0x3D02182, 0x19810B81, 0x2B810B81, 0xF190F090, 0x78902E81, 0xC810481, 0x4B811981, 0x3D0, 0x4D8214B0, 0x378206D0, 0x7C8015D0, 0xF817390, 0x74902681, 0x2A817590, 0x6D04D82, 0x3D03782, 0x4822A82, 0x53824D82, 0xD190D090, 0x3D0EF90, 0, 0x4A9014B0, 0x3C22782, 0xF821982, 0x7C8015D0, 0x1F824182, 0xE824B82, 0x2E810282, 0x71907090, 0x6D02782, 0xC811F82, 0x41817290, 0x4C814981, 0x4812681, 0x28814B81, 0x6810481, 0x27824A90, 0x198203C2, 0x3D00F82, 0, 0x6A9014B0, 0x6C906B90, 0x6E906D90, 0x7C8015D0, 0x94909390, 0x4B811981, 0x2D02881, 0x9D90EB90, 0x4C811581, 0x6A901F81, 0x2E816B90, 0x9E90EC90, 0x4C820C81, 0x208206D0, 0x2B8106D0, 0xEE90ED90, 0x4C811581, 0x3D04B81, 0, 0x3FC014B0, 0x7C8015D0, 0x67900190, 0x3D06890, 0x2B824182, 0x6D045C2, 0x54905281, 0x26810481, 0x4B810481, 0xD812881, 0x24902B81, 0x69902781, 0x4B812681, 0x28811381, 0x27810C81, 0x4B810D81, 0x3D0, 0x444914B0, 0x6D00B82, 0x15D02982, 0x93907C80, 0x19819490, 0x28814B81, 0xD821B82, 0x4A8245C2, 0x3C22682, 0x4C827FC0, 0x4B823982, 0x81310C81, 0x8127813E, 0x81EA902E, 0x81549052, 0x904B8111, 0x810C81C6, 0x810D8127, 0x3D04B, 0x415014B0, 0xD00B824C, 0xD0298206, 0x907C8015, 0x82A290E5, 0x8206D013, 0x90E69029, 0x90AC90E7, 0x90169051, 0x90E990E8, 0x822E8149, 0x8206D00B, 0x827FC029, 0xD006D00D, 3, 0x188214B0, 0x1C820282, 0x40823182, 0x7C8015D0, 0x5A905990, 0x5C905B90, 0x3D05D90, 0x2E815E90, 0x4B813581, 0x52810881, 0x5C90E390, 0xE490DC90, 0x41815890, 0x3D04B81, 0x2B824182, 0x6D045C2, 0x54905281, 0x26810481, 0x4B810481, 0x2B81DC90, 0x3C821B90, 0x53821F82, 0x7B905281, 0x26811781, 0x4990E290, 0x3D0, 0x559014B0, 0x57905690, 0x7C8015D0, 0xDE90DD90, 0xE090DF90, 0x3D05790, 0x56905590, 0xE1905281, 0xC6901981, 0x27810C81, 0x4B810D81, 0x418203D0, 0x45C22B82, 0x528106D0, 0x4815490, 0x4812681, 0xDC904B81, 0x1B902B81, 0x1F823C82, 0x52815382, 0x17817B90, 0xE2902681, 0x3D04990, 0, 0x4C8214B0, 0x178206D0, 0x538247C2, 0x7C8015D0, 0x4990D790, 0xD990D890, 0xDB90DA90, 0x4C8003D0, 0x46804980, 0x52814580, 0x53905290, 0x4B811981, 0x418203D0, 0x45C22B82, 0x528106D0, 0x4815490, 0x4812681, 0xDC904B81, 0x1B902B81, 0x1F823C82, 0x52815382, 0x17817B90, 0x48902681, 0x3D04990, 0x94909390, 0xC912781, 0x48909890, 0x3D04990, 0, 0xB8214B0, 0x49824182, 0x7C8015D0, 0x4D810481, 0x4D810481, 0x28812A81, 0x4D811381, 0x4F905281, 0x27815090, 0x4B810D81, 0x249003D0, 0x1A822781, 0x408206D0, 0x53820482, 0x189002D0, 0x1A822781, 0x408206D0, 0x6820282, 0x3D02882, 0x27811D90, 0x50904F90, 0x3D0, 0x408214B0, 0x53821282, 0x53823082, 0x2A822082, 0x7C8015D0, 0x4A824182, 0xC814B82, 0x24813490, 0x1F811181, 0x53823082, 0x2A822082, 0x7C8003D0, 0x40820BB0, 0x53821282, 0x28810CD0, 0x6810481, 0xC818E90, 0x4812C81, 0x3E811381, 0x26814C81, 0x4B810481, 0x3D0, 0x198214B0, 0x4B822682, 0x4C901982, 0x15D04D90, 0xA827C80, 0x13821F82, 0xC815382, 0x7E905490, 0x1F811781, 0x4A9002D0, 0xD3905281, 0x1581D490, 0x26811B81, 0x94909390, 0x1F811781, 0x5281D590, 0x6890D690, 0x19816490, 0x4C904B81, 0x17824D90, 0x26821982, 0x3D04082, 0, 0x118214B0, 0x43C22182, 0x378223C2, 0x7C8015D0, 0x45904490, 0x3D04690, 0x1F820482, 0x2824A82, 0x28824790, 0x28823E82, 0x49904890, 0x238003D0, 0x3C822490, 0x53821F82, 0x48902781, 0xB6904990, 0x3D00F91, 0, 0x3C8214B0, 0x3C22782, 0x28206D0, 0x3E8206D0, 0x15D006D0, 0xFE907C80, 0xD090FF90, 0x5281D190, 0x49904890, 0x1F811781, 0x8590D290, 0x19823982, 0x3D02882, 0x41822082, 0x188206D0, 0x42905281, 0x15814390, 0x4B811B81, 0xC81C690, 0xD812781, 0x3D04B81, 0, 0xC8214B0, 0x3E821982, 0xF821982, 0x7C8015D0, 0xCA909190, 0x64903A90, 0xCB904B90, 0xCC90C190, 0xC824990, 0x3E821982, 0xF821982, 0x3F9003D0, 0x19820C82, 0xCD902E81, 0x4F802781, 0x12823280, 0x188206D0, 0x43900C81, 0x1981CE90, 0x19824B81, 0x6D03482, 0xC812982, 0xF81CF90, 0x4B812A81, 0x3D0, 0x158214B0, 0x3E8206D0, 0x7FC04B82, 0x6D01482, 0x4B821082, 0x7C8015D0, 0xC890C790, 0x38902E81, 0x5281C990, 0xC090BF90, 0x19816490, 0x31904B81, 0xC1903290, 0x3D0C290, 0x4813190, 0xC490C390, 0x42812781, 0xA4903290, 0xC5905281, 0x19812B90, 0xC6904B81, 0x27810C81, 0x4B810D81, 0x3D0, 0x319014B0, 0x14823290, 0x108206D0, 0x15D04B82, 0x4A907C80, 0xA6905281, 0xBC90A790, 0xBD902B81, 0x1781BE90, 0xBF902681, 0x6490C090, 0x4B811981, 0x32903190, 0xC290C190, 0x319003D0, 0xC3900481, 0x2781C490, 0x32904281, 0x5281A490, 0x2B90C590, 0x4B811981, 0xC81C690, 0xD812781, 0x3D04B81, 0, 0x208214B0, 0x3C825382, 0x4B8206D0, 0xD043B990, 0xB07C8015, 0x902F900B, 0xD0269030, 0x9028810C, 0x81048127, 0x81028126, 0x3D04B, 0x208214B0, 0x3C825382, 0x4B8206D0, 0xD042B990, 0xB07C8015, 0x902A900B, 0x90BA9085, 0x902C902B, 0xD02690BB, 0x9028810C, 0x81048127, 0x81028126, 0x3D04B, 0x208214B0, 0x3C825382, 0x4B8206D0, 0xD041B990, 0xB07C8015, 0x8238820B, 0xD03D824A, 0x90288206, 0x810CD026, 0x81279028, 0x814C810B, 0x81048126, 0x3D04B, 0x219014B0, 0x23902290, 0x7C8015D0, 0x6390B690, 0xB890B790, 0x22902190, 0x3D02390, 0x27812490, 0x6D01A82, 0x4824082, 0x2D05382, 0x27811890, 0x6D01A82, 0x2824082, 0x28820682, 0x3D0, 0xB09014B0, 0x15D0B190, 0x1D827C80, 0x23C24A82, 0x7FC02982, 0x2D821982, 0xF8206D0, 0x49901F90, 0xB0902E81, 0x3D0B190, 0x481B290, 0xE81B390, 0x2F812B81, 0xB590B490, 0x3E811781, 0x47C11781, 0x3D00681, 0, 0x118214B0, 0x43C22182, 0x378223C2, 0x7C8015D0, 0x4A817990, 0x4812481, 0x4812681, 0x2D02681, 0x49904890, 0xD812781, 0x4812A81, 0x3D0, 0x4C8214B0, 0x178206D0, 0x538247C2, 0x7C8015D0, 0x4A817990, 0x4812481, 0x4812681, 0x2D02681, 0x49904890, 0xD812781, 0x4812A81, 0x3D0};
const char SECTION(".rdata") aDiazepam[] = "DIAZEPAM";
const char SECTION(".rdata") aMedicine[] = "MEDICINE";
int SECTION(".rdata") jpt_8003C2B8[] = {0x8003C2C0, 0x8003C4DC, 0x8003C4DC, 0x8003C4DC, 0x8003C2C0, 0x8003C390, 0x8003C3D0, 0x8003C4DC, 0x8003C4DC, 0x8003C414};
int SECTION(".rdata") jpt_8003C55C[] = {0x8003C564, 0x8003C660, 0x8003C760, 0x8003C8D8, 0x8003C934};
const char SECTION(".rdata") aPanelMakeError[] = "PANEL MAKE Error\n";
const char SECTION(".rdata") aClaymore[] = "CLAYMORE";
int SECTION(".rdata") dword_crap5[] = {0x508014B0, 0x47805380, 0x15D03180, 0xAA907C80, 0x4990AB90, 0x4824982, 0x4B823582, 0x939003D0, 0x19819490, 0x28814B81, 0x96909590, 0x6D04282, 0x2B812982, 0x4B81AC90, 0x879003D0, 0xD829B90, 0x278106D0, 0x96909590, 0x98909790, 0x238002D0, 0x3C821D90, 0x53821F82, 0x7B905281, 0x28811981, 0x7F907E90, 0x3D0, 0x218214B0, 0x358243C2, 0x10827FC0, 0x2D824C82, 0x298206D0, 0x7C8015D0, 0xA790A690, 0xA990A890, 0x84905E90, 0x3D08590, 0x1D902380, 0x1F823C82, 0x52815382, 0x19817B90, 0x7C902881, 0x2D00881, 0x19817D90, 0x88902881, 0x4B811281, 0x39103D0, 0x83900491, 0x5915281, 0x17810691, 0xA69002D0, 0x9390A790, 0x52819E90, 0xA990A890, 0x4B811981, 0x3D0, 0x198214B0, 0x53821F82, 0x10827FC0, 0x2D824C82, 0x298206D0, 0x7C8015D0, 0xFF90FE90, 0x4A90A390, 0x84905E90, 0x3D08590, 0x1D902380, 0x1F823C82, 0x52815382, 0x19817B90, 0x7C902881, 0x2D00881, 0x19817D90, 0x88902881, 0x4B811281, 0xA29003D0, 0x19817E90, 0x28814B81, 0xE39002D0, 0xDC905C90, 0x9F90E490, 0x1915281, 0x15810291, 0x4B811B81, 0x3D0, 0x804314B0, 0x90A29034, 0x8015D085, 0x8237827C, 0x82198249, 0x8223C221, 0x90A2900F, 0x8003D085, 0x821D9023, 0x821F823C, 0x90278153, 0xD09E909D, 0x90238002, 0x823C8224, 0x8153821F, 0x90A29027, 0x3D082, 0xF8214B0, 0x4824C82, 0x2824282, 0x7C8015D0, 0x99909190, 0x9B909A90, 0x6A909C90, 0x3D06B90, 0x1D902380, 0x1F823C82, 0x27815382, 0x9E909D90, 0x9D9003D0, 0xDC909E90, 0xED902B81, 0x1581EE90, 0x4B814C81, 0x7E90A290, 0xC890FD90, 0xAC902B81, 0x28814B81, 0x7E90A290, 0x4B811981, 0x3D0, 0x198214B0, 0x3C22682, 0xC825382, 0x7FC006D0, 0x15823F82, 0x4B820482, 0x7C8015D0, 0x91906A90, 0x3F829290, 0x4821582, 0x3D04B82, 0x94909390, 0x4B811981, 0x95902881, 0x42829690, 0x298206D0, 0xAC902B81, 0x3D04B81, 0x9B908790, 0x6D00D82, 0x95902781, 0x97909690, 0x2D09890, 0x1D902380, 0x1F823C82, 0x52815382, 0x19817B90, 0x7E902881, 0x3D08C90, 0, 0x4A8214B0, 0x13824282, 0x3F825382, 0x4821582, 0x15D04B82, 0x89907C80, 0x8A903790, 0x3F828B90, 0x4821582, 0x3D04B82, 0x1D902380, 0x1F823C82, 0x52815382, 0x19817B90, 0x7E902881, 0x3D08C90, 0x8C907E90, 0x2D0FC90, 0x9B908790, 0x6D00D82, 0x3F822781, 0x4821582, 0x52814B82, 0x90908F90, 0xD812781, 0x3D04B81, 0, 0x108214B0, 0x2D824C82, 0x298206D0, 0x7C8015D0, 0x83908290, 0x84905E90, 0x3D08590, 0x1D902380, 0x1F823C82, 0x52815382, 0x19817B90, 0x5B902881, 0x3482F890, 0x52815382, 0xD81F990, 0x7D9002D0, 0x28811981, 0x12818890, 0x3D04B81, 0x53823482, 0xF9905281, 0x26810481, 0x49810B81, 0x3580FA90, 0xFC90FB90, 0xA2902B81, 0x3D07E90, 0, 0x358214B0, 0x3E8201C2, 0x15D01982, 0x2827C80, 0x4B821582, 0x49822882, 0x35820482, 0x3D04B82, 0x1D902380, 0x1F823C82, 0x52815382, 0x19817B90, 0x7E902881, 0x3D07F90, 0x17817B90, 0x25812481, 0x4B811181, 0x2D02881, 0x4B823582, 0x6D00A82, 0x80902882, 0x3D08C90, 0};
int SECTION(".rdata") dword_80011A8C[] = {0x1D8214B0, 0x138206D0, 0x34824082, 0x28821982, 0x15D04B82, 0x42907C80, 0x98900C91, 0xE910D91, 0x4C8203D0, 0x168206D0, 0x959006D0, 0xC1909690, 0x94909390, 0x238003D0, 0x3C821D90, 0x53821F82, 0x7B905281, 0x28811981, 0x23C24D82, 0xA820F82, 0x2D05382, 0x19817D90, 0x7E902881, 0x3D07F90, 0x37821582, 0x23C24C82, 0x6D01582, 0x94909390, 0xF91B690, 0x3D0, 0x504D14B0, 0x53203520, 0x8015D044, 0x8215827C, 0x823E8236, 0x82538217, 0xD053820C, 0x90238003, 0x823C821D, 0x8153821F, 0x817B9052, 0x90288119, 0xD07F907E, 0x817B9003, 0x81248117, 0x81118125, 0xD028814B, 0x82358202, 0xD00A824B, 0x90288206, 0xD08C9080, 0x82158203, 0xC24C8237, 0xD0158223, 0x90939006, 0x3D094, 0x45524548, 0xA642520, 0};
const char SECTION(".rdata") aPressSelectToE[] = "PRESS SELECT TO EXIT";
const char SECTION(".rdata") aSetCallFreqD[] = "set call freq %d\n";
const char SECTION(".rdata") aNoResponse[] = "NO RESPONSE";
int SECTION(".rdata") dword_80011BB0[] = {0xAE90AD90, 0x4A810281, 0x1B813E81, 0x3D05381, 0};
const char SECTION(".rdata") aGetpotionD[] = "GetPotion %d\n";
const char SECTION(".rdata") aPushSelect[] = "PUSH SELECT";
const char SECTION(".rdata") aCallbackTypeDP[] = "callback type %d proc %X\n";
const char SECTION(".rdata") aExecproc[] = "ExecProc\n";
const char SECTION(".rdata") aExitMusenki[] = "EXIT MUSENKI\n";
int SECTION(".rdata") jpt_80041650[] = {0x80041658, 0x80041670, 0x80041948, 0x800419C4, 0x80041B28, 0x80041B98, 0x80041DE0, 0x80041E08, 0x80042064, 0x80041D5C, 0x800418C4, 0x80041F4C, 0x80041F70, 0x80041FA0, 0x80041FC8, 0x80042038, 0x80042044, 0x80042064, 0x80041E94, 0x80041EE4};
int SECTION(".rdata") jpt_80041A84[] = {0x80042064, 0x80041A8C, 0x80041ACC, 0x80041AF4, 0x80041B1C};
const char SECTION(".rdata") aTotalD[] = "TOTAL %d\n";
const char SECTION(".rdata") aClipD[] = "CLIP %d\n";
const char SECTION(".rdata") aXDYD[] = "x %d y %d\n";
const char SECTION(".rdata") aWDHD[] = "w %d h %d\n";
const char SECTION(".rdata") aWrongRubiCodeX[] = "Wrong rubi code %x\n";
const char SECTION(".rdata") aNoMemoryForSav[] = "NO MEMORY FOR SAVE TEX\n";
const char SECTION(".rdata") aNoFaceData[] = "NO_FACE_DATA\n";
const char SECTION(".rdata") aFrameNumD[] = "frame num %d\n";
const char SECTION(".rdata") aSetCharaCodeD[] = "set chara code %d\n";
const char SECTION(".rdata") aAnimeCharaDCod[] = "ANIME CHARA %d CODE %d\n";
const char SECTION(".rdata") aVoxcodeX[] = "voxcode %X\n";
const char SECTION(".rdata") aIllegalCodeX[] = "illegal code %x\n";
const char SECTION(".rdata") aSetDS[] = "set %d %s\n";
const char SECTION(".rdata") aBlockExecError[] = "block exec error\n";
const char SECTION(".rdata") aNoMemoryForFac[] = "NO MEMORY FOR FACE %d\n";
const char SECTION(".rdata") aFaceDataNumD[] = "face data num %d\n";
const char SECTION(".rdata") aNoMemoryForSta[] = "NO MEMORY FOR STACK\n";
const char SECTION(".rdata") aNoMemory[] = "no memory\n";
int SECTION(".rdata") dword_crap6 = 0;
