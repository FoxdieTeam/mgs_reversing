#include "linker.h"
#include "libgcl/libgcl.h"

const char s03e_dword_800CBFA8[] = {'e', 'v', 'p', 'a'};
const char s03e_dword_800CBFAC[] = {'n', 'e', 'l', '.'};
const char s03e_dword_800CBFB0[] = {'c', 0x0, '0', '0'};

// Game/lamp.c
const char aTexparseerror[] = "TEX:PARSE ERROR\n";
const char aLampC[] = {'l', 'a', 'm', 'p', '.', 'c', 0x0, '0'};

const char s03e_dword_800CBFD0[] = {'i', 'n', 't', 'r'};
const char s03e_dword_800CBFD4[] = {'_', 'c', 'a', 'm'};
const char s03e_dword_800CBFD8[] = {'.', 'c', 0x0, 'g'};

const char aMotseC[] = "motse.c";

// Enemy/wall.c
const char aDestroy[] = "destroy\n";
const char aBox01[] = "box_01";
const char aDbx1[] = "dbx1";
const char aDbx2[] = "dbx2";
const char aWallC[] = {'w', 'a', 'l', 'l', '.', 'c', 0x0, 'M'};

// Enemy/asioto.c
const char aAsiotoSeSetErr[] = " asioto se set err \n";
const char aAsiotoSeNoiseSetErr[] = " asioto se noise set err \n";
const char aMigiSodesuri[] = " migi sodesuri %d \n";
const char aAsiotoC[] = {'a', 's', 'i', 'o', 't', 'o', '.', 'c', 0x0, 'r', 'e', 'A'};

// Okajima/uji.c
const char aUji[] = "uji";
const char aUjiC[] = {'u', 'j', 'i', '.', 'c', 0x0, '4', '4'};

const int s03e_dword_800CC070 = 0x800C7544;
const int s03e_dword_800CC074 = 0x800C7544;
const int s03e_dword_800CC078 = 0x800C7564;
const int s03e_dword_800CC07C = 0x800C7584;
const int s03e_dword_800CC080 = 0x800C75A4;

const SVECTOR s03e_svec_800CC084 = {0, -80, 0, 0};

const char s03e_aKill_800CC08C[] = "kill";

const char s03e_dword_800CC094[] = {0xb2, 0xbb, 0xc6, 0xfe};
const char s03e_dword_800CC098[] = {0xa4, 0xec, 0xa4, 0xeb};
const char s03e_dword_800CC09C[] = {0x0, 0x0, 0x0, 0x0};

const char s03e_dword_800CC0A0[] = {0xb2, 0xbb, 0xc0, 0xda};
const char s03e_dword_800CC0A4[] = {0xa4, 0xeb, 0x0, 0x0};

const char s03e_dword_800CC0A8[] = {0xbb, 0xeb, 0xce, 0xcf};
const char s03e_dword_800CC0AC[] = {0xcc, 0xe1, 0xa4, 0xb9};
const char s03e_dword_800CC0B0[] = {0x0, 0x0, 0x0, 0x0};

const char s03e_dword_800CC0B4[] = {0xbb, 0xeb, 0xce, 0xcf};
const char s03e_dword_800CC0B8[] = {0xcc, 0xb5, 0xa4, 0xaf};
const char s03e_dword_800CC0BC[] = {0xa4, 0xb9, 0x0, 0x0};

const char s03e_dword_800CC0C0[] = {0xbd, 0xe8, 0xcd, 0xfd};
const char s03e_dword_800CC0C4[] = {0xba, 0xc6, 0xb3, 0xab};
const char s03e_dword_800CC0C8[] = {0x0, 0x0, 0x0, 0x0};

const char s03e_dword_800CC0CC[] = {0xbd, 0xe8, 0xcd, 0xfd};
const char s03e_dword_800CC0D0[] = {0xc4, 0xe4, 0xbb, 0xdf};
const char s03e_dword_800CC0D4[] = {0x0, 0x0, 0x0, 0x0};
