$ErrorActionPreference = "Stop"

$actualValue = Get-FileHash -Path C:\mgs\test2.exe -Algorithm SHA256
if ($actualValue.Hash -eq "4b8252b65953a02021486406cfcdca1c7670d1d1a8f3cf6e750ef6e360dc3a2f") {
    Write-Host "OK $actualValue.Hash" -ForegroundColor "green"
}
else {
    Throw "produced binary is not matching $actualValue.Hash"
}
