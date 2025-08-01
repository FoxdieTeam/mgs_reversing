#include "memcard.h"

#include <stdio.h>
#include <sys/file.h>
#include <kernel.h>
#include <libapi.h>
#include "psxdefs.h"

#include "common.h"
#include "mts/mts.h"

STATIC int memcard_initialized = FALSE;

extern long             gHardware_end_io;
extern long             gHardware_end_write;
extern long             gHardware_timeout;
extern long             gHardware_new_device;
extern long             gSoftware_end_io;
extern long             gSoftware_end_write;
extern long             gSoftware_timeout;
extern long             gSoftware_new_device;
extern TMemCardFunc     gHwCard_do_op;
extern TMemCardFunc     gSwCard_do_op;
extern volatile int     gSwCardLastOp;
extern volatile int     gHwCardLastOp;
extern MEM_CARD         gMemCards[2];
extern volatile long    gMemCard_io_size;

static void memcard_hwcard_do_op(int op);
static void memcard_swcard_do_op(int op);
static int memcard_dummy(int state);

static inline void memcard_access_wait(void)
{
    printf("[R]");

    while ((gHwCard_do_op != memcard_hwcard_do_op) ||
           (gSwCard_do_op != memcard_swcard_do_op))
    {
        printf("ACCESS WAIT..\n");
        mts_wait_vbl(2);
    }

    gHwCardLastOp = 0;
    gSwCardLastOp = 0;
}

static void memcard_hwcard_do_op(int op)
{
    gHwCardLastOp = op;
}

static void memcard_swcard_do_op(int op)
{
    gSwCardLastOp = op;
}

static void memcard_hwcard_end_io()
{
    gHwCard_do_op(1);
}

static void memcard_hwcard_end_write()
{
    printf("*** hw card error\n");
    gHwCard_do_op(2);
}

static void memcard_hwcard_timeout()
{
    printf("[C.H.T.O]");
    gHwCard_do_op(3);
}

static void memcard_hwcard_new()
{
    printf("*** hw card new\n");
    gHwCard_do_op(4);
}

static void memcard_swcard_end_io()
{
    gSwCard_do_op(1);
}

static void memcard_swcard_end_write()
{
    printf("*** sw card error\n");
    gSwCard_do_op(2);
}

static void memcard_swcard_timeout()
{
    printf("[C.S.T.O]");
    gSwCard_do_op(3);
}

static void memcard_swcard_new()
{
    printf("*** sw card new\n");
    gSwCard_do_op(4);
}

static void memcard_set_sw_hw_card_fns(void)
{
    gHwCard_do_op = memcard_hwcard_do_op;
    gSwCard_do_op = memcard_swcard_do_op;
}

/**
 * @brief Determines whether the memory card in the specified port is formatted.
 *
 * This function reads the first sector of the first block from the specified
 * memory card. If the first two bytes are 'M' and 'C', then the card is deemed
 * formatted, unformatted otherwise.
 *
 * @param port The port to check: 0 for port 1, 1 for port 2.
 *
 * @bug When passing 1 as argument, the function does not check port 2, but tries
 * to access port B of MultiTap on port 1 instead, which results in an error.
 *
 * @return
 * - 1 if the memory card is formatted.
 * - 5 if the memory card is unformatted.
 * - 2 if an error occurred.
 */
static int memcard_easy_format_test(int port)
{
    char buffer[128];

    printf("easy_format_test\n");
    memset(buffer, 0, sizeof(buffer));

    memcard_access_wait();

    // BUG: the first parameter is the channel, not the port, so the correct
    // value to pass is port * 16 + cardIndex. Therefore the function works
    // correctly when port is 0, but when port is 1, it tries to access
    // port B of MultiTap on port 1, which results in an error.
    // However, this function is probably never executed by the game.
    // See also the comment in memcard_init().
    _card_read(port, 0, buffer);

    do {
        mts_wait_vbl(1);
    } while (!gHwCardLastOp);

    if (gHwCardLastOp != 1)
    {
        printf("card_error\n");
        return 2;
    }
    else
    {
        if (buffer[0] == 'M' && buffer[1] == 'C')
        {
            printf("card_normal\n");
            return 1;
        }
        else
        {
            printf("card_unformat\n");
            return 5;
        }
    }
}

/**
 * Gets information about all the files contained in a memory card.
 *
 * For each file in the memory card, this function fills
 * gMemCards[port].files[i] fields by setting the file name
 * and size, and MEM_CARD_FILE::field_14 to 0 (unknown meaning).
 *
 * @param port The memory card port: 0 for port 1, 1 for port 2.
 * @param pUsedBlocksCount When the function returns, contains the number of
 * blocks that are in use in the memory card.
 *
 * @return The number of files contained in the memory card.
 */
