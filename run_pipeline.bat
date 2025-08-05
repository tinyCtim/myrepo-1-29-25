@echo off
REM Check if input file is provided
IF "%1"=="" (
    echo Usage: run_pipeline.bat inputfile.txt
    goto end
)

REM Define temp file
set TEMPFILE=__temp_output.txt

REM Run first program and redirect output to a temp file
caesar02r_try %1 > %TEMPFILE%

REM Run second program with the temp file as input
caesar02_try %TEMPFILE%

REM Delete the temporary file
del %TEMPFILE%

echo.

:end

