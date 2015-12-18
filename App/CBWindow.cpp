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
    UncheckableActionGroup* dimActGroup = new UncheckableActionGroup(this);
    QAction *actFitHeight = new QAction("Ajuster à la &Hauteur", this);
    actFitHeight->setCheckable(true);
    actFitHeight->setIcon(QIcon("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/fitHeight.svg"));
    dimActGroup->addAction(actFitHeight);

    QAction *actFitWidth = new QAction("Ajuster à la largeur", this);
    actFitWidth->setCheckable(true);
    actFitWidth->setIcon(QIcon("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/fitWidth.svg"));
    dimActGroup->addAction(actFitWidth);

    QAction *actFitScreen = new QAction("actFitWidth", this);
    actFitScreen->setCheckable(true);
    actFitScreen->setIcon(QIcon("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/fitScreen.svg"));
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

    wolverineMiniature->setPixmap(QPixmap("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/wolverine.jpg").scaledToWidth(120, Qt::SmoothTransformation));

    dockMiniatures->setWidget(wolverineMiniature);
    addDockWidget(Qt::LeftDockWidgetArea, dockMiniatures);

    ///La zone d'affichage principale
    CBScrollArea *displayArea = new CBScrollArea(this);
    displayArea->setBackgroundRole(QPalette::Dark);
    displayArea->setWidgetResizable(true); //Permet au PagesContainer de s'étendre

    QPixmap* wolverinePixmap = new QPixmap("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/wolverine.jpg");
    QPixmap* wolverinePixmap1 = new QPixmap("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/wolverine.jpg");
    QPixmap* wolverineBisPixmap = new QPixmap("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/wolverineBis.jpg");
    QPixmap* wolverineBisPixmap1 = new QPixmap("D:/Documents/Gabriel/Documents/ENSTA/IN204/ComicBookReader/App/images/wolverineBis.jpg");
    PagesContainer* pagesContainerDouble = new PagesContainer(QVector<QPixmap*>({wolverinePixmap, wolverineBisPixmap, wolverinePixmap1, wolverineBisPixmap1, wolverinePixmap, wolverineBisPixmap, wolverinePixmap1, wolverineBisPixmap1}), displayArea);
    displayArea->setWidget(pagesContainerDouble);

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
    connect(pagesContainerDouble, SIGNAL(pagesSizeChanged(int)), slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(sliderMoved(int)), dimActGroup, SLOT(uncheckActions()));

    connect(slider, SIGNAL(sliderMoved(int)), pagesContainerDouble, SLOT(setPolicyPersonnal(int)));
    connect(actFitHeight, SIGNAL(triggered(bool)), pagesContainerDouble, SLOT(setPolicyFitHeight()));
    connect(actFitWidth, SIGNAL(triggered(bool)), pagesContainerDouble, SLOT(setPolicyFitWidth()));
    connect(actFitScreen, SIGNAL(triggered(bool)), pagesContainerDouble, SLOT(setPolicyFitScreen()));

    connect(displayArea, SIGNAL(resized()), pagesContainerDouble, SLOT(applyResizePolicy()));

}

CBWindow::~CBWindow()
{

}
