/*
Дерп-Тамагочи v. 1.0
====================
Автор: MASTER TIME
Все права принадлежат Хасбро, весь мир принадлежит Хасбро!
==========================================================
Функции:
Лежачая поза Дерпи, пони моргает, комната, режим ночи, возможность кормить маффинами, возможность гладить, 
возможность спать. Внешний таймер голода (НАКОНЕЦ-ТО!), встроенный таймер голода, отключение голода, отключение побега.
Если Дерпи долго "дразнить" маффином, она начнёт что-то подозревать)).
Если Дерпи гладить, она довольно щурится)).
Шкала голода, настройки, Дерпи убегает (когда голодает), возможность перезапуска.
Добавлены короткие фразочки :3
*/
#include "U8glib.h" // Библиотека для экрана
#include <Wire.h> // Какая-то непонятная хрень, вроде библиотека на провода...
#include <DS1307RTC.h> // Библиотека для часов реального времени
#include <TimeLib.h> // Ещё одна библиотека для часов реального времени
#include "rus7x13.h" // Патриотический шрифт
#include "rus6x12.h" // Ещё один патриотический шрифт

U8GLIB_ST7920_128X64_1X u8g(40, 42, 44); 
// Контакты "A" "B" "C", соответственно с схемой (можно заменить на другие цифровые)

#define soundPIN 35
//Контакт "D" (на схеме) - Пьезоэлемент или динамик для вывода звука. (можно заменить на другой цифровой)

#define GOLODOVKA 2 
// сколько едениц голода отнимается в час (при использовании внешнего таймера, на базе часов реального времени)


