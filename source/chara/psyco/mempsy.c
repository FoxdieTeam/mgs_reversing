#include <stdio.h>
#include <stddef.h>
#include "mts/mts.h"    // for cprintf

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libhzd/libhzd.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

#include "chara/snake/sna_init.h"
#include "chara/snake/shadow.h"         // for NewShadow
#include "okajima/blurpure.h"           // for NewBlurPure
#include "takabe/cineutil.h"            // for OpenCinemaScreen, etc.

/*---------------------------------------------------------------------------*/

#define BODY_DATA   GV_StrCode( "psycho" )
#define MOTION_DATA GV_StrCode( "psy_07b2" )

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | \
                      DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

typedef struct _ACTION {
    int time;
    int action;
} ACTION;

typedef struct _SAVEFILE {
    char *name;
    int   mask;
} SAVEFILE;

typedef struct _Work {
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT m_segs1[ 17 ];
    MOTION_SEGMENT m_segs2[ 17 ];
    SVECTOR        rots[ 16 ];
    SVECTOR        adjust[ 16 ];
    MATRIX         light[ 2 ];
    void          *shadow;
    void          *blur;
    short          field_7E0; /* unused */
    short          field_7E2; /* unused */
    int            field_7E4; /* unused */
    int            field_7E8; /* unused */
    int            flag;
    void          *action;
    int            time;
    ACTION        *action_list;
    int            time2;
    short          field_800;
    short          field_802;
    short          field_804;
    short          field_806;
    SVECTOR        field_808; /* unused */
    int            field_810;
    int            field_814[ 40 ];
    int            field_8B4[ 7 ];
} Work;

/*---------------------------------------------------------------------------*/

static ACTION s07b_dword_800C34A8[] = 
{
    { 0x0000, 0x0006 },
    { 0x0010, 0x0005 },
    { 0x0064, 0x0003 },
    { 0x0000, 0x0004 },
    { 0x0000, 0x0005 },
    { 0x0000, 0x0006 },
    { 0x0000, 0x0007 },
    { 0x0000, 0x0004 },
    { 0x006E, 0x0005 },
    { 0x0000, 0x0006 },
    { 0x0000, 0x0007 },
    { 0x0000, 0x0004 },
    { 0x0073, 0x0005 },
    { 0x0000, 0x0006 },
    { 0x0000, 0x0007 },
    { 0x0000, 0x0004 },
    { 0x0000, 0x0005 },
    { 0x006E, 0x0006 },
    { 0x0000, 0x0007 },
    { 0x0000, 0x0004 },
    { 0x00BE, 0x0001 },
    { 0x0000, 0x0001 },
    { 0x008E, 0x0002 },
    { 0x0000, 0x0008 },
    { 0x0033, 0x0009 },
    { 0x0000, 0x0002 },
    { 0x0000, 0x0001 },
    { 0x0000, 0x0004 },
    { 0x0000, 0x0001 },
    { 0x0000, 0x0005 },
    { 0x0000, 0x0006 },
    { 0x0000, 0x0007 },
    { 0x0000, 0x0004 },
    { 0x0000, 0x0005 },
    { 0x0000, 0x0002 },
    { 0x0000, 0x0002 },
    { 0x0000, 0x0009 },
    { 0x0041, 0x0004 },
    { 0x0078, 0x0005 },
    { 0x0000, 0x0009 },
    { 0x003C, 0x0006 },
    { 0x0082, 0x0007 },
    { 0x0000, 0x0009 },
    { 0x003D, 0x0004 },
    { 0x0077, 0x0005 },
    { 0x0000, 0x0001 },
    { 0x0079, 0x0002 },
    { 0x0000, 0x000A },
    { 0x0054, 0x0002 },
    { 0x00C2, 0x0003 },
    { 0x0154, 0x000D },
    { 0x0000, 0x0004 },
    { 0x004A, 0x0005 },
    { 0x0000, 0x0007 },
    { 0x0047, 0x0002 },
    { 0x0000, 0x0007 },
    { 0x0040, 0x000C },
    { 0x0000, 0x000B },
    { 0x0000, 0x000B },
    { 0x0000, 0x000B },
    { 0x0000, 0x0002 },
    { 0x0000, 0x0000 },
};

static int s07b_dword_800C3698[] =
{
    1, 5, 4, 3, 3, 4, 3, 3,
    5, 4, 3, 3, 4, 5, 5, 1,
    1, 2, 2, 1, 2, 1, 3, 3,
    4, 2, 5, 1, 5, 5, 1, 5,
    1, 2, 1, 1, 1, 1, 1, 1,
};

static char s07b_dword_800C3738[] =
{
    1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 1, 3,
};

static int s07b_dword_800C3748[] =
{
    17, 18, -1, -1, 39, 26, -1, -1,
    22, 19, 21, 20, 24, 23, -1, 25,
};

/*---------------------------------------------------------------------------*/

#define GENRE_MISC              (0x0000)
#define GENRE_ACTION            (0x0100)
#define GENRE_ADV               (0x0200)    // Japanese-style Adventure Game
#define GENRE_FIGHTING          (0x0200)
#define GENRE_FIGHTINGACTION    (GENRE_ACTION | GENRE_FIGHTING)
#define GENRE_RPG               (0x0400)
#define GENRE_ACTIONRPG         (GENRE_ACTION | GENRE_RPG)
#define GENRE_RENAI_SIM         (0x0800)    // Japan-only
#define GENRE_ADVENTURE         (0x0800)
#define GENRE_ACTIONADVENTURE   (GENRE_ACTION | GENRE_ADVENTURE)
#define GENRE_ARCADE            (0x1000)
#define GENRE_ACTIONARCADE      (GENRE_ACTION | GENRE_ARCADE)
#define GENRE_SPORTS            (0x2000)

/* Japanese version */
#define TITLE_TOKIMEMO          (0x0001)
#define TITLE_POLICENAUTS       (0x0002)
#define TITLE_HIDEOKOJIMA       (0x0010)    // "A Hideo Kojima Game"
#define TITLE_KCEJAPAN          (0x0020)    // Developed by KCE Japan

/* International versions */
#define TITLE_SUIKODEN          (0x0001)
#define TITLE_AZUREDREAMS       (0x0002)
#define TITLE_CASTLEVANIA       (0x0010)
#define TITLE_VANDALHEARTS      (0x0020)

