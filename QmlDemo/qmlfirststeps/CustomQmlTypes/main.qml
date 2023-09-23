import QtQuick 2.12
import QtQuick.Controls 2.5

//window containing the application
ApplicationWindow {

    visible: true

    //title of the application
    title: qsTr("Hello World")
    width: 640
    height: 480

	Column {
		width: 180
		height: 180
		padding: 1.5
		topPadding: 10.0
		bottomPadding: 10.0
		spacing: 5

		MessageLabel{
			width: parent.width - 2
			msgType: "debug"
		}
		MessageLabel {
			width: parent.width - 2
			message: "This is a warning!"
			msgType: "warning"
		}
		MessageLabel {
			width: parent.width - 2
			message: "A critical warning!"
			msgType: "critical"
		}
	}
}