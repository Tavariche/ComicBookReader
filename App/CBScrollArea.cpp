#include "CBScrollArea.h"

CBScrollArea::CBScrollArea(QWidget* parent) : QScrollArea(parent)
{}

//Emis lors d'un redimensionnement de la scrollArea
void CBScrollArea::resizeEvent(QResizeEvent *)
{
    emit resized();
}
