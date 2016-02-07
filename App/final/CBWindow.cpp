#include <QtSvg>
#include <QVector>
#include <QMessageBox>  //  Pour debugging.
#include "CBWindow.h"
#include "PagesContainer.h"
#include "CBScrollArea.h"
#include "UncheckableActionGroup.h"
#include "ThumbnailsPanel.h"
#include "PageNbField.h"


CBWindow::CBWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Allocation des modules du programme
    navigation_manager = new NavigationManager();
    dockMiniatures = new QDockWidget(this);
    comic_book = new ComicBook();
    pagesContainer = new PagesContainer(this);

    ///Les actions
    //Quitter
    QAction *actQuitter = new QAction("&Quitter", this);
    actQuitter->setIcon(QIcon(":/new/Icons/images/blackCross.svg"));
    connect(actQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    actQuitter->setShortcut(Qt::ALT + Qt::Key_F4);


    //Groupe des actions de dimensionnement
    UncheckableActionGroup* dimActGroup = new UncheckableActionGroup(this);
    QAction *actFitHeight = new QAction("Ajuster à la &Hauteur", this);
    actFitHeight->setCheckable(true);
    actFitHeight->setIcon(QIcon(":/new/Icons/images/fitHeight.svg"));
    actFitHeight->setShortcut(Qt::CTRL + Qt::Key_3);
    dimActGroup->addAction(actFitHeight);

    QAction *actFitWidth = new QAction("Ajuster à la largeur", this);
    actFitWidth->setCheckable(true);
    actFitWidth->setIcon(QIcon(":/new/Icons/images/fitWidth.svg"));
    actFitWidth->setShortcut(Qt::CTRL + Qt::Key_2);
    dimActGroup->addAction(actFitWidth);

    QAction *actFitScreen = new QAction("ajuster à l'écran", this);
    actFitScreen->setCheckable(true);
    actFitScreen->setIcon(QIcon(":/new/Icons/images/fitScreen.svg"));
    actFitScreen->setChecked(true);
    actFitScreen->setShortcut(Qt::CTRL + Qt::Key_1);
    dimActGroup->addAction(actFitScreen);

    //Action de commutation du mode plein écran
    QAction *actFullScreen = new QAction("Activer le mode plein écran", this);
    actFullScreen->setCheckable(true);
    actFullScreen->setIcon(QIcon(":/new/Icons/images/fullScreen.svg"));
    actFullScreen->setShortcut(QKeySequence::FullScreen);

    //Actions de navigation
    QAction *actNextPage = new QAction("Page suivante", this);
    actNextPage->setIcon(QIcon(":/new/Icons/images/rightSingle.svg"));
    actNextPage->setShortcut(Qt::Key_Right);
    QAction *actPreviousPage = new QAction("Page précédente", this);
    actPreviousPage->setIcon(QIcon(":/new/Icons/images/leftSingle.svg"));
    actPreviousPage->setShortcut(Qt::Key_Left);
    QAction *actFirstPage = new QAction("Première page", this);
    actFirstPage->setIcon(QIcon(":/new/Icons/images/leftDouble.svg"));
    actFirstPage->setShortcut(Qt::ALT + Qt::Key_Left);
    QAction *actLastPage = new QAction("Dernière page", this);
    actLastPage->setIcon(QIcon(":/new/Icons/images/rightDouble.svg"));
    actLastPage->setShortcut(Qt::ALT + Qt::Key_Right);

    connect(actNextPage, SIGNAL(triggered(bool)), navigation_manager, SLOT(goToNextPage()));
    connect(actPreviousPage, SIGNAL(triggered(bool)), navigation_manager, SLOT(goToPreviousPage()));
    connect(actFirstPage, SIGNAL(triggered(bool)), navigation_manager, SLOT(goToFirstPage()));
    connect(actLastPage, SIGNAL(triggered(bool)), navigation_manager, SLOT(goToLastPage()));

    //Action d'affichage du thumbnailsPanel
    QAction *actDispThumbnailsPanel = new QAction("Afficher les miniatures", this);
    actDispThumbnailsPanel->setIcon(QIcon(":/new/Icons/images/miniatures.svg"));
    actDispThumbnailsPanel->setShortcut(Qt::Key_F1);
    actDispThumbnailsPanel->setCheckable(true);
    connect(actDispThumbnailsPanel, SIGNAL(triggered(bool)), this, SLOT(displayDockMiniatures(bool)));


    ///Les menus
    //Fichiers
    QMenu *menuFichiers = menuBar()->addMenu("&Fichier");
    menuFichiers->addAction(actQuitter);
        ///Ajouter l'ouverture de CB

    //Affichage
    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
    menuAffichage->addAction(actFitHeight);
    menuAffichage->addAction(actFitWidth);
    menuAffichage->addAction(actFitScreen);
    menuAffichage->addAction(actFullScreen);

    menuAffichage->addSeparator();
    menuAffichage->addAction(actDispThumbnailsPanel);

    menuAffichage->addSeparator();
    QMenu* nbPages = menuAffichage->addMenu("Pages par écran");
        //Définition compacte naïve des actions de sélection du nombre de pages par écran
    QActionGroup* nbPagesGroup = new QActionGroup(this);
    nbPagesGroup->setExclusive(true);
    auto act = nbPagesGroup->addAction("1");
         act->setShortcut(Qt::ALT + Qt::CTRL + Qt::Key_1); act->setCheckable(true);
         nbPages->addAction(act); if(DEFAULT_PAGE_NUMBER == 1) act->setChecked(true);
         act = nbPagesGroup->addAction("2");
         act->setShortcut(Qt::ALT + Qt::CTRL + Qt::Key_2); act->setCheckable(true);
         nbPages->addAction(act); if(DEFAULT_PAGE_NUMBER == 2) act->setChecked(true);
         act = nbPagesGroup->addAction("3");
         act->setShortcut(Qt::ALT + Qt::CTRL + Qt::Key_3); act->setCheckable(true);
         nbPages->addAction(act); if(DEFAULT_PAGE_NUMBER == 3) act->setChecked(true);
         act = nbPagesGroup->addAction("4");
         act->setShortcut(Qt::ALT + Qt::CTRL + Qt::Key_4); act->setCheckable(true);
         nbPages->addAction(act); if(DEFAULT_PAGE_NUMBER == 4) act->setChecked(true);
         //Connexions
     auto it = nbPages->actions().constBegin();
     connect(*it++, SIGNAL(triggered(bool)), navigation_manager, SLOT(setNumberPagesDisplayed1()));
     connect(*it++, SIGNAL(triggered(bool)), navigation_manager, SLOT(setNumberPagesDisplayed2()));
     connect(*it++, SIGNAL(triggered(bool)), navigation_manager, SLOT(setNumberPagesDisplayed3()));
     connect(*it++, SIGNAL(triggered(bool)), navigation_manager, SLOT(setNumberPagesDisplayed4()));

    //Navigation
    QMenu *menuNavigation = menuBar()->addMenu("&Navigation");
    menuNavigation->addAction(actNextPage);
    menuNavigation->addAction(actPreviousPage);
    menuNavigation->addAction(actFirstPage);
    menuNavigation->addAction(actLastPage);

    ///La toolbar
    QToolBar *RightToolBar = new QToolBar("RightToolBar", this);
    RightToolBar->setMovable(false);
    addToolBar(Qt::RightToolBarArea, RightToolBar);
    RightToolBar->addAction(actQuitter);

    RightToolBar->addSeparator();
    RightToolBar->addAction(actFitScreen);
    RightToolBar->addAction(actFitWidth);
    RightToolBar->addAction(actFitHeight);

    RightToolBar->addSeparator();
    RightToolBar->addAction(actFullScreen);

    ///Le dock miniatures
    dockMiniatures->setWindowTitle("Miniatures");
    dockMiniatures->setMinimumWidth(THUMBNAILS_PANEL_MIN_WIDTH);
    dockMiniatures->setMaximumWidth(MAX_THUMBNAILS_WIDTH);
    dockMiniatures->setFeatures(QDockWidget::NoDockWidgetFeatures);
    //Contenu du dock
    ThumbnailsPanel* thumbnailsPanel = new ThumbnailsPanel(comic_book, navigation_manager, dockMiniatures);
    dockMiniatures->setWidget(thumbnailsPanel);
    addDockWidget(Qt::LeftDockWidgetArea, dockMiniatures);
    //Affichage du dock
    actDispThumbnailsPanel->trigger();

    ///La zone d'affichage principale
    //Ajout des actions utiles en mode plein écran (perte du contrôle sur la mainWindow)
    pagesContainer->addActions(menuAffichage->actions());
    pagesContainer->addActions(menuFichiers->actions());
    pagesContainer->addActions(menuNavigation->actions());
    setCentralWidget(pagesContainer);
    //Il se construira au signal suivant
    connect (navigation_manager->getPagesBuffer(), SIGNAL(bufferUpdated(PagesBuffer*)),
             pagesContainer, SLOT(setBuffer(PagesBuffer*)));
    //Signaux de redimensionnement et passage en plein écran
    connect(actFitHeight, SIGNAL(triggered(bool)), pagesContainer, SLOT(setFitHeightPolicy()));
    connect(actFitWidth, SIGNAL(triggered(bool)), pagesContainer, SLOT(setFitWidthPolicy()));
    connect(actFitScreen, SIGNAL(triggered(bool)), pagesContainer, SLOT(setFitScreenPolicy()));
    connect(actFullScreen, SIGNAL(triggered(bool)), pagesContainer, SLOT(toggleFullScreen()));

    ///La statusbar qui n'en est pas une
    QStatusBar *statusBar = new QStatusBar(this);
    statusBar->setSizeGripEnabled(false);
    QSlider *slider = new QSlider(Qt::Horizontal, statusBar);
    slider->setFixedWidth(150);
    //Plage de zoom
    slider->setRange(200, 2000);
    connect(pagesContainer, SIGNAL(pagesSizeChanged(int)), slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(sliderMoved(int)), dimActGroup, SLOT(uncheckActions()));
    connect(slider, SIGNAL(sliderMoved(int)), pagesContainer, SLOT(setPersonalPolicy(int)));

    //Boutons de navigation
    QPushButton *next = new QPushButton(QIcon(":/new/Icons/images/rightSingle.svg"), "",statusBar) ;
    QPushButton *previous = new QPushButton(QIcon(":/new/Icons/images/leftSingle.svg"), "",statusBar) ;
    QPushButton *last = new QPushButton(QIcon(":/new/Icons/images/rightDouble.svg"), "",statusBar) ;
    QPushButton *first = new QPushButton(QIcon(":/new/Icons/images/leftDouble.svg"), "",statusBar) ;
    connect(next, SIGNAL(clicked()), actNextPage, SLOT(trigger()));
    connect(previous, SIGNAL(clicked()), actPreviousPage, SLOT(trigger()));
    connect(last, SIGNAL(clicked()), actLastPage, SLOT(trigger()));
    connect(first, SIGNAL(clicked()), actFirstPage, SLOT(trigger()));

    //Affichage et saisie de la page voulue
    PageNbField *pageNb = new PageNbField(statusBar);
    pageNb->setButtonSymbols(QAbstractSpinBox::NoButtons);
    connect(pageNb, SIGNAL(SG_goToPage(int)), navigation_manager, SLOT(goToPage(int)));
    connect(navigation_manager, SIGNAL(SG_goToPage(int,int)), pageNb, SLOT(setPageNb(int)));
    statusBar->addPermanentWidget(first);
    statusBar->addPermanentWidget(previous);
    statusBar->addPermanentWidget(pageNb);
    statusBar->addPermanentWidget(next);
    statusBar->addPermanentWidget(last);
    statusBar->addPermanentWidget(slider);

    setStatusBar(statusBar);

    //  Le ComicBook préviens le NavigationManager lorsque celui-ci à calculer le nombre total de pages
    //  contenues dans le ComicBook.
    connect (comic_book, SIGNAL(SG_numberPagesComputed(uint)),
             navigation_manager, SLOT(setNumberPagesInComicBook(uint))) ;

    //  Le NavigationManager demande au ComicBook de charger les pages demandées.
    connect (navigation_manager, SIGNAL(SG_goToPage(int,int)),
             comic_book, SLOT(loadPages(int,int))) ;

    //  Le ComicBook préviens le PagesBuffer lorsqu'il a finit de charger les pages dans la mémoire.
    connect (comic_book, SIGNAL(SG_pagesLoaded(QVector<QVector<PageManager*> >)),
             navigation_manager->getPagesBuffer(), SLOT(updateBuffer(QVector<QVector<PageManager*> >))) ;

    connect (comic_book, SIGNAL(SG_initialised()),
             thumbnailsPanel, SLOT(refreshPanel()));

    //Ouverture du ComicBook, TEMPORAIRE
    comic_book->setPathToComicBook ("C:/Users/Gabriel/Dropbox/ENSTA/IN204/Baboo/ComicBookReader/App/images/Titans Hunt") ;
    comic_book->initialise () ;
    navigation_manager->setNumberPagesDisplayed (DEFAULT_PAGE_NUMBER) ;
}

void CBWindow::displayDockMiniatures(bool display)
{
    if(display){
        dockMiniatures->show();
    } else {
        dockMiniatures->hide();
    }
}

CBWindow::~CBWindow()
{
}
