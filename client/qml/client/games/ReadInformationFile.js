var string= ""
function readFile(file) {
    var request = new XMLHttpRequest()
    request.open("GET", file)
    request.onreadystatechange = function(event) {
        if (request.readyState === XMLHttpRequest.DONE) {
            string= request.responseText
            ruleInformationTxt.sInfotext=string
            ruleInformationTxt.sLastInfotext=string
        }
    }
    request.send()


}