static int memcard_loaddir(int port, int *pUsedBlocksCount)
{
    struct DIRENTRY dir;
    char name[32];
    int files;
    int blocks;

    blocks = 0;

    sprintf(name, "bu%02X:*", port * 16);
    printf("load_dir %s start\n", name);

    if (firstfile(name, &dir))
    {
        files = 0;

        do {
            memcpy(gMemCards[port].files[files].name, dir.name, sizeof(dir.name));
            gMemCards[port].files[files].field_14 = 0;
            gMemCards[port].files[files].field_18_size = dir.size;
            blocks += (dir.size + 8191) / MC_BLOCK_SIZE;
            files++;
        }
        while (nextfile(&dir));

        printf("TOTAL %d FILES used %d block\n", files, blocks);
        *pUsedBlocksCount = blocks;
        return files;
    }

    printf("NO FILE\n");
    *pUsedBlocksCount = 0;
    return 0;
}

/**
 * Helper function for memcard_get_files().
 *
 * This function fills all gMemCards[port] fields by setting the card
 * index, the number of files contained in the card, the number of free blocks,
 * and MEM_CARD::last_op to 1 (unknown meaning). It then calls
 * memcard_loaddir() to fill the array MEM_CARD::files.
 *
 * @param port The memory card port: 0 for port 1, 1 for port 2.
 */
static void memcard_load_files(int port)
{
    int pUsedBlocksCount;
    gMemCards[port].card_idx = port;
    gMemCards[port].last_op = 1;
    gMemCards[port].file_count = memcard_loaddir(port, &pUsedBlocksCount);
    gMemCards[port].free_blocks = 15 - pUsedBlocksCount;
}

// Pure function whose return value is never used
// (as of the current decompilation status).
static int memcard_dummy(int state)
{
    switch (state)
    {
    case 1:
        return 0;
    case 4:
        return 0x01000000;
    case 2:
        return 0xc0000002;
    case 3:
        return 0xc0000003;
    default:
        return 0x80000000;
    }
}

void memcard_reset_status(void)
{
    gMemCards[0].last_op = 2;
    gMemCards[1].last_op = 2;
}

int memcard_check(int port)
{
    int chan;
    int retries;
    int sw_card_op;
    int hw_card_op;

    chan = port * 16;
    retries = 0;

    if ((gMemCards[port].last_op == 5) || (gMemCards[port].last_op == 2))
    {
        goto loop_24;
    }

    while (1)
    {
        memcard_access_wait();
        _card_info(chan);

        if ((retries++) > 10)
        {
            printf("MEMCARD:RETRY OVER!!\n");
            return 0x80000002;
        }

        // FIXME: why does THIS need a goto while the others need a do while?
    retry1:
        mts_wait_vbl(1);

        if ((sw_card_op = !gSwCardLastOp))
            goto retry1;

        sw_card_op = gSwCardLastOp;
        switch (sw_card_op)
        {
            case 1:
                if (gMemCards[port].last_op == 5)
                {
                    return 0x80000001;
                }

                if (gMemCards[port].last_op == 4)
                {
                    goto exit;
                }

                sw_card_op = 1;
                gMemCards[port].last_op = sw_card_op;
                return 0;

            case 2:

            case 3:
                gMemCards[port].last_op = sw_card_op;
                memcard_retry(port);
                return;

            case 4:
                break;

            default:
                return; // FIXME: Return without value in function that returns long???
        }

    loop_24:
        memcard_access_wait();
        _card_clear(chan);

        do {
            mts_wait_vbl(1);
        } while ((hw_card_op = !gHwCardLastOp));
        hw_card_op = gHwCardLastOp;

        if (hw_card_op == 1)
        {
            gMemCards[port].last_op = 4;

            memcard_access_wait();
            _card_load(chan);

            do {
                mts_wait_vbl(1);
            } while ((sw_card_op = !gSwCardLastOp));

            sw_card_op = gSwCardLastOp;

            if (sw_card_op == 4)
            {
                gMemCards[port].last_op = 5;

                {
                    register int ret asm("v0");
                    ret = 0x80000000;
                    asm("" :: "r"(ret));
                }

                return 0x80000001; // or "return ret | 1;" (with ret variable outside block)
            }

            if (sw_card_op == 1)
            {
                gMemCards[port].last_op = 4;
                break;
            }

            printf("RETRY(new)\n");
        }
        else
        {
            printf("RETRY\n");
        }
    }

exit:
    return 0x1000000;
}

