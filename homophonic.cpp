#include "homophonic.h"



//This reads from FileWithKey
//results are written in KeyArray

void readKey(FILE *FileWithKey,key KeyArray)
{
    int i,j,n;

    for(i=0;i<26;i++){
        fscanf(FileWithKey,"%d",&n);
        KeyArray[i].n=n;
        KeyArray[i].numbers=(char (*)[20])calloc(n,sizeof(num));
        for(j=0;j<n;j++)
            fscanf(FileWithKey,"%s",KeyArray[i].numbers[j]);
    }
}

//returns the pointer to a string of nums used to replace a particular character. picked randomly.
char *get_Number(char letter,key KeyArray)
{
    int tempr;
    char *result;
    tempr=rand();
    tempr%=KeyArray[letter-'a'].n;
    result=(char*)KeyArray[letter-'a'].numbers[tempr];
    return(result);
}

//performs linear search to return correspondng character, else returns 0.
char getLetter(char *number,key KeyArray)
{
    int i,j;

    for(i=0;i<26;i++)
        for(j=0;j<KeyArray[i].n;j++)
            if(!(strcmp(number,KeyArray[i].numbers[j])))
                return(i+'a');

    return('\0');

}

void generateKey(const char* plain_text,key KeyArray)
{

}

//This does a homophonic encryption, one letter is substituted with any of the numbers or combination of numbers at random
void encryptFile(char * plain_name, char *out_name)
{   key KeyArray;
    FILE *PlainTextFile;

    if((PlainTextFile=fopen(plain_name,"r"))==NULL){
        fprintf(stderr,"Error opening input file.\n");
        exit(1);
    }

    char * plain_text = new char ();
    generateKey();
    int StreamingChar;


    while((StreamingChar=getc(PlainTextFile))!=EOF){

        if(isalpha(StreamingChar)){

            fprintf(En_Dec_Text_File,"%s ",get_Number(tolower(StreamingChar),KeyArray)); //get number from key array and write to file with encrpted text
     //all letters are coverted to lower case for the sake of convenience
        }
        else if(isdigit(StreamingChar)){

            fprintf(En_Dec_Text_File,"{%c}",StreamingChar); //if digit, directly write to file
        }
        else if(StreamingChar=='\n'){

            fprintf(En_Dec_Text_File," -1\n"); // mark of a new line
        }

        else{

            fprintf(En_Dec_Text_File,"%c",StreamingChar);}
    }
}


// decryptFile decrypts PlainTextFile and writes back to En_Dec_Text_File


void decryptFile(FILE *PlainTextFile, FILE *En_Dec_Text_File, key KeyArray)
{
    int StreamingChar,position,Lcharacter,Xcharacter;
    char BLOCK[100],Pcharacter;

    while((StreamingChar=getc(PlainTextFile))!=EOF){

        position=0;

        if(isdigit(StreamingChar)){                       //decrytpting a stream of encrypted text
            BLOCK[position++]=StreamingChar;
            StreamingChar=getc(PlainTextFile);

            while((isdigit(StreamingChar))&&(StreamingChar!=EOF)){
                BLOCK[position++]=StreamingChar;
                StreamingChar=getc(PlainTextFile);
            }

        if(StreamingChar!=' ')
                ungetc(StreamingChar,PlainTextFile); // tokenising to get next character, whitespaces are separators between characters.

        BLOCK[position]='\0';

        Pcharacter=getLetter(BLOCK,KeyArray);

        if(Pcharacter) putc(Pcharacter,En_Dec_Text_File);

        else fprintf(En_Dec_Text_File,"Can't Find!");

        }

        else if(StreamingChar=='-'){                      //check for new line and end of line
            Lcharacter=getc(PlainTextFile);
            if(Lcharacter=='1'){
                Xcharacter=getc(PlainTextFile);
                if(Xcharacter=='\n'){
                    fprintf(En_Dec_Text_File,"\n");
                    continue;
                }
                else {
                    ungetc(Xcharacter,PlainTextFile);
                    ungetc(Lcharacter,PlainTextFile);
                }
            }
            else{
                ungetc(Lcharacter,PlainTextFile);
                putc(StreamingChar,En_Dec_Text_File);
                continue;
            }
            putc(StreamingChar,En_Dec_Text_File);
        }

        else if(StreamingChar=='{'){                //any plaintext digit is denoted in {} as a character, recognises that here.
            Lcharacter=getc(PlainTextFile);
            if(isdigit(Lcharacter)){
                Xcharacter=getc(PlainTextFile);
                if(Xcharacter=='}'){
                    putc(Lcharacter,En_Dec_Text_File); //puts this in the output file which will now contain the decrypted text
                    continue;
                }
                else{
                    ungetc(Xcharacter,PlainTextFile);
                    ungetc(Lcharacter,PlainTextFile);
                }
            }
            else {
                ungetc(Lcharacter,PlainTextFile);
                putc(StreamingChar,En_Dec_Text_File);
                continue;
            }
            putc(StreamingChar,En_Dec_Text_File);
        }

        else putc(StreamingChar,En_Dec_Text_File);
    }


}
