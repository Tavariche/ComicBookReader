#ifndef CBWINDOW_H
#define CBWINDOW_H


#include <QtWidgets>
#include "ComicBook.h"
#include "NavigationManager.h"


class CBWindow : public QMainWindow
{
    Q_OBJECT

    ComicBook m_comic_book ;

    NavigationManager m_navigation_manager ;

public:
    explicit CBWindow(QWidget *parent = 0);
    ~CBWindow();

private:
};

#endif // MAINWINDOW_H
