# JSON TreeView - Qt6 Application

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

## Overview

**JSON TreeView** is a Qt6 application that reads a JSON file and dynamically constructs a tree data structure. The tree structure is displayed using a QML `TreeView`, allowing users to explore nested JSON data by expanding and collapsing nodes. Users can edit leaf node values and save the modified JSON structure back to a file.

### Features
- Parses and visualizes a JSON file in a tree structure.
- Supports all JSON data types: objects, arrays, strings, numbers, booleans, and null.
- Expand and collapse nodes in the tree.
- Edit and update values of leaf nodes.
- Save the modified JSON structure to a file.
---

## Usage

1. **Loading the JSON File**:
   - The application loads a `sample.json` file by default, which contains nested JSON objects and arrays.

2. **Navigating the Tree**:
   - Click on nodes with the arrow (`▶` for collapsed, `▼` for expanded) to expand or collapse the nodes.

3. **Editing Leaf Node Values**:
   - Click on a leaf node (one without children) to display its value in the text field. Modify the value, then click the **Save** button to apply the changes.

4. **Saving the JSON**:
   - Once you make modifications, click the **Save** button to save the updated JSON structure to a file.

---

## Project Structure

- **`main.cpp`**: Application entry point. Initializes the model and exposes it to QML.
- **`JsonTreeModel.h` / `JsonTreeModel.cpp`**: Implements the tree model (`QAbstractItemModel`) that reads and manages the JSON structure.
- **`JsonTreeItem.h` / `JsonTreeItem.cpp`**: Represents individual tree nodes, managing children and expansion state.
- **`main.qml`**: QML UI file that displays the tree structure and handles user interactions.
- **`sample.json`**: Example JSON file for testing.

---

## Example JSON File

The project uses a sample JSON file with the following structure:

```json
{
    "title": "Sample JSON Tree",
    "version": 1.0,
    "active": true,
    "config": {
        "threshold": 0.75,
        "items": ["item1", "item2", "item3"],
        "options": {
            "option1": null,
            "option2": false,
            "option3": [1, 2, 3, 4]
        }
    },
    "data": [
        {
            "id": "a1",
            "value": "Alpha"
        },
        {
            "id": "b2",
            "value": "Beta"
        }
    ]
}
