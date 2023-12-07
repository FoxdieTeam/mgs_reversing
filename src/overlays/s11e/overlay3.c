#include "linker.h"

/*
const int s11e_dword_800DEB74 = 0x800D4524;
const int s11e_dword_800DEB78 = 0x800D459C;
const int s11e_dword_800DEB7C = 0x800D44AC;
const int s11e_dword_800DEB80 = 0x800D450C;
const int s11e_dword_800DEB84 = 0x800D45D4;
const int s11e_dword_800DEB88 = 0x800D4628;
const int s11e_dword_800DEB8C = 0x800D4628;
const int s11e_dword_800DEB90 = 0x800D45F0;
const int s11e_dword_800DEB94 = 0x800D4604;
*/

const char rp_shift_800DEB98[] = {'8', 0xff, 0xe8, 0x3};
const char s11e_dword_800DEB9C[] = {'X', 0x2, 0x0, 0x0};

const char force_800DEBA0[] = {0x5, 0x0, 0x0, 0x0};
const char s11e_aD_800DEBA4[] = "d";

const char size_800DEBA8[] = {0x90, 0x1, 0xe8, 0x3};
const char s11e_dword_800DEBAC[] = {0x90, 0x1, 0x0, 0x0};

const char s11e_dword_800DEBB0[] = {0x0, 0x0, 0x0, 0x0};




const int s11e_dword_800DEBB4 = 0x800D652C;
const int s11e_dword_800DEBB8 = 0x800D657C;
const int s11e_dword_800DEBBC = 0x800D6644;
const int s11e_dword_800DEBC0 = 0x800D6600;
const int s11e_dword_800DEBC4 = 0x800D6688;
const int s11e_dword_800DEBC8 = 0x800D66BC;
const int s11e_dword_800DEBCC = 0x800D6778;
const int s11e_dword_800DEBD0 = 0x800D67C0;
const int s11e_dword_800DEBD4 = 0x800D6800;
const int s11e_dword_800DEBD8 = 0x800D67E0;
const int s11e_dword_800DEBDC = 0x800D682C;
const int s11e_dword_800DEBE0 = 0x800D682C;
const char s11e_aFamasbullet_800DEBE4[] = "FA-MAS/BULLET * 25";
const char s11e_aSocombullet_800DEBF8[] = "SOCOM/BULLET * 12";
const char s11e_dword_800DEC0C[] = {'R', 'A', 'T', 'I'};
const char s11e_dword_800DEC10[] = {'O', 'N', 0x0, 0x8e};
const char s11e_aKirari_800DEC14[] = "kirari01";
const char s11e_dword_800DEC20[] = {0x0, 0x0, 0x0, 0x0};
const int s11e_dword_800DEC24 = 0x800D942C;
const int s11e_dword_800DEC28 = 0x800D9474;
const int s11e_dword_800DEC2C = 0x800D945C;
const int s11e_dword_800DEC30 = 0x800D9464;
const int s11e_dword_800DEC34 = 0x800D946C;
const char s11e_dword_800DEC38[] = {0x0, 0x0, 0x0, 0x0};
const int s11e_dword_800DEC3C = 0x800D96A0;
const int s11e_dword_800DEC40 = 0x800D96B8;
const int s11e_dword_800DEC44 = 0x800D97A8;
const int s11e_dword_800DEC48 = 0x800D96D0;
const int s11e_dword_800DEC4C = 0x800D96F0;
const int s11e_dword_800DEC50 = 0x800D9708;
const int s11e_dword_800DEC54 = 0x800D9720;
const int s11e_dword_800DEC58 = 0x800D9738;
const int s11e_dword_800DEC5C = 0x800D976C;
const int s11e_dword_800DEC60 = 0x800D9750;
const int s11e_dword_800DEC64 = 0x800D9960;
const int s11e_dword_800DEC68 = 0x800D9970;
const int s11e_dword_800DEC6C = 0x800D9980;
const int s11e_dword_800DEC70 = 0x800D9990;
const int s11e_dword_800DEC74 = 0x800D99A0;
const char s11e_aDareda_800DEC78[] = "dareda!!\n";
const char s11e_aNannootoda_800DEC84[] = "nanno otoda!!\n";
const char s11e_aTadanohakoka_800DEC94[] = "tadano hakoka\n";
const char s11e_aKonoasiatoha_800DECA4[] = "kono asiatoha??\n";
const char s11e_aKinoseika_800DECB8[] = "kinoseika !!\n";
const char s11e_aItazo_800DECC8[] = "itazo \n";
const char s11e_aKottida_800DECD0[] = "kottida!!\n";
const char s11e_aHaitinimodoruzo_800DECDC[] = "haitini modoruzo!!\n";
const char s11e_aKottida_800DECF0[] = "kottida !!\n";
const char s11e_dword_800DECFC[] = {0x0, 0x0, 0x0, 0x0};