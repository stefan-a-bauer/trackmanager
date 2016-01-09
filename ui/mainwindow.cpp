#include "mainwindow.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QSettings>

#include "Exception.h"
#include "Layer.h"

MainWindow::MainWindow(Repository *repository, AbstractImporter *importer)
{
    m_repository = repository;
    m_importer = importer;

    m_marble = new Marble::MarbleWidget();
    m_marble->setProjection(Marble::Mercator);
    m_marble->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    setCentralWidget(m_marble);

    auto layer = new Layer(this, repository);

    connect(m_marble, SIGNAL(zoomChanged(int)), layer, SLOT(onZoomChanged(int)));

    m_marble->addLayer(layer);

    m_importAction = new QAction(tr("&Import..."), this);
    connect(m_importAction, SIGNAL(triggered()), this, SLOT(import()));
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_importAction);
}

void MainWindow::import()
{
    try
    {
        QSettings settings;

        QString lastImportedFileKey = "lastImportedFile";

        QString lastImportedFile = settings.value(lastImportedFileKey).toString();

        QString fileName = QFileDialog::getOpenFileName(this, tr("Select file to import"), lastImportedFile);

        if (!fileName.isEmpty())
        {
            settings.setValue(lastImportedFileKey, fileName);

            QList<Activity> activities = m_repository->getActivities();

            if (activities.length() == 0)
            {
                m_repository->createActivity("Default Activity");
                activities = m_repository->getActivities();
            }

            const Activity &activity = activities.first();

            QList<Gear> gear = m_repository->getGear();

            if (gear.length() == 0)
            {
                m_repository->createGear("Default Gear", activity);
                gear = m_repository->getGear();
            }

            m_importer->Import(*m_repository, fileName, gear.first(), activity);
        }
    }
    catch (Exception &exception)
    {
        QMessageBox::critical(this, tr("Failed to import file"), exception.what());
    }
}
