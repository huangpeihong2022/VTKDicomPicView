#include "rgbachange.h"
#include <QDebug>

RGBAchange::RGBAchange()
{
    m_Point << -3024 << -16 << 641 << 3071;
    m_Red << 0 << 0.73 << 0.9 << 1;
    m_Green << 0 << 0.25 << 0.82 << 1;
    m_Blue << 0.5 << 0.3 << 0.56 << 1;
    m_Alpha << 0 << 0 << 0.72 << 0.71;
    m_volumeProperty = nullptr;
    m_volume = nullptr;
    m_item=nullptr;
    compositeOpacity=nullptr;
    color=nullptr;
}

void RGBAchange::SetParam(vtkVolumeProperty *volumeProperty, vtkVolume *volume, QQuickVTKRenderItem *item)
{
    m_volumeProperty = volumeProperty;
    m_volume = volume;
    m_item = item;
}

void RGBAchange::setRchange(QPointF OldPoint, QPointF NewPoint)
{
//    qDebug()<<"------";
//    qDebug()<<"oldpoint:"<<OldPoint<<" newpoint"<<NewPoint;
    if(!m_volumeProperty)
    {
        qDebug()<<"错误";
        return;
    }
    if(!m_item)
    {
        qDebug()<<"错误";
        return;
    }
    if(!m_volume)
    {
        qDebug()<<"错误";
        return;
    }

    compositeOpacity = m_volumeProperty->GetScalarOpacity();
    color = m_volumeProperty->GetRGBTransferFunction();

    compositeOpacity->RemoveAllPoints();
    color->RemoveAllPoints();

    QList<double>::iterator it_m_color = m_Red.begin();

    int num = 0;
    for(; it_m_color != m_Red.end(); ++it_m_color)
    {
        if(*it_m_color == OldPoint.y())
        {
            break;
        }
        num++;
    }

    switch(num)
    {
        case 0:{
            m_Point[0] = NewPoint.x();
            m_Red[0] = NewPoint.y();
            break;
        }
        case 1:{
            m_Point[1] = NewPoint.x();
            m_Red[1] = NewPoint.y();
            break;
        }
        case 2:{
            m_Point[2] = NewPoint.x();
            m_Red[2] = NewPoint.y();
            break;
        }
        case 3:{
            m_Point[3] = NewPoint.x();
            m_Red[3] = NewPoint.y();
            break;
        }
    }

    //设置不透明度
    compositeOpacity->AddPoint(m_Point[0], m_Alpha[0], 0.5, 0.0);
    compositeOpacity->AddPoint(m_Point[1], m_Alpha[1], 0.49, .61);
    compositeOpacity->AddPoint(m_Point[2], m_Alpha[2], .5, 0.0);
    compositeOpacity->AddPoint(m_Point[3], m_Alpha[3], 0.5, 0.0);

    //设置颜色属性.
    color->AddRGBPoint(m_Point[0], m_Red[0], m_Green[0], m_Blue[0], 0.5, 0.0);
    color->AddRGBPoint(m_Point[1], m_Red[1], m_Green[1], m_Blue[1], 0.49, .61);
    color->AddRGBPoint(m_Point[2], m_Red[2], m_Green[2], m_Blue[2], .5, 0.0);
    color->AddRGBPoint(m_Point[3], m_Red[3], m_Green[3], m_Blue[3], .5, 0.0);

    m_volumeProperty->SetScalarOpacity(compositeOpacity);
    m_volumeProperty->SetColor(color);

    m_volume->SetProperty(m_volumeProperty);

    m_item->renderer()->AddVolume(m_volume);
    m_item->renderer()->ResetCamera();
    m_item->renderer()->SetBackground(0, 0, 0);
    m_item->renderer()->SetViewport(0, 0, 0.5, 1);
}

