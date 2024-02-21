
## macOS : Command Line Examples - *Qt6 (RGB Color Picker)*

This example uses [Qt](https://wiki.qt.io/Qt_for_Beginners) (6.6.0_1) to implement an RGB color picker.

First, use brew to [install](https://formulae.brew.sh/formula/qt) Qt or ```brew install qt```.

Then [install XCode](https://developer.apple.com/documentation/safari-developer-tools/installing-xcode-and-simulators) (15.2) using the Mac App Store.

This example uses ```qmake``` to generate the Makefile. A convenience ```build.sh``` is included :

```
qmake qt6-rgb_color_picker.pro 
make all
qt6-rgb_color_picker.app/Contents/MacOS/qt6-rgb_color_picker
```

Note the last step of the above, calls compiled application directly [according to the Mac OS Qt app path](https://stackoverflow.com/questions/61669808/how-to-execute-a-qt-app-on-macos-terminal).

The first step of the above uses a *.pro file with qmake, the contents of which are :

```
TEMPLATE = app
TARGET = qt6-rgb_color_picker
QT = core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
SOURCES +=  qt6-rgb_color_picker.cc
```

