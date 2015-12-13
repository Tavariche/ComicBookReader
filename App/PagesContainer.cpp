#include "PagesContainer.h"

PagesContainer::PagesContainer(QWidget* parent) : QWidget(parent)
{}

void PagesContainer::setResizePolicy(ResizePolicy resizePolicy)
{
    m_resizePolicy = resizePolicy;
}

ResizePolicy PagesContainer::getResizePolicy()
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
}

void PagesContainer::setPolicyPersonnal(int newWidth)
{
    setResizePolicy(ResizePolicy::personal);
    scaleToWidth(newWidth);
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
