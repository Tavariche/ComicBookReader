#ifndef PAGES_BUFFER_H
#define PAGES_BUFFER_H


#include <QObject>
#include <QVector>
#include "e_page_role.h"
#include "PageManager.h"


/********************************************************
*   PagesBuffer
* -------------------------------------------------------
*   Stocke les adresses des parges chargées en mémoire par
*   le comic book.
********************************************************/

class PagesBuffer:
        public QObject
{
    Q_OBJECT
    
    //  Tableau contenant les références des pages chargées en mémoire.
    //      [NEXT]:    page(s) suivante(s).
    //      [PREVIOUS]:    page(s) précédente(s).
    //      [FIRST]:    page(s) du début.
    //      [LAST]:    page(s) de la fin.
    //      [CURRENT]:    page(s) actuellement visionnée(s).
    //  Les constantes entre crochets sont définies dans le fichier e_page_role.h.
    QVector<QVector<PageManager*> > m_buffer ;
    
    signals:
        //  Descr:  émis lorsque le PageBuffer a mis à jour sont tableau de pointeurs vers
        //          les nouvelles images chargées en mémoire.
        //  Conex:  connecté au PagesContainer associé.
        void bufferUpdated () ;
        
    public slots:
        //  Descr:  Décharge les images qui ne sont plus utiles et met à jour le tableau de
        //          pointeurs du PagesBuffer.
        //  Param:  * buffer:   tableau de pointeurs contenant les adresses des images
        //                      chargées en mémoire.
        void updateBuffer (QVector<QVector<PageManager*> > buffer) ;
    
    public:
        PagesBuffer () ;
        ~PagesBuffer () ;

        //  Descr:  Met à jour la taille des tableaux de référence (nécessaire quand le
        //          nombre de pages à afficher simultanément est modifié).
        //  Param:  * number_pages_displayed:   nombre de pages affichées simultanément.
        void setNumberPagesDisplayed (unsigned int number_pages_displayed) ;
};

#endif // PAGES_BUFFER_H
