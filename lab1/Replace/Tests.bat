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
REM If search string is absent in File, output file must be equal to input file
%MyProgram% NonEmptyFile.txt "%TEMP%\output.txt" "search" "replace" || goto err
fc NonEmptyFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 Passed

REM Process missing file should fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" "search" "replace" > nul && goto err
echo Test 3 Passed

REM If output file is not specified, program must fail
%MyProgram% MissingFile.txt > nul && goto err
echo Test 4 Passed

REM If input and output file is not specified, program must fail
%MyProgram% > nul && goto err
echo Test 5 Passed

REM If search string is empty, output file must be equal to input file
%MyProgram% NonEmptyFile.txt "%TEMP%\output.txt" "" "replace" || goto err
fc NonEmptyFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 6 Passed

REM If search string and replace string is empty, output file must be equal to input file
%MyProgram% NonEmptyFile.txt "%TEMP%\output.txt" "" "" || goto err
fc NonEmptyFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 7 Passed

REM If replace string is empty, output file must be equal to expected result
%MyProgram% cat.txt "%TEMP%\output_test8.txt" "cat" "" || goto err
fc test8_expected.txt "%TEMP%\output_test8.txt" > nul || goto err
echo Test 8 Passed

REM Clear spaces test
%MyProgram% cat.txt "%TEMP%\output_test9.txt" " " "" || goto err
fc test9_expected.txt "%TEMP%\output_test9.txt" > nul || goto err
echo Test 9 Passed

REM Process Zero-length-file
%MyProgram% zero-length.txt "%TEMP%\output.txt" " " "" || goto err
fc zero-length.txt "%TEMP%\output.txt" > nul || goto err
echo Test 10 Passed

REM Replace search string 1231234 with replace string in input file, contains sequence 12312312345 and write result to output file
%MyProgram% 12312312345.txt "%TEMP%\output.txt" "1231234" "xxx" || goto err
fc test12_expected.txt "%TEMP%\output.txt" > nul || goto err
echo Test 12 Passed

REM Тесты прошли успешно
echo All tests passed successfuly
exit /B 0

REM Тесты завершились с ошибкой
:err
echo Test failed
exit /B 1