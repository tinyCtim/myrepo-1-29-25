@echo off
set TEMP=__temp
IF "%1" NEQ "" (
 type %1
 echo.
 caesar03 %1 -c > %TEMP%
 type %TEMP%
 echo.
 caesar03 %TEMP% -d
 del %TEMP%
 ) ELSE (
 echo Usage caesar.bat filename
)
echo.

