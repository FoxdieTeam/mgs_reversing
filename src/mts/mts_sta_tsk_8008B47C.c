#include "linker.h"
#include "mts_new.h"

extern const char aAssertionFaled[]; // = "assertion faled : %s line %d : Task %d\n";
extern const char aMtsStaTskServe[];
extern const char asc_80013E2C[]; // = "\n";
extern const char aMtsNewC[]; // = "\n";

void mts_send_8008982C(int dst, unsigned char *message);
int mts_receive_80089D24(int src, unsigned char *message);
void mts_print_process_status_8008B77C(void);

extern int gTaskIdx_800C0DB0;

// TODO: is mts_msg wrong ??
typedef struct mts_msg2
{
    int field_0;
    int field_4_task_idx;
    void (*field_8)(void);
    void* field_C;
    //void* field_10;
} mts_msg2;

int mts_sta_tsk_8008B47C(int tasknr, void (*proc)(void), void* stack_pointer)
{
    mts_msg2 msg;
    int src_idx;

    msg.field_4_task_idx = tasknr;
    msg.field_8 = proc;
    msg.field_0 = 0;
    msg.field_C = stack_pointer;
    mts_send_8008982C(0, (unsigned char *)&msg);
    src_idx = mts_receive_80089D24(0, (unsigned char *)&msg);
    if ( src_idx )
    {
        mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, 1344, gTaskIdx_800C0DB0);
        mts_printf_8008BBA0(aMtsStaTskServe, src_idx);
        mts_printf_8008BBA0(asc_80013E2C);
        mts_print_process_status_8008B77C();
    }
    return msg.field_0;
}