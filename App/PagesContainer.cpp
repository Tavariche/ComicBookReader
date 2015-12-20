#include <QtConcurrent/QtConcurrent>
#include <functional>
#include "PagesContainer.h"

// Constructeur par défaut.
PagesContainer::PagesContainer(QWidget* parent) : QWidget(parent)
{
    setResizePolicy(FIT_SCREEN);
}


// Constructeur.
PagesContainer::PagesContainer(const QVector<QPixmap*> pages, QWidget* parent) : QWidget(parent)
{
    m_originalPages = pages;
    m_numberOfPages = (int) pages.size();
    m_globalEquivalentWidth = 0;

    for(int i = 0 ; i < m_numberOfPages ; i++){
        m_equivalentWidth.push_back((((double)m_originalPages[0]->height()) / m_originalPages[i]->height()) * m_originalPages[i]->width() );
        m_globalEquivalentWidth += m_equivalentWidth[i];
    }
    m_globalPagesRatio = (double) m_originalPages[0]->height() / m_globalEquivalentWidth;

    for(int i = 0 ; i < m_numberOfPages  ; i++){
        QLabel* temp = new QLabel;
        temp->setPixmap(*m_originalPages[i]);
        m_pagesLabel.push_back(temp);
    }


    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_pagesLabel[0]);
    m_layout->setAlignment(m_pagesLabel[0], m_numberOfPages == 1 ? Qt::AlignCenter : Qt::AlignHCenter | Qt::AlignRight);
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

    setResizePolicy(FIT_SCREEN);
}

/** PagesContainer(const QVector<PageManager*> pages, const QWidget* parent) : QWidget(parent)
 ** {
 **     m_pages = pages;
 **     setResizePolicy(FIT_SCREEN);
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
    emit pagesSizeChanged(m_pagesLabel[0]->pixmap()->width());

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
    emit pagesSizeChanged(m_pagesLabel[0]->pixmap()->width());

}

void PagesContainer::scale(const int newMaxWidth, const int newMaxHeight)
{
    //Sélection des Pixmap nécessitant un redimentionnement et désactivation des màj
    QVector<QPixmap*> selectedPages;
    QVector<int> indirTable; //Mémorise à quel pixmap affecter le futur résultat
    for(int i = 0 ; i < m_numberOfPages ; i++){
        m_pagesLabel[i]->setUpdatesEnabled(false);
        if(! alreadyScaled(i, newMaxWidth, newMaxHeight)){
            selectedPages.push_back(m_originalPages[i]);
            indirTable.push_back(i);
        }
    }

    //Si rien à modifier
    if(indirTable.empty()){refresh(); return;}

    QPixmap(QPixmap::*function)(int, int, Qt::AspectRatioMode, Qt::TransformationMode) const = &QPixmap::scaled;
    QFuture<QPixmap> result = QtConcurrent::mapped(selectedPages, std::bind(function, std::placeholders::_1, newMaxWidth, newMaxHeight, Qt::KeepAspectRatio, Qt::FastTransformation));
    for(int i = 0 ; i < indirTable.size() ; i++){
        m_pagesLabel[indirTable[i]]->setPixmap(result.results()[i]);
    }

    refresh();
    emit pagesSizeChanged(m_pagesLabel[0]->pixmap()->width());


}

bool PagesContainer::alreadyScaled(const int index, const int newMaxWidth, const int newMaxHeight)
{
    double pageRatio((double) m_originalPages[index]->height() / m_originalPages[index]->width()),
           screenRatio((double) newMaxHeight / newMaxWidth);

    if((pageRatio >= screenRatio) && m_pagesLabel[index]->pixmap()->height() == newMaxHeight) return true;
    else if((pageRatio <= screenRatio) && m_pagesLabel[index]->pixmap()->width() == newMaxWidth) return true;
    else return false;
}

void PagesContainer::fitHeight()
{
    QScrollArea* parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget());
    if (parentScrollArea==0) exit(1);

    int spacing(m_layout->spacing() * (m_numberOfPages - 1)),
        H(parentScrollArea->maximumViewportSize().height()),
        h(H - parentScrollArea->horizontalScrollBar()->height()),
        W(parentScrollArea->maximumViewportSize().width() - spacing);

    //Traitement des problèmes de présence de scrollBar
    if (W < h / m_globalPagesRatio){
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

    //Traitement des problèmes de présence de scrollBar
    if (H < w * m_globalPagesRatio){
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
    double screenRatio = (double)parentScrollArea->maximumViewportSize().height() / parentScrollArea->maximumViewportSize().width();

    if (m_globalPagesRatio < screenRatio)
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
    if (m_resizePolicy & FIT_WIDTH)
        fitWidth();
    else if (m_resizePolicy & FIT_HEIGHT)
        fitHeight();
    else if (m_resizePolicy & FIT_SCREEN)
        fitScreen();
    else
        refresh();
}

void PagesContainer::setPolicyPersonnal(const int newWidth)
{
    setResizePolicy(PERSONAL);

    if (newWidth <= 0) return;
    scaleToWidth(newWidth);
}

void PagesContainer::setPolicyFitWidth()
{
    setResizePolicy(FIT_WIDTH);
    applyResizePolicy();
}

void PagesContainer::setPolicyFitHeight()
{
    setResizePolicy(FIT_HEIGHT);
    applyResizePolicy();
}

void PagesContainer::setPolicyFitScreen()
{
    setResizePolicy(FIT_SCREEN);
    applyResizePolicy();
}

//void PagesContainer::changePages(const QVector<PagesManager*> newPages)
//{
//    m_originalPages = newPages;
//    applyResizePolicy();
//}
