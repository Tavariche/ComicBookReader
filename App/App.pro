QT += \
    widgets \
    svg \
    concurrent

HEADERS += \
    CBWindow.h \
    PagesContainer.h \
    CBScrollArea.h \
    UncheckableActionGroup.h \
    ComicBook.h \
    NavigationManager.h \
    PageManager.h \
    PagesBuffer.h \
    e_page_role.h

SOURCES += \
    main.cpp \
    CBWindow.cpp \
    PagesContainer.cpp \
    CBScrollArea.cpp \
    UncheckableActionGroup.cpp \
    ComicBook.cpp \
    NavigationManager.cpp \
    PageManager.cpp \
    PagesBuffer.cpp

CONFIG += c++11

INCLUDEPATH += E:/documents/Librairies/zlib-1.2.8
LIBS += -LE:/documents/Librairies/zlib-1.2.8 -lz
INCLUDEPATH += E:/documents/Librairies/quazip-0.7/quazip
LIBS += -LE:/documents/Librairies/quazip-0.7/quazip/release -lquazip
