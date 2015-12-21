#include <QMessageBox>  //  Pour debugging.
#include "PageManager.h"


PageManager::PageManager (): QObject()
{
    m_image_name = "" ;
    m_loaded = false ;

    //  Initialiser les images à null.
}


PageManager::PageManager (QString image_name): QObject()
{    
    m_image_name = image_name ;
    m_loaded = false ;

    //  Initialiser les images à null.
}


PageManager::PageManager(const PageManager& page_manager): QObject()
{
    m_image_name = page_manager.m_image_name ;
    m_original = page_manager.m_original ;
    m_resized.setPixmap(*(page_manager.m_resized.pixmap())) ;
    m_thumbnail.setPixmap(*(page_manager.m_thumbnail.pixmap())) ;
    m_loaded = page_manager.m_loaded ;
}


PageManager::~PageManager ()
{

}


void PageManager::load (QString path_to_image)
{
    if (m_image_name.isEmpty())
    {
        QMessageBox::critical(0, "Erreur - Chargement PageManager", "La page ne peut pas être chargée sans avoir\nau préalable spécifié le nom de son image associée.") ;
    }
    else if (!m_loaded)
    {
        m_original.fromImage(QImage(path_to_image + m_image_name)) ;
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
