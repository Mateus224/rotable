#ifndef IMAGE_CONTAINER_H
#define IMAGE_CONTAINER_H

//------------------------------------------------------------------------------

#include <QObject>
#include <QMap>
#include <QString>
#include <QPixmap>
#include <filecontainer/file.h>

//------------------------------------------------------------------------------

namespace rotable {
  class ImageContainer;
}

class QImage;

//------------------------------------------------------------------------------

/**
 * This class stores images.
 */
class rotable::ImageContainer: public QObject
{
  Q_OBJECT

public:
  /**
   * Default constructor
   *
   * @param parent          parent object
   */
  explicit ImageContainer(QObject* parent = 0);

  /**
   * Destructor
   */
  ~ImageContainer();

  /**
   * Add an extra image to the container.
   * (The container will store the image on the HDD.)
   *
   * @param name          image name
   * @param image         image
   * @return              true on success
   */
  bool addImage(const QString& name, QImage* image);

  /**
   * Check whether the container has an image with given name.
   *
   * @param name          image name
   * @return              true if image exists
   */
  bool hasImage(const QString& name) const;

  /**
   * Get Image with given name.
   *
   * @param name          image name
   * @return              image or null if image is unknown
   */
  QImage* getImage(const QString& name) const;

  /**
   * Get Image with given name as QPixmap.
   *
   * @param name          image name
   * @return              pixmap (can be invalid)
   */
  QPixmap getImageAsPixmap(const QString& name) const;

  /**
   * Set directory for additional images.
   * Changing this will reload all images!
   * (Default: ./images/)
   *
   * @param dir           new directory for additional images
   */
  void setDir(const QString& dir);

  /**
   * Get a list of all image names.
   *
   * @return              image name list
   */
  QStringList imageNames() const;

private:
  /* Images */
  QMap<QString, QImage*> _images;

  /* Directory for additional images */
  QString _imageDir;
}; // class ImageContainer

//------------------------------------------------------------------------------

#endif // IMAGE_CONTAINER_H
