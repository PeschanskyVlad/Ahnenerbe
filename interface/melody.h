#ifndef MELODY_H
#define MELODY_H


class Melody
{
    unsigned char melodySize;
    unsigned char * melodyArr;
    Melody();
public:
    Melody(const char * melodyFileName);
    ~Melody();

  //  void setNote(unsigned char index, unsigned char frequency, unsigned char duration);
  //  void Melody::setMelodyFromFile(const char * melodyFileName);
};

#endif // MELODY_H
