Push-Location $PSScriptRoot

if ($Env:APPVEYOR_URL -And !$Env:APPVEYOR_PULL_REQUEST_NUMBER)
{
	$progressToolOutput = (progress_script\progress.exe $PSScriptRoot\..\obj\asm.sym) | Out-String

	$msg =
"
$progressToolOutput
"
	Write-Host $msg

	.\webhook.ps1 -webHookUrl (get-item env:HOOK_URL).Value -message $msg
}
