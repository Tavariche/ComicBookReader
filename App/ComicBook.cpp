#include "ComicBook.h"


ComicBook::ComicBook (): QObject()
{
    m_path_to_cb = "" ;
    m_number_of_pages_displayed = 1 ;
    m_table_pages.resize(0);
}


ComicBook::ComicBook (QString path_to_cb): QObject()
{
    m_path_to_cb = path_to_cb ;
    m_number_of_pages_displayed = 1 ;
    m_table_pages.resize(0);
}


ComicBook::~ComicBook ()
{

}


void ComicBook::loadPages (unsigned int page, bool reload_first_and_last)
{
    //  On charge les pages à visionner, les précédentes et les suivantes.
    unsigned int number_pages_to_load = m_number_of_pages_displayed * 3 ;
    for (unsigned int k=0 ; k<number_pages_to_load ; k++)
    {
        int index_page = (int) (page + k - m_number_of_pages_displayed) ;
        if (index_page < m_table_pages.size())
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
