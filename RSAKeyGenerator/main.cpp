#include <QCoreApplication>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
using namespace CryptoPP;

#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)

QString projectPath(QUOTEME(PWD_PRO));

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // InvertibleRSAFunction is used directly only because the private key
    // won't actually be used to perform any cryptographic operation;
    // otherwise, an appropriate typedef'ed type from rsa.h would have been used.
    AutoSeededRandomPool rng;
    InvertibleRSAFunction privkey;
    privkey.Initialize(rng, 2048);

    // With the current version of Crypto++, MessageEnd() needs to be called
    // explicitly because Base64Encoder doesn't flush its buffer on destruction.
    Base64Encoder privkeysink(new FileSink(QString(projectPath+"/../privkey.txt").toStdString().c_str()));
    privkey.DEREncode(privkeysink);
    privkeysink.MessageEnd();

    // Suppose we want to store the public key separately,
    // possibly because we will be sending the public key to a third party.
    RSAFunction pubkey(privkey);

    Base64Encoder pubkeysink(new FileSink(QString(projectPath+"/../publkey.txt").toStdString().c_str()));
    pubkey.DEREncode(pubkeysink);
    pubkeysink.MessageEnd();

    return a.exec();
}
