
// start angle of a dialer rotation
var startAngle = 0;

// dialer center X
var centerX = null;
// dialer center Y
var centerY = null;

// the dialer stop angle
var dialerStopAngle = Math.PI / 4;
// angle between numbers
var digitAngle = (3 * Math.PI / 2) / 9;

// maximum angle before the finger reaches the dialer stop
var maxAngle;

var thisangle;

var angleDiff=0;

var lastangle=0;

var i=0;

var a=0;

var timecounter=0;

var radius=0;

var AngelChangiging=0;


//////////////////////////
//Dialer Move
//
var Listlist = new Array
//
var AngelChangigingCounter=0;
//
var Clockwise=false
////////////////////////////




function initialize()
{
    centerX = dialer.x + dialer.width / 2;
    centerY = dialer.y + dialer.height / 2;
}
/*
function holeFromAngle(angle)
{
    var hole = Math.round(angle / digitAngle) % 12;

    if(hole < 10)
    {
	return hole;
    }
    else
    {
	return null;
    }
}
*/

function getEventAngle(event)
{
    var angle = Math.atan2(event.y - centerY, event.x - centerX);

    if(angle < 0)
    angle += 2 * Math.PI;

    return angle;
}
function getAngleDiff(angle)
{
    while(angle < startAngle)
	angle += 2 * Math.PI;
    thisangle=angle
    //console.log("diff:",angle - startAngle)
    return (angle - startAngle);
}

function dialerPressed(event)
{

    var newAngle = getEventAngle(event);
    //rotation=angleDiff * 180 / Math.PI
    //var hole = holeFromAngle(2 * Math.PI - newAngle);

    // check the angle corresponds to a hole
    //if(hole != null)

	// hold the starting angle value
    radius=-event.y+centerY

    startAngle = newAngle;
    console.log("startAngle1",startAngle* 180 / Math.PI)


}

function dialerMoved(event)
{
    root.restartCounter()
    if(startAngle != null)
    {

        var newAngle = getEventAngle(event);
        angleDiff = getAngleDiff(newAngle);


    //var currentTime = new Date().getTime();
    //console.log("angleDiff:",angleDiff,"time:",currentTime-root.startTime)

    /*
      nach der ersten bewegung der musarea probleme
      das erste bild wird da kurz gezeigt wo die flasche aufgehört hat zu drehen bei letzter runde
      */

        rotation=(angleDiff * 180 / Math.PI)+lastangle


     //console.log("rotation   0:",((angleDiff * 180 / Math.PI)+lastangle)%360)
     //console.log("angleDiff   0:",angleDiff * 180 / Math.PI)
     //console.log("lastangle   0:",lastangle)

        lastangle =(angleDiff * 180 / Math.PI)+lastangle
        timeChanged()
        if(AngelChangiging>180)
        {
            AngelChangiging=360-AngelChangiging
            Clockwise=true
        }
        else
            Clockwise=false

        Listlist[AngelChangigingCounter]=AngelChangiging


        console.log(Listlist[AngelChangigingCounter])
        AngelChangigingCounter++

    }


}







function dialerReleased(event)
{
    AngelChangigingCounter=0
    if(startAngle != null)
    {
    var angleDiff = getAngleDiff(getEventAngle(event));
    console.log("start",startAngle)
    //var hole = holeFromAngle(Math.min(angleDiff, maxAngle) - dialerStopAngle);


        var runden=20;
        var geschwindigkeit=3
//TODO: Durchschnittsbildung der letzten 5 angleDiff und abfangen wenn =0
    i+=1
    rotation= ((200*runden)/geschwindigkeit)+lastangle
     console.log("angleDiff:", angleDiff * 180 / Math.PI)

    if(i==2)
    rotaryReleaseAnimation.direction= RotationAnimation.Counterclockwise;
     else
    rotaryReleaseAnimation.direction= RotationAnimation.Clockwise;
    rotaryReleaseAnimation.duration=(10*angleDiff*runden)*geschwindigkeit

    //hier wird die Flasche zurückgelegt auf den Punkt wo man loslässt
    //lastangle darf nicht in betracht gezogen werden da rotation schon aufgerufen worderen ist
    //und rotaryReleaseAnimation.from sich auf den Winkel von der bottleArea sich bezieht
    rotaryReleaseAnimation.from=-((200*runden)/geschwindigkeit)
    rotaryReleaseAnimation.to =0// die Flasche muss wieder auf der bottleArea "landen"
    rotaryReleaseAnimation.running = true

    lastangle=((200*runden)/geschwindigkeit)+lastangle // wichtig für die ausgangsposition des nächsten drehens


    }
}








function timeChanged()  {
    if(root.startTime==0)
    {
        root.startTime = new Date().getTime(); //returns the number of milliseconds since the epoch (1970-01-01T00:00:00Z);
    }
    var currentTime = new Date().getTime();
    var timeDiff=(currentTime-root.startTime)/50;
    root.secondsElapsed = timeDiff;
    var GradangleDiff=angleDiff * 180 / Math.PI
    if (GradangleDiff>180)
        GradangleDiff=360-GradangleDiff

    AngelChangiging=angleDiff * 180 / Math.PI
    console.log("   1:  ",AngelChangiging )


}







