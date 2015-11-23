#include "CBWindow.h"

CBWindow::CBWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ///Juste pour le côté esthétique
    setGeometry(200, 200, 700, 550);

    ///Les actions
    //Quitter
    QAction *actQuitter = new QAction("&Quitter", this);
    actQuitter->setIcon(QIcon("/home/gabriel/Code/ComicBookReader/App/images/blackCross.svg"));
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
    //Petite image pour le remplir un peu
    QLabel *wolverineMiniature = new QLabel("Wolverine", this);
    wolverineMiniature->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    wolverineMiniature->setPixmap(QPixmap("/home/gabriel/Code/ComicBookReader/App/images/wolverine.jpg").scaledToWidth(90, Qt::SmoothTransformation));
    dockMiniatures->setWidget(wolverineMiniature);
    addDockWidget(Qt::LeftDockWidgetArea, dockMiniatures);

    ///La zone d'affichage principale
    QLabel *wolverine = new QLabel("Wolverine", this);
    wolverine->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter	);
    wolverine->setPixmap(QPixmap("/home/gabriel/Code/ComicBookReader/App/images/wolverine.jpg").scaledToWidth(400, Qt::SmoothTransformation));
    QTabWidget* displayArea = new QTabWidget(this);
    displayArea->addTab(wolverine, "Wolverine");
    setCentralWidget(displayArea);
}

CBWindow::~CBWindow()
{

}
