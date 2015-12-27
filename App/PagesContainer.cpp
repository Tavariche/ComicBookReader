#include <QtConcurrent/QtConcurrent>
#include <functional>
#include "PagesContainer.h"

//Constructeur par défaut
PagesContainer::PagesContainer(QWidget* parent) : QWidget(parent)
{
    m_numberOfPages = 0;
    m_globalPagesRatio = 1; //Arbitraire, évite une éventuelle division par 0
    m_layout = new QHBoxLayout(this);
    m_parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget());

    setResizePolicy(ResizePolicy::fitScreen);
}

//Constructeur avec initialisation des pages
PagesContainer::PagesContainer(const QVector<QPixmap*> pages, QWidget* parent) : QWidget(parent)
{
    m_numberOfPages = 0; //Evite le bug de refresh lors de l'appel à setResizePolicy

    //Récupération de la scrollArea parente
    m_parentScrollArea = dynamic_cast<QScrollArea*>(parentWidget());
    if(! m_parentScrollArea) exit(-1);

    //Politique de redimentionnement par défaut arbitraire
    setResizePolicy(ResizePolicy::fitScreen);

    //Remplissage du pagesContainer
    setPages(pages);
}

//Fonction de remplissage du page container avec de nouvelles pages
void PagesContainer::setPages(const QVector<QPixmap*> newPages)
{
    m_originalPages = newPages;
    m_numberOfPages = (int) m_originalPages.size();

    //Calcule du ratio équivalent global des pages
    int globalEquivalentWidth = 0;
    for(int i = 0 ; i < m_numberOfPages ; i++)
        globalEquivalentWidth += (double)m_originalPages[0]->height() / m_originalPages[i]->height() * m_originalPages[i]->width();
    m_globalPagesRatio = (double) m_originalPages[0]->height() / globalEquivalentWidth;

    //Remplissage initial des QLabels par les originaux ; Un redimensionnement aura lieu juste après.
    for(int i = 0 ; i < m_numberOfPages  ; i++){
        QLabel* temp = new QLabel;
        temp->setPixmap(*m_originalPages[i]);
        m_pagesLabel.push_back(temp);
    }

    delete layout(); //Obligatoire si un layout est déjà en place (pas d'écrasement possible)
    m_layout = new QHBoxLayout(this); //Disposition horizontale
    m_layout->addWidget(m_pagesLabel[0]);
    //Page de gauche centrée si seule est à droite de son emplacement si suivie
    m_layout->setAlignment(m_pagesLabel[0], m_numberOfPages == 1 ? Qt::AlignCenter : Qt::AlignHCenter | Qt::AlignRight);
    //Pages intérmédiaires centrées
    for(int i = 1 ; i < m_numberOfPages - 1 ; i++){
        m_layout->addWidget(m_pagesLabel[i]);
        m_layout->setAlignment(m_pagesLabel[i], Qt::AlignCenter);
    }
    //Dernière page alignée à gauche
    if(m_numberOfPages >= 2){
        m_layout->addWidget(m_pagesLabel[m_numberOfPages - 1]);
        m_layout->setAlignment(m_pagesLabel[m_numberOfPages - 1], Qt::AlignHCenter | Qt::AlignLeft);
    }
    //Définit les marges autour des pages puis l'écart entre deux pages
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(15);

    applyResizePolicy(); //Application de la politique de redimentionnement aux pages

    setLayout(m_layout); //App+lication du layout
}

//Futur constructeur
/** PagesContainer(const QVector<PageManager*> pages, const QWidget* parent) : QWidget(parent)
 ** {
 **     m_pages = pages;
 **     setResizePolicy(ResizePolicy::fitScreen);
 ** }
 **/

//Redimentionnement de toutes les pages à la hauteur newHeight
void PagesContainer::scaleToHeight(const int newHeight)
{
    //Sélection des Pixmap nécessitant un redimentionnement et désactivation des màj des QLabels
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

    //Le parallélisme sera plutôt dans le buffer et la fonction de redimentionement dans le pageManager à l'avenir
    QFuture<QPixmap> result = QtConcurrent::mapped(selectedPages, std::bind(&QPixmap::scaledToHeight, std::placeholders::_1, newHeight, Qt::FastTransformation));
    for(int i = 0 ; i < indirTable.size() ; i++){ //Mise à jour des QLabels modifiés
        m_pagesLabel[indirTable[i]]->setPixmap(result.results()[i]);
    }

    refresh(); //Mise à jour de l'affichage
    emit pagesSizeChanged(m_pagesLabel[0]->pixmap()->width()); //Indique notamment au curseur de zoom la nouvelle largeur des pages (indexée sur celle de la première)

}

//Redimentionnement de toutes les pages à la largeur newWidth
//Fonctionne comme scaleToHeight
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

