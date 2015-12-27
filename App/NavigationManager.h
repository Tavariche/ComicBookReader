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
    
    //  Descr:  Nombre total de pages du comic book (duplication des données, problématique ?).
    unsigned int m_number_pages ;
    
    //  Descr:  Index de la page actuellement affichée.
    unsigned int m_current_page ;

    //  Nombre de page à afficher simultanément.
    unsigned int m_number_of_pages_displayed ;

    //  Descr:  Buffer contenant les références des images chargées en mémoire.
    PagesBuffer m_pages_buffer ;

    signals:
        // Descr:   Demande au comic book associé de charger la page 'page'.
        // Param:   * page: page que le comic book doit charger.
        //          * reload_first_and_last:    précise si les premières et dernières pages doivent être
        //                                      rechargée.
        // Conex:   Connecté au comic book associé.
        void SG_goToPage (unsigned int page, unsigned int number_of_pages_displayed) ;
    
    public slots:
        void goToLastPage () ;
        void goToFirstPage () ;
        void goToPage (unsigned int page) ;
        void goToNextPage () ;
        void goToPreviousPage () ;

        //  Descr:  Met à jour le nombre de pages total contenues dans le comic book.
        //  Param:  * number_pages: nombre total de pages contenues dans le comic book.
        void setNumberPagesInComicBook (unsigned int number_pages) { m_number_pages = number_pages ; }

        //  Descr:  Met à jour le nombre de pages affichées simultanément.
        //  Param:  * number_pages: nombre de pages à afficher simultanément.
        void setNumberPagesDisplayed (unsigned int number_pages) ;
    
    public:
        NavigationManager () ;
        explicit NavigationManager (unsigned int number_pages) ;
        ~NavigationManager () ;

        PagesBuffer* getPagesBuffer () { return &m_pages_buffer ; }
};

#endif // NAVIGATION_MANAGER_H
