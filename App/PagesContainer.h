#ifndef PAGESCONTAINER_H
#define PAGESCONTAINER_H

#include <QtWidgets>
#include <QVector>
#include <vector>
#include <QtConcurrent/QtConcurrent>
#include <functional>


///Revoir les histoires de resize policy...


/* Widget qui sera chargé de contenir et de gérer l'affichage des pages.
 * Il contient entre autre le layout et les PageLabel des pages à afficher.
 * Il doit aussi se charger de redimensionner tout le buffer lorsque ceci est nécessaire.
 *
 * Ce widget n'a besoin que des références vers les pagesManager à afficher dans la résolution souhaitée pour fonctionner.
 *
 * Temporairement, il fonctionnera avec des ref vers des pixmap seuls.
 */


// Un enum des options d'affichage pouvant être activées
enum ResizePolicy{
    personal = 1 << 0, //Au curseur
    fitWidth = 1 << 1, //Ajusté à la largeur
    fitHeight = 1 << 2,//Ajusté à la hauteur
    fitScreen = 1 << 3 //Ajusté à l'écran
};



class PagesContainer : public QWidget
{
    Q_OBJECT

private:
    //Vecteur de pointeurs sur les pageManager
    ///vector<PageManager*> m_pages;
    //Pages au format natif puis redimensionné et QLabel
    QVector<QPixmap*> m_originalPages;
    ///QVector<QPixmap> m_resizedPages; //inutil
    QVector<QLabel*> m_pagesLabel;
    //Répétition de la taille des vecteurs ci-dessus
    int m_numberOfPages;
    //Contient pour chaque page le rapport de la hauteur de la première page sur la sienne
    QVector<int> m_equivalentWidth;
    int m_globalEquivalentWidth;
    double m_globalPagesRatio;

    //Redimensionnement sans vrifications à la dimension souhaitée toutes les pages
    virtual void scaleToHeight(const int newHeight);
    virtual void scaleToWidth(const int newWidth);
    virtual void scale(const int newMaxWidth, const int newMaxHeight);
    bool alreadyScaled(const int index, const int newMaxWidth, const int newMaxHeight);

    //Layout d'affichage côte à côté
    QHBoxLayout* m_layout;

    //Politique de redimensionnement (cf struct de flags plus haut)
    ResizePolicy m_resizePolicy;
    //Accesseurs de la politique de redimensionnement
    void setResizePolicy(const ResizePolicy resizePolicy);
    ResizePolicy getResizePolicy() const;

public:
    //Constructeurs
    PagesContainer(QWidget* parent);
    PagesContainer(const QVector<QPixmap*> pages, QWidget* parent);
    ///PagesContainer(const QVector<PageManager*> pages, const QWidget* parent);

public slots:
    //Les 4 slots de redimentionnement
    virtual void fitHeight();
    virtual void fitWidth();
    virtual void fitScreen();
    //Rafraîchissement manuel de l'affichage parfois nécessaire
    virtual void refresh();

    //remplace les pages par les newPages fournies
    ///void changePages(const QVector<PagesManager*> newPages);

    //Slots permettant de définir les politiques de redimentionnement
    void setPolicyPersonnal(const int newWidth);
    void setPolicyFitWidth();
    void setPolicyFitHeight();
    void setPolicyFitScreen();
    //Slot d'application de la politique de redimensionnement
    void applyResizePolicy();


signals:
    void pagesSizeChanged(const int width);
};


#endif // PAGESCONTAINER_H

