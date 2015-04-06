#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <marble/MarbleWidget.h>

#include "abstractimporter.h"
#include "abstractmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(
            AbstractModel *model,
            AbstractImporter *importer);

private slots:
    void import();

private:
    AbstractModel *_model;
    AbstractImporter *_importer;

    Marble::MarbleWidget *_marble;
    QMenu *_fileMenu;
    QAction *_importAction;
};

#endif // MAINWINDOW_H
