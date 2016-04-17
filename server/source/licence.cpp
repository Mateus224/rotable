#include "licence.h"

#include <QByteArray>
#include <QCryptographicHash>
#include <QTextCodec>

#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>

#include <fstream>
#include <streambuf>

using namespace std;
using namespace rotable;
using namespace CryptoPP;

//------------------------------------------------------------------------------

rotable::Licence::Licence(const QString &hostname, const QString &path, QObject *parent): QObject(parent), _maxTable(0), _connectedTable(0),
   _hostname(hostname),  _path(path)
{
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

    return key;                                            
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

void Licence::parseLicence(string licence)
{
    //Split licence to fields and hash
    auto splitLicence =  QString(licence.c_str()).split(";;");
    //Check hash licence with licence fields
    if(Q_UNLIKELY(
                splitLicence[1] != QTextCodec::codecForName("UTF-8")->toUnicode(QCryptographicHash::hash(splitLicence[0].toUtf8(),
                                                            QCryptographicHash::Sha3_512).toHex())))
            throw new UnvalidLiceneException;

   //Split to fields
   QStringList licenceFields = splitLicence[0].split(";");
   //Read data to check
   #ifdef Q_OS_ANDROID
        QString platform = "Android";
   #else
        QString platform = "PC";
   #endif
   //Check data with licene
   if(Q_UNLIKELY(licenceFields[0] != _hostname && licenceFields[1] != platform))
       throw new UnvalidLiceneException;
   //Read licece time
   _licenceBegin = QDate::fromString(licenceFields[3], "dd.MM.yyyy");
   _licenceEnd = QDate::fromString(licenceFields[4], "dd.MM.yyyy");
   //Verification licence time
   verifityTime();

   _maxTable = licenceFields[2].toInt();
}

//------------------------------------------------------------------------------

void Licence::verifityTime()
{
    QDate  lastDate;
    lastDate =  QDate::currentDate();

    QDate *lastIncomeDate = nullptr;
    emit getLastIncomeDate(lastIncomeDate);\
    if(Q_LIKELY(lastIncomeDate))
        if(Q_UNLIKELY(*lastIncomeDate > lastDate))
            throw new UnvalidTimeException;

    if(Q_UNLIKELY(_licenceBegin < lastDate || _licenceEnd > lastDate))
        throw new UnvalidLiceneException;
}


//------------------------------------------------------------------------------

void rotable::Licence::loadLicence(const QString &path)
{
    try{
        auto key = loadKeyFromFile();
        //Change base on path
        auto licence = loadToString((path+QString("licence.data")).toStdString());
        auto sig = loadToString((path+QString("sig.data")).toStdString());
        verifityLicence(key, licence, sig);
        parseLicence(licence);
    }
    catch(NoPublKeyException){ }
    catch(NoLicenceException){ }
    catch(SignLicenceException){ }
    catch(UnvalidLiceneException){ }
    catch(UnvalidTimeException){ }

}

//------------------------------------------------------------------------------

string Licence::getLicenceStatus()
{  
    //TODO: not needed now, add laetly
    return string("");
}

//------------------------------------------------------------------------------

bool Licence::getLicence(QTcpSocket *socket)
{
    if(Q_UNLIKELY(_maxTable == _connectedTable))
        return false;
    ++_connectedTable;
    connect(socket, &QTcpSocket::disconnected, this, &Licence::disconnectTable);
    return true;
}

//------------------------------------------------------------------------------

void Licence::disconnectTable()
{
    --_connectedTable;
}

//------------------------------------------------------------------------------
