#include "languagesupport.h"

#include <QGuiApplication>
#include <QTranslator>
#include <QDir>

//-----------------------------------------------------

using namespace rotable;

//-----------------------------------------------------

LanguageSupport::LanguageSupport(AppType apptype)
{
    _applicationType = apptype;

    _translator1 = new QTranslator(this);
    _translator2 = new QTranslator(this);
}

//-----------------------------------------------------

void LanguageSupport::LoadInit()
{
    QString locale = QLocale::system().name();
    locale.truncate(locale.lastIndexOf("_"));
    selectLanguage(locale);
}

//-----------------------------------------------------

QString LanguageSupport::getEmptyString()
{
    return "";
}

//-----------------------------------------------------

Q_INVOKABLE void LanguageSupport::selectLanguage(QString language)
{
    if(language == QString("en"))
    {
        qApp->removeTranslator(_translator1);
        qApp->removeTranslator(_translator2);
    }
    else
    {
        switch (_applicationType)
        {
        case AppType::client:
            loadSingleFile("Client_"+language);
            break;
        case AppType::waiter:
            loadSingleFile("waiter_"+language);
            break;
        case AppType::server:
            break;
        case AppType::admin:
            break;
        }
        qApp->installTranslator(_translator1);
    }

    emit languageChanged();
}

//-----------------------------------------------------

bool LanguageSupport::loadSingleFile(QString qmFileName)
{
    bool loadSuccesfull = _translator1->load(qmFileName,"localisation");
    if (!loadSuccesfull) qDebug() << "Could not load file "+qmFileName;
    return loadSuccesfull;
}
