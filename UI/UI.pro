QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    mainwindow.cpp \
    main.cpp

HEADERS += \
    mainwindow.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Data/release/ -lData
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Data/debug/ -lData
else:unix: LIBS += -L$$OUT_PWD/../Data/ -lData

INCLUDEPATH += $$PWD/../Data
DEPENDPATH += $$PWD/../Data

TARGET = QExaminator

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Data/release/libData.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Data/debug/libData.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Data/release/Data.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Data/debug/Data.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Data/libData.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Domain/release/ -lDomain
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Domain/debug/ -lDomain
else:unix: LIBS += -L$$OUT_PWD/../Domain/ -lDomain

INCLUDEPATH += $$PWD/../Domain
DEPENDPATH += $$PWD/../Domain

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Domain/release/libDomain.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Domain/debug/libDomain.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Domain/release/Domain.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Domain/debug/Domain.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Domain/libDomain.a
