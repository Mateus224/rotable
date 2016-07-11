#include "private/precomp.h"

#include "imagecontainer.h"

#include <QDirIterator>
#include <QImage>
#include <QResource>

//------------------------------------------------------------------------------

using namespace rotable;

//------------------------------------------------------------------------------

ImageContainer::ImageContainer(QObject* parent)
  : QObject(parent)
{
  setDir("./images/");
}

//------------------------------------------------------------------------------

ImageContainer::~ImageContainer()
{
    qDeleteAll(_images);
    _images.clear();
}

//------------------------------------------------------------------------------

bool ImageContainer::addImage(const QString &name, QImage *image)
{
  if (0 == image || image->isNull() || name.isEmpty()) {
    return false;
  }

  if (_images.contains(name)) {
    return false;
  }

  if (!image->save(_imageDir + name + ".png")) {
    return false;
  }

  _images[name] = image;

  return true;
}

//------------------------------------------------------------------------------

bool ImageContainer::hasImage(const QString &name) const
{
  return _images.contains(name);
}

//------------------------------------------------------------------------------

QImage *ImageContainer::getImage(const QString &name) const
{
  if (_images.contains(name)) {
    return _images[name];
  }

  return 0;
}

//------------------------------------------------------------------------------

QPixmap ImageContainer::getImageAsPixmap(const QString &name) const
{
  if (_images.contains(name)) {
    QPixmap pm;
    if (pm.convertFromImage(*_images[name])) {
      return pm;
    } else {
      qCritical() << tr("Could not convert image '%1' to QPixmap!").arg(name);
    }
  }

  return QPixmap();
}

//------------------------------------------------------------------------------

void ImageContainer::setDir(const QString &dir)
{
  _images.clear();

  _imageDir = dir;

#if defined(_WIN64) || defined(_WIN32)
  _imageDir.replace('/', QDir::separator());
#else
  _imageDir.replace('\\', QDir::separator());
  _imageDir.replace(':', QDir::separator());
#endif

  if (!_imageDir.endsWith(QDir::separator())) {
    _imageDir += QDir::separator();
  }

  _images["beer"] = new QImage(":/images/resources/beer.png");
  _images["bottle"] = new QImage(":/images/resources/bottle.png");
  _images["cocktail"] = new QImage(":/images/resources/cocktail.png");
  _images["dices"] = new QImage(":/images/resources/dices.png");
  _images["hotdrink"] = new QImage(":/images/resources/hotdrink.png");
  _images["longdrink"] = new QImage(":/images/resources/longdrink.png");
  _images["shot"] = new QImage(":/images/resources/shot.png");
  _images["soft"] = new QImage(":/images/resources/soft.png");
  _images["wine"] = new QImage(":/images/resources/wine.png");
  _images["waiter"] = new QImage(":/images/resources/waiter.png");

  // Load images from imageDir
  QDirIterator dirIt(_imageDir, QDirIterator::NoIteratorFlags);
  while (dirIt.hasNext()) {
    dirIt.next();

    QFileInfo fi(dirIt.filePath());

    if (fi.isFile()) {
      if (fi.suffix() == "png") {
        QString name = fi.baseName();
        if (!_images.contains(name)) {
          QImage* image = new QImage(dirIt.filePath());
          if (!image->isNull()) {
            _images[name] = image;
          }
        }
      }
    }
  }
}

//------------------------------------------------------------------------------

QStringList ImageContainer::imageNames() const
{
  return _images.keys();
}
