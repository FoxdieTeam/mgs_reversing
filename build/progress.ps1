Push-Location $PSScriptRoot

function Percentage([float]$cur, [float]$max)
{
     ($cur/ $max) * 100.0
}

$sourceCount = Get-ChildItem ..\src\ -recurse | Measure-Object -property length -sum
$asmCount = Get-ChildItem ..\asm\ -recurse | Measure-Object -property length -sum

Write-Host Bytes of code in src $sourceCount.Sum
Write-Host Bytes of code in asm $asmCount.Sum

$total = $sourceCount.Sum + $asmCount.Sum

$ret = Percentage -cur $sourceCount.Sum -max $total
$ret = [math]::Round($ret,8)
Write-Host Progress: $ret%

