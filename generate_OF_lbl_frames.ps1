$programPath="C:\Users\Adam\Documents\Visual Studio 2013\Projects\SexRecognizer.Biometrics\x64\Debug\SexRecognizer.Client.exe"
$inputPath = "C:\Users\Adam\Pictures\inz-klatki-high\test"
$outputPath = "C:\Users\Adam\Pictures\inz-klatki-high\test_output\"
$labelsPath = "C:\Users\Adam\Pictures\inz-klatki-high\tumgaid_labels\allgender.txt"
$labelsOutputPath = "C:\Users\Adam\Pictures\inz-klatki-high\test\labels.txt"
$labels = Get-Content $labelsPath
$personDirs = Get-ChildItem $inputPath | where {$_.Attributes -eq 'Directory'} | % { $_.FullName }

New-Item $labelsOutputPath -type file

write-host $personDirs
$i = 0
$j= 0
$labelFileContent = ""
foreach($pdir in $personDirs)
{
	$seqDirs = Get-ChildItem $pdir | where {$_.Attributes -eq 'Directory'} | % { $_.FullName }
	foreach($sdir in $seqDirs)
	{
        write-host $sdir
        $arg1 = $sdir
        $arg2 = "-p"
        $arg3 = [io.path]::combine($outputPath, [string]$i)
        if ($arg1.StartsWith("Script"))
        New-Item $arg3 -type directory
		& $programPath $arg1 $arg2 $arg3
        $i = $i + 1
        $labelFileContent+= ([string]$i+';'+[string](($labels[$j] -as [int]) - 1) + '`n')
	}
    $j = $j + 1
}

$labelFileContent | Out-File $labelsOutputPath