#ifndef THUMBNAILSPANEL_H
#define THUMBNAILSPANEL_H

#include <QWidget>
#include <QtWidgets>
#include <QVector>
#include "CBScrollArea.h"
#include "ComicBook.h"
#include "NavigationManager.h"

#define MAX_THUMBNAILS_WIDTH 200

//---------------------------------------------------------------------------//
//  ThumbnailCell - héritée de QWidget.                                      //
//---------------------------------------------------------------------------//
//  Cette classe sert à contenir un thumbnail, son label texte et à          //
//  émettre le siganl approprié lorsqu'elle est cliquée.                     //
//---------------------------------------------------------------------------//

//Classe représentant une cellule du dock des thumbnails
//Non imbriquée car pas de signal et slot pour une classe imbriquée
class thumbnailCell : public QWidget
{
    Q_OBJECT

    //Numéro de page associé à la cellule
    int m_pageNb;
    //Thumbnail de la cellule
    QLabel* m_pageThumbnail;
    //Texte associé (Page n)
    QLabel m_pageNbText;

protected :
    //Permet de n'emettre le signal de changement de page que sur un clique gauche
    virtual void mousePressEvent(QMouseEvent* event);

public slots:
    void emitPageNb();

public :
    //Constructeurs
    thumbnailCell(QWidget* parent = 0);
    thumbnailCell(int pageNb, QLabel* pageThumbnail, QWidget* parent = 0);
    ~thumbnailCell(){}

    //Affectation des éléments de la cellule
    void setThumbnail(int pageNb, QLabel* pageThumbnail);
    //Disposition des éléments de la cellule
    void layoutThumbnail();

signals:
    //Emet le numéro de page du thumbnail cliqué
    void thumbnailClicked(int);
};

//---------------------------------------------------------------------------//
//  ThumbnailPanel - hérité de CBScrollArea                                  //
//---------------------------------------------------------------------------//
//  Cette classe sert à contenir les ThumbnailsCell définis ci-dessus        //
//  Elle gère ensuite le redimensionnement notamment.                        //
//---------------------------------------------------------------------------//


class ThumbnailsPanel : public CBScrollArea
{
    Q_OBJECT

    //Liste des thumbnails et de leur numéro regroupés au sein d'un widget
    QVector<thumbnailCell*> m_thumbnailsList;

    //Layout contenant les cellules et widget global
    QVBoxLayout m_layout;
    QWidget* m_widget;

    //CBScrollArea parente
    QScrollArea* m_scrollArea;

    //ComicBook attaché
    ComicBook* m_attachedCB;
    //NavigationManager attaché
    NavigationManager* m_attachedNM;

    virtual void resizeEvent(QResizeEvent *e);

public:
    ThumbnailsPanel(QWidget* parent = 0);
    ThumbnailsPanel(ComicBook* attachedCB, NavigationManager* attachedNM, QWidget* parent = 0);
    void basicInit();
    ~ThumbnailsPanel(){}

    //Définit le ComicBook attaché
    void setAttachedCB(ComicBook* attachedCB){ m_attachedCB = attachedCB;}
    //Définit le NavigationManager attaché
    void setAttachedNM(NavigationManager* attachedNM){ m_attachedNM = attachedNM;}

public slots:
    //Mise à jour de l'affichage
    void refreshPanel(bool rebuildLayout = true);
    void test(){}
};

#endif // THUMBNAILSPANEL_H
