#include "sight.h"

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Menu/menuman.h"
#include "strcode.h"

#define EXEC_LEVEL GV_ACTOR_AFTER2

short word_8009F5FC = 1;
int  dword_8009F600 = 0;
int  dword_8009F604 = -1;
int  dword_8009F608 = 0;

STATIC void sight_act_helper_8007111C(SightWork *work)
{
    int     message_result;
    GV_MSG *message;

    message_result = GV_ReceiveMessage(0x30da, &message);

    if (message_result > 0)
    {
        while (--message_result >= 0)
        {
            switch (message->message[0])
            {
            case HASH_ON:
                dword_8009F608 &= ~1;
                break;

            case HASH_OFF:
                dword_8009F608 |= 1;
                break;
            }

            message++;
        }
    }
}

static inline int calc(int diff, int offset)
{
    int mult = diff * offset;

    if (mult < 0)
    {
        mult += 3;
    }

    return mult >> 2;
}

// Handles the animation of the HUD when transitioning into the scope view or the box or gas mask's first-person view.
// Various permutations show the logic is sound but getting it to match is hard and is essentially forced here by the
// use of absurd intermediates.
STATIC void sight_800711C0(SightWork *work, int frameCount, void *primitive, int primOffsetIndicesIndex,
                    SightPrimOffsetIndices *primOffsetIndices, SightPrimOffsetInfo *primOffsetInfo, int primOffset,
                    unsigned int flags)
{
    void                *currentPrimX;
    char                 code;
    int                  gouraudShaded;
    void                *primBuf;
    int                  step;
    int                  index;
    void                *currentPrimY;
    int                  currentPrimOffsetIndex;
    SightPrimOffsetInfo *currentPrimOffsetInfo;
    int                  diff;
    char                *indices;
    int                  invalid;
    int                 *frameCountPtr;

    DVECTOR localXY;

    currentPrimX = primitive + 8;
    index = 0;
    invalid = -1;
    currentPrimY = primitive + 10;

    primOffsetIndices += primOffsetIndicesIndex - 1;
    indices = primOffsetIndices->indices;

    code = getcode(primitive);
    gouraudShaded = (code >> 2) & 4;
    step = gouraudShaded + 4;

    primBuf = work->field_34_primitiveBufferInfo->field_8_primitiveBuffer + primOffset + 8;

    for (; index < 4; primBuf += step, currentPrimY += step, currentPrimX += step, index++)
    {
        currentPrimOffsetIndex = indices[index];
        if (currentPrimOffsetIndex != 0)
        {
            currentPrimOffsetInfo = &primOffsetInfo[currentPrimOffsetIndex - 1];
            if (frameCount == invalid)
            {
                diff = currentPrimOffsetInfo->field_0_nextFrame - currentPrimOffsetInfo->field_1_prevFrame;
            }
            else
            {
                if (currentPrimOffsetInfo->field_0_nextFrame >= frameCount)
                {
                    continue;
                }
                if ((currentPrimOffsetInfo->field_1_prevFrame + 1 < frameCount) && ((flags & 0x8000) != 0))
                {
                    continue;
                }

                *(int *)currentPrimX = *(int *)primBuf;
                diff = *(frameCountPtr = &frameCount) - currentPrimOffsetInfo->field_1_prevFrame;
                if (diff >= 0)
                {
                    continue;
                }
            }

            localXY.vx = calc(diff, currentPrimOffsetInfo->field_2_xOffsetMultiplier);
            localXY.vy = calc(diff, currentPrimOffsetInfo->field_3_yOffsetMultiplier);

            *(short *)currentPrimX += localXY.vx;
            *(short *)currentPrimY += localXY.vy;
        }
    }
}

