param (
  [string[]]$cla
)

&"g++" -o "bfcompiler.exe" .\main.cpp

&./bfcompiler.exe $cla
