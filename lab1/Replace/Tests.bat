@echo off

REM Путь к тестируемой программе передаётся через 1-й аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Process empty File
%MyProgram% Empty.txt "%TEMP%\output.txt" "search" "replace" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 Passed

REM Process non empty File
%MyProgram% NonEmptyFile.txt "%TEMP%\output.txt" "search" "replace" || goto err
fc NonEmptyFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 Passed

REM Copy missing file should fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" "search" "replace" > nul && goto err
echo Test 3 Passed

REM If output file is not specified, program must fail
%MyProgram% MissingFile.txt > nul && goto err
echo Test 4 Passed

REM If input and output file is not specified, program must fail
%MyProgram% > nul && goto err
echo Test 5 Passed

REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Тесты завершились с ошибкой
:err
echo Test failed
exit /B 1