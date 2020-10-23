#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sfr_defs.h>

#define F_CPU 16000000UL  // 16 MHz (cpu freq used by the delay functions)
#include <stdlib.h>
#include "dwenguinoPrints.h"
#include "dwenguinoACC.h"
#include "dwenguinoDraw.h"
#define TIME_GAME 64
#define TOJUMP_VALUE 20
#define INCREMENT 2
#define DECREMENT 1
//global variable tijd and tick for use in interrupt
volatile int tijd=0;
volatile unsigned int timetick=0;
volatile BYTE starttime_increment=0;
//Reduce tijd every second
ISR(TIMER1_COMPA_vect){
  --tijd;
}

ISR(TIMER3_COMPA_vect){
  ++timetick;
}

//global variable dead to know when button is pushed
volatile BYTE dead=0;
//upper button
ISR(INT4_vect){
  dead=2;
}

//right button
ISR(INT7_vect){
  starttime_increment=INCREMENT;
}

//left button
ISR(INT5_vect){
  starttime_increment=DECREMENT;
}

int main(void){
  srand(time(0));

  SREG = SREG | _BWO(SREG_I); //set SREG_I of SREG on 1 //Global interrupt on
  //initialize timer1
  OCR1A = 15624;// amount of cycles per second
  TIMSK1 = TIMSK1 | _BWO(OCIE1A);
  TCCR1A = TCCR1A | _BWO(COM1A1);
  TCCR1B = TCCR1B | _BWO(WGM12) | _BWO(CS12) | _BWO(CS10); //CTC en prescaler 1024

  //initialize timer3
  OCR3A = 124;// amount of cycles per second
  TIMSK3 = TIMSK3 | _BWO(OCIE3A);
  TCCR3A = TCCR3A | _BWO(COM3A1);
  TCCR3B = TCCR3B | _BWO(WGM32) | _BWO(CS32) | _BWO(CS30); //CTC en prescaler 1024

  //interupt for buttons
  EICRB &= ~_BWO(ISC40);// set ISC40 of EICRB on 0
  EICRB = EICRB | _BWO(ISC41); //on falling edge
  EIMSK = EIMSK | _BWO(INT4) | _BWO(PINE5) | _BWO(PINE7); //INT4 gives interupt
  DDRE &= ~(_BWO(PINE4) | _BWO(PINE5) | _BWO(PINE7)); // PiN4 as input
  PORTE = PORTE | _BWO(PINE4) | _BWO(PINE5) | _BWO(PINE7); // pull-up resitance on

  //Activate display
  initLCD();
  backlightOn();
  clearLCD();
  //Set characters for platforms
  initCustomCharacters();

  //initialize variables
  unsigned int starttime=TIME_GAME;
  tijd=starttime;
  unsigned int tijdoffset=0;
  //initialize the lights
  DDRA=0b11111111;
  PORTA=0b00000000;

  //initialize accelerometer by putting it out of sleep mode
  initAccelerometer();

  //initialize board and platform arrays + variables
  unsigned int plaatsinarray=0;
  BYTE **bord=calloc(LCD_WIDTH<<1,sizeof(BYTE*));
  for(BYTE i=0;i<(LCD_WIDTH<<1);i++){
    bord[i]=calloc(LCD_HEIGHT,sizeof(BYTE));
  }
  BYTE *balkl=calloc(B_LENGTH,sizeof(BYTE));
  BYTE *balkr=calloc(B_LENGTH,sizeof(BYTE));

  //extra variables
  BYTE direction=0;
  unsigned int delayteller=0;
  BYTE bal=BALL_LEFT;
  BYTE arbteller=0;
  BYTE died=0;
  unsigned int score=0;
  int roll=0;
  int pitch=0;
  BYTE waittime=60;

  //initalize platforms to use
  initBalken(balkl,balkr);

  //Wait for start button pressed
  dead=1;
  while(dead==1){
    StartMessage();
    if(starttime_increment==DECREMENT && starttime>1){starttime--;}
    if(starttime_increment==INCREMENT){starttime++;}
    ClearPartLCD(1,11,6);
    TimeMessage(starttime);
    //wait 8 ms = 1 timetick, so button only counts one time
    if(starttime_increment>0){
      timetick=0;
      while(timetick<1){}
      starttime_increment=0;
    }
  }
  //calculate, because is constant once game loop starts
  unsigned int tijdDeling=(unsigned int)starttime>>3;
  tijd=starttime;//start game

  //Main game loop
  while(1){
    //go in loop at least once
    waittime=10;
    if(delayteller>0){
      //slowdown of game based on the roll
      while(timetick<waittime){
        roll=leesRoll();
        int npitch=leesPitch();
        if(npitch>TOJUMP_VALUE || npitch<-TOJUMP_VALUE){
          pitch=npitch;
        }
        if(roll>-95){
          waittime=(100+roll)>>2;
        }
        else{
          waittime=2;
        }
      }
    }
    unsigned int currenttick=timetick;
    //wait for timetick to end
    while(currenttick>=timetick){;}
    timetick=0;

    //increment amount of lamps if enough time has gone by
    if(tijd+tijdoffset<starttime){
      PORTA=(PORTA<<1)+1;
      tijdoffset=tijdoffset+tijdDeling;
    }

    //every 4 delayteller the main game loop starts (delayteller=ticks)
    if(delayteller%4==0){
      //fill bord with platforms
      int j=plaatsinarray;
      for(BYTE i=0;i<(LCD_WIDTH<<1);i++){
        if(j>B_LENGTH){
          j=0;
        }
        bord[i][0]=balkl[j];
        bord[i][1]=balkr[j];
        j++;
      }
      plaatsinarray++; //Platforms go down one place (so half a character)
      if(plaatsinarray>B_LENGTH){
        plaatsinarray=0;
      }

      //Board only changes every 4 ticks.
      DrawBoard(bord);

      //check if ball needs to move and icrement score if jumped
      if(pitch>TOJUMP_VALUE && bal==BALL_LEFT){
        bal=BALL_LEFT_AIR;
        direction=0;
        arbteller=1;
        score++;
      }
      if(pitch<(-TOJUMP_VALUE) && bal==BALL_RIGHT){
        bal=BALL_RIGHT_AIR;
        direction=1;
        arbteller=1;
        score++;
      }

      if(arbteller==0){
        if(bal==BALL_LEFT_AIR || bal==BALL_RIGHT_AIR){
          if(direction==0){bal++;}
          if(direction==1){bal--;}
        }
      }

      //Check if dead (time<1 or ball not on a platform)
      if((bal==BALL_LEFT && bord[0][0]==0)||(bal==BALL_RIGHT && bord[0][1]==0) || tijd<1 ){
        dead=1;
        GameOver(score, tijd);
        DrawBal(bal,delayteller, bord, direction);
        //reset
        tijdoffset=0;
        roll=0;
        plaatsinarray=0;
        direction=0;
        delayteller=0;
        bal=BALL_LEFT;
        arbteller=0;
        initBalken(balkl,balkr);
        died=1;
        score=0;
        pitch=0;

        //Stay on dead screen until button is pressed
        while(dead==1){ }
        tijd=starttime;
        dead=0;
        PORTA=0b00000000;
      }
      pitch=0;
    }


    arbteller=0;
    //DrawBal every tick
    DrawBal(bal,delayteller, bord, direction);


    //for game reset, so tick doesn't increment (note that died==1 only if a reset happened)
    if(died!=1){
      delayteller++;
    }
    else{died=0;}

    //wait for current timetick to end
    while(timetick<1){;}
    timetick=0;
  }
}
