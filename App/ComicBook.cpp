#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include "e_page_role.h"
#include "ComicBook.h"
#include <QtConcurrent/QtConcurrent>
#include <functional>
#include <cstdlib>
#include "Uncompression.h"

#define THUMBNAIL_RATIO 2 // Par défaut un thumbnail est au plus 2 fois plus haut que large

using namespace std ;

ComicBook::ComicBook (): QObject()
{
    m_extension_filter << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp" << "*.tiff" ;
    m_path_to_archive = "" ;
    m_path_to_cb = "" ;
    m_initialised = false ;
    m_next_to_archive = false ;
    m_table_pages.resize(0);
}


void ComicBook::flush()
{
    if (m_next_to_archive)
    {
        QDir dir (m_path_to_cb) ;
        dir.removeRecursively() ;
    }

    m_path_to_archive = "" ;
    m_path_to_cb = "" ;
    m_table_pages.clear() ;
    m_initialised = false ;
    m_next_to_archive = false ;
}


void ComicBook::uncompressComicBook ()
{
    if (m_path_to_archive.isEmpty())
    {
        QMessageBox::critical(0,
                              "Erreur - Décompression Impossible",
                              "Le chemin vers l'archive contenant l'ensemble des images compressées du Comic Book n'a pas été spécifié.");
    }
    else
    {
        //  On récupère le chemin vers le dossier temporaire.
        string temp_folder = "" ;
        const char* var_env_temp = getenv("TEMP") ;
        QFileInfo file_info (m_path_to_archive) ;
        if (!var_env_temp)  //  Si la variable d'environnement TEMP n'existe pas, on décompresse l'archive dans le dossier où elle se situe.
        {
            m_next_to_archive = true ;
            temp_folder = file_info.absolutePath().toStdString() ;
        }
        else
            temp_folder = string(var_env_temp) ;

        for (unsigned int i=0 ; i<temp_folder.size() ; i++)
        {
            if (temp_folder[i] == '\\') temp_folder[i] = '/' ;
        }

        if (temp_folder[temp_folder.size()-1] != '\\')
            temp_folder += "/" ;

        temp_folder = temp_folder + file_info.baseName().toStdString() + "/" ;
        m_path_to_cb = QString::fromStdString(temp_folder) ;

        //  On décompresse l'archive dans le dossier déterminé plus haut.
        QString::fromStdString(uncompressArchive(m_path_to_archive.toStdString(), temp_folder)) ;

        //  On récupère le sous-dossier le plus intérieur.
        m_path_to_cb = getPathAbsInnerDirectory(m_path_to_cb) ;
    }
}


QString ComicBook::getPathAbsInnerDirectory (QString path)
{
    QDir dir (path) ;
    QStringList list_subdir = dir.entryList (QDir::NoDotAndDotDot | QDir::Dirs, QDir::SortFlag::DirsFirst) ;

    while (!list_subdir.empty())
    {
        path += list_subdir[0] + "/" ;
        dir.setPath(path) ;
        list_subdir.clear() ;
        list_subdir = dir.entryList (QDir::NoDotAndDotDot | QDir::Dirs, QDir::SortFlag::DirsFirst) ;
    }
    return path ;
}


void ComicBook::initialise ()
{
    if (!m_path_to_cb.isEmpty())
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

        m_initialised = true ;

        emit SG_initialised() ;
    }
}


void ComicBook::loadPages (int page, int number_of_pages_displayed)
{
    //  Le chargement des pages ne se fait que si le ComicBook a été initialisé auparavant.
    if (m_initialised)
    {
        //  Création et remplissage d'un buffer temporaire avant de mettre à jour le PagesBuffer.
        QVector<QVector<PageManager*> > buffer (5) ;

        //  On commence par placer dans le buffer les références des pages actuellement visionnées.
        for (int i=0 ; i<number_of_pages_displayed ; i++)
        {
            if (i + page < m_table_pages.size()) buffer[CURRENT].push_back(&(m_table_pages[i + page])) ;
            else break ;
        }

        //  On place ensuite les références des pages suivantes et précédentes.
        for (int i=0 ; i<number_of_pages_displayed ; i++)
        {
            if (i + page + number_of_pages_displayed < m_table_pages.size()) buffer[NEXT].push_back(&(m_table_pages[i + page + number_of_pages_displayed])) ;
            else break ;
        }

        for (int i=0 ; i<number_of_pages_displayed ; i++)
        {
            if (i + page - number_of_pages_displayed >= 0) buffer[PREVIOUS].push_back(&(m_table_pages[i + page - number_of_pages_displayed])) ;
            else break ;
        }

        //  On place enfin dans le buffer les références des pages du début et de la fin du comic book.
        for (int i=0 ; i<number_of_pages_displayed ; i++)
        {
            if (i < m_table_pages.size()) buffer[FIRST].push_back(&(m_table_pages[i])) ;
            else break ;
        }

        int offset = m_table_pages.size() % number_of_pages_displayed ;
        if (offset == 0) offset = number_of_pages_displayed ;
        for (int i=0 ; i<number_of_pages_displayed ; i++)
        {
            if (i - offset + m_table_pages.size() < m_table_pages.size()) buffer[LAST].push_back(&(m_table_pages[i - offset + m_table_pages.size()])) ;
            else break ;
        }

        emit SG_pagesLoaded (buffer) ;
    }
}


void ComicBook::computeThumbnail (int width, int height)
{
    //Calcul de la hauteur maximale si height <= 0
    if(height <= 0) height = (int) (THUMBNAIL_RATIO * width);
    //Redimentionnement série
    for(uint i = 0 ; i < getNumberOfPages() ; i++)
        m_table_pages[i].computeThumbnail(width, height);
}
