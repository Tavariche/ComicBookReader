#ifndef PAGELABEL_H
#define PAGELABEL_H

#include <QtWidgets>

#define ZOOMING_FACTOR 15. //Permet d'ajuster le facteur multiplicatif de zoom sur la plage 0-100
#define ZOOMING_MIN 50 //Définit la niveau minimum du zoom (valeur 0)

class PageLabel : public QLabel
{
    Q_OBJECT

private :
    QPixmap originalPixmap; //provisoire
public :
    PageLabel(const QString &text, const QString &pagePath, QWidget* parent = 0); //chemin absolu à remplacer plus tard par une référence sur pixmap

public slots :
    void scalePage(const int);
};

#endif // PAGELABEL_H

