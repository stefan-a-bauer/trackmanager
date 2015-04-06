#include "mainwindow.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QSettings>

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
    QSettings settings;

    QString lastImportedFileKey = "lastImportedFile";

    QString lastImportedFile = settings.value(lastImportedFileKey).toString();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Select file to import"), lastImportedFile);

    if (!fileName.isEmpty())
    {
        settings.setValue(lastImportedFileKey, fileName);
        _importer->Import(_model, fileName);
    }
}