// Ниже очень страшные вещи, которые лучше не трогать...
byte HAPPY=10;
byte FOOD=100;
byte EEMEM FOODsave;
byte DERPx=65;
byte EEMEM DERPxsave;
byte DERPy=53;
byte glaza;
byte DERPxH;
byte DERPyH;
byte OKNOx=25;
byte OKNOy=3;
byte muffinX=7;
byte muffinY=7;
byte cursorX;
byte cursorY;
byte rukaX;
byte FRAZ;
byte EEMEM FRAZsave;
byte rukaY;
byte love=1;
bool END;
bool END2;
bool switchGLAZA;
bool direct1=1;
byte random1;
boolean grom;
byte RAZNOST;
byte SLEEP;
byte hmmm;
byte HOUR;
byte MIN;
byte EEMEM MINsave;
byte SKALA;
byte SKALAON;
byte EEMEM SKALAONsave;
byte realDAY;
byte Rtime;
bool sost;
int switchFRAZ;
bool nya;
byte MOOD; //4 - восторг, 3 - улыбка, 2 - серьёзная, 1 - грустная 0 - спокойная
boolean storm;
boolean night;
byte select13menu=1;
boolean up;
boolean down;
boolean left;
boolean right;
bool FOODterm;
bool select13item;
bool animation;
byte golodovka;
byte select13;
byte EEMEM TIMERsetsave;
byte TIMERset;
long REALtime11;
bool RESTART;
int position13;
static unsigned char wallpaper[] {
0x00,0x04,0x08,0x04,0x00,0x80,0x40,0x80,0x00,0x04,0x08,0x04,0x00,0x80,0x40,0x80,0x00,0x04,0x08,
0x04,0x00,0x80,0x40,0x80,0x00,0x04,0x08,0x04,0x00,0x80,0x40,0x80,0x00,0x04,0x08,0x04,0x00,0x80,
0x40,0x80,0x00,0xFF,0xFF,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,
0x00,0x00,0x00,0xFF,0x00,0x00,0x00
};
void draw() 
{


  if(night==1){
  u8g.drawBox(0,0,128,64); 
  u8g.setColorIndex(0);  
  }else{
   storm=0;  
  }
u8g.drawXBM( 0, 0, 8, 64, wallpaper);  
u8g.drawXBM( 8, 0, 8, 64, wallpaper);  
u8g.drawXBM( 16, 0, 8, 64, wallpaper);   
u8g.drawXBM( 24, 0, 8, 64, wallpaper); 
u8g.drawXBM( 32, 0, 8, 64, wallpaper); 
u8g.drawXBM( 40, 0, 8, 64, wallpaper); 
u8g.drawXBM( 48, 0, 8, 64, wallpaper); 
u8g.drawXBM( 56, 0, 8, 64, wallpaper); 
u8g.drawXBM( 64, 0, 8, 64, wallpaper);  
u8g.drawXBM( 72, 0, 8, 64, wallpaper); 
u8g.drawXBM( 80, 0, 8, 64, wallpaper); 
u8g.drawXBM( 88, 0, 8, 64, wallpaper); 
u8g.drawXBM( 96, 0, 8, 64, wallpaper); 
u8g.drawXBM( 104, 0, 8, 64, wallpaper); 
u8g.drawXBM( 112, 0, 8, 64, wallpaper); 
u8g.drawXBM( 120, 0, 8, 64, wallpaper); 



if(storm==1){
     static unsigned long timer = millis(); 
              if (millis() - timer > 300) {
               random1=random(1,10);             
               timer = millis();     
                 } 
if(night==1){
  if (random1==1){
   if (grom==0){
     tone(35, 50, 100); 
     if (love==0 && SLEEP<5){
      glaza=1;
      SLEEP=0;
     }     
     grom=1;
   }else if (grom==1){
u8g.setColorIndex(0); 
u8g.drawBox(OKNOx,OKNOy,24,31); 
u8g.setColorIndex(1); 
u8g.drawRFrame(OKNOx,OKNOy,24,31,0);
u8g.drawLine(OKNOx,OKNOy+7,OKNOx+23,OKNOy+7); 
u8g.drawLine(OKNOx,OKNOy+14,OKNOx+23,OKNOy+14); 
u8g.drawLine(OKNOx,OKNOy+21,OKNOx+23,OKNOy+21);
u8g.drawBox(OKNOx+11,OKNOy,2,29); 
u8g.drawBox(OKNOx,OKNOy+28,24,3); 
   } 
}else{
u8g.setColorIndex(1); 
u8g.drawBox(OKNOx,OKNOy,24,31); 
u8g.setColorIndex(1); 
grom=0;
}
}else{
    if (random1==1){
   if (grom==0){
     tone(35, 50, 100); 
     grom=1;
   }else if (grom==1){
u8g.setColorIndex(1); 
u8g.drawBox(OKNOx,OKNOy,24,31); 
u8g.setColorIndex(0); 
u8g.drawLine(OKNOx,OKNOy+7,OKNOx+23,OKNOy+7); 
u8g.drawLine(OKNOx,OKNOy+14,OKNOx+23,OKNOy+14); 
u8g.drawLine(OKNOx,OKNOy+21,OKNOx+23,OKNOy+21);
u8g.drawBox(OKNOx+11,OKNOy,2,29);
u8g.drawRFrame(OKNOx,OKNOy,24,31,0); 
u8g.drawBox(OKNOx,OKNOy+28,24,3); 
u8g.setColorIndex(1); 
   } 
}else{
u8g.setColorIndex(0); 
u8g.drawBox(OKNOx,OKNOy,24,31); 
u8g.setColorIndex(1); 
u8g.drawRFrame(OKNOx,OKNOy,24,31,0);
u8g.drawLine(OKNOx,OKNOy+7,OKNOx+23,OKNOy+7); 
u8g.drawLine(OKNOx,OKNOy+14,OKNOx+23,OKNOy+14); 
u8g.drawLine(OKNOx,OKNOy+21,OKNOx+23,OKNOy+21);
u8g.drawBox(OKNOx+11,OKNOy,2,29); 
u8g.drawBox(OKNOx,OKNOy+28,24,3); 
grom=0;
}
}                 
}
if (night==0){
  u8g.setColorIndex(0); 
u8g.drawBox(OKNOx,OKNOy,24,31); 
u8g.setColorIndex(1); 
u8g.drawRFrame(OKNOx,OKNOy,24,31,0);
u8g.drawLine(OKNOx,OKNOy+7,OKNOx+23,OKNOy+7); 
u8g.drawLine(OKNOx,OKNOy+14,OKNOx+23,OKNOy+14); 
u8g.drawLine(OKNOx,OKNOy+21,OKNOx+23,OKNOy+21);
u8g.drawBox(OKNOx+11,OKNOy,2,29); 
u8g.drawBox(OKNOx,OKNOy+28,24,3); 
}


      
    
             


 
//лежит влево
u8g.setColorIndex(0); 
u8g.drawBox(DERPx-9,DERPy-13,25,12); 
u8g.drawBox(DERPx-15,DERPy-7,25,7); 
u8g.drawBox(DERPx-17,DERPy-5,3,5); 
u8g.drawBox(DERPx+11,DERPy-11,8,7);  
u8g.drawLine(DERPx+16,DERPy-12,DERPx+16,DERPy-4); 
u8g.drawLine(DERPx+19,DERPy-7,DERPx+19,DERPy-8);   
u8g.setColorIndex(1); 




u8g.drawLine(DERPx-2,DERPy,DERPx+3,DERPy); 
u8g.drawLine(DERPx+4,DERPy-1,DERPx+9,DERPy-1); 
u8g.drawLine(DERPx-3,DERPy-1,DERPx-8,DERPy-1); 
u8g.drawLine(DERPx-9,DERPy,DERPx-15,DERPy); 
u8g.drawLine(DERPx-15,DERPy-1,DERPx-18,DERPy-1); 
u8g.drawLine(DERPx+10,DERPy-2,DERPx+15,DERPy-2); 
u8g.drawLine(DERPx-18,DERPy-1,DERPx-18,DERPy-4); 
u8g.drawLine(DERPx-15,DERPy-2,DERPx-15,DERPy-3); 
u8g.drawLine(DERPx-3,DERPy-2,DERPx-3,DERPy-3); 
u8g.drawLine(DERPx+10,DERPy-5,DERPx+10,DERPy-11); 
u8g.drawLine(DERPx-15,DERPy-4,DERPx-13,DERPy-6);  
u8g.drawLine(DERPx-13,DERPy-6,DERPx-7,DERPy-6);  
u8g.drawLine(DERPx-18,DERPy-4,DERPx-15,DERPy-7);  
u8g.drawLine(DERPx-15,DERPy-7,DERPx-9,DERPy-7); 
u8g.drawLine(DERPx-10,DERPy-8,DERPx-10,DERPy-11);  
u8g.drawLine(DERPx-6,DERPy-5,DERPx-5,DERPy-5); 
u8g.drawLine(DERPx-2,DERPy-4,DERPx-2,DERPy-5); 
u8g.drawLine(DERPx-2,DERPy-8,DERPx-2,DERPy-10); 
u8g.drawLine(DERPx,DERPy-6,DERPx+3,DERPy-6); 
u8g.drawLine(DERPx+1,DERPy-10,DERPx+3,DERPy-10); 
u8g.drawLine(DERPx+2,DERPy-8,DERPx+3,DERPy-8); 
u8g.drawLine(DERPx+4,DERPy-9,DERPx+6,DERPy-9); 
u8g.drawLine(DERPx+6,DERPy-10,DERPx+6,DERPy-12); 
u8g.drawLine(DERPx+4,DERPy-11,DERPx+5,DERPy-11); 
u8g.drawLine(DERPx+15,DERPy-3,DERPx+16,DERPy-3); 
u8g.drawLine(DERPx+18,DERPy-5,DERPx+18,DERPy-7); 
u8g.drawLine(DERPx+20,DERPy-5,DERPx+20,DERPy-8); 
u8g.drawLine(DERPx+18,DERPy-11,DERPx+16,DERPy-13); 
u8g.drawLine(DERPx+19,DERPy-9,DERPx+19,DERPy-10); 
u8g.drawLine(DERPx+17,DERPy-14,DERPx+18,DERPy-14); 
u8g.drawLine(DERPx+17,DERPy-15,DERPx+13,DERPy-15); 
u8g.drawLine(DERPx+12,DERPy-14,DERPx+10,DERPy-14); 
u8g.drawLine(DERPx+10,DERPy-15,DERPx+10,DERPy-13); 
u8g.drawLine(DERPx+10,DERPy-13,DERPx+8,DERPy-13); 
u8g.drawLine(DERPx+7,DERPy-14,DERPx+3,DERPy-14); 
u8g.drawLine(DERPx+5,DERPy-13,DERPx,DERPy-13); 
u8g.drawLine(DERPx+2,DERPy-12,DERPx-1,DERPy-12); 
u8g.drawPixel( DERPx+10, DERPy-3); 
u8g.drawPixel( DERPx+9, DERPy-4); 
u8g.drawPixel( DERPx+9, DERPy-7); 
u8g.drawPixel( DERPx+7, DERPy-7); 
u8g.drawPixel( DERPx+4, DERPy-7); 
u8g.drawPixel( DERPx+4, DERPy-5); 
u8g.drawPixel( DERPx+9, DERPy-9); 
u8g.drawPixel( DERPx+8, DERPy-10);
u8g.drawPixel( DERPx-3, DERPy-6);
u8g.drawPixel( DERPx-1, DERPy-5); 
u8g.drawPixel( DERPx-1, DERPy-7);  
u8g.drawPixel( DERPx-1, DERPy-11);    
u8g.drawPixel( DERPx+3, DERPy-7); 
u8g.drawPixel( DERPx+5, DERPy-8); 
u8g.drawPixel( DERPx+17, DERPy-4);  
u8g.drawPixel( DERPx+17, DERPy-8);
u8g.drawPixel( DERPx+19, DERPy-6);  
u8g.drawPixel( DERPx+15, DERPy-13);    
u8g.drawPixel( DERPx+9, DERPy-12);   


DERPxH=DERPx-8;
DERPyH=DERPy-16;
//голова влево
u8g.setColorIndex(0); 
u8g.drawBox(DERPxH,DERPyH-20,9,25); 
u8g.drawBox(DERPxH-4,DERPyH-19,15,19); 
u8g.drawBox(DERPxH-11,DERPyH-19,5,2);
u8g.drawBox(DERPxH-6,DERPyH-23,9,13);
u8g.drawBox(DERPxH-9,DERPyH-17,3,4);
u8g.drawBox(DERPxH-11,DERPyH-14,2,2);
u8g.drawPixel(DERPxH-7, DERPyH-23);
u8g.drawBox(DERPxH+3,DERPyH-22,4,2);
u8g.drawBox(DERPxH+11,DERPyH-15,2,13);
u8g.drawLine(DERPxH-5,DERPyH-3,DERPxH-5,DERPyH-6);    
u8g.setColorIndex(1); 
u8g.drawLine(DERPxH+7,DERPyH+4,DERPxH+5,DERPyH+2); 
u8g.drawLine(DERPxH+7,DERPyH+4,DERPxH+9,DERPyH+4); 
u8g.drawPixel( DERPxH, DERPyH+1); 
u8g.drawLine(DERPxH-1,DERPyH+2,DERPxH-1,DERPyH+4);
u8g.drawLine(DERPxH+8,DERPyH+3,DERPxH+8,DERPyH+1); 
u8g.drawLine(DERPxH+5,DERPyH+1,DERPxH+5,DERPyH); 
u8g.drawLine(DERPxH-2,DERPyH,DERPxH+2,DERPyH); 
u8g.drawLine(DERPxH+2,DERPyH,DERPxH+8,DERPyH-6); 
u8g.drawPixel(DERPxH-3, DERPyH-1); 
u8g.drawLine(DERPxH-4,DERPyH-1,DERPxH-6,DERPyH-3); 
u8g.drawLine(DERPxH-6,DERPyH-3,DERPxH-6,DERPyH-6); 
u8g.drawLine(DERPxH-5,DERPyH-7,DERPxH-5,DERPyH-10); 
u8g.drawLine(DERPxH-5,DERPyH-11,DERPxH-8,DERPyH-11); 
u8g.drawLine(DERPxH,DERPyH-11,DERPxH-1,DERPyH-11); 
u8g.drawLine(DERPxH+9,DERPyH,DERPxH+13,DERPyH-4); 
u8g.drawLine(DERPxH+13,DERPyH-4,DERPxH+13,DERPyH-10); 
u8g.drawLine(DERPxH+12,DERPyH-10,DERPxH+12,DERPyH-15); 
u8g.drawPixel(DERPxH+11, DERPyH-16); 
u8g.drawLine(DERPxH+10,DERPyH-17,DERPxH+7,DERPyH-17); 
u8g.drawLine(DERPxH+7,DERPyH-17,DERPxH+7,DERPyH-12);
u8g.drawLine(DERPxH+9,DERPyH-12,DERPxH+9,DERPyH-15);
u8g.drawLine(DERPxH+1,DERPyH-12,DERPxH+3,DERPyH-12);
u8g.drawLine(DERPxH+4,DERPyH-13,DERPxH+6,DERPyH-13);
u8g.drawLine(DERPxH+6,DERPyH-1,DERPxH+6,DERPyH-2);
u8g.drawLine(DERPxH+5,DERPyH-2,DERPxH+7,DERPyH-2); 
u8g.drawLine(DERPxH+11,DERPyH-2,DERPxH+11,DERPyH-4); 
u8g.drawLine(DERPxH+11,DERPyH-9,DERPxH+10,DERPyH-8); 
u8g.drawLine(DERPxH+9,DERPyH-8,DERPxH+8,DERPyH-7);  
u8g.drawLine(DERPxH-1,DERPyH-12,DERPxH-1,DERPyH-13);  
u8g.drawPixel(DERPxH, DERPyH-14); 
u8g.drawLine(DERPxH-2,DERPyH-13,DERPxH-3,DERPyH-12);  
u8g.drawPixel(DERPxH-4, DERPyH-12);
u8g.drawLine(DERPxH-7,DERPyH-12,DERPxH-4,DERPyH-15); 
u8g.drawPixel(DERPxH-6, DERPyH-14);
u8g.drawLine(DERPxH-7,DERPyH-13,DERPxH-9,DERPyH-13); 
u8g.drawLine(DERPxH-10,DERPyH-12,DERPxH-13,DERPyH-12); 
u8g.drawLine(DERPxH-13,DERPyH-12,DERPxH-8,DERPyH-17); 
u8g.drawLine(DERPxH-8,DERPyH-17,DERPxH-13,DERPyH-17); 
u8g.drawPixel(DERPxH-12, DERPyH-18);
u8g.drawLine(DERPxH-11,DERPyH-19,DERPxH-8,DERPyH-20); 
u8g.drawLine(DERPxH-7,DERPyH-20,DERPxH-6,DERPyH-21); 
u8g.drawPixel(DERPxH-5, DERPyH-21);
u8g.drawLine(DERPxH-6,DERPyH-21,DERPxH-9,DERPyH-24); 
u8g.drawLine(DERPxH-9,DERPyH-24,DERPxH-1,DERPyH-24); 
u8g.drawLine(DERPxH-1,DERPyH-24,DERPxH+4,DERPyH-22); 
u8g.drawLine(DERPxH+5,DERPyH-21,DERPxH+5,DERPyH-24); 
u8g.drawPixel(DERPxH+6, DERPyH-23);
u8g.drawLine(DERPxH+7,DERPyH-22,DERPxH+7,DERPyH-21); 
u8g.drawLine(DERPxH+8,DERPyH-20,DERPxH+8,DERPyH-19); 
u8g.drawLine(DERPxH+9,DERPyH-20,DERPxH+9,DERPyH-22); 
u8g.drawLine(DERPxH+9,DERPyH-20,DERPxH+9,DERPyH-22); 
u8g.drawLine(DERPxH+10,DERPyH-19,DERPxH+10,DERPyH-18); 
u8g.drawPixel(DERPxH+11, DERPyH-20);
u8g.drawLine(DERPxH,DERPyH-6,DERPxH-3,DERPyH-6);
u8g.drawLine(DERPxH-3,DERPyH-4,DERPxH-3,DERPyH-5);
u8g.drawLine(DERPxH,DERPyH-3,DERPxH-2,DERPyH-3);




//лицо влево
if (storm!=1){
   if (SLEEP<3){
  if(MOOD==4){
  u8g.drawPixel(DERPxH+1, DERPyH-4);
  u8g.drawPixel(DERPxH, DERPyH-2);
  u8g.drawPixel(DERPxH-1, DERPyH-2);
  u8g.drawPixel(DERPxH+1, DERPyH-3);
  u8g.drawPixel(DERPxH+1, DERPyH-2); 
}

if(MOOD==3){ 
  u8g.drawPixel(DERPxH+1, DERPyH-4); 
  
}
if(MOOD==2){

      u8g.drawPixel(DERPxH+1, DERPyH-3); 
  
}
if(MOOD==1){

      u8g.drawPixel(DERPxH+1, DERPyH-2); 
   
}
 }
}


switch (glaza) {
 case 1:
u8g.drawPixel(DERPxH-2, DERPyH-10); 
u8g.drawPixel(DERPxH+2, DERPyH-10); 
u8g.drawPixel(DERPxH+3, DERPyH-10);  
u8g.drawPixel(DERPxH+4, DERPyH-10); 
u8g.drawPixel(DERPxH+6, DERPyH-10);
u8g.drawPixel(DERPxH+2, DERPyH-9);  
u8g.drawPixel(DERPxH+6, DERPyH-9);
u8g.drawPixel(DERPxH-2, DERPyH-9);  
u8g.drawPixel(DERPxH+3, DERPyH-9);  
u8g.drawPixel(DERPxH+4, DERPyH-9);
u8g.drawPixel(DERPxH-3, DERPyH-9); 
u8g.drawPixel(DERPxH+6, DERPyH-8);
u8g.drawPixel(DERPxH-3, DERPyH-8);
u8g.drawPixel(DERPxH+3, DERPyH-8);  
u8g.drawPixel(DERPxH+4, DERPyH-8); 
u8g.drawPixel(DERPxH+2, DERPyH-8);
u8g.drawPixel(DERPxH-2, DERPyH-8); 
u8g.drawPixel(DERPxH+6, DERPyH-7); 
u8g.drawPixel(DERPxH-3, DERPyH-7);
u8g.drawPixel(DERPxH+2, DERPyH-7); 
u8g.drawPixel(DERPxH+7, DERPyH-9); 
u8g.drawPixel(DERPxH-6, DERPyH-9);
    break;
 case 2:
u8g.drawPixel(DERPxH+2, DERPyH-9);  
u8g.drawPixel(DERPxH+6, DERPyH-9);
u8g.drawPixel(DERPxH-2, DERPyH-9);  
u8g.drawPixel(DERPxH+3, DERPyH-9);  
u8g.drawPixel(DERPxH+4, DERPyH-9);
u8g.drawPixel(DERPxH-3, DERPyH-9); 
u8g.drawPixel(DERPxH+6, DERPyH-8);
u8g.drawPixel(DERPxH-3, DERPyH-8);
u8g.drawPixel(DERPxH+3, DERPyH-8);  
u8g.drawPixel(DERPxH+4, DERPyH-8); 
u8g.drawPixel(DERPxH+2, DERPyH-8);
u8g.drawPixel(DERPxH-2, DERPyH-8); 
u8g.drawPixel(DERPxH+6, DERPyH-7); 
u8g.drawPixel(DERPxH-3, DERPyH-7);
u8g.drawPixel(DERPxH+2, DERPyH-7);
u8g.drawPixel(DERPxH+7, DERPyH-9);  
u8g.drawPixel(DERPxH-6, DERPyH-9);
    break;
 case 3:
u8g.drawPixel(DERPxH+6, DERPyH-8);
u8g.drawPixel(DERPxH-3, DERPyH-8);
u8g.drawPixel(DERPxH+3, DERPyH-8);  
u8g.drawPixel(DERPxH+4, DERPyH-8); 
u8g.drawPixel(DERPxH+2, DERPyH-8);
u8g.drawPixel(DERPxH-2, DERPyH-8); 
u8g.drawPixel(DERPxH+6, DERPyH-7); 
u8g.drawPixel(DERPxH-3, DERPyH-7);
u8g.drawPixel(DERPxH+2, DERPyH-7); 
u8g.drawPixel(DERPxH+7, DERPyH-9); 
u8g.drawPixel(DERPxH+6, DERPyH-9); 
u8g.drawPixel(DERPxH-6, DERPyH-9); 
    break;
 case 4:
u8g.drawPixel(DERPxH+6, DERPyH-7); 
u8g.drawPixel(DERPxH-3, DERPyH-7);
u8g.drawPixel(DERPxH+2, DERPyH-7); 
u8g.drawPixel(DERPxH+7, DERPyH-8); 
u8g.drawPixel(DERPxH+6, DERPyH-8); 
u8g.drawPixel(DERPxH-6, DERPyH-8); 
    break;
 case 5:
u8g.drawPixel(DERPxH+7, DERPyH-8); 
u8g.drawPixel(DERPxH-6, DERPyH-7); 
    break;
 case 6:
u8g.drawPixel(DERPxH+7, DERPyH-8); 
u8g.drawPixel(DERPxH-6, DERPyH-7); 
    break;
}

u8g.drawPixel(DERPxH+6, DERPyH-7);
if (hmmm<4){
if (nya!=1){  
u8g.drawLine(DERPxH+2,DERPyH-6,DERPxH+5,DERPyH-6); 
u8g.drawPixel(DERPxH-4, DERPyH-6); 
  if (night==0){
  SLEEP=0;
   static unsigned long timer = millis(); 
      if (millis() - timer > 30) {      
        if (direct1==1) {
          if (glaza!=6) {
           glaza++;
        }else{
           direct1=0;
        }
        }
        if (direct1==0) {
           if (glaza!=1) {  
           glaza--;     
        }else{
            static unsigned long timer = millis(); 
              if (millis() - timer > 10000) {
                  direct1=1;    
               timer = millis();     
                 }   
        }
        }
     
       timer = millis();     
  }
}else{
    if (storm==1){
     if (love==1){
      static unsigned long timer = millis(); 
              if (millis() - timer > 10000) {
                
          if (glaza!=6) {
           glaza++;
           SLEEP++;
        }else{
           direct1=0;
        }          
               timer = millis();     
                 }  
  }else{
       static unsigned long timer = millis(); 
              if (millis() - timer > 10000) {               
          if (glaza<=2) {
           glaza++;
        }else{
           direct1=0;
        }          
               timer = millis();     
                 } 
  }
  }else{
    static unsigned long timer = millis(); 
              if (millis() - timer > 10000) {
                
          if (glaza!=6) {
           glaza++;
           SLEEP++;
        }else{
           direct1=0;
        }          
               timer = millis();     
                 }    
  }
  
}
}else{
 u8g.drawLine(DERPxH-2,DERPyH-7,DERPxH-2,DERPyH-8); 
u8g.drawLine(DERPxH-2,DERPyH-7,DERPxH-2,DERPyH-8); 
u8g.drawLine(DERPxH-3,DERPyH-9,DERPxH-4,DERPyH-9);
u8g.drawLine(DERPxH+2,DERPyH-7,DERPxH+2,DERPyH-8); 
u8g.drawLine(DERPxH+3,DERPyH-9,DERPxH+5,DERPyH-9); 
u8g.drawLine(DERPxH+6,DERPyH-7,DERPxH+6,DERPyH-8); 
u8g.drawPixel(DERPxH+7, DERPyH-7);  
}
  
   
}else{
  if (select13menu==1){
    u8g.drawLine(DERPxH+2,DERPyH-6,DERPxH+5,DERPyH-6); 
u8g.drawPixel(DERPxH-4, DERPyH-6); 
    glaza=3;
  }else{
if (nya!=1){
u8g.drawLine(DERPxH+2,DERPyH-6,DERPxH+5,DERPyH-6); 
u8g.drawPixel(DERPxH-4, DERPyH-6); 
   if (night==0){
  SLEEP=0;
   static unsigned long timer = millis(); 
      if (millis() - timer > 30) {      
        if (direct1==1) {
          if (glaza!=6) {
           glaza++;
        }else{
           direct1=0;
        }
        }
        if (direct1==0) {
           if (glaza!=1) {  
           glaza--;     
        }else{
            static unsigned long timer = millis(); 
              if (millis() - timer > 10000) {
                  direct1=1;    
               timer = millis();     
                 }   
        }
        }
     
       timer = millis();     
  }
}else{
    if (storm==1){
     if (love==1){
      static unsigned long timer = millis(); 
              if (millis() - timer > 10000) {
                
          if (glaza!=6) {
           glaza++;
           SLEEP++;
        }else{
           direct1=0;
        }          
               timer = millis();     
                 }  
  }else{
       static unsigned long timer = millis(); 
              if (millis() - timer > 10000) {               
          if (glaza<=2) {
           glaza++;
        }else{
           direct1=0;
        }          
               timer = millis();     
                 } 
  }
  }else{
    static unsigned long timer = millis(); 
              if (millis() - timer > 10000) {
                
          if (glaza!=6) {
           glaza++;
           SLEEP++;
        }else{
           direct1=0;
        }          
               timer = millis();     
                 }    
  }
  
}
}else{
u8g.drawLine(DERPxH-2,DERPyH-7,DERPxH-2,DERPyH-8); 
u8g.drawLine(DERPxH-2,DERPyH-7,DERPxH-2,DERPyH-8); 
u8g.drawLine(DERPxH-3,DERPyH-9,DERPxH-4,DERPyH-9);
u8g.drawLine(DERPxH+2,DERPyH-7,DERPxH+2,DERPyH-8); 
u8g.drawLine(DERPxH+3,DERPyH-9,DERPxH+5,DERPyH-9); 
u8g.drawLine(DERPxH+6,DERPyH-7,DERPxH+6,DERPyH-8); 
u8g.drawPixel(DERPxH+7, DERPyH-7); 
}

    
    
  } 
}

 


u8g.drawPixel(DERPxH-2, DERPyH-11); 
u8g.drawPixel(DERPxH-2, DERPyH-7); 
u8g.drawLine(DERPxH+2,DERPyH-12+glaza,DERPxH+5,DERPyH-12+glaza); 
u8g.drawLine(DERPxH-2,DERPyH-12+glaza,DERPxH-4,DERPyH-12+glaza); 




u8g.setColorIndex(0);
u8g.drawBox(0,0,15,64);
u8g.setColorIndex(1);

 
switch (select13menu) {
 case 1:
   u8g.drawRFrame(0,0,15,16,1);
   if (right==0){
    if (select13item==1){      
      muffinX++;
    } 
    if (select13item==0){
      select13item=1;
      tone(35, 170, 100); 
      muffinX=21;
      right=0;
      delay(200);
    }       
   }
   if (left==0){
      if (muffinX>=20){
       muffinX--;  
      }else{
        select13item=0;
        tone(35, 150, 100); 
        muffinX=7;
        muffinY=7;
        sost=0;
        left=1;
        delay(200);
      }
   }
   if (select13item==1){
  
   if (hmmm<4){
     MOOD=4; 
     if (sost==0){
       hmmm++;
       sost=1;
     }  
    }else{
      MOOD=0;
    }         
    if (switchGLAZA==0){
       direct1=1;
       switchGLAZA=1;
    }
   
if (up==0){
   muffinY--;
}
if (down==0){
   muffinY++;
}
if (muffinX>=DERPxH-10 && muffinY>=DERPyH-15 && muffinX<=DERPxH+10 && muffinY<=DERPyH+2 && SLEEP<3){
  muffinX=7;
  muffinY=7;
  direct1=1;
  select13item=0;
  FOOD=FOOD+17;
  hmmm=0;
   tone(soundPIN, 750, 100);
   right=1; 
   delay(200);
}
   }else{ 
    if (hmmm<4){
      MOOD=3; // обычное настроение  
    }else{
      MOOD=0;
    }
         
    switchGLAZA=0;
   }

      
    break;
 case 2:
   u8g.drawRFrame(0,16,15,16,1);
      if(right==LOW){
    if (love==0){
       love=1;
         tone(soundPIN, 370, 100);
       right=1;
        delay(200);
    }else{
       love=0;
         tone(soundPIN, 320, 100);
       right=1;
        delay(200);
    }
  
   }
    break;
 case 3:
   u8g.drawRFrame(0,32,15,16,1);
   if(right==LOW){
    if (night==0){
       night=1;
        random1=random(1,2); 
        if (random1==1){
           storm=1;
        }
         tone(soundPIN, 310, 100);
       right=1;
        delay(200);
    }else{
       night=0;
         tone(soundPIN, 350, 100);
       right=1;
        delay(200);
    } 
   }
    break;
 case 4:
   u8g.drawRFrame(0,48,15,16,1);
         u8g.setColorIndex(0); 
   u8g.drawBox(15,0,124,64); 
    u8g.setColorIndex(1); 
  u8g.setFont(rus7x13);
    if(TIMERset==3){
      u8g.drawStr( 22, 15, "побег");
    }else{
       u8g.drawStr( 22, 15, "голод");
    } 
    u8g.drawStr( 22, 29, "шкала");
    u8g.drawStr( 22, 43, "фразы");
     u8g.drawStr( 22, 56, "рестарт");
     u8g.drawStr( 85, 56, "пуск");
   u8g.setFont(rus6x12); 
   if(right==LOW){
    select13++;
    tone(soundPIN, 350, 100);
        right=1;
   }
    if(left==LOW){
    select13--;
    tone(soundPIN, 350, 100);
    left=1;
   }
   if(select13==2){
   

    if(up==LOW){
       tone(soundPIN, 350, 40);
       position13--; 
      up=1;
      delay(200);
    }
     if(down==LOW){
       tone(soundPIN, 350, 40);
       position13++;
      down=1;
      delay(200);
    }
   }
   if(position13==0){
     if(select13==2){
      u8g.drawRFrame(15,5,47,14,1);
     }
      
       if(select13==3){
        u8g.drawRFrame(65,5,57,14,1);
    if(up==LOW){
       tone(soundPIN, 750, 40);
      TIMERset++; //2 - внутренний, 1 - модуль, 0 - OFF
      eeprom_write_byte(&TIMERsetsave, TIMERset);
      up=1;
      delay(200);
    }
     if(down==LOW){
       tone(soundPIN, 750, 40);
      TIMERset--;
      eeprom_write_byte(&TIMERsetsave, TIMERset);
      down=1;
      delay(200);
    }
   }
   }

if(position13==1){
  if(select13==2){
      u8g.drawRFrame(15,19,47,14,1);
     }
     if(select13==3){
       u8g.drawRFrame(80,19,37,14,1);
    if(up==LOW){
       tone(soundPIN, 750, 40);
      SKALAON=1; 
      eeprom_write_byte(&SKALAONsave, SKALAON);
      up=1;
      delay(200);
    }
     if(down==LOW){
       tone(soundPIN, 750, 40);
      SKALAON=0;
      eeprom_write_byte(&SKALAONsave, SKALAON);
      down=1;
      delay(200);
    }
   }
}
 

if(position13==2){
  if(select13==2){
      u8g.drawRFrame(15,33,47,14,1);
     }
     if(select13==3){
       u8g.drawRFrame(80,33,37,14,1);
    if(up==LOW){
       tone(soundPIN, 750, 40);
      FRAZ=1; 
      eeprom_write_byte(&FRAZsave, FRAZ);
      up=1;
      delay(200);
    }
     if(down==LOW){
       tone(soundPIN, 750, 40);
      FRAZ=0; 
      eeprom_write_byte(&FRAZsave, FRAZ);
      down=1;
      delay(200);
    }
   }
}   
if(position13==3){
  if(select13==2){
      u8g.drawRFrame(15,46,61,14,1);
     }
     if(select13==3){
       u8g.drawRFrame(80,46,37,14,1);
    if(up==LOW){
       tone(soundPIN, 550, 300);
      RESTART=1; 
      up=1;
      delay(200);
    }
     if(down==LOW){
       tone(soundPIN, 550, 300);
      RESTART=1; 
      down=1;
      delay(200);
    }
   }
} 
  

   if(TIMERset==0){
  u8g.setFont(rus7x13);
  u8g.drawStr( 85, 15, "выкл");
  }
  if(TIMERset==1){
       u8g.setFont(rus7x13);
  u8g.drawStr( 75, 15, "таймер");
  }
  if(TIMERset==2){
     u8g.setFont(rus7x13);
  u8g.drawStr( 75, 15, "память");
  }
   if(TIMERset==3){
  u8g.setFont(rus7x13);
  u8g.drawStr( 85, 15, "выкл");
  }
 if(SKALAON==0){
            u8g.setFont(rus7x13);
  u8g.drawStr( 85, 29, "выкл");
  }
  if(SKALAON==1){
       u8g.setFont(rus7x13);
  u8g.drawStr( 88, 29, "вкл");
  }
 if(FRAZ==0){
            u8g.setFont(rus7x13);
  u8g.drawStr( 85, 43, "выкл");
  }
  if(FRAZ==1){
       u8g.setFont(rus7x13);
  u8g.drawStr( 88, 43, "вкл");
  }

  
    break;
}

//маффин
if (night==1){
  if (muffinX!=7){
    u8g.drawBox(muffinX-4,muffinY-2,9,3);
    u8g.drawBox(muffinX-3,muffinY-3,6,5);
u8g.setColorIndex(0); 
u8g.drawBox(muffinX-3,muffinY+2,7,3);
u8g.drawBox(muffinX-2,muffinY+5,5,1);
u8g.drawBox(muffinX-4,muffinY+2,9,1);
u8g.drawBox(muffinX-4,muffinY+1,2,1);
u8g.drawBox(muffinX-5,muffinY-1,1,2);
u8g.drawBox(muffinX-3,muffinY-3,2,1);
u8g.drawBox(muffinX-1,muffinY-4,3,1);
u8g.drawBox(muffinX+2,muffinY-3,2,1);
u8g.drawBox(muffinX+5,muffinY-1,1,2);
u8g.drawPixel(muffinX, muffinY);
u8g.drawPixel(muffinX-3, muffinY);
u8g.drawPixel(muffinX+2, muffinY+1);
u8g.drawPixel(muffinX+3, muffinY-1);
u8g.drawPixel(muffinX+1, muffinY-2);
u8g.drawPixel(muffinX-2, muffinY-2);
u8g.drawPixel(muffinX-4, muffinY-2);
u8g.drawPixel(muffinX+4, muffinY-2);
u8g.drawPixel(muffinX+4, muffinY+1);
u8g.setColorIndex(1); 
  }else{
u8g.drawBox(muffinX-3,muffinY+2,7,3);
u8g.drawBox(muffinX-2,muffinY+5,5,1);
u8g.drawBox(muffinX-4,muffinY+2,9,1);
u8g.drawBox(muffinX-4,muffinY+1,2,1);
u8g.drawBox(muffinX-5,muffinY-1,1,2);
u8g.drawBox(muffinX-3,muffinY-3,2,1);
u8g.drawBox(muffinX-1,muffinY-4,3,1);
u8g.drawBox(muffinX+2,muffinY-3,2,1);
u8g.drawBox(muffinX+5,muffinY-1,1,2);
u8g.drawPixel(muffinX, muffinY);
u8g.drawPixel(muffinX-3, muffinY);
u8g.drawPixel(muffinX+2, muffinY+1);
u8g.drawPixel(muffinX+3, muffinY-1);
u8g.drawPixel(muffinX+1, muffinY-2);
u8g.drawPixel(muffinX-2, muffinY-2);
u8g.drawPixel(muffinX-4, muffinY-2);
u8g.drawPixel(muffinX+4, muffinY-2);
u8g.drawPixel(muffinX+4, muffinY+1); 
  }

}else{
u8g.setColorIndex(0); 
u8g.drawBox(muffinX-4,muffinY-2,9,3);
u8g.drawBox(muffinX-3,muffinY-3,6,5);
u8g.setColorIndex(1);  
u8g.drawBox(muffinX-3,muffinY+2,7,3);
u8g.drawBox(muffinX-2,muffinY+5,5,1);
u8g.drawBox(muffinX-4,muffinY+2,9,1);
u8g.drawBox(muffinX-4,muffinY+1,2,1);
u8g.drawBox(muffinX-5,muffinY-1,1,2);
u8g.drawBox(muffinX-3,muffinY-3,2,1);
u8g.drawBox(muffinX-1,muffinY-4,3,1);
u8g.drawBox(muffinX+2,muffinY-3,2,1);
u8g.drawBox(muffinX+5,muffinY-1,1,2);
u8g.drawPixel(muffinX, muffinY);
u8g.drawPixel(muffinX-3, muffinY);
u8g.drawPixel(muffinX+2, muffinY+1);
u8g.drawPixel(muffinX+3, muffinY-1);
u8g.drawPixel(muffinX+1, muffinY-2);
u8g.drawPixel(muffinX-2, muffinY-2);
u8g.drawPixel(muffinX-4, muffinY-2);
u8g.drawPixel(muffinX+4, muffinY-2);
u8g.drawPixel(muffinX+4, muffinY+1);
}



//Сердце
u8g.drawBox(4,21,7,5);
u8g.drawBox(2,21,11,3);
u8g.drawBox(3,20,4,5);
u8g.drawBox(8,20,4,5);
u8g.drawBox(5,26,5,1);
u8g.drawBox(6,27,3,1);
u8g.drawBox(5,26,5,1);
u8g.drawBox(4,19,2,1);
u8g.drawBox(9,19,2,1);
u8g.drawPixel(7, 28);
    
//Лампочка
u8g.drawBox(5,45,5,1);
u8g.drawBox(11,41,1,3);
u8g.drawBox(3,41,1,3);
u8g.drawBox(5,36,5,3);
u8g.drawBox(6,35,3,1);
u8g.drawBox(7,38,1,4);
u8g.drawPixel(4, 44);
u8g.drawPixel(10, 44);
u8g.drawPixel(6, 42);
u8g.drawPixel(8, 42);
u8g.drawPixel(4, 40);
u8g.drawPixel(10, 40);
u8g.drawPixel(5, 39);
u8g.drawPixel(9, 39);

//Шестерёнка
u8g.drawBox(5,55,5,3);
u8g.drawBox(6,54,3,5);
u8g.drawBox(6,61,3,1);
u8g.drawBox(8,60,3,1);
u8g.drawBox(11,57,1,3);
u8g.drawBox(12,55,1,3);
u8g.drawBox(11,53,1,3);
u8g.drawBox(8,52,3,1);
u8g.drawBox(6,51,3,1);
u8g.drawBox(4,52,3,1);
u8g.drawBox(3,53,1,3);
u8g.drawBox(2,55,1,3);
u8g.drawBox(3,57,1,3);
u8g.drawBox(4,60,3,1);


if (love>=1){
  if (animation==0){
    rukaX=DERPxH+4;
    rukaY=DERPyH-21;
    animation=1;
  }else{
     static unsigned long timer = millis(); 
              if (millis() - timer > 200) {
                if (rukaX>DERPxH+9 && rukaY==DERPyH-21){
                  rukaY++;
                  if (FOOD>30){
                   HAPPY++;
                  }             
                }
                if (rukaX>DERPxH+12){
                  rukaX=DERPxH+4;
                  rukaY=DERPyH-21;
                }else{
                  rukaX++; 
                }     
               timer = millis();     
                 }
  }
   
   u8g.setColorIndex(0); 
   u8g.drawBox(rukaX-6,rukaY-3,10,8);
   u8g.drawBox(rukaX+4,rukaY+1,10,4);
   u8g.drawBox(rukaX-9,rukaY-7,8,6);
   u8g.drawBox(rukaX-15,rukaY-5,16,2);
   u8g.drawBox(rukaX-10,rukaY+3,6,2);
   u8g.drawBox(rukaX+4,rukaY-1,5,2);
   u8g.drawBox(rukaX+9,rukaY+5,5,1);
   u8g.setColorIndex(1);   
  u8g.drawLine(rukaX,rukaY+4,rukaX+6,rukaY+4);
  u8g.drawLine(rukaX+7,rukaY+5,rukaX+8,rukaY+5);  
  u8g.drawLine(rukaX+9,rukaY+6,rukaX+14,rukaY+6);  
  u8g.drawLine(rukaX+14,rukaY+6,rukaX+14,rukaY+1);  
  u8g.drawPixel(rukaX+13, rukaY+1);
    u8g.drawLine(rukaX+12,rukaY,rukaX+9,rukaY); 
   u8g.drawLine(rukaX+8,rukaY-1,rukaX+5,rukaY-1); 
   u8g.drawLine(rukaX+4,rukaY-2,rukaX+3,rukaY-2); 
   u8g.drawLine(rukaX+3,rukaY-3,rukaX+2,rukaY-3);   
  u8g.drawLine(rukaX+2,rukaY-3,rukaX-3,rukaY-8); 
  u8g.drawLine(rukaX-3,rukaY-8,rukaX-8,rukaY-8); 
    u8g.drawLine(rukaX-7,rukaY-7,rukaX-13,rukaY-7); 
      u8g.drawLine(rukaX-10,rukaY-6,rukaX-15,rukaY-6); 
      u8g.drawPixel(rukaX-16, rukaY-5);
       u8g.drawLine(rukaX-15,rukaY-4,rukaX-11,rukaY-4); 
      u8g.drawLine(rukaX-10,rukaY-3,rukaX-9,rukaY-3); 
       u8g.drawLine(rukaX-8,rukaY-2,rukaX-6,rukaY); 
       u8g.drawPixel(rukaX-6, rukaY+1);
       u8g.drawLine(rukaX-7,rukaY+2,rukaX-10,rukaY+2);
       u8g.drawPixel(rukaX-11, rukaY+3); 
       u8g.drawLine(rukaX-10,rukaY+4,rukaX-8,rukaY+4);
       u8g.drawLine(rukaX-7,rukaY+5,rukaX-1,rukaY+5);
       u8g.drawLine(rukaX-9,rukaY-5,rukaX-8,rukaY-5);
       u8g.drawPixel(rukaX-7, rukaY-4); 
       u8g.drawLine(rukaX-6,rukaY-6,rukaX-5,rukaY-5);
       u8g.drawLine(rukaX-4,rukaY-7,rukaX-3,rukaY-6);    
}

if (SKALAON==1){
  if (night==0){
  u8g.setColorIndex(0);
u8g.drawBox(125,0,3,64);
u8g.setColorIndex(1);
u8g.drawLine(125,0,125,63);

u8g.drawLine(126,SKALA,126,63);
u8g.drawLine(127,SKALA,127,63);
}else{
    u8g.setColorIndex(1);
u8g.drawBox(125,0,3,64);
u8g.setColorIndex(0);
u8g.drawLine(125,0,125,63);

u8g.drawLine(126,SKALA,126,63);
u8g.drawLine(127,SKALA,127,63);
 u8g.setColorIndex(1);
}
}

if (MOOD>=3 && night==0 && FRAZ==1 && select13menu!=4){
u8g.setFont(rus7x13);


if (switchFRAZ==0){
 random1=random(1,1);  
    switchFRAZ=1;  
}
if (switchFRAZ==1){
   static unsigned long timer = millis(); 
              if (millis() - timer > 10000) {              
                  switchFRAZ=2;    
               timer = millis();     
                 } 
     if (random1==1){
      u8g.setColorIndex(0);
u8g.drawBox(DERPxH+19,DERPyH-34,43,25);
u8g.drawBox(DERPxH+18,DERPyH-33,45,23);
u8g.setColorIndex(1);
u8g.drawRFrame(DERPxH+18,DERPyH-34,46,26,3);
u8g.drawPixel( DERPxH+16, DERPyH-8);
u8g.drawPixel( DERPxH+17, DERPyH-7);
u8g.drawPixel( DERPxH+18, DERPyH-7);
u8g.drawPixel( DERPxH+19, DERPyH-7);
u8g.drawPixel( DERPxH+17, DERPyH-8);
u8g.drawPixel( DERPxH+18, DERPyH-8);
u8g.drawPixel( DERPxH+19, DERPyH-8);
u8g.drawPixel( DERPxH+20, DERPyH-8);
u8g.drawPixel( DERPxH+21, DERPyH-8);
u8g.drawPixel( DERPxH+17, DERPyH-9);
u8g.drawPixel( DERPxH+18, DERPyH-9);
u8g.drawPixel( DERPxH+17, DERPyH-10);
u8g.drawPixel( DERPxH+18, DERPyH-10);
u8g.drawPixel( DERPxH+19, DERPyH-9);
u8g.drawPixel( DERPxH+16, DERPyH-7);  
        u8g.drawStr(DERPxH+33,DERPyH-18, "ня!");          
     }
  
}
if (muffinX>21){
  switchFRAZ=2;   
  u8g.setColorIndex(0);
u8g.drawBox(DERPxH+19,DERPyH-34,43,25);
u8g.drawBox(DERPxH+18,DERPyH-33,45,23);
u8g.setColorIndex(1);
u8g.drawRFrame(DERPxH+18,DERPyH-34,46,26,3);
u8g.drawPixel( DERPxH+16, DERPyH-8);
u8g.drawPixel( DERPxH+17, DERPyH-7);
u8g.drawPixel( DERPxH+18, DERPyH-7);
u8g.drawPixel( DERPxH+19, DERPyH-7);
u8g.drawPixel( DERPxH+17, DERPyH-8);
u8g.drawPixel( DERPxH+18, DERPyH-8);
u8g.drawPixel( DERPxH+19, DERPyH-8);
u8g.drawPixel( DERPxH+20, DERPyH-8);
u8g.drawPixel( DERPxH+21, DERPyH-8);
u8g.drawPixel( DERPxH+17, DERPyH-9);
u8g.drawPixel( DERPxH+18, DERPyH-9);
u8g.drawPixel( DERPxH+17, DERPyH-10);
u8g.drawPixel( DERPxH+18, DERPyH-10);
u8g.drawPixel( DERPxH+19, DERPyH-9);
u8g.drawPixel( DERPxH+16, DERPyH-7);  
  u8g.drawStr(DERPxH+26,DERPyH-18, "хочу!");
}

}

}
void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

