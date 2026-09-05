$bytes = [System.IO.File]::ReadAllBytes('D:\workcode\game\warden\build5_copy.log')
$text = [System.Text.Encoding]::Unicode.GetString($bytes)
$clean = [regex]::Replace($text, '\x1b\[[0-9;]*[mK]', '')
[System.IO.File]::WriteAllText('D:\workcode\game\warden\build5_utf8.log', $clean, [System.Text.Encoding]::UTF8)
$lines = $clean.Split([char[]]@(10))
Write-Output "Lines: $($lines.Count)"
$errors = ($lines | Where-Object { $_ -match 'fatal error' }).Count
$errs = ($lines | Where-Object { $_ -match ' error:' }).Count
$linking = ($lines | Where-Object { $_ -match 'Linking CXX executable' }).Count
Write-Output "Fatal errors: $errors"
Write-Output "Total errors: $errs"
Write-Output "Linking: $linking"
