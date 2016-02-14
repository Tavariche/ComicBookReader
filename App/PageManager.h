#ifndef PAGEMANAGER_H
#define PAGEMANAGER_H


#include <QObject>
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <QtCore>


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
    
    //  Indique si une page a déjà été redimentionnée au cours d'une opération de redimentionnement
    //  Permet de traiter le cas des doublons dans le buffer (1e page = page courrante, ...)
    bool m_alreadyResized ;

    QMutex m_mutex ;

    // Caractéristiques de la page
    int height;
    int width;
    void setCarac();

    public:
        PageManager () ;

        //  Descr:  Constructeur de copie.
        //  Param : * page_manager: PageManger à copier.
        PageManager(const PageManager& page_manager) ;

        //  Descr:  Constructeur explicite du PageManager.
        //  Param : * image_name:   nom (avec l'extension) de l'image associée au PageManager.
        explicit PageManager (QString path_to_image) ;
        ~PageManager () ;
        
        //  Descr:  Spécifie le nom de l'image associée au PageManager et calcul les caractéristiques correspondantes
        //  Param : * image_name:   nom (avec l'extension) de l'image associée au PageManager.
        void setPathToImage (QString path_to_image) { m_path_to_image = path_to_image ;  setCarac();}
        
        //  Descr:  Charge la page associée au PageManager.
        void load () ;

        //  Descr : Redimentionne m_original à la hauteur demandée et stocke le résultat dans m_resized
        //  Param : * newHeight:    nouvelle hauteur de l'image en pixels
        void scaleToHeight(const int newHeight);

        //  Descr : Redimentionne m_original à la largeur demandée et stocke le résultat dans m_resized
        //  Param : * newHeight:    nouvelle largeur de l'image en pixels
        void scaleToWidth(const int newWidth);

        //  Descr : Redimentionne m_original au plus grand dans le limites données et sans déformation.
        //          Stocke le résultat dans m_resized.
        //  Param : * newMaxHeight:     hauteur maximale du cadre de redimentionnement
        //          * newMaxWidth:      largeur maximale du cadre de redimentionnement
        void scale(const int newMaxWidth, const int newMaxHeight);

        //  Descr : Rafraichit l'affichage de m_resized
        void refresh();

        //  Descr : fixe la valeur de m_alreadyResized comme voulu
        void setAlreadyResized(bool newValue){QMutex mutex; mutex.lock(); m_alreadyResized = newValue; mutex.unlock();}
        
        //  Descr:  Décharge la page.
        //  Param : * keep_thumbnail:   true:   décharge m_original et m_resized mais conserve m_thumbnail.
        //                              false:  décharge toutes les images y compris m_thumbnail.
        void unload (bool keep_thumbnail = true, bool keep_resized = false) ;
        
        
        //  Calcule la miniature associée à l'image originale et la stocke dans m_thumbnail.
        void computeThumbnail (const int newWidth, const int newHeight) ;

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

        //  Desc: Retourne la largeur ou la hauteur de l'image associée
        int getWidth(){return width;}
        int getHeight(){return height;}
};

#endif // PAGEMANAGER_H
