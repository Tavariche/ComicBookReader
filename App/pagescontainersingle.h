#ifndef PAGESCONTAINERSINGLE_H
#define PAGESCONTAINERSINGLE_H

#include "PagesContainer.h"

/* la sous-classe de l'affichage par page unique
 */
class PagesContainerSingle : public PagesContainer
{
    Q_OBJECT

private:
    //Le layout à une cellule pour contenir le QLabel de la page
    QHBoxLayout* m_layout;
    //Contient un pointeur vers l'original de l'image de la page à afficher
    QPixmap* m_originalPagePixmap;
    QPixmap* m_redimPagePixmap;
    //Affiche la page redimentionnée (m_redimPagePixmap)
    QLabel* m_pageLabel;

public:
    PagesContainerSingle(QPixmap* pagePixmap,QWidget* parent);
    //Redimentionnements naïfs
    virtual void scaleToHeight(int newHeight);
    virtual void scaleToWidth(int newWidth);


public slots:
    //redimentionne la page à la largeur width en préservant le ratio depuis l'appel du curseur
    virtual void cursorResizePages(const int width);
    //redimensionne la page pour qu'elle occupe toute la hauteur
    virtual void fitHeight();
    //redimensionne la page pour qu'elle occupe toute la largeur
    virtual void fitWidth();
    //redimensionne la page pour qu'elle s'ajuste à l'écran
    virtual void fitScreen();
    //remplace la page par la newPage fournie
    virtual void changePages(std::vector<QPixmap> newPage);
};


#endif // PAGESCONTAINERSINGLE_H

