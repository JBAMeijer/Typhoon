@echo off
setlocal enableextensions enabledelayedexpansion

title ~Typhoon project generator~

set list=vs2022 vs2019 vs2017
echo Choose for which enviroment u want to generate project files for:
set /a counter=1
(for %%a in (%list%) do (
	echo !counter!. %%a
	set /a counter += 1
))
set "a=%globalparam1%"
goto :aCheck
:aPrompt
set /p "a=Enter Choice: "
:aCheck
if not defined a goto :aPrompt

if %a%==1 (
	pushd %~dp0\..\
	call vendor\bin\premake\premake5.exe vs2022
	popd
)
if %a%==2 (
	pushd %~dp0\..\
	call vendor\bin\premake\premake5.exe vs2019
	popd
)
if %a%==3 (
	pushd %~dp0\..\
	call vendor\bin\premake\premake5.exe vs2017
	popd
)
PAUSE