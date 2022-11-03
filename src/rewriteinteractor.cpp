#include "rewriteinteractor.h"
#include <QDebug>

rewriteInteractor::rewriteInteractor()
{
    m_threshold=0;
    d=0;
    size=0;
    m_volumeProperty = nullptr;
    m_volume = nullptr;
    m_rgbchange = nullptr;
}

void rewriteInteractor::SetParam(vtkVolumeProperty *volumeProperty , vtkVolume *volume , RGBAchange *rgbchange)
{
    m_volumeProperty = volumeProperty;
    m_volume = volume;
    m_rgbchange = rgbchange;
}

void rewriteInteractor::OnMouseMove()
{
    int x = this->Interactor->GetEventPosition()[0];
    int y = this->Interactor->GetEventPosition()[1];
    mouseY=y;

    switch (this->State)
    {
      case VTKIS_ENV_ROTATE:
        this->FindPokedRenderer(x, y);
        this->EnvironmentRotate();
        this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
        break;

      case VTKIS_ROTATE:
        this->FindPokedRenderer(x, y);
        this->Rotate();
        this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
        break;

      case VTKIS_PAN:
        this->FindPokedRenderer(x, y);
        this->Pan();
        this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
        break;

      case VTKIS_SPIN:
        this->FindPokedRenderer(x, y);
        this->Thresholdchanged();
        this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
        break;
    }

}

void rewriteInteractor::OnMiddleButtonDown()
{
    this->FindPokedRenderer(this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1]);
    if (this->CurrentRenderer == nullptr)
    {
      return;
    }
    this->State = VTKIS_SPIN;
}

void rewriteInteractor::OnMiddleButtonUp()
{
    if(this->State!=VTKIS_SPIN)
    {
        return;
    }
    this->State = VTKIS_NONE;
    if (this->Interactor)
    {
        this->ReleaseFocus();
    }
}

void rewriteInteractor::OnLeftButtonDown()
{
    this->FindPokedRenderer(this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1]);
    if (this->CurrentRenderer == nullptr)
    {
        return;
    }
    this->State = VTKIS_ROTATE;
}

void rewriteInteractor::OnLeftButtonUp()
{
    if(this->State!=VTKIS_ROTATE)
    {
        return;
    }
    this->State = VTKIS_NONE;
    if (this->Interactor)
    {
        this->ReleaseFocus();
    }
}

void rewriteInteractor::OnRightButtonDown()
{
    this->FindPokedRenderer(this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1]);
    if (this->CurrentRenderer == nullptr)
    {
        return;
    }
    this->State = VTKIS_PAN;
}

void rewriteInteractor::OnRightButtonUp()
{
    if(this->State!=VTKIS_PAN)
    {
        return;
    }
    this->State = VTKIS_NONE;
    if (this->Interactor)
    {
        this->ReleaseFocus();
    }
}

void rewriteInteractor::OnMouseWheelForward()
{
    this->FindPokedRenderer(this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1]);
    if (this->CurrentRenderer == nullptr)
    {
        return;
    }
    MoveSliceForward();

    if (this->Interactor)
    {
        this->ReleaseFocus();
    }
}

void rewriteInteractor::OnMouseWheelBackward()
{
    this->FindPokedRenderer(this->Interactor->GetEventPosition()[0], this->Interactor->GetEventPosition()[1]);
    if (this->CurrentRenderer == nullptr)
    {
        return;
    }
    MoveSliceBackward();

    if (this->Interactor)
    {
        this->ReleaseFocus();
    }
}

