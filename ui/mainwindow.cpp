#include "mainwindow.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QSettings>

#include "Exception.h"
#include "Layer.h"


#define SETTINGS_VIEW "View"

#define SETTINGS_LAST_IMPORT_DIRECTORY "lastImportDirectory"
#define SETTINGS_VIEW_RANGE "range"
#define SETTINGS_VIEW_COORDINATES "coordinates"


MainWindow::MainWindow(Repository *repository, AbstractImporter *importer)
{
    m_repository = repository;
    m_importer = importer;

    m_marble = new Marble::MarbleWidget();
    m_marble->setProjection(Marble::Mercator);
    m_marble->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    setCentralWidget(m_marble);

    auto layer = new Layer(this, repository);

    // restore the view before wiring up the layer to avoid senseless loading of tracks for the default view
    RestoreView();

    connect(m_marble, SIGNAL(zoomChanged(int)), layer, SLOT(onZoomChanged(int)));
    connect(
        m_marble,
        SIGNAL(visibleLatLonAltBoxChanged(GeoDataLatLonAltBox)),
        layer,
        SLOT(onVisibleLatLonAltBoxChanged(GeoDataLatLonAltBox)));

    m_marble->addLayer(layer);

    m_importAction = new QAction(tr("&Import..."), this);
    connect(m_importAction, SIGNAL(triggered()), this, SLOT(import()));
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_importAction);
}

MainWindow::~MainWindow()
{
    auto lookAt = m_marble->lookAt();

    auto range = lookAt.range();
    auto coordinates = lookAt.coordinates();

    QSettings settings;

    settings.beginGroup(SETTINGS_VIEW);
    settings.setValue(SETTINGS_VIEW_RANGE, range);
    settings.setValue(SETTINGS_VIEW_COORDINATES, coordinates.toString());
    settings.endGroup();

    delete m_marble;
    m_marble = NULL;
}

void MainWindow::import()
{
    try
    {
        QSettings settings;

        QString lastImportDirectory = settings.value(SETTINGS_LAST_IMPORT_DIRECTORY).toString();

        QString fileName = QFileDialog::getOpenFileName(this, tr("Select file to import"), lastImportDirectory);

        if (!fileName.isEmpty())
        {
            settings.setValue(SETTINGS_LAST_IMPORT_DIRECTORY, QFileInfo(fileName).canonicalPath());

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

void MainWindow::RestoreView()
{
    bool ok;

    QSettings settings;

    settings.beginGroup(SETTINGS_VIEW);

    auto coordinatesString = settings.value(SETTINGS_VIEW_COORDINATES).toString();
    auto coordinates = Marble::GeoDataCoordinates::fromString(coordinatesString, ok);

    if (!ok)
    {
        return;
    }

    auto range = settings.value(SETTINGS_VIEW_RANGE).toReal(&ok);

    settings.endGroup();

    if (!ok)
    {
        return;
    }

    Marble::GeoDataLookAt lookAt;

    lookAt.setCoordinates(coordinates);
    lookAt.setRange(range);

    m_marble->flyTo(lookAt, Marble::FlyToMode::Jump);
}
