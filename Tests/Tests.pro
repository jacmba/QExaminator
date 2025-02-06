QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testquestion.cpp \
    main.cpp \
    testquestionrepository.cpp

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

HEADERS += \
    testquestionrepository.h \
    tst_testquestion.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Data/release/ -lData
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Data/debug/ -lData
else:unix: LIBS += -L$$OUT_PWD/../Data/ -lData

INCLUDEPATH += $$PWD/../Data
DEPENDPATH += $$PWD/../Data

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Data/release/libData.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Data/debug/libData.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Data/release/Data.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Data/debug/Data.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Data/libData.a

DISTFILES += \
    test_questions.json

# Define the UI build directory
UI_BUILD_PATH = $$OUT_PWD/../UI

# Define the test data file
testdata.files = $$PWD/test_questions.json
testdata.path = $$UI_BUILD_PATH  # Copy it to UI's build directory

# Rename the file to questions.json after copying
QMAKE_POST_LINK += $$QMAKE_COPY $$PWD/test_questions.json $$UI_BUILD_PATH/questions.json $$escape_expand(\\n)

INSTALLS += testdata
