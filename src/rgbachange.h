#ifndef RGBACHANGE_H
#define RGBACHANGE_H

#include <QObject>
#include <QPointF>
#include <vtkColorTransferFunction.h>
#include "vtkSmartPointer.h"
#include "vtkVolumeProperty.h"
#include "vtkVolume.h"
#include "QQuickVTKRenderItem.h"
#include "vtkPiecewiseFunction.h"

class RGBAchange : public QObject
{
    Q_OBJECT

public:
    RGBAchange();

    Q_INVOKABLE void setRchange(QPointF OldPoint, QPointF NewPoint);
    Q_INVOKABLE void setGchange(QPointF OldPoint, QPointF NewPoint);
    Q_INVOKABLE void setBchange(QPointF OldPoint, QPointF NewPoint);
    Q_INVOKABLE void setAchange(QPointF OldPoint, QPointF NewPoint);
    void SetParam(vtkVolumeProperty *volumeProperty, vtkVolume *volume, QQuickVTKRenderItem *item);

public:
    QList<double> m_Point;
    QList<double> m_Red;
    QList<double> m_Green;
    QList<double> m_Blue;
    QList<double> m_Alpha;
    vtkVolumeProperty *m_volumeProperty;
    vtkVolume *m_volume;
    QQuickVTKRenderItem *m_item;
    vtkPiecewiseFunction *compositeOpacity;
    vtkColorTransferFunction *color;
};

#endif // RGBACHANGE_H
