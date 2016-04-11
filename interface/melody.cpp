#include <stdlib.h>
#include <stdio.h>
#include "melody.h"



Melody::Melody(const char * melodyFileName)
{
    /*

    FILE * file = fopen(melodyFileName, "r");
    char tempChar;
    fscanf(file,"%d",&tempChar);
    melodySize=tempChar;


    if(melodySize > 99) return;

    melodyArr = new unsigned char[2*melodySize + 2];

    memset(melodyArr, melodySize + 2, 0);

    melodyArr[0] = '\1';
    for(int i = 2; !feof(file); i++){
        fscanf(file,"%d",&tempChar);
        melodyArr[i] = tempChar;

    }

    fclose(file);
*/

}

Melody::~Melody()
{
    delete [] melodyArr;
}


/*
void Melody::setNote(unsigned char index, unsigned char noteNumber, unsigned char duration)
{
    if(index < 1 || index > melodySize) return;

    melodyArr[2*index] = noteNumber;
    melodyArr[2*index + 1] = duration;
}
*/
/*
void Melody::setMelodyFromFile(const char * melodyFileName)
{
    FILE * file = fopen(melodyFileName, "r");


    for(int i = 2; !feof(file)){

    }


}*/
