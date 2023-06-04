import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
ApplicationWindow {
    visible: true
    Connections {
        target: controlled
        function onFlagChanged(){
            if(controlled.flag)
                text.text="Wait for the connection"
            else
                text.text="The connection was successful"
        }
    }
    Text {
        id: text
        text:"Wait for the connection"
        anchors.centerIn: parent
    }
}
