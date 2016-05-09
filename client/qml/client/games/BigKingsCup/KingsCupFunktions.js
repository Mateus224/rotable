//----------------------------------------------------------
var sCard
var icard=100
var icard_lastCard
var sCard_lastCard
var playedCards =[]
var Kings=[]
var j=0
var sInfo=[]
var w=1
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
        if(icard===45||icard===46||icard===47||icard===48)
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
    w++
    sInfo[0]=sInfo[1]
    //iCard starts at 1 so we have to sub 1 take the floor.
    sInfo[1]= (Math.floor((icard-1)/4)+2).toString()

    console.log("sInfo:    "+sInfo[0]+" "+sInfo[1])
}
//----------------------------------------------------------
