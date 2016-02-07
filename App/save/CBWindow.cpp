#include <QtSvg>
#include <QVector>
#include <QMessageBox>  //  Pour debugging.
#include "CBWindow.h"
#include "PagesContainer.h"
#include "CBScrollArea.h"
#include "UncheckableActionGroup.h"
#include "ThumbnailsPanel.h"


CBWindow::CBWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ///Juste pour le côté esthétique
    setGeometry(200, 200, 700, 550);

    ///Les actions
    //Quitter
    QAction *actQuitter = new QAction("&Quitter", this);
    actQuitter->setIcon(QIcon(":/new/Icons/images/blackCross.svg"));
    connect(actQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    //Groupe des actions de dimensionnement
    UncheckableActionGroup* dimActGroup = new UncheckableActionGroup(this);
    QAction *actFitHeight = new QAction("Ajuster à la &Hauteur", this);
    actFitHeight->setCheckable(true);
    actFitHeight->setIcon(QIcon(":/new/Icons/images/fitHeight.svg"));
    dimActGroup->addAction(actFitHeight);

    QAction *actFitWidth = new QAction("Ajuster à la largeur", this);
    actFitWidth->setCheckable(true);
    actFitWidth->setIcon(QIcon(":/new/Icons/images/fitWidth.svg"));
    dimActGroup->addAction(actFitWidth);

    QAction *actFitScreen = new QAction("actFitWidth", this);
    actFitScreen->setCheckable(true);
    actFitScreen->setIcon(QIcon(":/new/Icons/images/fitScreen.svg"));
    actFitScreen->setChecked(true);
    dimActGroup->addAction(actFitScreen);

    ///Les menus
    //Fichiers
    QMenu *menuFichiers = menuBar()->addMenu("&Fichier");
    menuFichiers->addAction(actQuitter);
    //Affichage
    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
    menuAffichage->addAction(actFitHeight);
    menuAffichage->addAction(actFitWidth);
    menuAffichage->addAction(actFitScreen);


    ///La toolbar
    QToolBar *RightToolBar = new QToolBar("RightToolBar", this);
    addToolBar(Qt::RightToolBarArea, RightToolBar);
    RightToolBar->addAction(actQuitter);
    RightToolBar->addSeparator();
    RightToolBar->addAction(actFitHeight);
    RightToolBar->addAction(actFitWidth);
    RightToolBar->addAction(actFitScreen);


    ///Le dock miniatures
    QDockWidget *dockMiniatures = new QDockWidget("Miniatures", this);
    CBScrollArea * thumbnailsArea = new CBScrollArea(dockMiniatures);
    dockMiniatures->setMinimumWidth(130);
    //Petite image pour le remplir un peu
    ThumbnailsPanel* thumbnailsPanel = new ThumbnailsPanel(&comic_book, &navigation_manager, thumbnailsArea);
    dockMiniatures->setWidget(thumbnailsPanel);
    addDockWidget(Qt::LeftDockWidgetArea, dockMiniatures);

    ///La zone d'affichage principale
    QTabWidget* tabArea = new QTabWidget(this);
    CBScrollArea* displayArea = new CBScrollArea(tabArea);
    PagesContainer* pagesContainer = new PagesContainer(displayArea);
    displayArea->setWidget(pagesContainer);
    displayArea->setWidgetResizable(true); //Permet au PagesContainer de s'étendre

    tabArea->addTab(displayArea, "Tab 1");

    setCentralWidget(tabArea);

    ///La statusbar
    QStatusBar *statusBar = new QStatusBar(this);
    statusBar->setSizeGripEnabled(false);
    QSlider *slider = new QSlider(Qt::Horizontal, statusBar);
    slider->setFixedWidth(150);
    slider->setRange(200, 2000);
    QLCDNumber *valZoom = new QLCDNumber(statusBar);

    valZoom->setSegmentStyle(QLCDNumber::Outline);

    QPushButton *next = new QPushButton("Suivante",this) ;
    QPushButton *previous = new QPushButton("Précédente",this) ;

    statusBar->addPermanentWidget(slider);
    statusBar->insertPermanentWidget(0, valZoom);

// /////////////////////////////////////////////////////////////////
// TEST   //
//
    statusBar->insertPermanentWidget(1,previous);
    statusBar->insertPermanentWidget(2,next);
    connect(next, SIGNAL(clicked()),&navigation_manager, SLOT(goToNextPage()));
    connect(previous, SIGNAL(clicked()),&navigation_manager, SLOT(goToPreviousPage()));

//  DEBUG   DEBUG   DEBUG   DEBUG   DEBUG   //
//    connect(next, SIGNAL(clicked()),
//            &comic_book, SLOT(displayPageManagerState()));
//    connect(previous, SIGNAL(clicked()),
//            &comic_book, SLOT(displayPageManagerState()));
//  DEBUG   DEBUG   DEBUG   DEBUG   DEBUG   //
// /////////////////////////////////////////////////////////////////

    setStatusBar(statusBar);

    /// Connexions.
    connect(slider, SIGNAL(valueChanged(int)), valZoom, SLOT(display(int)));
    connect(pagesContainer, SIGNAL(pagesSizeChanged(int)), slider, SLOT(setValue(int)));

    connect(slider, SIGNAL(sliderMoved(int)), dimActGroup, SLOT(uncheckActions()));
    connect(slider, SIGNAL(sliderMoved(int)), pagesContainer, SLOT(setPersonalPolicy(int)));
    connect(actFitHeight, SIGNAL(triggered(bool)), pagesContainer, SLOT(setFitHeightPolicy()));
    connect(actFitWidth, SIGNAL(triggered(bool)), pagesContainer, SLOT(setFitWidthPolicy()));
    connect(actFitScreen, SIGNAL(triggered(bool)), pagesContainer, SLOT(setFitScreenPolicy()));

    connect(displayArea, SIGNAL(resized(int)), pagesContainer, SLOT(applyResizePolicy()));

    //  Le ComicBook préviens le NavigationManager lorsque celui-ci à calculer le nombre total de pages
    //  contenues dans le ComicBook.
    connect (&comic_book, SIGNAL(SG_numberPagesComputed(uint)),
             &navigation_manager, SLOT(setNumberPagesInComicBook(uint))) ;

    //  Le NavigationManager demande au ComicBook de charger les pages demandées.
    connect (&navigation_manager, SIGNAL(SG_goToPage(uint,uint)),
             &comic_book, SLOT(loadPages(uint,uint))) ;

    //  Le ComicBook préviens le PagesBuffer lorsqu'il a finit de charger les pages dans la mémoire.
    connect (&comic_book, SIGNAL(SG_pagesLoaded(QVector<QVector<PageManager*> >)),
             navigation_manager.getPagesBuffer(), SLOT(updateBuffer(QVector<QVector<PageManager*> >))) ;

    connect (navigation_manager.getPagesBuffer(), SIGNAL(bufferUpdated(PagesBuffer*)),
             pagesContainer, SLOT(setBuffer(PagesBuffer*)));

    connect (&comic_book, SIGNAL(SG_initialised()),
             thumbnailsPanel, SLOT(refreshPanel()));

    // ///////////////
    //  Ce code doit être executé après la connection des éléments entre eux parce que certaines opérations
    //  mettent à jour d'autres objets aux moyens des signaux et des slots.
    // ///////////////

    //comic_book.setPathToArchive ("E:/documents/CodeBlocks/ComicBookReader/App/images/Titans Hunt.cbz") ;
    //comic_book.uncompressArchive () ;
    comic_book.setPathToComicBook ("C:/Users/Gabriel/Dropbox/ENSTA/IN204/Baboo/ComicBookReader/App/images/Titans Hunt") ;
    comic_book.initialise () ;
    navigation_manager.setNumberPagesDisplayed (2) ;
}


CBWindow::~CBWindow()
{

}
