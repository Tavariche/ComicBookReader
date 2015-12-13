#include "CBWindow.h"

CBWindow::CBWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ///Juste pour le côté esthétique
    setGeometry(200, 200, 700, 550);

    ///Les actions
    //Quitter
    QAction *actQuitter = new QAction("&Quitter", this);
    actQuitter->setIcon(QIcon("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/blackCross.svg"));
    connect(actQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    //Groupe des actions de dimensionnement
    QActionGroup* dimActGroup = new QActionGroup(this);
    QAction *actFitHeight = new QAction("Ajuster à la &Hauteur", this);
    actFitHeight->setCheckable(true);
    actFitHeight->setIcon(QIcon("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/fitHeight.svg"));
    dimActGroup->addAction(actFitHeight);
    QAction *actFitWidth = new QAction("Ajuster à la largeur", this);
    actFitWidth->setCheckable(true);
    actFitWidth->setIcon(QIcon("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/fitWidth.svg"));
    dimActGroup->addAction(actFitWidth);
    QAction *actFitScreen = new QAction("Ajuster à l'écran", this);
    actFitScreen->setCheckable(true);
    actFitScreen->setIcon(QIcon("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/fitScreen.svg"));
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
    RightToolBar->addAction(actFitHeight);
    RightToolBar->addAction(actFitWidth);
    RightToolBar->addAction(actFitScreen);


    ///Le dock miniatures
    QDockWidget *dockMiniatures = new QDockWidget("Miniatures", this);
    dockMiniatures->setMinimumWidth(130);
    //Petite image pour le remplir un peu
    QLabel *wolverineMiniature = new QLabel("Wolverine", this);
    wolverineMiniature->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    wolverineMiniature->setPixmap(QPixmap("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/wolverine.jpg").scaledToWidth(120, Qt::SmoothTransformation));

    dockMiniatures->setWidget(wolverineMiniature);
    addDockWidget(Qt::LeftDockWidgetArea, dockMiniatures);

    ///La zone d'affichage principale
    CBScrollArea *displayArea = new CBScrollArea(this);
    displayArea->setBackgroundRole(QPalette::Dark);
    displayArea->setWidgetResizable(true); //Permet au PagesContainer de s'étendre

    QPixmap* wolverinePixmap = new QPixmap("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/wolverine.jpg");
    *wolverinePixmap = wolverinePixmap->scaledToWidth(400, Qt::SmoothTransformation);
    PagesContainerSingle* pagesContainerSingle = new PagesContainerSingle(wolverinePixmap, displayArea);
    displayArea->setWidget(pagesContainerSingle);

    /*
    pageLabel *wolverine = new pageLabel("Wolverine", "D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/wolverine.jpg", displayArea);
    wolverine->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter	);
    wolverine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //wolverine->setPixmap(QPixmap("D:/Documents/Gabriel/Documents/ENSTA/ComicBookReader/App/images/wolverine.jpg").scaledToWidth(400, Qt::SmoothTransformation));

    displayArea->setWidget(wolverine);
    */
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

    //QPushButton *test2 = new QPushButton("Test2",statusBar);

    statusBar->addPermanentWidget(slider);
    statusBar->insertPermanentWidget(0, valZoom);
    setStatusBar(statusBar);

    connect(slider, SIGNAL(valueChanged(int)), valZoom, SLOT(display(int)));
    connect(slider, SIGNAL(sliderMoved(int)), pagesContainerSingle, SLOT(setPolicyPersonnal(int)));
    connect(actFitHeight, SIGNAL(triggered(bool)), pagesContainerSingle, SLOT(setPolicyFitHeight()));
    connect(actFitWidth, SIGNAL(triggered(bool)), pagesContainerSingle, SLOT(setPolicyFitWidth()));
    connect(actFitScreen, SIGNAL(triggered(bool)), pagesContainerSingle, SLOT(setPolicyFitScreen()));
    connect(pagesContainerSingle, SIGNAL(pagesSizeChanged(int)), slider, SLOT(setValue(int)));
    connect(displayArea, SIGNAL(resized()), pagesContainerSingle, SLOT(applyResizePolicy()));

}

CBWindow::~CBWindow()
{

}
