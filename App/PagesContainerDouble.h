#ifndef PAGESCONTAINERDOUBLE_H
#define PAGESCONTAINERDOUBLE_H


#include "PagesContainer.h"
#include <cmath>

/* la sous-classe de l'affichage par page double
 */
class PagesContainerDouble : public PagesContainer
{
    Q_OBJECT

private:
    //Contient un pointeur vers l'original de l'image de la page à afficher
    //tempoiraire, à remplacer par le vector de pageManager
    QPixmap* m_LeftOriginalPagePixmap;
    QPixmap* m_RightOriginalPagePixmap;
    QPixmap* m_LeftRedimPagePixmap;
    QPixmap* m_RightRedimPagePixmap;
    //Affiche la page redimentionnée (m_redimPagePixmap)
    QLabel* m_LeftPageLabel;
    QLabel* m_RightPageLabel;

public:
    //COnstructeurs
    PagesContainerDouble(QWidget* parent);
    PagesContainerDouble(QPixmap* leftPagePixmap, QPixmap* rightPagePixmap, QWidget* parent);
    ///PagesContainerDouble(const vector<PageManager*> pages, const QWidget* parent);

    //Redimentionnements naïfs
    virtual void scaleToHeight(const int indice, const int newHeight); //temporaire, géré par pageManager à l'avenir (1 ou 2)
    virtual void scaleToWidth(const int indice, const int newWidth);
    virtual void scale(const int indice, const int newMaxWidth, const int newMaxHeight);



public slots:
    //Les 4 slots de redimentionnement
    virtual void cursorResizePages(const int width);
    virtual void fitHeight();
    virtual void fitWidth();
    virtual void fitScreen();
    //Rafraîchissement manuel de l'affichage parfois nécessaire
    virtual void refresh() const;
};




#endif // PAGESCONTAINERDOUBLE_H

