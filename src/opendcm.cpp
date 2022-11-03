#include "opendcm.h"
#include <vtkNew.h>
#include <vtkRenderWindow.h>

OpenDcm::OpenDcm()
{
    m_rgbchange = nullptr;
    reader = vtkDICOMImageReader::New();
    volumeMapper = vtkGPUVolumeRayCastMapper::New();
    volumeProperty = vtkVolumeProperty::New();
    compositeOpacity = vtkPiecewiseFunction::New();
    volumeGradientOpacity = vtkPiecewiseFunction::New();
    color = vtkColorTransferFunction::New();
    volume = vtkVolume::New();
    dcmViewer = vtkImageViewer2::New();
    resliceAxes = vtkMatrix4x4::New();
    imageStyle = vtkInteractorStyleTrackballCamera::New();
    interactor = vtkRenderWindowInteractor::New();
    imagecolor = vtkImageMapToColors::New();
    imageViewer = vtkImageViewer2::New();
    table = vtkLookupTable::New();
    reslice = vtkImageReslice::New();
    myinteractor = new rewriteInteractor;
}

OpenDcm::~OpenDcm()
{
    reader->Delete();
    reader = nullptr;
    volumeMapper->Delete();
    volumeMapper = nullptr;
    volumeProperty->Delete();
    volumeProperty = nullptr;
    compositeOpacity->Delete();
    compositeOpacity = nullptr;
    volumeGradientOpacity->Delete();
    volumeGradientOpacity = nullptr;
    color->Delete();
    color = nullptr;
    volume->Delete();
    volume = nullptr;
    dcmViewer->Delete();
    dcmViewer = nullptr;
    resliceAxes->Delete();
    resliceAxes = nullptr;
    imageStyle->Delete();
    imageStyle = nullptr;
    imagecolor->Delete();
    imagecolor = nullptr;
    imageViewer->Delete();
    imageViewer = nullptr;
    interactor->Delete();
    interactor = nullptr;
    table->Delete();
    table = nullptr;
    reslice->Delete();
    reslice = nullptr;

    myinteractor->Delete();
    myinteractor = nullptr;
}

void OpenDcm::setParam(RGBAchange *rgbchange)
{
    m_rgbchange = rgbchange;
}

int OpenDcm::viewDcmFile(QQuickVTKRenderItem *item)
{
    MyDialog dlg;

    QStringList filelist = dlg.OpenFile();

    if(filelist.isEmpty())
    {
        dlg.Wraningdlg();
        return 0;
    }

    foreach(QString variable, filelist)
    {
        reader->SetFileName(variable.toUtf8().data());
        reader->Update();

        dcmViewer->SetInputConnection(reader->GetOutputPort());
        dcmViewer->SetRenderWindow(item->renderer()->GetRenderWindow());
        dcmViewer->Render();
        dcmViewer->GetRenderer()->ResetCamera();
        dcmViewer->Render();

        item->renderer()->SetBackground(0, 0, 0);
        item->renderer()->SetViewport(0, 0, 0.5, 1);
    }
    return 2;
}

