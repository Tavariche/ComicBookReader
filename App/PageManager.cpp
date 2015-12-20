#include "PageManager.h"


PageManager::PageManager (): QObject()
{
    m_image_name = "" ;

    //  Initialiser les images à null.
}


PageManager::PageManager (QString image_name): QObject()
{    
    m_image_name = image_name ;

    //  Initialiser les images à null.
}


PageManager::PageManager(const PageManager& page_manager): QObject()
{
    m_image_name = page_manager.m_image_name ;
    m_original = page_manager.m_original ;
    m_resized = page_manager.m_resized ;
    m_thumbnail = page_manager.m_thumbnail ;
}


PageManager::~PageManager ()
{

}


void PageManager::load (QString path_to_image)
{
    if (m_image_name.isEmpty())
    {
        //  Signaler erreur dans log.
    }
    /*else if (// Vérifier que m_original n'est pas chargée avant d'effectuer l'opération.)
    {*/
    ////////////////////////////////////////////////////////////
    ///
    /// Charger les images.
    ///
    ////////////////////////////////////////////////////////////
    /*}*/
}


void PageManager::unload (bool keep_thumbnail)
{

}


void PageManager::computeResized ()
{

}


void PageManager::computeThumbnail ()
{

}
