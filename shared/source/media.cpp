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

QString Media::getPath(int mediaType)
{
    switch (mediaType) {
    case ComPackage::AdvertisingVideo:
        _path="/opt/rotable/AdvertisingVideo";
        break;
    case ComPackage::AdvertisingPicture:
        _path="/opt/rotable/AdvertisingPicture";
        break;
    case ComPackage::CatergoryIcon:
        _path="/opt/rotable/CategoryIcone";
        break;
    case ComPackage::ProductPicture:
        _path="/opt/rotable/ProductPicture";
        break;
    default:
        break;
    }
    return _path;
}




