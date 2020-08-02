// Arduino code for CVI project. Temp sensor GUI. 
// read sensor and write to RS232. read RS232 to set alert (buzzer and led)

#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7,6,5,4,3,2); // initialize the LCD display with the numbers of the interface pins

float powervoltage=5; //define the power supply voltage.
int incomingByte;
unsigned short int alarm[4]={70,0,0,0};
int led=0;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);           // set up the LCD's number of columns and rows
  lcd.setCursor(0,0);        // set the cursor to column 0, line 0
  lcd.print("the temp is");  // print a message to the LCD
  pinMode(13,OUTPUT);        // set pin13 as output for alert
}

void loop() 
{
  double temperature = 0.0; 
  double sensorValue = analogRead(A0);             // read the input on analog pin 0
  temperature=(sensorValue/1023)*powervoltage*100; // temp formula from sensor datasheet
  Serial.print(temperature);                       // print out the value you read
  Serial.readBytes((char*)alarm,6);                // read user input for threshold temp for the alert
      if(temperature>alarm[0])
        digitalWrite(13,HIGH);                     // activate led and buzzer when current temp is higher then treshold temp
     else
        digitalWrite(13,LOW);                      // disable led and buzzer when current temp is lower then treshold temp
    lcd.setCursor(0,2);                            // set the cursor to column 0, line 2
    lcd.print(temperature);                        // print a current temp to the LCD
}
