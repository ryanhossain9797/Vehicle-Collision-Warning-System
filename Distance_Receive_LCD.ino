#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7,8,9,10,11,12);

SoftwareSerial BTSerial(2, 3); // RX | TX
String inString = "";
int rArr[] = {0,0,0};

byte righty[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000
};
byte lefty[8] = {
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011,
  B00011
};
byte down7[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};
byte down2[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111
};


byte down3[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000
};

byte down4[8] = {
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

byte clearPixel[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
  };

void setup()
{
  Serial.begin(9600);
  BTSerial.begin(38400);  // HC-05 default speed in AT command more
  
  lcd.createChar(0, lefty);
  lcd.createChar(5,righty);
  lcd.createChar(7,down7);
  lcd.createChar(2,down2);
  lcd.createChar(3,down3); 
  lcd.createChar(4,down4);
  lcd.createChar(9,clearPixel); 
  lcd.begin(16, 2);

  lcd.setCursor(5,0);
  lcd.write(byte(0));
  lcd.write(byte(7));
  lcd.write(byte(7));
  lcd.write(byte(7));
  lcd.write(byte(5));
}

void loop()
{
  inString = "";
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  while (BTSerial.available() > 0) {
    int inChar = BTSerial.read();
    if (isDigit(inChar)){
      //convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
     }
    if ((inChar == '\r') || (inChar == '\n')) {
      Serial.println(inString);
     
      Serial.println(inString.charAt(0));
      if(inString.charAt(0)=='1'){
          rArr[0]=3;
        }else if(inString.charAt(0)=='2'){
          rArr[0]=2;
        }else if(inString.charAt(0)=='3'){
          rArr[0]=1;
        }else{
          rArr[0]=0;
          }
          
      if(inString.charAt(1)=='1'){
         rArr[1]=3;
        }else if(inString.charAt(1)=='2'){
          rArr[1]=2;
        }else if(inString.charAt(1)=='3'){
          rArr[1]=1;
        }else{
          rArr[1]=0;
          }
     
      if(inString.charAt(2)=='1'){
          rArr[2]=3;
        }else if(inString.charAt(2)=='2'){
          rArr[2]=2;
        }else if(inString.charAt(2)=='3'){
          rArr[2]=1;
        }else{
          rArr[2]=0;
          }
    }
    update();
  }
  
}
void update(){
  
 /* left side */
     if(rArr[0]==1){
      lcd.setCursor(4,0);
      lcd.write(byte(0));
     }else{
      lcd.setCursor(4,0);
      lcd.write(byte(9));
      }
      
      if(rArr[0]==2){
      lcd.setCursor(2,0);
      lcd.write(byte(0));
     }else{
      lcd.setCursor(2,0);
      lcd.write(byte(9));
      }

       if(rArr[0]==3){
      lcd.setCursor(0,0);
      lcd.write(byte(0));
     }else{
      lcd.setCursor(0,0);
      lcd.write(byte(9));
      }

   /* right side */ 
     if(rArr[2]==1){
      lcd.setCursor(10,0);
      lcd.write(byte(5));
     }else{
      lcd.setCursor(10,0);
      lcd.write(byte(9));
      }
      
      if(rArr[2]==2){
      lcd.setCursor(13,0);
      lcd.write(byte(5));
     }else{
      lcd.setCursor(13,0);
      lcd.write(byte(9));
      }

      if(rArr[2]==3){
      lcd.setCursor(15,0);
      lcd.write(byte(5));
     }else{
      lcd.setCursor(15,0);
      lcd.write(byte(9));
      }

   /* rear end */ 
     if(rArr[1]==1){
      lcd.setCursor(6,1);
      lcd.write(byte(2));
      lcd.write(byte(2));
      lcd.write(byte(2));
     }else if(rArr[1]==2){
      lcd.setCursor(6,1);
      lcd.write(byte(3));
      lcd.write(byte(3));
      lcd.write(byte(3));
     }else if(rArr[1]==3){
      lcd.setCursor(6,1);
      lcd.write(byte(4));
      lcd.write(byte(4));
      lcd.write(byte(4));
     }else if(rArr[1]==0){
      lcd.setCursor(6,1);
      lcd.write(byte(9));
      lcd.write(byte(9));
      lcd.write(byte(9));
      }

      //delay(1000);
}
