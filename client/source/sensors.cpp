#include "private/precomp.h"

#include "sensors.h"

#define LED_Pin 1
#define PWM_CHECK_INTERVAL 50
#define DISPLAY_SENSOR_CHECK_INTERVAL 25
#define DISTANCE_SENSOR_CHECK_INTERVAL 250
#define PCF8591_SLAVE_ADDR	0x48
#define PCF8591_FORCE 0
#define REG_CTL				0x40


#ifdef __arm__
#include <wiringPi.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <linux/types.h>
#include <linux/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif


//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

Sensors::Sensors(QObject *parent) :
  QObject(parent), _screenRotation(0), _i2cDevice(-1), _contact(false),
  _contactThreshold(50)
{
  connect(&_displaySensorCheckTimer, SIGNAL(timeout()), this, SLOT(checkDisplaySensors()));
  _displaySensorCheckTimer.start(DISPLAY_SENSOR_CHECK_INTERVAL);
  connect(&_distanceSensorCheckTimer, SIGNAL(timeout()), this, SLOT(checkDistanceSensors()));
  _distanceSensorCheckTimer.start(DISTANCE_SENSOR_CHECK_INTERVAL);
  connect(&_ledPWM_CheckTimer,SIGNAL(timeout()),this,SLOT(set_PWM_signal()));
  _ledPWM_CheckTimer.start(PWM_CHECK_INTERVAL);


 if(_device==3||_device==4)
 {
#ifdef __arm__
  _i2cDevice = open("/dev/i2c-1", O_RDWR);
  if (-1 == _i2cDevice) {
    qDebug() << tr("Error reading /dev/i2c-1: %1").arg(strerror(errno));
  } else {
    if (-1 == ioctl(_i2cDevice, PCF8591_FORCE ? I2C_SLAVE_FORCE : I2C_SLAVE,
                    PCF8591_SLAVE_ADDR))
    {
      qDebug() << tr("Error at ioctl: %1").arg(QString(strerror(errno)));
      close(_i2cDevice);
      _i2cDevice = -1;
    }
  }
  _intervalCounter=0;
  _lighter=true;
#endif
 }
}

//------------------------------------------------------------------------------

void Sensors::set_PWM_signal()
{
    if(_device==4)
    {
#ifdef __arm__
    if(_intervalCounter==50)
    {
          _lighter=false;
    }
    else if(_intervalCounter==10)
    {
        _lighter=true;
    }
    QString cons="gpio pwm 1 ";
    QString num= QString::number(_intervalCounter);
    QString sys=cons+num;

    char *c_num = new char[sys.length() + 1];
    strcpy(c_num, sys.toStdString().c_str());

    if(_lighter)
    {
        system(c_num);
       _intervalCounter=_intervalCounter+2;
    }
    else
    {
        system(c_num);
        _intervalCounter=_intervalCounter-2;
    }
    //qDebug()<<_intervalCounter;
#endif
  _ledPWM_CheckTimer.start(PWM_CHECK_INTERVAL);
    }
}


//------------------------------------------------------------------------------

Sensors::~Sensors()
{
#ifdef __arm__
  if (-1 != _i2cDevice) {
    close(_i2cDevice);
  }
#endif
}

//------------------------------------------------------------------------------

void Sensors::checkDisplaySensors()
{
    if(_device==1||_device==2)
    {
        _screenRotation=0;
    }
    else{

#ifdef __arm__
/*  qDebug() << tr("Sensors %1, %2, %3, %4")
              .arg(digitalRead(7)).arg(digitalRead(8))
              .arg(digitalRead(24)).arg(digitalRead(25));
*/
  if (LOW == digitalRead(7)) {
    if (_screenRotation != 180) {
      _screenRotation = 180;
      emit rotationChanged();
    }
  } else if (LOW == digitalRead(8)) {
    if (_screenRotation != 0) {
      _screenRotation = 0;
      emit rotationChanged();
    }
  } else if (LOW == digitalRead(24)) {
    if (_screenRotation != 270) {
      _screenRotation = 270;
      emit rotationChanged();
    }
  } else if (LOW == digitalRead(25)) {
    if (_screenRotation != 90) {
      _screenRotation = 90;
      emit rotationChanged();
    }
  }
#endif
  _displaySensorCheckTimer.start(DISPLAY_SENSOR_CHECK_INTERVAL);
      }
}

//------------------------------------------------------------------------------

void Sensors::checkDistanceSensors()
{
#ifdef __arm__
  if (-1 != _i2cDevice) {
    // ctl byte //output enable und die 4 analogen eingänge ins reg_ctl register schreiben
    if (i2c_smbus_write_byte_data(_i2cDevice, REG_CTL, 0x43) < 0) {
      qDebug() << tr("Error in i2c_smbus_write_byte_data: %1").arg(strerror(errno));
    } else {

      long values[4];

      for (int i = 0; i < 4; ++i) {
        long res = i2c_smbus_read_byte_data(_i2cDevice, 0x40 + i);
        //qDebug() << res;
        values[i] = res;
        if (res < 0) {
          qDebug() << tr("Error in i2c_smbus_read_byte_data: %1").arg(strerror(errno));
        } else {
          if (res > _contactThreshold) {
            if (!_contact) {
              _contact = true;
              emit contactChanged();
            }
          } else {
            if (_contact) {
              _contact = false;
              emit contactChanged();
            }
          }
        }
      }

     /* qDebug() << tr("Distance Sensor %1, %2, %3, %4")
                  .arg(values[0]).arg(values[1])
                  .arg(values[2]).arg(values[3]);*/
    }
  }
#endif

  _distanceSensorCheckTimer.start(DISTANCE_SENSOR_CHECK_INTERVAL);
}
