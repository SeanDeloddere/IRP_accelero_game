/*
 * dwenguinoDraw.c
 */

#include "dwenguinoDraw.h"


void DrawBoard(BYTE** bord){
   //m for left and right side
   BYTE m=1;
   //l for right and left side
   for (BYTE l=0;l<2;l++){
     //i for 16 characters on one line
     for(BYTE i=0;i<16;i++){
       //4 options: empty, full, only top half or only bottom half is filled
       if(bord[i*2][l]==0 && bord[(i*2)+1][l]==0){
         printCharToLCD(' ' ,m , 15-i);
       }
       else if(bord[i*2][l]==1 && bord[(i*2)+1][l]==1){
         printCharToLCD(0+l*3 , m, 15-i);
       }
       else if(bord[i*2][l]==1 && bord[(i*2)+1][l]==0){
         printCharToLCD(2+l*3 , m, 15-i);
       }
       else if(bord[i*2][l]==0 && bord[(i*2)+1][l]==1){
         printCharToLCD(1+l*3 , m, 15-i);
       }
     }
     m--;
   }
 }

void DrawBal(BYTE ball,int delayt, BYTE** bord,BYTE direction){
   //every if is slightly different to draw the ball, so this is not split into functions.
   //Every dataLCD is present, so the character that gets created can easily be viewed in the code.
   if(ball==BALL_LEFT){
     commandLCD(0x70);
     dataLCD(0b00000);
     dataLCD(0b00000);
     dataLCD(0b00000);
     dataLCD(0b00000);
     dataLCD(0b00011);
     dataLCD(0b00011);
     if(bord[0][0]==0 && bord[1][0]==0){
       dataLCD(0b00000);
       dataLCD(0b00000);
     }
     else if(bord[0][0]==1 && bord[1][0]==0){
       dataLCD(0b00111);
       dataLCD(0b00111);
     }
     else if(bord[0][0]==0 && bord[1][0]==1){
       dataLCD(0b11100);
       dataLCD(0b11100);
     }
     else { //if  bord[0][0]==1 && bord[1][0]==1
       dataLCD(0b11111);
       dataLCD(0b11111);
     }
     printCharToLCD(6,1 ,15 );
   }
   else if(ball==BALL_RIGHT){
     commandLCD(0x70);
     if(bord[0][1]==0 && bord[1][1]==0){
       dataLCD(0b00000);
       dataLCD(0b00000);
     }
     else if(bord[0][1]==1 && bord[1][1]==0){
       dataLCD(0b00111);
       dataLCD(0b00111);
     }
     else if(bord[0][1]==0 && bord[1][1]==1){
       dataLCD(0b11100);
       dataLCD(0b11100);
     }
     else if(bord[0][1]==1 && bord[1][1]==1){
       dataLCD(0b11111);
       dataLCD(0b11111);
     }
     dataLCD(0b00011);
     dataLCD(0b00011);
     dataLCD(0b00000);
     dataLCD(0b00000);
     dataLCD(0b00000);
     dataLCD(0b00000);
     printCharToLCD(6,0 ,15 );
   }

   else if(ball==BALL_LEFT_AIR){
     commandLCD(0x70);
     if(delayt%4+3*direction==3){
       dataLCD(0b11000);
       dataLCD(0b11000);
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b00000);
     } else if(delayt%4+direction==2){
       dataLCD(0b00000);
       dataLCD(0b11000);
       dataLCD(0b11000);
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b00000);
     }else if(delayt%4-direction==1){
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b01100);
       dataLCD(0b01100);
       dataLCD(0b00000);
       dataLCD(0b00000);
     }else{
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b00110);
       dataLCD(0b00110);
       dataLCD(0b00000);
     }

     if(bord[0][0]==0 && bord[1][0]==0){
       dataLCD(0b00000);
       dataLCD(0b00000);
     }
     else if(bord[0][0]==1 && bord[1][0]==0){
       dataLCD(0b00111);
       dataLCD(0b00111);
     }
     else if(bord[0][0]==0 && bord[1][0]==1){
       dataLCD(0b11100);
       dataLCD(0b11100);
     }
     else if(bord[0][0]==1 && bord[1][0]==1){
       dataLCD(0b11111);
       dataLCD(0b11111);
     }
     printCharToLCD(6,1 ,15);
   }
   else if(ball==BALL_RIGHT_AIR){
     commandLCD(0x70);
     if(bord[0][1]==0 && bord[1][1]==0){
       dataLCD(0b00000);
       dataLCD(0b00000);
     }
     else if(bord[0][1]==1 && bord[1][1]==0){
       dataLCD(0b00111);
       dataLCD(0b00111);
     }
     else if(bord[0][1]==0 && bord[1][1]==1){
       dataLCD(0b11100);
       dataLCD(0b11100);
     }
     else if(bord[0][1]==1 && bord[1][1]==1){
       dataLCD(0b11111);
       dataLCD(0b11111);
     }
     if(delayt%4+3*direction==3){
       dataLCD(0b00000);
       dataLCD(0b00110);
       dataLCD(0b00110);
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b00000);

     } else if(delayt%4+direction==2){
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b01100);
       dataLCD(0b01100);
       dataLCD(0b00000);
       dataLCD(0b00000);
     } else if (delayt%4-direction==1){
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b11000);
       dataLCD(0b11000);
       dataLCD(0b00000);
     } else{
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b00000);
       dataLCD(0b11000);
       dataLCD(0b11000);
     }
     printCharToLCD(6,0 ,15);
   }
 }

