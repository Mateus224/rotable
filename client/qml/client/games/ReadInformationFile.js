var string= "test"
function readFile(file) {
    var request = new XMLHttpRequest()
    request.open("GET", file)
    request.onreadystatechange = function(event) {
        if (request.readyState === XMLHttpRequest.DONE) {
            string= request.responseText
            console.log(string)
        }
    }
    request.send()


}
