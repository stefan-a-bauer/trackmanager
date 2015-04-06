#include <QApplication>

#include "gpximporter.h"
#include "mainwindow.h"
#include "model.h"

int main (int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Stefan Bauer");
    QCoreApplication::setApplicationName("trackmanager");

    QApplication app(argc, argv);

    Model model;
    GpxImporter importer;

    MainWindow mainWindow(&model, &importer);

    mainWindow.show();

    return app.exec();
}
