@echo off
echo build %cd%
echo -----

set EXE=%EMBSYSLIB%\Tools\Bmp2Font.exe

%EXE% -F Font_16x24   -w 16 -h 24 -f 32 -l 127

echo.
