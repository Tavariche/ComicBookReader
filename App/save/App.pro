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
    ThumbnailsPanel.h

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
    ThumbnailsPanel.cpp

CONFIG += c++11

#INCLUDEPATH += D:/Qt/zlib-1.2.8
#LIBS += -LD:/Qt/zlib-1.2.8 -lz
#INCLUDEPATH += D:/Qt/quazip-0.7/quazip
#LIBS += -LD:/Qt/quazip-0.7/quazip/release -lquazip

RESOURCES += \
    ressources.qrc
