#pragma once

#include <string>

#include <QTcpSocket>
#include <QException>
#include <QDate>
#include <QObject>

#include <cryptopp/rsa.h>



//------------------------------------------------------------------------------

namespace rotable{
    class Licence;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::Licence class provide support for check, verifity licence and
 * control connected table
 */
class rotable::Licence: public QObject{
private:
    Q_OBJECT
public:

    /**
     * @brief Licence
     * Default constructor, load licence key and parse it
     * @param hostname      hostname
     * @param path          path to licence
     * @parent              parent object
     */
    Licence(const QString &hostname, const QString &path, QObject *parent = nullptr);

    /**
     * @brief loadLicence
     * Provide load licence
     * @param path          path to licence
     */
    void loadLicence(const QString &path);

    /**
     * @brief loadLicence
     * Provide load licence from default path
     */
    void loadLicence() { loadLicence(_path); }

    /**
     * @brief getLicenceStatus
     * prepare data about licence for admonistration application
     * @return              string with data
     */
    std::string getLicenceStatus();

    /**
     * @brief getLicence
     * reserve licence for specific conncection
     * @param socket        Socket with connection
     * @return              true if licence is free
     */
    bool getLicence(QTcpSocket *socket);

signals:
    /**
     * @brief getLastIncomeDate
     * Signal connect to database and return last date in income
     * table to ansure if anyone change date
     * @param date          last date in income table
     */
    void getLastIncomeDate(QDate *date);

public slots:
    void disconnectTable();

private:
    /**
     * @brief loadKeyFromFile
     * Get pubic key from resourse
     * @return              key
     */
    CryptoPP::RSA::PublicKey loadKeyFromFile() const;

    /**
     * @brief loadToString
     * Read file and save it to string
     * @param filePath      path to licence
     * @return              string with licences
     */
    std::string loadToString(std::string filePath) const;

    /**
     * @brief verifityLicence
     * Verifity licence
     * @param publicKey     public key
     * @param licence       licence
     * @param sig           signature of licence
     */
    void verifityLicence(CryptoPP::RSA::PublicKey publicKey, std::string licence, std::string sig) const;

    /**
     * @brief parseLicence
     * Parse licence and save options
     * @param licence       encode licence
     */
    void parseLicence(std::string licence);

    /**
     * @brief verifityTime
     * Check if time is system is property and if licence isn't aut of date
     */
    void verifityTime();

    /**
     * @brief _maxTable
     * Maximum number of table
     */
    int _maxTable;
    /**
     * @brief _connectedTable
     * Actual connected table
     */
    int _connectedTable;

    QDate _licenceBegin;
    QDate _licenceEnd;

    QString _hostname;
    QString _path;

    //--------------------------------------------------------------------------
    // Exceptions
    //--------------------------------------------------------------------------

    /**
     * @brief The NoLicenceException class
     * Exception when licence file not found
     */
    class NoLicenceException: QException{};
    /**
     * @brief The NoPublKeyException class
     * Exception when public key not found
     */
    class NoPublKeyException: QException{};
    /**
     * @brief The UnvalidLiceneException class
     * Exception when hash of licence is wrong
     */
    class UnvalidLiceneException: QException{};
    /**
     * @brief The SingLicenceException class
     * Exception when sign file don't responds to licence
     */
    class SignLicenceException: QException{};

    /**
     * @brief The UnvalidTimeException class
     * Exception when time of last income is older from actual date
     */
    class UnvalidTimeException: QException{};
};

//------------------------------------------------------------------------------
