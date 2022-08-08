::@ECHO OFF
::TODO::
::Add Mkdir command for when you start to release this garbage to the world

::NOTES::
::/EHsc is an exception handler warning thing more here...
::http://www.cplusplus.com/doc/tutorial/exceptions/
::To debug use /Zi

::doskey SDL2="C:\libs\SDL2-devel-2.0.22-VC\SDL2-2.0.22\include"

::INCLUDE DIRECTORIES
set SDL2="C:\libs\SDL2-devel-2.0.22-VC\SDL2-2.0.22\include"
set SDL2_image="C:\libs\SDL2_image-devel-2.0.5-VC\SDL2_image-2.0.5\include"
set SDL2_ttf="C:\libs\SDL2_ttf-2.0.18\include"
set SDL2_mixer="C:\libs\SDL2_mixer-2.0.4\include"
set glm="C:\dev\SAIL\sail_engine\external\glm"
::set lua53="C:\libs\LUA-5.3.6_WIN32" 
::set luaINCLUDE="C:\dev\pikuma\SAIL\include\lua"

::LIBRARY DIRECTORIES
set SDL2_lib="C:\libs\SDL2-devel-2.0.22-VC\SDL2-2.0.22\lib\x86"
set SDL2_image_lib="C:\libs\SDL2_image-devel-2.0.5-VC\SDL2_image-2.0.5\lib\x86"
set SDL2_ttf_lib="C:\libs\SDL2_ttf-2.0.18\lib\x86"
set SDL2_mixer_lib="C:\libs\SDL2_mixer-2.0.4\lib\x86"
set lua536_lib="C:\libs\LUA-5.3.6_WIN32"

::DEBUG COMPILE?
:: cl.exe /Zi /EHsc /nologo /FeC:\dev\SAIL\sail_engine\src\Game.exe C:\dev\SAIL\sail_engine\src\Game.cpp

::INCLUDE SUB-DIRECTORIES

::SOURCE FILES
set SRC_FILES=../src/*.cpp ../src/ECS/*.cpp ../src/ECSComponents/*.cpp ../src/testSource/*.cpp

call cl /Zi /EHsc /nologo /Fe %SRC_FILES% /std:c++17 /EHsc -W4 -I%SDL2% -I%SDL2_image% -I%SDL2_ttf% -I%SDL2_mixer% -I%glm% -link -LIBPATH:%SDL2_lib% -LIBPATH:%SDL2_image_lib% -LIBPATH:%SDL2_ttf_lib% -LIBPATH:%SDL2_mixer_lib% -LIBPATH:%lua536_lib% user32.lib SDL2main.lib SDL2.lib SDL2_image.lib SDL2_ttf.lib liblua53.a shell32.lib /SUBSYSTEM:CONSOLE /out:../debug/main.exe