//------------------------------------------------------------------------------
void rewriteInteractor::Thresholdchanged()
{
    if (this->CurrentRenderer == nullptr)
    {
        return;
    }

    if(d==0)
    {
        d=mouseY-m_threshold;
        m_threshold=mouseY;
        return;
    }

    d=mouseY-m_threshold;
    m_volumeProperty->GetScalarOpacity()->RemoveAllPoints();
    m_volumeProperty->GetRGBTransferFunction()->RemoveAllPoints();
    if(d>0)
    {
        QList<double>::iterator it_m_Point = m_rgbchange->m_Point.begin();

        for(; it_m_Point != m_rgbchange->m_Point.end(); ++it_m_Point)
        {
            *it_m_Point+=100;
        }

        //设置不透明度.
        m_volumeProperty->GetScalarOpacity()->AddPoint(m_rgbchange->m_Point[0], m_rgbchange->m_Alpha[0], 0.5, 0.0);
        m_volumeProperty->GetScalarOpacity()->AddPoint(m_rgbchange->m_Point[1], m_rgbchange->m_Alpha[1], 0.5, 0.0);
        m_volumeProperty->GetScalarOpacity()->AddPoint(m_rgbchange->m_Point[2], m_rgbchange->m_Alpha[2], .49, .61);
        m_volumeProperty->GetScalarOpacity()->AddPoint(m_rgbchange->m_Point[3], m_rgbchange->m_Alpha[3], .5, 0.0);

        //设置颜色属性.
        m_volumeProperty->GetRGBTransferFunction()->AddRGBPoint(m_rgbchange->m_Point[0], m_rgbchange->m_Red[0], m_rgbchange->m_Green[0], m_rgbchange->m_Blue[0], 0.5, 0.0);
        m_volumeProperty->GetRGBTransferFunction()->AddRGBPoint(m_rgbchange->m_Point[1], m_rgbchange->m_Red[1], m_rgbchange->m_Green[1], m_rgbchange->m_Blue[1], 0.49, .61);
        m_volumeProperty->GetRGBTransferFunction()->AddRGBPoint(m_rgbchange->m_Point[2], m_rgbchange->m_Red[2], m_rgbchange->m_Green[2], m_rgbchange->m_Blue[2], .5, 0.0);
        m_volumeProperty->GetRGBTransferFunction()->AddRGBPoint(m_rgbchange->m_Point[3], m_rgbchange->m_Red[3], m_rgbchange->m_Green[3], m_rgbchange->m_Blue[3], .5, 0.0);
    }
    else if(d<0)
    {
        QList<double>::iterator it_m_Point = m_rgbchange->m_Point.begin();

        for(; it_m_Point != m_rgbchange->m_Point.end(); ++it_m_Point)
        {
            *it_m_Point-=100;
        }

        //设置不透明度.
        m_volumeProperty->GetScalarOpacity()->AddPoint(m_rgbchange->m_Point[0], m_rgbchange->m_Alpha[0], 0.5, 0.0);
        m_volumeProperty->GetScalarOpacity()->AddPoint(m_rgbchange->m_Point[1], m_rgbchange->m_Alpha[1], 0.5, 0.0);
        m_volumeProperty->GetScalarOpacity()->AddPoint(m_rgbchange->m_Point[2], m_rgbchange->m_Alpha[2], .49, .61);
        m_volumeProperty->GetScalarOpacity()->AddPoint(m_rgbchange->m_Point[3], m_rgbchange->m_Alpha[3], .5, 0.0);

        //设置颜色属性.
        m_volumeProperty->GetRGBTransferFunction()->AddRGBPoint(m_rgbchange->m_Point[0], m_rgbchange->m_Red[0], m_rgbchange->m_Green[0], m_rgbchange->m_Blue[0], 0.5, 0.0);
        m_volumeProperty->GetRGBTransferFunction()->AddRGBPoint(m_rgbchange->m_Point[1], m_rgbchange->m_Red[1], m_rgbchange->m_Green[1], m_rgbchange->m_Blue[1], 0.49, .61);
        m_volumeProperty->GetRGBTransferFunction()->AddRGBPoint(m_rgbchange->m_Point[2], m_rgbchange->m_Red[2], m_rgbchange->m_Green[2], m_rgbchange->m_Blue[2], .5, 0.0);
        m_volumeProperty->GetRGBTransferFunction()->AddRGBPoint(m_rgbchange->m_Point[3], m_rgbchange->m_Red[3], m_rgbchange->m_Green[3], m_rgbchange->m_Blue[3], .5, 0.0);
    }
    this->CurrentRenderer->AddVolume(m_volume);

    m_threshold=mouseY;

    this->Interactor->Render();
}

void rewriteInteractor::Rotate()
{
    if (this->CurrentRenderer == nullptr)
    {
        return;
    }

    vtkRenderWindowInteractor* rwi = this->Interactor;

    int dx = rwi->GetEventPosition()[0] - rwi->GetLastEventPosition()[0];
    int dy = rwi->GetEventPosition()[1] - rwi->GetLastEventPosition()[1];

    const int* size = this->CurrentRenderer->GetRenderWindow()->GetSize();

    double delta_elevation = -200.0 / size[1];
    double delta_azimuth = -200.0 / size[0];

    double rxf = dx * delta_azimuth;
    double ryf = dy * delta_elevation;

    vtkCamera* camera = this->CurrentRenderer->GetActiveCamera();
    camera->Azimuth(rxf);
    camera->Elevation(ryf);
    camera->OrthogonalizeViewUp();

    if (this->AutoAdjustCameraClippingRange)
    {
        this->CurrentRenderer->ResetCameraClippingRange();
    }

    if (rwi->GetLightFollowCamera())
    {
        this->CurrentRenderer->UpdateLightsGeometryToFollowCamera();
    }

    rwi->Render();
}

void rewriteInteractor::Pan()
{
    if (this->CurrentRenderer == nullptr)
    {
        return;
    }

    vtkRenderWindowInteractor* rwi = this->Interactor;

    double viewFocus[4], focalDepth, viewPoint[3];
    double newPickPoint[4], oldPickPoint[4], motionVector[3];

    // Calculate the focal depth since we'll be using it a lot

    vtkCamera* camera = this->CurrentRenderer->GetActiveCamera();
    camera->GetFocalPoint(viewFocus);
    this->ComputeWorldToDisplay(viewFocus[0], viewFocus[1], viewFocus[2], viewFocus);
    focalDepth = viewFocus[2];

    this->ComputeDisplayToWorld(rwi->GetEventPosition()[0], rwi->GetEventPosition()[1], focalDepth, newPickPoint);

    // Has to recalc old mouse point since the viewport has moved,
    // so can't move it outside the loop

    this->ComputeDisplayToWorld(rwi->GetLastEventPosition()[0], rwi->GetLastEventPosition()[1], focalDepth, oldPickPoint);

    // Camera motion is reversed

    motionVector[0] = oldPickPoint[0] - newPickPoint[0];
    motionVector[1] = oldPickPoint[1] - newPickPoint[1];
    motionVector[2] = oldPickPoint[2] - newPickPoint[2];

    camera->GetFocalPoint(viewFocus);
    camera->GetPosition(viewPoint);
    camera->SetFocalPoint(motionVector[0] + viewFocus[0], motionVector[1] + viewFocus[1], motionVector[2] + viewFocus[2]);

    camera->SetPosition(motionVector[0] + viewPoint[0], motionVector[1] + viewPoint[1], motionVector[2] + viewPoint[2]);

    if (rwi->GetLightFollowCamera())
    {
        this->CurrentRenderer->UpdateLightsGeometryToFollowCamera();
    }

    rwi->Render();
}

void rewriteInteractor::MoveSliceForward()
{
    this->vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
}

void rewriteInteractor::MoveSliceBackward()
{
    this->vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
}
