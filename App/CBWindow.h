#ifndef CBWINDOW_H
#define CBWINDOW_H


#include <QtWidgets>
#include "ComicBook.h"
#include "NavigationManager.h"


class CBWindow : public QMainWindow
{
    Q_OBJECT

    ComicBook comic_book ;

    NavigationManager navigation_manager ;

public:
    explicit CBWindow(QWidget *parent = 0);
    ~CBWindow();

private:
};

#endif // MAINWINDOW_H
