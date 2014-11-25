#ifndef ROTABLE_IMAGEPROVIDER_H
#define ROTABLE_IMAGEPROVIDER_H

//------------------------------------------------------------------------------

#ifndef QQUICKIMAGEPROVIDER_H
#include <QQuickImageProvider>
#endif

#include "imagecontainer.h"

//------------------------------------------------------------------------------

namespace rotable {
  class Client;
  class ImageProvider;
}

//------------------------------------------------------------------------------

/**
 * Client logic
 */
class rotable::ImageProvider : public QQuickImageProvider
{
public:
  /**
   * Constructor
   *
   * @param client        client object
   */
  ImageProvider(Client* client);

  /**
   * Destructor
   */
  ~ImageProvider();

  /**
   * Return image with given id.
   *
   * @param id                image id
   * @param size              original image size
   * @param requestedSize     requested size (only used when valid)
   * @return                  image
   */
  QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize);

  /**
   * Image received.
   *
   * @param name              image name
   * @param image             image
   */
  void imageReceived(QString name, QImage image);

private:
  /* Stored images from server */
  QMap<QString, QImage> _images;

  /* Image container for local image files */
  ImageContainer _imageContainer;

  /* Client */
  Client* _client;
}; // class ImageProvider

//------------------------------------------------------------------------------

#endif // ROTABLE_IMAGEPROVIDER_H
