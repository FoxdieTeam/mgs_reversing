param([String]$psyq_path="")

$ErrorActionPreference = "Stop"

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

    (Get-Content $psyq_path\psyq.ini.template) | 
    Foreach-Object {$_ -replace '\$PSYQ_PATH',$psyq_path_without_bin}  | 
    Out-File $psyq_path\psyq.ini
}


$cc_opts = "-O2 -g -c"
$asm_opts = "/l /q"

# Compile all .C files
$cFiles = Get-ChildItem *.C
foreach ($file in $cFiles)
{
    $objName = $file.Name
    $objName = $objName.replace(".C", "").replace(".c", "")
    ccpsx.exe -O2 -g -c "$objName.c" "-o$objName.obj"
    if($LASTEXITCODE -eq 0)
    {
        Write-Host "Compiled $objName.c"  -ForegroundColor "green"
    } 
    else 
    {
        Write-Error "Compilation failed for: ccpsx.exe -O2 -g -c $objName.c -o$objName.obj"
    }
}

# Compile all .S files
$sFiles = Get-ChildItem *.S
foreach ($file in $sFiles)
{
    $objName = $file.Name
    $objName = $objName.replace(".S", "").replace(".s", "")
    asmpsx.exe /l /q "$objName.s","$objName.obj"
    if($LASTEXITCODE -eq 0)
    {
        Write-Host "Assembled $objName.s"  -ForegroundColor "green"
    } 
    else 
    {
        Write-Error "Assembling failed for:asmpsx.exe /l /q $objName.s,$objName.obj"
    }
}

# Run the linker
psylink.exe /m "@linker.txt",test2.cpe,asm.sym,asm.map
if($LASTEXITCODE -eq 0)
{
    Write-Host "Linked test2.cpe" -ForegroundColor "yellow"
} 
else 
{
    Write-Error "Linking failed"
}

# Convert CPE to an EXE
.\cpe2exe.exe /CJ test2.cpe
if($LASTEXITCODE -eq 0)
{
    Write-Host "test2.cpe -> test2.exe" -ForegroundColor "yellow"
} 
else 
{
    Write-Error "Converting CPE to EXE failed"
}

# Validate the output is matching the OG binary hash
$actualValue = Get-FileHash -Path test2.exe -Algorithm SHA256
if ($actualValue.Hash -eq "4b8252b65953a02021486406cfcdca1c7670d1d1a8f3cf6e750ef6e360dc3a2f")
{
    Write-Host OK $actualValue.Hash -ForegroundColor "green"
}
else
{
    Write-Error Binary is not matching $actualValue.Hash
}
