#include <QDir>
#include <QFileInfo>
#include <QMessageBox>  //  Pour debugging.
#include "e_page_role.h"
#include "ComicBook.h"
#include <JlCompress.h>
#include <QtConcurrent/QtConcurrent>
#include <functional>


ComicBook::ComicBook (): QObject()
{
    m_path_to_archive = "" ;
    m_path_to_cb = "" ;
    m_table_pages.resize(0);
    m_extension_filter << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" ;
}


ComicBook::~ComicBook ()
{
    //  Suppression du dossier contenant les fichiers de l'archive décompressée ?
}


void ComicBook::uncompressArchive ()
{
    //  Aller voir sur //  http://www.antonioborondo.com/2014/10/22/zipping-and-unzipping-files-with-qt/
    //  pour compiler les librairies externes de décompression et les pouvoir utiliser dans le projet.

    if (m_path_to_archive.isEmpty())
    {
        QMessageBox::critical(0,
                              "Erreur - Décompression Impossible",
                              "Le chemin vers l'archive contenant l'ensemble des images compressées\ndu Comic Book n'a pas été spécifié.");
    }
    else
    {
        //  On commence par décompresser l'archive.
            //  A-t-on affaire à une archive zip ou rar ?
        //  On récupère le chemin du dossier dans lequel se trouve l'archive.
        QFileInfo file_info (m_path_to_archive) ;
        QString extraction_dir = file_info.absolutePath () ;
        JlCompress::extractDir (m_path_to_archive, extraction_dir) ;
        m_path_to_cb = extraction_dir + "/" ;   //  On met à jour le chemin vers le dossier décompressé.
    }
}


void ComicBook::initialise ()   //  Testée --> Fonctionnelle.
{
    if (m_path_to_cb.isEmpty())
    {
        QMessageBox::critical(0,
                              "Erreur - Initialisation Comic Book",
                              "Le Comic Book a tenté d'être initialisé sans que le chemin vers le dossier décompressé\nest été spécifié.") ;
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

        //  On précise aux PageManager le chemin de leur image associée.
        unsigned int index_page = 0 ;
        foreach (QFileInfo file_info, list_images)
        {
            if (file_info.isFile())
            {
                m_table_pages[index_page].setPathToImage(file_info.absoluteFilePath()) ;
                index_page++ ;
            }
            else break; //  Les dossiers sont situés à la fin de la liste. On arrête donc l'algorithme
                        //  dès qu'on rencontre le premier.
        }
    }
}


void ComicBook::loadPages (unsigned int page, unsigned int number_of_pages_displayed)   //  Testée --> Fonctionnelle.
{
    /*unsigned int index_first_current_page = (page/number_of_pages_displayed)*number_of_pages_displayed ;
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
    }*/

    // Création et remplissage d'un buffer temporaire avant de mettre à jour le PagesBuffer.
    QVector<QVector<PageManager*> > buffer (5) ;
    QVector<PageManager*> loading_buffer (5 * number_of_pages_displayed, NULL) ;  //  Sert à paralléliser le chargement des pages.
    unsigned int loading_buffer_index = 0 ;
    for (int i=0 ; i<5 ; i++) buffer[i].resize (number_of_pages_displayed) ;

    //  On commence par placer dans le buffer les références des pages actuellement visionnées.
    for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
    {
        if ((int)(i + page) < m_table_pages.size()) buffer[CURRENT][i] = &(m_table_pages[i + page]) ;
        else buffer[CURRENT][i] = &(m_table_pages[m_table_pages.size() - 1]) ;
        loading_buffer[loading_buffer_index] = buffer[CURRENT][i] ;
        loading_buffer_index++ ;
    }

    //  On place ensuite les références des pages suivantes et précédentes.
    for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
    {
        if ((int)(i + page + number_of_pages_displayed) < m_table_pages.size()) buffer[NEXT][i] = &(m_table_pages[i + page + number_of_pages_displayed]) ;
        else buffer[NEXT][i] = &(m_table_pages[m_table_pages.size() - 1]) ;
        loading_buffer[loading_buffer_index] = buffer[NEXT][i] ;
        loading_buffer_index++ ;
    }

    for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
    {
        if ((int)(i + page - number_of_pages_displayed) > 0) buffer[PREVIOUS][i] = &(m_table_pages[i + page - number_of_pages_displayed]) ;
        else buffer[PREVIOUS][i] = &(m_table_pages[0]) ;
        loading_buffer[loading_buffer_index] = buffer[PREVIOUS][i] ;
        loading_buffer_index++ ;
    }

    //  On place enfin dans le buffer les références des pages du début et de la fin du comic book.
    for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
    {
        if ((int)i < m_table_pages.size()) buffer[FIRST][i] = &(m_table_pages[i]) ;
        else buffer[FIRST][i] = &(m_table_pages[m_table_pages.size() - 1]) ;
        loading_buffer[loading_buffer_index] = buffer[FIRST][i] ;
        loading_buffer_index++ ;
    }

    unsigned int offset = m_table_pages.size() % number_of_pages_displayed ;
    if (offset == 0) offset = number_of_pages_displayed ;
    for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
    {
        if ((int)(i - offset) + m_table_pages.size() < m_table_pages.size()) buffer[LAST][i] = &(m_table_pages[(int)(i - offset) + m_table_pages.size()]) ;
        else buffer[LAST][i] = &(m_table_pages[m_table_pages.size() - 1]) ;
        loading_buffer[loading_buffer_index] = buffer[LAST][i] ;
        loading_buffer_index++ ;
    }

    //  On charge les pages dont les références sont contenues dans le buffer temporaire. Chargement parallélisé.
    QtConcurrent::blockingMap (loading_buffer, [](PageManager* pm) { pm->load () ; }) ;

    emit SG_pagesLoaded (buffer) ;
}


void ComicBook::computeThumbnail ()
{

}
