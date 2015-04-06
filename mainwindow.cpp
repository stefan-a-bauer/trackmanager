#include "mainwindow.h"

#include <QMenuBar>

MainWindow::MainWindow()
{
    _marble = new Marble::MarbleWidget();
    _marble->setProjection(Marble::Mercator);
    _marble->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    setCentralWidget(_marble);

    _importAction = new QAction(tr("&Import..."), this);
    connect(_importAction, SIGNAL(triggered()), this, SLOT(import()));
    _fileMenu = menuBar()->addMenu(tr("&File"));
    _fileMenu->addAction(_importAction);
}

void MainWindow::import()
{

}
