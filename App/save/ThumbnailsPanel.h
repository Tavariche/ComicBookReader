#ifndef THUMBNAILSPANEL_H
#define THUMBNAILSPANEL_H

#include <QWidget>
#include <QtWidgets>
#include <QVector>
#include "CBScrollArea.h"
#include "ComicBook.h"
#include "NavigationManager.h"

//Classe représentant une cellule du dock des thumbnails
//Non imbriquée car pas de signal et slot pour une classe imbriquée
class thumbnailCell : public QWidget
{
    Q_OBJECT

    int m_pageNb;
    QLabel* m_pageThumbnail;
    QLabel m_pageNbText;

    virtual void mousePressEvent(QMouseEvent* event);

public slots:
    void emitPageNb();

public :
    thumbnailCell(QWidget* parent = 0);
    thumbnailCell(int pageNb, QLabel* pageThumbnail, QWidget* parent = 0);
    void setThumbnail(int pageNb, QLabel* pageThumbnail);
    void layoutThumbnail();

signals:
    //Emet le numéro de page du thumbnail cliqué
    void thumbnailClicked(uint);
};

class ThumbnailsPanel : public QWidget
{
    Q_OBJECT

    //Liste des thumbnails et de leur numéro regroupés au sein d'un widget
    QVector<thumbnailCell*> m_thumbnailsList;

    //Layout contenant les cellules
    QVBoxLayout m_layout;

    //CBScrollArea parente
    QScrollArea* m_scrollArea;

    //ComicBook attaché
    ComicBook* m_attachedCB;
    //NavigationManager attaché
    NavigationManager* m_attachedNM;

    virtual void resizeEvent(QResizeEvent *);

public:
    ThumbnailsPanel(QWidget* parent = 0);
    ThumbnailsPanel(ComicBook* attachedCB, NavigationManager* attachedNM, QWidget* parent = 0);

    //Définit le ComicBook attaché
    void setAttachedCB(ComicBook* attachedCB){ m_attachedCB = attachedCB;}
    //Définit le NavigationManager attaché
    void setAttachedNM(NavigationManager* attachedNM){ m_attachedNM = attachedNM;}

public slots:
    //Mise à jour de l'affichage
    void refreshPanel(bool rebuildLayout = true);
};

#endif // THUMBNAILSPANEL_H
