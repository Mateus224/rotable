#include "licence.h"

using namespace std;
using namespace rotable;

#include <QByteArray>

//------------------------------------------------------------------------------

rotable::Licence::Licence()
{
    //TODO: add path to licence
    loadLicence("");
}

//------------------------------------------------------------------------------

string rotable::Licence::loadKeyFromFile() const
{
    //Open file from resource
    QFile file(":/publkey.txt");
    if (Q_UNLIKELY(!file.open(QIODevice::ReadOnly)))        //Check if we can read
        throw new NoPublKeyException();                     //Something is  wrong with key
    QByteArray blob = file.readAll();                       //Read file
    return blob.toStdString();                              // Convert to string and return
}

//------------------------------------------------------------------------------

string Licence::loadLicenceFromFile() const
{

}

//------------------------------------------------------------------------------

bool Licence::verifityLicence(string publicKey) const
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

}

//------------------------------------------------------------------------------

void Licence::disconnectTable()
{
    --_connectedTable;
}

//------------------------------------------------------------------------------
