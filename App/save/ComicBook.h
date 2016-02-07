#ifndef COMICBOOK_H
#define COMICBOOK_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QMessageBox>  //  Pour debugging.
#include "PageManager.h"

#define THUMBNAIL_RATIO 2 // Par défaut un thumbnail est au plus 1,5 fois plus haut que large

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
    QStringList m_extension_filter ;

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

        void SG_initialised();
    
    public slots:
        //  Descr:  Charge la page index_page ainsi que les adjacentes.
        //  Param:  * index_page:   index de la page à charger.
        //          * reload_first_and_last:    précise si les premières et dernières pages doivent être
        //                                      rechargée.
        void loadPages (unsigned int index_page, unsigned int number_of_pages_displayed) ;

        //  DEBUG   DEBUG   DEBUG   DEBUG   DEBUG   //
        //  Descr:  Affiche l'état des PageManager dans une message box.
        //          Util pour le debugging.
//        void displayPageManagerState ()
//        {
//            QString s = "Etats des PageManager:\n" ;
//            for (int i=0 ; i<m_table_pages.size() ; i++)
//            {
//                if (m_table_pages[i].isLoaded()) s += "[X]\n" ;
//                else s += "[ ]\n" ;
//            }
//            QMessageBox::information(0, "DEBUGGING", s) ;
//        }
        //  DEBUG   DEBUG   DEBUG   DEBUG   DEBUG   //
    
    public:
        ComicBook () ;
        ~ComicBook () ;

        //  Descr:  Décompresse l'archive contenant les images du comic book et met à jour la variable m_path_to_cb.
        ///void uncompressArchive () ;

        //  Descr:  Initialise les PageManager en leur indiquant leur nom. Nécessite que m_path_to_cb
        //          soit spécifié.
        void initialise () ;

        //  Descr:  Spécifie le chemin vers l'archive contenant les images compressées du comic book.
        //  Param:  * path: chemin vers le dossier contenant l'ensemble des images du comic book.
        void setPathToArchive (QString path) { m_path_to_archive = path ; }
        
        //  Descr:  Spécifie le chemin vers le dossier contenant les images du comic book.
        //  Param:  * path: chemin vers le dossier contenant l'ensemble des images du comic book.
        void setPathToComicBook (QString path) { m_path_to_cb = path ; }
        
        //  Descr:  Demande le calcul des miniatures de l'ensemble des pages du comic book.
        void computeThumbnail (int width, int height = -1) ;
        
        //  Descr:  Retourne le nombre total de pages du comic book.
        uint getNumberOfPages () const { return m_table_pages.size() ; }

        //  Descr: Retourne un pointeur sur le pageManager voulu
        PageManager* getPage(uint i){
            qDebug() << "COUCOU  " << i << " " << getNumberOfPages();
            if(i == 0 || i > getNumberOfPages()) return 0;
            else{
                qDebug() << "COUCOU  " << i;
                return &m_table_pages[i-1];
            }
        }
};

#endif // COMICBOOK_H
