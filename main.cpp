#include <cstdlib>

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KMessageBox>
#include <KLocale>

int main (int argc, char *argv[])
{
    KAboutData aboutData(
                         "trackmanager",
                         NULL,
                         ki18n("TrackManager"),
                         "0.1",
                         ki18n("Manages tracks"),
                         KAboutData::License_GPL_V3,
                         ki18n("Copyright (C) 2015 Stefan Bauer"),
                         ki18n(""),
                         "",
                         "stefan-a-bauer@gmx.net");

    KCmdLineArgs::init( argc, argv, &aboutData );
    KApplication app;
    return  EXIT_SUCCESS;
}
