# debug.ps1 For Debugging
if ($myInvocation.MyCommand.Path -and (-not $env:__IS_DEBUG_CONSOLE)) {
    $env:__IS_DEBUG_CONSOLE = 1

    $scriptPath = $myInvocation.MyCommand.Path
    # Launch in a new window
    Start-Process powershell.exe -ArgumentList "-NoExit -ExecutionPolicy Bypass -File `"$scriptPath`""
    exit
}

Remove-Item env:\__IS_DEBUG_CONSOLE -ErrorAction SilentlyContinue

$modulePath = "$PSScriptRoot\debug.psm1"
Import-Module -Name $modulePath -Force

Write-Host "Initializing Diagnostic Suite..." -ForegroundColor Cyan

Show-DebugMenu