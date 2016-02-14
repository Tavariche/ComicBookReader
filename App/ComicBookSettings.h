#ifndef COMICBOOKSETTINGS_H
#define COMICBOOKSETTINGS_H


#include <QString>
#include "e_reading_style.h"


/********************************************************
*   ComicBookSettings
* -------------------------------------------------------
*   Classe gérant le chargement/enregistrement des options relatives
*   à un Comic Book. Les options sont sauvegardées dans un fichier
*   .ini contenant au minimum les clés:
*       * Archive: Chemin vers l'archive du Comic Book.
*       * ReadingStyle: Indique le sens dans lequel le Comic Book est lu.
*       * NumberPagesDisplayed: Nombre de pages affichées simultanément.
*       * CurrentPage: Page à laquelle la lecture s'est arrêtée. Fait
*       office de marque page.
********************************************************/

class ComicBookSettings
{
    //  Chemin vers le dossier contenant les fichiers d'options .cbstp.
    static QString m_cbstp_folder ;

    //  Nombre de pages affichées simultanément.
    unsigned int m_number_pages_displayed ;

    //  Numéro de la page visionnée.
    unsigned int m_current_page ;

    //  Sens de lecture du comic book.
    e_reading_style m_reading_style ;

    public:
        ComicBookSettings();

        //  Descr:  Sauvegarde les options de lecture dans un fichier .cbstp.
        //  Param:  * path_to_archive:  chemin vers l'archive du Comic Book.
        void saveSettings (QString path_to_archive) ;

        //  Descr:  Charge les options relatives à un comic book depuis un fichier .ini.
        //  Param:  * comic_book_name:  nom du comic book dont il faut charger les options.
        //  Return: Retourne true si le chargement s'est effectué correctement, false sinon.
        bool loadSettings (QString comic_book_name) ;

        void setCurrentPage(unsigned int n) { m_current_page = n ; }
        void setNumberPagesDisplayed(unsigned int n) { m_number_pages_displayed = n ; }
        void setReadingStyle(e_reading_style rs) { m_reading_style = rs ; }
        static void setCBSTPFolder(QString path) { m_cbstp_folder = path ; }

        unsigned int getCurrentPage() const { return m_current_page ; }
        unsigned int getNumberPagesDisplayed() const { return m_number_pages_displayed ; }
        e_reading_style getReadingStyle() const { return m_reading_style ; }
};

#endif // COMICBOOKSETTINGS_H
