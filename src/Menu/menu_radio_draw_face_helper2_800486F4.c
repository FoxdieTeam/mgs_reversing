#include "Menu/menuman.h"

void menu_radio_draw_face_helper2_800486F4(menu_chara_struct_sub *pSub, int idx)
{
    face_anim_image *image1;
    face_anim_image *image2;

    image1 = image2 = NULL;
    if (pSub->field_0_animState == 1)
    {
        if (pSub->field_E > 0)
        {
            image2 = pSub->field_14_face_anim.simple_anim->field_8_eyes[(pSub->field_E + 1) / 2 - 1];
            pSub->field_E++;
            if (pSub->field_E > 6)
            {
                pSub->field_E = 0;
            }
        }
        if (pSub->field_4C_leftCodecPortraitFrame > 0)
        {
            image1 = pSub->field_14_face_anim.simple_anim->field_14_mouth[pSub->field_4C_leftCodecPortraitFrame - 1];
        }
        sub_80046B10(pSub->field_14_face_anim.simple_anim->field_4_face, idx);
        if (image1)
        {
            sub_80046B10(image1, idx);
        }
        if (image2)
        {
            sub_80046B10(image2, idx);
        }
    }
}
