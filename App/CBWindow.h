#ifndef CBWINDOW_H
#define CBWINDOW_H

#include <QMainWindow>

class CBWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CBWindow(QWidget *parent = 0);

    ~CBWindow();

private:
};

#endif // MAINWINDOW_H