#include "linker.h"
#include "psyq.h"
#include "overlays/s00a/Enemy/enemy.h"

const char aBoxkeriSnake[] = "スネーク";
const char sBoxkeriDanbowl[] = "段ボール";
const char aCbBox[] = "cb_box";
const char aBoxkeriC[] = {'b', 'o', 'x', 'k', 'e', 'r', 'i', '.', 'c', 0x0, 0x7, 'R'};

const char aSmoke[] = "smoke";
const char aSmokeC[] = "smoke.c";

// Enemy/wall.c
const char aDestroy[] = "destroy\n";
const char aBox01[] = "box_01";
const char aDbx1[] = "dbx1";
const char aDbx2[] = "dbx2";
const char aWallC[] = {'w', 'a', 'l', 'l', '.', 'c', 0x0, 0x80};

// Enemy/asioto.c
const char aAsiotoSeSetErr[] = " asioto se set err \n";
const char aAsiotoSeNoiseSetErr[] = " asioto se noise set err \n";
const char aMigiSodesuri[] = " migi sodesuri %d \n";
const char aAsiotoC[] = {'a', 's', 'i', 'o', 't', 'o', '.', 'c', 0x0, 0x15, 'S', 'e'};
