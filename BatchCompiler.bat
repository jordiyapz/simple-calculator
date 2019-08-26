@ECHO off
rem Written by Jordi Yaputra
if exist main.exe (del main.exe)
g++ -o main main.cpp
main.exe
pause