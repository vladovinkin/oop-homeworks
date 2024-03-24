@echo off

REM Путь к тестируемой программе передаётся через 1-й аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Process input with equal date
%MyProgram% < equaldate.txt > "%TEMP%\output.txt" || goto err
fc result_same_week_day.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 Passed

REM Process input with same week day intercalary
%MyProgram% < same_week_day_leap.txt > "%TEMP%\output.txt" || goto err
fc result_same_week_day.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 Passed

REM Process input with same week day non intercalary
%MyProgram% < same_week_day_non_leap.txt > "%TEMP%\output.txt" || goto err
fc result_same_week_day.txt "%TEMP%\output.txt" > nul || goto err
echo Test 3 Passed

REM Process input with different years
%MyProgram% < error.txt > "%TEMP%\output.txt" || goto err
fc result_error.txt "%TEMP%\output.txt" > nul || goto err
echo Test 4 Passed

REM Process input with different week days
%MyProgram% < different_week_day.txt > "%TEMP%\output.txt" || goto err
fc result_different_week_day.txt "%TEMP%\output.txt" > nul || goto err
echo Test 5 Passed

REM Process input with garbage date
%MyProgram% < garbage.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc result_error_date_data.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 Passed

REM Process input with incorrect day
%MyProgram% < incorrect_day.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc result_error_date_data.txt "%TEMP%\output.txt" > nul || goto err
echo Test 7 Passed

REM Process input with incorrect month
%MyProgram% < incorrect_month.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc result_error_date_data.txt "%TEMP%\output.txt" > nul || goto err
echo Test 8 Passed

REM Process input with incorrect year
%MyProgram% < incorrect_year.txt > "%TEMP%\output.txt"
IF NOT ERRORLEVEL 1 goto err
fc result_error_date_data.txt "%TEMP%\output.txt" > nul || goto err
echo Test 9 Passed

REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Тесты завершились с ошибкой
:err
echo Test failed
exit /B 1
