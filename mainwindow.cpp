#include "mainwindow.h"

MainWindow::MainWindow()
{
    _marble = new Marble::MarbleWidget();
    _marble->setProjection(Marble::Mercator);
    _marble->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    setCentralWidget(_marble);
}
