//#include "PagesContainerDouble.h"


//PagesContainerDouble::PagesContainerDouble(QWidget *parent) : PagesContainer(parent)
//{}

///** PagesContainerDouble::PagesContainerDouble(const vector<PageManager*> pages, const QWidget* parent) :
// **     PagesContainer(pages, parent)
// ** {}
// **/

//PagesContainerDouble::PagesContainerDouble(QPixmap* leftPagePixmap, QPixmap* rightPagePixmap, QWidget* parent) :
//    PagesContainer(parent)
//{
//    m_LeftOriginalPagePixmap = leftPagePixmap;
//    m_LeftRedimPagePixmap = new QPixmap(*m_LeftOriginalPagePixmap);
//    m_LeftPageLabel = new QLabel;
//    m_LeftPageLabel->setPixmap(*m_LeftRedimPagePixmap);

//    m_RightOriginalPagePixmap = rightPagePixmap;
//    m_RightRedimPagePixmap = new QPixmap(*m_RightOriginalPagePixmap);
//    m_RightPageLabel = new QLabel;
//    m_RightPageLabel->setPixmap(*m_RightRedimPagePixmap);

//    m_layout = new QHBoxLayout(this);
//    m_layout->addWidget(m_LeftPageLabel);
//    m_layout->setAlignment(m_LeftPageLabel, Qt::AlignHCenter | Qt::AlignRight);
//    m_layout->addWidget(m_RightPageLabel);
//    m_layout->setAlignment(m_RightPageLabel, Qt::AlignHCenter | Qt::AlignLeft);
//    m_layout->setContentsMargins(0, 0, 0, 0);
//    m_layout->setSpacing(15);
//    setLayout(m_layout);

//    //Initialisation de la politique de redimensionnement et du curseur
//    emit pagesSizeChanged(m_LeftPageLabel->size().width());
//}

//void PagesContainerDouble::cursorResizePages(const int width)
//{
//    if (width <= 0) return;

//    *m_LeftRedimPagePixmap = m_LeftOriginalPagePixmap->scaledToWidth(width);
//    m_LeftPageLabel->setPixmap(*m_LeftRedimPagePixmap);

//    *m_RightRedimPagePixmap = m_RightOriginalPagePixmap->scaledToWidth(width);
//    m_RightPageLabel->setPixmap(*m_RightRedimPagePixmap);
//}

//void PagesContainerDouble::scaleToHeight(const int indice, const int newHeight)
//{
//    if (indice == 1) {//Page gauche
//        if(newHeight == m_LeftRedimPagePixmap->height()) {refresh(); return;}

//        *m_LeftRedimPagePixmap = m_LeftOriginalPagePixmap->scaledToHeight(newHeight, Qt::SmoothTransformation);
//        m_LeftPageLabel->setPixmap(*m_LeftRedimPagePixmap);

//        //Calcul de la nouvelle largeur pour signal de redimensionnement
//        //L'image gauche pilote le curseur provisoirement
//        int newWidth((double)newHeight / m_LeftOriginalPagePixmap->height() * m_LeftOriginalPagePixmap->width());
//        emit pagesSizeChanged(newWidth);

//    } else if (indice == 2) { //Page droite
//        if(newHeight == m_RightRedimPagePixmap->height()) {refresh(); return;}

//        *m_RightRedimPagePixmap = m_RightOriginalPagePixmap->scaledToHeight(newHeight, Qt::SmoothTransformation);
//        m_RightPageLabel->setPixmap(*m_RightRedimPagePixmap);
//    }

//}

//void PagesContainerDouble::scaleToWidth(const int indice, const int newWidth)
//{
//    if (indice == 1) {
//        if(newWidth == m_LeftRedimPagePixmap->width()) {refresh(); return;}

//        *m_LeftRedimPagePixmap = m_LeftOriginalPagePixmap->scaledToWidth(newWidth, Qt::SmoothTransformation);
//        m_LeftPageLabel->setPixmap(*m_LeftRedimPagePixmap);

//        //L'image gauche pilote le curseur provisoirement
//        emit pagesSizeChanged(newWidth);

//    } else if (indice == 2) {
//        if(newWidth == m_RightRedimPagePixmap->width()) {refresh(); return;}

