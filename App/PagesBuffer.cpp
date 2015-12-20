#include "PagesBuffer.h"


PagesBuffer::PagesBuffer (): QObject()
{

}


PagesBuffer::~PagesBuffer ()
{

}


void PagesBuffer::updateBuffer (QVector<QVector<PageManager*> > buffer)
{
    for (int i=0 ; i<m_buffer.size() ; i++)
    {
        for (int j=0 ; j<m_buffer.size() ; j++)
            m_buffer[i][j] = buffer[i][j] ;
    }
}


void PagesBuffer::setNumberPagesDisplayed (unsigned int number_pages_displayed)
{
    for (int i=0 ; i<m_buffer.size() ; i++)
    {
        m_buffer[i].resize(number_pages_displayed) ;
    }
}
