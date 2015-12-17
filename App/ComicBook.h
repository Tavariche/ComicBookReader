#ifndef COMICBOOK_H
#define COMICBOOK_H

#include <vector>
#include <QString>
#include "PageManager.h"

/********************************************************
*   ComicBook
* -------------------------------------------------------
*   Représente un comic book.
********************************************************/

class ComicBook
{
    Q_OBJECT
    
    //  Chemin vers le dossier du comic book contenant toutes les images.
    QString m_path_to_cb ;
    
    //  Tableau contenant les pages du comic book (par soucis d'optimisation elles sont chargées/déchargées au besoin).
    std::vector<PageManager> m_table_pages ; 
    
    public slots:
        void loadPages (unsigned int index_page) ;
        
    signals:
        // Signale la fin du chargement des pages demandées et transmet leurs références sous forme de tableau.
        void loadingEnded (std::vector<std::vector<PageManager&> > buffer) ;
    
    public:
        ComicBook () ;
        explicit ComicBook (QString path_to_cb) ;
        ~ComicBook () ;
        
        //  Spécifie le chemin vers le dossier contenant les images du comic book.
        void setPathToComicBook (QString path) { m_path_to_cb = path ; }
        
        //  Demande le calcul des miniatures de l'ensemble des pages du comic book.
        void computeThumbnail () ;
        
        //  Retourne le nombre total de pages du comic book.
        unsigned int getNumberOfPages () { return m_table_pages.size() ; }
};

#endif // COMICBOOK_H
