#include <QMessageBox>  //  Pour debugging.
#include "PagesBuffer.h"


PagesBuffer::PagesBuffer (): QObject()
{
    m_buffer.resize (5) ;
    m_pagesData.resize(5) ;
    m_indexToRole = QVector<e_pages_roles>(INDEX_TO_ROLE);
}


PagesBuffer::~PagesBuffer ()
{

}


void PagesBuffer::updateBuffer (QVector<QVector<PageManager*> > buffer) //  Testée --> Fonctionnelle.
{
    //  On commence par soulager la mémoire des pages dont on n'a plus besoin.
    int buffer_size = m_buffer.size () ;
    int buffer_NEXT_size = m_buffer[NEXT].size () ;
    for (int i=0 ; i<buffer_size ; i++)
    {
        for (int j=0 ; j<buffer_NEXT_size ; j++)
        {
            bool found = false ;
            if (m_buffer[i][j] == NULL) continue ;
            for (int k=0 ; k<buffer_size ; k++)
            {
                for (int l=0 ; l<buffer_NEXT_size ; l++)
                {
                    if (buffer[k][l] == m_buffer[i][j])
                    {
                        found = true ;
                        break ;
                    }
                }
                if (found) break ;
            }

            if (!found) m_buffer[i][j]->unload (false) ; //  On décharge les images inutiles.
        }
    }


    //  On met ensuite à jour le tableau de pointeurs qui constitue le buffer.
    for (int j=0 ; j<m_buffer[NEXT].size() ; j++)
    {
        m_buffer[NEXT][j] = buffer[NEXT][j] ;
        m_buffer[PREVIOUS][j] = buffer[PREVIOUS][j] ;
        m_buffer[FIRST][j] = buffer[FIRST][j] ;
        m_buffer[LAST][j] = buffer[LAST][j] ;
        m_buffer[CURRENT][j] = buffer[CURRENT][j] ;
    }

    computeInfo();

    emit bufferUpdated(this);
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

void PagesBuffer::setNumberPagesDisplayed (unsigned int number_pages_displayed) //  Testée --> Fonctionnelle.
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
        auto pages = *getPages(i);
        for(int j = 0 ; j < getNumberOfPages(i) ; j++)
            pages[j]->setAlreadyResized(newValue);
    }
}

