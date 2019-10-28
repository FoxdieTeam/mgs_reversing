$ErrorActionPreference = "Stop"

$actualValue = Get-FileHash -Path C:\mgs\test2.exe -Algorithm SHA256
if ($actualValue.Hash -eq "lol") {
    Write-Host "OK" -ForegroundColor "green"
}
else {
    Throw "produced binary is not matching"
}
