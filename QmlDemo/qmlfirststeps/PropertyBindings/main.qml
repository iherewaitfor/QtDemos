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
		width: 400
		height: 200

		Rectangle {
			width: parent.width / 2
			height: parent.height
			color: "blue"
		}

		Rectangle {
			width: parent.width / 2
			height: parent.height
			x: parent.width / 2
			color: "green"
		}
	}
}