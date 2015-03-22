#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : KXmlGuiWindow(parent)
{
    _marble = new Marble::MarbleWidget(parent);
    _marble->setProjection(Marble::Mercator);
    _marble->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    setCentralWidget(_marble);
    setupGUI();
}

MainWindow::~MainWindow()
{
    delete _marble;
}
