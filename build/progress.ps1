Push-Location $PSScriptRoot

function Percentage([float]$cur, [float]$max)
{
     ($cur/ $max) * 100.0
}

$sourceCount = Get-ChildItem ..\src\ -recurse | Measure-Object -property length -sum
$asmCount = Get-ChildItem ..\asm\ -recurse | Measure-Object -property length -sum


$total = $sourceCount.Sum + $asmCount.Sum

$ret = Percentage -cur $sourceCount.Sum -max $total
$ret = [math]::Round($ret,8)

$srcCount = $sourceCount.Sum
$asmCount = $asmCount.Sum

$msg =
"
Bytes of code in src $srcCount
Bytes of code in asm $asmCount
Progress: $ret%
"
Write-Host $msg

if ($Env:APPVEYOR_URL && !$Env:APPVEYOR_PULL_REQUEST_NUMBER)
{
	.\webhook.ps1 -webHookUrl (get-item env:HOOK_URL).Value -message $msg
}
