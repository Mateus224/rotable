var component;
var sprite;
var count_table_objects=0



function createSpriteObjects() {
    console.log("test");
    component = Qt.createComponent("Sprite.qml");

    if (component.status == Component.Ready)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation() {
    if (component.status == Component.Ready) {
        sprite = component.createObject(appWindow, {"x": count_table_objects+10, "y": count_table_objects*100});
        if (sprite == null) {
            // Error Handling
            console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }

    count_table_objects++
}
