import QtQuick
import QtQuick.Controls
ApplicationWindow{
    id:root

    width: 800
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
        property int count:0
        onEntered: {
            let ratio = Qt.point(mouseX / root.width, mouseY/ root.height);
            controller.mouseEntered(ratio);//为什么能直接用controller的
            console.log(ratio)
        }
        onPressed: {
            let ratio = Qt.point(mouseX / root.width, mouseY/ root.height);
            controller.mousePressed(ratio);//为什么能直接用controller的
             //console.log(ratio)
        }
        onReleased: {
            let ratio = Qt.point(mouseX/ root.width, mouseY / root.height);
            controller.mouseReleased(ratio);
        }

        onPositionChanged: {
            let ratio = Qt.point(mouseX  / root.width, mouseY / root.height);
            controller.mouseMoved(ratio);
            //console.log(ratio)
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
    Item{
        anchors.fill: parent
        focus:true
        Keys.onPressed: (event)=>{
            event.accept=true
            if(event.key==Qt.Key_K)
                controller.keyPressed(37)
            if(event.key==Qt.Key_C)
                controller.keyPressed(46)
            if(event.key==Qt.Key_Control)
                controller.keyPressed(29)
            console.log("键盘按下")
            console.log(event.key)

        }
        Keys.onReleased: (event)=>{
            event.accept=true
            if(event.key==Qt.Key_K)
                controller.keyReleased(37)
            if(event.key==Qt.Key_C)
                controller.keyReleased(46)
            if(event.key==Qt.Key_Control)
                controller.keyReleased(29)
            //controller.keyReleased(event.key)
            console.log("键盘松开")
        }
    }



}


//https://elixir.bootlin.com/linux/v4.9/source/include/uapi/linux/input-event-codes.h#L74