static SAVEFILE s07b_dword_800C3788[] = {
#ifdef INTEGRAL
    { "SLPS-00002", GENRE_ARCADE },     // Gokujou Parodius Da! Deluxe Pack
    { "SLPS-00015", GENRE_MISC },       // TwinBee Taisen Puzzle-dama
    { "SLPS-00016", GENRE_SPORTS },     // Jikkyou Powerful Pro Yakyuu '95
    { "SLPS-00067", GENRE_SPORTS },     // Jikkyou Powerful Pro Yakyuu '95: Kaimakuban
    { "SLPS-00068", GENRE_SPORTS },     // J.League Jikkyou Winning Eleven
    { "SLPS-00090", GENRE_MISC },       // Eisei Meijin
    { "SLPS-00100", GENRE_MISC },       // Detana Twinbee Yahoo! Deluxe Pack
    { "SLPS-00065", GENRE_MISC },       // Tokimeki Memorial: Forever with You
    { "SLPS-00064", GENRE_MISC },       // Tokimeki Memorial: Forever with You (Genteiban)
    { "SLPS-00097", GENRE_RPG | TITLE_SUIKODEN }, // Gensou Suikoden
    { "SLPS-00188", GENRE_SPORTS },     // NBA Power Dunkers
    { "SLPS-00215", GENRE_MISC },       // Policenauts
    { "SLPS-00228", GENRE_MISC },       // Private Collection: Policenauts
    { "SLPS-00154", GENRE_MISC },       // Snatcher
    { "SLPS-00255", GENRE_ARCADE },     // Susume! Taisen Puzzle-dama
    { "SLPS-00272", GENRE_SPORTS },     // World Soccer Winning Eleven
    { "SLPS-00217", GENRE_ADVENTURE },  // Ganbare Goemon: Uchuu Kaizoku Akogingu
    { "SLPS-00303", GENRE_ARCADE },     // Gradius Deluxe Pack
    { "SLPM-86001", GENRE_MISC },       // Private Collection: Tokimeki Memorial
    { "SLPM-86003", GENRE_SPORTS },     // Eikou no Fairway: Virtual Golf Simulation
    { "SLPM-86002", GENRE_SPORTS },     // Hyper Olympic in Atlanta
    { "SLPM-86005", GENRE_ARCADE },     // Tokimeki Memorial Taisen Puzzledama
    { "SLPM-86006", GENRE_MISC },       // Pachinko Dream
    { "SLPM-86004", GENRE_SPORTS },     // Bottom of the 9th: Major League Heroes
    { "SLPM-86007", GENRE_RPG | TITLE_VANDALHEARTS }, // Vandal Hearts: Ushinawareta Kodai Bunmei
    { "SLPM-86009", GENRE_ARCADE },     // Sexy Parodius
    { "SLPM-86010", GENRE_SPORTS },     // J.League Jikkyou Winning Eleven '97
    { "SLPM-86011", GENRE_SPORTS },     // NBA Power Dunkers 2
    { "SLPM-86013", GENRE_ARCADE },     // Speed King: Neo Kobe 2045
    { "SLPM-86008", GENRE_ARCADE },     // Jikkyou Oshaberi Parodius: Forever with Me
    { "SLPM-86015", GENRE_FIGHTING },   // Lightning Legend: Daigo no Daibouken
    { "SLPM-86014", GENRE_MISC },       // Eisei Meijin II
    { "SLPM-86021", GENRE_ARCADE },     // Henry Explorers
    { "SLPM-86023", GENRE_ACTIONADVENTURE | TITLE_CASTLEVANIA }, // Akumajou Dracula X: Gekka no Yasoukyoku
    { "SLPM-86012", GENRE_MISC },       // Breeding Stud: Bokujou de Aimashou
    { "SLPM-86029", GENRE_MISC },       // Tokimeki Memorial Selection: Fujisaki Shiori
    { "SLPM-86035", GENRE_SPORTS },     // World Soccer Winning Eleven '97
    { "SLPM-86034", GENRE_ACTION },     // Poitter's Point
    { "SLPM-86036", GENRE_MISC },       // Tokimeki Memorial: Taisen Tokkaedama
    { "SLPM-86037", GENRE_ARCADE },     // Salamander Deluxe Pack Plus
    { "SLPM-86039", GENRE_MISC },       // Tokimeki Memorial Drama Series Vol.1: Nijiiro no Seishun
    { "SLPM-86024", GENRE_SPORTS },     // Jikkyou Powerful Pro Yakyuu '97: Kaimakuban
    { "SLPM-86042", GENRE_ARCADE },     // Gradius Gaiden
    { "SLPM-86044", GENRE_SPORTS },     // Break Point
    { "SLPM-86016", GENRE_MISC },       // Paro Wars
    { "SLPM-86047", GENRE_ACTIONRPG | TITLE_AZUREDREAMS }, // Other Life Azure Dreams
    { "SLPM-86025", GENRE_ARCADE },     // Lethal Enforcers Deluxe Pack
    { "SLPM-86052", GENRE_MISC },       // Konami Antiques: MSX Collection Vol.1
    { "SLPM-86022", GENRE_ARCADE },     // Midnight Run: Road Fighter 2
    { "SLPM-86254", GENRE_MISC },       // Aitakute...: Your Smiles in My Heart
    { "SLPM-86055", GENRE_SPORTS },     // J.League Jikkyou Winning Eleven 3
    { "SLPM-86053", GENRE_MISC },       // Tokimeki Memorial: Forever with You (PlayStation the Best)
    { "SLPM-86056", GENRE_SPORTS },     // Hyper Olympic in Nagano
    { "SLPM-86060", GENRE_SPORTS },     // NBA Power Dunkers 3
    { "SLPM-86062", GENRE_MISC },       // Konami Antiques: MSX Collection Vol.2
    { "SLPM-86068", GENRE_MISC },       // Mitsumete Knight
    { "SLPM-86072", GENRE_MISC },       // Konami Antiques: MSX Collection Vol.3
    { "SLPM-86065", GENRE_ACTIONARCADE }, // Broken Helix
    { "SLPM-86070", GENRE_MISC },       // Tokimeki Memorial Drama Series Vol.2: Irodori no Love Song
    { "SLPM-86076", GENRE_MISC },       // Yoshimura Shougi
    { "SLPM-86077", GENRE_RPG },        // TwinBee RPG
    { "SLPM-86078", GENRE_SPORTS },     // Actua Ice Hockey
    { "SLPM-86086", GENRE_SPORTS },     // World Soccer Jikkyou Winning Eleven 3: World Cup France '98
    { "SLPM-86026", GENRE_ACTION },     //
    { "SLPM-86046", GENRE_SPORTS },     // Jikkyou American Baseball
    { "SLPM-86075", GENRE_MISC },       // Jersey Devil no Daibouken
    { "SLPM-86119", GENRE_SPORTS },     // Jikkyou American Baseball 2
    { "SLPM-86124", GENRE_ARCADE },     // Exciting Bass
    { "SLPM-86122", GENRE_MISC },       // Dolphin's Dream
    { "SLPM-86123", GENRE_MISC },       // Bishi Bashi Special
    { "SLPM-86099", GENRE_ACTION },     // Magical Medical
    { "SLPM-86100", GENRE_MISC },       // Dancing Blade Katte ni Momotenshi! (Disc 1)
    { "SLPM-86101", GENRE_MISC },       // Dancing Blade Katte ni Momotenshi! (Disc 2)
    { "SLPM-86102", GENRE_MISC },       // Dancing Blade Katte ni Momotenshi! (Disc 3)
    { "SLPM-86097", GENRE_SPORTS },     // Jikkyou Powerful Pro Yakyuu '98: Kaimakuban
    { "SLPM-86096", GENRE_MISC },       // Yu-Gi-Oh! Monster Capsule Breed & Battle
    { "SLPM-86061", GENRE_ACTION },     // Poitter's Point 2: Sodom no Inbou
    { "SLPM-86087", GENRE_MISC },       // Breeding Stud 2
    { "SLPM-86094", GENRE_MISC },       // Tokimeki no Houkago: Ne Quiz Shiyo
    { "SLPM-86111", GENRE_ACTION },     // METAL GEAR SOLID
    { "SLPM-86124", GENRE_MISC },       // Exciting Bass (again!)
    { "SLPM-86132", GENRE_SPORTS },     // Hyper Olympic in Nagano (PlayStation the Best)
    { "SLPM-86162", GENRE_SPORTS },     // World Soccer Jikkyou Winning Eleven 3: Final Ver.
    { "SLPM-86133", GENRE_FIGHTING },   // Bugi
    { "SLPM-86134", GENRE_RPG },        // Mitsumete Knight R: Daibouken-hen
    { "SLPM-86150", GENRE_MISC },       // Dance! Dance! Dance!
    { "SLPM-86154", GENRE_SPORTS },     // J.League Jikkyou Winning Eleven '98-'99
    { "SLPM-86155", GENRE_ADVENTURE },  // Ganbare Goemon: Kuru nara Koi! Ayashige Ikka no Kuroi Kage
    { "SLPM-80349", GENRE_ARCADE },     //
    { "SLPM-86168", GENRE_RPG | TITLE_SUIKODEN }, // Gensou Suikoden II
    { "SLPM-86173", GENRE_MISC },       // Mahjong Yarou ze!
    { "SLPM-86176", GENRE_SPORTS },     // NBA Power Dunkers 4
    { "SLPM-86184", GENRE_ARCADE },     // beatmania APPEND 3rdMIX
    { "SLPM-86149", GENRE_SPORTS },     // Jikkyou Powerful Pro Yakyuu '98: Ketteiban
    { "SLPM-86191", GENRE_MISC },       // Seishoujo Kantai Virgin Fleet
    { "SLPM-86192", GENRE_ADVENTURE },  // Silent Hill
    { "SLPM-86190", GENRE_MISC },       // Uchi ni Pochi ga Yattekita in my Pocket
    { "SLPM-86200", GENRE_MISC },       // Glint Glitters
    { "SLPM-86177", GENRE_ACTION },     // Shin Jidaigeki Action: Rasetsu no Ken
    { "SLPM-86210", GENRE_MISC },       // Dancing Blade Katte ni Momotenshi II: Tears of Eden (Disc 1)
    { "SLPM-86211", GENRE_MISC },       // Dancing Blade Katte ni Momotenshi II: Tears of Eden (Disc 2)
    { "SLPM-86212", GENRE_MISC },       // Dancing Blade Katte ni Momotenshi II: Tears of Eden (Disc 3)
    { "SLPM-86183", GENRE_ARCADE },     // Pop'n Music
    { "SLPM-86222", GENRE_ARCADE },     // Dance Dance Revolution
    { "SLPM-86224", GENRE_MISC },       // Tokimeki Memorial Drama Series Vol.3: Tabidachi no Uta (Disc 1)
    { "SLPM-86225", GENRE_MISC },       // Tokimeki Memorial Drama Series Vol.3: Tabidachi no Uta (Disc 2)
    { "SLPM-86199", GENRE_MISC },       // Eisei Meijin III: Game Creator Yoshimura Nobuhiro no Zunou
    { "SLPM-86229", GENRE_ARCADE },     // beatmania APPEND GottaMix
    { "SLPM-86228", GENRE_ARCADE },     // Konami 80's Arcade Gallery
    { "SLPM-86233", GENRE_MISC },       // Gungage
#else
#ifdef JAPANESE
/* Japanese version */
    // Gokujou Parodius Da! Deluxe Pack
    { "BISLPS-00002", GENRE_ARCADE },
    // TwinBee Taisen Puzzle-dama
    { "BISLPS-00015", GENRE_MISC },
    // Jikkyou Powerful Pro Yakyuu '95
    { "BISLPS-00016", GENRE_SPORTS },
    // Jikkyou Powerful Pro Yakyuu '95: Kaimakuban
    { "BISLPS-00067", GENRE_SPORTS },
    // J.League Jikkyou Winning Eleven
    { "BISLPS-00068", GENRE_SPORTS },
    // Eisei Meijin
    { "BISLPS-00090", GENRE_MISC },
    // Detana Twinbee Yahoo! Deluxe Pack
    { "BISLPS-00100", GENRE_MISC },
    // Tokimeki Memorial: Forever with You
    { "BISLPS-00065", GENRE_RENAI_SIM | TITLE_TOKIMEMO },
    // Tokimeki Memorial: Forever with You (Genteiban)
    { "BISLPS-00064", GENRE_RENAI_SIM | TITLE_TOKIMEMO },
    // Gensou Suikoden
    { "BISLPS-00097", GENRE_RPG },
    // NBA Power Dunkers
    { "BISLPS-00188", GENRE_SPORTS },
    // Policenauts
    { "BISLPS-00215", GENRE_ADV | TITLE_POLICENAUTS | TITLE_HIDEOKOJIMA | TITLE_KCEJAPAN },
    // Private Collection: Policenauts
    { "BISLPS-00228", GENRE_ADV | TITLE_POLICENAUTS | TITLE_HIDEOKOJIMA | TITLE_KCEJAPAN },
    // Snatcher
    { "BISLPS-00154", GENRE_ADV | TITLE_HIDEOKOJIMA },
    // Susume! Taisen Puzzle-dama
    { "BISLPS-00255", GENRE_ARCADE },
    // World Soccer Winning Eleven
    { "BISLPS-00272", GENRE_SPORTS },
    // Ganbare Goemon: Uchuu Kaizoku Akogingu
    { "BISLPS-00217", GENRE_ACTION },
    // Gradius Deluxe Pack
    { "BISLPS-00303", GENRE_ARCADE },
    // Private Collection: Tokimeki Memorial
    { "BISLPM-86001", GENRE_RENAI_SIM | TITLE_TOKIMEMO },
    // Eikou no Fairway: Virtual Golf Simulation
    { "BISLPM-86003", GENRE_SPORTS },
    // Hyper Olympic in Atlanta
    { "BISLPM-86002", GENRE_SPORTS },
    // Tokimeki Memorial Taisen Puzzledama
    { "BISLPM-86005", GENRE_ARCADE | TITLE_TOKIMEMO },
    // Pachinko Dream
    { "BISLPM-86006", GENRE_MISC },
    // Bottom of the 9th: Major League Heroes
    { "BISLPM-86004", GENRE_SPORTS },
    // Vandal Hearts: Ushinawareta Kodai Bunmei
    { "BISLPM-86007", GENRE_RPG },
    // Sexy Parodius
    { "BISLPM-86009", GENRE_ARCADE },
    // J.League Jikkyou Winning Eleven '97
    { "BISLPM-86010", GENRE_SPORTS },
    // NBA Power Dunkers 2
    { "BISLPM-86011", GENRE_SPORTS },
    // Speed King: Neo Kobe 2045
    { "BISLPM-86013", GENRE_ARCADE },
    // Jikkyou Oshaberi Parodius: Forever with Me
    { "BISLPM-86008", GENRE_ARCADE },
    // Lightning Legend: Daigo no Daibouken
    { "BISLPM-86015", GENRE_MISC },
    // Eisei Meijin II
    { "BISLPM-86014", GENRE_MISC },
    // Henry Explorers
    { "BISLPM-86021", GENRE_ARCADE },
    // Akumajou Dracula X: Gekka no Yasoukyoku
    { "BISLPM-86023", GENRE_ACTION },
    // Breeding Stud: Bokujou de Aimashou
    { "BISLPM-86012", GENRE_MISC },
    // Tokimeki Memorial Selection: Fujisaki Shiori
    { "BISLPM-86029", GENRE_MISC | TITLE_TOKIMEMO },
    // World Soccer Winning Eleven '97
    { "BISLPM-86035", GENRE_SPORTS },
    // Poitter's Point
    { "BISLPM-86034", GENRE_ACTION },
    // Tokimeki Memorial: Taisen Tokkaedama
    { "BISLPM-86036", GENRE_MISC | TITLE_TOKIMEMO },
    // Salamander Deluxe Pack Plus
    { "BISLPM-86037", GENRE_ARCADE },
    // Tokimeki Memorial Drama Series Vol.1: Nijiiro no Seishun
    { "BISLPM-86039", GENRE_ADV | TITLE_TOKIMEMO | TITLE_KCEJAPAN },
    // Jikkyou Powerful Pro Yakyuu '97: Kaimakuban
    { "BISLPM-86024", GENRE_SPORTS },
    // Gradius Gaiden
    { "BISLPM-86042", GENRE_ARCADE },
    // Break Point
    { "BISLPM-86044", GENRE_SPORTS },
    // Paro Wars
    { "BISLPM-86016", GENRE_MISC },
    // Other Life Azure Dreams
    { "BISLPM-86047", GENRE_ACTIONRPG },
    // Lethal Enforcers Deluxe Pack
    { "BISLPM-86025", GENRE_ARCADE },
    // Konami Antiques: MSX Collection Vol.1
    { "BISLPM-86052", GENRE_MISC },
    // Midnight Run: Road Fighter 2
    { "BISLPM-86022", GENRE_ARCADE },
    // Aitakute...: Your Smiles in My Heart: Oroshitate no Diary: Introduction Disc
    { "BISLPM-80162", GENRE_RENAI_SIM },
    // J.League Jikkyou Winning Eleven 3
    { "BISLPM-86055", GENRE_SPORTS },
    // Tokimeki Memorial: Forever with You (PlayStation the Best)
    { "BISLPM-86053", GENRE_MISC | TITLE_TOKIMEMO },
    // Hyper Olympic in Nagano
    { "BISLPM-86056", GENRE_SPORTS },
    // NBA Power Dunkers 3
    { "BISLPM-86060", GENRE_SPORTS },
    // Konami Antiques: MSX Collection Vol.2
    { "BISLPM-86062", GENRE_MISC },
    // Mitsumete Knight
    { "BISLPM-86068", GENRE_RENAI_SIM },
    // Konami Antiques: MSX Collection Vol.3
    { "BISLPM-86072", GENRE_MISC },
    // Broken Helix
    { "BISLPM-86065", GENRE_ACTIONARCADE },
    // Tokimeki Memorial Drama Series Vol.2: Irodori no Love Song
    { "BISLPM-86070", GENRE_ADV | TITLE_TOKIMEMO | TITLE_KCEJAPAN },
    // Yoshimura Shougi
    { "BISLPM-86076", GENRE_MISC },
    // TwinBee RPG
    { "BISLPM-86077", GENRE_RPG },
    // Actua Ice Hockey
    { "BISLPM-86078", GENRE_SPORTS },
    // World Soccer Jikkyou Winning Eleven 3: World Cup France '98
    { "BISLPM-86086", GENRE_SPORTS },
    //
    { "BISLPM-86026", GENRE_ACTION },
    // Jikkyou American Baseball
    { "BISLPM-86046", GENRE_SPORTS },
    // Jersey Devil no Daibouken
    { "BISLPM-86075", GENRE_MISC },
    // Jikkyou American Baseball 2
    { "BISLPM-86119", GENRE_SPORTS },
    // Exciting Bass
    { "BISLPM-86124", GENRE_ARCADE },
    // Dolphin's Dream
    { "BISLPM-86122", GENRE_MISC },
    // Bishi Bashi Special
    { "BISLPM-86123", GENRE_MISC },
    // Magical Medical
    { "BISLPM-86099", GENRE_ACTION },
    // Dancing Blade Katte ni Momotenshi! (Disc 1)
    { "BISLPM-86100", GENRE_ADV },
    // Dancing Blade Katte ni Momotenshi! (Disc 2)
    { "BISLPM-86101", GENRE_ADV },
    // Dancing Blade Katte ni Momotenshi! (Disc 3)
    { "BISLPM-86102", GENRE_ADV },
    // Jikkyou Powerful Pro Yakyuu '98: Kaimakuban
    { "BISLPM-86097", GENRE_SPORTS },
    // Yu-Gi-Oh! Monster Capsule Breed & Battle
    { "BISLPM-86096", GENRE_MISC },
    // Poitter's Point 2: Sodom no Inbou
    { "BISLPM-86061", GENRE_ACTION },
    // Breeding Stud 2
    { "BISLPM-86087", GENRE_MISC },
    // Tokimeki no Houkago: Ne Quiz Shiyo
    { "BISLPM-86094", GENRE_MISC | TITLE_TOKIMEMO },
#else
#ifdef PAL
/* European version */
    // Parodius
    { "SLES-00036", GENRE_ACTION },
    // Goal Storm
    { "SLES-00069", GENRE_SPORTS },
    // NBA in the Zone
    { "SLES-00171", GENRE_SPORTS },
    // International Track & Field
    { "SLES-00333", GENRE_SPORTS },
    // Konami Open Golf
    { "SLES-00337", GENRE_SPORTS },
    // Project Overkill
    { "SLES-00500", GENRE_ACTION },
    // NBA in the Zone 2
    { "SLES-00560", GENRE_SPORTS },
    // International Superstar Soccer Deluxe
    { "SLES-00511", GENRE_SPORTS },
    // Contra: Legacy of War
    { "SLES-00608", GENRE_ACTION },
    // Whizz
    { "SLES-00141", GENRE_MISC },
    // Suikoden
    { "SLES-00527", GENRE_RPG | TITLE_SUIKODEN },
    // Crypt Killer
    { "SLES-00292", GENRE_ACTION },
    // Vandal Hearts
    { "SLES-00204", GENRE_RPG | TITLE_VANDALHEARTS },
    // Soviet Strike (Germany)
    { "SLES-00509", GENRE_SPORTS },
    // International Superstar Soccer Pro
    { "SLES-00559", GENRE_SPORTS },
    // Road Rage
    { "SLES-00543", GENRE_MISC },
    // Lethal Enforcers
    { "SLES-00542", GENRE_ACTION },
    // Poy Poy
    { "SLES-00785", GENRE_ACTION },
    // Castlevania: Symphony of the Night
    { "SLES-00524", GENRE_ACTION | TITLE_CASTLEVANIA },
    // Midnight Run: Road Fighter 2
    { "SLES-00590", GENRE_MISC },
    // Broken Helix (Germany)
    { "SLES-00962", GENRE_ACTION },
    // NBA Pro 98
    { "SLES-00882", GENRE_SPORTS },
    // Nagano Winter Olympics '98
    { "SLES-00999", GENRE_SPORTS },
    // Azure Dreams
    { "SLES-01219", GENRE_RPG | TITLE_AZUREDREAMS },
    // International Superstar Soccer Pro '98
    { "SLES-01218", GENRE_SPORTS },
    // International Superstar Soccer Pro '98
    { "SLES-01264", GENRE_SPORTS },
    // Diver's Dream
    { "SLES-01535", GENRE_ACTION },
#else
/* North American version */
    // NBA in the Zone
    { "SLUS-00048", GENRE_SPORTS },
    // Goal Storm
    { "SLUS-00055", GENRE_SPORTS },
    // Bottom of the 9th
    { "SLUS-00049", GENRE_SPORTS },
    // International Track & Field
    { "SLUS-00238", GENRE_SPORTS },
    // The Final Round
    { "SLUS-00064", GENRE_SPORTS },
    // Project Overkill
    { "SLUS-00045", GENRE_ACTION },
    // NBA in the Zone 2
    { "SLUS-00294", GENRE_SPORTS },
    // Suikoden
    { "SLUS-00292", GENRE_RPG | TITLE_SUIKODEN },
    // Iron Man / X-O Manowar in Heavy Metal
    { "SLUS-00235", GENRE_ACTION },
    // Vandal Hearts
#ifdef BUGFIX
    { "SLUS-00447", GENRE_RPG | TITLE_VANDALHEARTS },
#else
    { "SLUS-00447", GENRE_RPG /*| TITLE_VANDALHEARTS*/ },
#endif
    // Contra: Legacy of War
    { "SLUS-00288", GENRE_ACTION },
    // Goal Storm '97
    { "SLUS-00295", GENRE_SPORTS },
    // Broken Helix
    { "SLUS-00289", GENRE_ACTION },
    // Lethal Enforcers I & II
    { "SLUS-00293", GENRE_ACTION },
    // Poy Poy
    { "SLUS-00486", GENRE_ACTION },
    // Bottom of the 9th '97
    { "SLUS-00296", GENRE_SPORTS },
    // Castlevania: Symphony of the Night
    { "SLUS-00067", GENRE_ACTION | TITLE_CASTLEVANIA },
    // NBA in the Zone '98
    { "SLUS-00445", GENRE_SPORTS },
    // Nagano Winter Olympics '98
    { "SLUS-00591", GENRE_SPORTS },
    // Azure Dreams
    { "SLUS-00614", GENRE_RPG | TITLE_AZUREDREAMS },
    // Bottom of the 9th '99
    { "SLUS-00678", GENRE_SPORTS },
    // International Superstar Soccer Pro '98
    { "SLUS-00674", GENRE_SPORTS },
    // Kensei: Sacred Fist
    { "SLUS-00600", GENRE_FIGHTINGACTION },
    // Silent Hill
    { "SLUS-00707", GENRE_ADVENTURE },
#endif // PAL
#endif // JAPANESE
#endif // INTEGRAL
};

