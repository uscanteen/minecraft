# module.psm1 For Debugging
function Invoke-VguiProcess {
    [CmdletBinding()]
    param()

    try {
        Write-Host "Initializing VGUI Enviroment..." -ForegroundColor Cyan

        Write-Host "VGUI Executed Seccesfully!" -ForegroundColor Green
    }
    catch {
        $ErrorRecord = $_
        $logPath = "$PSScriptRoot\logs\VGUI_Error.log"

        Write-Error "A VGUI error occurred: $($ErrorRecord.Exception.Message)"

        $logEntry = @"
        =====================================
        Date: $(Get-Date)
        Error Code: F E U
        Exception: $($ErrorRecord.Exception.Message)
        Stack Trace: $($ErrorRecord.StackTrace)
        =====================================
"@
        Add-Content -Path $logPath -Value $logEntry
        Write-Warning "Detailed error log saved to: $logPath"
    }
}

Export-ModuleMember -Function Invoke-VguiProcess