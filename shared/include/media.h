#ifndef MEDIA_H
#define MEDIA_H
#ifndef QICON_H
#include <QIcon>
#endif

#ifndef QJSONOBJECT_H
#include <QJsonObject>
#endif
#include "compackage.h"
namespace rotable {
    class Media;
}

class rotable::Media : public QObject
{
    Q_OBJECT
public:
    explicit Media(QObject *parent = 0);

    /**
     * @brief
     *
     * @return const QString
     */
    inline const QString& name() const { return _name; }
    /**
     * @brief
     *
     * @param str
     */
    void setName(const QString &str);

    /**
     * @brief
     *
     * @return const QString
     */
    inline const QString& icon() const { return _icon; }
    /**
     * @brief is not implemented now
     *
     * @param ico
     */
    void setIcon(const QString &ico);

    /**
     * @brief
     *
     * @return int
     */

    inline int id() const { return _id; }
    /**
     * @brief
     *
     * @param id
     */
    inline void setId(int id) { _id = id; }

    /**
     * @brief getPath
     * return the Path to the file
     * every kind of media has an other path
     */
    QString getPath(int mediaType);

    /**
     * @brief getSize
     * @return the size of the file
     */
    int getSize();

    /**
     * @brief getPlayed
     * @return how often the file was played on the clients
     */
    int getPlayed();

    /**
     * @brief freeMbOnSD for knowing if we can store the file
     * @return how much free MB is on the SD card
     */
    int getFreeMbOnSD();

    /**
     * @brief setFrequenz
     * set how often we will play advertising
     */
    inline void setFrequenz(int frequnez);

    /**
     * @brief getFrequenz
     * set how often we will play advertising
     * @return time in minutes
     */
    inline  int getFrequency() const { return _frequency; }
    /**
     * @brief
     *
     * @param sequence
     */
private:
  /* Media name */
  QString _name;

  /* Media icon */
  QString _icon;

  /* Unique category ID */
  int _id;
  /*the frequenz for playing advertising*/
  int _frequency;

  QString _path;

};

#endif // MEDIA_H
