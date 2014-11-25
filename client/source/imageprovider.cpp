#include "private/precomp.h"

#include "imageprovider.h"
#include "client.h"
#include "utils.h"

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ImageProvider::ImageProvider(rotable::Client *client)
  : QQuickImageProvider(QQuickImageProvider::Image,
    QQmlImageProviderBase::ForceAsynchronousImageLoading),
    _client(client)
{

}

//------------------------------------------------------------------------------

ImageProvider::~ImageProvider()
{

}

//------------------------------------------------------------------------------

QImage ImageProvider::requestImage(
    const QString &id, QSize *size, const QSize &requestedSize)
{
  if (!_images.contains(id)) {
    if (_imageContainer.hasImage(id)) {
      _images[id] = *_imageContainer.getImage(id);
    } else {
      QString packageId = _client->requestImage(id);

      // wait for result:
      while (_client->hasPackage(packageId)) {
        delay(100);
      }

      // image still not in images: insert dummy
      // because server probably rejected our request.
      if (!_images.contains(id)) {
        _images[id] = QImage(requestedSize, QImage::Format_Mono);
      }
    }
  }

  QImage ret = _images[id];

  if (size) {
    *size = ret.size();
  }

  if (requestedSize.isValid()) {
    return ret.scaled(requestedSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  } else {
    return ret;
  }
}

//------------------------------------------------------------------------------

void ImageProvider::imageReceived(QString name, QImage image)
{
  _images[name] = image;
}
