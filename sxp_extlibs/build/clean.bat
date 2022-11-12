@echo off
call clean_int.bat
rd ..\lib /s /q
del vs2008\*.pdb
del vs2010\*.pdb
del vs2012\*.pdb