// Called every frame when in the first-person view with the thermal goggles or night-vision goggles.
STATIC void sight_act_helper_80071320(SightWork *work, void *targetPrim, short *xyOffsetBuffer, int primOffset)
{
    void *posX;
    void *posY;
    void *primBuf;
    char  code;
    void *copiedPrim;
    void *copiedXY;
    int   gouraudShaded;
    int   tag;
    int   iterations;
    int   gouraudShadedShifted;
    int   index;
    int   step;

    posX = targetPrim + 8;
    if (work->field_50 < 3)
    {
        primBuf = work->field_34_primitiveBufferInfo->field_8_primitiveBuffer;
        copiedPrim = primBuf + primOffset;

        code = getcode(targetPrim);
        gouraudShaded = (code >> 4) & 1;

        tag = *(int *)copiedPrim;
        if (tag == 0xff)
        {
            iterations = 1;
        }
        else
        {
            if ((code & 0x40) != 0)
            {
                if ((code & 0x4) == 0)
                {
                    if ((code & 0x8) != 0)
                    {
                        iterations = 3;
                    }
                    else
                    {
                        iterations = 2;
                    }
                }
                else
                {
                    iterations = 4;
                }
            }
            else
            {
                if ((code & 0x8) != 0)
                {
                    iterations = 4;
                }
                else
                {
                    iterations = 3;
                }
            }
        }

        copiedXY = copiedPrim + 8; // Access (x,y) coordinates.
        do
        {
            index = 0;
        } while (0); // Force a match because of regswap.
        if (iterations != 0)
        {
            gouraudShadedShifted = gouraudShaded << 2;
            step = gouraudShadedShifted + 4;
            posY = posX + 2;

            do
            {
                // Copy (x,y) coordinates.
                *(int *)posX = *(int *)copiedXY;
                copiedXY += step;

                // Now apply (x,y) offsets.
                *(short *)posX += xyOffsetBuffer[0];
                posX += step;

                *(short *)posY += xyOffsetBuffer[1];
                posY += step;

                index++;
            } while (index < iterations);
        }
    }
}

// Called when transitioning into the first-person view with any relevant items.
STATIC void sight_act_helper_800713FC(SightWork *work, int clock)
{
    void                     *primBuf;
    unsigned int             *primBufIter;
    SightPrimitiveBufferInfo *primBufInfo;
    int                       primBufSize;
    int                       numPrims;
    SightPrimBufInfoStruct   *ancillaryInfo;
    unsigned int             *origBuf;
    int                       index;
    int                       primOffset;
    void                     *currentPrim;
    int                       tag;

    primBuf = work->field_38_primitiveDoubleBuffer[clock];
    primBufIter = primBuf;

    primBufInfo = work->field_34_primitiveBufferInfo;
    ancillaryInfo = primBufInfo->field_4_ancillaryInfo;
    numPrims = primBufInfo->field_3_primCount;
    primBufSize = primBufInfo->field_0_primitiveBufferSize;
    origBuf = primBufInfo->field_8_primitiveBuffer;

    for (index = 0; index < (primBufSize / 4); index++)
    {
        *primBufIter++ = *origBuf++;
    }

    while (--numPrims >= 0)
    {
        primOffset = ancillaryInfo->field_2_primOffset;
        currentPrim = (char *)primBuf + primOffset;
        tag = *(int *)currentPrim;
        if (tag != 0xff)
        {
            *(char *)(currentPrim + 3) = tag;
        }
        ++ancillaryInfo;
    }
}

// Called every frame to display the scope's text pseudo-primitives.
STATIC void sight_act_helper_80071498(SightTextPseudoPrim *textPrim)
{
    MENU_Locate(textPrim->field_8_posX, textPrim->field_A_posY, 0);
    MENU_Color(textPrim->field_4_r, textPrim->field_5_g, textPrim->field_6_b);
    MENU_Printf("%s", textPrim->field_C_text);
}

