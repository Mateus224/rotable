#pragma once

#include <string>
#include <QException>

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
    void loadLicence(std::string path);

    /**
     * @brief getLicenceStatus
     * prepare data about licence for admonistration application
     * @return              string with data
     */
    std::string getLicenceStatus();

public slots:
    void connectTable();
    void disconnectTable();

private:
    /**
     * @brief loadKeyFromFile
     * Get pubic key from resourse
     * @return              string with key
     */
    CryptoPP::RSA::PublicKey loadKeyFromFile() const;

    /**
     * @brief loadLicenceFromFile
     * Get licence from file
     * @return              string with licence to encode
     */
    std::string loadLicenceFromFile() const;

    /**
     * @brief verifityLicence
     * Verifity licence from file
     * @param publicKey     public key
     * @return              true on success
     */
    bool verifityLicence(CryptoPP::RSA::PublicKey publicKey) const;

    /**
     * @brief parseLicence
     * Parse licence and save options
     * @param licence       encode licence
     */
    void parseLicence(std::string licence) const;

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
