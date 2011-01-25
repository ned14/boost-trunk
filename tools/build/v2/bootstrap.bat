@ECHO OFF

REM Copyright (C) 2009 Vladimir Prus
REM
REM Distributed under the Boost Software License, Version 1.0.
REM (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

ECHO Bootstrapping the build engine
if exist ".\engine\src\bin.ntx86\bjam.exe" del engine\src\bin.ntx86\bjam.exe
if exist ".\engine\src\bin.ntx86_64\bjam.exe" del engine\src\bin.ntx86_64\bjam.exe
cd engine\src

call .\build.bat %* > ..\..\bootstrap.log
@ECHO OFF
cd ..\..

if exist ".\engine\src\bin.ntx86\bjam.exe" (
   copy .\engine\src\bin.ntx86\bjam.exe . > nul
   goto :bjam_built)

if exist ".\engine\src\bin.ntx86_64\bjam.exe" (
   copy .\engine\src\bin.ntx86_64\bjam.exe . > nul
   goto :bjam_built)

goto :bjam_failure

:bjam_built

ECHO.
ECHO Bootstrapping is done. To build, run:
ECHO.
ECHO     .\bjam --prefix=DIR install
ECHO.

goto :end

:bjam_failure

ECHO.
ECHO Failed to bootstrap the build engine
ECHO Please consult bootstrap.log for furter diagnostics.
ECHO.


goto :end

:end
