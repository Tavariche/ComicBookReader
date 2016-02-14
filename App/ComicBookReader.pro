CONFIG += c++11

QT += \
    widgets \
    svg \
    concurrent

INCLUDEPATH += E:/documents/Librairies/libarchive-3.1.2

LIBS += -LE:/documents/Librairies/libarchive-3.1.2 -llibarchive

HEADERS += \
    CBScrollArea.h \
    CBWindow.h \
    ComicBook.h \
    ComicBookSettings.h \
    e_page_role.h \
    e_reading_style.h \
    NavigationManager.h \
    PageManager.h \
    PageNbField.h \
    PagesBuffer.h \
    PagesContainer.h \
    ThumbnailsPanel.h \
    UncheckableActionGroup.h \
    Uncompression.h

SOURCES += \
    CBScrollArea.cpp \
    CBWindow.cpp \
    ComicBook.cpp \
    ComicBookSettings.cpp \
    main.cpp \
    NavigationManager.cpp \
    PageManager.cpp \
    PageNbField.cpp \
    PagesBuffer.cpp \
    PagesContainer.cpp \
    ThumbnailsPanel.cpp \
    UncheckableActionGroup.cpp \
    Uncompression.cpp

RESOURCES += \
    icones.qrc
