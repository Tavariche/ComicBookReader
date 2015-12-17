#ifndef PAGESCONTAINER_H
#define PAGESCONTAINER_H

#include <QtWidgets>
#include <vector>

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
    //Politique de redimensionnement (cf struct de flags plus haut)
    ResizePolicy m_resizePolicy;

protected:
    //Layout d'affichage côte à côté
    QHBoxLayout* m_layout;

    //Constructeurs
    PagesContainer(QWidget* parent);
    ///PagesContainer(const vector<PageManager*> pages, const QWidget* parent);

    //Accesseurs de la politique de redimensionnement
    void setResizePolicy(const ResizePolicy resizePolicy);
    ResizePolicy getResizePolicy() const;

public:
    //Redimensionnement sans vrifications à la dimension souhaitée
    virtual void scaleToHeight(const int indice, const int newHeight) = 0;
    virtual void scaleToWidth(const int indice, const int newWidth) = 0;
    virtual void scale(const int indice, const int newMaxWidth, const int newMaxHeight) = 0;

public slots:
    //Les 4 slots de redimentionnement
    virtual void cursorResizePages(const int width) = 0;
    virtual void fitHeight() = 0;
    virtual void fitWidth() = 0;
    virtual void fitScreen() = 0;
    //Rafraîchissement manuel de l'affichage parfois nécessaire
    virtual void refresh() const = 0;

    //remplace les pagse par les newPages fournies
    ///void changePages(const std::vector<PagesManager*> newPages);

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

