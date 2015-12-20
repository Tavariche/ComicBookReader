#ifndef PAGES_BUFFER_H
#define PAGES_BUFFER_H


#include <QObject>
#include <QVector>
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
    //      [0]:    page(s) suivante(s).
    //      [1]:    page(s) précédente(s).
    //      [2]:    page(s) du début.
    //      [3]:    page(s) de la fin.
    //      [4]:    page(s) actuellement visionnée(s).
    QVector<QVector<PageManager*> > m_buffer ;
    
    signals:
        //  Descr:  émis lorsque le PageBuffer a mis à jour sont tableau de pointeurs vers
        //          les nouvelles images chargées en mémoire.
        //  Connection: connecté au PagesContainer associé.
        void bufferUpdated () ;
        
    public slots:
        //  Descr:  met à jour le tableau de pointeurs du PagesBuffer.
        //  Param:  * buffer:   tableau de pointeurs contenant les adresses des images
        //                      chargées en mémoire.
        void updateBuffer (QVector<QVector<PageManager*> > buffer) ;
    
    public:
        PagesBuffer () ;
        ~PagesBuffer () ;

        //  Descr:  met à jour la taille des tableaux de référence (nécessaire quand le
        //          nombre de pages à afficher simultanément est modifié).
        //  Param:  * number_pages_displayed:   nombre de pages affichées simultanément.
        void setNumberPagesDisplayed (unsigned int number_pages_displayed) ;
};

#endif // PAGES_BUFFER_H
