import QtQuick 2.12
import QtQuick.Controls 2.5

//window containing the application
ApplicationWindow {

    visible: true

    //title of the application
    title: qsTr("Hello World")
    width: 640
    height: 480

    Rectangle {
        width: 200
        height: 100
        color: "red"

        Text {
            anchors.centerIn: parent
            text: "Hello, World!"
        }
        //handle clicked input.
        TapHandler {
            onTapped: parent.color = "blue"
        }
        // handle keyboard input
        focus: true
        Keys.onPressed: {
            if (event.key == Qt.Key_Return) {
                color = "Yellow";
                event.accepted = true;
            }
        }
    }
}