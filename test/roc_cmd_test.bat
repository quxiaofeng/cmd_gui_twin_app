set path=..\qt;%PATH%
if not exist ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\release\roc_cmd.exe goto NoReleaseCmd
start ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\release\roc_cmd.exe test1.png result\result1.bmp
start ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\release\roc_cmd.exe test1.png result1.bmp
start ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\release\roc_cmd.exe test1.png
start ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\release\roc_cmd.exe test1.png result1.bmp result1.bmp2
start ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\release\roc_cmd.exe test1.png
:NoReleaseCmd

if not exist ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\debug\roc_cmd.exe goto NoDebugCmd
start ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\debug\roc_cmd.exe test2.png ..\test\result\result2.bmp
start ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\debug\roc_cmd.exe test2.png result2.bmp
start ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\debug\roc_cmd.exe test2.png
start ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\debug\roc_cmd.exe test2.png result2.bmp result2.bmp2
start ..\roc_cmd-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\debug\roc_cmd.exe test2.png
:NoDebugCmd

if not exist ..\roc_gui-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\release\roc_gui.exe goto NoReleaseGui
start ..\roc_gui-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\release\roc_gui.exe test1.png
:NoReleaseGui

if not exist ..\roc_gui-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\debug\roc_gui.exe goto NoDebugGui
start ..\roc_gui-build-desktop-Qt_4_8_1_for_Desktop_-_MSVC2010__Qt_SDK____\debug\roc_gui.exe test1.png
:NoDebugGui
