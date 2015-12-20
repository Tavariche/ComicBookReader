#ifndef NAVIGATION_MANAGER_H
#define NAVIGATION_MANAGER_H


#include <QObject>
#include "PagesBuffer.h"


/********************************************************
*   NavigationManager
* -------------------------------------------------------
*   Gère la navigation d'une page à l'autre dans le
*   ComicBook.
********************************************************/

class NavigationManager:
        public QObject
{
    Q_OBJECT
    
    //  Descr: Nombre total de pages du comic book (duplication des données, problématique ?).
    unsigned int m_number_pages ;
    
    //  Descr: Index de la page actuellement affichée.
    unsigned int m_current_page ;

    //  Descr: Buffer contenant les références des images chargées en mémoire.
    PagesBuffer m_pages_buffer ;

    signals:
        // Descr: Demande au comic book associé de charger la page 'page'.
        // Param:
        //      * page: page que le comic book doit charger.
        // Connection: Connecté au comic book associé.
        void SG_goToPage (unsigned int page) ;
    
    public slots:
        void goToLastPage () ;
        void goToFirstPage () ;
        void goToPage (unsigned int page) ;
        void goToNextPage () ;
        void goToPreviousPage () ;
    
    public:
        NavigationManager () ;
        explicit NavigationManager (unsigned int number_pages) ;
        ~NavigationManager () ;
};

#endif // NAVIGATION_MANAGER_H