//Redimentionnement de toutes les pages dans les limites newMaxWidth et newMaxHeight
//Fonctionnement presque identique à scaleToHeight
void PagesContainer::scale(const int newMaxWidth, const int newMaxHeight)
{
    //Sélection des Pixmap nécessitant un redimentionnement et désactivation des màj
    QVector<QPixmap*> selectedPages;
    QVector<int> indirTable; //Mémorise à quel pixmap affecter le futur résultat
    double screenRatio((double) newMaxHeight / newMaxWidth);
    for(int i = 0 ; i < m_numberOfPages ; i++){
        m_pagesLabel[i]->setUpdatesEnabled(false);

        double pageRatio((double) m_originalPages[i]->height() / m_originalPages[i]->width());
        //Le test contient les deux façons qu'une image peut avoir d'être bien dimensionnée et une négation au début
        if(! (((pageRatio >= screenRatio) && m_pagesLabel[i]->pixmap()->height() == newMaxHeight) ||
          ((pageRatio <= screenRatio) && m_pagesLabel[i]->pixmap()->width() == newMaxWidth))){
            selectedPages.push_back(m_originalPages[i]);
            indirTable.push_back(i);
        }
    }

    //Si rien à modifier
    if(indirTable.empty()){refresh(); return;}

    auto function = static_cast<QPixmap(QPixmap::*)(int, int, Qt::AspectRatioMode, Qt::TransformationMode) const> (&QPixmap::scaled);
    QFuture<QPixmap> result = QtConcurrent::mapped(selectedPages, std::bind(function, std::placeholders::_1, newMaxWidth, newMaxHeight, Qt::KeepAspectRatio, Qt::FastTransformation));
    for(int i = 0 ; i < indirTable.size() ; i++){
        m_pagesLabel[indirTable[i]]->setPixmap(result.results()[i]);
    }

    refresh();
    emit pagesSizeChanged(m_pagesLabel[0]->pixmap()->width());
}

//Ajustement des pages à la hauteur de l'écran
void PagesContainer::fitHeight()
{
    if(m_numberOfPages == 0) return; //Si pas de pages

    int spacing(m_layout->spacing() * (m_numberOfPages - 1)), //Ecart inter-pages
        H(m_parentScrollArea->maximumViewportSize().height()), //Hauteur écran sans scrollbar
        h(H - m_parentScrollArea->horizontalScrollBar()->height()), //Hauteur écran avec scrollbar
        W(m_parentScrollArea->maximumViewportSize().width() - spacing); //Largeur de l'écran sans scrollbar

    //Calcul du redimentionnent à appliquer
    if (W < h / m_globalPagesRatio){
        scaleToHeight(h);
    }else{
        scale(W/m_numberOfPages, H);
    }
}

//Ajustement des pges à la largeur de l'écran
//Fonctionnement identique à fitHeight
void PagesContainer::fitWidth()
{
    if(m_numberOfPages == 0) return;

    int spacing(m_layout->spacing() * (m_numberOfPages - 1)),
        H(m_parentScrollArea->maximumViewportSize().height()),
        W(m_parentScrollArea->maximumViewportSize().width() - spacing),
        w(W - m_parentScrollArea->verticalScrollBar()->width());

    //Traitement des problèmes de présence de scrollBar
    if (H < w * m_globalPagesRatio){
        scaleToWidth(w/m_numberOfPages);
    }else{
        scale(W/m_numberOfPages, H);
    }
}

//Ajustement à l'écran
void PagesContainer::fitScreen()
{
    if(m_numberOfPages == 0) return;

    //Ratio hauteur / largeur de l'écran
    double screenRatio = (double)m_parentScrollArea->maximumViewportSize().height() / m_parentScrollArea->maximumViewportSize().width();

    //Déterminer si l'ajustement à l'écran correspond à un ajustement à la largeur ou à la hauteur
    if (m_globalPagesRatio < screenRatio) fitWidth();
    else fitHeight();
}

//Rafraichissement de l'affichage
void PagesContainer::refresh()
{
    for(int i = 0 ; i < m_numberOfPages ; i ++){
        m_pagesLabel[i]->setUpdatesEnabled(true); //Réactivation des modifs
        m_pagesLabel[i]->update(); //Mise à jour des QLabels
        //Cacher afficher est le seul moyen que j'ai trouvé pour corriger les problèmes d'affichage quend le QLabel n'était pas redimensionné
        m_pagesLabel[i]->hide();
        m_pagesLabel[i]->show();
    }
}

//Application de la politique de redimentionnement
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

//Foncitons de changement de la politique
//Il aurait été possible den'en utiliser qu'une avec paramètre mais leur utilisation entant que slot aurait été très compliquée
void PagesContainer::setResizePolicy(const ResizePolicy newPolicy)
{
    m_resizePolicy = newPolicy;
    applyResizePolicy();
}

void PagesContainer::setPersonalPolicy(int newWidth)
{
    setResizePolicy(ResizePolicy::personal);
    scaleToWidth(newWidth);
}

void PagesContainer::setFitWidthPolicy()
{
    setResizePolicy(ResizePolicy::fitWidth);
    applyResizePolicy();
}

void PagesContainer::setFitHeightPolicy()
{
    setResizePolicy(ResizePolicy::fitHeight);
    applyResizePolicy();
}

void PagesContainer::setFitScreenPolicy()
{
    setResizePolicy(ResizePolicy::fitScreen);
    applyResizePolicy();
}
