#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>

#include "abstractimporter.h"
#include "Repository.h"
#include "ControlView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(
            Repository *repository,
            AbstractImporter *importer);
    virtual ~MainWindow();

private slots:
    void import();

private:
    void createMenus(const QList<QAction*> &panelActions);
    void RestoreView();

    Repository *m_repository;
    AbstractImporter *m_importer;

    ControlView *m_controlView;
    QMenu *m_fileMenu;
    QAction *m_importAction;
    QMenu *m_settingsMenu;
    QMenu *m_panelMenu;
};

#endif // MAINWINDOW_H
