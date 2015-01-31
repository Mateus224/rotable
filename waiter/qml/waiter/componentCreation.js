var component;
var sprite;


function consolee() {
     console.log("test");
}


function initialize()
{
    centerX = dialer.x + dialer.width / 2;
    centerY = dialer.y + dialer.height / 2;
}

function createSpriteObjects() {

    component = Qt.createComponent("Sprite.qml");

    if (component.status == Component.Ready)
        finishCreation();
    else
        component.statusChanged.connect(finishCreation);
}

function finishCreation() {
    if (component.status == Component.Ready) {
        sprite = component.createObject(appWindow, {"x": 100, "y": 100});
        if (sprite == null) {
            // Error Handling
            console.log("Error creating object");
        }
    } else if (component.status == Component.Error) {
        // Error Handling
        console.log("Error loading component:", component.errorString());
    }
}
