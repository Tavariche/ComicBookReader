#include <QtSvg>
#include <QVector>
#include <QMessageBox>  //  Pour debugging.
#include "CBWindow.h"
#include "PagesContainer.h"
#include "CBScrollArea.h"
#include "UncheckableActionGroup.h"


CBWindow::CBWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ///Juste pour le côté esthétique
    setGeometry(200, 200, 700, 550);

    ///Les actions
    //Quitter
    QAction *actQuitter = new QAction("&Quitter", this);
    actQuitter->setIcon(QIcon("E:/documents/CodeBlocks/ComicBookReader/App/images/blackCross.svg"));
    connect(actQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    //Groupe des actions de dimensionnement
    UncheckableActionGroup* dimActGroup = new UncheckableActionGroup(this);
    QAction *actFitHeight = new QAction("Ajuster à la &Hauteur", this);
    actFitHeight->setCheckable(true);
    actFitHeight->setIcon(QIcon("E:/documents/CodeBlocks/ComicBookReader/App/images/fitHeight.svg"));
    dimActGroup->addAction(actFitHeight);

    QAction *actFitWidth = new QAction("Ajuster à la largeur", this);
    actFitWidth->setCheckable(true);
    actFitWidth->setIcon(QIcon("E:/documents/CodeBlocks/ComicBookReader/App/images/fitWidth.svg"));
    dimActGroup->addAction(actFitWidth);

    QAction *actFitScreen = new QAction("actFitWidth", this);
    actFitScreen->setCheckable(true);
    actFitScreen->setIcon(QIcon("E:/documents/CodeBlocks/ComicBookReader/App/images/fitScreen.svg"));
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
    dockMiniatures->setMinimumWidth(130);
    //Petite image pour le remplir un peu
    QLabel *wolverineMiniature = new QLabel("Wolverine", this);
    wolverineMiniature->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    wolverineMiniature->setPixmap(QPixmap("E:/documents/CodeBlocks/ComicBookReader/App/images/wolverine.jpg").scaledToWidth(120, Qt::SmoothTransformation));

    dockMiniatures->setWidget(wolverineMiniature);
    addDockWidget(Qt::LeftDockWidgetArea, dockMiniatures);

    ///La zone d'affichage principale
    CBScrollArea *displayArea = new CBScrollArea(this);
    displayArea->setBackgroundRole(QPalette::Dark);
    displayArea->setWidgetResizable(true); //Permet au PagesContainer de s'étendre

    QPixmap* wolverinePixmap = new QPixmap("E:/documents/CodeBlocks/ComicBookReader/App/images/wolverine.jpg");
    QPixmap* wolverineBisPixmap = new QPixmap("E:/documents/CodeBlocks/ComicBookReader/App/images/wolverineBis.jpg");
    PagesContainer* pagesContainer = new PagesContainer(QVector<QPixmap*>({wolverinePixmap, wolverineBisPixmap}), displayArea);
    pagesContainer->setPages(QVector<QPixmap*>({wolverineBisPixmap, wolverinePixmap}));
    displayArea->setWidget(pagesContainer);


    QTabWidget* tab = new QTabWidget(this);
    tab->addTab(displayArea, "Wolverine");
    setCentralWidget(tab);

    ///La statusbar
    QStatusBar *statusBar = new QStatusBar(this);
    statusBar->setSizeGripEnabled(false);
    QSlider *slider = new QSlider(Qt::Horizontal, statusBar);
    slider->setFixedWidth(150);
    slider->setRange(50, 3000);
    QLCDNumber *valZoom = new QLCDNumber(statusBar);

    valZoom->setSegmentStyle(QLCDNumber::Outline);

    QPushButton *next = new QPushButton("Suivante",this) ;
    QPushButton *previous = new QPushButton("Précédente",this) ;

    statusBar->addPermanentWidget(slider);
    statusBar->insertPermanentWidget(0, valZoom);

    //  /// ////
    // TEST
    //
    statusBar->insertPermanentWidget(1,previous);
    statusBar->insertPermanentWidget(2,next);
    connect(next, SIGNAL(clicked()),&navigation_manager, SLOT(goToNextPage()));
    connect(previous, SIGNAL(clicked()),&navigation_manager, SLOT(goToPreviousPage()));
///   DEBUGGING
//    connect(next, SIGNAL(clicked()),
//            &comic_book, SLOT(displayPageManagerState()));
//    connect(previous, SIGNAL(clicked()),
//            &comic_book, SLOT(displayPageManagerState()));
    //
    //  //  //

    setStatusBar(statusBar);

    /// Connections.
    connect(slider, SIGNAL(valueChanged(int)), valZoom, SLOT(display(int)));
    connect(pagesContainer, SIGNAL(pagesSizeChanged(int)), slider, SLOT(setValue(int)));

    connect(slider, SIGNAL(sliderMoved(int)), dimActGroup, SLOT(uncheckActions()));
    connect(slider, SIGNAL(sliderMoved(int)), pagesContainer, SLOT(setPersonalPolicy(int)));
    connect(actFitHeight, SIGNAL(triggered(bool)), pagesContainer, SLOT(setFitHeightPolicy()));
    connect(actFitWidth, SIGNAL(triggered(bool)), pagesContainer, SLOT(setFitWidthPolicy()));
    connect(actFitScreen, SIGNAL(triggered(bool)), pagesContainer, SLOT(setFitScreenPolicy()));

    connect(displayArea, SIGNAL(resized()), pagesContainer, SLOT(applyResizePolicy()));

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

    // ///////////////
    //  Ce code doit être executé après la connection des éléments entre eux parce que certaines opérations
    //  mettent à jour d'autres objets aux moyens des signaux et des slots.
    // ///////////////

    //  Le chemin vers le comic book doit OBLIGATOIREMENT terminer par '/'.
    //comic_book.setPathToArchive ("E:/documents/CodeBlocks/ComicBookReader/App/images/ComicBookTest.zip") ;
    //comic_book.uncompressArchive () ;
    comic_book.setPathToComicBook ("E:/documents/CodeBlocks/ComicBookReader/App/images/Titans Hunt/") ;
    comic_book.initialise () ;
    navigation_manager.setNumberPagesDisplayed (1) ;
}


CBWindow::~CBWindow()
{

}
