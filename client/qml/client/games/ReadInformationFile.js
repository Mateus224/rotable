var string
function readFile(file) {
    var request = new XMLHttpRequest()
    request.open("GET", "test.txt")
    request.onreadystatechange = function(event) {
        if (request.readyState === XMLHttpRequest.DONE) {
            string= request.responseText
            console.log(string)
        }
    }
    request.send()


}