int OpenDcm::viewDcmDir(QQuickVTKRenderItem *item, RGBAchange *rgbchange)
{
    MyDialog dlg;

    Mypath=dlg.OpenDir();

    if(Mypath.isEmpty())
    {
        dlg.Wraningdlg();
        return 0;
    }

    reader->SetDirectoryName(Mypath.toUtf8().data());
    reader->SetDataByteOrderToLittleEndian();
    reader->Update();

    volumeMapper->SetInputData(reader->GetOutput());
    volumeMapper->SetSampleDistance(0.1);
    volumeMapper->SetAutoAdjustSampleDistances(0);
    volumeMapper->SetBlendModeToComposite();

    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn(); //打开或者关闭阴影测试.
    volumeProperty->SetAmbient(0.4);
    volumeProperty->SetDiffuse(0.6);  //漫反射.
    volumeProperty->SetSpecular(0.2); //镜面反射.

    //设置不透明度.
    compositeOpacity->AddPoint(rgbchange->m_Point[0], rgbchange->m_Alpha[0], 0.5, 0.0);
    compositeOpacity->AddPoint(rgbchange->m_Point[1], rgbchange->m_Alpha[1], 0.49, .61);
    compositeOpacity->AddPoint(rgbchange->m_Point[2], rgbchange->m_Alpha[2], .5, 0.0);
    compositeOpacity->AddPoint(rgbchange->m_Point[3], rgbchange->m_Alpha[3], 0.5, 0.0);
    volumeProperty->SetScalarOpacity(compositeOpacity); //设置不透明度传输函数.

    //设置梯度不透明属性.
    volumeGradientOpacity->AddPoint(10, 0.0);
    volumeGradientOpacity->AddPoint(90, 0.5);
    volumeGradientOpacity->AddPoint(100, 1.0);
    volumeProperty->SetGradientOpacity(volumeGradientOpacity); //设置梯度不透明度效果对比.

    //设置颜色属性.
    color->AddRGBPoint(rgbchange->m_Point[0], rgbchange->m_Red[0], rgbchange->m_Green[0], rgbchange->m_Blue[0], 0.5, 0.0);
    color->AddRGBPoint(rgbchange->m_Point[1], rgbchange->m_Red[1], rgbchange->m_Green[1], rgbchange->m_Blue[1], 0.49, .61);
    color->AddRGBPoint(rgbchange->m_Point[2], rgbchange->m_Red[2], rgbchange->m_Green[2], rgbchange->m_Blue[2], .5, 0.0);
    color->AddRGBPoint(rgbchange->m_Point[3], rgbchange->m_Red[3], rgbchange->m_Green[3], rgbchange->m_Blue[3], .5, 0.0);
    volumeProperty->SetColor(color);

    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);

    rgbchange->SetParam(volumeProperty, volume, item);

    myinteractor->SetParam(volumeProperty, volume, rgbchange);
    item->renderer()->GetRenderWindow()->GetInteractor()->SetInteractorStyle(myinteractor);

    item->renderer()->AddVolume(volume);
    item->renderer()->ResetCamera();
    item->renderer()->SetBackground(0, 0, 0);
    item->renderer()->SetViewport(0, 0, 0.5, 1);

    return 1;
}

void OpenDcm::droviewDcmFile(QQuickVTKRenderItem *item , const char *path)
{
    reader->SetFileName(path);
    reader->Update();

    dcmViewer->SetInputConnection(reader->GetOutputPort());
    dcmViewer->SetRenderWindow(item->renderer()->GetRenderWindow());
    dcmViewer->Render();
    dcmViewer->GetRenderer()->ResetCamera();
    dcmViewer->Render();

    item->renderer()->ResetCamera();
    item->renderer()->SetBackground(0, 0, 0);
    item->renderer()->SetViewport(0, 0, 0.5, 1);
}

void OpenDcm::droviewDcmDir(QQuickVTKRenderItem *item, const char *path)
{
    reader->SetDirectoryName(path);
    reader->SetDataByteOrderToLittleEndian();
    reader->Update();

    volumeMapper->SetInputData(reader->GetOutput());
    volumeMapper->SetSampleDistance(0.1);
    volumeMapper->SetAutoAdjustSampleDistances(0);
    volumeMapper->SetBlendModeToComposite();

    volumeProperty->SetInterpolationTypeToLinear();
    volumeProperty->ShadeOn(); //打开或者关闭阴影测试.
    volumeProperty->SetAmbient(0.4);
    volumeProperty->SetDiffuse(0.6);  //漫反射.
    volumeProperty->SetSpecular(0.2); //镜面反射.

    //设置不透明度.
    compositeOpacity->AddPoint(m_rgbchange->m_Point[0], m_rgbchange->m_Alpha[0], 0.5, 0.0);
    compositeOpacity->AddPoint(m_rgbchange->m_Point[1], m_rgbchange->m_Alpha[1], 0.49, .61);
    compositeOpacity->AddPoint(m_rgbchange->m_Point[2], m_rgbchange->m_Alpha[2], .5, 0.0);
    compositeOpacity->AddPoint(m_rgbchange->m_Point[3], m_rgbchange->m_Alpha[3], 0.5, 0.0);
    volumeProperty->SetScalarOpacity(compositeOpacity); //设置不透明度传输函数.

    //设置梯度不透明属性.
    volumeGradientOpacity->AddPoint(10, 0.0);
    volumeGradientOpacity->AddPoint(90, 0.5);
    volumeGradientOpacity->AddPoint(100, 1.0);
    volumeProperty->SetGradientOpacity(volumeGradientOpacity); //设置梯度不透明度效果对比.

    //设置颜色属性.
    color->AddRGBPoint(m_rgbchange->m_Point[0], m_rgbchange->m_Red[0], m_rgbchange->m_Green[0], m_rgbchange->m_Blue[0], 0.5, 0.0);
    color->AddRGBPoint(m_rgbchange->m_Point[1], m_rgbchange->m_Red[1], m_rgbchange->m_Green[1], m_rgbchange->m_Blue[1], 0.49, .61);
    color->AddRGBPoint(m_rgbchange->m_Point[2], m_rgbchange->m_Red[2], m_rgbchange->m_Green[2], m_rgbchange->m_Blue[2], .5, 0.0);
    color->AddRGBPoint(m_rgbchange->m_Point[3], m_rgbchange->m_Red[3], m_rgbchange->m_Green[3], m_rgbchange->m_Blue[3], .5, 0.0);
    volumeProperty->SetColor(color);

    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);

    m_rgbchange->SetParam(volumeProperty, volume, item);

    rewriteInteractor *myinteractor = new rewriteInteractor;
    myinteractor->SetParam(volumeProperty, volume , m_rgbchange);
    item->renderer()->GetRenderWindow()->GetInteractor()->SetInteractorStyle(myinteractor);

    item->renderer()->AddVolume(volume);
    item->renderer()->ResetCamera();
    item->renderer()->SetBackground(0, 0, 0);
    item->renderer()->SetViewport(0, 0, 0.5, 1);
    item->update();
}

