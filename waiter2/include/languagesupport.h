#ifndef LANGUAGESUPPORT_H
#define LANGUAGESUPPORT_H

//------------------------------------------------------------------------------

#ifndef QSTRING_H
#include <QObject>
#endif

namespace rotable
{
    class Languagesupport;
}

//------------------------------------------------------------------------------

class rotable::LanguageSupport : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString emptyString READ getEmptyString NOTIFY languageChanged)

public:
    LanguageSupport()
    {
        translator1 = new QTranslator(this);
        translator2 = new QTranslator(this);
    }

    QString getEmptyString()
    {
       return "";
    }

    Q_INVOKABLE void selectLanguage(QString language)
    {
        if(language==QString("de"))
        {
            translator1->load("localisation/main2_de", ".");
            qApp->installTranslator(translator1);
        }

        if(language == QString("en"))
        {
            qApp->removeTranslator(translator1);
            qApp->removeTranslator(translator2);
        }

        emit languageChanged();
    }

signals:
    void languageChanged();

private:
    QTranslator *translator1;
    QTranslator *translator2;
};

//------------------------------------------------------------------------------

#endif // LANGUAGESUPPORT_H
