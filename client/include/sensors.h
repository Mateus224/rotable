#ifndef ROTABLE_SENSORS_H
#define ROTABLE_SENSORS_H

//------------------------------------------------------------------------------

#ifndef QOBJECT_H
#include <QObject>
#endif

#ifndef QTIMER_H
#include <QTimer>
#endif

//------------------------------------------------------------------------------

namespace rotable {
  class Sensors;
}

//------------------------------------------------------------------------------

class rotable::Sensors : public QObject
{
  Q_OBJECT

public:
  explicit Sensors(QObject *parent = 0);
  ~Sensors();

  inline int screenRotation() const { return _screenRotation; }
  inline bool contact() const { return _contact; }

signals:
  void rotationChanged();
  void contactChanged();

public slots:
  void checkDisplaySensors();
  void checkDistanceSensors();

private:
  int _screenRotation;

  QTimer _displaySensorCheckTimer;
  QTimer _distanceSensorCheckTimer;

  int _i2cDevice;
  bool _contact;
  int _contactThreshold;
}; // class Sensors

//------------------------------------------------------------------------------

#endif // ROTABLE_SENSORS_H
