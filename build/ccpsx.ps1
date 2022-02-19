param([String]$psyq_path, [String]$flags, [String]$c, [String]$o, [String]$includes)

# MAKEFILE
#   @#powershell.exe -File ccpsx.ps1 -psyq_path "$(PSYQ_4_PATH)" -flags "$(CFLAGS)" -c "$<" -o "$@" -includes "$(INCLUDES)"

$c = Resolve-Path -Path $c.Replace("/", "\")
$o = $o.Replace("/", "\")
#$includes = $includes.Replace("/", "\")
$includes = $includes.Replace("-I ", "-I")

$tmp_folder = "$env:TEMP\_mgs"
New-Item -Force -ItemType directory -Path $tmp_folder | Out-Null

$outputFile = Split-Path $c -leaf

$tmp_c = "$tmp_folder\$( $outputFile )"
$tmp_asm = "$tmp_folder\$( $outputFile.Replace(".c", ".s") )"

$cpppsx_flags = "-undef -D__GNUC__=2 -D__OPTIMIZE__ $includes -lang-c -Dmips -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D__CHAR_UNSIGNED__ -D_LANGUAGE_C -DLANGUAGE_C"
#$flags = $flags.Replace("-Wall", "")
$aspsx_flags = $flags.Replace("-O2", "").Replace("-Wall", "")

$env:PSYQ_PATH = "$psyq_path\bin"
$env:CPLUS_INCLUDE_PATH = "$psyq_path\include" # NEW
$env:C_PLUS_INCLUDE_PATH = "$psyq_path\include"
$env:C_INCLUDE_PATH = "$psyq_path\include"
$env:LIBRARY_PATH = "$psyq_path\lib"
$env:PSX_PATH = "$psyq_path\bin"
$env:TMPDIR = $env:TEMP # NEW

#$psyq3_path = $psyq_path.Replace("4.3", "4.4")

$CPPPSX = "$psyq_path\bin\CPPPSX.EXE $cpppsx_flags `"$c`" `"$tmp_c`""
$CC1PSX = "$psyq_path\bin\CC1PSX.EXE -quiet $flags `"$tmp_c`" -o `"$tmp_asm`""
$ASPSX = "$psyq_path\bin\ASPSX.EXE -q $aspsx_flags `"$tmp_asm`" -o `"$o`""

#Write-Host $CPPPSX
#Write-Host $CC1PSX
#Write-Host $ASPSX

Invoke-Expression $CPPPSX
Invoke-Expression $CC1PSX
Invoke-Expression $ASPSX
