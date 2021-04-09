@echo off

set defaultIco=E:\Beauty\logo\logo.ico
If "%1"=="" (
    exit
) else (
    set bat=%~dp0%1
    echo %bat%
)
If "%2"=="" (
    exit
) else (
    set exe=%~dp0%2
)
If "%3"=="" (
    set ico=%defaultIco%
) else (
    set ico=%~dp0%3
)
If "%4"=="" (
    Bat2Exe.exe /bat %bat% /exe %exe% /icon %ico% /invisible
) else (
    Bat2Exe.exe /bat %bat% /exe %exe% /icon %ico% /visible
)
