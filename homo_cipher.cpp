#include "homo_cipher.h"

homo_cipher::homo_cipher()
{
   for (std::size_t i=0; i<26; ++i){
       letter_entrance[i]=0;
   }

}

    //сгенерировать n ключей для entrance[i]==n, записать их в letter_key[i] ==>QString
homo_cipher::homo_cipher(QString plainText){
    for (std::size_t i=0; i<26; ++i){
        letter_entrance[i]=0;
    }

    QString alphabet = "abcdefghijklmnopqrstuvwxyz";
    QString plainText_copy=plainText.toLower();
    std::size_t len = plainText_copy.length();

    std::srand(std::time(nullptr));

    for(QString::iterator i = plainText_copy.begin(); i < plainText_copy.end(); ++i)
        if(alphabet.indexOf(*i)==-1){
            plainText_copy.remove((*i));
            --i;
        }

    while(plainText_copy.length()){
        letter_entrance[alphabet.indexOf(plainText_copy[0])] = std::count(plainText_copy.begin(),plainText_copy.end(),plainText_copy[0]);
        plainText_copy.remove(plainText_copy[0]);
    }

    std::size_t entrance_sum=0;
    for (std::size_t i=0; i<26; ++i){
        entrance_sum+=letter_entrance[i];
    }

    std::vector <int> random_keys (entrance_sum);
    for(std::size_t i = 0; i < entrance_sum; ++i){
        int current;
        while(current = std::rand() % len, std::find(random_keys.begin(),random_keys.end(),current) != random_keys.end())
            ;
        random_keys[i] = current;
    }

    for (std::size_t i=0; i<26; ++i){
        for(std::size_t j=0; j < letter_entrance[i]; ++j){
            letter_key[i].push_back(random_keys[0]);
            random_keys.erase(random_keys.begin());
        }
    }
}


QString homo_cipher::get_key(){
    QString keyText;

    for (std::size_t i=0; i<26; ++i){
        keyText += QString("%1 ").arg(letter_entrance[i]);
        for (std::size_t j=0; j<letter_entrance[i]; ++j){
            keyText += QString(" %1").arg(letter_key[i][j]);
        }
        keyText += '\n';
    }

    return keyText;


}

void homo_cipher::set_key(QString keyText){
    QStringList lines = keyText.split("\n");

    for (std::size_t i=0; i<26; ++i){
        QStringList key_data = lines[i].split(" ", QString::SkipEmptyParts);
        for (QStringList::iterator j= key_data.begin(); j<key_data.end(); ++j){
            std::size_t num = static_cast<std::size_t>((*j).toInt());
            if(j==key_data.begin()){
                letter_entrance[i]= num;
            } else letter_key[i].push_back(num);
            }
        }
}

QString homo_cipher::encrypt(QString plainText){

    std::vector <std::size_t> letter_key_copy[26];
    for (std::size_t i=0; i<26; ++i){
        letter_key_copy[i]=letter_key[i];
    }

    QString alphabet = "abcdefghijklmnopqrstuvwxyz";
    QString number_alphabet ="123456789";

    QString plainText_copy=plainText.toLower();
    int len = plainText.length();

    QString output;

    for (int i=0; i < len; ++i ){
        int index = alphabet.indexOf(plainText_copy[i]);
        int number_index = number_alphabet.indexOf(plainText_copy[i]);
        if(index != -1){
           output += QString("%1 ").arg(letter_key_copy[index][0]);
           letter_key_copy[index].erase(letter_key_copy[index].begin());
        }
        else{
            if (number_index !=-1){
                output+= QString("%1").arg(plainText_copy[i]);
            } else
                output += QString(" %1 ").arg(plainText_copy[i]);
        }

    }

    output += '\n';

    return output;

}

QString homo_cipher::decrypt(QString outText){
    std::vector <std::size_t> letter_key_copy[26];
    for (std::size_t i=0; i<26; i++){
        letter_key_copy[i]=letter_key[i];
    }
    QString decrText;
    QString alphabet = "abcdefghijklmnopqrstuvwxyz";
    QStringList cipher_list = outText.split(" ");



    for (QStringList::iterator i=cipher_list.begin(); i<cipher_list.end(); ++i){
        bool ok;


        if(i != cipher_list.begin() && i <= (cipher_list.end()-3))
            if((*i).isEmpty() && (*(i+1)).isEmpty() && (*(i+2)).isEmpty()){
                (*i) = ' ';
                decrText+=(*i);
                i += 2;
            }
        int number =(*i).toInt(&ok);
        if (ok){
            bool find =0;
            for (std::size_t j=0; j<26; ++j){
                std::vector<std::size_t>::iterator index =std::find(letter_key_copy[j].begin(), letter_key_copy[j].end(),number);
                if (index != letter_key_copy[j].end()){
                    decrText += alphabet[j];
                     find =1;
                }
            }
            if (!find)
                decrText+=(*i)+ ' ';


        } else decrText+=(*i);

    }

    decrText += '\n';

    return decrText;
}



