$bytes = [System.IO.File]::ReadAllBytes('D:\workcode\game\warden\build_errors.log')
$text = [System.Text.Encoding]::Unicode.GetString($bytes)
# Remove ANSI escape codes - these are ESC [ ... m or ESC [ ... K sequences
$clean = [regex]::Replace($text, '\x1b\[[0-9;]*[mK]', '')
# Also remove ESC[01m and similar
$clean = [regex]::Replace($clean, '\x1b\[[0-9;]*m', '')
$clean = [regex]::Replace($clean, '\x1b\[[0-9;]*K', '')
# Save clean version
[System.IO.File]::WriteAllText('D:\workcode\game\warden\build_clean.log', $clean, [System.Text.Encoding]::UTF8)
# Extract fatal errors
$lines = $clean -split "`r?`n"
$errors = @()
foreach ($line in $lines) {
    if ($line -match 'fatal error:\s*(.+?):\s*No such file') {
        $errors += $matches[1].Trim()
    }
}
$errors | Sort-Object -Unique | Out-File -FilePath 'D:\workcode\game\warden\missing_headers.txt' -Encoding utf8
Write-Output "Found $($errors.Count) unique missing headers"
