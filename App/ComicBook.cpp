#include <QDir>
#include <QFileInfo>
#include <QMessageBox> //   Pour debugging.
#include "ComicBook.h"


ComicBook::ComicBook (): QObject()
{
    m_path_to_cb = "" ;
    m_number_of_pages_displayed = 1 ;
    m_table_pages.resize(0);
    m_extension_filter << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" ;
}


ComicBook::ComicBook (QString path_to_cb): QObject()
{
    m_path_to_cb = path_to_cb ;
    m_number_of_pages_displayed = 1 ;
    m_table_pages.resize(0);
    m_extension_filter << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" ;
}


ComicBook::~ComicBook ()
{

}


void ComicBook::initialise ()
{
    if (m_path_to_cb.isEmpty())
    {
        //  Signaler erreur: le chemin vers le comic book n'est pas spécifié.
    }
    else
    {
        //  On compte le nombre de pages qui composent le comic book.
        QDir dir_comic_book (m_path_to_cb) ;
        QFileInfoList list_images = dir_comic_book.entryInfoList (m_extension_filter, QDir::NoFilter, QDir::SortFlag::Name | QDir::SortFlag::DirsLast) ;

        unsigned int counter_pages = 0 ;
        foreach (QFileInfo file_info, list_images)
        {
            if (file_info.isFile()) counter_pages++ ;
            else break; //  Les dossiers sont situés à la fin de la liste. On arrête donc l'algorithme
                        //  dès qu'on rencontre le premier.
        }

        m_table_pages.resize (counter_pages) ;

        //  On précise aux PageManager le nom de leur image associée.
        unsigned int index_page = 0 ;
        foreach (QFileInfo file_info, list_images)
        {
            if (file_info.isFile())
            {
                m_table_pages[index_page].setImageName(file_info.fileName()) ;
                index_page++ ;
            }
            else break; //  Les dossiers sont situés à la fin de la liste. On arrête donc l'algorithme
                        //  dès qu'on rencontre le premier.
        }
    }
}


void ComicBook::loadPages (unsigned int page, bool reload_first_and_last)
{
    //  On charge les pages à visionner, les précédentes et les suivantes.
    unsigned int number_pages_to_load = m_number_of_pages_displayed * 3 ;
    for (unsigned int k=0 ; k<number_pages_to_load ; k++)
    {
        int index_page = (int) (page + k - m_number_of_pages_displayed) ;
        if (index_page >= 0 and index_page < m_table_pages.size())
            m_table_pages[(unsigned int) index_page].load (m_path_to_cb) ;
    }

    if (reload_first_and_last)
    {
        //  On commence par charger les premières pages du comic book.
        for (unsigned int index_page=0 ; index_page<m_number_of_pages_displayed ; index_page++)
        {
            if ((int) index_page < m_table_pages.size())
                m_table_pages[index_page].load (m_path_to_cb) ;
        }

        //  On charge ensuite les dernières pages.
        unsigned int offset = m_table_pages.size() % m_number_of_pages_displayed ;
        if (offset == 0) offset = m_number_of_pages_displayed ;
        for (unsigned int k=0 ; k<offset ; k++)
        {
            int index_page = (int) (m_table_pages.size() - k) ;
            if (index_page > 0)
                m_table_pages[(unsigned int) index_page].load (m_path_to_cb) ;
        }
    }

    ////////////////////////////////////////////////////////////
    ///
    /// Créer un buffer, le remplir et le passer au PagesBuffer.
    ///
    ////////////////////////////////////////////////////////////

    // emit SG_pagesLoaded (buffer) ;
}


void ComicBook::computeThumbnail ()
{

}
