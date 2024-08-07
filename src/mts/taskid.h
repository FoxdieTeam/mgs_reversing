/*
 * ref."beatmania APPEND 5thMIX"
 *  work.5th/include/task_id.h (Apr.08,1998)
 *  work.5th/libfs/taskid.h (May.12,1998)
 */
#ifndef TASKID_H_INCLUDED
#define TASKID_H_INCLUDED
/*
   MTS TASK ID
*/

#define MTSID_SYSTEM            0
#define MTSID_SOUND_INT         1
#define MTSID_SOUND_SET         2
#define MTSID_GAME              3
#define MTSID_SOUND_DUMMY       4
#define MTSID_SOUND_MAIN        5

/* Apr.08,1998 */
#define MTSID_CD_READ           6
#define MTSID_MEMORY_CARD       7

/* May.12,1998 */
#define MTSID_CD_SYSTEM         6
#define MTSID_MEMCARD           8

#define MTSID_IDLE              (MTS_NR_TASK - 1)

#endif
