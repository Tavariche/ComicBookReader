#ifndef NAVIGATION_MANAGER_H
#define NAVIGATION_MANAGER_H

#include "PagesBuffer.h"

/********************************************************
*   NavigationManager
* -------------------------------------------------------
*   Gère la navigation d'une page à l'autre dans le
*   ComicBook.
********************************************************/

class NavigationManager
{
    Q_OBJECT
    
    //  Nombre total de pages du comic book (duplication des données, problématique ?).
    unsigned int m_number_pages ;
    
    //  Index de la page actuellement affichée.
    unsigned int current_page ;

    //  Buffer contenant les références des images chargées en mémoire.
    PagesBuffer m_pages_buffer ;
    
    public slots:
        void goToLastPage () ;
        void goToFirstPage () ;
        void goToPage (unsigned int page) ;
        void goToNextPage () ;
        void goToPreviousPage () ;
    
    public:
        NavigationManager () ;
        ~NavigationManager () ;
};

#endif // NAVIGATION_MANAGER_H
