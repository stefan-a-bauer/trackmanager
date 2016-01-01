#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QtSql/QSqlDatabase>
#include <QVariant>
#include "TrackPoint.h"
#include "WayPoint.h"
#include "Highlight.h"

class Repository
{
public:
    Repository();
    ~Repository();

    void open();

    void close();

    void beginTransaction();

    void commitTransaction();

    void rollbackTransaction();

    pkey_t createActivity(const QString &name);

    pkey_t createGear(const QString &name, const Activity &activity);

    pkey_t createTour(const QString &name, const QString &description);

    pkey_t createTrack(
        const QString &name,
        const QString &description,
        pkey_t tourId,
        const Gear &gear,
        const Activity &activity);

    pkey_t createTrackPoint(double lat, double lon, double elevation, const QDateTime &time, pkey_t trackId);

    pkey_t createWayPoint(
        const QString &name,
        double lat,
        double lon,
        double elevation,
        const QDateTime &time,
        pkey_t tourId);

    pkey_t createHighlight(const QString &name,
        const QString &description,
        const QList<Position> &geometry,
        qint32 rating, const Activity &activity);

    QList<Activity> getActivities();
    QList<Gear> getGear();
    QList<Tour> getTours();
    QList<Track> getTracks();
    QList<TrackPoint> getTrackPoints(const Track &track);
    QList<WayPoint> getWayPoints(const Tour &tour);

private:
    QSqlDatabase m_db;

    void execute(const QString &sql);
    void loadSpatialite();
    void init();
    void createTable(const char *name, const char *columns);
    pkey_t insert(const QString &table, const QStringList &columns, const QStringList &values, const QList<QVariant> &bindValues);
    pkey_t insert(const QString &table, const QStringList &columns, const QList<QVariant> &bindValues);
};

#endif
