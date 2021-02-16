set a=%~dp0

cd %a%\..\Obj

If exist ..\..\User\Build copy *.hex ..\..\User\Build 
If exist ..\..\User\Build copy *.bin ..\..\User\Build 
If exist ..\..\User\Build copy *.axf ..\..\User\Build 

cd %a%\..\List

If exist ..\..\User\Build copy *.map ..\..\User\Build
If exist ..\..\User\Build copy *.lst ..\..\User\Build

cd %a%

exit
