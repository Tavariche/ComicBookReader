#include <QMessageBox>  //  Pour debugging.
#include "PageManager.h"


PageManager::PageManager (): QObject()
{
    m_path_to_image = "" ;
    m_loaded = false ;
}


PageManager::PageManager (QString path_to_image): QObject()
{    
    m_path_to_image = path_to_image ;
    m_loaded = false ;
}


PageManager::PageManager(const PageManager& page_manager): QObject()
{
    m_path_to_image = page_manager.m_path_to_image ;
    m_original = page_manager.m_original ;
    m_resized.setPixmap(*(page_manager.m_resized.pixmap())) ;
    m_thumbnail.setPixmap(*(page_manager.m_thumbnail.pixmap())) ;
    m_loaded = page_manager.m_loaded ;
}


PageManager::~PageManager ()
{

}


void PageManager::load ()
{
    if (m_path_to_image.isEmpty())
    {
        QMessageBox::critical(0, "Erreur - Chargement PageManager", "La page ne peut pas être chargée sans lui avoir au préalable spécifié le chemin vers son image.") ;
    }
    else if (!m_loaded)
    {
        m_original.fromImage(QImage(m_path_to_image)) ;
        m_loaded = true ;
    }
}


void PageManager::unload (bool keep_thumbnail)
{
    m_original.fromImage(QImage(0, 0, QImage::Format_ARGB32)) ;
    m_resized.setPixmap(QPixmap(0, 0));
    if (!keep_thumbnail) m_thumbnail.setPixmap(QPixmap(0, 0));

    m_loaded = false ;
}


void PageManager::computeResized ()
{

}


void PageManager::computeThumbnail ()
{

}
