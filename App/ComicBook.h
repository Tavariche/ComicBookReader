#ifndef COMICBOOK_H
#define COMICBOOK_H

#include <QObject>
#include <QVector>
#include <QString>
#include "PageManager.h"

/********************************************************
*   ComicBook
* -------------------------------------------------------
*   Représente un comic book.
********************************************************/

class ComicBook:
        public QObject
{
    Q_OBJECT
    
    //  Chemin vers le dossier du comic book qui contient toutes les images. Il doit IMPERATIVEMENT
    //  terminer par un slash '/'.
    QString m_path_to_cb ;
    
    //  Tableau contenant toutes les pages du comic book (par soucis d'optimisation elles sont
    //  chargées/déchargées au besoin).
    QVector<PageManager> m_table_pages ;

    //  Nombre de page à afficher simultanément.
    unsigned int m_number_of_pages_displayed ;
    
    public slots:
        //  Descr:  charge la page index_page ainsi que les adjacentes.
        //  Param:  * index_page:   index de la page à charger.
        void loadPages (unsigned int index_page, bool reload_first_and_last = false) ;

        
    signals:
        // Descr:   Signale la fin du chargement des pages demandées et transmet leurs références sous
        //          forme de tableau.
        // Param:   * buffer:   tableau contenant les adresses des images chargées en mémoire par le
        //                      comic book.
        // Connection:  Connecté au PagesBuffer associé.
        void SG_pagesLoaded (QVector<QVector<PageManager*> > buffer) ;
    
    public:
        ComicBook () ;
        explicit ComicBook (QString path_to_cb) ;
        ~ComicBook () ;
        
        //  Descr:  Spécifie le chemin vers le dossier contenant les images du comic book.
        //  Param:  * path: chemin vers le dossier contenant l'ensemble des images du comic book.
        void setPathToComicBook (QString path) { m_path_to_cb = path ; }

        //  Descr:  met à jour le nombre de pages à afficher simultanément.
        //  Param:  * number:   nombre de pages à afficher simultanément.
        void setNumberOfPagesDisplayed (unsigned int number) { m_number_of_pages_displayed = number ; }
        
        //  Descr:  Demande le calcul des miniatures de l'ensemble des pages du comic book.
        void computeThumbnail () ;
        
        //  Descr:  Retourne le nombre total de pages du comic book.
        unsigned int getNumberOfPages () const { return m_table_pages.size() ; }
};

#endif // COMICBOOK_H
