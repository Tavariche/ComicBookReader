#include "PageLabel.h"

PageLabel::PageLabel(const QString &text, const QString &pagePath, QWidget* parent) : QLabel(text, parent)
{
    //La question du dimensionnement initial reste en suspens...
    originalPixmap = QPixmap(pagePath);
    setPixmap(originalPixmap);
}




void PageLabel::scalePage(int value)
{
    unsigned newWidth(ZOOMING_MIN + value * ZOOMING_FACTOR);
    QSize newSize(pixmap()->size() * newWidth / pixmap()->width());

    setPixmap(originalPixmap.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}