STATIC void sight_act_800714EC(SightWork *work)
{
    SightPrimitiveBufferInfo *primBufInfo;
    SightPrimBufInfoStruct   *ancillaryInfo;
    int                       primCount;
    DR_TPAGE                 *tPageBuf;
    unsigned int              frameCount;
    int                       field30;
    int                       frameCountPositive;
    unsigned char            *ot;
    int                       field54Flags;
    void                     *primBuf;
    int                       flag;
    unsigned char             offsetIndicesIndex;
    int                       primOffset;
    char                      tPageInfo;
    char                      ancField1Anded;
    char                      ancField1Shifted;
    SightPrimOffsetIndices   *primOffsetIndicesArray;
    void                     *offsetPrimBuf;
    SightPrimBufInfo_0x14    *infoField14;
    char                      infoField14Field0;
    SightPrimOffsetInfo      *primOffsetInfoArray;
    int                       frameCountMod;
    char                      infoField14Field1;
    int                       tag;
    char                      code;
    short                    *xyOffsetBuffer;

    if (work->field_20_itemId != *work->field_24_itemEquippedIndicator)
    {
        GV_DestroyActor((GV_ACT *)work);
        return;
    }

    work->field_54_maybeFlags &= 0xffff7fff;

    if (work->field_58_clock != GV_Clock && (++work->field_5A_maybeFlags & 0xffff) == 2)
    {
        work->field_54_maybeFlags |= 0x8000;
        work->field_5A_maybeFlags = 0;
    }

    work->field_58_clock = GV_Clock;
    sight_act_helper_8007111C(work);
    work->field_28_currentMap = GM_CurrentMap;

    primBufInfo = work->field_34_primitiveBufferInfo;
    primCount = primBufInfo->field_3_primCount;
    ancillaryInfo = primBufInfo->field_4_ancillaryInfo;

    tPageBuf = work->field_44_tPageDoubleBuffer[GV_Clock];

    frameCount = work->field_2C_frameCount;
    field30 = work->field_30;
    ot = DG_ChanlOTag(1);

    primOffsetIndicesArray = primBufInfo->field_C_primOffsetIndicesArray;
    primOffsetInfoArray = primBufInfo->field_10_primOffsetInfoArray;
    primBuf = work->field_38_primitiveDoubleBuffer[GV_Clock];

    if (field30 == 0 && primBufInfo->field_2 < work->field_2C_frameCount)
    {
        flag = (0x100 << GV_Clock);
        if (!(work->field_54_maybeFlags & flag))
        {
            work->field_54_maybeFlags |= flag;
            sight_act_helper_800713FC(work, GV_Clock);
        }
        if ((work->field_54_maybeFlags & 0x300) == 0x300)
        {
            work->field_30 = 1;
        }
    }

    xyOffsetBuffer = work->field_4C_xyOffsetBuffer;
    field54Flags = work->field_54_maybeFlags;
    if (xyOffsetBuffer != (short *)0x0)
    {
        if (xyOffsetBuffer[0] == 0 && xyOffsetBuffer[1] == 0)
        {
            if (++work->field_50 >= 3 && !(field54Flags & 0x8000))
            {
                work->field_50 = 2;
            }
        }
        else
        {
            work->field_50 = 0;
        }
    }

    frameCountPositive = 0;
    if (!(field54Flags & (0x100 << GV_Clock)))
    {
        frameCountPositive = (0 < frameCount);
    }

    while (--primCount >= 0)
    {
        primOffset = ancillaryInfo->field_2_primOffset;                 // 0x1(s5)
        tPageInfo = ancillaryInfo->field_1_tPageInfo;                   // 0x0(s5)
        offsetIndicesIndex = ancillaryInfo->field_0_offsetIndicesIndex; // 0x0(t0)

        ancillaryInfo++;
        offsetPrimBuf = primBuf + primOffset;
        ancField1Anded = tPageInfo & 0x3f; // This keeps the 6 LSBs.
        ancField1Shifted = tPageInfo >> 6;

        if (frameCountPositive != 0 && offsetIndicesIndex != 0)
        {
            sight_800711C0(work, frameCount, offsetPrimBuf, offsetIndicesIndex, primOffsetIndicesArray,
                           primOffsetInfoArray, primOffset, field54Flags);
        }

        if (ancField1Anded != 0)
        {
            infoField14 = &work->field_34_primitiveBufferInfo->field_14_array[ancField1Anded - 1];
            infoField14Field0 = infoField14->field_0;
            frameCountMod = work->field_2C_frameCount % infoField14Field0;
            infoField14Field1 = infoField14->field_1;
            if (frameCountMod < infoField14Field1)
            {
                continue;
            }
        }
        if (field30 != 0 && xyOffsetBuffer != (short *)0x0)
        {
            sight_act_helper_80071320(work, offsetPrimBuf, xyOffsetBuffer, primOffset);
        }
        tag = *(int *)offsetPrimBuf;
        if (tag == 0xff)
        {
            if (!(dword_8009F608 & 1) && !(GM_PlayerStatus & PLAYER_NOT_SIGHT))
            {
                sight_act_helper_80071498(offsetPrimBuf);
            }
        }
        else
        {
            if (!(dword_8009F608 & 1) && !(GM_PlayerStatus & PLAYER_NOT_SIGHT))
            {
                addPrim(ot, offsetPrimBuf);
            }
            code = getcode(offsetPrimBuf);
            if ((code & 2) != 0) // Checking for semi-transparency.
            {
                SetDrawTPage(tPageBuf, 0, 1, ancField1Shifted << 5);
                if (!(dword_8009F608 & 1) && !(GM_PlayerStatus & PLAYER_NOT_SIGHT))
                {
                    addPrim(ot, tPageBuf);
                }
                tPageBuf += 1;
            }
        }
    }

    if (work->field_2C_frameCount < 0x7fff0000 && GV_PauseLevel == 0)
    {
        work->field_2C_frameCount++;
    }

    menu_Text_Init_80038B98();
}