//        *m_RightRedimPagePixmap = m_RightOriginalPagePixmap->scaledToWidth(newWidth, Qt::SmoothTransformation);
//        m_RightPageLabel->setPixmap(*m_RightRedimPagePixmap);
//    }
//}

//void PagesContainerDouble::scale(const int indice, const int newMaxWidth, const int newMaxHeight)
//{
//    if (indice == 1) {
//        if(newMaxWidth == m_LeftRedimPagePixmap->width() && newMaxHeight == m_LeftRedimPagePixmap->height()) {refresh(); return;}

//        *m_LeftRedimPagePixmap = m_LeftOriginalPagePixmap->scaled(newMaxWidth, newMaxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        m_LeftPageLabel->setPixmap(*m_LeftRedimPagePixmap);

//        //L'image gauche pilote le curseur provisoirement
//        emit pagesSizeChanged(m_LeftRedimPagePixmap->width());

//    } else if (indice == 2) {
//        if(newMaxWidth == m_RightRedimPagePixmap->width() && newMaxHeight == m_RightRedimPagePixmap->height()) {refresh(); return;}

//        *m_RightRedimPagePixmap = m_RightOriginalPagePixmap->scaled(newMaxWidth, newMaxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//        m_RightPageLabel->setPixmap(*m_RightRedimPagePixmap);
//    }
//}

//void PagesContainerDouble::fitHeight()
//{
//    QScrollArea* parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget());
//    if (parentScrollArea==0) exit(1);

//    int spacing(m_layout->spacing()),
//        H(parentScrollArea->maximumViewportSize().height()),
//        h(H - parentScrollArea->horizontalScrollBar()->height()),
//        W(parentScrollArea->maximumViewportSize().width() - spacing);
//    double rightEquivalentWidth((((double)m_LeftOriginalPagePixmap->height()) / m_RightOriginalPagePixmap->height())* m_RightOriginalPagePixmap->width()),
//           ratioHW = ((double)m_LeftOriginalPagePixmap->height()) / (m_LeftOriginalPagePixmap->width() + rightEquivalentWidth);

//    //Traitement des problèmes de présence de scrollBar
//    if (W < h / ratioHW){
//        scaleToHeight(1,h);
//        scaleToHeight(2,h);
//    }else{
//        scale(1, W/2, H);
//        scale(2, W/2, H);
//    }
//}

//void PagesContainerDouble::fitWidth()
//{
//    QScrollArea* parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget());
//    if (parentScrollArea==0) exit(1);

//    int spacing(m_layout->spacing()),
//        H(parentScrollArea->maximumViewportSize().height()),
//        W(parentScrollArea->maximumViewportSize().width() - spacing),
//        w(W - parentScrollArea->verticalScrollBar()->width());
//    double rightEquivalentWidth((((double)m_LeftOriginalPagePixmap->height()) / m_RightOriginalPagePixmap->height())* m_RightOriginalPagePixmap->width()),
//           ratioHW = ((double)m_LeftOriginalPagePixmap->height()) / (m_LeftOriginalPagePixmap->width() + rightEquivalentWidth);

//    //Traitement des problèmes de présence de scrollBar
//    if (H < ratioHW * w){
//        scaleToWidth(1,w/2);
//        scaleToWidth(2,w/2);
//    }else{
//        scale(1, W/2, H);
//        scale(2, W/2, H);
//    }
//}

//void PagesContainerDouble::fitScreen()
//{
//    QScrollArea* parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget()->parentWidget());

//    int spacing(m_layout->spacing());
//    double ratioPage = ((double)m_LeftOriginalPagePixmap->height()) / (m_LeftOriginalPagePixmap->width() * 2 + spacing),
//           ratioScreen = ((double)parentScrollArea->maximumViewportSize().height() / parentScrollArea->maximumViewportSize().width());

//    if (ratioPage < ratioScreen)
//        fitWidth();
//    else fitHeight();
//}

//void PagesContainerDouble::refresh() const
//{
//    //Rien trouvé de mieux pour rafraichir l'affichage ><
//    m_LeftPageLabel->hide();
//    m_RightPageLabel->hide();
//    m_LeftPageLabel->show();
//    m_RightPageLabel->show();
//}
