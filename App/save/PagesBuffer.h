#ifndef PAGES_BUFFER_H
#define PAGES_BUFFER_H


#include <QObject>
#include <QVector>
#include "e_page_role.h"
#include "PageManager.h"

#define INDEX_TO_ROLE {CURRENT, NEXT, PREVIOUS, FIRST, LAST}

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

    //Tableau contenant des infos précalculées sur le buffer
    typedef struct {int numberOfPages; double pagesRatio;} PageData;
    QVector<PageData> m_pagesData ;
    //Calcule d'informations utiles sur les blocs de pages
    void computeInfo();

    //Ordre de priorité de traitement des pages
    QVector<e_pages_roles> m_indexToRole;
    
    signals:
        //  Descr:  émis lorsque le PageBuffer a mis à jour sont tableau de pointeurs vers
        //          les nouvelles images chargées en mémoire. Communique les pages à afficher.
        //  Conex:  connecté au PagesContainer associé.
        void bufferUpdated (PagesBuffer*) ;
        
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

        //  Descr:  Accès aux pages par depuis un entier. Permet l'itération par boucle.
        //          Définit en même temps l'ordre de priorité des pages.
        QVector<PageManager*>* getPages(int pages_index);
        QVector<PageManager*>* getPages(e_pages_roles role){return &m_buffer[role];}

        //  Descr:  Accès aux infos de page
        int getNumberOfPages(int index = 0){return m_pagesData[index].numberOfPages;}
        double getPagesRatio(int index = 0){return m_pagesData[index].pagesRatio;}
        int getNumberOfBlocs(){return m_pagesData.size();}

        //  Descr:  Réinitialisation de bool m_alreadyResized des PageManager
        void resetAlreadyResized(bool newValue = false);
};

#endif // PAGES_BUFFER_H
