#include "UncheckableActionGroup.h"

UncheckableActionGroup::UncheckableActionGroup(QWidget* parent) : QActionGroup(parent)
{
    setExclusive(true);
}

void UncheckableActionGroup::uncheckActions()
{
    QList<QAction*> allActions(actions());
    for(QList<QAction*>::iterator action = allActions.begin() ; action != allActions.end() ; action++)
            (*action)->setChecked(false);
}
