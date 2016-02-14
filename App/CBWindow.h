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
    ComicBook* m_comic_book ;
    NavigationManager* m_navigation_manager ;
    QDockWidget* m_dockMiniatures;


public slots:
    void displayDockMiniatures(bool display = true);

    //  Descr:  Ouvre un Comic Book à l'aide de l'explorateur de fichiers.
    void openCB() ;

public:
    explicit CBWindow(QWidget *parent = 0);
    ~CBWindow();

    //  Descr:  Ferme un Comic Book en enregistrant ses paramètres de lecture.
    void closeCB() ;

private:
};

#endif // MAINWINDOW_H
