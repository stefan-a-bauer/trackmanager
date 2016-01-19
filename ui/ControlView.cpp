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


#include "ControlView.h"

#include <QLayout>
#include <QDockWidget>

#include <marble/MarbleWidget.h>
#include <marble/MarbleDebug.h>
#include <marble/MarbleDirs.h>
#include <marble/MarbleModel.h>
#include <marble/MarbleMap.h>
#include <marble/MapThemeManager.h>
#include <marble/MapViewWidget.h>

ControlView::ControlView( QWidget *parent )
   : QWidget( parent ),
     m_mapThemeManager( new Marble::MapThemeManager( this ) ),
     m_togglePanelVisibilityAction( 0 ),
     m_isPanelVisible( true )
{
    m_marbleWidget = new Marble::MarbleWidget( this );
    m_marbleWidget->setSizePolicy( QSizePolicy( QSizePolicy::MinimumExpanding,
                                                QSizePolicy::MinimumExpanding ) );

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( m_marbleWidget );
    layout->setMargin( 0 );
    setLayout( layout );
}

ControlView::~ControlView()
{
    // nothing to do
}

Marble::MapThemeManager *ControlView::mapThemeManager()
{
    return m_mapThemeManager;
}

QString ControlView::defaultMapThemeId() const
{
    QStringList fallBackThemes;
      fallBackThemes << "earth/srtm/srtm.dgml";
      fallBackThemes << "earth/bluemarble/bluemarble.dgml";
      fallBackThemes << "earth/openstreetmap/openstreetmap.dgml";

    const QStringList installedThemes = m_mapThemeManager->mapThemeIds();

    foreach(const QString &fallback, fallBackThemes) {
        if (installedThemes.contains(fallback)) {
            return fallback;
        }
    }

    if (installedThemes.size()) {
        return installedThemes.first();
    }

    return QString();
}

QList<QAction*> ControlView::setupDockWidgets(QMainWindow *mainWindow)
{
    mainWindow->setTabPosition( Qt::LeftDockWidgetArea, QTabWidget::North );
    mainWindow->setTabPosition( Qt::RightDockWidgetArea, QTabWidget::North );

    QDockWidget *mapViewDock = new QDockWidget( tr( "Map View" ), this );
    mapViewDock->setObjectName( "mapViewDock" );
    mapViewDock->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    Marble::MapViewWidget* mapViewWidget = new Marble::MapViewWidget( this );
    mapViewWidget->setMarbleWidget( marbleWidget(), m_mapThemeManager );
    connect( mapViewWidget, SIGNAL(showMapWizard()), this, SIGNAL(showMapWizard()) );
    connect( mapViewWidget, SIGNAL(showUploadDialog()), this, SIGNAL(showUploadDialog()) );
    connect( mapViewWidget, SIGNAL(mapThemeDeleted()), this, SIGNAL(mapThemeDeleted()) );
    mapViewDock->setWidget( mapViewWidget );
    mainWindow->addDockWidget( Qt::LeftDockWidgetArea, mapViewDock );
    mapViewDock->raise();

    QList<QAction*> panelActions;
    panelActions << mapViewDock->toggleViewAction();

    // Local list of panel view toggle actions
    m_panelActions << mapViewDock->toggleViewAction();
    foreach( QAction* action, m_panelActions ) {
        m_panelVisibility << action->isVisible();
    }

    // Create Settings->Panels Menu
    // Toggle All Panels action
    m_togglePanelVisibilityAction = new QAction( tr("Hide &All Panels"), this);
    m_togglePanelVisibilityAction->setShortcut( Qt::Key_F9 );
    m_togglePanelVisibilityAction->setStatusTip(tr("Show or hide all panels."));
    connect(m_togglePanelVisibilityAction, SIGNAL(triggered()), this, SLOT(togglePanelVisibility()));

    // Include a Separator in the List
    QAction *panelSeparatorAct = new QAction( this );
    panelSeparatorAct->setSeparator( true );

    // Return a list of panel view actions for Marble Menu including show/hide all
    QList<QAction*> panelMenuActions;
    panelMenuActions << m_togglePanelVisibilityAction;
    panelMenuActions << panelSeparatorAct;
    foreach( QAction* action, m_panelActions ) {
        panelMenuActions << action;
    }

    return panelMenuActions;
}

void ControlView::togglePanelVisibility()
{
    Q_ASSERT( m_panelVisibility.size() == m_panelActions.size() );
    if ( m_isPanelVisible ) {
        for( int p=0; p<m_panelActions.size(); ++p ) {
            // Save state of individual dock visibility
            m_panelVisibility[p] = m_panelActions.at(p)->isChecked();

            // hide panel if it is showing
            if ( m_panelActions.at(p)->isChecked() ) {
                m_panelActions.at(p)->activate( QAction::Trigger );
            }
        }

        // Change Menu Item Text
        m_togglePanelVisibilityAction->setText( tr("Show &All Panels") );
        m_isPanelVisible = false;
    } else {
        for( int p=0; p<m_panelActions.size(); ++p ) {
            // show panel if it was showing before all panels were hidden
            if ( m_panelVisibility.at(p) && !m_panelActions.at(p)->isChecked() ) {
                m_panelActions.at(p)->activate( QAction::Trigger );
            }
        }

        // Change Menu Item Text
        m_togglePanelVisibilityAction->setText( tr("Hide &All Panels") );
        m_isPanelVisible = true;
    }
}
