#ifndef PAGES_BUFFER_H
#define PAGES_BUFFER_H

#include <vector>
#include "PageManager.h"

/********************************************************
*   PagesBuffer
* -------------------------------------------------------
*   Stocke les références des parges chargées en mémoire.
********************************************************/

class PagesBuffer
{
    Q_OBJECT
    
    // Tableau contenant les références des pages chargées en mémoire.
    std::vector<std::vector<PageManager*> > m_buffer ;
    
    signals:
        // Signal émis lorsque le PageBuffer a mis à jour sont tableau de références.
        void bufferUpdated () ;
        
    slot:
        void update (std::vector<std::vector<PageManager*> > buffer) ;
    
    public:
        PagesBuffer () ;
        ~PagesBuffer () ;
};

#endif // PAGES_BUFFER_H
