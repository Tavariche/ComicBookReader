#include <QtConcurrent/QtConcurrent>
#include <functional>
#include "PagesContainer.h"

#define DEFAULT_POLICY FIT_SCREEN

#define PAGES_GAP 15

//Opérations communes aux constructeurs
void PagesContainer::basicInit()
{
    m_resizingThread.clear();
    setBackgroundRole(QPalette::Dark);
    m_scrollArea = this;
    m_widget = new QWidget(m_scrollArea);
    m_scrollArea->setWidget(m_widget);
    setWidgetResizable(true);
    fullScreenEnabled = false;
    m_parent = parentWidget();
    m_buffer = 0;

    setResizePolicy(DEFAULT_POLICY);

    connect(this, SIGNAL(resized()), this, SLOT(applyResizePolicy()));
}

//Constructeur par défaut
PagesContainer::PagesContainer(QWidget* parent) : CBScrollArea(parent)
{
    basicInit();
}

//Constructeur avec initialisation du buffer associé
PagesContainer::PagesContainer(PagesBuffer *buffer, QWidget* parent) : CBScrollArea(parent)
{
    basicInit();

    //Remplissage du pagesContainer
    m_buffer = buffer ;
    m_resizingThread.fill(QFuture<void>(), m_buffer->getNumberOfBlocs());
}

//Changement du buffer de référence et construction de l'affichage correspondant
void PagesContainer::updateDisplay()
{
    int numberOfPages(m_buffer->getNumberOfPages());

    clearLayout(m_widget->layout()); //Obligatoire si un layout est déjà en place (pas d'écrasement possible)
    m_layout = new QHBoxLayout(this); //Disposition horizontale
    m_layout->addWidget(getResizedPage(0));

    //Page de gauche centrée si seule et à droite de son emplacement si suivie
    m_layout->setAlignment(getResizedPage(0), numberOfPages == 1 ? Qt::AlignCenter : Qt::AlignHCenter | Qt::AlignRight);
    //Pages intérmédiaires centrées
    for(int i = 1 ; i <  numberOfPages - 1 ; i++){
        m_layout->addWidget(getResizedPage(i));
        m_layout->setAlignment(getResizedPage(i), Qt::AlignCenter);
    }

    //Dernière page alignée à gauche
    if(numberOfPages >= 2){
        m_layout->addWidget(getResizedPage(numberOfPages - 1));
        m_layout->setAlignment(getResizedPage(numberOfPages - 1), Qt::AlignHCenter | Qt::AlignLeft);
    }

    //Définit les marges autour des pages puis l'écart entre deux pages
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(PAGES_GAP);

    m_widget->setLayout(m_layout); //Application du layout

    applyResizePolicy(); //Application de la politique de redimentionnement aux pages
}


//Ajustement des pages à la hauteur de l'écran
void PagesContainer::fitHeight(int index)
{
    //Si l'index est spécifié entre 0 et 4 on n'applique le redimensionement qu'à celui-ci
    bool respectIndex = (index != NONE);

    if(m_buffer->getNumberOfBlocs() == 0) return; //Si pas de pages on a terminé

    int H(m_scrollArea->maximumViewportSize().height()), //Hauteur écran sans scrollbar
        h(H - m_scrollArea->horizontalScrollBar()->height()); //Hauteur écran avec scrollbar

    for(int i = respectIndex ? index : 0 ; i < m_buffer->getNumberOfBlocs() ; i++){
        int numberOfPages = m_buffer->getNumberOfPages(i) ; //Nombre de pages à l'écran
        if (numberOfPages == 0) continue ;

        int spacing(m_layout->spacing() * (numberOfPages - 1)), //Ecart total entre les pages
            W(m_scrollArea->maximumViewportSize().width() - spacing); //Largeur de l'écran sans les écarts

        //Calcul du redimentionnent à appliquer
        if (W < h / m_buffer->getPagesRatio(i)){
            m_resizingThread[i] = QtConcurrent::map(*m_buffer->getPages(i), std::bind(&PageManager::scaleToHeight, std::placeholders::_1, h));
        }else{
            m_resizingThread[i] = QtConcurrent::map(*m_buffer->getPages(i), std::bind(&PageManager::scale, std::placeholders::_1, W/numberOfPages, H));
        }

        if(i == 0) refresh();  //Pages prioritaires (affichage)
        //On ne continue pas la boucle si on ne devait appliquer qu'à l'index
        if(respectIndex) return;
    }
}

//Ajustement des pages à la largeur de l'écran
//Fonctionnement identique à fitHeight
void PagesContainer::fitWidth(int index, int specifiedWidth)
{
    bool respectIndex = (index != NONE);

    if(m_buffer->getNumberOfBlocs() == 0) return;

    int H(m_scrollArea->maximumViewportSize().height());

    for(int i = respectIndex ? index : 0 ; i < m_buffer->getNumberOfBlocs() ; i++){
        int numberOfPages = m_buffer->getNumberOfPages(i) ;
        if (numberOfPages == 0) continue ;

        int spacing(m_layout->spacing() * (numberOfPages - 1)),
            W(m_scrollArea->maximumViewportSize().width() - spacing),
            w(W - m_scrollArea->verticalScrollBar()->width());
        if (specifiedWidth != 0){
            m_resizingThread[i] = QtConcurrent::map(*m_buffer->getPages(i), std::bind(&PageManager::scaleToWidth, std::placeholders::_1, specifiedWidth));
        }else if (H < w * m_buffer->getPagesRatio(i)){
            m_resizingThread[i] = QtConcurrent::map(*m_buffer->getPages(i), std::bind(&PageManager::scaleToWidth, std::placeholders::_1, w/numberOfPages));
        }else{
            m_resizingThread[i] = QtConcurrent::map(*m_buffer->getPages(i), std::bind(&PageManager::scale, std::placeholders::_1, W/numberOfPages, H));
        }
        if(i == 0) refresh();
        if(respectIndex) return;
    }
}

