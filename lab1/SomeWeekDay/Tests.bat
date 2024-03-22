@echo off

REM ���� � ����������� ��������� ��������� ����� 1-� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Process empty input
%MyProgram% < empty.txt >> "%TEMP%\output.txt" || goto err
fc empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 Passed


REM ����� ������ �������
echo All tests passed successfuly
exit /B 0

REM ����� ����������� � �������
:err
echo Test failed
exit /B 1