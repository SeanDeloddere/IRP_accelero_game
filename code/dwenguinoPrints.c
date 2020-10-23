/*
 * dwenguinoPrints.c
 */
 #include "dwenguinoPrints.h"

 void StartMessage(){
   setCursorLCD(0, 0);
   appendCharToLCD('P');
   appendCharToLCD('R');
   appendCharToLCD('E');
   appendCharToLCD('S');
   appendCharToLCD('S');
   appendCharToLCD(' ');
   appendCharToLCD('B');
   appendCharToLCD('U');
   appendCharToLCD('T');
   appendCharToLCD('T');
   appendCharToLCD('O');
   appendCharToLCD('N');
 }

 void GameOver(unsigned int score, int tijd){
   setCursorLCD(0, 0);
   if(tijd>1){
     appendCharToLCD('Y');
     appendCharToLCD('O');
     appendCharToLCD('U');
     appendCharToLCD(' ');
     appendCharToLCD('D');
     appendCharToLCD('I');
     appendCharToLCD('E');
     appendCharToLCD('D');
     appendCharToLCD('!');
     appendCharToLCD(' ');
     appendCharToLCD(' ');
   }
   else{
     appendCharToLCD('T');
     appendCharToLCD('I');
     appendCharToLCD('M');
     appendCharToLCD('E');
     appendCharToLCD(' ');
     appendCharToLCD('U');
     appendCharToLCD('P');
     appendCharToLCD('!');
     appendCharToLCD('!');
     appendCharToLCD(' ');
     appendCharToLCD(' ');
   }
   setCursorLCD(1, 0);
   appendCharToLCD('S');
   appendCharToLCD('C');
   appendCharToLCD('O');
   appendCharToLCD('R');
   appendCharToLCD('E');
   appendCharToLCD(':');
   appendCharToLCD(' ');
   appendCharToLCD(' ');
   appendCharToLCD(' ');
   appendCharToLCD(' ');
   appendCharToLCD(' ');
   printIntToLCD(score, 1, 6);
 }

void TimeMessage(unsigned int starttime){
  setCursorLCD(1, 0);
  appendCharToLCD('T');
  appendCharToLCD('I');
  appendCharToLCD('M');
  appendCharToLCD('E');
  appendCharToLCD(' ');
  appendCharToLCD('G');
  appendCharToLCD('A');
  appendCharToLCD('M');
  appendCharToLCD('E');
  appendCharToLCD(':');
  appendCharToLCD(' ');
  appendIntToLCD(starttime);
}

void ClearPartLCD(BYTE line, BYTE start, BYTE length){
  if(start<LCD_WIDTH && line <=1){
    setCursorLCD(line, start);
    if(start+length>=LCD_WIDTH){length=LCD_WIDTH-start;}
    for(int i=0;i<length;i++){
      appendCharToLCD(' ');
    }
  }

}