void RGBAchange::setGchange(QPointF OldPoint, QPointF NewPoint)
{
    if(!m_volumeProperty)
    {
        qDebug()<<"错误";
        return;
    }
    if(!m_item)
    {
        qDebug()<<"错误";
        return;
    }
    if(!m_volume)
    {
        qDebug()<<"错误";
        return;
    }

    compositeOpacity = m_volumeProperty->GetScalarOpacity();
    color = m_volumeProperty->GetRGBTransferFunction();

    compositeOpacity->RemoveAllPoints();
    color->RemoveAllPoints();

    QList<double>::iterator it_m_color = m_Green.begin();

    int num = 0;
    for(; it_m_color != m_Green.end(); ++it_m_color)
    {
        if(*it_m_color == OldPoint.y())
        {
            break;
        }
        num++;
    }

    switch(num)
    {
        case 0:{
            m_Point[0] = NewPoint.x();
            m_Green[0] = NewPoint.y();
            break;
        }
        case 1:{
            m_Point[1] = NewPoint.x();
            m_Green[1] = NewPoint.y();
            break;
        }
        case 2:{
            m_Point[2] = NewPoint.x();
            m_Green[2] = NewPoint.y();
            break;
        }
        case 3:{
            m_Point[3] = NewPoint.x();
            m_Green[3] = NewPoint.y();
            break;
        }
    }

    //设置不透明度
    compositeOpacity->AddPoint(m_Point[0], m_Alpha[0], 0.5, 0.0);
    compositeOpacity->AddPoint(m_Point[1], m_Alpha[1], 0.49, .61);
    compositeOpacity->AddPoint(m_Point[2], m_Alpha[2], .5, 0.0);
    compositeOpacity->AddPoint(m_Point[3], m_Alpha[3], 0.5, 0.0);

    //设置颜色属性.
    color->AddRGBPoint(m_Point[0], m_Red[0], m_Green[0], m_Blue[0], 0.5, 0.0);
    color->AddRGBPoint(m_Point[1], m_Red[1], m_Green[1], m_Blue[1], 0.49, .61);
    color->AddRGBPoint(m_Point[2], m_Red[2], m_Green[2], m_Blue[2], .5, 0.0);
    color->AddRGBPoint(m_Point[3], m_Red[3], m_Green[3], m_Blue[3], .5, 0.0);

    m_volumeProperty->SetScalarOpacity(compositeOpacity);
    m_volumeProperty->SetColor(color);

    m_volume->SetProperty(m_volumeProperty);

    m_item->renderer()->AddVolume(m_volume);
    m_item->renderer()->ResetCamera();
    m_item->renderer()->SetBackground(0, 0, 0);
    m_item->renderer()->SetViewport(0, 0, 0.5, 1);
}

void RGBAchange::setBchange(QPointF OldPoint, QPointF NewPoint)
{
    if(!m_volumeProperty)
    {
        qDebug()<<"错误";
        return;
    }
    if(!m_item)
    {
        qDebug()<<"错误";
        return;
    }
    if(!m_volume)
    {
        qDebug()<<"错误";
        return;
    }

    compositeOpacity = m_volumeProperty->GetScalarOpacity();
    color = m_volumeProperty->GetRGBTransferFunction();

    compositeOpacity->RemoveAllPoints();
    color->RemoveAllPoints();

    QList<double>::iterator it_m_color = m_Blue.begin();

    int num = 0;
    for(; it_m_color != m_Blue.end(); ++it_m_color)
    {
        if(*it_m_color == OldPoint.y())
        {
            break;
        }
        num++;
    }

    switch(num)
    {
        case 0:{
            m_Point[0] = NewPoint.x();
            m_Blue[0] = NewPoint.y();
            break;
        }
        case 1:{
            m_Point[1] = NewPoint.x();
            m_Blue[1] = NewPoint.y();
            break;
        }
        case 2:{
            m_Point[2] = NewPoint.x();
            m_Blue[2] = NewPoint.y();
            break;
        }
        case 3:{
            m_Point[3] = NewPoint.x();
            m_Blue[3] = NewPoint.y();
            break;
        }
    }

    //设置不透明度
    compositeOpacity->AddPoint(m_Point[0], m_Alpha[0], 0.5, 0.0);
    compositeOpacity->AddPoint(m_Point[1], m_Alpha[1], 0.49, .61);
    compositeOpacity->AddPoint(m_Point[2], m_Alpha[2], .5, 0.0);
    compositeOpacity->AddPoint(m_Point[3], m_Alpha[3], 0.5, 0.0);

    //设置颜色属性.
    color->AddRGBPoint(m_Point[0], m_Red[0], m_Green[0], m_Blue[0], 0.5, 0.0);
    color->AddRGBPoint(m_Point[1], m_Red[1], m_Green[1], m_Blue[1], 0.49, .61);
    color->AddRGBPoint(m_Point[2], m_Red[2], m_Green[2], m_Blue[2], .5, 0.0);
    color->AddRGBPoint(m_Point[3], m_Red[3], m_Green[3], m_Blue[3], .5, 0.0);

    m_volumeProperty->SetScalarOpacity(compositeOpacity);
    m_volumeProperty->SetColor(color);

    m_volume->SetProperty(m_volumeProperty);

    m_item->renderer()->AddVolume(m_volume);
    m_item->renderer()->ResetCamera();
    m_item->renderer()->SetBackground(0, 0, 0);
    m_item->renderer()->SetViewport(0, 0, 0.5, 1);
}

