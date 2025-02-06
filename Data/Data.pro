QT -= gui

TEMPLATE = lib
CONFIG += staticlib

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    questionrepository.cpp

HEADERS += \
    questionrepository.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

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
