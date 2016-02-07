#include "ThumbnailsPanel.h"
#include <qstring.h>


ThumbnailsPanel::ThumbnailsPanel(QWidget* parent) : QWidget(parent)
{
    m_thumbnailsList.clear();
    m_scrollArea = dynamic_cast<QScrollArea*>(parentWidget());
    m_attachedCB = 0;
}

ThumbnailsPanel::ThumbnailsPanel(ComicBook* attachedCB, NavigationManager *attachedNM, QWidget* parent) : QWidget(parent)
{
    setAttachedCB(attachedCB);
    setAttachedNM(attachedNM);
    m_thumbnailsList.clear();
    m_scrollArea = dynamic_cast<QScrollArea*>(parentWidget());
    //Construction de l'affichage des mignatures
    refreshPanel(false);
}

void ThumbnailsPanel::resizeEvent(QResizeEvent *)
{
    refreshPanel(false);
}


void ThumbnailsPanel::refreshPanel(bool rebuildLayout)
{
    //Redimensionnement des thumbnails
    m_attachedCB->computeThumbnail(m_scrollArea->width() - m_scrollArea->verticalScrollBar()->width());

    //Reconstruction du layout
    if(!rebuildLayout) return;
    m_thumbnailsList.clear();
    for(uint i = 1 ; i <= m_attachedCB->getNumberOfPages() ; i++){
        m_thumbnailsList.append(new thumbnailCell(i, m_attachedCB->getPage(i)->getThumbnail(), this));
    }

    QLayoutItem* child;
    while ((child = m_layout.takeAt(0)) != 0) {
        delete child;
    }

    for(int i = 0 ; i < m_thumbnailsList.size() ; i++){
        m_layout.addWidget(m_thumbnailsList[i]);
        connect(m_thumbnailsList[i], SIGNAL(thumbnailClicked(uint)), m_attachedNM, SLOT(goToPage(uint)));
    }
    setLayout(&m_layout);
}





//ThumbnailCell------------------------------------------------------------------

thumbnailCell::thumbnailCell(QWidget* parent) : QWidget(parent)
{
    m_pageNb = 0;
    m_pageThumbnail = 0;
    m_pageNbText.clear();
    m_pageNbText.setText("no page set");
    m_pageNbText.setParent(this);
    layoutThumbnail();
}

thumbnailCell::thumbnailCell(int pageNb, QLabel* pageThumbnail, QWidget* parent) : QWidget(parent)
{
    setThumbnail(pageNb, pageThumbnail);
    layoutThumbnail();
}

void thumbnailCell::setThumbnail(int pageNb, QLabel* pageThumbnail)
{
    m_pageNb = pageNb;
    m_pageThumbnail = pageThumbnail;

    QString title;

    title = "page " + QString::number(m_pageNb);
    m_pageNbText.setText(title);
    m_pageNbText.setParent(this);
}

void thumbnailCell::layoutThumbnail()
{
    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(m_pageThumbnail);
    layout->addWidget(&m_pageNbText);

    layout->setAlignment(Qt::AlignCenter);

    setLayout(layout);
}

void thumbnailCell::emitPageNb()
{
    emit thumbnailClicked(m_pageNb);
}

void thumbnailCell::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
        emitPageNb();
}



