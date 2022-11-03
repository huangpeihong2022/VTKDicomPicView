import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.2
import QtQuick.Controls
import QtQuick.Dialogs
import OpenDcm
import QQuickVTKRenderWindow 1.0
import QQuickVTKRenderItem 1.0
import QtCharts

ApplicationWindow {
    id: root
//    width: 1000
//    height: 800
    visibility:"Maximized"
    visible: true
    title: qsTr("DICOM图像浏览")

    OpenDcm {
        id: opendcm
    }

    DropArea {
        anchors.fill: parent
      //  onEntered: console.log("entered")
        onDropped: function(drop){
            opendcm.setParam(rgbachange);

            if(drop.hasUrls){
                for(var i = 0; i < drop.urls.length; i++){
                    var flag = opendcm.droview(_coneView, drop.urls[i]);
                    check(flag);
                }
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons:Qt.LeftButton;
        propagateComposedEvents: true
        onReleased: parent.Drag.drop()
    }

    Column {
        ToolBar {
            id : toolbar1
            height: 25
            width: root.width
            Row{
                ToolButton {
                    text: qsTr("文件(F)")
                    //onClicked:
                }
                ToolButton {
                    text: qsTr("图像(I)")
                    //onClicked:
                }
                ToolButton {
                    text: qsTr("工具栏(T)")
                    //onClicked:
                }
                ToolButton{
                    text: qsTr("系统(s)")
                    //onClicked:
                }
            }
        }
        ToolBar {
            id: toolbar2
            width: root.width
            height: 50
            Row{
                ToolButton{
                    width: 75
                    height:toolbar2.height
                    ToolButton {
                            width: 60
                            id: filebutton
                            height:toolbar2.height
                            icon.source: "/res/file.png"
                            icon.color: "transparent"
                            display: AbstractButton.TextUnderIcon
                            text: qsTr("打开文件")
                            onClicked: {
                                var flag = opendcm.viewDcmDir(_coneView,rgbachange);
                                check(flag);
                            }
                    }
                    ToolButton {
                            x:filebutton.x+filebutton.width
                            width: 20
                            height:toolbar2.height
                            icon.source: "/res/downarrow.png"
                            icon.color: "transparent"
                            onClicked: filemenu.open()
                    }
                }

                ToolSeparator {
                    contentItem: Rectangle {  //设置颜色一定要配置大小，不然默认是最小的显示不出来
                        implicitWidth: 1
                        implicitHeight: toolbar2.height-6
                        color: "gray"
                    }
                }

                ToolButton{
                    width: 75
                    height:toolbar2.height
                    ToolButton {
                        width: 60
                        id: saveasbutton
                        height:toolbar2.height
                        icon.source: "/res/saveas.png"
                        icon.color: "transparent"
                        display: AbstractButton.TextUnderIcon
                        text: qsTr("另存图像")
                        //onClicked:
                    }
                    ToolButton {
                            x:saveasbutton.x+saveasbutton.width
                            width: 20
                            height:toolbar2.height
                            icon.source: "/res/downarrow.png"
                            icon.color: "transparent"
                            onClicked: saveasmenu.open()
                    }
                }

                ToolSeparator {
                    contentItem: Rectangle {  //设置颜色一定要配置大小，不然默认是最小的显示不出来
                        implicitWidth: 1
                        implicitHeight: toolbar2.height-6
                        color: "gray"
                    }
                }

                ToolButton {
                    height:toolbar2.height
                    icon.source: "/res/tile.png"
                    icon.color: "transparent"
                    display: AbstractButton.TextUnderIcon
                    text: qsTr("平铺图像")
                    //onClicked:
                }

                ToolSeparator {
                    contentItem: Rectangle {  //设置颜色一定要配置大小，不然默认是最小的显示不出来
                        implicitWidth: 1
                        implicitHeight: toolbar2.height-6
                        color: "gray"
                    }
                }

                ToolButton{
                    height:toolbar2.height
                    icon.source: "/res/auto.png"
                    icon.color: "transparent"
                    display: AbstractButton.TextUnderIcon
                    text: qsTr("自动调窗")
                    //onClicked:
                }
                ToolButton{
                    height:toolbar2.height
                    icon.source: "/res/adjust.png"
                    icon.color: "transparent"
                    display: AbstractButton.TextUnderIcon
                    text: qsTr("调窗工具")
                    //onClicked:
                }

                ToolSeparator {
                    contentItem: Rectangle {  //设置颜色一定要配置大小，不然默认是最小的显示不出来
                        implicitWidth: 1
                        implicitHeight: toolbar2.height-6
                        color: "gray"
                    }
                }

                ToolButton{
                    height:toolbar2.height
                    icon.source: "/res/roam.png"
                    icon.color: "transparent"
                    display: AbstractButton.TextUnderIcon
                    text: qsTr("图像漫游")
                    //onClicked:
                }

                ToolSeparator {
                    contentItem: Rectangle {  //设置颜色一定要配置大小，不然默认是最小的显示不出来
                        implicitWidth: 1
                        implicitHeight: toolbar2.height-6
                        color: "gray"
                    }
                }

                ToolButton{
                    height:toolbar2.height
                    icon.source: "/res/loupe.png"
                    icon.color: "transparent"
                    display: AbstractButton.TextUnderIcon
                    text: qsTr("图像缩放")
                    //onClicked:
                }

                ToolButton{
                    height:toolbar2.height
                    icon.source: "/res/zoom.png"
                    icon.color: "transparent"
                    display: AbstractButton.TextUnderIcon
                    text: qsTr("放大镜")
                    //onClicked:
                }

                ToolSeparator {
                    contentItem: Rectangle {  //设置颜色一定要配置大小，不然默认是最小的显示不出来
                        implicitWidth: 1
                        implicitHeight: toolbar2.height-6
                        color: "gray"
                    }
                }

                ToolButton{
                    height:toolbar2.height
                    icon.source: "/res/picture.png"
                    icon.color: "transparent"
                    display: AbstractButton.TextUnderIcon
                    text: qsTr("选择图像")
                    //onClicked:
                }

                ToolSeparator {
                    contentItem: Rectangle {  //设置颜色一定要配置大小，不然默认是最小的显示不出来
                        implicitWidth: 1
                        implicitHeight: toolbar2.height-6
                        color: "gray"
                    }
                }

                ToolButton{
                    id: dbutton
                    height:toolbar2.height
                    icon.source: "/res/3d.png"
                    icon.color: "transparent"
                    display: AbstractButton.TextUnderIcon
                    text: qsTr("切片转换")
                    objectName: "changebutton"
                    onClicked:{
                        slicemenu.open();
                    }
                }
            }
        }
    }

    QQuickVTKRenderWindow {
        id: vtkwindow
        x: 0
        y: toolbar1.height+toolbar2.height
        width: root.width
        height: root.height-toolbar1.height-toolbar2.height
    }

    // add one or more vtk render items
    QQuickVTKRenderItem {
        id: _coneView
        objectName: "ConeView"
        x: 0
        y: toolbar1.height+toolbar2.height
        width: root.width/2-20
        height: root.height-toolbar1.height-toolbar2.height

        renderWindow: vtkwindow
    }

    RChartView {
        id: rchart
        x: root.width/2+20
        y: toolbar1.height+toolbar2.height+10
        width: root.width/2-20
        height: (root.height-toolbar1.height-toolbar2.height)/4-20
        visible: false
    }

    GChartView{
        id: gchart
        x: root.width/2+20
        y: toolbar1.height+toolbar2.height+rchart.height+30
        width: root.width/2-20
        height: (root.height-toolbar1.height-toolbar2.height)/4-20
        antialiasing: true
        theme:ChartView.ChartThemeBlueNcs
        visible: false
    }

    BChartView{
        id: bchart
        x: root.width/2+20
        y: toolbar1.height+toolbar2.height+rchart.height+gchart.height+50
        width: root.width/2-20
        height: (root.height-toolbar1.height-toolbar2.height)/4-20
        antialiasing: true
        theme:ChartView.ChartThemeBlueNcs
        visible: false
    }

    AChartView{
        id: achart
        x: root.width/2+20
        y: toolbar1.height+toolbar2.height+rchart.height+gchart.height+bchart.height+70
        width: root.width/2-20
        height: (root.height-toolbar1.height-toolbar2.height)/4-20
        antialiasing: true
        theme:ChartView.ChartThemeBlueNcs
        visible: false
    }

    Menu {
        id: filemenu
        x: filebutton.x;
        y: toolbar2.height+toolbar1.height;
        MenuItem {
            text: "新建窗口"
            onClicked: { console.log("新建窗口") }
        }
        MenuItem {
            text: "打开单个文件"
            onClicked: {
                var flag = opendcm.viewDcmFile(_coneView);
                check(flag);
            }
        }
        MenuItem {
            text: "打开dicom文件夹"
            onClicked: {
                var flag = opendcm.viewDcmDir(_coneView, rgbachange);
                check(flag);
            }
        }
    }
    Menu {
        id: saveasmenu
        x: filebutton.x+80;
        y: saveasbutton.y+toolbar2.height+toolbar1.height;
        MenuItem  {
            text: "保存图像"
            onClicked: { console.log("保存图像") }
        }
        MenuItem  {
            text: "另存为..."
            onClicked: { console.log("另存为...") }
        }
    }

    Menu {
        id: slicemenu
        x: dbutton.x;
        y: saveasbutton.y+toolbar2.height+toolbar1.height;
        MenuItem  {
            text: "轴切片"
            onClicked: { opendcm.sliceView(1); }
        }
        MenuItem  {
            text: "冠切片"
            onClicked: { opendcm.sliceView(2); }
        }
        MenuItem  {
            text: "矢切片"
            onClicked: { opendcm.sliceView(3); }
        }
    }

    function check(flag){
        if(flag === 0)
        {
            return;
        }
        else if(flag === 1)
        {
            rchart.visible = true;
            gchart.visible = true;
            bchart.visible = true;
            achart.visible = true;
            _coneView.width = root.width/2-20;
        }
        else if(flag === 2)
        {
            rchart.visible = false;
            gchart.visible = false;
            bchart.visible = false;
            achart.visible = false;
            _coneView.width = root.width;
        }
        else
        {
            return;
        }
    }
}
