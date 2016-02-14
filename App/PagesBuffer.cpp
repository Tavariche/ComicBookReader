#include <QMessageBox>  //  Pour debugging.
#include "PagesBuffer.h"


PagesBuffer::PagesBuffer (): QObject()
{
    m_buffer.resize (5) ;
    m_pagesData.resize(5) ;
    m_indexToRole = QVector<e_pages_roles>(INDEX_TO_ROLE);
}


void PagesBuffer::flush ()
{
    m_buffer.clear() ;
    m_pagesData.clear() ;

    m_buffer.resize (5) ;
    m_pagesData.resize(5) ;
}


void PagesBuffer::updateBuffer (QVector<QVector<PageManager*> > buffer)
{
    /*
     * Variables:
     *  - buffer_m_size:    nombre de sous-buffers contenus dans le m_buffer (attribut).
     *  - sub_buffer_m_size:    taille du sous-buffer m_buffer.
     *
     *  - buffer_size:    nombre de sous-buffers contenus dans le buffer (paramètre).
     *  - sub_buffer_size:    taille du sous-buffer buffer.
     */

    //  On commence par soulager la mémoire des pages dont on n'a plus besoin.

    for (int i=0, buffer_m_size = m_buffer.size () ; i<buffer_m_size ; i++)
    {
        for (int j=0, sub_buffer_m_size = m_buffer[i].size() ; j<sub_buffer_m_size ; j++)
        {
            bool found = false ;
            if (m_buffer[i][j] == NULL) continue ;
            for (int k=0, buffer_size = buffer.size() ; k<buffer_size ; k++)
            {
                for (int l=0, sub_buffer_size = buffer[k].size() ; l<sub_buffer_size ; l++)
                {
                    if (buffer[k][l] == m_buffer[i][j])
                    {
                        found = true ;
                        break ;
                    }
                }
                if (found) break ;
            }
            //  Si l'image n'a pas été trouvée c'est qu'on n'en a plus besoin donc on la décharge.
            if (!found) m_buffer[i][j]->unload () ;
        }
    }

    for (int i=0, buffer_size = buffer.size () ; i<buffer_size ; i++)
    {
        m_buffer[i].resize(buffer[i].size()) ;
        for (int j=0, sub_buffer_size = buffer[i].size() ; j<sub_buffer_size ; j++)
        {
            m_buffer[i][j] = buffer[i][j] ;
        }
    }

    computeInfo();

    emit bufferUpdated();
}


//Calcul des infos sur les pages
void PagesBuffer::computeInfo(){
    for (int i = 0 ; i < m_buffer.size() ; i++){
        m_pagesData[i].numberOfPages = m_buffer[i].size();

        if(m_buffer[i].size() == 0){m_pagesData[i].pagesRatio = 1; continue ;}

        double equivalentWidth = m_buffer[i][0]->getWidth();

        for(int j = 1 ; j < m_buffer[i].size() ; j++){
            equivalentWidth += m_buffer[i][j]->getWidth() * ((double) m_buffer[i][0]->getHeight() / m_buffer[i][j]->getHeight());
        }

        m_pagesData[i].pagesRatio = m_buffer[i][0]->getHeight() / equivalentWidth;
    }
}


void PagesBuffer::setNumberPagesDisplayed (unsigned int number_pages_displayed)
{
    for (int i=0 ; i<m_buffer.size() ; i++)
    {
        m_buffer[i].resize(number_pages_displayed) ;
        for (uint j=0 ; j<number_pages_displayed ; j++) m_buffer[i][j] = NULL ;
    }
}


QVector<PageManager*>* PagesBuffer::getPages(int pages_index)
{
    e_pages_roles role(m_indexToRole[pages_index]);
    return getPages(role);
}


void PagesBuffer::resetAlreadyResized(bool newValue){
    for(int i = 0 ; i < getNumberOfBlocs() ; i++){
        QVector<PageManager*> pages = *getPages(i);

        for(int j = 0 ; j < getNumberOfPages(i) ; j++){
            pages[j]->setAlreadyResized(newValue);
        }
    }
}
