
echo The Current Directory is %cd%

::set CURRENT_PATH=cd

title %cd%

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"

call cd
cmd /k