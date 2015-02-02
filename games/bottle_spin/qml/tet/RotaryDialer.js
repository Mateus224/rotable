
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

var AngelChangiging=0;


///////////////////////////
//
var queue=[0,0,0,0,0,0,0,0,0,0]
//
var index_queue=0
//
///////////////////////////

function initialize()
{
    centerX = dialer.x + dialer.width / 2;
    centerY = dialer.y + dialer.height / 2;
}


function getEventAngle(event)
{
    var angle = Math.atan2(event.y - centerY, event.x - centerX);

    if(angle < 0)
    angle += 2 * Math.PI;

    return angle;
}

//------------------------------------

function getAngleDiff(angle)
{
    while(angle < startAngle)
	angle += 2 * Math.PI;
    thisangle=angle

    return (angle - startAngle)
}

//---------------------------------------


function dialerPressed(event)
{

    var newAngle = getEventAngle(event);

	// hold the starting angle value
    radius=-event.y+centerY

    startAngle = newAngle;
    console.log("startAngle1",startAngle* 180 / Math.PI)


}


//----------------------------------------------------------
function dialerMoved(event)
{
        var newAngle = getEventAngle(event);
        angleDiff = getAngleDiff(newAngle);

        dialerView.rotation=(angleDiff * 180 / Math.PI)+lastangle


        lastangle =(angleDiff * 180 / Math.PI)+lastangle


        angleDiff=(angleDiff/Math.PI)*180

        if(angleDiff>180)
        {
            angleDiff=angleDiff-360
            console.log("diffangleL",angleDiff)
        }
        else
         console.log("diffangleR",angleDiff)
        moving_average();

}
//---------------------------------------------------------

function moving_average()
{
        if(index_queue==9)
        {
            queue.shift()
            queue[index_queue]=angleDiff
            index_queue=8
        }
        else
            queue[index_queue]=angleDiff

         console.log("queue",queue[0],queue[1],queue[2],queue[3],queue[4],queue[5],queue[6],queue[7],queue[8],queue[9])
        index_queue++
}


//-----------------------------------------------------------
var geschwindigkeit=0

function dialerReleased(event)
{
    var angleDiff = getAngleDiff(getEventAngle(event));
    //console.log("start",startAngle)

    var runden=20;

    geschwindigkeit++
    dialerView.rotation= ((200*runden)/geschwindigkeit)+lastangle
    // console.log("angleDiff:", angleDiff * 180 / Math.PI)


    rotaryReleaseAnimation.direction= RotationAnimation.Clockwise;
    rotaryReleaseAnimation.duration=(10*runden)*geschwindigkeit
    //hier wird die Flasche zurückgelegt auf den Punkt wo man loslässt
    //lastangle darf nicht in betracht gezogen werden da rotation schon aufgerufen worderen ist
    //und rotaryReleaseAnimation.from sich auf den Winkel von der bottleArea sich bezieht
    rotaryReleaseAnimation.from=-((200*runden)/geschwindigkeit)
    rotaryReleaseAnimation.to =0// die Flasche muss wieder auf der bottleArea "landen"
    rotaryReleaseAnimation.running = true
    lastangle=((200*runden)/geschwindigkeit)+lastangle // wichtig für die ausgangsposition des nächsten drehens

}