void memcard_init(void)
{
    int port;

    if (!memcard_initialized)
    {
        memcard_initialized = !memcard_initialized;
        gHwCardLastOp = 1;

        gSwCardLastOp = 1;
        memcard_set_sw_hw_card_fns();

        EnterCriticalSection();

        gHardware_end_io = OpenEvent(HwCARD, EvSpIOE, EvMdINTR, (openevent_cb_t)memcard_hwcard_end_io);
        gHardware_end_write = OpenEvent(HwCARD, EvSpERROR, EvMdINTR, (openevent_cb_t)memcard_hwcard_end_write);
        gHardware_timeout = OpenEvent(HwCARD, EvSpTIMOUT, EvMdINTR, (openevent_cb_t)memcard_hwcard_timeout);
        gHardware_new_device = OpenEvent(HwCARD, EvSpNEW, EvMdINTR, (openevent_cb_t)memcard_hwcard_new);

        gSoftware_end_io = OpenEvent(SwCARD, EvSpIOE, EvMdINTR, (openevent_cb_t)memcard_swcard_end_io);
        gSoftware_end_write = OpenEvent(SwCARD, EvSpERROR, EvMdINTR, (openevent_cb_t)memcard_swcard_end_write);
        gSoftware_timeout = OpenEvent(SwCARD, EvSpTIMOUT, EvMdINTR, (openevent_cb_t)memcard_swcard_timeout);
        gSoftware_new_device = OpenEvent(SwCARD, EvSpNEW, EvMdINTR, (openevent_cb_t)memcard_swcard_new);

        EnableEvent(gHardware_end_io);
        EnableEvent(gHardware_end_write);
        EnableEvent(gHardware_timeout);
        EnableEvent(gHardware_new_device);

        EnableEvent(gSoftware_end_io);
        EnableEvent(gSoftware_end_write);
        EnableEvent(gSoftware_timeout);
        EnableEvent(gSoftware_new_device);

        ExitCriticalSection();

        port = 0;

        InitCARD(0);
        StartCARD();
        _bu_init();
        mts_set_vsync_task();
        memcard_reset_status();

        for (port = 0; port < 2; port++)
        {
            if (!memcard_check(port))
            {
                // I couldn't make the game enter this path without forcing it,
                // but I think it is never executed because the function below
                // is bugged with regard to port 2.
                long memCardType = memcard_easy_format_test(port);
                if (memCardType == 5) // Unformatted card.
                {
                    gMemCards[port].last_op = 5;
                }
                else if (memCardType == 1) // Formatted card.
                {
                    gMemCards[port].last_op = 1;
                }
                else // Error.
                {
                    gMemCards[port].last_op = 2;
                }
            }
            else
            {
                gMemCards[port].last_op = 5;
            }
        }
    }
}

void memcard_exit(void)
{
    StopCARD();
    EnterCriticalSection();
    CloseEvent(gHardware_end_io);
    CloseEvent(gHardware_end_write);
    CloseEvent(gHardware_timeout);
    CloseEvent(gHardware_new_device);
    CloseEvent(gSoftware_end_io);
    CloseEvent(gSoftware_end_write);
    CloseEvent(gSoftware_timeout);
    CloseEvent(gSoftware_new_device);
    ExitCriticalSection();
    memcard_initialized = FALSE;
}

void memcard_retry(int port)
{
    int op;
    int count;
    int i;

    switch (gMemCards[port].last_op)
    {
    case 1:
    case 4:
        // Dead code path.
        op = gMemCards[port].last_op;
        memcard_dummy(op);
        return;

    case 3:
        count = 1;
        break;

    case 2:
        count = 20;
        break;
    }

    for (i = 0; i < count; i++)
    {
        memcard_access_wait();
        _card_info(port * 16);

        do {
            mts_wait_vbl(1);
        }
        while (!gSwCardLastOp);

        op = gSwCardLastOp;

        if (op == 1 || op == 4)
        {
            break;
        }

        mts_wait_vbl(3);
    }

    memcard_dummy(op);
}

/**
 * Gets the number of files, their name and size, and the number of free blocks
 * for the memory card in the specified port.
 *
 * This function calls other internal functions to fill all
 * gMemCards[port] fields, but only if such card is in a suitable
 * status to perform the operation, i.e., if its last_op
 * is 1 or 4 (unknown meaning).
 *
 * @param port The memory card port: 0 for port 1, 1 for port 2.
 *
 * @return A pointer to gMemCards[port] containing the requested
 * information if the operation was performed, otherwise 0.
 */
MEM_CARD *memcard_get_files(int port)
{
    MEM_CARD *pCardBase = gMemCards;
    MEM_CARD *pCard = &pCardBase[port];

    if (pCard->last_op == 1 || pCard->last_op == 4)
    {
        memcard_load_files(port);
        pCard->last_op = 1;
        return pCard;
    }
    return 0;
}

