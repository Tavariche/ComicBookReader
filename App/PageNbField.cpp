#include "PageNbField.h"

PageNbField::PageNbField(QWidget *parent) : QSpinBox(parent)
{
    connect(this, SIGNAL(editingFinished()), this, SLOT(emitInternalPageNb()));
}

