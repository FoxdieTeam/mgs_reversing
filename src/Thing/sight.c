#include "sight.h"
#include "libgv/libgv.h"
#include "Menu/menuman.h"

// used for all first person HUDs

extern int dword_8009F608;

void sight_act_helper_8007111C(void)
{
    int     message_result;
    GV_MSG *message;

    message_result = GV_ReceiveMessage_80016620(0x30da, &message);

    if (message_result > 0)
    {
        while (--message_result >= 0)
        {
            switch (message->message[0])
            {
            case 0xe4e:
                dword_8009F608 &= ~1;
                break;
            case 0xc927:
                dword_8009F608 |= 1;
                break;
            }

            message++;
        }
    }
}

#pragma INCLUDE_ASM("asm/Thing/sight_800711C0.s")            // 352 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_act_helper_80071320.s") // 220 bytes
#pragma INCLUDE_ASM("asm/Thing/sight_act_helper_800713FC.s") // 156 bytes

extern const char aStringFormat[];

void sight_act_helper_80071498(SightTextPseudoPrim *param_1, int param_2, int param_3, int param_4)
{
    menu_Text_XY_Flags_80038B34(param_1->field_8_posX, param_1->field_A_posY, 0);
    menu_Color_80038B4C(param_1->field_4_r, param_1->field_5_g, param_1->field_6_b);
    menu_Text_80038C38(aStringFormat, param_1->field_C_text);
}

#pragma INCLUDE_ASM("asm/Thing/sight_act_800714EC.s") // 1244 bytes

extern int dword_8009F600;
extern int dword_8009F604;
extern int dword_8009F608;

void sight_kill_800719C8(Actor_Sight *sight)
{
    if (sight->field_38_primitiveBuffer)
    {
        GV_DelayedFree_80016254(sight->field_38_primitiveBuffer);
    }

    if (sight->field_44_tPageBuffer)
    {
        GV_DelayedFree_80016254(sight->field_44_tPageBuffer);
    }

    if ((0 < dword_8009F600) && (--dword_8009F600 == 0))
    {
        dword_8009F604 = -1;
    }

    dword_8009F608 &= ~1;
}

extern int GV_Clock_800AB920;

int sight_loader_80071A54(Actor_Sight *sight, int hashedFileName, short *itemEquippedIndicator, short itemId,
                          short *xyOffsetBuffer)
{
    // Primitive buffer info.
    int                       cacheId;
    SightPrimitiveBufferInfo *info;
    int                       primitiveBufferSize;
    SightPrimBufInfoStruct   *ancillaryInfo;

    // Primitive buffer pointers.
    unsigned int *primitiveBuffer;      // Our entire allocated space for the double buffers.
    unsigned int *firstPrimitiveBuffer; // The first of our double buffers.
    unsigned int *firstPrimitiveBufferCopy;
    unsigned int *targetBuffer; // The copy target (we iterate over both buffers).
    unsigned int *originBuffer; // The original primitive buffer which copy into both of our double buffers.

    // Iterators/counters.
    int i;
    int a; // @todo: name this properly once SightPrimitiveBufferInfo's field_3 is understood.

    // Primitive iteration and access.
    unsigned int   code;
    unsigned int  *currentPrimitive;
    unsigned short offset;
    unsigned int   tag;

    // TPage information.
    int       tPageCount;
    DR_TPAGE *tPageMem;

    // Other.
    unsigned int   flags;
    unsigned char *field_C; // @todo: document these 3 fields.
    unsigned char *field_10;
    unsigned char  unkBool;

    flags = sight->field_54_maybeFlags;
    cacheId = GV_CacheID_800152DC(hashedFileName, 's');
    info = (SightPrimitiveBufferInfo *)GV_GetCache_8001538C(cacheId);
    sight->field_34_primitiveBufferInfo = info;

    if (!info)
    {
        return -1;
    }

    ancillaryInfo = info->field_4_ancillaryInfo;
    primitiveBufferSize = info->field_0_primitiveBufferSize;
    a = info->field_3;
    field_C = info->field_C;
    tPageCount = 0;
    field_10 = info->field_10;
    primitiveBuffer = (unsigned int *)GV_Malloc_8001620C(primitiveBufferSize * 2);
    sight->field_38_primitiveBuffer = primitiveBuffer;

    if (!primitiveBuffer)
    {
        return -1;
    }

    if (primitiveBuffer)
    {
        sight->field_3C_primitiveBuffer = (unsigned int *)(((char *)primitiveBuffer) + primitiveBufferSize);
        originBuffer = sight->field_34_primitiveBufferInfo->field_8_primitiveBuffer;
        targetBuffer = primitiveBuffer;
        firstPrimitiveBuffer = targetBuffer;
        firstPrimitiveBufferCopy = firstPrimitiveBuffer;
        for (i = 0; i < (primitiveBufferSize / 4); i++)
        {
            *(targetBuffer++) = *(originBuffer++);
        }

        while ((--a) >= 0)
        {
            offset = ancillaryInfo->field_2;
            currentPrimitive = (unsigned int *)(((char *)firstPrimitiveBufferCopy) + offset);
            tag = *currentPrimitive;

            if (tag != 0xff)
            {
                *(((char *)currentPrimitive) + 3) = tag;
            }

            if ((flags & 2) == 0)
            {
                unkBool = ancillaryInfo->field_0;

                if (unkBool != 0)
                {
                    sight_800711C0(sight, -1, (SightTextPseudoPrim *)currentPrimitive, ancillaryInfo->field_0, field_C,
                                   field_10, 0, 0);
                }
            }

            code = *(((unsigned char *)currentPrimitive) + 7);

            if ((code & 2) != 0)
            {
                tPageCount++;
            }

            ancillaryInfo++;
        }

        firstPrimitiveBuffer = primitiveBuffer;
        targetBuffer = (unsigned int *)(((char *)firstPrimitiveBuffer) + primitiveBufferSize);
        for (i = 0; i < (primitiveBufferSize / 4); i++)
        {
            *(targetBuffer++) = *(firstPrimitiveBuffer++);
        }

        if ((flags & 2) != 0)
        {
            sight->field_2C_frameCount = (sight->field_34_primitiveBufferInfo->field_2) + 2;
        }

        else
        {
            sight->field_2C_frameCount = 0;
        }

        sight->field_30 = (flags >> 1) & 1;
        sight->field_20_itemId = itemId ^ 0;
        sight->field_24_itemEquippedIndicator = itemEquippedIndicator;

        if (tPageCount == 0)
        {
            sight->field_44_tPageBuffer = (DR_TPAGE *)0x0;
            sight->field_48_tPageBuffer = (DR_TPAGE *)0x0;
        }

        else
        {
            tPageMem = (DR_TPAGE *)GV_Malloc_8001620C((tPageCount * 2) * (sizeof(DR_TPAGE)));

            if (tPageMem == ((DR_TPAGE *)0x0))
            {
                return -1;
            }

            sight->field_44_tPageBuffer = tPageMem;
            sight->field_48_tPageBuffer = tPageMem + tPageCount;
        }

        sight->field_40 = tPageCount;
        sight->field_4C_xyOffsetBuffer = xyOffsetBuffer;
        sight->field_50 = 0;
        sight->field_54_maybeFlags = 0;
        sight->field_58_clock = GV_Clock_800AB920;
        sight->field_5A_maybeFlags = 0;
        return 0;
    }
}

