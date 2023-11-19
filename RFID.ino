#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
void setup() 
{
  lcd.begin();
  lcd.clear();         
  lcd.backlight();
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  lcd.clear();
  if (content.substring(1) == "72 6E 0F 51") //change here the UID of the card/cards that you want to give access
  {
    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("AC Granted !");
    Serial.println("Authorized access");
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    Serial.println();
    delay(3000);
  }
 
 else   {
    lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
    lcd.print("AC Denied !");
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    Serial.println(" Access denied");
    delay(3000);
  }
}
