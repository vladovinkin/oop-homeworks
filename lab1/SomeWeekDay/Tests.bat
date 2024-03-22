@echo off

REM Путь к тестируемой программе передаётся через 1-й аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Process empty input
%MyProgram% < empty.txt >> "%TEMP%\output.txt" || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 Passed


REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Тесты завершились с ошибкой
:err
echo Test failed
exit /B 1