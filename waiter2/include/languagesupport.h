#ifndef LANGUAGESUPPORT_H
#define LANGUAGESUPPORT_H

//------------------------------------------------------------------------------

#ifndef QSTRING_H
#include <QObject>
#include <QTranslator>
#include <QDir>
#endif

namespace rotable
{
    class LanguageSupport;
}

//------------------------------------------------------------------------------

class rotable::LanguageSupport : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString emptyString READ getEmptyString NOTIFY languageChanged)

public:
    LanguageSupport();

    QString getEmptyString();

    Q_INVOKABLE void selectLanguage(QString language);

signals:
    void languageChanged();

private:
    QTranslator* _translator1;
    QTranslator* _translator2;

    QStringList _qmlFileNames;

    void loadQmlTranslations(QDir directory);
};

//------------------------------------------------------------------------------

#endif // LANGUAGESUPPORT_H
