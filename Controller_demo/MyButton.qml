import QtQuick

import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle
{
    id:root
    width:50
    height:50
    radius:6
    property alias text:rect_text.text
    property alias tip_text:btn_tip.text
    property alias  images: image.source
    color: rect_mouse.pressed ? "#01968c" : (rect_mouse.containsMouse ? "#20c9b3" : "#00beac")
    signal myclicked
    Image {
       id: image
       anchors.centerIn: parent
       width: parent.width-10
       height: parent.width-10
       fillMode: Image.PreserveAspectCrop
       anchors.horizontalCenter:parent.horizontalCenter
       anchors.verticalCenter: parent.verticalCenter
       anchors.verticalCenterOffset: 0
    }
        Text
        {
            id:rect_text
            font.pointSize: 16
            font.bold: true
            color:"#ffffff"
            anchors.horizontalCenter:parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 0
        }
    ToolTip
    {
        id:btn_tip
        font.pointSize: 14
        delay: 500
        timeout: 2000
        x:parent.width/2
        y:parent.height
    }

    MouseArea
    {
        id:rect_mouse
        anchors.fill: parent
        hoverEnabled: true //是否处理悬浮事件，默认false，只有按下鼠标键时才处理鼠标事件，为true时即使没有按下鼠标键也会作相应的处理
        preventStealing:true//默认为false，为true时可以防止当前鼠标事件被其它对象拦截。
        propagateComposedEvents:true//默认为 false，当设置为 true 时，就可以将事件传递给重叠的其他鼠标区域了
        enabled: true
        cursorShape: Qt.PointingHandCursor

        onPressed:
        {
            image.anchors.verticalCenterOffset = 5
        }

        onEntered:
        {
            if(btn_tip.text != null)
                btn_tip.open()
        }

        onReleased:
        {
            if(rect_mouse.containsMouse)//鼠标在按钮范围才有效
                root.myclicked()

            image.anchors.verticalCenterOffset = 0
        }

        onExited://鼠标离开时关闭
        {
            btn_tip.close()
        }
    }
}
