//#include <Adafruit_ST7789.h>
//#include <Adafruit_ST7735.h>
//float temp;
/* 
  Nokia Tune
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// change this to make the song slower or faster
int tempo = 180;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Nokia Ringtone 
  // Score available at https://musescore.com/user/29944637/scores/5266155
  
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2, 
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

/*
 Example using the SparkFun HX711 breakout board with a scale
 By: Nathan Seidle
 SparkFun Electronics
 Date: November 19th, 2014
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 This example demonstrates basic scale output. See the calibration sketch to get the calibration_factor for your
 specific load cell setup.
 This example code uses bogde's excellent library:"https://github.com/bogde/HX711"
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
 The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
 based load cell which should allow a user to measure everything from a few grams to tens of tons.
 Arduino pin 2 -> HX711 CLK
 3 -> DAT
 5V -> VCC
 GND -> GND
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
*/

#include "HX711.h"


#define calibration_factor -198900.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

//Changed from 3 2 to A4 A5 
#define LOADCELL_DOUT_PIN  A4
#define LOADCELL_SCK_PIN  A5

HX711 scale;
int tempPin = 2;
#define trigPin 13
#define echoPin 12
#include <LiquidCrystal.h>
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int light_pattern_size = 2;
const char light_pattern[light_pattern_size] = {0x00, 0x0F};
unsigned char b_temp;
//unsigned char temp;
signed int food_weight;
unsigned int evaluate_food;
unsigned short xPosition;
unsigned short yPosition;
const char sound_pattern_size = 2;
const double sound_pattern[sound_pattern_size] = {261.63, 293.66}; // C4, D4
unsigned char counter;
const int buzzer = 6;
double weight = 0;
int button;
int index = 0;
int row = 0;
int buttonFlag = 0;
int buttonCounter = 0;
int motor_flag = 0; //stops motor when flag is raised
const int rs = 4, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long duration; // variable for the duration of sound wave travel
int distance;
int x=0;
int y=0;
int w = 0;
int z = 0;
int a = 0;
int totalTime = 0; 
int motorTimer = 0;


const int xAxis_median = 100;


typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;


int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States{SM1_start, waitPress, wait, state2Press, state2, state3Press, state3, state4Press, state4, startPress};

enum SM2_States{SM2_INIT, Go};

enum SM3_States {SM3_INIT, weight_check};

void setup() {
    pinMode(6, OUTPUT);
    pinMode(13, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(12, INPUT); 
  lcd.setCursor(0,0);
  pinMode(3, OUTPUT);
//  state = SM1_start;
  pinMode(A0, INPUT);
    pinMode(A1, INPUT);
  xPosition = analogRead(A0);
  yPosition = analogRead(A1);
   lcd.begin(16,2);
   pinMode(2, INPUT_PULLUP);
     unsigned char i = 0;
  tasks[i].state = SM1_start;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &tick2;
  i++;
  tasks[i].state = SM3_INIT;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &tick3;
  delay_gcd = 100;
   digitalWrite(3, LOW);
   
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("HX711 scale demo");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  pinMode(buzzer, OUTPUT);

  Serial.println("Readings:");
}

  //int VRM= analogRead(A2);
  int VRM = (5.00 / 1023.00) * analogRead(A2);      //Conversion to voltage
  int VRC = 5 - VRM;
  int RTC = VRM / (VRC / 10000);               //Resistance of RT

  int lnC = log(RTC / 10000);
  int TXC = (1 / ((lnC / 3977) + (1 / 298.15))); //Temperature from thermistor

  int TXCY = TXC - 273.15; //Conversion to Celsius
int  TXCM = (TXCY * (9/5)) + 32; 
float  temp = TXCM + 14;

int desired = temp;
int i =10; 

int tick2(int state){
  switch(state){
    case SM2_INIT: 
      if(desired < temp) {
        //analogWrite(3, 250);
        state = Go;
      }
      else {
        //digitalWrite(3,LOW);
        state = SM2_INIT;
      }
      break;

    case Go: 
    
  
      if(desired >= temp) {
        //digitalWrite(3,LOW);
        state = SM2_INIT;
        //digitalWrite(3,LOW);
      }
      else{
        if (distance < 10){
    analogWrite(3, 100);
  }
  else if(distance < 20){
    analogWrite(3, 125);
  }
  else if(distance < 30){
    analogWrite(3, 175);      
  }

  else { 
    analogWrite(3, 250);
  }
        state = Go; 
      }
  }
  return state;
}

//Tick Function Utilized to Report and Check Weight (Buzzer + Weight Scale)
int tick3(int state){
 switch(state){
    case SM3_INIT: 
    state = weight_check;
    break;

    case weight_check:
    state = weight_check;
    break;

    default:
    state = weight_check;
    break;
  }

  switch(state){
    case SM3_INIT:
    break;

    case weight_check:
  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 3); //scale.get_units() returns a float
  Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();

Serial.print("Weight: ");
Serial.print(weight);
Serial.println();

  if (scale.get_units() < (-1*weight)){
    motor_flag = 1;
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
  }
    break;

    default:
    break;
  }
  return state;
}

