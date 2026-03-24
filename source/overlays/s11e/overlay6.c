#include "common.h"
#include "libgcl/libgcl.h"

/*
const int s11e_dword_800DED00 = 0x800DA0E0;
const int s11e_dword_800DED04 = 0x800DA0F0;
const int s11e_dword_800DED08 = 0x800DA100;
const int s11e_dword_800DED0C = 0x800DA110;
const int s11e_dword_800DED10 = 0x800DA120;
const int s11e_dword_800DED14 = 0x800DA130;
const int s11e_dword_800DED18 = 0x800DA140;
const int s11e_dword_800DED1C = 0x800DA150;
*/
/*
const int s11e_dword_800DED20 = 0x800DA8C4;
const int s11e_dword_800DED24 = 0x800DA930;
const int s11e_dword_800DED28 = 0x800DA958;
const int s11e_dword_800DED2C = 0x800DA980;
const int s11e_dword_800DED30 = 0x800DA9A8;
const int s11e_dword_800DED34 = 0x800DA9D0;
const int s11e_dword_800DED38 = 0x800DA9F8;
const int s11e_dword_800DED3C = 0x800DAA20;
const int s11e_dword_800DED40 = 0x800DAA48;
const int s11e_dword_800DED44 = 0x800DAA70;
const int s11e_dword_800DED48 = 0x800DAA98;
const int s11e_dword_800DED4C = 0x800DAAAC;
const int s11e_dword_800DED50 = 0x800DAAD4;
const int s11e_dword_800DED54 = 0x800DAB04;
const int s11e_dword_800DED58 = 0x800DABC8;
const int s11e_dword_800DED5C = 0x800DAB48;
const int s11e_dword_800DED60 = 0x800DABC8;
*/
const char s11e_aZoned_800DED64[] = "zone=%d ";
const char s11e_aEnemyvoicexx_800DED70[] = "ENEMY VOICE [0x%x]\n";
const char s11e_aZkecomc_800DED84[] = "zk11ecom.c";


SVECTOR SECTION(".bss") ZAKOCOM_PlayerPosition_800DF278;

//zakocommand start
int SECTION(".bss") ZakoCommand_800DF280;
int SECTION(".bss") s11e_dword_800DF284;
int SECTION(".bss") s11e_dword_800DF288;
int SECTION(".bss") s11e_dword_800DF28C;
int SECTION(".bss") s11e_dword_800DF290;
int SECTION(".bss") s11e_dword_800DF294;
int SECTION(".bss") s11e_dword_800DF298;
int SECTION(".bss") s11e_dword_800DF29C;
int SECTION(".bss") s11e_dword_800DF2A0;
int SECTION(".bss") s11e_dword_800DF2A4;
int SECTION(".bss") s11e_dword_800DF2A8;
int SECTION(".bss") s11e_dword_800DF2AC;
int SECTION(".bss") s11e_dword_800DF2B0;
int SECTION(".bss") s11e_dword_800DF2B4;
int SECTION(".bss") s11e_dword_800DF2B8;
int SECTION(".bss") s11e_dword_800DF2BC;
int SECTION(".bss") s11e_dword_800DF2C0;
int SECTION(".bss") s11e_dword_800DF2C4;
int SECTION(".bss") s11e_dword_800DF2C8;
int SECTION(".bss") s11e_dword_800DF2CC;
int SECTION(".bss") s11e_dword_800DF2D0;
int SECTION(".bss") s11e_dword_800DF2D4;
int SECTION(".bss") s11e_dword_800DF2D8;
int SECTION(".bss") s11e_dword_800DF2DC;
int SECTION(".bss") s11e_dword_800DF2E0;
int SECTION(".bss") s11e_dword_800DF2E4;
int SECTION(".bss") s11e_dword_800DF2E8;
int SECTION(".bss") s11e_dword_800DF2EC;
int SECTION(".bss") s11e_dword_800DF2F0;
int SECTION(".bss") s11e_dword_800DF2F4;
int SECTION(".bss") s11e_dword_800DF2F8;
int SECTION(".bss") s11e_dword_800DF2FC;
int SECTION(".bss") s11e_dword_800DF300;
int SECTION(".bss") s11e_dword_800DF304;
int SECTION(".bss") s11e_dword_800DF308;
int SECTION(".bss") s11e_dword_800DF30C;
int SECTION(".bss") s11e_dword_800DF310;
int SECTION(".bss") s11e_dword_800DF314;
int SECTION(".bss") s11e_dword_800DF318;
int SECTION(".bss") s11e_dword_800DF31C;
int SECTION(".bss") s11e_dword_800DF320;
int SECTION(".bss") s11e_dword_800DF324;
int SECTION(".bss") s11e_dword_800DF328;
int SECTION(".bss") s11e_dword_800DF32C;
int SECTION(".bss") s11e_dword_800DF330;
int SECTION(".bss") s11e_dword_800DF334;
int SECTION(".bss") s11e_dword_800DF338;
int SECTION(".bss") s11e_dword_800DF33C;
int SECTION(".bss") s11e_dword_800DF340;
int SECTION(".bss") s11e_dword_800DF344;
int SECTION(".bss") s11e_dword_800DF348;
int SECTION(".bss") s11e_dword_800DF34C;
int SECTION(".bss") s11e_dword_800DF350;
int SECTION(".bss") s11e_dword_800DF354;
int SECTION(".bss") s11e_dword_800DF358;
int SECTION(".bss") s11e_dword_800DF35C;
int SECTION(".bss") s11e_dword_800DF360;
int SECTION(".bss") s11e_dword_800DF364;
int SECTION(".bss") s11e_dword_800DF368;
int SECTION(".bss") s11e_dword_800DF36C;
int SECTION(".bss") s11e_dword_800DF370;
int SECTION(".bss") s11e_dword_800DF374;
int SECTION(".bss") s11e_dword_800DF378;
int SECTION(".bss") s11e_dword_800DF37C;
int SECTION(".bss") s11e_dword_800DF380;
int SECTION(".bss") s11e_dword_800DF384;
int SECTION(".bss") s11e_dword_800DF388;
int SECTION(".bss") s11e_dword_800DF38C;
int SECTION(".bss") s11e_dword_800DF390;
int SECTION(".bss") s11e_dword_800DF394;
int SECTION(".bss") s11e_dword_800DF398;
int SECTION(".bss") s11e_dword_800DF39C;
int SECTION(".bss") s11e_dword_800DF3A0;
//zakocommand end
int SECTION(".bss") s11e_dword_800DF3A4;

int SECTION(".bss") TOPCOMMAND_800DF3A8;
int SECTION(".bss") s11e_dword_800DF3AC;

int SECTION(".bss") s11e_dword_800DF3B0;
int SECTION(".bss") s11e_dword_800DF3B4;
int SECTION(".bss") ZAKOCOM_PlayerAddress_800DF3B8;
int SECTION(".bss") ZAKOCOM_PlayerMap_800DF3BC;
