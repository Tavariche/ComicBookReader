#include "NavigationManager.h"


NavigationManager::NavigationManager (): QObject()
{
    m_number_pages = 0 ;
    m_current_page = 0 ;
}


NavigationManager::NavigationManager (unsigned int number_pages): QObject()
{
    m_number_pages = number_pages ;
    m_current_page = 0 ;
}



NavigationManager::~NavigationManager ()
{

}


void NavigationManager::goToLastPage ()
{
    if (m_number_pages > 0) m_current_page = m_number_pages - 1 ;
    emit SG_goToPage (m_current_page) ;
}


void NavigationManager::goToFirstPage ()
{
    m_current_page = 0 ;
    emit SG_goToPage (m_current_page) ;
}


void NavigationManager::goToPage (unsigned int page)
{
    if (page >= m_number_pages) m_current_page = m_number_pages - 1 ;
    else m_current_page = page ;
    emit SG_goToPage (m_current_page) ;
}


void NavigationManager::goToNextPage ()
{
    if (m_current_page < m_number_pages - 1) m_current_page++ ;
    emit SG_goToPage (m_current_page) ;
}


void NavigationManager::goToPreviousPage ()
{
    if (m_current_page > 0) m_current_page-- ;
    emit SG_goToPage (m_current_page) ;
}
