#include "sight.h"
#include "libgv/libgv.h"
#include "Menu/menuman.h"
#include "libdg/libdg.h"
#include "Game/game.h"

short word_8009F5FC = 1;
int  dword_8009F600 = 0;
int  dword_8009F604 = -1;
int  dword_8009F608 = 0;

void sight_act_helper_8007111C(Actor_Sight *sight)
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
void sight_800711C0(Actor_Sight *sight, int frameCount, void *primitive, int primOffsetIndicesIndex,
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

    primBuf = sight->field_34_primitiveBufferInfo->field_8_primitiveBuffer + primOffset + 8;

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
void sight_act_helper_80071320(Actor_Sight *sight, void *targetPrim, short *xyOffsetBuffer, int primOffset)
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
    if (sight->field_50 < 3)
    {
        primBuf = sight->field_34_primitiveBufferInfo->field_8_primitiveBuffer;
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
void sight_act_helper_800713FC(Actor_Sight *sight, int clock)
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

    primBuf = sight->field_38_primitiveDoubleBuffer[clock];
    primBufIter = primBuf;

    primBufInfo = sight->field_34_primitiveBufferInfo;
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

extern const char aStringFormat[];

// Called every frame to display the scope's text pseudo-primitives.
void sight_act_helper_80071498(SightTextPseudoPrim *textPrim)
{
    menu_Text_XY_Flags_80038B34(textPrim->field_8_posX, textPrim->field_A_posY, 0);
    menu_Color_80038B4C(textPrim->field_4_r, textPrim->field_5_g, textPrim->field_6_b);
    menu_Text_80038C38(aStringFormat, textPrim->field_C_text);
}

extern int GV_Clock_800AB920;
extern int GM_CurrentMap_800AB9B0;
extern int GM_PlayerStatus_800ABA50;
extern int GV_PauseLevel_800AB928;

void sight_act_800714EC(Actor_Sight *sight)
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

    if (sight->field_20_itemId != *sight->field_24_itemEquippedIndicator)
    {
        GV_DestroyActor_800151C8((GV_ACT *)sight);
        return;
    }

    sight->field_54_maybeFlags &= 0xffff7fff;

    if (sight->field_58_clock != GV_Clock_800AB920 && (++sight->field_5A_maybeFlags & 0xffff) == 2)
    {
        sight->field_54_maybeFlags |= 0x8000;
        sight->field_5A_maybeFlags = 0;
    }

    sight->field_58_clock = GV_Clock_800AB920;
    sight_act_helper_8007111C(sight);
    sight->field_28_currentMap = GM_CurrentMap_800AB9B0;

    primBufInfo = sight->field_34_primitiveBufferInfo;
    primCount = primBufInfo->field_3_primCount;
    ancillaryInfo = primBufInfo->field_4_ancillaryInfo;

    tPageBuf = sight->field_44_tPageDoubleBuffer[GV_Clock_800AB920];

    frameCount = sight->field_2C_frameCount;
    field30 = sight->field_30;
    ot = DG_Chanl(1)->mOrderingTables[GV_Clock_800AB920];

    primOffsetIndicesArray = primBufInfo->field_C_primOffsetIndicesArray;
    primOffsetInfoArray = primBufInfo->field_10_primOffsetInfoArray;
    primBuf = sight->field_38_primitiveDoubleBuffer[GV_Clock_800AB920];

    if (field30 == 0 && primBufInfo->field_2 < sight->field_2C_frameCount)
    {
        flag = (0x100 << GV_Clock_800AB920);
        if (!(sight->field_54_maybeFlags & flag))
        {
            sight->field_54_maybeFlags |= flag;
            sight_act_helper_800713FC(sight, GV_Clock_800AB920);
        }
        if ((sight->field_54_maybeFlags & 0x300) == 0x300)
        {
            sight->field_30 = 1;
        }
    }

    xyOffsetBuffer = sight->field_4C_xyOffsetBuffer;
    field54Flags = sight->field_54_maybeFlags;
    if (xyOffsetBuffer != (short *)0x0)
    {
        if (xyOffsetBuffer[0] == 0 && xyOffsetBuffer[1] == 0)
        {
            if (++sight->field_50 >= 3 && !(field54Flags & 0x8000))
            {
                sight->field_50 = 2;
            }
        }
        else
        {
            sight->field_50 = 0;
        }
    }

    frameCountPositive = 0;
    if (!(field54Flags & (0x100 << GV_Clock_800AB920)))
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
            sight_800711C0(sight, frameCount, offsetPrimBuf, offsetIndicesIndex, primOffsetIndicesArray,
                           primOffsetInfoArray, primOffset, field54Flags);
        }

        if (ancField1Anded != 0)
        {
            infoField14 = &sight->field_34_primitiveBufferInfo->field_14_array[ancField1Anded - 1];
            infoField14Field0 = infoField14->field_0;
            frameCountMod = sight->field_2C_frameCount % infoField14Field0;
            infoField14Field1 = infoField14->field_1;
            if (frameCountMod < infoField14Field1)
            {
                continue;
            }
        }
        if (field30 != 0 && xyOffsetBuffer != (short *)0x0)
        {
            sight_act_helper_80071320(sight, offsetPrimBuf, xyOffsetBuffer, primOffset);
        }
        tag = *(int *)offsetPrimBuf;
        if (tag == 0xff)
        {
            if (!(dword_8009F608 & 1) && !(GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000))
            {
                sight_act_helper_80071498(offsetPrimBuf);
            }
        }
        else
        {
            if (!(dword_8009F608 & 1) && !(GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000))
            {
                addPrim(ot, offsetPrimBuf);
            }
            code = getcode(offsetPrimBuf);
            if ((code & 2) != 0) // Checking for semi-transparency.
            {
                SetDrawTPage_800924A8(tPageBuf, 0, 1, ancField1Shifted << 5);
                if (!(dword_8009F608 & 1) && !(GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000))
                {
                    addPrim(ot, tPageBuf);
                }
                tPageBuf += 1;
            }
        }
    }

    if (sight->field_2C_frameCount < 0x7fff0000 && GV_PauseLevel_800AB928 == 0)
    {
        sight->field_2C_frameCount++;
    }

    menu_Text_Init_80038B98();
}

