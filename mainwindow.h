#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <marble/MarbleWidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow();
    ~MainWindow();

  private:
    Marble::MarbleWidget *_marble;
};

#endif // MAINWINDOW_H
