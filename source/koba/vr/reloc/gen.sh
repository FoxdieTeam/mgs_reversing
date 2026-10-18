#!/bin/sh
# Regenerates the relocatable asm (INCLUDE_ASM_RELOC) from the original vr_sud01 overlay.
# usage (from the repo root)
OV=${OV:-/home/snake/dev/mgs_tools/vrov}
MAP=${MAP:-obj_vr/asm_vr_sud01_lhs.map}   # exe publics (any VR link map of the build)
S="python3 build/symbolize_asm.py $OV/vr_sud01.bin"
$S 800D58C8 --name VrDrawTime --map $MAP --symfile source/koba/vr/reloc/vr_data.syms \
   --string 800DF344=vr_fmt_label --string 800DF348=vr_fmt_time --out source/koba/vr/reloc/VrDrawTime.s
$S 800D7578 --name BackgrndSetPanel --map $MAP --out source/koba/vr/reloc/BackgrndSetPanel.s
$S 800DDEAC --name VrBg3GetResources --map $MAP --symfile source/koba/vr/reloc/bg3.syms \
   --string 800DF6E4=bg3_op_back_l --string 800DF6F0=bg3_op_back_r --out source/koba/vr/reloc/VrBg3GetResources.s
$S 800D9904 --name VrClearDrawResult --map $MAP --symfile source/koba/vr/reloc/vr_data.syms --symfile source/koba/vr/reloc/vrclear.syms \
   --string 800DF4A8=vrclear_str_1st --string 800DF4AC=vrclear_str_2nd --string 800DF4B0=vrclear_str_3rd \
   --string 800DF4B4=vrclear_str_record --string 800DF4BC=vrclear_ranks:ptrs:4 \
   --globl vrclear_fmt_s --string 800DF4CC=vrclear_fmt_s --string 800DF4D0=vrclear_fmt_d \
   --string 800DF4D4=vrclear_str_bullet --string 800DF4E0=vrclear_str_bonus3 --string 800DF4F8=vrclear_str_bonus1 --out source/koba/vr/reloc/VrClearDrawResult.s

# vrbox4.c (UFO mission revision of vrbox.c, original in the vcd_n04 overlay)
OV4=$OV/vcd_n04.bin
MAP4=${MAP4:-obj_vr/asm_vcd_n04_lhs.map}
S4="python3 build/symbolize_asm.py $OV4"
$S4 800D0C24 --name VrBox4Act --map $MAP4 --symfile source/koba/vr/reloc/vrbox4.syms --out source/koba/vr/reloc/VrBox4Act.s
$S4 800D050C --name VrBox4InitShadow --map $MAP4 --symfile source/koba/vr/reloc/vrbox4.syms \
   --string 800D4784=vrbox4_str_shadow --out source/koba/vr/reloc/VrBox4InitShadow.s
