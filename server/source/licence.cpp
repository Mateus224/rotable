#include "licence.h"

#include <QByteArray>
#include <QCryptographicHash>
#include <QTextCodec>
#include <QResource>
#include <QHostInfo>
#include <QFile>
#include <QDir>

#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>

#include <fstream>
#include <streambuf>

using namespace std;
using namespace rotable;
using namespace CryptoPP;

//------------------------------------------------------------------------------

rotable::Licence::Licence(const QString &path, QObject *parent): Licence(QDir(path), parent)
{

}

//------------------------------------------------------------------------------

Licence::Licence(const QDir &path, QObject *parent): QObject(parent), _maxTable(0), _connectedTable(0),
    _path(path)
{
    _hostname = QHostInfo::localHostName();
    loadLicence();
}

//------------------------------------------------------------------------------

RSA::PublicKey  rotable::Licence::loadKeyFromFile() const
{
    //Open file from resource
    QFile file(":/publkey.txt");
    if (Q_UNLIKELY(!file.open(QIODevice::ReadOnly)))        //Check if we can read
        throw new NoPublKeyException();                     //Something is  wrong with key
    QTextStream in(&file);
    std::string key_source = in.readAll().toStdString();
    ArraySource as((const byte*)key_source.data(), key_source.size(),
                                true, new Base64Decoder());
    RSA::PublicKey key;
    key.Load(as);

    return key;
}

//------------------------------------------------------------------------------

string Licence::loadToString(const QString &filePath) const
{
    QFile file(filePath);
    if (Q_UNLIKELY(!file.open(QIODevice::ReadOnly)))        //Check if we can read
        throw new NoLicenceException();
    QTextStream in(&file);
    std::string str = in.readAll().toStdString();
    return str;
}

//------------------------------------------------------------------------------

void Licence::verifityLicence(RSA::PublicKey publicKey,string licencePath, string sigPath) const
{
    //Read signed message
    string signedTxt;
    FileSource(licencePath.c_str(), true, new StringSink(signedTxt));
    string sig;
    FileSource(sigPath.c_str(), true, new StringSink(sig));

    RSASSA_PKCS1v15_SHA_Verifier verifier(publicKey);
    string combined(signedTxt);
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
        cout << err.what() << endl;
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

//    if(Q_UNLIKELY(_licenceBegin < lastDate || _licenceEnd < lastDate))
//        throw new UnvalidLiceneException;
}

//------------------------------------------------------------------------------

bool Licence::isLicenceExists()
{
    if(Q_LIKELY(QFile(_path.filePath("licence.dat")).exists()))
        return true;
    return false;
}


//------------------------------------------------------------------------------

void rotable::Licence::loadLicence(const QDir &path) try
{
    _path = path;
    if(Q_UNLIKELY(!isLicenceExists()))
        return;

    auto key = loadKeyFromFile();
    verifityLicence(key, path.filePath("licence.dat").toStdString(),
                    path.filePath("licence.crt").toStdString());
    auto licence = loadToString(path.filePath("licence.dat"));
    parseLicence(licence);

}
catch(NoPublKeyException){ }
catch(NoLicenceException){ }
catch(SignLicenceException){ }
catch(UnvalidLiceneException){ }
catch(UnvalidTimeException){ }

//------------------------------------------------------------------------------

QString Licence::getLicenceStatus()
{  
    //TODO: not needed now, add laetly
    return QString("aaa");
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
