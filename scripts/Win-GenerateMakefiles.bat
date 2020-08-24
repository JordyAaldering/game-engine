@echo off

pushd ..\
call vendor\premake\premake5.exe gmake2
popd

IF %ERRORLEVEL% NEQ 0 (
    PAUSE
)
