if not exist ..\data (
mkdir ..\data
)
if not exist ..\data\libcurl.dll (
copy ..\..\oxygine-framework\oxygine\third_party\win32\dlls\libcurl.dll ..\data\libcurl.dll
)
if not exist ..\data\pthreadVCE2.dll (
copy ..\..\oxygine-framework\oxygine\third_party\win32\dlls\pthreadVCE2.dll ..\data\pthreadVCE2.dll
)

if not exist ..\data\zlib.dll (
copy ..\..\oxygine-framework\oxygine\third_party\win32\dlls\zlib.dll ..\data\zlib.dll
)

if not exist ..\data\SDL2.dll (
copy ..\..\oxygine-framework\libs\SDL2.dll ..\data\SDL2.dll
)