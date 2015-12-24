#ifndef PAGESCONTAINER_H
#define PAGESCONTAINER_H

#include <QtWidgets>
#include <QVector>


///Revoir les histoires de resize policy...


/* Widget chargé de gérer l'affichage des pages.
 * Il contient entre autre le layout et les pointeurs sur les PageManager's des pages à afficher.
 * Il doit aussi se charger de donner l'ordre de redimensionner tout le buffer lorsque ceci est nécessaire.
 *
 * Ce widget n'a besoin que des pointeurs vers les pagesManager à afficher pour fonctionner.
 *
 * Temporairement, il fonctionne avec des pointeurs vers des pixmap seuls.
 */


// Un enum des options d'affichage pouvant être activées
enum ResizePolicy{
    personal = 1 << 0, //Au curseur de zoom
    fitWidth = 1 << 1, //Ajusté à la largeur
    fitHeight = 1 << 2,//Ajusté à la hauteur
    fitScreen = 1 << 3 //Ajusté à l'écran
};



class PagesContainer : public QWidget
{
    Q_OBJECT

    //Vecteur de pointeurs sur les pageManager
    ///vector<PageManager*> m_pages;
    //Pages au format natif puis redimensionné et QLabel ; provisoire
    QVector<QPixmap*> m_originalPages;
    QVector<QLabel*> m_pagesLabel;
    //Répétition de la taille des vecteurs ci-dessus (de la taille de m_pages à l'avenir)
    //Petite réprétition d'impact mémoire presque nul mais bien pratique
    int m_numberOfPages;
    //Ratio hauteur sur largeur de l'ensemble des pages normalisées en hauteur
    double m_globalPagesRatio;

    //Redimensionnement sans vrifications à la dimension souhaitée toutes les pages ; situé dans le pageManager à l'avenir
    void scaleToHeight(const int newHeight);
    void scaleToWidth(const int newWidth);
    void scale(const int newMaxWidth, const int newMaxHeight);

    //Layout d'affichage côte à côte ; mosaïque si le coeur m'en dit à la fin
    QHBoxLayout* m_layout;
    //Pointeur sur la scrollArea parent
    QScrollArea* m_parentScrollArea;

    //Politique de redimensionnement (cf flags plus haut)
    ResizePolicy m_resizePolicy;

public:
    //Constructeurs
    PagesContainer(QWidget* parent = 0);
    PagesContainer(const QVector<QPixmap*> pages, QWidget* parent = 0);
    ///PagesContainer(const QVector<PageManager*> pages, const QWidget* parent);

public slots:
    //Les 4 slots de redimentionnement
    void fitHeight();
    void fitWidth();
    void fitScreen();
    //Rafraîchissement manuel de l'affichage parfois nécessaire
    void refresh();

    //remplace les pages par les newPages fournies ; c'est le coeur du constructeur en fait.
    void setPages(const QVector<QPixmap*> newPages);

    //Slot permettant de définir les politiques de redimentionnement
    void setPersonalPolicy(int newWidth);
    void setFitWidthPolicy();
    void setFitHeightPolicy();
    void setFitScreenPolicy();
    void setResizePolicy(const ResizePolicy newPolicy);
    //Slot (finira sûrement en méthode) d'application de la politique de redimensionnement
    void applyResizePolicy();


signals:
    void pagesSizeChanged(const int width); //Informe le curseur de zoom
};


#endif // PAGESCONTAINER_H
