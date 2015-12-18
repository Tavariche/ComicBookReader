//#include "PagesContainerSingle.h"

//PagesContainerSingle::PagesContainerSingle(QWidget *parent) : PagesContainer(parent)
//{}

///** PagesContainerSingle::PagesContainerSingle(const vector<PageManager*> pages, const QWidget* parent) :
// **     PagesContainer(pages, parent)
// ** {}
// **/

//PagesContainerSingle::PagesContainerSingle(QPixmap* pagePixmap, QWidget* parent) :
//    PagesContainer(parent)
//{
//    m_originalPagePixmap = pagePixmap;
//    m_redimPagePixmap = new QPixmap(*m_originalPagePixmap);
//    m_pageLabel = new QLabel;
//    m_pageLabel->setPixmap(*m_redimPagePixmap);

//    m_layout = new QHBoxLayout(this);
//    m_layout->addWidget(m_pageLabel);
//    m_layout->setAlignment(m_pageLabel, Qt::AlignCenter);
//    m_layout->setContentsMargins(0, 0, 0, 0);
//    setLayout(m_layout);

//    //Initialisation de la politique de redimensionnement et du curseur
//    emit pagesSizeChanged(m_pageLabel->size().width());
//}

//void PagesContainerSingle::cursorResizePages(const int width)
//{
//    if (width <= 0) return;

//    *m_redimPagePixmap = m_originalPagePixmap->scaledToWidth(width);
//    m_pageLabel->setPixmap(*m_redimPagePixmap);
//}

//void PagesContainerSingle::scaleToHeight(const int newHeight)
//{
//    if(newHeight == m_redimPagePixmap->height()) {refresh(); return;}

//    *m_redimPagePixmap = m_originalPagePixmap->scaledToHeight(newHeight, Qt::SmoothTransformation);
//    m_pageLabel->setPixmap(*m_redimPagePixmap);

//    //Calcul de la nouvelle largeur pour signal de redimensionnement
//    int newWidth((double)newHeight / m_originalPagePixmap->height() * m_originalPagePixmap->width());
//    emit pagesSizeChanged(newWidth);
//}

//void PagesContainerSingle::scaleToWidth(const int newWidth)
//{
//    if(newWidth == m_redimPagePixmap->width()) {refresh(); return;}

//    *m_redimPagePixmap = m_originalPagePixmap->scaledToWidth(newWidth, Qt::SmoothTransformation);
//    m_pageLabel->setPixmap(*m_redimPagePixmap);

//    emit pagesSizeChanged(newWidth);
//}

//void PagesContainerSingle::fitHeight()
//{
//    QScrollArea* parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget());
//    if (parentScrollArea==0) exit(1);

//    int H(parentScrollArea->maximumViewportSize().height()),
//        h(H - parentScrollArea->horizontalScrollBar()->height()),
//        W(parentScrollArea->maximumViewportSize().width());
//    double ratioHW = ((double)m_originalPagePixmap->height()) / m_originalPagePixmap->width();

//    //Traitement des problèmes de présence de scrollBar
//    if (W > H / ratioHW)
//        scaleToHeight(H);
//    else if (W < h / ratioHW)
//        scaleToHeight(h);
//    else
//        scaleToWidth(W);
//}

//void PagesContainerSingle::fitWidth()
//{
//    QScrollArea* parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget());
//    if (parentScrollArea==0) exit(1);

//    int H(parentScrollArea->maximumViewportSize().height()),
//        W(parentScrollArea->maximumViewportSize().width()),
//        w(W - parentScrollArea->verticalScrollBar()->width());
//    double ratioHW = ((double)m_originalPagePixmap->height()) / m_originalPagePixmap->width();

//    //Traitement des problèmes de présence de scrollBar
//    if (H > ratioHW * W)
//        scaleToWidth(W);
//    else if (H < ratioHW * w)
//        scaleToWidth(w);
//    else
//        scaleToHeight(H);
//}

//void PagesContainerSingle::fitScreen()
//{
//    QScrollArea* parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget());

//    double ratioPage = ((double)m_originalPagePixmap->height()) / m_originalPagePixmap->width(),
//           ratioScreen = ((double)parentScrollArea->maximumViewportSize().height() / parentScrollArea->maximumViewportSize().width());

//    if (ratioPage < ratioScreen)
//        fitWidth();
//    else fitHeight();
//}

//void PagesContainerSingle::refresh() const
//{
//    //Rien trouvé de mieux pour rafraichir l'affichage ><
//    m_pageLabel->hide();
//    m_pageLabel->show();
//}
