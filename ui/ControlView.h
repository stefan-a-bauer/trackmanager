//
// This file originates from the Marble Virtual Globe.
// Copied 2016-01-17.
//
// Original Copyright notice:
//
// This program is free software licensed under the GNU LGPL.
//
// Copyright 2005-2007 Torsten Rahn <tackat@kde.org>
// Copyright 2007      Inge Wallin  <ingwa@kde.org>
//
// Adaptions for trackmanager:
// Copyright 2016 Stefan Bauer <stefan-a-bauer@gmx.net>

#ifndef CONTROLVIEW_H
#define CONTROLVIEW_H


#include <QWidget>
#include <QPixmap>
#include <QPointer>
#include <QMainWindow>
#include <QActionGroup>

#include <marble/MarbleWidget.h>
#include <marble/MapThemeManager.h>

class ControlView : public QWidget
{
    Q_OBJECT

 public:
    explicit ControlView( QWidget * = 0 );
    virtual ~ControlView();

    Marble::MarbleWidget      *marbleWidget()        { return m_marbleWidget; }
    Marble::MarbleModel       *marbleModel()         { return m_marbleWidget->model(); }
    Marble::MapThemeManager   *mapThemeManager();

    QPixmap mapScreenShot() { return m_marbleWidget->mapScreenShot(); }
    
    /**
      * Returns a default map theme: earth/srtm/srtm.dgml if installed,
      * any other theme id if earth/srtm/srtm.dgml is not installed,
      * or an empty string if no themes are installed at all
      */
    QString defaultMapThemeId() const;

    QList<QAction*> setupDockWidgets( QMainWindow* mainWindow );

 public slots:

    /**
     *  Toggles all of the docking panels on or off
     */
    void togglePanelVisibility();

signals:
    void showMapWizard();
    void showUploadDialog();
    void mapThemeDeleted();

 private:

    Marble::MapThemeManager   *const m_mapThemeManager;
    Marble::MarbleWidget      *m_marbleWidget;
    QAction         *m_togglePanelVisibilityAction;
    QList<QAction*>  m_panelActions;
    QList<bool>      m_panelVisibility;
    bool             m_isPanelVisible;
};

#endif
