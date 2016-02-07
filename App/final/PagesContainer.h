#ifndef PAGESCONTAINER_H
#define PAGESCONTAINER_H

#include <QtWidgets>
#include <QVector>
#include <QtConcurrent/QtConcurrent>
#include <functional>
#include "ComicBook.h"
#include "PageManager.h"
#include "PagesBuffer.h"
#include "CBScrollArea.h"
//#include "CBWindow.h"

//---------------------------------------------------------------------------//
//  PagesContainer - hérité de CBScrollArea                                  //
//---------------------------------------------------------------------------//
//  Widget chargé de gérer l'affichage des pages à l'écran.                  //
//  Il redimensionne le buffer quand c'est nécessaire                        //
//---------------------------------------------------------------------------//


// Options d'affichage pouvant être activées (séparément)
enum ResizePolicy{
    PERSONAL = 1 << 0, //A la largeur voulue pour l'ensemble des pages
    FIT_WIDTH = 1 << 1, //Ajusté à la largeur
    FIT_HEIGHT = 1 << 2,//Ajusté à la hauteur
    FIT_SCREEN = 1 << 3 //Ajusté à l'écran
};

class PagesContainer : public CBScrollArea
{
    Q_OBJECT

private:
    //Pointeur sur le buffer des pages
    PagesBuffer* m_buffer;

    //Stocke les threads de redimentionnement pour permettre leur contrôle
    QVector<QFuture<void> > m_resizingThread;

    //Pointeur sur l'objet lui-même (la scrollArea)
    CBScrollArea* m_scrollArea;
    //Widget contenant tout le reste
    QWidget* m_widget;
    //Layout d'affichage côte à côte
    QHBoxLayout* m_layout;

    //Pointeur sur le parent pour le conserver lors du plein écran
    QWidget* m_parent;

    //Politique de redimensionnement (cf flags plus haut)
    ResizePolicy m_resizePolicy;
    int m_customWidth;

    //Action de retour du plein écran
    bool fullScreenEnabled;

    //Retourne un pointeur sur l'image originale de la page "index" du bloc de rôle "role"
    QPixmap* getOriginalPage(const int index, const e_pages_roles role = CURRENT){
        return (*m_buffer->getPages(role))[index]->getOriginal();
    }
    //Retourne un pointeur sur le QLabel redimensionné de la page i du bloc de role spécifié
    QLabel* getResizedPage(const int index, const e_pages_roles role = CURRENT){
        return (*m_buffer->getPages(role))[index]->getResized();
    }

    //Attend la fin des threads ou du thread spécifié
    // cancelThreads:   true -> threads stoppés si inachevés
    //                  false -> threads laissés jusqu'à ce qu'ils terminent
    // index:   spécifie le thread concerné lors de l'appel
    //          si non spécifié, tous les threads sont concernés
    void finishThreads(bool cancelThreads = true, int index = -1);


public:
    //Constructeurs
    PagesContainer(QWidget* parent = 0);
    PagesContainer(PagesBuffer* buffer, QWidget* parent = 0);
    //Réalise les opérations communes aux constructeurs
    void basicInit();

    //Destructeur
    ~PagesContainer();

public slots:
    //Slots de calcul des nouvelles dimensions des pages
    //Possibilité de n'appliquer cela qu'au bloc de page "index"
    void fitHeight(const int index = NONE);
    //Possibilité de spécifier la largeur
    void fitWidth(const int index = NONE, const int specifiedWidth = 0);
    //S'applique toujours à toutes les pages dans la pratique
    void fitScreen();

    //Rafraîchissement manuel de l'affichage pour restreindre aux pages affichées
    void refresh(const int index = 0);

    //Réinitialisation du PagesContainer avec le nouveau buffer de pages "newBuffer
    void setBuffer(PagesBuffer* newBuffer);

    //Slot permettant de définir les politiques de redimentionnement
    void setPersonalPolicy(const int newWidth);
    void setFitWidthPolicy();
    void setFitHeightPolicy();
    void setFitScreenPolicy();
    void setResizePolicy(const ResizePolicy newPolicy);
    //Application de la politique de redimensionnement
    void applyResizePolicy();

    //Activation et désactivation du mode fullScreen
    void toggleFullScreen();

    //Fermeture du logiciel entier si fermeture du pagesContainer
    virtual void closeEvent(QCloseEvent* e);


signals:
    //Emis lors du redimentionnement des pages
    //Transmet la largeur en pixels de la première page affichée (indicateur)
    void pagesSizeChanged(const int width);
};

void clearLayout(QLayout *layout);

#endif // PAGESCONTAINER_H
