# main.ps1 For Debugging


if ($myInvocation.MyCommand.Path -and (-not $env:__IS_DEBUG_CONSOLE)) {
    $env:__IS_DEBUG_CONSOLE = 1
    
    $scriptPath = $myInvocation.MyCommand.Path
    
    
    Start-Process powershell.exe -ArgumentList "-NoExit -ExecutionPolicy Bypass -File `"$scriptPath`""
    exit
}


Remove-Item env:\__IS_DEBUG_CONSOLE -ErrorAction SilentlyContinue


$modulePath = "$PSScriptRoot\module.psm1"
Import-Module -Name $modulePath -Force

Write-Host "Starting VGUI from isolated debug console..." -ForegroundColor Yellow
Invoke-VguiProcess