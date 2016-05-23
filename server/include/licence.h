#pragma once

#include <string>
#include <QException>

#ifdef Q_OS_WIN
#include <dependencies/cryptopp/include/rsa.h>
#else
#include <cryptopp/rsa.h>
#endif

//------------------------------------------------------------------------------

namespace rotable{
    class Licence;
}

//------------------------------------------------------------------------------

/**
 * @brief The rotable::Licence class provide support for check, verifity licence and
 * control connected table
 */
class rotable::Licence{
public:
    /**
     * @brief Licence
     * Default constructor, load licence key and parse it
     */
    Licence();

    /**
     * @brief loadLicence
     * Provide load licence
     * @param path          path to licence
     */
    void loadLicence(std::__cxx11::string path);

    /**
     * @brief getLicenceStatus
     * prepare data about licence for admonistration application
     * @return              string with data
     */
    std::__cxx11::string getLicenceStatus();

public slots:
    void connectTable();
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
    std::__cxx11::string loadToString(std::__cxx11::string filePath) const;

    /**
     * @brief verifityLicence
     * Verifity licence
     * @param publicKey     public key
     * @param licence       licence
     * @param sig           signature of licence
     */
    void verifityLicence(CryptoPP::RSA::PublicKey publicKey, std::__cxx11::string licence, std::__cxx11::string sig) const;

    /**
     * @brief parseLicence
     * Parse licence and save options
     * @param licence       encode licence
     */
    void parseLicence(std::__cxx11::string licence) const;

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
};

//------------------------------------------------------------------------------
