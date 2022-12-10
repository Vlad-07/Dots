@echo OFF
call vendor\.bin\premake\premake5.exe vs2022
call Eis\Freezer.bat
PAUSE