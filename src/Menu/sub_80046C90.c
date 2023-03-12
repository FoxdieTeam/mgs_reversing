#include "Menu/menuman.h"
#include "Game/game.h"

int sub_80046C90(menu_chara_struct_sub *pSub, int idx, face_full_anim *pFullAnim, int pFrameNum)

{
    face_full_anim_frame *fullAnimFrame;
    short                 field_10;
    unsigned int          tmp;

    while (1)
    {
        if (pFrameNum >= pFullAnim->field_0_frame_count)
        {
            return 0;
        }

        fullAnimFrame = &pFullAnim->field_4_frames[pFrameNum];
        if (fullAnimFrame->field_0_palette == NULL && fullAnimFrame->field_4_frame == NULL)
        {
            tmp = fullAnimFrame->field_8;
            switch (tmp)
            {
            case 0:
                GM_Sound_80032968(0, 0x3f, fullAnimFrame->field_10);
                pFrameNum++;
                break;

            case 1:
                if (pSub->field_4C_leftCodecPortraitFrame == 0)
                {
                    pSub->field_4C_leftCodecPortraitFrame = fullAnimFrame->field_10;
                }

                if (pSub->field_4C_leftCodecPortraitFrame < 255)
                {
                    if (pSub->field_4C_leftCodecPortraitFrame == tmp)
                    {
                        return 0;
                    }
                    pSub->field_4C_leftCodecPortraitFrame--;
                }
                pFrameNum = 0;
                break;

            default:
                pFrameNum++;
                break;
            }
        }
        else
        {
            if (fullAnimFrame->field_10 > 0)
            {
                sub_80046BD8(idx);
            }
            menu_radio_load_palette_80046B74(fullAnimFrame->field_0_palette, idx);
            sub_80046B10(fullAnimFrame->field_4_frame, idx);

            pSub->field_E = fullAnimFrame->field_8;

            tmp = pFrameNum;
            field_10 = fullAnimFrame->field_10;

            pSub->field_8_animFrameNum = tmp;
            pSub->field_A = field_10;
            pSub->field_C = field_10;
            return 1;
        }
    }
}
