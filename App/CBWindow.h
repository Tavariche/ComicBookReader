#ifndef CBWINDOW_H
#define CBWINDOW_H


#include <QtWidgets>
#include <QString>
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

    //  Descr:  Ouvre un Comic Book à l'aide de l'explorateur de fichiers.
    //  Param:  * cb_name:  nom du Comic Book à charger.
    void openCB() ;

    //  Descr:  Ouvre un Comic Book depuis la liste des Comic Books récemment consultés.
    //  Param:  * cb_name:  nom du Comic Book à charger.
    void openRecentCB(QString cb_name) ;

    //  Descr:  Ferme un Comic Book en enregistrant ses paramètres de lecture.
    void closeCB() ;

private:
};

#endif // MAINWINDOW_H