int tick(int state){
  switch (state){
    case SM1_start: 
    Serial.println(button);
    Serial.println("stateStart");
    if(i==10){
     lcd.clear();
     lcd.setCursor(0,0);
     Serial.println(xPosition);
       Serial.println(yPosition);
     lcd.print("Pet Type?");
     
     lcd.setCursor(1,1);
      if(xPosition > 750 && x!=3){
          x++;
        }
        else if(xPosition < 250 && x!=0){
          x--;
        }
    if (x==0)
      lcd.print("bird");
    else if (x==1)
      lcd.print("hamster");
    else if (x==2)
      lcd.print("cat");
     else if (x==3)
      lcd.print("dog"); 
     
    lcd.blink();
    lcd.setCursor(0,1);
  i=0;
    }
      if(button ==0){
        
        state = waitPress;
      }
      else{
        i++;
        state = SM1_start;
      }
    break;

    case waitPress: 
    Serial.println("waitPress");
    Serial.println(button);
      if(button ==1){
        state = wait;
       
      }
      else{
        state = waitPress;
        
      }
      break;

    case wait: 
     Serial.println("wait");
      if(button ==0){
        i=0;
        lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Active?");
     lcd.setCursor(1,1);
     
      //lcd.print(temp);
      //lcd.print(" *F");
      state = state2Press;
        
      }
      else{

       lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Pet Size");
     Serial.println(button);
     Serial.println(xPosition);
     Serial.println(yPosition);
     lcd.setCursor(1,1);
      if(xPosition > 750 && w!=3){
          w++;
        }
        else if(xPosition < 250 && w!=0){
          w--;
        }
    if (w==0)
      lcd.print("extra small");
    else if (w==1)
      lcd.print("small");
    else if (w==2)
      lcd.print("medium");
     else if (w==3)
      lcd.print("big"); 
     
    lcd.blink();
    lcd.setCursor(0,1);
        state = wait;
      }
      break;

      case state2Press: 
        if(button ==1){
          state = state2;
          
        }
        else{
          state = state2Press;
        }
        break;

      case state2: 

      Serial.println("wait");
      if(button ==0){
        i=0;
        lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Diet?");
     lcd.setCursor(1,1);
     
      //lcd.print(temp);
      //lcd.print(" *F");
      state = state3Press;
        
      }
      else{

       lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Active?");
     Serial.println(button);
     Serial.println(xPosition);
     Serial.println(yPosition);
     lcd.setCursor(1,1);
      if(xPosition > 750 && y!=3){
          y++;
        }
        else if(xPosition < 250 && y!=0){
          y--;
        }
    if (y==0)
      lcd.print("Not active");
    else if (y==1)
      lcd.print("semi-active");
    else if (y==2)
      lcd.print("active");
     else if (y==3)
      lcd.print("very active"); 
     
    lcd.blink();
    lcd.setCursor(0,1);
        state = state2;
      }
      break;


    case state3Press: 
      if(button ==1){
        state = state3;
      }
      else{
        state = state3Press;
      }
      break;

    case state3: 
      Serial.println("wait");
      if(button ==0){
        i=0;
        lcd.clear();
     lcd.setCursor(0,0);
     //lcd.print("Loading");
     lcd.setCursor(1,1);
     
      lcd.print(temp);
      //lcd.print(" *F");
      state = state4Press;
        
      }
      else{

       lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Diet?");
     Serial.println(button);
     Serial.println(xPosition);
     Serial.println(yPosition);
     lcd.setCursor(1,1);
      if(xPosition > 750 && z!=2){
          z++;
        }
        else if(xPosition < 250 && z!=0){
          z--;
        }
    if (z==0)
      lcd.print("No");
    else if (z==1)
      lcd.print("Semi");
    else if (z==2)
      lcd.print("Yes"); 
     
    lcd.blink();
    lcd.setCursor(0,1);
        state = state3;
      }
      break;


    case state4Press: 
      if(button ==1){
        state=state4;
      }

      else{
        state=state4Press;
      }

      break;



      case state4: 

      if (button ==0){
        state = startPress;
         x=0;
        y=0;
         w = 0;
         z = 0;
         a = 0;
      }

      else {
           
      weight = log(pow(x,.3) + pow(y,.5) + pow(z,.1)) * 5; 
            
         
      double timePass = weight * 1000;
      Serial.print("timepass: ");
      Serial.println(timePass);
       
      if (!motor_flag)      
      analogWrite(3, 200);
      else
      analogWrite(3,0);
            
         lcd.clear();
         lcd.noBlink();
         if(a==0){
          lcd.setCursor(0,0);
          lcd.print("Waiting for food");
          lcd.setCursor(0,1);
          lcd.print("button=reset");
         }
         else if (a==1){
          lcd.setCursor(0,0);
          lcd.print("Weight: 0");
          lcd.setCursor(0,1);
          lcd.print("button=reset");
         }
         else if (a==-1){
          lcd.setCursor(0,0);
          lcd.print("Time left: 0");
          lcd.setCursor(0,1);
          lcd.print("button=reset");
         }
         lcd.setCursor(0,0);
         
         Serial.println(button);
         Serial.println(xPosition);
         Serial.println(yPosition);
         lcd.setCursor(1,1);
          if(xPosition > 750 && a!=1){
              a++;
            }
            else if(xPosition < 250 && a!=-1){
              a--;
            }
        state = state4;
      }
      break;



      case startPress: 
          if(button == 1){
            state = SM1_start;
          }
          else{
            state = startPress;
          }
          break;
          
  
      default: break;
   
  }
  return state;
}


void loop() {
 long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  //Serial.println(distance);

  Serial.print("distance: ");
      Serial.println(distance);
    totalTime++; 
    
  //  Serial.print("total time: ");
    
    if (totalTime > 6500)
      totalTime = 0;
      
    //Serial.println(totalTime);
    digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  xPosition = analogRead(A0);
  yPosition = analogRead(A1);
   temp = analogRead(A2);
   int VRT= analogRead(A2);
    VRT = (5.00 / 1023.00) * VRT;      //Conversion to voltage
  int VR = 5 - VRT;
  int RT = VRT / (VR / 10000);               //Resistance of RT

  int ln = log(RT / 10000);
  int TX = (1 / ((ln / 3977) + (1 / 298.15))); //Temperature from thermistor

  TX = TX - 273.15; //Conversion to Celsius
  TX = (TX * (9/5)) + 32; 
  temp = TX + 14;
  //Serial.println(temp);
  button= digitalRead(2);

    unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
//tick();


  //Serial.println(
  //if(desired < temp) {analogWrite(3, 100); }
  //else{digitalWrite(3,LOW); }
   //delay(1000); // update sensor reading each one second
}
