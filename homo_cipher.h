#ifndef HOMO_CIPHER_H
#define HOMO_CIPHER_H
#include <QString>
#include <algorithm>
#include <QStringList>
#include <ctime>

class homo_cipher{
    std::size_t letter_entrance[26]; //times letter appears in the plainText

    std::vector <std::size_t> letter_key[26]; //numbers which are code letters

public:

    homo_cipher(); //Done

    homo_cipher(QString plainText); //generates key ||Done

    QString get_key(); //generates key representation in file  ||Done

    void set_key(QString keyText);

    QString encrypt(QString plainText);

    QString decrypt(QString outText);




};

#endif // HOMO_CIPHER_H
