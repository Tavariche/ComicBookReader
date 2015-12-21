#include <QDir>
#include <QFileInfo>
#include <QMessageBox>  //  Pour debugging.
#include "e_page_role.h"
#include "ComicBook.h"


ComicBook::ComicBook (): QObject()
{
    m_path_to_cb = "" ;
    m_table_pages.resize(0);
    m_extension_filter << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" ;
}


ComicBook::ComicBook (QString path_to_cb): QObject()
{
    m_path_to_cb = path_to_cb ;
    m_table_pages.resize(0);
    m_extension_filter << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" ;
}


ComicBook::~ComicBook ()
{

}


void ComicBook::initialise ()   //  Testée --> Fonctionnelle.
{
    if (m_path_to_cb.isEmpty())
    {
        QMessageBox::critical(0, "Erreur - Initialisation Comic Book", "Un Comic Book ne peut pas être initialisé sans avoir\nde chemin spécifié.") ;
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

        emit SG_numberPagesComputed (counter_pages) ;   //  On signale que le nombre total de pages a été calculé.

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


void ComicBook::loadPages (unsigned int page, unsigned int number_of_pages_displayed, bool reload_first_and_last)   //  Testée --> Fonctionnelle.
{
    unsigned int index_first_current_page = (page/number_of_pages_displayed)*number_of_pages_displayed ;
    //  On charge les pages à visionner, les précédentes et les suivantes.
    unsigned int number_pages_to_load = number_of_pages_displayed * 3 ;
    for (unsigned int k=0 ; k<number_pages_to_load ; k++)
    {
        int index_page = (int) (index_first_current_page + k - number_of_pages_displayed) ;
        if (index_page >= 0 and index_page < m_table_pages.size())
            m_table_pages[(unsigned int) index_page].load (m_path_to_cb) ;
    }

    if (reload_first_and_last)
    {

        //  On commence par charger les premières pages du comic book.
        for (unsigned int index_page=0 ; index_page<number_of_pages_displayed ; index_page++)
        {
            if ((int) index_page < m_table_pages.size())
                m_table_pages[index_page].load (m_path_to_cb) ;
        }

        //  On charge ensuite les dernières pages.
        int offset = m_table_pages.size() % number_of_pages_displayed ;
        if (offset == 0) offset = number_of_pages_displayed ;
        for (int k=0 ; k<offset ; k++)
        {
            int index_page = m_table_pages.size() - k - 1 ;
            if (index_page > 0)
                m_table_pages[index_page].load (m_path_to_cb) ;
        }
    }

    // Création et remplissage d'un buffer temporaire avant de mettre à jour le PagesBuffer.
    QVector<QVector<PageManager*> > buffer (5) ;
    for (int i=0 ; i<5 ; i++) buffer[i].resize (number_of_pages_displayed) ;

    //  On commence par placer dans le buffer les références des pages actuellement visionnées.
    for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
    {
        if ((int)(i + page) < m_table_pages.size()) buffer[CURRENT][i] = &(m_table_pages[i + page]) ;
        else buffer[CURRENT][i] = &(m_table_pages[m_table_pages.size() - 1]) ;
    }

    //  On place ensuite les références des pages suivantes et précédentes.
    for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
    {
        if ((int)(i + page + number_of_pages_displayed) < m_table_pages.size()) buffer[NEXT][i] = &(m_table_pages[i + page + number_of_pages_displayed]) ;
        else buffer[NEXT][i] = &(m_table_pages[m_table_pages.size() - 1]) ;
    }

    for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
    {
        if ((int)(i + page - number_of_pages_displayed) > 0) buffer[PREVIOUS][i] = &(m_table_pages[i + page - number_of_pages_displayed]) ;
        else buffer[PREVIOUS][i] = &(m_table_pages[0]) ;
    }

    //  On place enfin dans le buffer les références des pages du début et de la fin du comic book.
    for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
    {
        if ((int)i < m_table_pages.size()) buffer[FIRST][i] = &(m_table_pages[i]) ;
        else buffer[FIRST][i] = &(m_table_pages[m_table_pages.size() - 1]) ;
    }

    unsigned int offset = m_table_pages.size() % number_of_pages_displayed ;
    if (offset == 0) offset = number_of_pages_displayed ;
    for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
    {
        if ((int)(i - offset) + m_table_pages.size() < m_table_pages.size()) buffer[LAST][i] = &(m_table_pages[(int)(i - offset) + m_table_pages.size()]) ;
        else buffer[LAST][i] = &(m_table_pages[m_table_pages.size() - 1]) ;
    }

    emit SG_pagesLoaded (buffer) ;
}


void ComicBook::computeThumbnail ()
{

}
