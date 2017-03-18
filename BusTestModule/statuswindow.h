#ifndef STATUSWINDOW_H
#define STATUSWINDOW_H
#include "statusthread.h"
#include <QMainWindow>
#include <QThread>

class statuswindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit statuswindow(QWidget *parent = 0);

private:
    void run();

signals:

public slots:
};

#endif // STATUSWINDOW_H
