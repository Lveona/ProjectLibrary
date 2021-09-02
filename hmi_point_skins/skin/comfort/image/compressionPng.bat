:: compressionPng.bat
echo off & setlocal EnableDelayedExpansion  
for /f "delims=" %%i in ('"dir /a/s/b/on *.png*"') do (  
set file=%%~fi  
set file=!file:/=/!  
D:\pngquanti\pngquanti.exe -f --ext .png !file!
echo !file! >> list.txt  
) 