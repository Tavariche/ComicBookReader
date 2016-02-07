#ifndef CBWINDOW_H
#define CBWINDOW_H


#include <QtWidgets>
#include "ComicBook.h"
#include "PagesContainer.h"
#include "ThumbnailsPanel.h"
#include "NavigationManager.h"


#define DEFAULT_PAGE_NUMBER 1
#define THUMBNAILS_PANEL_MIN_WIDTH 130

class CBWindow : public QMainWindow
{
    Q_OBJECT

private :
    PagesContainer* pagesContainer;
    //Impossible pour une PUTAIN de raison inexpliquée...
    ComicBook* comic_book ;
    NavigationManager* navigation_manager ;
    QDockWidget* dockMiniatures;


public slots:
    void displayDockMiniatures(bool display = true);

public:
    explicit CBWindow(QWidget *parent = 0);
    ~CBWindow();

private:
};

#endif // MAINWINDOW_H
