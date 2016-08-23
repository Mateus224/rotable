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

/**
 * The LanguageSupport class handles loading of .qm translation files and
 * translating the applications in realtime.
 * @version 1.0
 */
class rotable::LanguageSupport : public QObject
{
    Q_OBJECT

    /**
     * The emptyString property is used to tag QML text components,
     * so LangugageSupport can send languageChanged signal to them.
     *
     * QML Example:
     * Rect {
     *  Text: qsTr("This is transalted string") + languageSupportContextProperty.emptyString
     * }
     */
    Q_PROPERTY(QString emptyString READ getEmptyString NOTIFY languageChanged)

public:
    /**
     * Enumeration of application types.
     */
    enum AppType {server,client,waiter,admin};

    /**
     * Default constructor.
     *
     * @param apptype           type of application
     */
    LanguageSupport(AppType apptype);

    /**
     * It does what it says, returns an empty string.
     *
     * @return Qstring          the empty string
     */
    QString getEmptyString();

    /**
     * Since translator files cant be loaded it the constructor this function
     * loads the initial translation based on a system locale.
     *
     * This fuction has to be called after creating LanguageSupport object.
     *
     * @param language          if you want load a specific language at start, otherwise leave empty
     */
    void LoadInit(const QString &forceLang="");

    /**
      * This function needs to be called everytime you want to switch language in application.
      *
      * @param language         two letter name of the new language, for example "de", "fr"
      *
      * QML examlpe:
      * Button {
      *     OnClicked: languageSupportContextProperty.selectLanguage("en")
      * }
      */
    Q_INVOKABLE void selectLanguage(const QString& language);

signals:
    void languageChanged();

private:
    QTranslator* _translator1;
    QTranslator* _translator2;

    AppType _applicationType;

    bool loadSingleFile(const QString &qmFileName);
};

//------------------------------------------------------------------------------

#endif // LANGUAGESUPPORT_H
