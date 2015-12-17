#ifndef PAGESCONTAINERSINGLE_H
#define PAGESCONTAINERSINGLE_H

#include "PagesContainer.h"

/* la sous-classe de l'affichage par page unique
 */
class PagesContainerSingle : public PagesContainer
{
    Q_OBJECT

private:
    //Contient un pointeur vers l'original de l'image de la page à afficher
    //tempoiraire, à remplacer par le vector de pageManager
    QPixmap* m_originalPagePixmap;
    QPixmap* m_redimPagePixmap;
    //Affiche la page redimentionnée (m_redimPagePixmap)
    QLabel* m_pageLabel;

public:
    //COnstructeurs
    PagesContainerSingle(QWidget* parent);
    PagesContainerSingle(QPixmap* pagePixmap,QWidget* parent);
    ///PagesContainerSingle(const vector<PageManager*> pages, const QWidget* parent);

    //Redimentionnements naïfs
    virtual void scaleToHeight(const int newHeight);
    virtual void scaleToWidth(const int newWidth);


public slots:
    //Les 4 slots de redimentionnement
    virtual void cursorResizePages(const int width);
    virtual void fitHeight();
    virtual void fitWidth();
    virtual void fitScreen();
    //Rafraîchissement manuel de l'affichage parfois nécessaire
    virtual void refresh() const;
};


#endif // PAGESCONTAINERSINGLE_H

