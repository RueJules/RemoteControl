import QtQuick
import QtQuick.Controls
ApplicationWindow{
    id:root
    width: 640
    height: 480
    visible: true
    Image {
        id: image
        anchors.fill: parent
        sourceSize: Qt.size(parent.width, parent.height)
        cache: false//指定是否应缓存图像。默认值为true。在处理大型图像时，将缓存设置为false非常有用，以确保它们不会以牺牲小型“ui元素”图像为代价进行缓存。什么意思
        Connections {
            target: controller
            onNeedUpdate: {
                image.source = "image://screen/" + Date.now();
            }
        }
    }
//    TapHandler{
//        onTapped: {
//            let ratio = Qt.point(point.x / root.width,point.y/ root.height);
//            controller.mousePressed(ratio);//为什么能直接用controller的
//        }
//    }
    MouseArea {
        id: controllerArea
        hoverEnabled:true
        anchors.fill: parent
        onEntered: {
            let ratio = Qt.point(mouseX / root.width, mouseY/ root.height);
            controller.mouseEntered(ratio);//为什么能直接用controller的
        }
        onPressed: {
            let ratio = Qt.point(mouseX / root.width, mouseY/ root.height);
            controller.mousePressed(ratio);//为什么能直接用controller的
        }
        onReleased: {
            let ratio = Qt.point(mouseX/ root.width, mouseY / root.height);
            controller.mouseReleased(ratio);
        }

        onPositionChanged: {
            let ratio = Qt.point(mouseX  / root.width, mouseY / root.height);
            controller.mouseMoved(ratio);
        }
        onPressAndHold: {
        }
        onClicked:  {
        }
        onDoubleClicked: {
        }
        onWheel:{

        }
    }

}


