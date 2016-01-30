#ifndef COMICBOOKSETTINGS_H
#define COMICBOOKSETTINGS_H


#include <QString>
#include "e_reading_style.h"

/********************************************************
*   e_code_cbstp
* -------------------------------------------------------
*   Énumération regroupant les différentes erreurs pouvant
*   être rencontrées en manipulant un fichier .cbstp.
********************************************************/

enum e_code_cbstp
{
    CBSTP_NO_EXISTS,    //  N'existe pas.
    CBSTP_OPEN_FAIL,    //  Erreur lors de l'ouverture.
    CBSTP_INVALID,      //  Invalide.
    CBSTP_OK            //  Valide.
};


/********************************************************
*   ComicBookSettings
* -------------------------------------------------------
*   Classe gérant le chargement/enregistrement des options relatives
*   à un Comic Book. Les options sont sauvegardées dans un fichier
*   .ini contenant au minimum les clés:
*       * Archive: Chemin vers l'archive du Comic Book.
*       * UncompressedFolder: Chemin vers le dossier décompressé contenant
*       les images du Comic Book.
*       * NumberPagesDisplayed: Nombre de pages affichées simultanément.
*       * CurrentPage: Page à laquelle la lecture s'est arrêtée. Fait
*       office de marque page.
*       * ReadingStyle: Indique le sens dans lequel le Comic Book est lu.
********************************************************/

class ComicBookSettings
{
    //  Chemin vers le dossier contenant les fichiers d'options .cbstp.
    static QString m_cbstp_folder ;

    //  Chemin absolu vers l'archive du comic book.
    QString m_path_to_archive ;

    //  Chemin vers le dossier décompressé contenant les images du comic book.
    QString m_path_to_cb ;

    //  Nombre de pages affichées simultanément.
    unsigned int m_number_pages_displayed ;

    //  Numéro de la page visionnée.
    unsigned int m_current_page ;

    //  Sens de lecture du comic book.
    e_reading_style m_reading_style ;

    //  Descr:  Analyse un fichier .cbstp.
    //  Param:  * name: nom du comic book dont il faut analyser le fichier d'options.
    //  Retrn:  Retourne un code de type enum e_error_file (cf début du fichier).
    enum e_code_cbstp parseCBSTP (QString name) ;

    public:
        ComicBookSettings();
        ~ComicBookSettings();

        //  Descr:  Sauvegarde les options de lecture dans un fichier .ini.
        void saveComicBookSettings () ;

        //  Descr:  Charge les options relatives à un comic book depuis un fichier .ini.
        //  Param:  * comic_book_name:  nom du comic book dont il faut charger les options.
        //  Return: Retourne true si le chargement s'est effectué correctement, false sinon.
        bool loadComicBookSettings (QString comic_book_name) ;

        void setPathToArchive(QString path) { m_path_to_archive = path ; }
        void setPathToComicBook(QString path) { m_path_to_cb = path ; }
        void setCurrentPage(unsigned int n) { m_current_page = n ; }
        void setNumberPagesDisplayed(unsigned int n) { m_number_pages_displayed = n ; }
        void setReadingStyle(e_reading_style rs) { m_reading_style = rs ; }

        QString getPathToArchive() const { return m_path_to_archive ; }
        QString getPathToComicBook() const { return m_path_to_cb ; }
        unsigned int getCurrentPage() const { return m_current_page ; }
        unsigned int getNumberPagesDisplayed() const { return m_number_pages_displayed ; }
        e_reading_style getReadingStyle() const { return m_reading_style ; }
};

#endif // COMICBOOKSETTINGS_H
