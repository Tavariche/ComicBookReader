#ifndef PAGENBFIELD_H
#define PAGENBFIELD_H

#include <QtWidgets>

//---------------------------------------------------------------------------//
//  PageNbField - hérité de QSpinBox                                         //
//---------------------------------------------------------------------------//
//  Cette classe sert à afficher le numéro de la page actuelle et d'en       //
//  entrer un.                                                               //
//---------------------------------------------------------------------------//


class PageNbField : public QSpinBox
{
    Q_OBJECT

public slots:
    //Le numéro interne de page et celui affoché diffèrent de 1.
    //ces fonctions calculent la correction à l'émission du numéro voulu ou à la réception du nouveau
    void setPageNb(int internPageNb){setValue(internPageNb+1);}
    void emitInternalPageNb(){emit SG_goToPage(value() -1);}

signals:
    //Signal demandant le déplacement vers une nouvelle page
    void SG_goToPage(int);

public:
    PageNbField(QWidget* parent = 0);
};

#endif // PAGENBFIELD_H
