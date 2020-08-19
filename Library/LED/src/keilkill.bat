@echo off

echo Cleaning.
echo Cleaning....
del ..\*bak /s 1>nul 2>nul
del ..\*ddk /s  1>nul  2>nul
del ..\*edk /s  1>nul  2>nul
del ..\*lst /s  1>nul  2>nul
del ..\*lnp /s  1>nul  2>nul
del ..\*mpf /s  1>nul  2>nul
del ..\*mpj /s  1>nul  2>nul
del ..\*obj /s  1>nul  2>nul
del ..\*omf /s  1>nul  2>nul
::del ..\*opt /s  ::Deleting JLINK settings is not allowed
del ..\*plg /s  1>nul  2>nul
del ..\*rpt /s  1>nul  2>nul
del ..\*tmp /s  1>nul  2>nul
del ..\*__i /s  1>nul  2>nul
del ..\*crf /s  1>nul  2>nul
del ..\*o /s  1>nul  2>nul
del ..\*d /s  1>nul  2>nul
del ..\*tra /s  1>nul  2>nul
del ..\*dep /s 1>nul  2>nul      
::del JLinkLog.txt /s ::Deleting JLINK log is not allowed
del ..\*iex /s  1>nul  2>nul
del ..\*htm /s  1>nul  2>nul
del ..\*sct /s  1>nul  2>nul
del ..\*map /s  1>nul  2>nul

echo Cleaning_OK

exit