STATIC void sight_kill_800719C8(SightWork *work)
{
    if (*work->field_38_primitiveDoubleBuffer)
    {
        GV_DelayedFree(*work->field_38_primitiveDoubleBuffer);
    }

    if (*work->field_44_tPageDoubleBuffer)
    {
        GV_DelayedFree(*work->field_44_tPageDoubleBuffer);
    }

    if ((0 < dword_8009F600) && (--dword_8009F600 == 0))
    {
        dword_8009F604 = -1;
    }

    dword_8009F608 &= ~1;
}

STATIC int sight_loader_80071A54(SightWork *work, int hashedFileName, short *itemEquippedIndicator, short itemId,
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
    int primCount;

    // Primitive iteration and access.
    unsigned int   code;
    unsigned int  *currentPrimitive;
    unsigned short primOffset;
    unsigned int   tag;

    // TPage information.
    int       tPageCount;
    DR_TPAGE *tPageMem;

    // Other.
    unsigned int            flags;
    SightPrimOffsetIndices *primOffsetIndices;
    SightPrimOffsetInfo    *primOffsetInfo;
    char                    offsetIndicesIndex;

    flags = work->field_54_maybeFlags;
    cacheId = GV_CacheID(hashedFileName, 's');
    info = (SightPrimitiveBufferInfo *)GV_GetCache(cacheId);
    work->field_34_primitiveBufferInfo = info;

    if (!info)
    {
        return -1;
    }

    ancillaryInfo = info->field_4_ancillaryInfo;
    primitiveBufferSize = info->field_0_primitiveBufferSize;
    primCount = info->field_3_primCount;
    primOffsetIndices = info->field_C_primOffsetIndicesArray;
    tPageCount = 0;
    primOffsetInfo = info->field_10_primOffsetInfoArray;
    primitiveBuffer = (unsigned int *)GV_Malloc(primitiveBufferSize * 2);
    work->field_38_primitiveDoubleBuffer[0] = primitiveBuffer;

    if (!primitiveBuffer)
    {
        return -1;
    }
    else
    {
        work->field_38_primitiveDoubleBuffer[1] = (unsigned int *)(((char *)primitiveBuffer) + primitiveBufferSize);
        originBuffer = work->field_34_primitiveBufferInfo->field_8_primitiveBuffer;
        targetBuffer = primitiveBuffer;
        firstPrimitiveBuffer = targetBuffer;
        firstPrimitiveBufferCopy = firstPrimitiveBuffer;
        for (i = 0; i < (primitiveBufferSize / 4); i++)
        {
            *(targetBuffer++) = *(originBuffer++);
        }

        while (--primCount >= 0)
        {
            primOffset = ancillaryInfo->field_2_primOffset;
            currentPrimitive = (unsigned int *)(((char *)firstPrimitiveBufferCopy) + primOffset);
            tag = *currentPrimitive;

            if (tag != 0xff)
            {
                *(((char *)currentPrimitive) + 3) = tag;
            }

            if ((flags & 2) == 0)
            {
                offsetIndicesIndex = ancillaryInfo->field_0_offsetIndicesIndex;

                if (offsetIndicesIndex != 0)
                {
                    // Handle the animation of the HUD when transitioning into the scope view or the box or gas mask's
                    // first-person view.
                    sight_800711C0(work, -1, currentPrimitive, ancillaryInfo->field_0_offsetIndicesIndex,
                                   primOffsetIndices, primOffsetInfo, 0, 0);
                }
            }

            code = getcode(currentPrimitive);

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
            work->field_2C_frameCount = (work->field_34_primitiveBufferInfo->field_2) + 2;
        }

        else
        {
            work->field_2C_frameCount = 0;
        }

        work->field_30 = (flags >> 1) & 1;
        work->field_20_itemId = itemId ^ 0;
        work->field_24_itemEquippedIndicator = itemEquippedIndicator;

        if (tPageCount == 0)
        {
            work->field_44_tPageDoubleBuffer[0] = (DR_TPAGE *)0x0;
            work->field_44_tPageDoubleBuffer[1] = (DR_TPAGE *)0x0;
        }

        else
        {
            tPageMem = (DR_TPAGE *)GV_Malloc((tPageCount * 2) * (sizeof(DR_TPAGE)));

            if (tPageMem == ((DR_TPAGE *)0x0))
            {
                return -1;
            }

            work->field_44_tPageDoubleBuffer[0] = tPageMem;
            work->field_44_tPageDoubleBuffer[1] = tPageMem + tPageCount;
        }

        work->field_40 = tPageCount;
        work->field_4C_xyOffsetBuffer = xyOffsetBuffer;
        work->field_50 = 0;
        work->field_54_maybeFlags = 0;
        work->field_58_clock = GV_Clock;
        work->field_5A_maybeFlags = 0;
        return 0;
    }
}

