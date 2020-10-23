/*
 * dwenguinoACC.c
 */
 #include "dwenguinoACC.h"
// #include <stdlib.h>

void initAccelerometer(){
  //sent START condition
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
  //wait for START accepted
  while(!(TWCR & (1<<TWINT))){
    ;
  }

  //load adress accelerometer (SLA_W)
  TWDR= 0b11010000;
  //set TWINT = 1, start transmission
  TWCR = (1<<TWINT) | (1<<TWEN);
  while(!(TWCR & (1<<TWINT))){
    ;
  }
  //sent register Adress
  TWDR = 0x6B;
  TWCR = (1<<TWINT) | (1<<TWEN);
  while(!(TWCR & (1<<TWINT))){
    ;
  }
  //set register on 0
  TWDR = 0;
  TWCR = (1<<TWINT) | (1<<TWEN);
  while(!(TWCR & (1<<TWINT))){
    ;
  }
  //STOP condition
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

int read(int registerwaarde){
  TWCR=0;

  //sent START condition
  TWCR = _BWO(TWINT) | _BWO(TWSTA) | _BWO(TWEN);
  //wait for START accepted
  while(!(TWCR & _BWO(TWINT))){ ; }

  //load adress accelerometer (SLA_W)
  TWDR= 0b11010000;
  //set TWINT = 1, start transmission
  TWCR = _BWO(TWINT) | _BWO(TWEN);
  while(!(TWCR & _BWO(TWINT))){ ; }

  //sent register to read
  TWDR = registerwaarde;
  TWCR = _BWO(TWINT) | _BWO(TWEN);
  while(!(TWCR & _BWO(TWINT))){ ; }

  //sent repeatSTART condition
  TWCR = _BWO(TWINT) | _BWO(TWSTA) | _BWO(TWEN);
  while(!(TWCR & _BWO(TWINT))){ ; }

  //SLA_R
  TWDR= 0b11010001;
  TWCR = _BWO(TWINT) | _BWO(TWEN);
  while(!(TWCR & _BWO(TWINT))){ ; }

  TWDR = registerwaarde;
  TWCR = _BWO(TWINT) | _BWO(TWEN);
  while(!(TWCR & _BWO(TWINT))){ ; }

  //stop
  TWCR = _BWO(TWINT) | _BWO(TWEN) | _BWO(TWSTO);

  //return data in TWDR
  return TWDR;
}

int readX(){
  return read(0x3B);
}

int readx(){
  return read(0x3C);
}

int readY(){
  return read(0x3D);
}

int ready(){
  return read(0x3E);
}

int readZ(){
  return read(0x3F);
}

int readz(){
  return read(0x40);
}

int leesRoll(){
  int groteX=readX();
  int kleineX=readx();
  int groteZ=readZ();
  int kleineZ=readz();

  int Gx=((groteX<<8) | kleineX);
  int Gz=((groteZ<<8) | kleineZ);

  return (atan2(-Gx,Gz)*57.3);
}

int leesPitch(){
  int groteX=readX();
  int kleineX=readx();
  int groteY=readY();
  int kleineY=ready();
  int groteZ=readZ();
  int kleineZ=readz();

  long Gx=((groteX<<8) | kleineX);
  int Gy=((groteY<<8) | kleineY);
  long Gz=((groteZ<<8) | kleineZ);

  return(atan2(Gy,sqrt((Gx*Gx)+(Gz*Gz)))*57.3);
}
