
@echo off

@REM компиляция и запуск под windows

echo compile project...
g++ ./*.h ./*.cpp -o main

if %errorlevel% neq 0 (
    echo compile error!
    pause
    exit /b 1
)

echo "1.txt" file
type 1.txt

echo File "1.txt" test

main.exe -h 1.txt 1 9

echo File "1000.txt" test
main.exe -h 1000.txt 1 1001

echo File "1000.txt" test
main.exe -h 1000.txt 1 2000

echo File "1000.txt found way" test
main.exe -h 1000.txt 1 80

echo Error Handling... with "main.exe -f file"

main.exe -f file
