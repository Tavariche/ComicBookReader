#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include "e_page_role.h"
#include "ComicBook.h"
#include <QtConcurrent/QtConcurrent>
#include <functional>
#include <cstdlib>
#include "Uncompression.h"

using namespace std ;

QStringList ComicBook::m_extension_filter {"*.jpg" , "*.jpeg" , "*.png" , "*.bmp" , "*.tiff"} ;

ComicBook::ComicBook (): QObject()
{
    m_path_to_archive = "" ;
    m_path_to_cb = "" ;
    m_initialised = false ;
    m_table_pages.resize(0);
}


ComicBook::~ComicBook ()
{
    //  Suppression du dossier contenant les fichiers de l'archive décompressée.
    /*if (!m_path_to_cb.isEmpty())
    {
        QDir dir (m_path_to_cb) ;
        bool successely_removed = dir.removeRecursively () ;
        if (!successely_removed)
        {
            QMessageBox::critical(0,
                                  "Erreur - Suppression Dossier Décompressé",
                                  "Le dossier décompressé contenant les images du comic book n'a pas été supprimé correctement. Cela peut provoquer des erreurs lors de la prochaine ouverture du comicc book.\nVeuillez supprimer le dossier décompressé en passant par votre explorateur situé ici:\n"+m_path_to_cb) ;
        }
    }*/

    /*/// DEBUG
    QMessageBox::information(0,"DEBUG","Sauvegarde ComicBook") ;

    ComicBookSettings *cbs = new ComicBookSettings() ;
    cbs->setPathToArchive(m_path_to_archive) ;
    cbs->setPathToComicBook(m_path_to_cb) ;
    emit SG_saveSettings(cbs);*/
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
        //  On récupère le chemin du dossier temporaire.
        string temp_folder = "" ;
        const char* var_env_temp = getenv("TEMP") ;
        if (!var_env_temp)  //  Si la variable d'environnement TEMP n'existe pas, on décompresse l'archive dans le dossier où elle se situe.
        {
            QFileInfo file_info (m_path_to_archive) ;
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

        //  On décompresse l'archive dans le dossier déterminé plus haut.
        m_path_to_cb = QString::fromStdString(uncompressArchive(m_path_to_archive.toStdString(), temp_folder)) ;
    }
}


void ComicBook::initialise ()
{
    if (m_path_to_cb.isEmpty())
    {
        QMessageBox::critical(0,
                              "Erreur - Initialisation Comic Book",
                              "Le Comic Book a tenté d'être initialisé sans que le chemin vers le dossier décompressé ait été spécifié. Le chargement des pages ne peut pas s'effectuer.") ;
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

        m_initialised = true ;
    }
}


void ComicBook::loadPages (unsigned int page, unsigned int number_of_pages_displayed)
{
    //  Le chargement des pages ne se fait que si le ComicBook a été initialisé auparavant.
    if (m_initialised)
    {
        //  Création et remplissage d'un buffer temporaire avant de mettre à jour le PagesBuffer.
        QVector<QVector<PageManager*> > buffer (5) ;

        //  On commence par placer dans le buffer les références des pages actuellement visionnées.
        for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
        {
            if ((int)(i + page) < m_table_pages.size()) buffer[CURRENT].push_back(&(m_table_pages[i + page])) ;
            else break ;
        }

        //  On place ensuite les références des pages suivantes et précédentes.
        for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
        {
            if ((int)(i + page + number_of_pages_displayed) < m_table_pages.size()) buffer[NEXT].push_back(&(m_table_pages[i + page + number_of_pages_displayed])) ;
            else break ;
        }

        for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
        {
            if ((int)(i + page - number_of_pages_displayed) >= 0) buffer[PREVIOUS].push_back(&(m_table_pages[i + page - number_of_pages_displayed])) ;
            else break ;
        }

        //  On place enfin dans le buffer les références des pages du début et de la fin du comic book.
        for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
        {
            if ((int)i < m_table_pages.size()) buffer[FIRST].push_back(&(m_table_pages[i])) ;
            else break ;
        }

        unsigned int offset = m_table_pages.size() % number_of_pages_displayed ;
        if (offset == 0) offset = number_of_pages_displayed ;
        for (unsigned int i=0 ; i<number_of_pages_displayed ; i++)
        {
            if ((int)(i - offset) + m_table_pages.size() < m_table_pages.size()) buffer[LAST].push_back(&(m_table_pages[(int)(i - offset) + m_table_pages.size()])) ;
            else break ;
        }

        emit SG_pagesLoaded (buffer) ;
    }
}


void ComicBook::computeThumbnail ()
{

}
