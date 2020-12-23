#include<Keypad.h>  //libraries
#include<EEPROM.h>
#include <LiquidCrystal.h>
#include<Servo.h>
Servo servo;
#define yled 5   //green led
#define kled 6   // red led
#define buzzer 4

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);//Lcd connections LiquidCrystal(rs, enable, d4, d5, d6, d7)
// ( vss:GND ,VDD:+5V,VO:POT ,RW:GND,A:+5V,K:GND)

const byte satir = 4;  //rows
const byte sutun = 4;  //columbs
char sifre[4] = {'*', '#', 'C', '9'};
char sifre1[4];//password that we will click on the keypad
char y_sifre[4]={'1','9','2','3'};
char tus;   //char key 
int sifre_sayac=0;
int i = 0;  
char tus_takimi[4][4] = {  
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte satir_pins[4] = {A0, A1, A2, A3};  //rows_pins connected which pins
byte sutun_pins[4] = {A4, A5, 3, 2};    //columb_pins connecting which pins

Keypad tuss_takimi = Keypad(makeKeymap(tus_takimi), satir_pins, sutun_pins, 4, 4);  // special code from Keypad library. basically create map usin name of keypad and row_pins,columb_pins





void setup() 
{
  // put your setup code here, to run once:
  servo.attach(13);
  pinMode(yled, OUTPUT);  //designating leds and buzzer as OUTPUT
  pinMode(buzzer, OUTPUT);
  pinMode(kled, OUTPUT);
  lcd.begin(16,2);
  lcd.clear();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Hosgeldiniz");
  

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Hosgeldiniz");
  lcd.setCursor(0, 1);
  lcd.print("SIFRELI KAPI");   // LOCK DOOR SYSTEM
  delay(2000);
  lcd.clear();  
  lcd.setCursor(0, 0); 
  lcd.print("SIFREYI GIRINIZ:");    //YOU CAN PRINT HERE WHAT EVER YOU WANT ,THIS MEAN PASSWORD:
  Serial.begin(9600);
  Serial.println("Hos geldiniz");   //WELCOME
  Serial.println("Sifreyi giriniz");  
}




void loop() {
  // put your main code here, to run repeatedly:
   servo.write(0);
  
digitalWrite(kled,LOW);
digitalWrite(yled,LOW);
  tus = tuss_takimi.getKey();  //getKey gets key when we click on the keypad 

  if (tus)   //if key (tus then it will process as follow
  {
    if(i==0);
    lcd.clear();
    if(tus=='*')
    {
    sifre1[i++] = tus; 

    lcd.setCursor(i, 1); 
    lcd.print("*");   
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
      sifre_sayac++;
      if(sifre_sayac==3)
      {
        sifre_degistir();
        i=0;

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("HOSGELDINIZ");
        lcd.setCursor(0,1);
        lcd.print("SIFRE GIRINIZ");
      }
    }
    else
    {
       sifre1[i++] = tus;
       lcd.setCursor(i, 1); 
    lcd.print("*");   
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    }
  }

  if (i == 4)
  { delay(200);
     //default password u should write here like that 
 
    if ((strncmp(sifre1, sifre, 4) == 0))   
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      servo.write(90);
      lcd.print("SIFRE DOGRU!"); //password correct
      digitalWrite(yled, HIGH);
      digitalWrite(kled, LOW);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(4000);
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("SIFREYI GIRINIZ");  //password : 
      i = 0;
    }

    else
    {
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("SIFRE YANLIS!!!");  //wrong password
      digitalWrite(yled, LOW);
      digitalWrite(kled, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("SIFREYI GIRINIZ"); //password :
      i = 0;
    }
  }


}

void sifre_degistir()
{
  i=0;
  sifre_sayac=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("YONETICI SIFRESI");
  int s=1;
    while(s==1)
    {
       tus = tuss_takimi.getKey();

        if(tus)
        {
          if(i==0)
          lcd.clear();
          sifre1[i++] = tus;

          lcd.setCursor(1,0);
          lcd.print("GIRILEN SIFRE");
          lcd.setCursor(i,1);
          lcd.print('*');
          digitalWrite(buzzer,HIGH);
          delay(100);
          digitalWrite(buzzer,LOW);
          
        }

        if(i==4)
        {
          if((strncmp(sifre1,y_sifre, 4) == 0))
          {
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("YENI SIFRE");
            int k=0;
            int m=1;
              while(m==1)
              {
                tus = tuss_takimi.getKey();
                if(tus)
                {
                  
                    if(k==0)
                  
                    lcd.clear();
                    sifre[k++] = tus;
                  
                    
                     lcd.setCursor(1, 0); 
                     lcd.print("GiRiLEN  SiFRE"); 
                     lcd.setCursor((5+k), 1); 
                     lcd.print(tus);
                     digitalWrite(buzzer,HIGH);
                     delay(100);
                     digitalWrite(buzzer,LOW);
                   
                }
                if(k==4)
                m=0;
                
              }
              delay(300);
              lcd.setCursor(1,0);
              lcd.print("SIFRE DEGISTI");
              delay(2000);
          }
          else{
            lcd.clear();
            lcd.setCursor(4, 0); 
            lcd.print("YONETiCi");  
            lcd.setCursor(1, 1); 
            lcd.print("SiFRESi YANLIS!");
            delay(2000);
          }
         
          s=0;
        }
    }
}
