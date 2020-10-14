@echo off
pushd %~dp0\..\
call 3rdPart\premake\bin\premake5.exe vs2019
popd
PAUSE