extern const char aSightC[];

Actor_Sight *NewSight_80071CDC(int hashedFileName0, int hashedFileName1, short *itemEquippedIndicator, short itemId,
                               short *xyOffsetBuffer)
{
    Actor_Sight *sight = (Actor_Sight *)0x0;

    if (dword_8009F604 != -1 && dword_8009F604 != hashedFileName1)
    {
        return sight;
    }

    sight = (Actor_Sight *)GV_NewActor_800150E4(7, 0x5c);
    if (sight)
    {
        GV_SetNamedActor_8001514C((Actor *)sight, (TActorFunction)sight_act_800714EC,
                                  (TActorFunction)sight_kill_800719C8, aSightC);
        sight->field_54_maybeFlags = 0;

        if (sight_loader_80071A54(sight, hashedFileName0, itemEquippedIndicator, itemId, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor_800151C8((Actor *)sight);
            return 0;
        }

        dword_8009F600++;
        dword_8009F604 = hashedFileName1;
    }

    return sight;
}

extern short word_8009F5FC;

Actor_Sight *sight_init_80071DC8(int hashedFileName, short *xyOffsetBuffer)
{
    Actor_Sight *sight = (Actor_Sight *)0x0;

    if (dword_8009F604 != -1 && dword_8009F604 != hashedFileName)
    {
        return sight;
    }

    sight = (Actor_Sight *)GV_NewActor_800150E4(7, 0x5c);
    if (sight)
    {
        GV_SetNamedActor_8001514C((Actor *)sight, (TActorFunction)sight_act_800714EC,
                                  (TActorFunction)sight_kill_800719C8, aSightC);
        sight->field_54_maybeFlags = 0;

        if (sight_loader_80071A54(sight, hashedFileName, &word_8009F5FC, 1, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor_800151C8((Actor *)sight);
            return 0;
        }

        dword_8009F600++;
        dword_8009F604 = hashedFileName;
        word_8009F5FC = 1;
    }

    return sight;
}

Actor_Sight *sight_init_80071EA8(int hashedFileName0, int hashedFileName1, short *itemEquippedIndicator, short itemId,
                                 short *xyOffsetBuffer)
{
    Actor_Sight *sight = (Actor_Sight *)0x0;

    if (dword_8009F604 != -1 && dword_8009F604 != hashedFileName1)
    {
        return sight;
    }

    sight = (Actor_Sight *)GV_NewActor_800150E4(7, 0x5c);
    if (sight)
    {
        GV_SetNamedActor_8001514C((Actor *)sight, (TActorFunction)sight_act_800714EC,
                                  (TActorFunction)sight_kill_800719C8, aSightC);
        sight->field_54_maybeFlags = 2;

        if (sight_loader_80071A54(sight, hashedFileName0, itemEquippedIndicator, itemId, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor_800151C8((Actor *)sight);
            return 0;
        }

        dword_8009F600++;
        dword_8009F604 = hashedFileName1;
    }

    return sight;
}

Actor_Sight *sight_init_80071F98(int hashedFileName, short *xyOffsetBuffer)
{
    Actor_Sight *sight = (Actor_Sight *)0x0;

    if (dword_8009F604 != -1 && dword_8009F604 != hashedFileName)
    {
        return sight;
    }

    dword_8009F600++;
    dword_8009F604 = hashedFileName;

    sight = (Actor_Sight *)GV_NewActor_800150E4(7, 0x5c);
    if (sight)
    {
        GV_SetNamedActor_8001514C((Actor *)sight, (TActorFunction)sight_act_800714EC,
                                  (TActorFunction)sight_kill_800719C8, aSightC);
        sight->field_54_maybeFlags = 2;

        if (sight_loader_80071A54(sight, hashedFileName, &word_8009F5FC, 1, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor_800151C8((Actor *)sight);
            return 0;
        }

        word_8009F5FC = 1;
    }

    return sight;
}

extern short word_8009F5FC;

void sub_80072074()
{
    word_8009F5FC = 0;
}
