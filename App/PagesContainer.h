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


/* Un enum des options d'affichage pouvant être activées
 */
enum ResizePolicy{
    personal = 1 << 0,
    fitWidth = 1 << 1,
    fitHeight = 1 << 2,
    fitScreen = 1 << 3
};



class PagesContainer : public QWidget
{
    Q_OBJECT

private:
    ResizePolicy m_resizePolicy;

protected:
    PagesContainer(QWidget* parent);

    //Event pour conserver la page à la bonne taille

    void setResizePolicy(ResizePolicy resizePolicy);
    ResizePolicy getResizePolicy();

public:
    virtual void scaleToHeight(int newHeight) = 0;
    virtual void scaleToWidth(int newWidth) = 0;

public slots:
    virtual void cursorResizePages(const int width) = 0;
    virtual void fitHeight() = 0;
    virtual void fitWidth() = 0;
    virtual void fitScreen() = 0;
    virtual void changePages(std::vector<QPixmap> newPages) = 0; //Vecteur de PagesManager à l'avenir

    //Slots permettant aux actions de définir des politiques de redimentionnement
    void setPolicyPersonnal(int newWidth);
    void setPolicyFitWidth();
    void setPolicyFitHeight();
    void setPolicyFitScreen();
    //Slot d'application de la politique de redimensionnement
    void applyResizePolicy();


signals:
    void pagesSizeChanged(int width);
};


#endif // PAGESCONTAINER_H