/**
 * Tries to delete the specified file from the memory card in the specified port.
 *
 * @param port The memory card port: 0 for port 1, 1 for port 2.
 * @param filename The name of the file to delete.
 *
 * @return 1 if the file was deleted, 0 otherwise.
 */
int memcard_delete(int port, const char *filename)
{
    char tmp[32];

    MEM_CARD *pCardBase = gMemCards;
    MEM_CARD *pCard = &pCardBase[port];

    if (pCard->last_op == 1)
    {
        sprintf(tmp, "bu%02X:%s", 16 * port, filename);
        if (erase(tmp))
        {
            printf("Deleted File %s", filename);
            return 1;
        }
        printf("ERROR : can't delete %s\n", filename);
    }
    return 0;
}

static void memcard_hwcard_read_write_handler(int op)
{
    if (op == 1)
    {
        gMemCard_io_size -= 128;
        if (!gMemCard_io_size)
        {
            gHwCard_do_op = memcard_hwcard_do_op;
        }
    }
    else
    {
        gMemCard_io_size = -1;
        memcard_set_sw_hw_card_fns();
    }
}

static void memcard_swcard_read_write_handler(int op)
{
    if (op == 1)
    {
        printf("MEMCARD READ/WRITE end\n");
    }
    else
    {
        printf("ERROR : MEMCARD READ/WRITE\n");
    }
    gSwCard_do_op = (TMemCardFunc)memcard_swcard_do_op;
}

static void memcard_set_read_write(int fileSize)
{
    gHwCard_do_op = memcard_hwcard_read_write_handler;
    gSwCard_do_op = memcard_swcard_read_write_handler;
    gMemCard_io_size = fileSize;
}

#define ROUND_UP(val,rounding) (((val) + (rounding) - 1) / (rounding) * (rounding))

void memcard_write(int port, const char *filename, int offset, char *buffer, int size)
{
    int blocks = ROUND_UP(size, MC_BLOCK_SIZE) / MC_BLOCK_SIZE;
    int fd;
    char name[32];

    sprintf(name, "bu%02X:%s", port * 16, filename);

    fd = open(name, (blocks << 16) | O_CREAT);
    if (fd < 0)
    {
        printf("Warning : MEMCARD create error ... overwrite\n");
    }
    close(fd);

    fd = open(name, O_NOWAIT | O_WRONLY);
    if (fd < 0)
    {
        printf("MEMCARD WRITE ERROR FD %d\n", fd);
        gMemCard_io_size = -1;
        return;
    }

    printf("MEMCARD WRITE %s FD %d SIZE %d\n", filename, fd, size);
    size = ROUND_UP(size, 128);
    if (offset > 0)
    {
        lseek(fd, offset, SEEK_SET);
    }
    memcard_set_read_write(size);
    write(fd, buffer, size);
    close(fd);
    printf("WRITING FILE %s...\n", filename);
}

void memcard_read(int port, const char *filename, int offset, char *buffer, int size)
{
    char name[32];
    int fd;

    sprintf(name, "bu%02x:%s", port * 16, filename);
    fd = open(name, FREAD | FASYNC);
    if (fd < 0)
    {
        printf("MEMCARD READ ERROR FD %d\n", fd);
        gMemCard_io_size = -1;
        return;
    }
    size = ROUND_UP(size, 128);
    printf("MEMCARD READ %s FD %d SIZE %d\n", filename, fd, size);
    if (offset > 0)
    {
        lseek(fd, offset, SEEK_SET);
    }
    memcard_set_read_write(size);
    read(fd, buffer, size);
    close(fd);
    printf("READING FILE %s...\n", filename);
}

int memcard_get_status(void)
{
    return gMemCard_io_size;
}

/**
 * Tries to format the memory card in the specified port.
 *
 * @param       port    The memory card port: 0 for port 1, 1 for port 2.
 *
 * @retval      1       memory card was formatted.
 * @retval      0       memory card was not formatted.
 */
int memcard_format(int port)
{
    int  retries;
    char cardPath[32];

    retries = 4;
    sprintf(cardPath, "bu%02x:", port * 16);

    if (gMemCards[port].last_op == 5)
    {
    retry:
        if (format(cardPath) != 0)
        {
            printf("FORMATED %d\n", port);
            gMemCards[port].last_op = 1;
            return 1;
        }
        retries--;
        if (retries <= 0)
        {
            printf("ERROR : MEMCARD FORMAT\n");
            return 0;
        }
        goto retry; // TODO: find a match without goto
    }

    printf("ERROR : MEMCARD FORMATED CARD\n");
    return 0;
}
