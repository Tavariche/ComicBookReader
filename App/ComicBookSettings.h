#ifndef COMICBOOKSETTINGS_H
#define COMICBOOKSETTINGS_H


#include <QString>
#include "e_reading_style.h"


/********************************************************
*   ComicBookSettings
* -------------------------------------------------------
*   Classe contenant l'ensemble des options relatives
*   à la lecture d'un comic book.
********************************************************/

/// A remplacer par une structure par soucis de légèreté et de
/// simplicité d'utilisation.

class ComicBookSettings
{
    //  Chemin absolu vers l'archive du comic book.
    QString m_path_to_archive ;

    //  Chemin vers le dossier décompressé contenant les images du comic book.
    QString m_path_to_cb ;

    //  Nombre de pages affichées simultanément.
    unsigned int m_number_pages_displayed ;

    //  Nombre de pages total composant le comic book.
    unsigned int m_total_number_pages ;

    //  Numéro de la page visionnée.
    unsigned int m_current_page ;

    //  Sens de lecture du comic book.
    e_reading_style m_reading_style ;

    public:
        ComicBookSettings();
        ~ComicBookSettings();

        //  Descr:  Sauvegarde les options dans un fichier texte d'extension
        //          .cbstp (comic book setup).
        void saveComicBookSettings () ;

        //  Descr:  Charge les options relatives à un comic book depuis un
        //          fichier texte d'extension .cbstp (comic book setup).
        void loadComicBookSettings (QString comic_book_name) ;
};

#endif // COMICBOOKSETTINGS_H
