#include "ThumbnailsPanel.h"
#include <qstring.h>
#include <QtConcurrent/QtConcurrent>

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
    m_attachedCB = NULL ;
    m_attachedNM = NULL ;
}

ThumbnailsPanel::ThumbnailsPanel(ComicBook* attachedCB, NavigationManager *attachedNM, QWidget* parent) : CBScrollArea(parent)
{
    basicInit();
    setAttachedCB(attachedCB);
    setAttachedNM(attachedNM);
    //Construction de l'affichage des mignatures
    refreshPanel(false);
}

void ThumbnailsPanel::resizeEvent(QResizeEvent *e)
{
    if(!(e->oldSize().width() == e->size().width()))
        refreshPanel(false);
}


/*thumbnailsThreads[i] = QtConcurrent::run(&m_table_pages[i], &PageManager::computeThumbnail, width, height);
thumbnailsThreads[i].waitForFinished();*/

void ThumbnailsPanel::refreshPanel(bool rebuildLayout)
{
    if(m_attachedCB == NULL or m_attachedNM == NULL)
        return ;

    //Redimensionnement des thumbnails
    QtConcurrent::run(m_attachedCB, &ComicBook::computeThumbnail, std::min(m_scrollArea->width() - m_scrollArea->verticalScrollBar()->width() - 4, MAX_THUMBNAILS_WIDTH), -1).waitForFinished();

    if(!rebuildLayout) return;

    //Reconstruction du layout
    //Déconnection des signaux
    for(int i = 0 ; i < m_thumbnailsList.size() ; i++)
    {
        disconnect(m_thumbnailsList[i], SIGNAL(thumbnailClicked(int)), 0, 0);
        delete m_thumbnailsList[i];
    }
    m_thumbnailsList.clear();
    //nouvelle liste de cellules
    for(uint i = 1 ; i <= m_attachedCB->getNumberOfPages() ; i++)
    {
        m_thumbnailsList.append(new thumbnailCell(i, m_attachedCB->getThumbnail(i-1), this));
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
    m_pageThumbnail = NULL ;
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



