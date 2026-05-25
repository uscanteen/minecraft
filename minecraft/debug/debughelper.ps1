# debughelper.ps1

if ($MyInvocation.MyCommand.Path -and (-not $env:__IS_DEBUG_CONSOLE)) {
    $env:__IS_DEBUG_CONSOLE = 1
    $scriptPath = $MyInvocation.MyCommand.Path
    $psArgs = @("-NoExit", "-ExecutionPolicy", "Bypass", "-File", $scriptPath)
    Start-Process -FilePath "powershell.exe" -ArgumentList $psArgs
    exit
}

Remove-Item env:\__IS_DEBUG_CONSOLE -ErrorAction SilentlyContinue

function Show-ArchitectureHelp {
    Write-Host ""
    Write-Host "--- HOW THIS SCRIPTING ARCHITECTURE WORKS ---" -ForegroundColor Yellow
    Write-Host ".PS1 (The Launcher):" -ForegroundColor Green
    Write-Host "  * Think of this as the ignition switch."
    Write-Host "  * It sets up the environment, creates isolated console windows, and prevents infinite loops."
    Write-Host "  * It should contain very little logic - mostly just Import-Module and calling functions."
    Write-Host ""
    Write-Host ".PSM1 (The Module / Engine):" -ForegroundColor Green
    Write-Host "  * Think of this as the actual engine block."
    Write-Host "  * All your logic, GUI generation, and data processing goes here."
    Write-Host "  * Changes made here are instantly available to the .ps1 launcher upon the next run."
    Write-Host "  * Remember to use Export-ModuleMember at the bottom to expose your functions!"
    Write-Host "--------------------------------------------" -ForegroundColor Yellow
    Write-Host ""
}

function Show-DebuggingTips {
    Write-Host ""
    Write-Host "--- DEBUGGING TIPS AND TRICKS ---" -ForegroundColor Yellow
    Write-Host "PowerShell / UI Creation:" -ForegroundColor Magenta
    Write-Host "  * If the GUI does not open, verify your Add-Type assemblies (System.Windows.Forms) are loaded."
    Write-Host "  * Remember that ShowDialog() pauses the script. Any code after it will not run until the window closes."
    Write-Host ""
    Write-Host "Log Reading (VGUI and EOF):" -ForegroundColor Magenta
    Write-Host "  * EOF (End of File) errors usually mean a missing end tag or an unclosed bracket in your syntax."
    Write-Host "  * If your VGUI error log is empty but the UI crashed, check if the engine threw a silent exception."
    Write-Host "  * Always isolate syntax breaks in the EOF log before trying to fix logic in the VGUI log."
    Write-Host "--------------------------------------------" -ForegroundColor Yellow
    Write-Host ""
}

function Clear-DebugLogs {
    $scriptDir   = Split-Path -Parent $MyInvocation.MyCommand.Path
    $errorLogPath = Join-Path $scriptDir "vgui_error.log"
    $eofLogPath   = Join-Path $scriptDir "vgui_eof.log"

    Write-Host ""
    Write-Host "--- CLEARING LOGS ---" -ForegroundColor Yellow

    if (Test-Path $errorLogPath) {
        Remove-Item $errorLogPath -Force
        Write-Host "[OK] Cleared vgui_error.log" -ForegroundColor Green
    } else {
        Write-Host "[SKIP] vgui_error.log not found." -ForegroundColor DarkGray
    }

    if (Test-Path $eofLogPath) {
        Remove-Item $eofLogPath -Force
        Write-Host "[OK] Cleared vgui_eof.log" -ForegroundColor Green
    } else {
        Write-Host "[SKIP] vgui_eof.log not found." -ForegroundColor DarkGray
    }

    Write-Host "Workspace is clean. Ready for a fresh diagnostic run." -ForegroundColor Green
    Write-Host ""
}

Write-Host "============================================" -ForegroundColor Cyan
Write-Host "      DEBUGGER HELPER AND UTILITY TOOL      " -ForegroundColor Cyan
Write-Host "============================================" -ForegroundColor Cyan
Write-Host "1. How this architecture works (.ps1 vs .psm1)"
Write-Host "2. General Debugging Tips (VGUI and Lua)"
Write-Host "3. Clear existing log files (Fresh Start)"
Write-Host "============================================" -ForegroundColor Cyan

$choice = Read-Host "Select an option (1-3)"

switch ($choice) {
    '1' { Show-ArchitectureHelp }
    '2' { Show-DebuggingTips }
    '3' { Clear-DebugLogs }
    default { Write-Host "Invalid selection. Exiting." -ForegroundColor Red }
}