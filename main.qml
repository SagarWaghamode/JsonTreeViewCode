import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: "JSON TreeView"

    Component.onCompleted: {
        console.log("Application started successfully");
    }

    TreeView {
        id: treeView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: textField.top
        anchors.margins: 10
        clip: true

        model: jsonTreeModel

        selectionModel: ItemSelectionModel {}

        delegate: Item {
            implicitWidth: padding + label.x + label.implicitWidth + padding
            implicitHeight: label.implicitHeight * 1.5

            readonly property real indentation: 20
            readonly property real padding: 5

            required property TreeView treeView
            required property bool isTreeNode
            required property bool hasChildren
            required property int depth
            required property int row
            required property int column
            required property bool current

            property bool expanded: treeView.model.isExpanded(treeView.model.index(row, 0))

            Rectangle {
                id: background
                anchors.fill: parent
                color: current ? palette.highlight : "transparent"
                opacity: row % 2 === 0 ? 0.1 : 0.05
            }

            // Indicator for expandable nodes
            Label {
                id: indicator
                x: padding + (depth * indentation)
                anchors.verticalCenter: parent.verticalCenter
                visible: isTreeNode && hasChildren
                text: expanded ? "▼" : "▶"

            }

            // Display node content
            Label {
                id: label
                x: padding + (isTreeNode ? (depth + 1) * indentation : 0)
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width - padding - x
                clip: true
                text: model.display
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("Leaf node clicked at row:", row);
                    if (!hasChildren) {
                        textField.text = model.display; // Display value in the text field
                        textField.currentRow = row;     // Keep track of the selected row for editing
                    }
                    else
                    {
                        console.log("call to setexpand:", row);
                        treeView.model.setExpanded(treeView.model.index(row, 0), !expanded);
                    }
                }
            }
        }
    }

    // Editable TextField to display selected leaf node value
    TextField {
        id: textField
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: saveButton.top
        anchors.margins: 10
        placeholderText: "Click on a leaf node to edit its value"
        property int currentRow: -1; // Property to track selected row for editing
    }

    // Save button to apply the changes
    Button {
        id: saveButton
        text: "Save"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 10

        onClicked: {
            if (textField.currentRow !== -1) {
                console.log("Saving node at row:", textField.currentRow);
                let index = treeView.model.index(textField.currentRow, 0);
                // Update the model with the edited value from the TextField
                jsonTreeModel.setData(index, textField.text);
                jsonTreeModel.saveToFile();
            }
        }
    }
}
