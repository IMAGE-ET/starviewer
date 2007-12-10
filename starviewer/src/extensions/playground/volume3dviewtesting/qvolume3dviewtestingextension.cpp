/***************************************************************************
 *   Copyright (C) 2007 by Grup de Gràfics de Girona                       *
 *   http://iiia.udg.es/GGG/index.html?langu=uk                            *
 *                                                                         *
 *   Universitat de Girona                                                 *
 ***************************************************************************/

#include "qvolume3dviewtestingextension.h"
#include "volume.h"
#include "toolmanager.h"
// qt
#include <QAction>
#include <QSettings>

namespace udg {

QVolume3DViewTestingExtension::QVolume3DViewTestingExtension( QWidget * parent )
 : QWidget( parent )
{
    setupUi( this );

    initializeTools();
    createConnections();
    readSettings();
}

QVolume3DViewTestingExtension::~QVolume3DViewTestingExtension()
{
    writeSettings();
}

void QVolume3DViewTestingExtension::initializeTools()
{
    m_toolManager = new ToolManager(this);
    // obtenim les accions de cada tool que volem
    m_zoomToolButton->setDefaultAction( m_toolManager->getToolAction("ZoomTool") );
    m_rotate3DToolButton->setDefaultAction( m_toolManager->getToolAction("Rotate3DTool") );
    m_panToolButton->setDefaultAction( m_toolManager->getToolAction("TranslateTool") );

    // Activem les tools que volem tenir per defecte, això és com si clickéssim a cadascun dels ToolButton
    m_zoomToolButton->defaultAction()->trigger();
    m_panToolButton->defaultAction()->trigger();
    m_rotate3DToolButton->defaultAction()->trigger();

    // registrem al manager les tools que van amb el viewer principal
    QStringList toolsList;
    toolsList << "ZoomTool" << "TranslateTool" << "Rotate3DTool";
    m_toolManager->setViewerTools( m_3DView, toolsList );
    m_toolManager->refreshConnections();
}

void QVolume3DViewTestingExtension::createConnections()
{
    // orientacions axial,sagital i coronal
    connect( m_axialOrientationButton , SIGNAL( clicked() ) , m_3DView , SLOT( resetViewToAxial() ) );
    connect( m_sagitalOrientationButton , SIGNAL( clicked() ) , m_3DView , SLOT( resetViewToSagital() ) );
    connect( m_coronalOrientationButton , SIGNAL( clicked() ) , m_3DView , SLOT( resetViewToCoronal() ) );

    // actualització de la funció de transferència
    connect( m_transferFunctionUpdateButton, SIGNAL( clicked() ), SLOT( updateTransferFunctionFromEditor() ) );

    // actualització del mètode de rendering
    connect( m_renderingMethodComboBox, SIGNAL( activated(int) ), SLOT( updateRenderingMethodFromCombo(int) ) );
}

void QVolume3DViewTestingExtension::setInput( Volume * input )
{
    m_input = input;
    m_3DView->setInput( m_input );
    m_3DView->render();
}

void QVolume3DViewTestingExtension::updateTransferFunctionFromEditor()
{
    // obtenim la funció de transferència de l'editor i li assignem al 3D viewer
}

void QVolume3DViewTestingExtension::updateRenderingMethodFromCombo( int index )
{
    this->setCursor( QCursor(Qt::WaitCursor) );
    switch( index )
    {
    case 0:
        m_3DView->setRenderFunctionToRayCasting();
    break;

    case 1:
        m_3DView->setRenderFunctionToMIP3D();
    break;

    case 2:
        m_3DView->setRenderFunctionToTexture3D();
    break;

    case 3:
        m_3DView->setRenderFunctionToTexture2D();
    break;

    case 4:
        m_3DView->setRenderFunctionToIsoSurface();
    break;
    }
    m_3DView->render();
    this->setCursor( QCursor(Qt::ArrowCursor) );
}

void QVolume3DViewTestingExtension::readSettings()
{
    QSettings settings;
    settings.beginGroup("Starviewer-App-3DTesting");

    m_3DViewSplitter->restoreState( settings.value("3DViewSplitter").toByteArray() );

    settings.endGroup();
}

void QVolume3DViewTestingExtension::writeSettings()
{
    QSettings settings;
    settings.beginGroup("Starviewer-App-3DTesting");

    settings.setValue("3DViewSplitter", m_3DViewSplitter->saveState() );

    settings.endGroup();
}

}

