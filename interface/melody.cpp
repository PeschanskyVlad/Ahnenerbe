#include <stdlib.h>
#include <stdio.h>

#include "melody.h"

Melody::Melody(unsigned char melodySize)
{
    if(melodySize > 99) return;

    melodyArr = new unsigned char[2*melodySize + 2];
    memset(melodyArr, melodySize + 2, 0);

    melodyArr[0] = '\1';
    melodyArr[1] = melodySize;

    this->melodySize = melodySize;
}

Melody::~Melody()
{
    delete [] melodyArr;
}

void Melody::setNote(unsigned char index, unsigned char noteNumber, unsigned char duration)
{
    if(index < 1 || index > melodySize) return;

    melodyArr[2*index] = noteNumber;
    melodyArr[2*index + 1] = duration;
}


void Melody::setMelodyFromFile(const char * melodyFileName)
{

}
