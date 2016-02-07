#include "CBScrollArea.h"

CBScrollArea::CBScrollArea(QWidget* parent) : QScrollArea(parent)
{}

void CBScrollArea::resizeEvent(QResizeEvent *)
{
    emit resized(width());
}
