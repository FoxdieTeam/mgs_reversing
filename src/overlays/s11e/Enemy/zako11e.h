#include "Game/game.h"
#include "Game/object.h"
#include "Game/camera.h"
#include "Weapon/weapon.h"
#include "Game/homing_target.h"

typedef struct _WatcherPad
{
    int   press;           //0x04       //0xB38
    int   mode;            //0x08       //0xB3C
    int   tmp;             //0x0A       //0xB40
    int   time;            //0x0C       //0xB44
    short dir;             //0x10       //0xB48
    short sound;           //0x12       //0xB4A
} WatcherPad;

typedef struct _WatcherUnk
{
    int   field_00;    //0x00        //0x8C8
    short field_04;    //0x04        //0x8CC
    short field_06;    //0x06        //0x8CE
    int   field_08;    //0x08        //0x8D0
    int   field_0C;    //0x0C        //0x8D4
    int   field_10;    //0x10        //0x8D8
    int   field_14;    //0x14        //0x8DC
    short field_18;    //0x18        //0x8E0
    short field_1A;    //0x1A        //0x8E2
    short field_1C;    //0x1C        //0x8E4
    short field_1E;    //0x1E        //0x8E6
    short field_20;    //0x20        //0x8E8
    short field_22;    //0x22        //0x8EA
} WatcherUnk;

typedef struct _VISION
{
    short          facedir;                    //0xB8C
    short          field_B8E;                  //0xB8A
    short          length;                     //0xB90
    short          field_B92;                  //0xB92
} VISION;

typedef struct _PARAM
{
    signed char    field_B78;                  //0xB78
    signed char    blood;                      //0xB79
    signed char    area;                       //0xB7A 
    signed char    field_B7B;                  //0xB7B
    char           field_B7C;                  //0xB7C
    signed char    root;                       //0xB7D
    char           c_root;                     //0xB7E
    char           field_B7F;                  //0xB7F
    signed char    item;                       //0xB80
    char           field_B81;                  //0xB81
    short          life;                       //0xB82
    short          faint;                      //0xB84
    char           local_data;                 //0xB86
    char           local_data2;                //0xB87
} PARAM;

