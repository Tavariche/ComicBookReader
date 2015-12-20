#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H


#include <QObject>
#include <QString>
#include <QPixmap>


/********************************************************
*   PageManager
* -------------------------------------------------------
*   Représente une page du comic book.
********************************************************/

class PageManager:
        public QObject
{
    Q_OBJECT

    //  Nom (avec l'extension) de l'image à laquelle est associée le PageManager.
    QString m_image_name ;
    
    //  Image originale servant de base pour les calculs de redimensionnement.
    QPixmap m_original ;

    //  Image redimesionnée.
    QPixmap m_resized ;
    
    //  Image miniature associée à la page.
    QPixmap m_thumbnail ;
    
    public:
        PageManager () ;

        //  Constructeur de copie.
        //  Param : * page_manager: PageManger à copier.
        PageManager(const PageManager& page_manager) ;

        //  Constructeur explicite du PageManager.
        //  Param : * image_name:   nom (avec l'extension) de l'image associée au PageManager.
        explicit PageManager (QString image_name) ;
        ~PageManager () ;
        
        //  Spécifie le nom de l'image associée au PageManager.
        //  Param : * image_name:   nom (avec l'extension) de l'image associée au PageManager.
        void setImageName (QString image_name) { m_image_name = image_name ; }
        
        //  Charge la page associée au PageManager.
        //  Param : * path_to_image:    chemin vers le dossier dans lequel se trouve l'image image_name à charger.
        void load (QString path_to_image) ;
        
        //  Décharge la page.
        //  Param : * keep_thumbnail:   true:   décharge m_original et m_resized mais conserve m_thumbnail.
        //                              false:  décharge toutes les images y compris m_thumbnail.
        void unload (bool keep_thumbnail) ;
        
        //  Redimensionne l'image originale et stocke le résultat dans m_resized.
        void computeResized () ; 
        
        //  Calcule la miniature associée à l'image originale et la stocke dans m_thumbnail.
        void computeThumbnail () ; 
        
        //  Retourne une référence vers l'image originale.
        QPixmap* getOriginal () { return &m_original ; }
        
        //  Retourne une référence vers l'image redimensionnée.
        QPixmap* getResized () { return &m_resized ; }
        
        //  Retourne une référence vers la miniature.
        QPixmap* getThumbnail () { return &m_thumbnail ; }
};

#endif // PAGEMANAGER_H
