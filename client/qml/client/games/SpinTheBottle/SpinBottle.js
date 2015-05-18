
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
var queue=[0,0,0,0]
//
var index_queue=0
//
///////////////////////////


var velocity=0


function initialize()
{
    centerX =  (spinBottle.width / 2);
    centerY = (spinBottle.height / 2);
}


function getEventAngle(event)
{
    var angle
    angle = Math.atan2(event.y - centerY, event.x - centerX);
    //console.log("event",event.y,"centerY",centerY)
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
    queue=[0,0,0,0]
    velocity=0

}


//----------------------------------------------------------
function dialerMoved(event)
{
        var newAngle = getEventAngle(event);
        angleDiff = getAngleDiff(newAngle);

        spinBottle.rotation=((angleDiff / Math.PI) * 180)+lastangle


        lastangle =(angleDiff * 180 / Math.PI)+lastangle


        angleDiff=(angleDiff/Math.PI)*180

        if(angleDiff>180)
            angleDiff=angleDiff-360

        var average=moving_average();
        var Angular_velocity=(average/0.05)
        velocity=Angular_velocity*0.007 // meter per sec
}
//---------------------------------------------------------

function moving_average()
{
        if(index_queue==3)
        {
            queue.shift()
            queue[index_queue]=angleDiff
            index_queue=2
        }
        else
            queue[index_queue]=angleDiff

        index_queue++
        var average
        average=(queue[0]+queue[1]+queue[2]+queue[3])/4

        return average;
}


//-----------------------------------------------------------


function dialerReleased(event)
{
    var angleDiff = getAngleDiff(getEventAngle(event));
    //console.log("velocity:",velocity)

    if(velocity!==0)
    {
    spinBottle.rotation= (70*velocity*velocity*velocity)+lastangle //360 test number


    if(velocity>0)
       { rotaryReleaseAnimation.direction= RotationAnimation.Clockwise;}
    else
       {rotaryReleaseAnimation.direction= RotationAnimation.Counterclockwise;}
    rotaryReleaseAnimation.duration=300*Math.abs(velocity)*Math.abs(velocity)
    //hier wird die Flasche zurückgelegt auf den Punkt wo man loslässt
    //lastangle darf nicht in betracht gezogen werden da rotation schon aufgerufen worderen ist
    //und rotaryReleaseAnimation.from sich auf den Winkel von der bottleArea sich bezieht
    rotaryReleaseAnimation.from=-(70*velocity*velocity*velocity)
    rotaryReleaseAnimation.to =0// die Flasche muss wieder auf der bottleArea "landen"
    rotaryReleaseAnimation.running = true
    lastangle=(70*velocity*velocity*velocity)+lastangle  // wichtig für die ausgangsposition des nächsten drehens
    }
}


