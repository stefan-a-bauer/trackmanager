#include <QApplication>

#include "gpximporter.h"
#include "mainwindow.h"
#include "Repository.h"

int main (int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Stefan Bauer");
    QCoreApplication::setApplicationName("trackmanager");

    QApplication app(argc, argv);

    Repository repository;

    int exitCode;

    try
    {
        repository.open();

        GpxImporter importer;

        MainWindow mainWindow(&repository, &importer);

        mainWindow.show();

        exitCode = app.exec();
    }
    catch (std::exception &exception)
    {
        qDebug("%s\n", exception.what());
        exitCode = 1;
    }

    repository.close();

    return exitCode;
}
