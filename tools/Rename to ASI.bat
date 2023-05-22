@echo off

set file=%1
if not exist "%file%" (
	echo "%file%" does not exist!
	goto eof
)

copy %file% *.asi

:eof