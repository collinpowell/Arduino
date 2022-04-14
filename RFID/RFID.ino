

/*
 * 
 * Original code from keypad.h library: MultiKey.ino (@author Mark Stanley)
 * Written and updated by Ahmad Shamshiri (Robojax.com) on May 06, 2020 at 19:37 in Ajax, Ontario, Canada
 * 
 * This code for 5X4 keypad with text (more than 1 character);
 * written the code to allow any text for key. 
keypad has 
            "F1",  "F2", "#", "*",
            "1",  "2", "3", "UP",
            "4",  "5", "6", "DOWN",
            "7",  "8", "9", "ESC",
            "LEFT",  "0", "RIGHT", "ENT"  
             
 * Video code: 
 * 
 * Watch video for details: https://youtu.be/sbQ3D1_x_tg
 * 
 * Neee Wiring Diagram and full explanation of the code :http://robojax.com/L/?id=62

 
You can get the wiring diagram and full explanition of this code from my Arduino Course at Udemy.com
Learn Arduino step by step with all library, codes, wiring diagram all in one place
visit my course now http://robojax.com/L/?id=62

If you found this tutorial helpful, please support me so I can continue creating 
content like this. You can be my Patron and have early access to my videos here  http://robojax.com/L/?id=63
or make donation using PayPal http://robojax.com/L/?id=64

* 
 * Code is available at http://robojax.com/learn/arduino

 * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see . 

 */

#include <Keypad.h>

const byte ROWS = 5; //5 rows
const byte COLS = 4; //4 columns
char* specialKeys[] ={
            "F1",  "F2", "#", "*",
            "1",  "2", "3", "UP",
            "4",  "5", "6", "DOWN",
            "7",  "8", "9", "ESC",
            "LEFT",  "0", "RIGHT", "ENTER"  
                    };

                    
char specialKeysID[] = {
        'A',  'B', '#', '*',
        '1',  '2', '3', 'C',
        '4',  '5', '6', 'D',
        '7',  '8', '9', 'E',
        'F',  '0', 'G', 'H'
      };                    

char keys[ROWS][COLS] = {
{specialKeysID[0],  specialKeysID[1], specialKeysID[2], specialKeysID[3]},
{specialKeysID[4],  specialKeysID[5], specialKeysID[6], specialKeysID[7]},
{specialKeysID[8],  specialKeysID[9], specialKeysID[10], specialKeysID[11]},
{specialKeysID[12],  specialKeysID[13], specialKeysID[14], specialKeysID[15]},
{specialKeysID[16],  specialKeysID[17], specialKeysID[18], specialKeysID[19]}
};


byte rowPins[ROWS] = {2,3,4,5,6}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {A1,A0,8,7}; //connect to the column pinouts of the kpd

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;


void setup() {
  // Robojax 5x4 keypad test
  Serial.begin(9600);
  Serial.println("RFID");
}


void loop() {
  // Robojax 5x4 keypad test
  char key = keypad.getKey();
    // just print the pressed key
    
   if (key){
    Serial.print("Key: ");
    Serial.println(getKey(key));
  } 
  if(getKey(key) =="ENTER")
  {
     Serial.println("ENTER is pressed");   
  }
  
//Robojax.com 5x4 keypad detecting string value
}  // End loop


/*
 * getKey()
 * @brief gets the actual key value from single character 
 * @param k is character
 * @return returns acualt key value
 * Written by Ahmad Shamshiri for robojax.com
 * on May 06, 2020 at 19:37 in Ajax, Ontario, Canada
 */
char* getKey(char *k)
{
 //Robojax.com 5x4 keypad detecting string value
  for(int i=0; i<20; i++)
  {
    if(specialKeysID[i] ==k) return specialKeys[i];
  }
 
}//getKey
