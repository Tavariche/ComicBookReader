#ifndef NAVIGATION_MANAGER_H
#define NAVIGATION_MANAGER_H


#include <QObject>
#include "PagesBuffer.h"
#include "ComicBookSettings.h"
#include "e_reading_style.h"


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

    //  Descr:  Indique le sens de lecture du Comic Book.
    e_reading_style m_reading_style ;

    signals:
        // Descr:   Demande au comic book associé de charger la page 'page'.
        // Param:   * page: page que le comic book doit charger.
        //          * reload_first_and_last:    précise si les premières et dernières pages doivent être
        //                                      rechargée.
        // Conex:   Connecté au comic book associé.
        void SG_goToPage (int page, int number_of_pages_displayed) ;
    
    public slots:
        void goToLastPage () ;
        void goToFirstPage () ;
        void goToPage (int page) ;
        void goToNextPage () ;
        void goToPreviousPage () ;

        //  Descr:  Met à jour le nombre de pages total contenues dans le comic book.
        //  Param:  * number_pages: nombre total de pages contenues dans le comic book.
        void setNumberPagesInComicBook (unsigned int number_pages) ;

        //  Descr:  Met à jour le nombre de pages affichées simultanément.
        //  Param:  * number_pages: nombre de pages à afficher simultanément.
        void setNumberPagesDisplayed (unsigned int number_pages) ;

        //  Descr:  slots adaptés à l'utilisation des actions
        void setNumberPagesDisplayed1 () {setNumberPagesDisplayed(1);}
        void setNumberPagesDisplayed2 () {setNumberPagesDisplayed(2);}
        void setNumberPagesDisplayed3 () {setNumberPagesDisplayed(3);}
        void setNumberPagesDisplayed4 () {setNumberPagesDisplayed(4);}
    
    public:
        NavigationManager () ;
        explicit NavigationManager (unsigned int number_pages) ;
        ~NavigationManager () ;

        void flush () ;

        void setCurrentPage(unsigned int current_page) { m_current_page = current_page ; }
        void setReadingStyle(e_reading_style rs) { m_reading_style = rs ; }

        PagesBuffer* getPagesBuffer () { return &m_pages_buffer ; }
        unsigned int getNumberOfPagesDisplayed() const { return m_number_of_pages_displayed ; }
        unsigned int getCurrentPage() const { return m_current_page ; }
        e_reading_style getReadingStyle() const { return m_reading_style ; }
};

#endif // NAVIGATION_MANAGER_H
