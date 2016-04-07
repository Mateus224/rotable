#include "licence.h"

#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>

using namespace std;
using namespace rotable;
using namespace CryptoPP;

#include <QByteArray>

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

string Licence::loadLicenceFromFile() const
{

}

//------------------------------------------------------------------------------

bool Licence::verifityLicence(RSA::PublicKey publicKey) const
{

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
        if(Q_UNLIKELY(!verifityLicence(key)))
            ;


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
