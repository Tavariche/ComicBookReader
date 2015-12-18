#include "PagesContainer.h"

PagesContainer::PagesContainer(QWidget* parent) : QWidget(parent)
{
    setResizePolicy(ResizePolicy::fitScreen);
}

PagesContainer::PagesContainer(const QVector<QPixmap*> pages, QWidget* parent) : QWidget(parent)
{
    m_originalPages = pages;
    m_numberOfPages = (int) pages.size();
    m_globalEquivalentWidth = 0;

    for(int i = 0 ; i < m_numberOfPages ; i++){
        m_equivalentWidth.push_back((((double)m_originalPages[0]->height()) / m_originalPages[i]->height()) * m_originalPages[i]->width() );
        m_globalEquivalentWidth += m_equivalentWidth[i];
    }
    for(int i = 0 ; i < m_numberOfPages  ; i++){
        QLabel* temp = new QLabel;
        temp->setPixmap(*m_originalPages[i]);
        m_pagesLabel.push_back(temp);
    }


    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_pagesLabel[0]);
    m_layout->setAlignment(m_pagesLabel[0], Qt::AlignHCenter | Qt::AlignRight);
    for(int i = 1 ; i < m_numberOfPages - 1 ; i++){
        m_layout->addWidget(m_pagesLabel[i]);
        m_layout->setAlignment(m_pagesLabel[i], Qt::AlignCenter);
    }
    if(m_numberOfPages >= 2){
        m_layout->addWidget(m_pagesLabel[m_numberOfPages - 1]);
        m_layout->setAlignment(m_pagesLabel[m_numberOfPages - 1], Qt::AlignHCenter | Qt::AlignLeft);
    }
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(15);
    setLayout(m_layout);

    setResizePolicy(ResizePolicy::fitScreen);

    emit pagesSizeChanged(m_pagesLabel[0]->pixmap()->width());
}

/** PagesContainer(const QVector<PageManager*> pages, const QWidget* parent) : QWidget(parent)
 ** {
 **     m_pages = pages;
 **     setResizePolicy(ResizePolicy::fitScreen);
 ** }
 **/

void PagesContainer::scaleToHeight(const int newHeight)
{
    //Sélection des Pixmap nécessitant un redimentionnement et désactivation des màj
    QVector<QPixmap*> selectedPages;
    QVector<int> indirTable; //Mémorise à quel pixmap affecter le futur résultat
    for(int i = 0 ; i < m_numberOfPages ; i++){
        m_pagesLabel[i]->setUpdatesEnabled(false);
        if(m_pagesLabel[i]->pixmap()->height() != newHeight){
            selectedPages.push_back(m_originalPages[i]);
            indirTable.push_back(i);
        }
    }

    //Si rien à modifier
    if(indirTable.empty()){refresh(); return;}

    QFuture<QPixmap> result = QtConcurrent::mapped(selectedPages, std::bind(&QPixmap::scaledToHeight, std::placeholders::_1, newHeight, Qt::FastTransformation));
    for(int i = 0 ; i < indirTable.size() ; i++){
        m_pagesLabel[indirTable[i]]->setPixmap(result.results()[i]);
    }

    refresh();
}


void PagesContainer::scaleToWidth(const int newWidth)
{
    //Sélection des Pixmap nécessitant un redimentionnement et désactivation des màj
    QVector<QPixmap*> selectedPages;
    QVector<int> indirTable; //Mémorise à quel pixmap affecter le futur résultat
    for(int i = 0 ; i < m_numberOfPages ; i++){
        m_pagesLabel[i]->setUpdatesEnabled(false);
        if(m_pagesLabel[i]->pixmap()->width() != newWidth){
            selectedPages.push_back(m_originalPages[i]);
            indirTable.push_back(i);
        }
    }

    //Si rien à modifier
    if(indirTable.empty()){refresh(); return;}

    QFuture<QPixmap> result = QtConcurrent::mapped(selectedPages, std::bind(&QPixmap::scaledToWidth, std::placeholders::_1, newWidth, Qt::FastTransformation));
    for(int i = 0 ; i < indirTable.size() ; i++){
        m_pagesLabel[indirTable[i]]->setPixmap(result.results()[i]);
    }

    refresh();
}

void PagesContainer::scale(const int newMaxWidth, const int newMaxHeight)
{
    //Sélection des Pixmap nécessitant un redimentionnement très complexe et fonction rarement appelée donc tant pis
    for(int i = 0 ; i < m_numberOfPages ; i++) m_pagesLabel[i]->setUpdatesEnabled(false);

    QPixmap(QPixmap::*function)(int, int, Qt::AspectRatioMode, Qt::TransformationMode) const = &QPixmap::scaled;
    QFuture<QPixmap> result = QtConcurrent::mapped(m_originalPages, std::bind(function, std::placeholders::_1, newMaxWidth, newMaxHeight, Qt::KeepAspectRatio, Qt::FastTransformation));
    for(int i = 0 ; i < m_numberOfPages ; i++)
        m_pagesLabel[i]->setPixmap(result.results()[i]);

    refresh();

}

void PagesContainer::fitHeight()
{
    QScrollArea* parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget());
    if (parentScrollArea==0) exit(1);

    int spacing(m_layout->spacing() * (m_numberOfPages - 1)),
        H(parentScrollArea->maximumViewportSize().height()),
        h(H - parentScrollArea->horizontalScrollBar()->height()),
        W(parentScrollArea->maximumViewportSize().width() - spacing);
    double ratioHW = ((double)m_pagesLabel[0]->height()) / m_globalEquivalentWidth;

    //Traitement des problèmes de présence de scrollBar
    if (W < h / ratioHW){
        scaleToHeight(h);
    }else{
        scale(W/m_numberOfPages, H);
    }
}

void PagesContainer::fitWidth()
{
    QScrollArea* parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget());
    if (parentScrollArea==0) exit(1);

    int spacing(m_layout->spacing() * (m_numberOfPages - 1)),
        H(parentScrollArea->maximumViewportSize().height()),
        W(parentScrollArea->maximumViewportSize().width() - spacing),
        w(W - parentScrollArea->verticalScrollBar()->width());
    double ratioHW = (double)m_pagesLabel[0]->height() / m_globalEquivalentWidth;

    //Traitement des problèmes de présence de scrollBar
    if (H < w * ratioHW){
        scaleToWidth(w/m_numberOfPages);
    }else{
        scale(W/m_numberOfPages, H);
    }
}

void PagesContainer::fitScreen()
{
    QScrollArea* parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget());
    if (parentScrollArea==0) exit(1);

    int spacing(m_layout->spacing() * (m_numberOfPages - 1));
    double ratioPage = (double)m_pagesLabel[0]->height() / m_globalEquivalentWidth,
           ratioScreen = (double)parentScrollArea->maximumViewportSize().height() / parentScrollArea->maximumViewportSize().width();

    if (ratioPage < ratioScreen)
        fitWidth();
    else fitHeight();
}

void PagesContainer::refresh()
{
    for(int i = 0 ; i < m_numberOfPages ; i ++){
        m_pagesLabel[i]->setUpdatesEnabled(true);
        m_pagesLabel[i]->update();
        m_pagesLabel[i]->hide();
        m_pagesLabel[i]->show();
    }
}

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

    if (newWidth <= 0) return;
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

//void PagesContainer::changePages(const QVector<PagesManager*> newPages)
//{
//    m_originalPages = newPages;
//    applyResizePolicy();
//}
