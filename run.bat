@echo off

:: makefile run.bat version 2025-06-29

if "%1"=="-h" (
	echo Usage:
	echo run - build and run
	echo run make - build which better than make
	echo run clean - clean, build and run
	echo make clean - clean the project
	goto exit
)

if "%1"=="make" (
	make -j%NUMBER_OF_PROCESSORS% -s
	goto exit
)

if "%1"=="clean" (
	make clean
)

make -j%NUMBER_OF_PROCESSORS% -s 
if %errorlevel% neq 0 (
	echo Build failed.
	goto exit
)

timeout 1
::获取目录名
for %%I in ("%cd%") do set "folder=%%~nxI" 
::echo %folder%
STM32_Programmer_CLI -c port=swd shared -d build/%folder%.elf -hardRst -rst -s

:exit