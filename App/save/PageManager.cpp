#include <QMessageBox>  //  Pour debugging.
#include "PageManager.h"
#include <QtCore>
#include <QDebug>

PageManager::PageManager (): QObject()
{
    m_path_to_image = "" ;
    m_loaded = false ;
    m_resized.clear();
    m_thumbnail.clear();
}


PageManager::PageManager (QString path_to_image): QObject()
{    
    m_path_to_image = path_to_image ;
    m_loaded = false ;
    m_resized.clear();
    m_thumbnail.clear();
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
    QMutex mutex;
    mutex.lock();

    if (m_path_to_image.isEmpty())
    {
        QMessageBox::critical(0, "Erreur - Chargement PageManager", "La page ne peut pas être chargée sans lui avoir au préalable spécifié le chemin vers son image.") ;
    }
    else if (!m_loaded)
    {
        m_original = QPixmap(m_path_to_image) ;
        m_resized.setPixmap(m_original);
        m_loaded = true ;
    }
    mutex.unlock();
}


void PageManager::unload (bool keep_thumbnail)
{
    QMutex mutex;
    mutex.lock();
    m_original = QPixmap() ;
    m_resized.setPixmap(QPixmap());
    if (!keep_thumbnail) m_thumbnail.setPixmap(QPixmap());

    m_loaded = false ;
    mutex.unlock();
}

void PageManager::scaleToHeight(int newHeight)
{
    QMutex mutex;
    mutex.lock();
    load();
    if(m_alreadyResized) return;
    setAlreadyResized(true); // On part du principe que la fonction terminera et on empêche un autre thread d'y entrer
    m_resized.setUpdatesEnabled(false); //désactivation du rafraichissement automatique

    //Si rien à modifier on ne fait rien
    if(m_resized.pixmap()->height() == newHeight) return;

    m_resized.setPixmap(m_original.scaledToHeight(newHeight, Qt::SmoothTransformation));
    mutex.unlock();
}

void PageManager::scaleToWidth(int newWidth)
{
    QMutex mutex;
    mutex.lock();
    load();
    if(m_alreadyResized) return;
    setAlreadyResized(true);
    m_resized.setUpdatesEnabled(false);

    if(m_resized.pixmap()->width() == newWidth) return;
    m_resized.setPixmap(m_original.scaledToWidth(newWidth, Qt::SmoothTransformation));
    mutex.unlock();
}

void PageManager::scale(int newMaxWidth, int newMaxHeight)
{
    QMutex mutex;
    mutex.lock();
    load();
    if(m_alreadyResized) return;
    setAlreadyResized(true);
    m_resized.setUpdatesEnabled(false);
    //Si rien à modifier on ne fait rien
    double pageRatio = (double) m_resized.pixmap()->height() / m_resized.pixmap()->width(),
           screenRatio = (double) newMaxHeight / newMaxWidth;

    //Le test contient les deux façons qu'une image peut avoir d'être bien dimensionnée
    if(((pageRatio >= screenRatio) && m_resized.pixmap()->height() == newMaxHeight) ||
      ((pageRatio <= screenRatio) && m_resized.pixmap()->width() == newMaxWidth)) return;
    m_resized.setPixmap(m_original.scaled(newMaxWidth, newMaxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    mutex.unlock();
}

void PageManager::refresh()
{
    QMutex mutex;
    mutex.lock();
    m_resized.setUpdatesEnabled(true);
    m_resized.update();
    if(m_resized.isVisible()||1){
        m_resized.hide(); //Permet de forces le rafraichissement d'une image non modifié
        m_resized.show(); //Sans cela elle ne se replace pas dans le layout
    }

    mutex.unlock();
}

//Calcul des caractéristiques de la page
void PageManager::setCarac()
{
    QMutex mutex;
    mutex.lock();
    load();
    height = getOriginal()->height();
    width = getOriginal()->width();
    unload();
    mutex.unlock();
}

void PageManager::computeThumbnail (const int newWidth, const int newHeight)
{
    QMutex mutex;
    mutex.lock();
    load();
    m_thumbnail.clear();
    m_thumbnail.setPixmap(m_original.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    mutex.unlock();
}