typedef struct _ZakoWork
{
    GV_ACT         actor;
    CONTROL        control;                    //0x20
    OBJECT         body;                       //0x9C
    int            field_180;                  //0x180
    void          *kmd;                        //0x184
    DG_DEF        *def;                        //0x188
    MOTION_CONTROL m_ctrl;                     //0x18C
    OAR_RECORD     field_1DC[34];              //0x1DC
    SVECTOR        rots[16];                   //0x6A4
    SVECTOR        field_724;                  //0x724
    int            field_72C;                  //0x72C
    int            field_730;                  //0x730
    short          field_734;                  //0x734
    short          field_736;                  //0x736
    char           field_738[0x1C];            //0x738
    short          field_754;                  //0x754
    short          field_756;                  //0x756
    short          field_758;                  //0x756
    short          field_75A;                  //0x756
    short          field_75C;                  //0x75C
    short          field_75E;                  //0x75C
    char           field_760[0x44];            //0x760
    OBJECT         field_7A4;                  //0x7A4
    MATRIX         field_888;                  //0x888
    int            field_8A8;                  //0x8A8
    int            field_8AC;                  //0x8AC
    int            field_8B0;                  //0x8B0
    int            field_8B4;                  //0x8B4
    int            field_8B8;                  //0x8B8
    int            field_8BC;                  //0x8BC
    int            field_8C0;                  //0x8C0
    int            field_8C4;                  //0x8C4
    int            field_8C8;                  //0x8C8
    int            field_8CC;                  //0x8CC
    int            field_8D0;                  //0x8D0
    SVECTOR        field_8D4;                  //0x8D4
    int            field_8DC;                  //0x8DC
    short          field_8E0;                  //0x8E0
    short          field_8E2;                  //0x8E2
    short          field_8E4;                  //0x8E4
    short          field_8E6;                  //0x8E6
    int            field_8E8;                  //0x8E8
    void*          action;                     //0x8EC
    void*          action2;                    //0x8F0
    int            time;                       //0x8F4
    int            time2;                      //0x8F8
    int            actend;                     //0x8FC
    TARGET        *target;                     //0x900
    TARGET         field_904;                  //0x904
    TARGET         field_94C;                  //0x94C
    TARGET         punch;                      //0x994
    HOMING        *hom;                        //0x9DC
    short          scale;                      //0x9E0
    short          field_9E2;                  //0x9E2
    int            visible;                    //0x9E4
    int            field_9E8;                  //0x9E8
    SVECTOR        nodes[0x20];                //0x9EC
    int            search_flag;                //0xAEC
    GV_ACT*        field_AF0;                  //0xAF0
    int           *field_AF4;                  //0xAF4
    GV_ACT*        field_AF8;                  //0xAF8
    int           *field_AFC;                  //0xAFC
    void          *field_B00[8];               //0xB00
    short          think1;                     //0xB20
    short          think2;                     //0xB22
    short          think3;                     //0xB24
    short          think4;                     //0xB26
    unsigned int   count3;                     //0xB28
    int            t_count;                    //0xB2C
    int            l_count;                    //0xB30
    int            next_node;                  //0xB34
    WatcherPad     pad;                        //0xB38
    short          field_B4C;                  //0xB4C
    short          field_B4E;                  //0xB4E
    unsigned int   trigger;                    //0xB50
    GV_ACT*        subweapon;                  //0xB54
    short          field_B58;                  //0xB58
    short          field_B5A;                  //0xB5A
    short          field_B5C;                  //0xB5C
    short          field_B5E;                  //0xB5E
    int            field_B60;                  //0xB60
    int            field_B64;                  //0xB64
    GV_ACT        *field_B68;                  //0xB68
    int            mark_time;                  //0xB6C    //could be wrong
    int            act_status;                 //0xB70
    //int            field_B74;                  //0xB74
    signed char    field_B78;                  //0xB78
    signed char    param_blood;                //0xB79  //param.blood (should be struct)
    signed char    param_area;                 //0xB7A  //param.area  (should be struct)
    signed char    field_B7B;                  //0xB7B
    char           field_B7C;                  //0xB7C
    signed char    root;                       //0xB7D  //used as node index
    char           c_root;                     //0xB7E
    char           field_B7F;                  //0xB7F
    signed char    param_item;                 //0xB80  //param.item  (should be struct)
    char           field_B81;                  //0xB81
    short          param_life;                 //0xB82  //param.life  (should be struct)
    short          param_faint;                //0xB84  //param.faint (should be struct)
    char           local_data;                 //0xB86
    char           local_data2;                //0xB87
    int            field_B88;                  //0xB88
    VISION         vision;                     //0xB8C
    short          field_B94;                  //0xB94
    short          field_B96;                  //0xB96
    int            alert_level;                //0xB98
    signed char    modetime[4];                //0xB9C
    signed char    field_BA0;                  //0xBA0
    char           field_BA1;                  //0xBA1
    char           field_BA2;                  //0xBA2
    char           field_BA3;                  //0xBA3
    SVECTOR        field_BA4;                  //0xBA4
    int            field_BAC;                  //0xBAC
    int            field_BB0[8];               //0xBB0 //set_time
    short          field_BD0[4];               //0xBD0 //set_dir, might be svector
    SVECTOR        start_pos;                  //0xBD8
    SVECTOR        target_pos;                 //0xBE0
    int            start_addr;                 //0xBE8
    int            start_map;                  //0xBEC
    int            field_BF0;                  //0xBF0
    int            target_addr;                //0xBF4
    int            target_map;                 //0xBF8
    int            field_BFC;                  //0xBFC
    int            field_C00;                  //0xC00
    int            field_C04;                  //0xC04
    int            field_C08;                  //0xC08
    int            field_C0C;                  //0xC0C
    int            field_C10;                  //0xC10
    SVECTOR        field_C14;                  //0xC14
    int            field_C1C;                  //0xC1C
    int            field_C20;                  //0xC20
    int            sn_dis;                     //0xC24
    int            sn_dir;                     //0xC28
    short          faseout;                    //0xC2C
    short          field_C2E;                  //0xC2E
    int            field_C30;                  //0xC30
    char           field_C34;                  //0xC34 //num_set_time
    char           field_C35[7];               //0xC35 //set_time
    int            field_C3C;                  //0xC3C
    int            field_C40;                  //0xC40
    int            field_C44;                  //0xC44
    short          field_C48;                  //0xC48
    short          field_C4A;                  //0xC4A
    int            field_C4C;                  //0xC4C
} ZakoWork;

//zako11e.c
#define EN_FASEOUT 0x10000000
//put.c
#define PUTBREATH 1
#define BW_MARK 4