
//----------------------------------------------------------
var sCard
var icard=100
var icard_lastCard
var sCard_lastCard
var playedCards =[]
var Kings=[]
var j=0
function nextCard(){
    icard_lastCard=icard
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
        if(icard===21||icard===22||icard===23||icard===24)
        {
            if(Kings.length===3)
            {
                console.log("Verloren :-D")
                playedCards=[]
            }
            else{
                Kings.push(icard)
            }
        }
    }

    playedCards.push(icard)
    sCard=icard.toString()
    sCard_lastCard=icard_lastCard.toString()
    console.log("j:"+j+" mod2:"+j%2)
    if(j===0)
    {
        console.log("0lastCard: "+sCard_lastCard+ "this Card: "+sCard)
        imagefront.source="qrc:/client/games/BigKingsCup/Bilder/"+sCard+".png";
        imageBack.source="qrc:/client/games/BigKingsCup/Bilder/"+sCard+".png";
    }
    else if(j%2)
    {
        console.log("1lastCard: "+sCard_lastCard+ "this Card: "+sCard)
        imagefront.source="qrc:/client/games/BigKingsCup/Bilder/"+sCard+".png";
        imageBack.source="qrc:/client/games/BigKingsCup/Bilder/"+sCard_lastCard+".png";
    }else if(!(j%2))
    {
        console.log("2lastCard: "+sCard_lastCard+ "this Card: "+sCard)
        imagefront.source="qrc:/client/games/BigKingsCup/Bilder/"+sCard_lastCard+".png";
        imageBack.source="qrc:/client/games/BigKingsCup/Bilder/"+sCard+".png";
    }

    j++
}
//----------------------------------------------------------
