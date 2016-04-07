#include "licence.h"

#include <QByteArray>

#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>

#include <fstream>
#include <streambuf>

using namespace std;
using namespace rotable;
using namespace CryptoPP;

//------------------------------------------------------------------------------

rotable::Licence::Licence()
{
    //TODO: add path to licence
    loadLicence("");
}

//------------------------------------------------------------------------------

RSA::PublicKey  rotable::Licence::loadKeyFromFile() const
{
    //Open file from resource
    QFile file(":/publkey.txt");
    if (Q_UNLIKELY(!file.open(QIODevice::ReadOnly)))        //Check if we can read
        throw new NoPublKeyException();                     //Something is  wrong with key
    QByteArray data = file.readAll();                       //Read file
    ByteQueue queue;
    queue.Put2(reinterpret_cast<const byte *>(data.data()), data.size(), 0, true);
    RSA::PublicKey key;
    key.Load(queue);

    return key;                                            // Convert to string and return
}

//------------------------------------------------------------------------------

string Licence::loadToString(string filePath) const
{
    std::ifstream t(filePath);
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    return str;
}

//------------------------------------------------------------------------------

void Licence::verifityLicence(RSA::PublicKey publicKey,string licence, string sig) const
{
    RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);
    string combined(licence);
    combined.append(sig);

    try
    {
       StringSource(combined, true,
           new SignatureVerificationFilter(
               verifier, NULL,
               SignatureVerificationFilter::THROW_EXCEPTION
          )
       );
    }
    catch(SignatureVerificationFilter::SignatureVerificationFailed &err)
    {
        throw new SignLicenceException;
    }
}

//------------------------------------------------------------------------------

void Licence::parseLicence(string licence) const
{

}


//------------------------------------------------------------------------------

void rotable::Licence::loadLicence(string path)
{
    try{
        auto key = loadKeyFromFile();
        //Change base on path
        auto licence = loadToString("licence.data");
        auto sig = loadToString("sig.data");
        verifityLicence(key, licence, sig);
        parseLicence(licence);
    }
    catch(NoPublKeyException){

    }
    catch(NoLicenceException)
    {

    }

}

//------------------------------------------------------------------------------

string Licence::getLicenceStatus()
{

}

//------------------------------------------------------------------------------

void Licence::connectTable()
{
    if(Q_UNLIKELY(_maxTable == _connectedTable))
        ;
    ++_connectedTable;
}

//------------------------------------------------------------------------------

void Licence::disconnectTable()
{
    --_connectedTable;
}

//------------------------------------------------------------------------------
