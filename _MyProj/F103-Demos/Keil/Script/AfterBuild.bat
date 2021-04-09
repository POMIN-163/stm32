fromelf --text -c -o "$L@L.asm" "#L"
fromelf --bin -o "$L@L.bin" "#L"

set a=%~dp0

cd %a%\..\Obj

If exist ..\..\User\Build copy *.hex ..\..\User\Build\*.hex
If exist ..\..\User\Build copy *.bin ..\..\User\Build\*.bin
If exist ..\..\User\Build copy *.axf ..\..\User\Build\*.axf
If exist ..\..\User\Build copy *.asm ..\..\User\Build\Asm\*.asm

cd %a%\..\List

If exist ..\..\User\Build copy *.map ..\..\User\Build\*.map
:: If exist ..\..\User\Build copy *.lst ..\..\User\Build\*.lst
If exist ..\..\User\Build copy *.txt ..\..\User\Build\Asm\*.asm

cd %a%

exit
