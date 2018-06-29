#ifndef HOMO_CIPHER_H
#define HOMO_CIPHER_H
#include <QString>
#include <algorithm>
#include <QStringList>
#include <ctime>

class homo_cipher{
    std::size_t letter_entrance[26]; //times letter appears in the plain text

    std::vector <std::size_t> letter_key[26]; //substitution alphabet

public:

    homo_cipher(); 

    homo_cipher(QString plainText); //generates key 

    QString get_key(); //generates key representation in file 

    void set_key(QString keyText);  //key setter

    QString encrypt(QString plainText); 

    QString decrypt(QString outText);




};

#endif // HOMO_CIPHER_H
