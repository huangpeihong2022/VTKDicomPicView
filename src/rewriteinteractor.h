#ifndef REWRITEINTERACTOR_H
#define REWRITEINTERACTOR_H

#include "vtkInteractorStyle.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkRenderer.h"
#include "vtkVolumeProperty.h"
#include "vtkPiecewiseFunction.h"
#include "vtkColorTransferFunction.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include <QList>
#include "rgbachange.h"

class rewriteInteractor : public vtkInteractorStyleTrackballCamera
{
public:
    rewriteInteractor();

    void OnMouseMove() override;
    void OnMiddleButtonDown() override;
    void OnMiddleButtonUp() override;
    void OnLeftButtonDown() override;
    void OnLeftButtonUp() override;
    void OnRightButtonDown() override;
    void OnRightButtonUp() override;
    void OnMouseWheelForward() override;
    void OnMouseWheelBackward() override;

    void Pan() override;
    void Rotate() override;
    void Thresholdchanged();

    void SetParam(vtkVolumeProperty *volumeProperty, vtkVolume *volume, RGBAchange *rgbchange);
    void MoveSliceForward();
    void MoveSliceBackward();

public:
   int m_threshold;
   int d;
   int mouseY;
   double size;
   double MotionFactor;

   vtkVolumeProperty *m_volumeProperty;
   vtkVolume *m_volume;
   RGBAchange *m_rgbchange;
};

#endif // REWRITEINTERACTOR_H