/*---------------------------------------------------------------------------*/

extern u_short GM_WeaponTypes[];
extern u_short GM_ItemTypes[];

extern void s07b_800D2988( void );
extern void s07b_800D2A0C( int );
extern void s07b_800D2A64( void );
extern int  s07b_800D2C4C( void );
extern int  s07b_800D2CB4( int );

void s07b_800D8564( Work *work, int time );
void s07b_800D88E4( Work *work, int time );
void s07b_800D8B8C( Work *work, int time );

static inline void SetMode( Work *work, void *action )
{
    work->action = action;
    work->time = 0;
    work->field_802 = 0;
    work->field_800 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static int CheckCutsceneSkip( Work *work )
{
    GV_PAD *pad;

    pad = &GV_PadData[ 2 ];
    if ( ( pad[ 0 ].press | pad[ 1 ].press ) & PAD_CROSS )
    {
        s07b_800D2988();
        CloseCinemaScreen();
        GCL_ExecProc( work->field_8B4[ 0 ], NULL );
        return 1;
    }
    return 0;
}

static void s07b_800D7ED8( Work *work, int index )
{
    ACTION *list;
    int i;

    work->flag |= 0x1;
    work->time2 = 0;

    list = s07b_dword_800C34A8;
    i = 0;

    /* TODO: figure out this loop */
    for ( ;; )
    {
        if ( list->time != 0 )
        {
            /* do nothing */
        }
        else
        {
            if ( i == index ) break;
            i++;
        }

        list++;
    }

    work->action_list = list;
    work->field_810 = work->field_814[ index ];

    GCL_ExecProc( work->field_8B4[ s07b_dword_800C3698[ index ] ], NULL );
}

void s07b_800D7F6C( Work *work )
{
    ACTION *list;
    int time, action;

    if ( work->flag & 0x4 ) return;

    if ( work->flag & 0x2 )
    {
        work->flag &= ~0x1;
        if ( work->body.is_end )
        {
            work->flag |= 0x1;
            work->flag &= ~0x2;
        }
    }

    if ( work->flag & 0x1 )
    {
        time = work->time2++;
        list = work->action_list;

        if ( time == 0 && work->field_810 >= 0 )
        {
            s07b_800D2A0C( work->field_810 );
        }

        if ( time == list->time )
        {
            action = list->action;
            if ( work->body.action != action )
            {
                GM_ConfigObjectAction( &work->body, action, 0, 4 );
            }

            work->action_list++;
        }

        if ( work->body.is_end )
        {
            if ( list->time == 0 ) work->flag &= ~0x1;
            if ( work->body.action != 0 && work->body.action != 9 && work->body.action != 0 )
            {
                GM_ConfigObjectAction( &work->body, 0, 0, 4 );
            }
        }
    }
}

void s07b_800D80B8( Work *work, int time )
{
    int var_s1, index;

    if ( time == 0 )
    {
        OpenCinemaScreen( 1, 1000000 );
        s07b_800D7ED8( work, 0 );
        GCL_ExecProc( work->field_8B4[ 1 ], NULL );
    }

    var_s1 = work->field_800;
    switch ( work->field_802 )
    {
    case 0:
        if ( !s07b_800D2C4C() ) break;
        printf( "enemy watch %d\n", GM_EnemyWatchCount );
        index = 8;

        if ( GM_EnemyWatchCount > 8 )
        {
            index = 1;
            var_s1 = 1;
        }

        s07b_800D7ED8( work, index );

        work->field_800 = var_s1;
        work->field_802++;
        break;
    case 1:
        if ( !s07b_800D2C4C() ) break;
        printf( "continue count %d\n", GM_ContinueCount );

        if ( GM_ContinueCount > 8 )
        {
            index = ( var_s1 == 1 ) ? 2 : 9;
            var_s1 |= 2;
        }
        else
        {
            index = ( var_s1 == 1 ) ? 5 : 12;
        }

        s07b_800D7ED8( work, index );
        work->field_800 = var_s1;
        work->field_802++;
        break;
    case 2:
        if ( !s07b_800D2C4C() ) break;

        printf( "trap out count %d\n", GM_PitfallDeathCount );

        if ( GM_PitfallDeathCount > 4 )
        {
            switch ( var_s1 )
            {
            case 0:
                index = 13;
                break;
            case 1:
                index = 6;
                break;
            case 2:
                index = 10;
                break;
            default:
                index = 3;
                break;
            }
        }
        else
        {
            switch ( var_s1 )
            {
            case 0:
                index = 14;
                break;
            case 1:
                index = 7;
                break;
            case 2:
                index = 11;
                break;
            default:
                index = 4;
                break;
            }
        }

        s07b_800D7ED8( work, index );
        work->field_802++;
        break;
    case 3:
        if ( !s07b_800D2C4C() ) break;
        SetMode( work, s07b_800D8564 );
        break;
    }
}

void s07b_800D8338( char *name, char *arg1, char *arg2 )
{
    SAVEFILE *save;
    int i, j, match, mask, bit;

    save = s07b_dword_800C3788;

    for ( i = 0; i < COUNTOF( s07b_dword_800C3788 ); i++ )
    {
        match = 0;

        for ( j = 2; j < 12; j++ )
        {
            if ( name[ j ] != save->name[ j - 2 ] )
            {
                match = 1;
                break;
            }
        }

        if ( match == 0 ) break;
        save++;
    }

    if ( i != 110 && arg2[ i ] == 0 )
    {
        arg1[ 15 ]++;
        arg2[ i ] = 1;

        mask = save->mask;
        for ( i = 0; i < 15; i++ )
        {
            bit = 1 << i;
            if ( bit & mask ) arg1[ i ]++;
        }
    }
}

int s07b_800D8410( MEMCARD **cards )
{
    char sp10[ 16 ];
    char sp20[ 110 ];
    short mask;
    int i, j;
    MEMCARD *card;

    mask = 0;

    for ( i = 0; i < 16; i++ )
    {
        sp10[ i ] = 0;
    }

    for ( i = 0; i < COUNTOF( s07b_dword_800C3788 ); i++ )
    {
        sp20[ i ] = 0;
    }

    for ( i = 0; i < 2; i++ )
    {
        card = cards[ i ];
        if ( card == NULL ) continue;

        for ( j = 0; j < card->file_count; j++ )
        {
            printf( "name %s\n", card->files[ j ].name );
            s07b_800D8338( card->files[ j ].name, sp10, sp20 );
        }
    }

    for ( i = 0; i < 16; i++ )
    {
        if ( sp10[ i ] >= s07b_dword_800C3738[ i ] ) mask |= 1 << i;
    }

    return mask;
}

void s07b_800D8564( Work *work, int time )
{
    MEMCARD *cards[ 2 ];
    int i;

    if ( time == 0 )
    {
        cards[ 0 ] = cards[ 1 ] = 0;

        if ( !( memcard_check( 0 ) & 0x80000000 ) )
        {
            cards[ 0 ] = memcard_files( 0 );
        }

        if ( !( memcard_check( 1 ) & 0x80000000 ) )
        {
            cards[ 1 ] = memcard_files( 1 );
        }

        if ( cards[ 0 ] == NULL && cards[ 1 ] == NULL )
        {
            SetMode( work, s07b_800D88E4 );
            return;
        }

        work->field_804 = 1;
        s07b_800D7ED8( work, 15 );
        work->field_800 = s07b_800D8410( cards );
    }

    if ( work->field_806 == 0 )
    {
        if ( s07b_800D2CB4( work->field_814[ 15 ] ) )
        {
            work->field_804 = 0;
            if ( work->field_800 != 0 )
            {
                work->field_804 = 1;
                s07b_800D7ED8( work, 16 );
            }
            work->field_806 = 1;
        }
        return;
    }

    if ( work->field_800 == 0 )
    {
        if ( work->field_804 == 0 )
        {
            s07b_800D7ED8( work, 30 );

            if ( work->body.action != 8 )
            {
                GM_ConfigObjectAction( &work->body, 8, 0, 4 );
            }

            work->field_802 = 16;
            work->field_804 = 1;
            work->flag |= 0x2;
        }
        else if ( s07b_800D2C4C() )
        {
            work->field_800 = 1;
            work->field_804--;
        }
    }
    else if ( work->field_804 == 0 )
    {
        for ( i = work->field_802; i < 16; i++ )
        {
            if ( ( work->field_800 >> i ) & 0x1 ) break;
        }

        if ( i == 16 )
        {
            work->field_802 = 17;
            printf( "save count %d\n", GM_SaveCount );

            if ( GM_SaveCount > 8 )
            {
                if ( work->field_800 != 0 )
                {
                    s07b_800D7ED8( work, 28 );

                    if ( work->body.action != 8 )
                    {
                        GM_ConfigObjectAction( &work->body, 8, 0, 4 );
                    }

                    work->field_804 = 1;
                    work->flag |= 0x2;
                }
            }
            else
            {
                if ( work->field_800 != 0 )
                {
                    s07b_800D7ED8( work, 29 );

                    if ( work->body.action != 8 )
                    {
                        GM_ConfigObjectAction( &work->body, 8, 0, 4 );
                    }

                    work->flag |= 0x2;
                }
                else
                {
                    s07b_800D7ED8( work, 31 );
                }

                work->field_804 = 1;
            }
        }
        else
        {
            work->field_802 = i + 1;
            printf( "set %d\n", s07b_dword_800C3748[ i ] );
            s07b_800D7ED8(work, s07b_dword_800C3748[ i ] );
            work->field_804 = 1;
        }
    }
    else if ( s07b_800D2C4C() )
    {
        work->field_804--;
    }

    if ( work->field_802 == 17 && work->field_804 == 0 )
    {
        work->field_802 = 18;
        s07b_800D7ED8( work, 27 );
        work->field_804 = 1;
    }
    else if ( work->field_802 == 18 && ( work->field_804 == 0 || s07b_800D2C4C() ) )
    {
        SetMode( work, s07b_800D88E4 );
    }
}

void s07b_800D88E4( Work *work, int time )
{
    if ( time == 0 )
    {
        if ( mts_get_pad_vibration_type( 1 ) == 0 )
        {
            SetMode( work, s07b_800D8B8C );
            return;
        }
        else if ( GM_Configuration & ( GM_CONFIG_UNKNOWN_2000 | GM_CONFIG_VIBRATION_OFF ) )
        {
            SetMode( work, s07b_800D8B8C );
            return;
        }
        else
        {
            s07b_800D7ED8( work, 32 );
        }
    }

    switch ( work->field_800 )
    {
    case 0:
        if ( s07b_800D2C4C() )
        {
            s07b_800D7ED8( work, 33 );
            work->field_800++;
        }
        break;
    case 1:
        if ( s07b_800D2CB4( work->field_814[ 33 ] ) )
        {
            work->field_800++;
        }
        break;
    case 2:
        if ( work->field_802 == 0 )
        {
            s07b_800D7ED8( work, 36 );
        }

        if ( s07b_800D2CB4( work->field_814[ 36 ] ) )
        {
            s07b_800D7ED8( work, 37 );
        }

        if ( s07b_800D2CB4( work->field_814[ 37 ] ) )
        {
            s07b_800D7ED8( work, 38 );
        }

        if ( work->field_802 == 30 && work->body.action != 11 )
        {
            GM_ConfigObjectAction( &work->body, 11, 0, 4 );
        }

        if ( work->field_802 == 75 && work->body.action != 11 )
        {
            GM_ConfigObjectAction( &work->body, 11, 0, 4 );
        }

        if ( work->field_802 == 122 && work->body.action != 11 )
        {
            GM_ConfigObjectAction( &work->body, 11, 0, 4 );
        }

        if ( work->field_802 > 38 )
        {
            if ( work->field_802 < 48 )
            {
                GM_PadVibration = 1;
                GM_PadVibration2 = work->field_802 + 70;
            }
            else if ( work->field_802 > 70 && work->field_802 < 112 )
            {
                GM_PadVibration = 1;
                GM_PadVibration2 = work->field_802 + 75;
            }
            else if ( work->field_802 > 132 )
            {
                GM_PadVibration = 1;
                GM_PadVibration2 = work->field_802 + 74;
            }
        }

        if ( ++work->field_802 > 179 )
        {
            s07b_800D7ED8( work, 34 );
            work->field_800++;
        }
        break;
    case 3:
        if ( s07b_800D2CB4( work->field_814[ 34 ] ) )
        {
            SetMode( work, s07b_800D8B8C );
        }
        break;
    }
}

void s07b_800D8B8C( Work *work, int time )
{
    if ( time == 0 )
    {
        s07b_800D7ED8( work, 35 );
    }

    if ( !( work->flag & 0x4 ) )
    {
        if ( work->body.is_end && work->body.action == 12 )
        {
            work->flag |= 0x4;
            work->m_ctrl.info1.field_14 = 0;
            work->m_ctrl.interp = 15;
        }
    }

    if ( time == 148 )
    {
        GCL_ExecProc( work->field_8B4[ 6 ], NULL );
    }

    if ( s07b_800D2C4C() )
    {
        CloseCinemaScreen();
        if ( work->blur ) GV_DestroyOtherActor( work->blur );
        GCL_ExecProc( work->field_8B4[ 0 ], NULL );
    }
}

void s07b_800D8C60( Work *work )
{
    int frame, se_id;

    frame = work->m_ctrl.info1.frame;
    se_id = 0;
    switch ( work->body.action )
    {
    case 8:
        if ( frame == 0 ) se_id = 195;
        if ( frame == 50 ) se_id = 196;
        break;
    case 11:
        if ( frame == 26 || frame == 66 || frame == 128 || frame == 158 ) se_id = 197;
        break;
    case 12:
        if ( frame == 37 ) se_id = 56;
        break;
    }
    if ( se_id != 0 ) GM_SeSetMode( &work->control.mov, se_id, GM_SEMODE_BOMB );
}

void s07b_800D8D20( Work *work )
{
    int ( *action )( Work *, int );
    int time;

    s07b_800D2A64();
    CheckCinemaTimeout();

    sna_act_helper2_helper2_80033054( work->control.name, &work->adjust[ 6 ] );

    action = work->action;
    time = work->time;
    if ( time < 16000 ) work->time++;

    if ( !CheckCutsceneSkip( work ) )
    {
        action( work, time );
        s07b_800D7F6C( work );
        s07b_800D8C60( work );
    }
}

static void Act( Work *work )
{
    int ang;

    GM_ActMotion( &work->body );
    GM_ActControl( &work->control );
    GM_ActObject( &work->body );
    DG_GetLightMatrix2( &work->control.mov, work->light );

    ang = GV_Time % 128;
    ang = rsin( ang * 32 ) - rsin( ( ang - 1 ) * 32 );
    work->control.mov.vy += ang * 80 / 4096;

    s07b_800D8D20( work );
}

static void Die( Work *work )
{
    if ( work->shadow != NULL ) GV_DestroyActor( work->shadow );
    GM_FreeControl( &work->control );
    GM_FreeObject( &work->body );
    GM_PlayerStatus &= ~PLAYER_PAD_OFF;
    GM_GameStatus &= ~STATE_PADMASK;
}

static void s07b_800D8EEC( Work *work )
{
    work->field_7E8 = 0;
    work->flag = 0;

    work->field_800 = work->field_802 = 0;
    work->field_804 = work->field_806 = 0;

    work->field_808 = DG_ZeroVector;

    work->field_7E2 = -1;
    work->field_7E0 = 0;
    work->field_7E4 = 0;

    SetMode( work, s07b_800D80B8 );
}

static void s07b_800D8F60( Work *work )
{
    int i;
    int *data;
    char *str;

    i = 0;
    data = work->field_814;

    if ( GCL_GetOption( 't' ) )
    {
        while ( ( str = GCL_NextStr() ) != NULL )
        {
            if ( i == 40 ) break;
            *data = GCL_StrToInt( str );
            data++;
            i++;
        }
    }
}

static void s07b_800D8FD4( Work *work )
{
    int i;
    int *data;
    char *str;

    if ( GCL_GetOption( 'f' ) )
    {
        i = 0;
        data = work->field_8B4;
        while ( ( str = GCL_NextStr() ) != NULL )
        {
            if ( i == 7 ) break;
            *data = GCL_StrToInt( str );
            data++;
            i++;
        }
    }
}

static void InitShadow( Work *work )
{
    SVECTOR indices;

    indices.vx = 0;
    indices.vy = 6;
    indices.vz = 12;
    indices.pad = 15;
    work->shadow = NewShadow( &work->control, &work->body, indices );
}

static int GetResources( Work *work, int name, int where )
{
    CONTROL *control;
    OBJECT  *body;
    u_short  motion;

    control = &work->control;
    if ( GM_InitControl( control, name, where ) < 0 ) return -1;

    GM_ConfigControlString( control, GCL_GetOption( 'p' ), GCL_GetOption( 'd' ) );
    GM_ConfigControlHazard( control, 750, -2, -2 );
    control->seg_flag = HZD_SEG_NO_NAVIGATE;
    GM_ConfigControlTrapCheck( control );

    body = &work->body;
    GM_InitObject( body, BODY_DATA, BODY_FLAG, BODY_DATA );
    GM_ConfigObjectJoint( body );

    if ( GCL_GetOption( 'o' ) )
    {
        motion = GCL_StrToInt( GCL_NextStr() );
    }
    else
    {
        motion = MOTION_DATA;
    }

    GM_ConfigMotionControl( body, &work->m_ctrl, motion, work->m_segs1, work->m_segs2, &work->control, work->rots );
    GM_ConfigObjectLight( body, work->light );
    GM_ConfigObjectAction( body, 0, 0, 0 );

    GM_ConfigMotionAdjust( &work->body, work->adjust );
    work->body.objs->light->t[ 0 ] = 0;
    work->body.objs->light->t[ 1 ] = 0;
    work->body.objs->light->t[ 2 ] = 0;

    InitShadow( work );
    s07b_800D8EEC( work );
    s07b_800D8FD4( work );
    s07b_800D8F60( work );

    GM_GameStatus |= ( STATE_PAUSE_ONLY | PLAYER_PAD_OFF | PLAYER_SECOND_AVAILABLE );
    GM_GameStatus &= ~STATE_PADRELEASE;

    GV_PadMask = ~PAD_START;
    GM_PlayerStatus |= PLAYER_PAD_OFF;
    GM_GameStatus |= STATE_PADMASK;

    /* unequip scope/camera */
    if ( GM_ItemTypes[ GM_Item + 1 ] & 0x2 )
    {
        GM_Item = IT_None;
    }

    /* unequip stinger/psg1 */
    if ( GM_WeaponTypes[ GM_Weapon + 1 ] & 0x200 )
    {
        GM_Weapon = WP_None;
    }

    if ( GM_Item == IT_NVG || GM_Item == IT_ThermG )
    {
        GM_Item = IT_None;
    }

    work->blur = NewBlurPure();
    return 0;
}

void *NewMemoryPsycho( int name, int where )
{
    Work *work;

    work = GV_NewActor( GV_ACTOR_AFTER, sizeof(Work) );
    if ( work == NULL ) return NULL;

    GV_SetNamedActor( work, Act, Die, "mempsy.c" );
    if ( GetResources( work, name, where ) < 0 )
    {
        GV_DestroyActor( work );
        return NULL;
    }
    return (void *)work;
}
