#include "ComicBookSettings.h"
#include <QMessageBox>

ComicBookSettings::ComicBookSettings ()
{
    m_path_to_archive = "" ;
    m_path_to_cb = "" ;
    m_number_pages_displayed = 1 ;
    m_total_number_pages = 0 ;
    m_current_page = 0 ;
    m_reading_style = e_reading_style::OCCIDENTAL ;
}


ComicBookSettings::~ComicBookSettings()
{

}


void ComicBookSettings::saveComicBookSettings ()
{
    //  Sérialiser cet objet.

    //  Écrire la chaine dans un fichier texte.
}


void ComicBookSettings::loadComicBookSettings (QString comic_book_name)
{
    //  Ouvrir le fichier texte de nom comic_book_name et d'extension .cbstp.

    //  Désérialiser la chaine en initialisant l'objet avec la chaine contenue
    //  dans le fichier.

    //  Initialiser le comic book et le page manager associés.
}
