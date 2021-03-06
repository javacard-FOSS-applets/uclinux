@echo // Copyright (C) 1996-2005 Markus F.X.J. Oberhumer
@echo //
@echo //   DOS 16-bit
@echo //   Symantec C/C++
@echo //
@echo // NOTE: LZO breaks the optimizer, so we disable optimizations
@echo //
@call b\prepare.bat
@if "%BECHO%"=="n" echo off


set CC=sc -ml
set CF=-w- %CFI%
set LF=%BLIB%

%CC% %CF% -c @b\src.rsp
@if errorlevel 1 goto error
lib %BLIB% /b /c /n /noi @b\dos16\bc.rsp
@if errorlevel 1 goto error

%CC% %CF% -c examples\dict.c
@if errorlevel 1 goto error
%CC% dict.obj %LF%
@if errorlevel 1 goto error
%CC% %CF% -c examples\lzopack.c
@if errorlevel 1 goto error
%CC% lzopack.obj %LF%
@if errorlevel 1 goto error
%CC% %CF% -c examples\precomp.c
@if errorlevel 1 goto error
%CC% precomp.obj %LF%
@if errorlevel 1 goto error
%CC% %CF% -c examples\precomp2.c
@if errorlevel 1 goto error
%CC% precomp2.obj %LF%
@if errorlevel 1 goto error
%CC% %CF% -c examples\simple.c
@if errorlevel 1 goto error
%CC% simple.obj %LF%
@if errorlevel 1 goto error

%CC% %CF% -c lzotest\lzotest.c
@if errorlevel 1 goto error
%CC% lzotest.obj %LF%
@if errorlevel 1 goto error


@call b\done.bat
@goto end
:error
@echo ERROR during build!
:end
@call b\unset.bat
