#include "Game/homing_target.h"

typedef struct _WatcherPad
{
    int   field_00;        //0x00       //0xB34
    int   press;           //0x04       //0xB38
    int   field_08;        //0x08       //0xB3C
    int   tmp;             //0x0A       //0xB40
    int   time;            //0x0C       //0xB44
    short dir;             //0x10       //0xB48
    short sound;           //0x12       //0xB4A
} WatcherPad;

typedef struct _WatcherWork
{
    GV_ACT       actor;
    CONTROL      control;                    //0x20
    OBJECT       body;                       //0x9C
    char         field_C0_padding[0x674];    //0xC0
    short        field_734;                  //0x734
    short        field_736;                  //0x736
    char         field_738[0x6C];            //0x738
    OBJECT       field_7A4;                  //0x7A4
    char         field_7C8_padding[0xC0];    //0x7C8
    MATRIX       field_888;                  //0x888
    int          field_8A8;                  //0x8A8
    int          field_8AC;                  //0x8AC
    int          field_8B0;                  //0x8B0
    int          field_8B4;                  //0x8B4
    int          field_8B8;                  //0x8B8
    int          field_8BC;                  //0x8BC
    int          field_8C0;                  //0x8C0
    int          field_8C4;                  //0x8C4
    int          field_8C8;                  //0x8C8
    int          field_8CC;                  //0x8CC
    int          field_8D0;                  //0x8D0
    int          field_8D4;                  //0x8D4
    int          field_8D8;                  //0x8D8
    int          field_8DC;                  //0x8DC
    short        field_8E0;
    short        field_8E2;
    short        field_8E4;
    short        field_8E6;
    char         field_8E8_padding[0x04];
    void*        field_8EC_func;
    void*        field_8F0_func;
    int          field_8F4;
    int          field_8F8;
    int          actend;                     //0x8FC
    TARGET      *target;                     //0x900
    char         field_904_padding[0x48];
    TARGET       field_94C;                  //0x94C
    char         field_994_padding[0x48];    //0x994
    Homing_Target *hom;                      //0x9DC
    short        scale;                      //0x9E0
    short        field_9E2;                  //0x9E2
    short        visible;                    //0x9E4
    short        field_9E6;                  //0x9E6
    int          field_9E8;                  //0x9E8
    SVECTOR      nodes[0x20];                //0x9EC
    int          field_AEC;                  //0xAEC
    char         field_AF0_padding[0x2C];    //0xAF0
    int          field_B1C;                  //0xB1C
    short        think1;                     //0xB20
    short        think2;                     //0xB22
    short        think3;                     //0xB24
    short        think4;                     //0xB26
    unsigned int count3;                     //0xB28
    int          t_count;                    //0xB2C
    int          l_count;                    //0xB30
    WatcherPad   pad;                        //0xB34
    short        field_B4C;                  //0xB4C
    short        field_B4E;                  //0xB4E
    unsigned int trigger;                    //0xB50
    GV_ACT*      subweapon;                  //0xB54
    int          field_B58;                  //0xB58
    int          field_B5C;                  //0xB5C
    int          next_node;                  //0xB60    //could be wrong
    int          search_flag;                //0xB64    //could be wrong
    GV_ACT      *field_B68;                  //0xB68
    int          mark_time;                  //0xB6C    //could be wrong
    int          act_status;                 //0xB70
    int          field_B74;                  //0xB74
    signed char  field_B78;                  //0xB78
    signed char  field_B79;                  //0xB79
    signed char  field_B7A;                  //0xB7A
    char         field_B7B;                  //0xB7B
    char         field_B7C;                  //0xB7C
    char         field_B7D;                  //0xB7D
    char         field_B7E;                  //0xB7E
    char         field_B7F;                  //0xB7F
    char         param_item;                 //0xB80  //param.item (should be struct)
    char         field_B81;                  //0xB81
    short        field_B82;                  //0xB82
    short        field_B84;                  //0xB84
    char         local_data;                 //0xB86
    char         local_data2;                //0xB87
    int          field_B88;                  //0xB88
    short        vision_facedir;             //0xB8C  //vision.facedir (should be struct)
    short        field_B8E;
    short        vision_length;              //0xB90
    short        field_B92;
    short        field_B94;
    short        field_B96;
    int          alert_level;                //0xB98
    signed char  modetime[4];                //0xB9C
    signed char  field_BA0;                  //0xBA0
    char         field_BA1;                  //0xBA1
    char         field_BA2;                  //0xBA2
    char         field_BA3;                  //0xBA3
    SVECTOR      field_BA4;                  //0xBA4
    char         field_BAC_padding[0x2C];    //0xBAC
    SVECTOR      start_pos;                  //0xBD8
    SVECTOR      target_pos;                 //0xBE0
    int          field_BE8;                  //0xBE8
    int          field_BEC;                  //0xBEC
    int          field_BF0;                  //0xBF0
    int          target_addr;                //0xBF4
    int          target_map;                 //0xBF8
    int          field_BFC;                  //0xBFC
    int          field_C00;                  //0xC00
    int          field_C04;                  //0xC04
    int          field_C08;                  //0xC08
    int          field_C0C;                  //0xC0C
    int          field_C10;                  //0xC10
    SVECTOR      field_C14;                  //0xC14
    int          field_C1C;                  //0xC1C
    int          field_C20;                  //0xC20
    int          field_C24;                  //0xC24
    int          sn_dir;                     //0xC28
    short        faseout;                    //0xC2C
    short        field_C2E;                  //0xC2E
    int          field_C30;                  //0xC30
    int          field_C34;                  //0xC34
    int          field_C38;                  //0xC38
    int          field_C3C;                  //0xC3C
    int          field_C40;                  //0xC40
    int          field_C44;                  //0xC44
    short        field_C48;                  //0xC48
    short        field_C4A;                  //0xC4A
} WatcherWork;