#include "include/media.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

Media::Media(QObject* parent) :
  QObject(parent), _id(-1), _frequency(-1)
{

}

//------------------------------------------------------------------------------

void Media::setName(const QString &str)
{
  if (_name != str) {
    _name = str;
    //emit nameChanged();
  }
}
