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
		color: "lightgray"
		width: 200
		height: 200

		property int animatedValue: 0
		SequentialAnimation on animatedValue {
			loops: Animation.Infinite
			PropertyAnimation { to: 150; duration: 1000 }
			PropertyAnimation { to: 0; duration: 1000 }
		}

		Text {
			anchors.centerIn: parent
			text: parent.animatedValue
		}
	}
}