int OpenDcm::droview(QQuickVTKRenderItem *item, QUrl path)
{
    Mypath = path.toString();
    Mypath = Mypath.section("file:///", 1, 1);
    fi = new QFileInfo(Mypath);

    if (fi->exists())
    {
        if(fi->isFile())
        {
            droviewDcmFile(item, Mypath.toUtf8().data());
            return 2;
        }
        else if(fi->isDir())
        {
            droviewDcmDir(item, Mypath.toUtf8().data());
            return 1;
        }
    }
    else
    {
        MyDialog dlg;
        dlg.Wraningdlg();
        return 0;
    }
    return 0;
}

void OpenDcm::sliceView(int num)
{
    if(reader->GetDirectoryName() == nullptr)
    {
        return;
    }
    int extent[6];
    double spacing[3];
    double origin[3];

    reader->GetOutputInformation(0)->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
    reader->GetOutput()->GetSpacing(spacing);
    reader->GetOutput()->GetOrigin(origin);

    double center[3];
    center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
    center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
    center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);

    // Matrices for axial, coronal, sagittal, oblique view orientations
    static double axialElements[16] = {1, 0, 0, 0, 0, 1, 0, 0,
                                       0, 0, 1, 0, 0, 0, 0, 1};

    static double coronalElements[16] = {1, 0, 0, 0, 0, 0, 1, 0,
                                         0, -1, 0, 0, 0, 0, 0, 1};

    static double sagittalElements[16] = {
        0, 0, -1, 0, 
        1, 0, 0, 0,  
        0, -1, 0, 0, 
        0, 0, 0, 1   
    };

    // Set the slice orientation

    switch(num)
    {
        case 1:{
            resliceAxes->DeepCopy(axialElements);
            break;
        }
        case 2:
        {
            resliceAxes->DeepCopy(coronalElements);
            break;
        }
        case 3:
        {
            resliceAxes->DeepCopy(sagittalElements);
            break;
        }
        default: break;
    }

    // Set the point through which to slice
    resliceAxes->SetElement(0, 3, center[0]);
    resliceAxes->SetElement(1, 3, center[1]);
    resliceAxes->SetElement(2, 3, center[2]);

    // Extract a slice in the desired orientation
    reslice->SetInputConnection(reader->GetOutputPort());
    reslice->SetOutputDimensionality(2);
    reslice->SetResliceAxes(resliceAxes);
    reslice->SetInterpolationModeToLinear();

    // Create a greyscale lookup table
    table->SetRange(0, 2000);            // image intensity range
    table->SetValueRange(0.0, 1.0);      // from black to white
    table->SetSaturationRange(0.0, 0.0); // no color saturation
    table->SetRampToLinear();
    table->Build();

    // Map the image through the lookup table
    imagecolor->SetLookupTable(table);
    imagecolor->SetInputConnection(reslice->GetOutputPort());
    interactor->SetInteractorStyle(imageStyle);

    imageViewer->SetInputConnection(imagecolor->GetOutputPort());

    imageViewer->SetupInteractor(interactor);
    imageViewer->Render();
    imageViewer->GetRenderer()->ResetCamera();
    imageViewer->Render();

    interactor->Start();
}
