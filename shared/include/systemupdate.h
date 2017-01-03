#ifndef SYSTEMUPDATE_H
#define SYSTEMUPDATE_H
#ifndef QSTRING_H
#include <QString>
#endif
#include <QObject>

namespace rotable {
    class SystemUpdate;
}
class  rotable::SystemUpdate: public QObject
{
    Q_OBJECT
public:
    explicit SystemUpdate(QObject* parent = 0);


    //------------JSON-------------//

    QJsonValue toJSON() const;

    static SystemUpdate* fromJSON(const QJsonValue &jval);


    //------SET and GET data-------//

    inline int getId() const {return _id;}

    inline void setId(const int& id){_id = id;}


    inline double getCurrentVersion() const{return _currentVersion;}

    inline void setCurrentVersion(const double& currentVersion) {_currentVersion=currentVersion;}


    inline double getAvailableVersion() const{return _availableVersion;}

    inline void setAvailableVersion(const double& availableVersion) {_availableVersion=availableVersion;}


    inline QString getDateCurrentVersion() const{return _dateCurrentVersion;}

    inline void setDateCurrentVersion(const QString& dateCurrentVersion) {_dateCurrentVersion=dateCurrentVersion;}


    inline QString getDateAvailableVersion() const{return _dateAvailableVersion;}

    inline void setDateAvailableVersion(const QString& dateAvailableVersion) {_dateAvailableVersion=dateAvailableVersion;}

    int _id;
    double _currentVersion;
    double _availableVersion;
    QString _dateCurrentVersion;
    QString _dateAvailableVersion;

};

#endif // SYSTEMUPDATE_H
