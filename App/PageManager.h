#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H


#include <QObject>
#include <QString>
#include <QPixmap>
#include <QLabel>


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
    QString m_path_to_image ;
    
    //  Image originale servant de base pour les calculs de redimensionnement.
    QPixmap m_original ;

    //  Image redimesionnée.
    QLabel m_resized ;
    
    //  Image miniature associée à la page.
    QLabel m_thumbnail ;

    //  Indique si la page est chargée.
    bool m_loaded ;
    
    public:
        PageManager () ;

        //  Descr:  Constructeur de copie.
        //  Param : * page_manager: PageManger à copier.
        PageManager(const PageManager& page_manager) ;

        //  Descr:  Constructeur explicite du PageManager.
        //  Param : * image_name:   nom (avec l'extension) de l'image associée au PageManager.
        explicit PageManager (QString path_to_image) ;
        ~PageManager () ;
        
        //  Descr:  Spécifie le nom de l'image associée au PageManager.
        //  Param : * image_name:   nom (avec l'extension) de l'image associée au PageManager.
        void setPathToImage (QString path_to_image) { m_path_to_image = path_to_image ;  }
        
        //  Descr:  Charge la page associée au PageManager.
        //  Param : * path_to_image:    chemin vers le dossier dans lequel se trouve l'image image_name à charger.
        void load () ;
        
        //  Descr:  Décharge la page.
        //  Param : * keep_thumbnail:   true:   décharge m_original et m_resized mais conserve m_thumbnail.
        //                              false:  décharge toutes les images y compris m_thumbnail.
        void unload (bool keep_thumbnail) ;
        
        //  Redimensionne l'image originale et stocke le résultat dans m_resized.
        void computeResized () ; 
        
        //  Calcule la miniature associée à l'image originale et la stocke dans m_thumbnail.
        void computeThumbnail () ; 

        //  Descr:  Retourne le nom de l'image associée.
        QString getPathToImage () const { return m_path_to_image ; }
        
        //  Descr:  Retourne une référence vers l'image originale.
        QPixmap* getOriginal () { return &m_original ; }
        
        //  Descr:  Retourne une référence vers l'image redimensionnée.
        QLabel* getResized () { return &m_resized ; }
        
        //  Descr:  Retourne une référence vers la miniature.
        QLabel* getThumbnail () { return &m_thumbnail ; }

        //  Descr:  Indique si la page est chargée.
        bool isLoaded () const { return m_loaded ; }
};

#endif // PAGEMANAGER_H
