CONFIG += c++11

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
    e_page_role.h \
    e_reading_style.h \
    ComicBookSettings.h \
    Uncompression.h

SOURCES += \
    main.cpp \
    CBWindow.cpp \
    PagesContainer.cpp \
    CBScrollArea.cpp \
    UncheckableActionGroup.cpp \
    ComicBook.cpp \
    NavigationManager.cpp \
    PageManager.cpp \
    PagesBuffer.cpp \
    ComicBookSettings.cpp \
    Uncompression.cpp

INCLUDEPATH += E:/documents/Librairies/libarchive-3.1.2

LIBS += -LE:/documents/Librairies/libarchive-3.1.2 -llibarchive
