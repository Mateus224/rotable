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

void LanguageSupport::LoadInit(const QString &forceLang)
{
    if (forceLang=="")
    {
        QString locale = QLocale::system().name();
        locale.truncate(locale.lastIndexOf("_"));
        selectLanguage(locale);
    }
    else selectLanguage(forceLang);
}

//-----------------------------------------------------

QString LanguageSupport::getEmptyString()
{
    return "";
}

//-----------------------------------------------------

Q_INVOKABLE void LanguageSupport::selectLanguage(const QString &language)
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
            loadSingleFile("client_"+language);
            break;
        case AppType::waiter:
            loadSingleFile("waiter_"+language);
            break;
        case AppType::server:
            loadSingleFile("server_"+language);
            break;
        case AppType::admin:
            loadSingleFile("admin_"+language);
            break;
        }
        qApp->installTranslator(_translator1);
    }

    emit languageChanged();
}

//-----------------------------------------------------

bool LanguageSupport::loadSingleFile(const QString &qmFileName)
{
    bool loadSuccesfull = _translator1->load(qmFileName,"localisation");
    if (!loadSuccesfull) qDebug() << tr("Could not load file ")+qmFileName;
    return loadSuccesfull;
}