int EmptyPart(BYTE r3,int i, BYTE* balkl, BYTE* balkr){
  //Note that the random value r3 cannot be generated here, because initBalken needs this value
  switch(r3){
    case 0:
    balkl[i]=0;
    balkr[i]=0;
    return i+1;
    break;

    case 1:
    balkl[i]=0;
    balkl[i+1]=0;
    balkr[i]=0;
    balkr[i+1]=0;
    return i+2;
    break;

    default:
    return i;
  }
}

void fillBalken(unsigned int i, BYTE side, unsigned int size, BYTE* balkl,BYTE* balkr){
  BYTE sidel=1;
  BYTE sider=1;
  switch(side){
    case 0:
    sider=0;
    break;
    case 1:
    sidel=0;
    break;
    case 2:
    break;
  }
  for (unsigned int j=i;j<i+size;j++){
    balkl[j]=sidel;
    balkr[j]=sider;
  }
}

void initBalken(BYTE *balkl, BYTE *balkr){
   BYTE counterl=0;
   BYTE counterr=0;

   //start platform
   fillBalken(0,0,4,balkl,balkr);

   BYTE e1=rand()%9;
   BYTE e2=rand()%3;
   BYTE e3=rand()%3;

   //end platform, so no check for end of array needs to be done.
   fillBalken(B_LENGTH-6,2,6,balkl,balkr);

   for(unsigned int i=4;i<B_LENGTH-6;){
     BYTE r1=e1;
     BYTE r2=e2;
     BYTE r3=e3;
     e1=rand()%9;
     e2=rand()%3;
     e3=rand()%3;

     if((r1<4 || counterl==2) && (counterr!=2)){
       counterl=0;
       counterr++;
       fillBalken(i,1,3,balkl,balkr);
       i=i+3;
       switch(r2){
         case 0:
         fillBalken(i,1,1,balkl,balkr);
         i=i+1;
         break;

         case 1:
         fillBalken(i,1,2,balkl,balkr);
         i=i+2;
         break;

         default:
         break;
       }
       if(e1>3 || counterr==2){
         i=EmptyPart(r3,i,balkl,balkr);
       }
     }
     else if((r1>3 && r1<8) || (counterr==2)){
       counterr=0;
       counterl++;
       fillBalken(i,0,3,balkl,balkr);
       i=i+3;
       switch(r2){
         case 0:
         fillBalken(i,0,1,balkl,balkr);
         i=i+1;
         break;

         case 1:
         fillBalken(i,0,2,balkl,balkr);
         i=i+2;
         break;

         default:
         break;
       }
       if((!(e1>3 && e1<8)) || (counterl==2)){
         i=EmptyPart(r3,i,balkl,balkr);
       }
     }
     else{
       counterr++;
       counterl++;
       fillBalken(i,2,3,balkl,balkr);
       i=i+3;
       switch(r2){
         break;
         case 0:
         fillBalken(i,2,1,balkl,balkr);
         i=i+1;
         break;

         case 1:
         fillBalken(i,2,1,balkl,balkr);
         i=i+2;
         break;

         default:
         break;
       }
     }
   }
 }

void initCustomCharacters(){
   //only one commandLCD needed, because it will automatically increment

   //character 0
   commandLCD(0x40);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b11111);
   dataLCD(0b11111);

   //character 1
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b11100);
   dataLCD(0b11100);

   //character 2
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00111);
   dataLCD(0b00111);

   //character 3
   dataLCD(0b11111);
   dataLCD(0b11111);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);

   //character 4
   dataLCD(0b11100);
   dataLCD(0b11100);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);

   //character 5
   dataLCD(0b00111);
   dataLCD(0b00111);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
   dataLCD(0b00000);
 }
