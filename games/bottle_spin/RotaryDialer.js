// start angle of a dialer rotation
var startAngle = null;

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

function initialize()
{
    centerX = dialer.x + dialer.width / 2;
    centerY = dialer.y + dialer.height / 2;
}

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

    return (angle - startAngle);
}

function dialerPressed(event)
{
    var newAngle = getEventAngle(event);

    var hole = holeFromAngle(2 * Math.PI - newAngle);

    // check the angle corresponds to a hole
    if(hole != null)
    {
	// hold the starting angle value
	startAngle = newAngle;

	// evaluate the maximum rotation angle
	maxAngle = hole * digitAngle + dialerStopAngle;
    }
}

function dialerMoved(event)
{
    if(startAngle != null)
    {
	var newAngle = getEventAngle(event);

	var angleDiff = getAngleDiff(newAngle);

	if(angleDiff < 0)
	    angleDiff = 0;
	else if(angleDiff > maxAngle)
	    angleDiff = maxAngle;

	//console.log("angle: " + angleDiff + ", " + (angleDiff * 180 / Math.PI));

	dialer.rotation = angleDiff * 180 / Math.PI;
    }

    //console.log("MOVED: " + startX + ", " + startY + ", " + centerX + ", " + centerY);
}
function dialerReleased(event)
{
    if(startAngle != null)
    {
	var angleDiff = getAngleDiff(getEventAngle(event));

	var hole = holeFromAngle(Math.min(angleDiff, maxAngle) - dialerStopAngle);

	if(hole != null)
	{
	    var digit = (hole + 1) % 10;

	    numberEntered(digit);
	}

	console.log("DIFF: " + angleDiff + ", " + hole);
	rotaryReleaseAnimation.to = 0;
	rotaryReleaseAnimation.running = true;
	//dialer.rotation = 0;

	startAngle = null;
    }
}
