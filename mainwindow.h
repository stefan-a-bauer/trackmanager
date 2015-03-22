#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <KXmlGuiWindow>
#include <KTextEdit>
#include <marble/MarbleWidget.h>

class MainWindow : public KXmlGuiWindow
{
  public:
    MainWindow(QWidget *parent=0);
    ~MainWindow();

  private:
    Marble::MarbleWidget *_marble;

};

#endif // MAINWINDOW_H
