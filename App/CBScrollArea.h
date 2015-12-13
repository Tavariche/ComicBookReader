#ifndef CBSCROLLAREA_H
#define CBSCROLLAREA_H

#include <QtWidgets>

class CBScrollArea : public QScrollArea
{
    Q_OBJECT

protected:
    virtual void resizeEvent(QResizeEvent *);
public:
    CBScrollArea(QWidget* parent);
signals:
    void resized();
};

#endif // CBSCROLLAREA_H