//Ajustement à l'écran
void PagesContainer::fitScreen()
{
    if(m_buffer->getNumberOfBlocs() == 0) return;

    //Ratio hauteur / largeur de l'écran
    double screenRatio = (double)m_scrollArea->maximumViewportSize().height() / m_scrollArea->maximumViewportSize().width();

    //Déterminer si l'ajustement à l'écran correspond à un ajustement à la largeur ou à la hauteur
    for(int i = 0 ; i < m_buffer->getNumberOfBlocs() ; i++){
        if (m_buffer->getPagesRatio(i) < screenRatio) fitWidth(i);
        else fitHeight(i);
    }
}

//Rafraichissement de l'affichage
void PagesContainer::refresh(int index)
{
    finishThreads(false, index);
    for(QVector<PageManager*>::iterator it = m_buffer->getPages(index)->begin() ; it != m_buffer->getPages(index)->end() ; it ++)
        (*it)->refresh();
    if(index == 0) emit pagesSizeChanged(getResizedPage(index)->pixmap()->width());
}


//Terminaison des threads avec interruption et/ou sélection ou rien
void PagesContainer::finishThreads(bool cancelThreads, int index)
{
    bool respectIndex = index >= 0 && index <= 4 ;
    for(int i = respectIndex ? index : 0 ; i < 5 && cancelThreads ; i ++){
        if(m_resizingThread[i].isRunning()) m_resizingThread[i].cancel();
        if (respectIndex){return;}
    }
    for(int i = respectIndex ? index : 0 ; i < 5 ; i ++){
        if(!m_resizingThread[i].isFinished()) m_resizingThread[i].waitForFinished();
        if (respectIndex){return;}
    }

    //On passera toujours ici avant tout redimensionnement du buffer et une fois que ceux-ci sont terminés
    //C'est un bon endroit pour réinitialiser le flag alreadyResized des PagesMAnager
    if(! respectIndex) m_buffer->resetAlreadyResized();
}


//Commutation du mode plein écran
void PagesContainer::toggleFullScreen(){
    if(!fullScreenEnabled){
        setParent(0);
        setWindowFlags(Qt::WindowStaysOnTopHint);
        showFullScreen();
        applyResizePolicy();
    } else {
        //Cas particulier du parent QMainWindows
        QMainWindow* castedParent = dynamic_cast<QMainWindow*>(m_parent);
        if(castedParent) castedParent->setCentralWidget(this);
        setParent(m_parent);
        applyResizePolicy();
        m_parent->activateWindow();
    }
    fullScreenEnabled = !fullScreenEnabled;
}

//Application de la politique de redimentionnement
void PagesContainer::applyResizePolicy()
{
    if (!m_buffer || m_buffer->getNumberOfBlocs() == 0) return;

    finishThreads();

    if (m_resizePolicy & FIT_WIDTH)
    {
        fitWidth();
    }
    else if (m_resizePolicy & FIT_HEIGHT)
    {
        fitHeight();
    }
    else if (m_resizePolicy & FIT_SCREEN)
    {
        fitScreen();
    }
    else if (m_resizePolicy & PERSONAL)
    {
        fitWidth(NONE, m_customWidth);
    }
    else
    {
        refresh();
    }
}

//Foncitons de changement de la politique
//Il aurait été possible den'en utiliser qu'une avec paramètre mais leur utilisation entant que slot aurait été très compliquée
void PagesContainer::setResizePolicy(const ResizePolicy newPolicy)
{
    m_resizePolicy = newPolicy;
}

void PagesContainer::setPersonalPolicy(int newWidth)
{
    setResizePolicy(PERSONAL);
    m_customWidth = newWidth;
    applyResizePolicy();
}

void PagesContainer::setFitWidthPolicy()
{
    setResizePolicy(FIT_WIDTH);
    applyResizePolicy();
}

void PagesContainer::setFitHeightPolicy()
{
    setResizePolicy(FIT_HEIGHT);
    applyResizePolicy();
}

void PagesContainer::setFitScreenPolicy()
{
    setResizePolicy(FIT_SCREEN);
    applyResizePolicy();
}

PagesContainer::~PagesContainer()
{
    finishThreads();
    parentWidget()->parentWidget()->deleteLater();
}

//Destruction d'un layout
void clearLayout(QLayout *layout)
{
    if(layout == 0) return;

    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if(item->widget()) item->widget()->hide();
        layout->removeItem(item);
    }
    delete layout;
}

//Fermeture du logiciel entier si fermeture du pagesContainer
//Gère le beug du plein écran
void PagesContainer::closeEvent(QCloseEvent* e)
{
    qApp->quit();
    e->accept();
}
