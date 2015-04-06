#include "mainwindow.h"

#include <QFileDialog>
#include <QMenuBar>

MainWindow::MainWindow(AbstractModel *model, AbstractImporter *importer)
{
    _model = model;
    _importer = importer;

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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select file to import"));
    if (!fileName.isEmpty())
    {
        _importer->Import(_model, fileName);
    }
}
