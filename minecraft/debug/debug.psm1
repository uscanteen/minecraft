# GUI For Debug, EOF ERRORS / VGUI ERRORS DEBUG
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
function Show-DebugMenu {
    [CmdletBinding()]
    param()


    $errorLogPath = "$PSScriptRoot\vgui_error.log"
    $eofLogPath   = "$PSScriptRoot\vgui_eof.log"


    $form = New-Object System.Windows.Forms.Form
    $form.Text = "Diagnostic Debugger"
    $form.Size = New-Object System.Drawing.Size(800, 600)
    $form.StartPosition = "CenterScreen"
    $form.BackColor = [System.Drawing.Color]::FromArgb(40, 44, 52) # Dark background
    $form.ForeColor = [System.Drawing.Color]::White

    
    $outputBox = New-Object System.Windows.Forms.TextBox
    $outputBox.Multiline = $true
    $outputBox.ScrollBars = "Vertical"
    $outputBox.Location = New-Object System.Drawing.Point(20, 70)
    $outputBox.Size = New-Object System.Drawing.Size(740, 460)
    $outputBox.Font = New-Object System.Drawing.Font("Consolas", 10) # Monospace font for code
    $outputBox.BackColor = [System.Drawing.Color]::FromArgb(30, 30, 30)
    $outputBox.ForeColor = [System.Drawing.Color]::LightGreen
    $outputBox.ReadOnly = $true
    $form.Controls.Add($outputBox)


    $btnError = New-Object System.Windows.Forms.Button
    $btnError.Text = "Check Error log.."
    $btnError.Location = New-Object System.Drawing.Point(20, 20)
    $btnError.Size = New-Object System.Drawing.Size(150, 35)
    $btnError.BackColor = [System.Drawing.Color]::DarkRed
    $btnError.FlatStyle = "Flat"
    $btnError.Add_Click({
        if (Test-Path $errorLogPath) {
            $outputBox.ForeColor = [System.Drawing.Color]::LightCoral
            $outputBox.Text = Get-Content $errorLogPath -Raw
        } else {
            $outputBox.ForeColor = [System.Drawing.Color]::Yellow
            $outputBox.Text = "[WARNING] No standard error log found at:`r`n$errorLogPath"
        }
    })
    $form.Controls.Add($btnError)


    $btnEof = New-Object System.Windows.Forms.Button
    $btnEof.Text = "Check EOF Log..."
    $btnEof.Location = New-Object System.Drawing.Point(190, 20)
    $btnEof.Size = New-Object System.Drawing.Size(150, 35)
    $btnEof.BackColor = [System.Drawing.Color]::DarkGoldenrod
    $btnEof.FlatStyle = "Flat"
    $btnEof.Add_Click({
        if (Test-Path $eofLogPath) {
            $outputBox.ForeColor = [System.Drawing.Color]::LightSkyBlue
            $outputBox.Text = Get-Content $eofLogPath -Raw
        } else {
            $outputBox.ForeColor = [System.Drawing.Color]::Yellow
            $outputBox.Text = "[WARNING] No syntax (EOF) log found at:`r`n$eofLogPath"
        }
    })
    $form.Controls.Add($btnEof)


    $form.ShowDialog() | Out-Null
}


Export-ModuleMember -Function Show-DebugMenu