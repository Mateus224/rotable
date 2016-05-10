.import "../ReadInformationFile.js" as ReadInformationFile
//----------------------------------------------------------
var sCard
var icard
var icard_lastCard
var sCard_lastCard
var playedCards =[]
var Kings=[]
var j=0
var sInfo=[]
function nextCard(){
    if(j>0)
        icard_lastCard=icard
    else
        icard_lastCard=Math.floor((Math.random() * 52) + 1)
    icard=Math.floor((Math.random() * 52) + 1)
    if(!(playedCards.length===52))
        {
        for (var i = 0; i < playedCards.length; i++) {
             while(playedCards[i]=== icard)
             {
                 icard=Math.floor((Math.random() * 52) + 1)
                 i=-1
             }
        }
        if(icard===45||icard===46||icard===47||icard===48)
        {
            if(Kings.length===3)
            {
                ruleInformationTxt.state = "HIDDEN"
                gameLost.state="EXPANDED"
                card_mousArea.enabled=false

            }
            else{
                Kings.push(icard)
            }
        }
    }

    playedCards.push(icard)
    sCard=icard.toString()
    sCard_lastCard=icard_lastCard.toString()
    if(j===0)
    {
        imagefront.source="qrc:/client/games/BigKingsCup/pictures/"+sCard+".png";
        imageBack.source="qrc:/client/games/BigKingsCup/pictures/"+sCard+".png";
    }
    else if(j%2)
    {
        imagefront.source="qrc:/client/games/BigKingsCup/pictures/"+sCard+".png";
        imageBack.source="qrc:/client/games/BigKingsCup/pictures/"+sCard_lastCard+".png";
    }else if(!(j%2))
    {
        imagefront.source="qrc:/client/games/BigKingsCup/pictures/"+sCard_lastCard+".png";
        imageBack.source="qrc:/client/games/BigKingsCup/pictures/"+sCard+".png";
    }
    j++
    sInfo[0]=sInfo[1]
    //iCard starts at 1 so we have to sub 1 take the floor.
    sInfo[1]= (Math.floor((icard-1)/4)+2).toString()
    ReadInformationFile.readFile("BigKingsCup/gameInformationFiles/"+sInfo[0]+".txt")
    ruleInformationTxt.state = "HIDDEN"
    if(Kings.length===3)
    {
        ruleInformationTxt.state = "HIDDEN"
        gameLost.state="EXPANDED"
        card_mousArea.enabled=false

    }
    else{
        card_mousArea.enabled=false
        delay(1100, function() {
            card_mousArea.enabled=true;
        })
        expandedInformationWindowTimer.start()
    }
}
//----------------------------------------------------------
//Reset all variables
function newGame(){
    icard=0
    icard_lastCard=0
    sInfo=[]
    playedCards =[]
    Kings=[]
    j=0
    rotation.angle=0
    rotationB.angle=0
    flipable.flipped = false
    flipable_.flipped = false
}
//----------------------------------------------------------
//This timer is need for the mouseArea so that it is not
//possible to often to click on the cards
function delay(delayTime, cb) {
    mouseAreaTimer.interval = delayTime;
    mouseAreaTimer.repeat = false;
    mouseAreaTimer.triggered.connect(cb);
    mouseAreaTimer.start();
}

