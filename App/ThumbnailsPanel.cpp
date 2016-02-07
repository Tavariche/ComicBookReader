#include "ThumbnailsPanel.h"
#include <qstring.h>

void ThumbnailsPanel::basicInit()
{
    m_thumbnailsList.clear();
    m_scrollArea = this;
    m_widget = new QWidget(m_scrollArea);
    m_scrollArea->setWidget(m_widget);
    setWidgetResizable(true);

}

ThumbnailsPanel::ThumbnailsPanel(QWidget* parent) : CBScrollArea(parent)
{
    basicInit();
    m_attachedCB = 0;
}

ThumbnailsPanel::ThumbnailsPanel(ComicBook* attachedCB, NavigationManager *attachedNM, QWidget* parent) : CBScrollArea(parent)
{
    basicInit();
    setAttachedCB(attachedCB);
    setAttachedNM(attachedNM);
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
    m_attachedCB->computeThumbnail(std::min(m_scrollArea->width() - m_scrollArea->verticalScrollBar()->width() - 4, MAX_THUMBNAILS_WIDTH));

    if(!rebuildLayout) return;

    //Reconstruction du layout
    //Déconnection des signaux
    for(int i = 0 ; i < m_thumbnailsList.size() ; i++)
        disconnect(m_thumbnailsList[i], SIGNAL(thumbnailClicked(int)), 0, 0);

    m_thumbnailsList.clear();
    //nouvelle liste de cellules
    for(uint i = 1 ; i <= m_attachedCB->getNumberOfPages() ; i++){
        m_thumbnailsList.append(new thumbnailCell(i, m_attachedCB->getPage(i-1)->getThumbnail(), this));
        connect(m_thumbnailsList.last(), SIGNAL(thumbnailClicked(int)), m_attachedNM, SLOT(goToPage(int)));
    }
    //Vidage du layout
    QLayoutItem* child;
    while ((child = m_layout.takeAt(0)) != 0) {
        delete child;
    }
    //remplissage du layout
    for(int i = 0 ; i < m_thumbnailsList.size() ; i++)
        m_layout.addWidget(m_thumbnailsList[i]);

    m_layout.setMargin(0);
    m_widget->setLayout(&m_layout);
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

    layout->setAlignment(&m_pageNbText, Qt::AlignHCenter);
    layout->setAlignment(m_pageThumbnail, Qt::AlignHCenter);

    layout->setMargin(0);
    setLayout(layout);
}

void thumbnailCell::emitPageNb()
{
    emit thumbnailClicked(m_pageNb - 1);
}

void thumbnailCell::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
        emitPageNb();
}



