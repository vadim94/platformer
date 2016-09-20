robocopy ..\..\oxygine-framework\oxygine\third_party\win32\dlls ..\data libcurl.dll
robocopy ..\..\oxygine-framework\oxygine\third_party\win32\dlls ..\data pthreadVCE2.dll
robocopy ..\..\oxygine-framework\oxygine\third_party\win32\dlls ..\data zlib.dll
robocopy ..\..\oxygine-framework\libs ..\data SDL2.dll
robocopy resources ..\data\resources *
set rce=%errorlevel%
if not %rce%==1 exit %rce% else exit 0