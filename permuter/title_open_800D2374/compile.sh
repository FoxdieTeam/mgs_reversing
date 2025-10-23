#!/bin/sh

# MGS Reversing Project - Permuter Compile Script
# Adapted from FoxdieTeam decomp-permuter-psyq

# config
# --------------------------

G=8
PSYQ=4.4

# --------------------------

# Get absolute paths
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
MGS_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
PSYQ_SDK="$MGS_ROOT/../psyq_sdk"

if [ ! -d "$PSYQ_SDK" ]; then
    echo "PSYQ_SDK not found at $PSYQ_SDK"
    exit 1
fi

INPUT="$1"
OUTPUT="$3"
ASM="${INPUT}.asm"

# Include paths from MGS project
INCLUDES="-I$MGS_ROOT/include -I$MGS_ROOT/include/mgsvt -I$MGS_ROOT/include/sdk"

CPPPSX="cpp -nostdinc -undef -D__GNUC__=2 -D__OPTIMIZE__ -lang-c -Dmips  \
    -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ \
    -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C \
    $INCLUDES ${INPUT}"
CC1PSX="wine ${PSYQ_SDK}/psyq_${PSYQ}/bin/CC1PSX.EXE -quiet -O2 -G${G} -g0 -o ${ASM}"
ASPSX="wine ${PSYQ_SDK}/psyq_${PSYQ}/bin/aspsx.exe -q -G${G} -g0 $ASM -o ${OUTPUT}"

$($CPPPSX | $CC1PSX)
$($ASPSX)

rm "$ASM"
