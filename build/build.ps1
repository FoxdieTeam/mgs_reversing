param([String]$psyq_path="")

$ErrorActionPreference = "Stop"

Push-Location $PSScriptRoot

if (![string]::IsNullOrEmpty($psyq_path))
{
    # Setup PSYQ env vars
    $Env:path += ";" + $psyq_path
    $Env:PSYQ_PATH = $psyq_path
    # Setup PSYQ ini
    $psyq_path_without_bin = $psyq_path
    if ($psyq_path_without_bin.EndsWith("\bin\", "CurrentCultureIgnoreCase"))
    {
        $psyq_path_without_bin = $psyq_path_without_bin.Substring(0, $psyq_path_without_bin.Length - 5)
    }
    elseif ($psyq_path_without_bin.EndsWith("\bin", "CurrentCultureIgnoreCase"))
    {
        $psyq_path_without_bin = $psyq_path_without_bin.Substring(0, $psyq_path_without_bin.Length - 4)
    }

    $env:C_PLUS_INCLUDE_PATH = "$psyq_path_without_bin\include"
    $Env:c_include_path = "$psyq_path_without_bin\include"
    $env:PSX_PATH = $psyq_path

    (Get-Content $psyq_path\psyq.ini.template) | 
    Foreach-Object {$_ -replace '\$PSYQ_PATH',$psyq_path_without_bin}  | 
    Out-File $psyq_path\psyq.ini
}

#Remove-Item $PSScriptRoot\..\obj -Recurse -ErrorAction Ignore | out-null
New-Item -ItemType directory -Path $PSScriptRoot\..\obj -ErrorAction SilentlyContinue | out-null

# Compile all .C files
$cFiles = Get-ChildItem $PSScriptRoot\..\src\*.C
foreach ($file in $cFiles)
{
    $objName = $file.Name
    $objName = $objName.replace(".C", "").replace(".c", "")
		
    ccpsx.exe -O2 -g -c -Wall "$PSScriptRoot\..\src\$objName.c" "-o$PSScriptRoot\..\obj\$objName.obj"
    if($LASTEXITCODE -eq 0)
    {
        Write-Host "Compiled ..\src\$objName.c"  -ForegroundColor "green"
    } 
    else 
    {
        Write-Error "Compilation failed for: ccpsx.exe -O2 -g -c -Wall $PSScriptRoot\..\src\$objName.c -o$PSScriptRoot\..\obj\$objName.obj"
    }
}

# Compile all .S files
$sFiles = Get-ChildItem $PSScriptRoot\..\asm\*.S
foreach ($file in $sFiles)
{
    $objName = $file.Name
    $objName = $objName.replace(".S", "").replace(".s", "")
	
	$fullObjName = "..\obj\$objName.obj"
	$fullSName = "..\asm\$objName.s"
	
	$upToDate = $false

	if ([System.IO.File]::Exists("$PSScriptRoot\$fullObjName"))
	{
		$asmWriteTime = (get-item "$PSScriptRoot\$fullSName").LastWriteTime
		$objWriteTime = (get-item "$PSScriptRoot\$fullObjName").LastWriteTime
		$upToDate = $asmWriteTime -le $objWriteTime
		#Write-Host "$asmWriteTime $objWriteTime = $upToDate"
	}
	
	if ($upToDate -eq $false)
	{
		asmpsx.exe /l /q $fullSName,$fullObjName 
		if($LASTEXITCODE -eq 0)
		{
			Write-Host "Assembled $fullSName"  -ForegroundColor "green"
		} 
		else 
		{
			Write-Error "Assembling failed for:asmpsx.exe /l /q $fullSName,$fullObjName "
		}
	}
}

# Run the linker
psylink.exe /c /n 4000 /q /gp .sdata /m "@$PSScriptRoot\linker_command_file.txt",$PSScriptRoot\..\obj\test2.cpe,$PSScriptRoot\..\obj\asm.sym,$PSScriptRoot\..\obj\asm.map
if($LASTEXITCODE -eq 0)
{
    Write-Host "Linked test2.cpe" -ForegroundColor "yellow"
} 
else 
{
    Write-Error "Linking failed $LASTEXITCODE"
}

# Convert CPE to an EXE
#cpe2x.exe test2.cpe
cpe2exe.exe /CJ ..\obj\test2.cpe | out-null

if($LASTEXITCODE -eq 0)
{
    Write-Host "..\obj\test2.cpe -> ..\obj\test2.exe" -ForegroundColor "yellow"
} 
else 
{
    Write-Error "Converting CPE to EXE failed"
}


if ([System.IO.File]::Exists(".\MDasm.exe"))
{
	.\MDasm.exe ..\SLPM_862.47 168780 168856 | Out-File "target.asm"
	.\MDasm.exe ..\obj\test2.exe 168780 168856 | Out-File "dump.asm"
}

# Validate the output is matching the OG binary hash
$actualValue = Get-FileHash -Path $PSScriptRoot\..\obj\test2.exe -Algorithm SHA256
if ($actualValue.Hash -eq "4b8252b65953a02021486406cfcdca1c7670d1d1a8f3cf6e750ef6e360dc3a2f")
{
    .\progress.ps1
    Write-Host OK $actualValue.Hash -ForegroundColor "green"
}
else
{
    Write-Host Binary is not matching $actualValue.Hash -ForegroundColor "red"
    exit 1
}

