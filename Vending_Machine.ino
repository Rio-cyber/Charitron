//=================================
//            Libraries
//=================================
#include <Servo.h>                       //Using the Servo Library
#include <IRremote.h>                    //Using the IR Remote Library
//Libraries needed for the OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//=================================
//            Servo
//=================================
Servo flap;                              //Naming the Servo for easier use
int angle = 0;                           //Define a variable to control the angle of the Servo

//=================================
//            LEDs
//=================================
int redLED = 4;                          //Define variable for Pin Number of Red LED
int greenLED = 5;                        //Define variable for Pin Number of Green LED
int blueLED = 6;                         //Define variable for Pin Number of Blue LED
int i = 1;                               //Define global variable for while loop

//=================================
//            IR Sensor
//=================================
long int IRval;                          //Define variable for the reading of a button press
int IR_Recv = 2;                         //Define variable for Pin Number of IR Receiver
IRrecv irrecv(IR_Recv);                  //Calling function from IRremote Library
decode_results results;                  //Calling function from IRremote Library

//=================================
//            OLED Display
//=================================
#define SCREEN_WIDTH 128                 // OLED display width, in pixels
#define SCREEN_HEIGHT 64                 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
  
  flap.attach(9);                        //Attach the signal pin of Servo to Arduino Digital Pin 9
  pinMode(redLED, OUTPUT);               //Define the Arduino Digital Pin for the Red LED
  pinMode(greenLED, OUTPUT);             //Define the Arduino Digital Pin for the Green LED
  pinMode(blueLED, OUTPUT);              //Define the Arduino Digital Pin for the Blue LED
  Serial.begin(9600);                  //Begin the Serial Monitor for debugging 
  irrecv.enableIRIn();                   // Starts the receiver

    //DISPLAY
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Charitable Smart Vending Machine");
  display.display();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  IR();                                 //Calls the IR Function

  //if payment successful the flap will open and green LED wil glow
  digitalWrite(greenLED, HIGH);         //Green LED glows
  flap.write(90);                       //Servo rotates 90°
  delay(2000);                          //wait for 2 seconds
  flap.write(0);                        //Servo rotates back 90° to its initial position
  digitalWrite(greenLED, LOW);          //Green LED stops glowing


  //if payment not successful
  //Red LED will blink 3 times to indicate unsuccessful payment
  while(i<=3){
    digitalWrite(redLED, HIGH);
    delay(150);
    digitalWrite(redLED, LOW);
    delay(150);
    i++;

    
  }

}


void IR()
{
  //Uses functions from IRremote Library to read values of buttons on the remote
  if (irrecv.decode(&results)){
  IRval = results.value;                  //Stores the value of readings in the variable
  //Serial.println(IRval);                //Debug line to check the value of IR Signal

  if(IRval == 33441975)
  {
    Serial.println("Product Selected");
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("Product Selected");
    display.display(); 
    delay(2500);
    display.clearDisplay();
    display.print("Charitable Smart Vending Machine");
    display.display();
    }
  if(IRval == 33446055)
  {
    Serial.println("Donated Product Selected");
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("Donated Product Selected");
    display.display();
    delay(2500);
    display.clearDisplay();
    display.print("Charitable Smart Vending Machine");
    display.display();
    }
    if(IRval == 33454215)
  {
    Serial.println("Make Donation");
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("Make Donation");
    display.display();
    delay(2500);
    display.clearDisplay();
    display.print("Charitable Smart Vending Machine");
    display.display();
    }
    if(IRval == 33431775 || IRval == 1302831295)
  {
    Serial.println("Vend");
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("Vend");
    display.display();
    delay(2500);
    display.clearDisplay();
    display.print("Charitable Smart Vending Machine");
    display.display();
    }
    if(IRval == 33448095)
  {
    Serial.println("Reset/Cancel");
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("Reset/Cancel");
    display.display();
    delay(2500);
    display.clearDisplay();
    display.print("Charitable Smart Vending Machine");
    display.display();
    }
  irrecv.resume();

}
  }
