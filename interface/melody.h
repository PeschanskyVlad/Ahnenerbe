#ifndef MELODY_H
#define MELODY_H


class Melody
{
    unsigned char melodySize;
    unsigned char * melodyArr;
    Melody();
public:
    Melody(unsigned char melodySize);
    ~Melody();

    void setNote(unsigned char index, unsigned char frequency, unsigned char duration);
    void Melody::setMelodyFromFile(const char * melodyFileName);
};

#endif // MELODY_H