TIMERset = eeprom_read_byte(&TIMERsetsave);
SKALAON = eeprom_read_byte(&SKALAONsave);
DERPx = eeprom_read_byte(&DERPxsave);
FRAZ = eeprom_read_byte(&FRAZsave);
FOOD = eeprom_read_byte(&FOODsave);
MIN = eeprom_read_byte(&MINsave);
select13menu=2;
  
}
void loop() {
   tmElements_t tm;
Serial.begin(9600);
randomSeed(analogRead(A0));
select13menu = constrain(select13menu, 1, 4);
muffinX = constrain(muffinX, 0, 128);
muffinY = constrain(muffinY, 0, 64);
HAPPY = constrain(HAPPY, 1, 10);
FOOD = constrain(FOOD, 0, 100);
TIMERset = constrain(TIMERset, 0, 3);
select13 = constrain(select13, 1, 3);
position13 = constrain(position13, 0, 3);
SKALA = map(FOOD,0, 100, 64, 0);
golodovka = constrain(golodovka, 1, 3);
if (up==0){
  if(select13==1){
   if (select13item==0){
  select13menu--;
  tone(35, 150, 30);   
  delay(100);
  } 
  }  
}
if (down==0){
  if(select13==1){
      if (select13item==0){
  select13menu++;
  tone(35, 150, 30); 
  delay(100);    
  } 
  }
}
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
   
    up = digitalRead(4);
  down = digitalRead(5);
  left = digitalRead(2);
  right = digitalRead(3);



if (FOOD>50){
    if (love==1){ 
      static unsigned long timer = millis(); 
              if (millis() - timer > 5000) { 
                glaza=0;       
                  nya=1;
               timer = millis();     
                 }
}else{
        static unsigned long timer = millis(); 
              if (millis() - timer > 5000) { 
       if (glaza!=6) {
           glaza++;
        }else{
           direct1=0;
        }      
                  nya=0;
               timer = millis();     
                 }
}
   }else{
    nya=0;
   }




  
if (TIMERset>=2){
  
    static unsigned long timer = millis(); 
              if (millis() - timer > 600000) {
                if (FOOD>0){        
                  FOOD--; 
                  eeprom_write_byte(&FOODsave, FOOD);
                } 
               timer = millis();     
                 }
 
}
if (TIMERset==1){
 if (RTC.read(tm)) {
Rtime=tm.Hour;
if (Rtime>MIN) {
RAZNOST=Rtime-MIN;  
}
if (Rtime<MIN) {
RAZNOST=MIN-Rtime;  
}
if (Rtime==MIN) {
RAZNOST=0;  
}

if (RAZNOST>0) {
  FOOD=FOOD-(RAZNOST*GOLODOVKA);
  MIN=Rtime;
  eeprom_write_byte(&MINsave, MIN);
  eeprom_write_byte(&FOODsave, FOOD);
}



//HOUR = tm.Hour;
//MIN = tm.Minute;
//realDAY = tm.Day;
}
}
//Serial.print(RAZNOST);
if (select13item==0){
  if (FOOD>50){
    MOOD=3;
}
if (FOOD>20 && FOOD<60){
    MOOD=2;
}
if (FOOD<20){
    MOOD=1;
}  

if (TIMERset!=3){
  if (FOOD<=0){
  if (END==0){
    DERPx=200;
eeprom_write_byte(&DERPxsave, DERPx);
END=1;
  }
}
}
  
}

 if (RESTART==1){
   if (END2==0){
DERPx=65;
FOOD=100;
eeprom_write_byte(&DERPxsave, DERPx);
eeprom_write_byte(&FOODsave, FOOD);
  END2=1;
 }
 }
          
}
