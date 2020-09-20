@echo off

echo Cleaning....

copy %~dp0\AC5\*.axf %~dp0\*.axf 1>nul  2>nul
copy %~dp0\AC5\*.hex %~dp0\*.hex 1>nul  2>nul

del /q %~dp0\AC5
copy %~dp0\*.hex %~dp0\AC5\*.hex 1>nul  2>nul
copy %~dp0\*.axf %~dp0\AC5\*.axf 1>nul  2>nul

echo Cleaning_OK

::pause

exit