void RGBAchange::setAchange(QPointF OldPoint, QPointF NewPoint)
{
    if(!m_volumeProperty)
    {
        qDebug()<<"错误";
        return;
    }
    if(!m_item)
    {
        qDebug()<<"错误";
        return;
    }
    if(!m_volume)
    {
        qDebug()<<"错误";
        return;
    }

    compositeOpacity = m_volumeProperty->GetScalarOpacity();
    color = m_volumeProperty->GetRGBTransferFunction();

    compositeOpacity->RemoveAllPoints();
    color->RemoveAllPoints();

    QList<double>::iterator it_m_color = m_Alpha.begin();

    int num = 0;
    for(; it_m_color != m_Alpha.end(); ++it_m_color)
    {
        if(*it_m_color == OldPoint.y())
        {
            break;
        }
        num++;
    }

    switch(num)
    {
        case 0:{
            m_Point[0] = NewPoint.x();
            m_Alpha[0] = NewPoint.y();
            break;
        }
        case 1:{
            m_Point[1] = NewPoint.x();
            m_Alpha[1] = NewPoint.y();
            break;
        }
        case 2:{
            m_Point[2] = NewPoint.x();
            m_Alpha[2] = NewPoint.y();
            break;
        }
        case 3:{
            m_Point[3] = NewPoint.x();
            m_Alpha[3] = NewPoint.y();
            break;
        }
    }

    //设置不透明度
    compositeOpacity->AddPoint(m_Point[0], m_Alpha[0], 0.5, 0.0);
    compositeOpacity->AddPoint(m_Point[1], m_Alpha[1], 0.49, .61);
    compositeOpacity->AddPoint(m_Point[2], m_Alpha[2], .5, 0.0);
    compositeOpacity->AddPoint(m_Point[3], m_Alpha[3], 0.5, 0.0);

    //设置颜色属性.
    color->AddRGBPoint(m_Point[0], m_Red[0], m_Green[0], m_Blue[0], 0.5, 0.0);
    color->AddRGBPoint(m_Point[1], m_Red[1], m_Green[1], m_Blue[1], 0.49, .61);
    color->AddRGBPoint(m_Point[2], m_Red[2], m_Green[2], m_Blue[2], .5, 0.0);
    color->AddRGBPoint(m_Point[3], m_Red[3], m_Green[3], m_Blue[3], .5, 0.0);

    m_volumeProperty->SetScalarOpacity(compositeOpacity);
    m_volumeProperty->SetColor(color);

    m_volume->SetProperty(m_volumeProperty);

    m_item->renderer()->AddVolume(m_volume);
    m_item->renderer()->ResetCamera();
    m_item->renderer()->SetBackground(0, 0, 0);
    m_item->renderer()->SetViewport(0, 0, 0.5, 1);
}
