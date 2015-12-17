#include "PagesContainer.h"

PagesContainer::PagesContainer(QWidget* parent) : QWidget(parent)
{
    setResizePolicy(ResizePolicy::fitScreen);
}

/** PagesContainer(const vector<PageManager*> pages, const QWidget* parent) : QWidget(parent)
 ** {
 **     m_pages = pages;
 **     setResizePolicy(ResizePolicy::fitScreen);
 ** }
 **/

void PagesContainer::setResizePolicy(const ResizePolicy resizePolicy)
{
    m_resizePolicy = resizePolicy;
}

ResizePolicy PagesContainer::getResizePolicy() const
{
    return m_resizePolicy;
}

void PagesContainer::applyResizePolicy()
{
    if (m_resizePolicy & ResizePolicy::fitWidth)
        fitWidth();
    else if (m_resizePolicy & ResizePolicy::fitHeight)
        fitHeight();
    else if (m_resizePolicy & ResizePolicy::fitScreen)
        fitScreen();
    else
        refresh();
}

void PagesContainer::setPolicyPersonnal(const int newWidth)
{
    setResizePolicy(ResizePolicy::personal);
    scaleToWidth(1, newWidth);
    scaleToWidth(2, newWidth);
}

void PagesContainer::setPolicyFitWidth()
{
    setResizePolicy(ResizePolicy::fitWidth);
    applyResizePolicy();
}

void PagesContainer::setPolicyFitHeight()
{
    setResizePolicy(ResizePolicy::fitHeight);
    applyResizePolicy();
}

void PagesContainer::setPolicyFitScreen()
{
    setResizePolicy(ResizePolicy::fitScreen);
    applyResizePolicy();
}

/** void changePages(const std::vector<PagesManager*> newPages)
 ** {
 **     m_pages = newPages;
 ** }
 **/
