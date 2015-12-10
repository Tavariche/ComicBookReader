#include "CBWindow.h"
#include "pagelabel.h"


CBWindow::CBWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ///Juste pour le côté esthétique
    setGeometry(200, 200, 700, 550);

    ///Les actions
    //Quitter
    QAction *actQuitter = new QAction("&Quitter", this);
    actQuitter->setIcon(QIcon("D:/Documents/Gabriel/Documents/ENSTA/ComicBookReader/App/images/blackCross.svg"));
    connect(actQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    ///Les menus
    //Fichiers
    QMenu *menuFichiers = menuBar()->addMenu("&Fichier");
    menuFichiers->addAction(actQuitter);
    //Affichage
    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");

    ///La toolbar
    QToolBar *RightToolBar = new QToolBar("RightToolBar", this);
    addToolBar(Qt::RightToolBarArea, RightToolBar);
    RightToolBar->addAction(actQuitter);

    ///Le dock miniatures
    QDockWidget *dockMiniatures = new QDockWidget("Miniatures", this);
    dockMiniatures->setMinimumWidth(130);
    //Petite image pour le remplir un peu
    QLabel *wolverineMiniature = new QLabel("Wolverine", this);
    wolverineMiniature->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    wolverineMiniature->setPixmap(QPixmap("D:/Documents/Gabriel/Documents/ENSTA/ComicBookReader/App/images/wolverine.jpg").scaledToWidth(120, Qt::SmoothTransformation));

    dockMiniatures->setWidget(wolverineMiniature);
    addDockWidget(Qt::LeftDockWidgetArea, dockMiniatures);

    ///La zone d'affichage principale
    QScrollArea *displayArea = new QScrollArea(this);
    displayArea->setBackgroundRole(QPalette::Dark);
    displayArea->setWidgetResizable(true);

    pageLabel *wolverine = new pageLabel("Wolverine", "D:/Documents/Gabriel/Documents/ENSTA/ComicBookReader/App/images/wolverine.jpg", displayArea);
    wolverine->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter	);
    wolverine->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //wolverine->setPixmap(QPixmap("D:/Documents/Gabriel/Documents/ENSTA/ComicBookReader/App/images/wolverine.jpg").scaledToWidth(400, Qt::SmoothTransformation));

    displayArea->setWidget(wolverine);
    QTabWidget* tab = new QTabWidget(this);
    tab->addTab(displayArea, "Wolverine");
    setCentralWidget(tab);

    ///La statusbar
    QStatusBar *statusBar = new QStatusBar(this);
    statusBar->setSizeGripEnabled(false);
    QSlider *slider = new QSlider(Qt::Horizontal, statusBar);
    slider->setFixedWidth(150);
    QLCDNumber *valZoom = new QLCDNumber(statusBar);

    valZoom->setSegmentStyle(QLCDNumber::Outline);

    //QPushButton *test2 = new QPushButton("Test2",statusBar);

    statusBar->addPermanentWidget(slider);
    statusBar->insertPermanentWidget(0, valZoom);
    setStatusBar(statusBar);

    QObject::connect(slider, SIGNAL(valueChanged(int)), valZoom, SLOT(display(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), wolverine, SLOT(scalePage(int)));

}

CBWindow::~CBWindow()
{

}
