#include <QMessageBox>  //  Pour debugging.
#include "NavigationManager.h"


NavigationManager::NavigationManager (): QObject()
{
    m_number_pages = 0 ;
    m_current_page = 0 ;
    m_number_of_pages_displayed = 1 ;
    m_reading_style = OCCIDENTAL ;
}


NavigationManager::NavigationManager (unsigned int number_pages): QObject()
{
    m_number_pages = number_pages ;
    m_current_page = 0 ;
    m_number_of_pages_displayed = 1 ;
    m_reading_style = OCCIDENTAL ;
}



NavigationManager::~NavigationManager ()
{

}


void NavigationManager::flush()
{
    m_number_pages = 0 ;
    m_current_page = 0 ;
    m_number_of_pages_displayed = 1 ;
    m_reading_style = OCCIDENTAL ;
}


void NavigationManager::goToLastPage ()
{
    m_current_page = ((m_number_pages - 1) / m_number_of_pages_displayed) * m_number_of_pages_displayed ;

    emit SG_goToPage ((int) m_current_page, (int) m_number_of_pages_displayed) ;
}


void NavigationManager::goToFirstPage ()
{
    m_current_page = 0 ;
    emit SG_goToPage ((int) m_current_page, (int) m_number_of_pages_displayed) ;
}


void NavigationManager::goToPage (int page)
{
    if (page >= (int) m_number_pages)
    {
        goToLastPage() ;
        return ;
    }

    if (page < 0) m_current_page = 0;
    else
        m_current_page = (uint) (page) / m_number_of_pages_displayed * m_number_of_pages_displayed ;

    emit SG_goToPage ((int) m_current_page, (int) m_number_of_pages_displayed) ;
}


void NavigationManager::goToNextPage ()
{
    if (m_current_page < m_number_pages - m_number_of_pages_displayed) m_current_page += m_number_of_pages_displayed ;
    emit SG_goToPage ((int) m_current_page, (int) m_number_of_pages_displayed) ;
}


void NavigationManager::goToPreviousPage ()
{
    if (m_current_page >= m_number_of_pages_displayed) m_current_page -= m_number_of_pages_displayed ;
    emit SG_goToPage ((int) m_current_page, (int) m_number_of_pages_displayed) ;
}


void NavigationManager::setNumberPagesInComicBook (unsigned int number_pages)
{
    m_number_pages = number_pages ;

    if(m_current_page>m_number_pages)
        m_current_page = 0 ;
}


void NavigationManager::setNumberPagesDisplayed (unsigned int number_pages)
{
    m_number_of_pages_displayed = number_pages ;
    m_pages_buffer.setNumberPagesDisplayed (number_pages) ;
    m_current_page = (m_current_page / number_pages) * number_pages ;

    emit SG_goToPage(m_current_page, m_number_of_pages_displayed);
}

