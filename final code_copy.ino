#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
String textMessage;
String redledState = "on";
String blueledState = "on";
String greenledState = "on";

// LEDS connected to pin 10,11,12
const int blueled = 10;
const int greenled = 11;
const int redled = 12;
int S1=1,S2=1,S3=1;

void setup() {
  lcd.begin();
  pinMode(redled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(greenled, OUTPUT);
  lcd.setCursor(0,0);
  lcd.print("GSM Based Home");
  lcd.setCursor(0,1);
  lcd.print("   Automaton    ");
  delay(2000);
  // By default the leds is on
  digitalWrite(redled, HIGH);
  digitalWrite(blueled, HIGH);
  digitalWrite(greenled, HIGH);
 
  
  // Initializing serial commmunication
  Serial.begin(9600);

  // Give time to your GSM shield log on to network
  delay(20000);

  // AT command to set SIM900 to SMS mode
  Serial.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  Serial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("RED BLUE GREEN");

}

void loop(){
  if(Serial.available()>0){
    textMessage = Serial.readString(); 
    textMessage.toUpperCase();   
    delay(10);
  } 
  if (textMessage.indexOf("REDON")>=0){
    S1=1;
    // Turn on red led and save current state
    digitalWrite(redled, HIGH);
    redledState = "on"; 
    textMessage = "";   
  }
  if(textMessage.indexOf("REDOFF")>=0){
    S1=0;
    // Turn off red led and save current state
    digitalWrite(redled, LOW);
    redledState = "off"; 
    textMessage = ""; 
  }
     if(textMessage.indexOf("BLUEON")>=0){
       S2=1;
    // Turn on blueled and save current state
    digitalWrite(blueled, HIGH);
    blueledState = "on"; 
    textMessage = "";   
  }
   if(textMessage.indexOf("BLUEOFF")>=0){
     S2=0;
    // Turn off blueled and save current state
    digitalWrite(blueled, LOW);
    blueledState = "off"; 
    textMessage = ""; 
  }
    if(textMessage.indexOf("GREENON")>=0){
      S3=1;
    // Turn on green led and save current state
    digitalWrite(greenled, HIGH);
    greenledState = "on"; 
    textMessage = "";   
  }
  if (textMessage.indexOf("GREENOFF")>=0){
    S3=0;
    // Turn off grrenled and save current state
    digitalWrite(greenled, LOW);
    greenledState = "off"; 
    textMessage = ""; 
  } if(textMessage.indexOf("ALLON")>=0){
      S3=1;
      S2=1;
      S1=1;
    // Turn on all led and save current state
    digitalWrite(greenled, HIGH);
    greenledState = "on"; 
    digitalWrite(blueled, HIGH);
    blueledState = "on"; 
    digitalWrite(redled, HIGH);
    redledState = "on"; 
    textMessage = "";   
  }
  if (textMessage.indexOf("ALLOFF")>=0){
    S3=0;
    S2=0;
    S1=0;
    // Turn off ALLled and save current state
    digitalWrite(greenled, LOW);
    greenledState = "off"; 
    digitalWrite(blueled, LOW);
    blueledState = "off"; 
    digitalWrite(redled, LOW);
    redledState = "off"; 
    textMessage = ""; 
  }
  lcd.setCursor(3,1);
  if(S1==1){
    lcd.print("ON ");
  }
  else{
    lcd.print("OFF");
  }
    lcd.setCursor(8,1);
  if(S2==1){
    lcd.print("ON ");
  }
  else{
    lcd.print("OFF");
  }
    lcd.setCursor(13,1);
  if(S3==1){
    lcd.print("ON ");
  }
  else{
    lcd.print("OFF");
  }
    if(textMessage.indexOf("REDLEDSTATE")>=0){
    String message = "Red led is " + redledState;
    sendSMS(message);
    textMessage = "";
    
  }
  if(textMessage.indexOf("BLUELEDSTATE")>=0){
    String message = "Blue led is " + blueledState;
    sendSMS(message);
    textMessage = "";
    
  }
  if(textMessage.indexOf("GREENLEDSTATE")>=0){
    String message = "Green led is " + greenledState;
    sendSMS(message);
    textMessage = "";
    
  }
}  
void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
  delay(1200);
  Serial.print("AT");
  delay(3000);
  Serial.println();
  Serial.println("AT+CMGF=1\r"); 
  delay(3000);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  Serial.println();
  Serial.print("AT + CMGS =" );
  Serial.print("\"+919949853122\"");
  Serial.println(); 
  delay(3000);
  // Send the SMS
  Serial.print(message); 
  delay(4000);

  // End AT command with a ^Z, ASCII code 26
  Serial.println();
  Serial.write((char)26);
  delay(100);
  Serial.println();
  delay(5000);
}

