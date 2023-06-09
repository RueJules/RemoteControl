import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
ApplicationWindow{
    id:root
    width: 800
    height: 480
    visible:true

    property bool calflag: controller.cflag && controller.sflag
    onCalflagChanged:{
        if(calflag==true){
            call.tip_text="This button controls the voice"
            call.images="qrc:/images/call.png"
        }
        else{
            call.tip_text="This button discontrols the voice"
            call.images="qrc:/images/hangUp.png"
        }
    }
    MyButton{
        id:con
        tip_text: "This controls the connected button"
        onMyclicked: {
            if(controller.flag)

                dialog.open();

            else {
                controller.finish()
            }
        }
        anchors.top:image.bottom
        anchors.left: image.left
        images:"qrc:/images/heart.png"
    }
    MyButton{
        id:call
        tip_text: "This button controls the voice"
        onMyclicked: {
            if(!controller.flag){
                if(calflag){
                    controller.communication(dialog.ip)
                }else{
                   controller.discommunication();
                }
            }
        }
        anchors.top:image.bottom
        anchors.right:image.right
        images:"qrc:/images/call.png"
    }


    Connections {
        target: controller
        function onFlagChanged(){
            if(controller.flag){
                con.tip_text= "This controls the connected button"
                con.images="qrc:/images/heart.png"
                controllerArea.enabled=false;
                controllerArea.hoverEnabled=false;
                image.source="qrc:/images/background.jpg"
            }else{
                con.tip_text= "This discontrols the connected button"
                con.images="qrc:/images/heartbreak.png"
                controllerArea.enabled=true;
                controllerArea.hoverEnabled=true;
            }

        }
        function onCflagChanged(){
            calflag=controller.cflag && controller.sflag
        }
        function onSflagChanged(){
            calflag=controller.cflag && controller.sflag
        }
    }
    Dialog{
        id: dialog
        property alias ip: inputip.text
        title: qsTr("Connect")
        width: (ok.width+cancel.width)*1.5
        height: (ok.width+cancel.width)*1
        anchors.centerIn: parent
        onAccepted: {
            controller.requestNewConnection(ip)
        }
        onRejected: {
            controller.finish()
        }
        TextInput{
            id:inputip
            focus: true
            text:"10.252.132.39"
            visible: true
            width: 250
            horizontalAlignment: Text.AlignHCenter//水平居中
            anchors.centerIn: parent
            height: con.height
        }
        MyButton{
           id:ok
            width: 90
            height: 25
            text: "ok"

            anchors.top: inputip.bottom
            anchors.left: inputip.left
            onMyclicked: {
                dialog.accept()
            }
        }
        MyButton{
            id:cancel
            width: 90
            height: 25
            text:"cancel"
            anchors.top: inputip.bottom
            anchors.right: inputip.right
            onMyclicked: {
                dialog.reject()
            }
        }
    }
    Image {
        id: image
        width: parent.width
        height: parent.height-con.height
        sourceSize: Qt.size(image.width,image.height)
        cache: false//指定是否应缓存图像。默认值为true。在处理大型图像时，将缓存设置为false非常有用，以确保它们不会以牺牲小型“ui元素”图像为代价进行缓存
        source:"qrc:/images/background.jpg"
        Connections {
            target: controller
            function onNeedUpdate() {
                image.source = "image://screen/" + Date.now();
            }
        }
    }
    MouseArea {
        //鼠标区域
        id: controllerArea

        hoverEnabled:false
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        width: parent.width
        height: parent.height-con.height
        onEntered: {
            let ratio = Qt.point(mouseX / root.width, mouseY/ root.height);
            controller.mouseEntered(ratio);
            console.log(ratio)
        }
        onPressed:(event)=> {
            let ratio = Qt.point(mouseX / root.width, mouseY/ root.height);
            if(event.button==Qt.LeftButton)
                controller.leftMousePressed(ratio);
            if(event.button==Qt.RightButton)
                controller.rightMousePressed(ratio);
        }
        onReleased:(event)=> {
            let ratio = Qt.point(mouseX / root.width, mouseY/ root.height);
            if(event.button==Qt.LeftButton)
                controller.leftMouseReleased(ratio);
            if(event.button==Qt.RightButton)
                controller.rightMouseReleased(ratio);
        }

        onPositionChanged: {
            let ratio = Qt.point(mouseX  / root.width, mouseY / root.height);
            controller.mouseMoved(ratio);
        }
    }
    Item{
        //键盘区域
        width: parent.width
        height: parent.height-con.height
        focus:true

        Keys.onPressed :(event)=>{
            event.accept=true
            switch(event.key){
            case Qt.Key_Escape:
                controller.keyPressed(1)
                break;
            case Qt.Key_1:
                controller.keyPressed(2)
                break;
            case Qt.Key_2:
                controller.keyPressed(3)
                break;
            case Qt.Key_3:
                controller.keyPressed(4)
                break;
            case Qt.Key_4:
                controller.keyPressed(5)
                break;
            case Qt.Key_5:
                controller.keyPressed(6)
                break;
            case Qt.Key_6:
                controller.keyPressed(7)
                break;
            case Qt.Key_7:
                controller.keyPressed(8)
                break;
            case Qt.Key_8:
                controller.keyPressed(9)
                break;
            case Qt.Key_9:
                controller.keyPressed(10)
                break;
            case Qt.Key_0:
                controller.keyPressed(11)
                break;
            case Qt.Key_Minus:
                controller.keyPressed(12)
                break;
            case Qt.Key_Equal:
                controller.keyPressed(13)
                break;
            case Qt.Key_Backspace:
                controller.keyPressed(14)
                break;
            case Qt.Key_Tab:
                controller.keyPressed(15)
                break;
            case Qt.Key_Q:
                controller.keyPressed(16)
                break;
            case Qt.Key_W:
                controller.keyPressed(17)
                break;
            case Qt.Key_E:
                controller.keyPressed(18)
                break;
            case Qt.Key_R:
                controller.keyPressed(19)
                break;
            case Qt.Key_T:
                controller.keyPressed(20)
                break;
            case Qt.Key_Y:
                controller.keyPressed(21)
                break;
            case Qt.Key_U:
                controller.keyPressed(22)
                break;
            case Qt.Key_I:
                controller.keyPressed(23)
                break;
            case Qt.Key_O:
                controller.keyPressed(24)
                break;
            case Qt.Key_P:
                controller.keyPressed(25)
                break;
            case Qt.Key_BraceLeft:
                controller.keyPressed(26)
                break;
            case Qt.Key_BraceRight:
                controller.keyPressed(27)
                break;
            case Qt.Key_Enter:
                controller.keyPressed(28)
                break;
            case Qt.Key_Return:
                controller.keyPressed(28)
                break;
            case Qt.Key_Control:
                controller.keyPressed(29)
                break;
            case Qt.Key_A:
                controller.keyPressed(30)
                break;
            case Qt.Key_S:
                controller.keyPressed(31)
                break;
            case Qt.Key_D:
                controller.keyPressed(32)
                break;
            case Qt.Key_F:
                controller.keyPressed(33)
                break;
            case Qt.Key_G:
                controller.keyPressed(34)
                break;
            case Qt.Key_H:
                controller.keyPressed(35)
                break;
            case Qt.Key_J:
                controller.keyPressed(36)
                break;
            case Qt.Key_K:
                controller.keyPressed(37)
                break;
            case Qt.Key_L:
                controller.keyPressed(38)
                break;
            case Qt.Key_Semicolon:
                controller.keyPressed(39)
                break;
            case Qt.Key_Apostrophe:
                controller.keyPressed(40)
                break;
            case Qt.Key_QuoteLeft:
                controller.keyPressed(41)
                break;
            case Qt.Key_AsciiTilde:
                controller.keyPressed(41)
                break;
            case Qt.Key_Shift:
                controller.keyPressed(42)
                break;
            case Qt.Key_Backslash:
                controller.keyPressed(43)
                break;
            case Qt.Key_Z:
                controller.keyPressed(44)
                break;
            case Qt.Key_X:
                controller.keyPressed(45)
                break;
            case Qt.Key_C:
                controller.keyPressed(46)
                break;
            case Qt.Key_V:
                controller.keyPressed(47)
                break;
            case Qt.Key_B:
                controller.keyPressed(48)
                break;
            case Qt.Key_N:
                controller.keyPressed(49)
                break;
            case Qt.Key_M:
                controller.keyPressed(50)
                break;
            case Qt.Key_Comma:
                controller.keyPressed(51)
                break;
            case Qt.Key_Period:
                controller.keyPressed(52)
                break;
            case Qt.Key_Slash:
                controller.keyPressed(53)
                break;
            case Qt.Key_CapsLock:
                controller.keyPressed(58)
                break;
            case Qt.Key_SysReq://prtsc是截图键吗
                controller.keyPressed(99)//不确定linux下对应的是不是
                break;
            case Qt.Key_AsciiCircum:
                controller.keyPressed(111)
                break;
            case Qt.Key_F1:
                controller.keyPressed(59);
                break;
            case Qt.Key_F2:
                controller.keyPressed(60); //Key_COMPOSE
                break;
            case Qt.Key_F3:
                controller.keyPressed(61);
                break;
            case Qt.Key_F4:
                controller.keyPressed(62);
                break;
            case Qt.Key_F5:
                controller.keyPressed(63);
                break;
            case Qt.Key_F6:
                controller.keyPressed(64);
                break;
            case Qt.Key_F7:
                controller.keyPressed(65);
                break;
            case Qt.Key_F8:
                controller.keyPressed(66);
                break;
            case Qt.Key_F9:
                controller.keyPressed(67);
                break;
            case Qt.Key_F10:
                controller.keyPressed(68);
                break;
            case Qt.Key_F11:
                controller.keyPressed(87);
                break;
            case Qt.Key_F12:
                controller.keyPressed(88);
                break;
            case Qt.Key_Delete:
                controller.keyPressed(111);
                break;
            case Qt.Key_Alt:
                controller.keyPressed(56);
                break;
            case Qt.Key_PageUp:
                controller.keyPressed(104);
                break;
            case Qt.Key_PageDown:
                controller.keyPressed(109);
                break;
            case Qt.Key_Space:
                controller.keyPressed(57);
                break;
            case Qt.Key_Left:
                controller.keyPressed(105);
                break;
            case Qt.Key_Right:
                controller.keyPressed(106);
                break;
            case Qt.Key_Home:
                controller.keyPressed(102);
                break;
            case Qt.Key_End:
                controller.keyPressed(107);
                break;
            case Qt.Key_Exclam:
                controller.keyPressed(2);
                break;
            case Qt.Key_At:
                controller.keyPressed(3);
                break;
            case Qt.Key_NumberSign:
                controller.keyPressed(4)
                break;
            case Qt.Key_Dollar:
                controller.keyPressed(5)
                break;
            case Qt.Key_Percent:
                controller.keyPressed(6)
                break;
            case Qt.Key_AsciiCircum:
                controller.keyPressed(7)
                break;
            case Qt.Key_Ampersand:
                controller.keyPressed(8)
                break;
            case Qt.Key_Asterisk:
                controller.keyPressed(9)
                break;
            case Qt.Key_ParenLeft:
                controller.keyPressed(10)
                break;
            case Qt.Key_ParenRight:
                controller.keyPressed(11)
                break;
            case Qt.Key_Undersore:
                controller.keyPressed(12)
                break;
            case Qt.Key_Plus:
                controller.keyPressed(13)
                break;
            case Qt.Key_BracketLeft:
                controller.keyPressed(26)
                break;
            case Qt.Key_BracketRight:
                controller.keyPressed(27)
                break;
            case Qt.Key_Bar:
                 controller.keyPressed(43)
                 break;
            case Qt.Key_Colon:
                controller.keyPressed(39)
                break;
            case Qt.Key_QuoteDbl:
                controller.keyPressed(40)
                break;
            case Qt.Key_Less:
                controller.keyPressed(51)
                break;
            case Qt.Key_Greater:
                controller.keyPressed(52)
                break;
            case Qt.Key_Question:
                controller.keyPressed(53)
                break;
            }
        }
        Keys.onReleased:(event)=>{
            event.accept=true
            switch(event.key){
            case Qt.Key_Escape:
                controller.keyReleased(1)
                break;
            case Qt.Key_1:
                controller.keyReleased(2)
                break;
            case Qt.Key_2:
                controller.keyReleased(3)
                break;
            case Qt.Key_3:
                controller.keyReleased(4)
                break;
            case Qt.Key_4:
                controller.keyReleased(5)
                break;
            case Qt.Key_5:
                controller.keyReleased(6)
                break;
            case Qt.Key_6:
                controller.keyReleased(7)
                break;
            case Qt.Key_7:
                controller.keyReleased(8)
                break;
            case Qt.Key_8:
                controller.keyReleased(9)
                break;
            case Qt.Key_9:
                controller.keyReleased(10)
                break;
            case Qt.Key_0:
                controller.keyReleased(11)
                break;
            case Qt.Key_Minus:
                controller.keyReleased(12)
                break;
            case Qt.Key_Equal:
                controller.keyReleased(13)
                break;
            case Qt.Key_Backspace:
                controller.keyReleased(14)
                break;
            case Qt.Key_Tab:
                controller.keyReleased(15)
                break;
            case Qt.Key_Q:
                controller.keyReleased(16)
                break;
            case Qt.Key_W:
                controller.keyReleased(17)
                break;
            case Qt.Key_E:
                controller.keyReleased(18)
                break;
            case Qt.Key_R:
                controller.keyReleased(19)
                break;
            case Qt.Key_T:
                controller.keyReleased(20)
                break;
            case Qt.Key_Y:
                controller.keyReleased(21)
                break;
            case Qt.Key_U:
                controller.keyReleased(22)
                break;
            case Qt.Key_I:
                controller.keyReleased(23)
                break;
            case Qt.Key_O:
                controller.keyReleased(24)
                break;
            case Qt.Key_P:
                controller.keyReleased(25)
                break;
            case Qt.Key_BraceLeft:
                controller.keyReleased(26)
                break;
            case Qt.Key_BraceRight:
                controller.keyReleased(27)
                break;
            case Qt.Key_Enter:
                controller.keyReleased(28)
                break;
            case Qt.Key_Return:
                controller.keyPressed(28)
                break;
            case Qt.Key_Control:
                controller.keyReleased(29)
                break;
            case Qt.Key_A:
                controller.keyReleased(30)
                break;
            case Qt.Key_S:
                controller.keyReleased(31)
                break;
            case Qt.Key_D:
                controller.keyReleased(32)
                break;
            case Qt.Key_F:
                controller.keyReleased(33)
                break;
            case Qt.Key_G:
                controller.keyReleased(34)
                break;
            case Qt.Key_H:
                controller.keyReleased(35)
                break;
            case Qt.Key_J:
                controller.keyReleased(36)
                break;
            case Qt.Key_K:
                controller.keyReleased(37)
                break;
            case Qt.Key_L:
                controller.keyReleased(38)
                break;
            case Qt.Key_Semicolon:
                controller.keyReleased(39)
                break;
            case Qt.Key_Apostrophe:
                controller.keyReleased(40)
                break;
            case Qt.Key_QuoteLeft:
                controller.keyReleased(41)
                break;
            case Qt.Key_AsciiTilde:
                controller.keyReleased(41)
                break;
            case Qt.Key_Shift:
                controller.keyReleased(42)
                break;
            case Qt.Key_Backslash:
                controller.keyReleased(43)
                break;
            case Qt.Key_Z:
                controller.keyReleased(44)
                break;
            case Qt.Key_X:
                controller.keyReleased(45)
                break;
            case Qt.Key_C:
                controller.keyReleased(46)
                break;
            case Qt.Key_V:
                controller.keyReleased(47)
                break;
            case Qt.Key_B:
                controller.keyReleased(48)
                break;
            case Qt.Key_N:
                controller.keyReleased(49)
                break;
            case Qt.Key_M:
                controller.keyReleased(50)
                break;
            case Qt.Key_Comma:
                controller.keyReleased(51)
                break;
            case Qt.Key_Period:
                controller.keyReleased(52)
                break;
            case Qt.Key_Slash:
                controller.keyReleased(53)
                break;
            case Qt.Key_CapsLock:
                controller.keyReleased(58)
                break;
            case Qt.Key_SysReq://prtsc是截图键吗
                controller.keyReleased(99)//不确定linux下对应的是不是
                break;
            case Qt.Key_AsciiCircum:
                controller.keyReleased(111)
                break;
            case Qt.Key_F1:
                controller.keyReleased(59);
                break;
            case Qt.Key_F2:
                controller.keyReleased(60); //Key_COMPOSE
                break;
            case Qt.Key_F3:
                controller.keyReleased(61);
                break;
            case Qt.Key_F4:
                controller.keyReleased(62);
                break;
            case Qt.Key_F5:
                controller.keyReleased(63);
                break;
            case Qt.Key_F6:
                controller.keyReleased(64);
                break;
            case Qt.Key_F7:
                controller.keyReleased(65);
                break;
            case Qt.Key_F8:
                controller.keyReleased(66);
                break;
            case Qt.Key_F9:
                controller.keyReleased(67);
                break;
            case Qt.Key_F10:
                controller.keyReleased(68);
                break;
            case Qt.Key_F11:
                controller.keyReleased(87);
                break;
            case Qt.Key_F12:
                controller.keyReleased(88);
                break;
            case Qt.Key_Delete:
                controller.keyReleased(111);
                break;
            case Qt.Key_Alt:
                controller.keyReleased(56);
                break;
            case Qt.Key_PageUp:
                controller.keyReleased(104);
                break;
            case Qt.Key_PageDown:
                controller.keyReleased(109);
                break;
            case Qt.Key_Space:
                controller.keyReleased(57);
                break;
            case Qt.Key_Left:
                controller.keyReleased(105);
                break;
            case Qt.Key_Right:
                controller.keyReleased(106);
                break;
            case Qt.Key_Home:
                controller.keyReleased(102);
                break;
            case Qt.Key_End:
                controller.keyReleased(107);
                break;
            case Qt.Key_Exclam:
                controller.keyReleased(2);
                break;
            case Qt.Key_At:
                controller.keyReleased(3);
                break;
            case Qt.Key_NumberSign:
                controller.keyReleased(4)
                break;
            case Qt.Key_Dollar:
                controller.keyReleased(5)
                break;
            case Qt.Key_Percent:
                controller.keyReleased(6)
                break;
            case Qt.Key_AsciiCircum:
                controller.keyReleased(7)
                break;
            case Qt.Key_Ampersand:
                controller.keyReleased(8)
                break;
            case Qt.Key_Asterisk:
                controller.keyReleased(9)
                break;
            case Qt.Key_ParenLeft:
                controller.keyReleased(10)
                break;
            case Qt.Key_ParenRight:
                controller.keyReleased(11)
                break;
            case Qt.Key_Undersore:
                controller.keyReleased(12)
                break;
            case Qt.Key_Plus:
                controller.keyReleased(13)
                break;
            case Qt.Key_BracketLeft:
                controller.keyReleased(26)
                break;
            case Qt.Key_BracketRight:
                controller.keyReleased(27)
                break;
            case Qt.Key_Bar:
                controller.keyReleased(43)
                break;
            case Qt.Key_Colon:
                controller.keyReleased(39)
                break;
            case Qt.Key_QuoteDbl:
                controller.keyReleased(40)
                break;
            case Qt.Key_Less:
                controller.keyReleased(51)
                break;
            case Qt.Key_Greater:
                controller.keyReleased(52)
                break;
            case Qt.Key_Question:
                controller.keyReleased(53)
                break;
            }
        }
    }

}



