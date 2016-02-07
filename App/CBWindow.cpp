#include <QtSvg>
#include <QVector>
#include <QMessageBox>
#include <string>
#include "CBWindow.h"
#include "PagesContainer.h"
#include "CBScrollArea.h"
#include "UncheckableActionGroup.h"
#include "ComicBookSettings.h"


CBWindow::CBWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ///Juste pour le côté esthétique
    setGeometry(200, 200, 700, 550);

    ///Les actions
    //Quitter
    QAction *actQuitter = new QAction("&Quitter", this);
    actQuitter->setIcon(QIcon("E:/documents/Code/CodeBlocks/ComicBookReader/App/images/blackCross.svg"));
    connect(actQuitter, SIGNAL(triggered(bool)), qApp, SLOT(quit()));

    //Groupe des actions de dimensionnement
    UncheckableActionGroup* dimActGroup = new UncheckableActionGroup(this);
    QAction *actFitHeight = new QAction("Ajuster à la &Hauteur", this);
    actFitHeight->setCheckable(true);
    actFitHeight->setIcon(QIcon("E:/documents/Code/CodeBlocks/ComicBookReader/App/images/fitHeight.svg"));
    dimActGroup->addAction(actFitHeight);

    QAction *actFitWidth = new QAction("Ajuster à la largeur", this);
    actFitWidth->setCheckable(true);
    actFitWidth->setIcon(QIcon("E:/documents/Code/CodeBlocks/ComicBookReader/App/images/fitWidth.svg"));
    dimActGroup->addAction(actFitWidth);

    QAction *actFitScreen = new QAction("actFitWidth", this);
    actFitScreen->setCheckable(true);
    actFitScreen->setIcon(QIcon("E:/documents/Code/CodeBlocks/ComicBookReader/App/images/fitScreen.svg"));
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

    wolverineMiniature->setPixmap(QPixmap("E:/documents/Code/CodeBlocks/ComicBookReader/App/images/wolverine.jpg").scaledToWidth(120, Qt::SmoothTransformation));

    dockMiniatures->setWidget(wolverineMiniature);
    addDockWidget(Qt::LeftDockWidgetArea, dockMiniatures);

    ///La zone d'affichage principale
    CBScrollArea *displayArea = new CBScrollArea(this);
    displayArea->setBackgroundRole(QPalette::Dark);
    displayArea->setWidgetResizable(true); //Permet au PagesContainer de s'étendre

    QPixmap* wolverinePixmap = new QPixmap("E:/documents/Code/CodeBlocks/ComicBookReader/App/images/wolverine.jpg");
    QPixmap* wolverineBisPixmap = new QPixmap("E:/documents/Code/CodeBlocks/ComicBookReader/App/images/wolverineBis.jpg");
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

// /////////////////////////////////////////////////////////////////
// TEST   //
//
    statusBar->insertPermanentWidget(1,previous);
    statusBar->insertPermanentWidget(2,next);
    connect(next, SIGNAL(clicked()),&m_navigation_manager, SLOT(goToNextPage()));
    connect(previous, SIGNAL(clicked()),&m_navigation_manager, SLOT(goToPreviousPage()));

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
    connect (&m_comic_book, SIGNAL(SG_numberPagesComputed(uint)),
             &m_navigation_manager, SLOT(setNumberPagesInComicBook(uint))) ;

    //  Le NavigationManager demande au ComicBook de charger les pages demandées.
    connect (&m_navigation_manager, SIGNAL(SG_goToPage(uint,uint)),
             &m_comic_book, SLOT(loadPages(uint,uint))) ;

    //  Le ComicBook préviens le PagesBuffer lorsqu'il a finit de charger les pages dans la mémoire.
    connect (&m_comic_book, SIGNAL(SG_pagesLoaded(QVector<QVector<PageManager*> >)),
             m_navigation_manager.getPagesBuffer(), SLOT(updateBuffer(QVector<QVector<PageManager*> >))) ;

    // ///////////////
    //  Ce code doit être executé après la connection des éléments entre eux parce que certaines opérations
    //  mettent à jour d'autres objets aux moyens des signaux et des slots.
    // ///////////////

    openRecentCB("Titans Hunt") ;

    closeCB();
}


void CBWindow::openCB()
{
    /// Chercher une archive avec l'explorateur de fichiers.
}


void CBWindow::openRecentCB(QString cb_name)
{
    //  Tentative de chargement des options de lecture associées au Comic Book.
    ComicBookSettings cbs ;
    e_loading_status ls = cbs.loadSettings(cb_name) ;

    if(ls < CBSTP_INVALID)
    {
        //  Initialisation du Comic Book et du Navigation Manager.
        m_comic_book.setPathToArchive(cbs.getPathToArchive()) ;

        //  On initialise le reste des paramèters que si le chargement a été effectué entièrement.
        if(ls == CBSTP_OK)
        {
            m_navigation_manager.setCurrentPage(cbs.getCurrentPage()) ;
            m_navigation_manager.setNumberPagesDisplayed(cbs.getNumberPagesDisplayed()) ;
            m_navigation_manager.setReadingStyle(cbs.getReadingStyle()) ;
        }

        //
        //  On teste l'existence du dossier décompressé dans le dossier des fichiers temporaires (si ce dernier
        //  existe).
        //

        //  Récupération du chemin vers le dossier des fichiers temporaires s'il existe.
        std::string temp_folder = "" ;
        const char* var_env_temp = getenv("TEMP") ;
        if (var_env_temp)
            temp_folder = std::string(var_env_temp) ;
        //  Sinon on récupère le dossier où se trouve l'archive.
        else
        {
            QFileInfo file_info (cbs.getPathToArchive()) ;
            temp_folder = file_info.absolutePath().toStdString() ;
        }

        for (unsigned int i=0 ; i<temp_folder.size() ; i++)
        {
            if (temp_folder[i] == '\\') temp_folder[i] = '/' ;
        }

        if (temp_folder[temp_folder.size()-1] != '\\')
            temp_folder += "/" ;

        //  Test de l'existence du dossier décompressé.
        QString uncompressed_folder ;
        uncompressed_folder.fromStdString(temp_folder) ;
        uncompressed_folder += cb_name ;
        if (QFile::exists(uncompressed_folder))
            m_comic_book.setPathToComicBook(uncompressed_folder) ;
        else
            m_comic_book.uncompressComicBook() ;

        //  Initialisation du Comic Book qui le rend prêt pour la lecture.
        m_comic_book.initialise() ;

        return ;
    }

    /// Supprimer le Comic Book de la liste des Comic Book récemment consultés.

    //  Si on arrive jusqu'ici, c'est que le chargement a échoué. On prévient l'utilisateur.
    QMessageBox::information(0,"Erreur - Réouverture d'un Comic Book",
                             "Le Comic Book n'a pas pu être chargé correctement. Il est introuvable et a probablement été déplacé de son dossier original.") ;

    //  On charge un Comic Book avec l'explorateur de fichiers.
    openCB() ;
}


void CBWindow::closeCB()
{
    //  Récupération des options de lecture.
    ComicBookSettings cbs ;
    cbs.setPathToArchive(m_comic_book.getPathToArchive()) ;
    cbs.setReadingStyle(m_navigation_manager.getReadingStyle()) ;
    cbs.setNumberPagesDisplayed(m_navigation_manager.getNumberOfPagesDisplayed()) ;
    cbs.setCurrentPage(m_navigation_manager.getCurrentPage()) ;

    //  Sauvegarde des options de lecture dans un fichier.
    cbs.saveSettings() ;
}


CBWindow::~CBWindow()
{

}