SightWork *NewSight_80071CDC(int hashedFileName0, int hashedFileName1, short *itemEquippedIndicator, short itemId,
                             short *xyOffsetBuffer)
{
    SightWork *work = (SightWork *)NULL;

    if (dword_8009F604 != -1 && dword_8009F604 != hashedFileName1)
    {
        return work;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(SightWork));
    if (work)
    {
        GV_SetNamedActor((GV_ACT *)work, sight_act_800714EC, sight_kill_800719C8, "sight.c");
        work->field_54_maybeFlags = 0;

        if (sight_loader_80071A54(work, hashedFileName0, itemEquippedIndicator, itemId, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor((GV_ACT *)work);
            return 0;
        }

        dword_8009F600++;
        dword_8009F604 = hashedFileName1;
    }

    return work;
}

SightWork *sight_init_80071DC8(int hashedFileName, short *xyOffsetBuffer)
{
    SightWork *work = (SightWork *)NULL;

    if (dword_8009F604 != -1 && dword_8009F604 != hashedFileName)
    {
        return work;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(SightWork));
    if (work)
    {
        GV_SetNamedActor((GV_ACT *)work, sight_act_800714EC, sight_kill_800719C8, "sight.c");
        work->field_54_maybeFlags = 0;

        if (sight_loader_80071A54(work, hashedFileName, &word_8009F5FC, 1, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor((GV_ACT *)work);
            return 0;
        }

        dword_8009F600++;
        dword_8009F604 = hashedFileName;
        word_8009F5FC = 1;
    }

    return work;
}

SightWork *sight_init_80071EA8(int hashedFileName0, int hashedFileName1, short *itemEquippedIndicator, short itemId,
                               short *xyOffsetBuffer)
{
    SightWork *work = (SightWork *)NULL;

    if (dword_8009F604 != -1 && dword_8009F604 != hashedFileName1)
    {
        return work;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(SightWork));
    if (work)
    {
        GV_SetNamedActor((GV_ACT *)work, sight_act_800714EC, sight_kill_800719C8, "sight.c");
        work->field_54_maybeFlags = 2;

        if (sight_loader_80071A54(work, hashedFileName0, itemEquippedIndicator, itemId, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor((GV_ACT *)work);
            return 0;
        }

        dword_8009F600++;
        dword_8009F604 = hashedFileName1;
    }

    return work;
}

SightWork *sight_init_80071F98(int hashedFileName, short *xyOffsetBuffer)
{
    SightWork *work = (SightWork *)NULL;

    if (dword_8009F604 != -1 && dword_8009F604 != hashedFileName)
    {
        return work;
    }

    dword_8009F600++;
    dword_8009F604 = hashedFileName;

    work = GV_NewActor(EXEC_LEVEL, sizeof(SightWork));
    if (work)
    {
        GV_SetNamedActor((GV_ACT *)work, sight_act_800714EC, sight_kill_800719C8, "sight.c");
        work->field_54_maybeFlags = 2;

        if (sight_loader_80071A54(work, hashedFileName, &word_8009F5FC, 1, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor((GV_ACT *)work);
            return 0;
        }

        word_8009F5FC = 1;
    }

    return work;
}

void sub_80072074()
{
    word_8009F5FC = 0;
}
