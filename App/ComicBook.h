#ifndef COMICBOOK_H
#define COMICBOOK_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QMessageBox>  //  Pour debugging.
#include "PageManager.h"
#include "ComicBookSettings.h"

/********************************************************
*   ComicBook
* -------------------------------------------------------
*   Représente un comic book.
********************************************************/

class ComicBook:
        public QObject
{
    Q_OBJECT

    //  Chemin vers l'archive du comic book qui contient toutes les images compressées.
    QString m_path_to_archive ;
    
    //  Chemin vers le dossier du comic book qui contient toutes les images.
    QString m_path_to_cb ;

    //  Indique si le ComicBook a été initialisé correctement.
    bool m_initialised ;
    
    //  Tableau contenant toutes les pages du comic book (par soucis d'optimisation elles sont
    //  chargées/déchargées au besoin).
    QVector<PageManager> m_table_pages ;

    //  Liste contenant les extensions des images ouvrables par le comic book.
    static QStringList m_extension_filter ;

    signals:
        //  Descr:  Signale la fin du chargement des pages demandées et transmet leurs références sous
        //          forme de tableau.
        //  Param:  * buffer:   tableau contenant les adresses des images chargées en mémoire par le
        //                      comic book.
        //  Conex:  Connecté au PagesBuffer associé.
        void SG_pagesLoaded (QVector<QVector<PageManager*> > buffer) ;

        //  Descr:  Signale que le calcule du nombre total de pages contenues dans le comic book a été
        //          effectué.
        //  Param:  * number_pages: nombre total de pages contenues dans le comic book.
        //  Conex:  Connecté au NavigationManager associé.
        void SG_numberPagesComputed (unsigned int number_pages) ;
    
    public slots:
        //  Descr:  Charge la page index_page ainsi que les adjacentes.
        //  Param:  * index_page:   index de la page à charger.
        //          * reload_first_and_last:    précise si les premières et dernières pages doivent être
        //                                      rechargée.
        void loadPages (unsigned int index_page, unsigned int number_of_pages_displayed) ;
    
    public:
        ComicBook () ;

        //  Descr:  Destructeur de l'objet ComicBook. On en profite pour sauvegarder les options de lecture
        //          dans un fichier.
        ~ComicBook () ;

        //  Descr:  Décompresse l'archive contenant les images du comic book et met à jour la variable m_path_to_cb.
        void uncompressComicBook () ;

        //  Descr:  Initialise les PageManager en leur indiquant le nom de leur image associée.
        //          Nécessite que m_path_to_cb soit spécifié.
        void initialise () ;

        //  Descr:  Spécifie le chemin vers l'archive contenant les images compressées du comic book.
        //  Param:  * path: chemin vers le dossier contenant l'ensemble des images du comic book.
        void setPathToArchive (QString path) { m_path_to_archive = path ; }

        //  Descr:  Spécifie le chemin vers le dossier contenant les images du comic book.
        //  Param:  * path: chemin vers le dossier contenant l'ensemble des images du comic book.
        void setPathToComicBook (QString path) { m_path_to_cb = path ; }
        
        //  Descr:  Demande le calcul des miniatures de l'ensemble des pages du comic book.
        void computeThumbnail () ;
        
        unsigned int getNumberOfPages () const { return m_table_pages.size() ; }
        QString getPathToArchive() const { return m_path_to_archive ; }
};

#endif // COMICBOOK_H
