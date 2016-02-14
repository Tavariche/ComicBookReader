#ifndef UNCHECKABLEACTIONGROUP_H
#define UNCHECKABLEACTIONGROUP_H

#include <QtWidgets>
#include <QList>

class UncheckableActionGroup : public QActionGroup
{
    Q_OBJECT

public:
    UncheckableActionGroup(QWidget *parent);

public slots:
    //Décocher toutes les actions
    void uncheckActions();
};

#endif // UNCHECKABLEACTIONGROUP_H
