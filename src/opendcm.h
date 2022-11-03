#ifndef OPENDCM_H
#define OPENDCM_H

#include <QObject>
#include "rewriteinteractor.h"

#include "vtkAutoInit.h"

#include <vtkDICOMImageReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include "mydialog.h"
#include "rgbachange.h"

#include "QQuickVTKInteractiveWidget.h"
#include "QQuickVTKRenderItem.h"
#include "QQuickVTKRenderWindow.h"
#include "vtkActor.h"
#include "vtkAppendPolyData.h"
#include "vtkCamera.h"
#include "vtkClipPolyData.h"
#include "vtkCommand.h"
#include "vtkConeSource.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkGlyph3D.h"
#include "vtkImplicitPlaneRepresentation.h"
#include "vtkImplicitPlaneWidget2.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkNew.h"
#include "vtkPNGWriter.h"
#include "vtkPlane.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "vtkTestUtilities.h"
#include "vtkTesting.h"
#include "vtkWindowToImageFilter.h"

#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QTimer>
#include <QUrl>
#include <qdebug.h>
#include <qlist.h>
#include <qobject.h>
#include <qqml.h>
#include <vtkAngleRepresentation.h>
#include <vtkAngleRepresentation2D.h>
#include <vtkAngleWidget.h>
#include <vtkLeaderActor2D.h>
#include <vtkProperty2D.h>
#include <vtkTextProperty.h>
#include <vtkXMLImageDataReader.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkMarchingCubes.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>
#include <vtkOutlineFilter.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include "vtkCommand.h"
#include "vtkImageActor.h"
#include "vtkImageData.h"
#include "vtkImageMapToColors.h"
#include "vtkImageMapper3D.h"
#include "vtkImageReader2.h"
#include "vtkImageReslice.h"
#include "vtkInformation.h"
#include "vtkInteractorStyleImage.h"
#include "vtkLookupTable.h"
#include "vtkMatrix4x4.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSmartPointer.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkContourFilter.h"

#include "vtkImageResliceMapper.h"

class OpenDcm : public QObject
{
    Q_OBJECT

public:
    OpenDcm();
    ~OpenDcm();

    Q_INVOKABLE int viewDcmFile(QQuickVTKRenderItem *item) ;
    Q_INVOKABLE int viewDcmDir(QQuickVTKRenderItem *item, RGBAchange *rgbchange) ;
    void droviewDcmFile(QQuickVTKRenderItem *item, const char *path);
    void droviewDcmDir(QQuickVTKRenderItem *item, const char *path);
    Q_INVOKABLE int droview(QQuickVTKRenderItem *item, QUrl path);
    Q_INVOKABLE void sliceView(int num);
    Q_INVOKABLE void setParam(RGBAchange *rgbchange);

public:
    QString Mypath;
    RGBAchange *m_rgbchange;
    vtkDICOMImageReader *reader;
    vtkGPUVolumeRayCastMapper *volumeMapper;
    vtkVolumeProperty *volumeProperty;
    vtkPiecewiseFunction *compositeOpacity;
    vtkPiecewiseFunction *volumeGradientOpacity;
    vtkColorTransferFunction *color;
    vtkVolume *volume;
    vtkImageViewer2* dcmViewer;
    QFileInfo * fi;
    vtkMatrix4x4 *resliceAxes;
    vtkInteractorStyleTrackballCamera *imageStyle;
    vtkRenderWindowInteractor *interactor;
    vtkImageMapToColors *imagecolor;
    vtkLookupTable *table;
    vtkImageReslice *reslice;
    vtkImageViewer2 *imageViewer;
    rewriteInteractor *myinteractor;
};

#endif // OPENDCM_H
