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

//Changed from 3 2 to 1 0 
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
unsigned short xPosition;
unsigned short yPosition;
const char sound_pattern_size = 2;
const double sound_pattern[sound_pattern_size] = {261.63, 293.66}; // C4, D4
unsigned char counter;
const int buzzer = 6;
int button;
int index = 0;
int row = 0;
int buttonFlag = 0;
int buttonCounter = 0;
const int rs = 4, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
double currentWeight = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long duration; // variable for the duration of sound wave travel
int distance;
int x=0;
int y=0;
int w = 0;
int z = 0;
int a = 0;
double weight = 0;



int totalTime = 0; 
int motorTimer = 0;
int weightcounter = 0;
//enum SM3_States { SM3_INIT, SM2_S0, SM2_S1};


const int xAxis_median = 100;


typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;


int delay_gcd;
const unsigned short tasksNum = 1;
task tasks[tasksNum];


enum SM1_States{SM1_start, waitPress, wait, state2Press, state2, state3Press, state3, state4Press, state4, startPress, finish};


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





int i =10; 






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
       
        //lcd.print(temp);
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
      
      totalTime++;
     
      Serial.print("total Time: ");
      Serial.println(totalTime);
      currentWeight = scale.get_units();
      Serial.println(w);
      Serial.println(y);
      Serial.println(w);
      Serial.println(z);
      weight = -1 * log(pow((w+0.01), 0.5) + x + pow((y+0.01),0.3) + pow((z+1),-10))*2.5;
      Serial.print("Reading: ");
      Serial.print("currentWeight: ");
      Serial.println(currentWeight);
      Serial.print("Desired Weight: ");
      Serial.println(weight);
      Serial.println("Actual weight: ");
      Serial.print(scale.get_units(),3); //scale.get_units() returns a float
      Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
      Serial.println();

      
       
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
          lcd.print("Weight: ");
          lcd.setCursor(8,0);
          lcd.print(-1*currentWeight);
          lcd.setCursor(0,1);
          lcd.print("button=reset");
         }
         else if (a==-1){
            lcd.setCursor(0,0);
            lcd.print("Time left: ");
            lcd.setCursor(11,0);
            if (10-(totalTime/5) >= 0.1){
            lcd.print(10-(totalTime/5));}
            else{
            lcd.print(0);}
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


      if (button ==0){
        state = startPress;
        totalTime = 0;
        analogWrite(3,LOW);
         x=0;
         y=0;
         w = 0;
         z = 0;
         a = 0;
      }
      else if (totalTime > 50){
        
      
      if (currentWeight < weight/10) {
        //state = finish; // SCALE_BUZZING
        weightcounter++;
        if (weightcounter == 4){
          weightcounter = 0;
          analogWrite(3,LOW);
          totalTime = 0;
          state = finish; 
          
        }
        else{
          analogWrite(3,225);
          state= state4;
        }
      
      }
      else{
        analogWrite(3,225 );
        state = state4;
      }
      }
      else{ 
        state = state4;
      }
      break;


 
              
         


      case finish: // SCALE_BUZZING
      Serial.println("Finished");
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
      state = state4; // SCALE_IDLE
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

   
      
  xPosition = analogRead(A0);
  yPosition = analogRead(A1);

  button= digitalRead(2);

  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }

}
