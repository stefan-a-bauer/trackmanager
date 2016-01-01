#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <marble/MarbleWidget.h>

#include "abstractimporter.h"
#include "Repository.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(
            Repository *repository,
            AbstractImporter *importer);

private slots:
    void import();

private:
    Repository *m_repository;
    AbstractImporter *m_importer;

    Marble::MarbleWidget *m_marble;
    QMenu *m_fileMenu;
    QAction *m_importAction;
};

#endif // MAINWINDOW_H
