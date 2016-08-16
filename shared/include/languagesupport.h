#ifndef LANGUAGESUPPORT_H
#define LANGUAGESUPPORT_H

//------------------------------------------------------------------------------

#ifndef QSTRING_H
#include <QObject>
#include <QTranslator>
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
    enum AppType {server,client,waiter,admin};

    LanguageSupport(AppType apptype);

    QString getEmptyString();

    void LoadInit();

    Q_INVOKABLE void selectLanguage(QString language);

signals:
    void languageChanged();

private:
    QTranslator* _translator1;
    QTranslator* _translator2;

    AppType _applicationType;

    bool loadSingleFile(QString qmFileName);
};

//------------------------------------------------------------------------------

#endif // LANGUAGESUPPORT_H