void sight_kill_800719C8(Actor_Sight *sight)
{
    if (*sight->field_38_primitiveDoubleBuffer)
    {
        GV_DelayedFree_80016254(*sight->field_38_primitiveDoubleBuffer);
    }

    if (*sight->field_44_tPageDoubleBuffer)
    {
        GV_DelayedFree_80016254(*sight->field_44_tPageDoubleBuffer);
    }

    if ((0 < dword_8009F600) && (--dword_8009F600 == 0))
    {
        dword_8009F604 = -1;
    }

    dword_8009F608 &= ~1;
}

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
    primCount = info->field_3_primCount;
    primOffsetIndices = info->field_C_primOffsetIndicesArray;
    tPageCount = 0;
    primOffsetInfo = info->field_10_primOffsetInfoArray;
    primitiveBuffer = (unsigned int *)GV_Malloc_8001620C(primitiveBufferSize * 2);
    sight->field_38_primitiveDoubleBuffer[0] = primitiveBuffer;

    if (!primitiveBuffer)
    {
        return -1;
    }
    else
    {
        sight->field_38_primitiveDoubleBuffer[1] = (unsigned int *)(((char *)primitiveBuffer) + primitiveBufferSize);
        originBuffer = sight->field_34_primitiveBufferInfo->field_8_primitiveBuffer;
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
                    sight_800711C0(sight, -1, currentPrimitive, ancillaryInfo->field_0_offsetIndicesIndex,
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
            sight->field_44_tPageDoubleBuffer[0] = (DR_TPAGE *)0x0;
            sight->field_44_tPageDoubleBuffer[1] = (DR_TPAGE *)0x0;
        }

        else
        {
            tPageMem = (DR_TPAGE *)GV_Malloc_8001620C((tPageCount * 2) * (sizeof(DR_TPAGE)));

            if (tPageMem == ((DR_TPAGE *)0x0))
            {
                return -1;
            }

            sight->field_44_tPageDoubleBuffer[0] = tPageMem;
            sight->field_44_tPageDoubleBuffer[1] = tPageMem + tPageCount;
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
        GV_SetNamedActor_8001514C((GV_ACT *)sight, (TActorFunction)sight_act_800714EC,
                                  (TActorFunction)sight_kill_800719C8, aSightC);
        sight->field_54_maybeFlags = 0;

        if (sight_loader_80071A54(sight, hashedFileName0, itemEquippedIndicator, itemId, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor_800151C8((GV_ACT *)sight);
            return 0;
        }

        dword_8009F600++;
        dword_8009F604 = hashedFileName1;
    }

    return sight;
}

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
        GV_SetNamedActor_8001514C((GV_ACT *)sight, (TActorFunction)sight_act_800714EC,
                                  (TActorFunction)sight_kill_800719C8, aSightC);
        sight->field_54_maybeFlags = 0;

        if (sight_loader_80071A54(sight, hashedFileName, &word_8009F5FC, 1, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor_800151C8((GV_ACT *)sight);
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
        GV_SetNamedActor_8001514C((GV_ACT *)sight, (TActorFunction)sight_act_800714EC,
                                  (TActorFunction)sight_kill_800719C8, aSightC);
        sight->field_54_maybeFlags = 2;

        if (sight_loader_80071A54(sight, hashedFileName0, itemEquippedIndicator, itemId, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor_800151C8((GV_ACT *)sight);
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
        GV_SetNamedActor_8001514C((GV_ACT *)sight, (TActorFunction)sight_act_800714EC,
                                  (TActorFunction)sight_kill_800719C8, aSightC);
        sight->field_54_maybeFlags = 2;

        if (sight_loader_80071A54(sight, hashedFileName, &word_8009F5FC, 1, xyOffsetBuffer) < 0)
        {
            GV_DestroyActor_800151C8((GV_ACT *)sight);
            return 0;
        }

        word_8009F5FC = 1;
    }

    return sight;
}

void sub_80072074()
{
    word_8009F5FC = 0;
}
