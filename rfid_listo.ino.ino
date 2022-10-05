#include <SPI.h> 
#include <MFRC522.h>
#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>

// Rfid pines
#define SS_PIN 5
#define RST_PIN 27

// Buzzer pin
#define BUZZER 16

// Foquitos led
#define LED_ACCESS_PIN 21
//#define LED_DENIED_PIN 21 // change to other pin, just checking with 1 led

//LiquidCrystal_I2C lcd(0x3F,16,2);

MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class

int code[] = {140, 36, 255, 55}; //This is the stored UID (Unlock Card)
int codeRead = 0;
String uidString;

void setup() {
   Serial.begin(9600); 
   SPI.begin();       // Init SPI bus
   mfrc522.PCD_Init(); // Init MFRC522
   Serial.println("Arduino RFID reading UID");
   pinMode( LED_ACCESS_PIN , OUTPUT);
   pinMode(BUZZER, OUTPUT);
   //pinMode( LED_DENIED_PIN , OUTPUT); 
   //lcd.init();
  // Print a message to the LCD.
  //lcd.backlight();
  //lcd.setCursor(0,0);
  //lcd.print("Show your card:)");
}

void loop() {

if(mfrc522.PICC_IsNewCardPresent()) {
  
  if(mfrc522.PICC_ReadCardSerial()) {
    
     //lcd.clear();
     Serial.print("Tag UID:");
     //lcd.setCursor(0,0);
     //lcd.print("Tag UID:");
     //lcd.setCursor(0,1);
     
     for (byte i = 0; i < mfrc522.uid.size; i++) { 
       
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "); 
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      //lcd.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      //lcd.print(mfrc522.uid.uidByte[i], HEX);
      //lcd.print(" ");
      }
      Serial.println();
      int i = 0;
      boolean match = true;
      while(i<mfrc522.uid.size){
        if(!(int(mfrc522.uid.uidByte[i]) == int(code[i]))) {
          match = false;
        }
        i++;
      }
      delay(3000);
     //lcd.clear();
     //lcd.setCursor(0,0);
     if(match) {
      digitalWrite( LED_ACCESS_PIN , HIGH);
      digitalWrite(BUZZER, HIGH);
      delay (1000);
      digitalWrite(BUZZER, LOW);
      delay (1000);
      /*
      for (int i = 0; i < 2; i++){
        Serial.println("Entrando");
        digitalWrite(BUZZER, HIGH);
        delay (500);
        digitalWrite(BUZZER, LOW);
        delay(500);
      }
      */
      Serial.println("Acceso autorizado, Qchau 8)");
      //lcd.println("Acceso autorizado, Qchau 8)");
      }else{
        //digitalWrite( LED_DENIED_PIN , HIGH);
        for (int i = 0; i < 3; i++){
          
          //Serial.println("Entrando else");
         digitalWrite(BUZZER, HIGH);   //Setting the pin HIGH
         delay(500);
         digitalWrite(BUZZER, LOW);    //Setting the pin HIGH
         delay(400);
      }
        //lcd.println(" Acceso no autorizado, no Qchau :(");
       Serial.println("\nAcceso no autorizado, no Qchau :(");
     }
     Serial.println("============================");
     mfrc522.PICC_HaltA();
      delay(3000); 

      reset_state();
    }
  }
}
void reset_state() {
  //lcd.clear();
  //lcd.setCursor(0,0);
  //lcd.print("Show your card:)");
  digitalWrite( LED_ACCESS_PIN , LOW);
  //digitalWrite( LED_DENIED_PIN , LOW);
}
