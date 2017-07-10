robocopy ..\..\platformer-deps\oxygine-framework\oxygine\third_party\win32\dlls ..\data libcurl.dll
robocopy ..\..\platformer-deps\oxygine-framework\oxygine\third_party\win32\dlls ..\data pthreadVCE2.dll
robocopy ..\..\platformer-deps\oxygine-framework\oxygine\third_party\win32\dlls ..\data zlib.dll
robocopy ..\..\platformer-deps\oxygine-framework\libs ..\data SDL2.dll
robocopy resources ..\data\resources *
set rce=%errorlevel%
if not %rce%==1 exit %rce% else exit 0