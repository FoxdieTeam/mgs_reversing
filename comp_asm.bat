@echo off

del test2.exe
del *.cpe
del *.obj
del *.sym
del *.map

ccpsx -O2 -g -c main.c -omain.obj
asmpsx.exe /l /q rom.s,rom.obj
asmpsx.exe /l /q rom_rwdata.s,rom_rwdata.obj
asmpsx.exe /l /q rom_data.s,rom_data.obj

psylink /m @linker.txt,test2.cpe,asm.sym,asm.map

cpe2exe.exe /CJ test2.cpe
del *.cpe
del *.obj
