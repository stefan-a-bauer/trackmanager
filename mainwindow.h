#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <marble/MarbleWidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void import();

private:
    Marble::MarbleWidget *_marble;
    QMenu *_fileMenu;
    QAction *_importAction;
};

#endif // MAINWINDOW_H
