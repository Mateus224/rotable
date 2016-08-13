#include "languagesupport.h"

#include <QGuiApplication>

//-----------------------------------------------------

using namespace rotable;

//-----------------------------------------------------

LanguageSupport::LanguageSupport()
{
    _translator1 = new QTranslator(this);
    _translator2 = new QTranslator(this);

    loadQmlTranslations(QDir("localisation"));

    QString locale = QLocale::system().name();
    locale.truncate(locale.lastIndexOf("_"));
    if (_translator1->load("localisation/main2_"+locale)) qApp->installTranslator(_translator1);
    else qDebug() << tr("Could not load proper locale file.");
}

//-----------------------------------------------------

QString LanguageSupport::getEmptyString()
{
    return "";
}

//-----------------------------------------------------

Q_INVOKABLE void LanguageSupport::selectLanguage(QString language)
{
    if(language==QString("de"))
    {
        _translator1->load("localisation/main2_de", ".");
        qApp->installTranslator(_translator1);
    }

    if(language==QString("pl"))
    {
        _translator1->load("localisation/main2_pl", ".");
        qApp->installTranslator(_translator1);
    }

    if(language == QString("en"))
    {
        qApp->removeTranslator(_translator1);
        qApp->removeTranslator(_translator2);
    }

    emit languageChanged();
}

//-----------------------------------------------------

void LanguageSupport::loadQmlTranslations(QDir directory)
{
    _qmlFileNames = directory.entryList();
}
