#ifndef HOWTOINSTALLQWT_H
#define HOWTOINSTALLQWT_H

/*

1. Download and install QT 5.0.1 (MinGw) to: "C:\Qt\Qt5.0.1"
2. Download and extract Qwt 6.1 RC3 to: "C:\qwt-6.1-rc3"
3. Add "C:\Qt\Qt5.0.1\5.0.1\mingw47_32\bin" to your systems path variable (qmake.exe is located here)
4. Add "C:\Qt\Qt5.0.1\Tools\MinGW\bin" to your systems path variable (mingw32-make.exe is located here)
5. Open a command line (cmd) and navigate to: "C:\qwt-6.1-rc3"
6. Type: "qmake" (This command won't prompt any msg so don't worry)
7. Type: "mingw32-make" (Compiles the whole project with examples; this will take a while so be patient)
8. Type: "mingw32-make install" (This installs qwt to the directory set in "C:\qwt-6.1-rc3\qwtconfig.pri"; the default location is "C:/Qwt-$$QWT_VERSION-rc3" -> "C:\Qwt-6.1.0-rc3\")
9. Add "C:\Qwt-6.1.0-rc3\lib" to your systems path variable
10. Add a User variable named "QT_PLUGIN_PATH" with the following path "C:\Qwt-6.1.0-rc3\plugins"
11. Add a User variable named "QMAKEFEATURES" with the following path "C:\Qwt-6.1.0-rc3\features"
12. Start Qt Creator
13. Create a new project: File -> New File or Project ... -> Applications -> Qt Gui Application -> Choose
14. Name it "Test"
15. Create the project in the following directory: "C:\workspace"
16. Open file "Test.pro"
17. Add "Config += qwt" at the bottom
18. Open the main.c of the project and delete all its content.
19. Paste the following in the main.c (This is the qwt example "simpleplot"):

*/


//Lib used with the current Project (13/12/2017) is the qwt-6.1.3
//training https://habrahabr.ru/post/211204/


#endif // HOWTOINSTALLQWT_H
