%EMBSYSLIB%\Tools\Image.exe -out image.bin -in ../../Src/Resource/Font/Font_16x24.bin

ST-Link_CLI -P image.bin 0x8180000 -V while_programming
ST-Link_CLI -Rst

pause