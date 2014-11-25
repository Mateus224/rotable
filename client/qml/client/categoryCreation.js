function createCategory(parent_item, category) {
    var component = Qt.createComponent("ProductCategoryPage.qml");
    var productComponent = Qt.createComponent("ProductButton.qml");

    var object = component.createObject(parent_item,
                                        {"title": category["name"],
                                            "icon": category["icon"]});

    var productsarr = []
    for (var i = 0; i < category["products"].length; ++i) {
        //console.log(category["name"] + ": " + category["products"][i]["name"]);
        var productObject = productComponent.createObject(object,
                                                          {"name": category["products"][i]["name"],
                                                              "info": category["products"][i]["info"],
                                                              "price": category["products"][i]["price"],
                                                              "priceStr": category["products"][i]["priceStr"]});

        productsarr.push(productObject);
    }
    object.content = productsarr;

    if (object === null) {
        // Error Handling
        console.log("Error creating object");
    }

    return object;
}
