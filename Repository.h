#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
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
    QList<Track> getTracks(const Box &box);
    QList<TrackPoint> getTrackPoints(const Track &track);
    QList<WayPoint> getWayPoints(const Box &box);

private:
    QSqlDatabase m_db;
    QSqlQuery *m_pGetLastRowIdQuery;
    QSqlQuery *m_pInsertActivityQuery;
    QSqlQuery *m_pInsertGearQuery;
    QSqlQuery *m_pInsertTourQuery;
    QSqlQuery *m_pInsertTrackQuery;
    QSqlQuery *m_pInsertTrackPointQuery;
    QSqlQuery *m_pInsertWayPointQuery;
    QSqlQuery *m_pGetTracksQuery;
    QSqlQuery *m_pGetWayPointsQuery;

    void execute(const QString &sql);
    void loadSpatialite();
    void init();
    void prepareQueries();
    void createTable(const char *name, const char *columns);
    pkey_t insert(QSqlQuery *pQuery, const QList<QVariant> &bindValues);
};

#endif
