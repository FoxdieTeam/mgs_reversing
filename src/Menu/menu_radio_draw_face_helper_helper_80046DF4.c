#include "Menu/menuman.h"

extern const char aNoFaceData[]; // = "NO_FACE_DATA\n";

void menu_radio_draw_face_helper_helper_80046DF4(int idx, menu_chara_struct *pChara, int chara, int code, int a5)
{
    int                    i;
    face_header           *faceIter;
    face_simple_anim      *simpleAnim;
    face_full_anim        *fullAnim;
    menu_chara_struct_sub *pSub;

    pSub = &pChara->field_3C[idx];

    if (code == 0)
    {
        pSub->field_0_animState = 3;
        pSub->field_14_face_anim.raw_ptr = NULL;
        pSub->field_2_chara = chara;
    }
    else
    {
        faceIter = pChara->field_34_faces;

        for (i = pChara->field_30_face_count; i > 0; faceIter++, i--)
        {
            if (faceIter->field_2_code == code)
            {
                pSub->field_2_chara = chara;

                switch (faceIter->field_0_anim_type)
                {
                case FACE_ANIM_SIMPLE:
                    simpleAnim = faceIter->field_8_anim_data.simple_anim;
                    if (a5 >= 0)
                    {
                        sub_80046BD8(idx);
                    }

                    menu_radio_load_palette_80046B74(simpleAnim->field_0_palette, idx);
                    sub_80046B10(simpleAnim->field_4_face, idx);
                    pSub->field_0_animState = 1;
                    pSub->field_A = a5;
                    pSub->field_C = a5;
                    pSub->field_14_face_anim.simple_anim = simpleAnim;
                    pSub->field_4C_leftCodecPortraitFrame = 0;
                    pSub->field_E = 0;
                    return;

                case FACE_ANIM_FULL:
                    fullAnim = faceIter->field_8_anim_data.full_anim;
                    pSub->field_8_animFrameNum = 0;
                    pSub->field_4C_leftCodecPortraitFrame = 0;
                    sub_80046C90(pSub, idx, fullAnim, pSub->field_8_animFrameNum);
                    pSub->field_0_animState = 2;
                    pSub->field_14_face_anim.full_anim = fullAnim;
                    return;

                default:
                    return;
                }
            }
        }

        printf(aNoFaceData);
    }
}
