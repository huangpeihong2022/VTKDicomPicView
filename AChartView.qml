import QtQuick 2.0
import QtCharts
//import RGBAchange

ChartView {
    id: rchart
    property var points_X:[-3024,-16,641,3071]
    property var points_Y: [0,0,0.72,0.71]
    property point selectedPointInChart
    antialiasing: true
    theme:ChartView.ChartThemeBlueNcs

    SplineSeries{
        id: spline
    }

    ScatterSeries{
        id: points

        onHovered: function(point){
            var global_position
            global_position = rchart.mapToPosition(point,points)
            selectedHandler.x = global_position.x - selectedHandler.width / 2
            selectedHandler.y = global_position.y - selectedHandler.height / 2
            rchart.selectedPointInChart = point
            //console.log(point)
            selectedHandler.state = "HOVERED"
        }
        Connections {
            target: selectedHandler
            onDataModified: function(newX,newY){
                var newPoint
                newPoint = rchart.mapToValue(Qt.point(newX, newY),points)
                if(newPoint.x>=-3071 && newPoint.x<=3071 && newPoint.y>=0 && newPoint.y<=255)
                {
                    points.replace(rchart.selectedPointInChart.x, rchart.selectedPointInChart.y, newPoint.x, newPoint.y)
                    spline.replace(rchart.selectedPointInChart.x, rchart.selectedPointInChart.y, newPoint.x, newPoint.y)
                    rgbachange.setAchange(rchart.selectedPointInChart, newPoint)
                }
            }
        }
    }

    Item{
        id: selectedHandler;
        width: 15; height:15
        visible: false
        property real xCenter: x+width/2
        property real yCenter: y+height/2
        signal posChange(int xOffset, int yOffset)
        onPosChange: function(xOffset,yOffset){
                x += xOffset;y += yOffset
        }

        signal dataModified(real newX, real newY);
        state: "HIDE"
        states: [
            State{
                name:"HIDE"
                PropertyChanges{target: selectedHandler; opacity:0.8  }
                PropertyChanges{target: selectedHandler; visible:false}
            },
            State {
                name: "HOVERED"
                PropertyChanges {target: selectedHandler; opacity:0.5 }
                PropertyChanges {target: selectedHandler; visible:true}
            },

            State{
                name: "SELECTED"
                PropertyChanges{target: selectedHandler; opacity:0.8 }
                PropertyChanges{target: selectedHandler; visible:true}
            },
            State{
                name: "MODIFING"
                PropertyChanges{target: selectedHandler; opacity:0.9 }
                PropertyChanges{target: selectedHandler; visible:true}
            },
            State{
                name: "MODIFIED"
                PropertyChanges{target: selectedHandler; opacity:1.0 }
                PropertyChanges{target: selectedHandler; visible:true}
            }
        ]
        onStateChanged: {
            if(state === "MODIFIED"){
                dataModified(xCenter,yCenter);
            }
        }
        Rectangle{
            anchors.fill: parent
            color: "red"
            radius: width/2
        }
        MouseArea{
            anchors.fill: parent
            hoverEnabled: true // 必须设置为true 才能接受hover事件

            property int lastX: 0   // mouseX 是当前光标与root中心点的偏移量，在拖动的过程中要保持光标和root中心的偏移量不变
            property int lastY: 0

            onExited: {
                if(selectedHandler.state != "MODIFING"){ // sometimes move too fast
                    selectedHandler.state = "HIDE"
                }
            }

            onPressed: {
                selectPoint(mouseX,mouseY)
            }

            onReleased: {
                if(selectedHandler.state === "MODIFING"){
                    selectedHandler.state = "MODIFIED"
                }
            }

            onPositionChanged: {
                if (selectedHandler.state === "SELECTED" || selectedHandler.state === "MODIFING") {
                    selectedHandler.posChange(mouseX - lastX, mouseY - lastY)
                    if(selectedHandler.state === "SELECTED" ){
                        selectedHandler.state = "MODIFING"
                    }
                }
            }

            function selectPoint(mouseX,mouseY){
                if (selectedHandler.state === "HOVERED" ||  selectedHandler.state === "MODIFIED"){
                    selectedHandler.state = "SELECTED"
                    lastX = mouseX;
                    lastY = mouseY;
                }
            }
        }
    }
    Component.onCompleted:  {
        var index
        for(index = 0;index < points_X.length;index++){
            spline.append(points_X[index],points_Y[index])
            points.append(points_X[index],points_Y[index])
        }
        rchart.axisX().max = 3071
        rchart.axisX().min = -3071
        rchart.axisY().max = 1
        rchart.axisY().min = 0
    }
}
