#pragma once

#include <string>
#include <QException>

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
    std::string loadKeyFromFile() const;

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
    bool verifityLicence(std::string publicKey) const;

    /**
     * @brief parseLicence
     * Parse licence and save options
     * @param licence       encode licence
     */
    void parseLicence(std::string licence) const;

    int _maxTable;
    int _table;

    //--------------------------------------------------------------------------
    // Exceptions
    //--------------------------------------------------------------------------

    class NoLicenceException: QException{};
    class NoPublKeyException: QException{};
    class UnvalidLiceneException: QException{};
    class SingLicenceException: QException{};
};

//------------------------------------------------------------------------------
