$programPath=""
$inputPath = "C:\Program Files (x86)\OpenCV\build\x86"
$outputPath = ""
$labelsPath = ""
$labels = Get-Content $labelsPath
$personDirs = Get-ChildItem $inputPath | where {$_.Attributes -eq 'Directory'} | % { $_.FullName }
write-host $personDirs
$i = 0
$j= 0
$labelFileContent = ""
foreach($pdir in $personDirs)
{
	$seqDirs = Get-ChildItem $pdir | where {$_.Attributes -eq 'Directory'} | % { $_.FullName }
	foreach($sdir in $seqDirs)
	{
        $arg1 = $sdir
        $arg2 = "-p"
        $arg3 = [io.path]::combine($outputPath, [string]$i)
		& $programPath $arg1 $arg2 $arg3
        $i = $i + 1
        $labelFileContent+= ([string]$i+';'+[string](($labels[$j] -as [int]) - 1) + '`n')
	}
    $j = $j + 1
}