#ifndef CBSCROLLAREA_H
#define CBSCROLLAREA_H

#include <QtWidgets>

//---------------------------------------------------------------------------//
//  CBScrollArea - héritée de QScrollArea.                                   //
//---------------------------------------------------------------------------//
//  Cette classe sert uniquement à emettre un signal de redimentionnement    //
//  lorsque la zone d'affichage des pages est redimentionné.                 //
//---------------------------------------------------------------------------//

class CBScrollArea : public QScrollArea
{
    Q_OBJECT

protected:
    virtual void resizeEvent(QResizeEvent *);

public:
    CBScrollArea(QWidget* parent = 0);

signals:
    //Emis lors d'un redimensionnement de la scrollArea
    void resized();
};

#endif // CBSCROLLAREA_H
