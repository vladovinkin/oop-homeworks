@echo off

REM Путь к тестируемой программе передаётся через 1-й аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Process empty File
%MyProgram% _empty.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc __result_read_error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 Passed

REM Process standart matrix
%MyProgram% _matrix.txt > "%TEMP%\output.txt" || goto err
fc __result_matrix.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 Passed

REM Process garbage matrix
%MyProgram% _garbage.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc __result_data_error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 Passed

REM Process matrix with correct 1 line data
%MyProgram% _matrix_1line.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc __result_read_error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 Passed

REM Process matrix with correct 2 line data
%MyProgram% _matrix_2line.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc __result_read_error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 5 Passed

REM Process matrix with incomplete data
%MyProgram% _matrix_incomplete.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc __result_data_error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 Passed

REM Process matrix with error data type in last element
%MyProgram% _matrix_with_data_error.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc __result_data_error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 7 Passed

REM Process 0-matrix
%MyProgram% _matrix0.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc __result_det0.txt "%TEMP%\output.txt" > nul || goto err
echo Test 8 Passed

REM Process E-matrix
%MyProgram% _matrix1.txt > "%TEMP%\output.txt" || goto err
fc __result_matrix1.txt "%TEMP%\output.txt" > nul || goto err
echo Test 9 Passed

REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Тесты завершились с ошибкой
:err
echo Test failed
exit /B 1