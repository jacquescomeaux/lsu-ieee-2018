// Sketch for defining the setup for QTR sensors and motors. Program for motor control in all directions. 
#include <QTRSensors.h>
#include "Line_Sensors.h"
#include "Motor_Move.h"


// Setup QTR sensors into 8 arrays of 3 individual sensors. 8 * 3 = 24 total sensors used.

// Top array
QTRSensorsRC qtrrc_1((unsigned char[]) { 30, 31, 32}, 3, 4000, QTR_NO_EMITTER_PIN);
unsigned int sensors_1[3];

//Top-Right array
QTRSensorsRC qtrrc_2((unsigned char[]) { 33, 34, 35}, 3, 4000, QTR_NO_EMITTER_PIN);
unsigned int sensors_2[3];

//Right array
QTRSensorsRC qtrrc_3((unsigned char[]) { 36, 37, 38}, 3, 4000, QTR_NO_EMITTER_PIN);
unsigned int sensors_3[3];

//Bottom-Right array
QTRSensorsRC qtrrc_4((unsigned char[]) { 39, 40, 41}, 3, 4000, QTR_NO_EMITTER_PIN);
unsigned int sensors_4[3];

//Bottom array
QTRSensorsRC qtrrc_5((unsigned char[]) { 42, 43, 44}, 3, 4000, QTR_NO_EMITTER_PIN);
unsigned int sensors_5[3];

//Bottom-Left array
QTRSensorsRC qtrrc_6((unsigned char[]) { 45, 46, 47}, 3, 4000, QTR_NO_EMITTER_PIN);
unsigned int sensors_6[3];

//Left array
QTRSensorsRC qtrrc_7((unsigned char[]) { 48, 49, 50}, 3, 4000, QTR_NO_EMITTER_PIN);
unsigned int sensors_7[3];

//Top-Left array
QTRSensorsRC qtrrc_8((unsigned char[]) { 51, 52, 53}, 3, 4000, QTR_NO_EMITTER_PIN);
unsigned int sensors_8[3];


// Arduino setup routine.
void setup() {

// Sensor calibration. Function defined at the very bottom of sketch.
 manual_calibration();

// Initialize sensor data feedack in integers.
qtrrc_1.read(sensors_1);
qtrrc_2.read(sensors_2);
qtrrc_3.read(sensors_3);
qtrrc_4.read(sensors_4);
qtrrc_5.read(sensors_5);
qtrrc_6.read(sensors_6);
qtrrc_7.read(sensors_7);
qtrrc_8.read(sensors_8);

// Constants used as counters for each intersection type, initialized at 1.
int count_1 = 1;
int count_2 = 1;
int count_3 = 1;
int count_4 = 1;
int count_5 = 1;
int count_6 = 1;
int count_7 = 1;
int count_8 = 1;
int count_9 = 1;
int count_10 = 1;
int count_11 = 1;
int count_12 = 1;



// Temporary values just to rid of errors.////////////////////
int tag = 0; 
int start_button = 0;
int camera_bit = 0;
//////////////////////////////////////////////////////////////



// Define objects for classes////////////////////////////////
Line_Sensors L;
Motor_Move M;
///////////////////////////////////////////////////////////////



while (start_button){     // Replace start button with a bit toggl value (start push button).
   update_node(); /* Move motors forward until it detects a line. When sensors detect one of the 12 possible intersections,
   an integer called "tag" is updated to determine the identity of a specific intersection. "Tag ranges from values 1-12 (12 intersections).*/

// Begin of Routine //////////////////////////////////////////////////////////////////////////////////////////////////

/* This routine checks the tag identity value (intersection type), and depending on which tag tag we are currently on, check to see if Raspberry Pi camera gives back a token recognition signal. 
If no camera signal, then do not halt motors for token collection, and just proceed to next node (intersection). */

// Horizontal Intersection (tag = 1) 
while (tag == 1){
  while (count_1 == 1 || count_1 == 2 || count_1 == 3 || count_1 == 4 || count_1 == 5 || count_1 == 6 || count_1 == 7 || count_1 == 8) {
    /* "count" stands for the number of times the robot will visit the same intersection determined by "tag". For instance, this "tag = 1" or "horizontal intersection" is visited 8 times according to count.
     *  Therefore This means that while count is equal from 1-8 in this WHILE routine, the program will proceed to the next instruction.
     */
    if (camera_bit) {           // If camera returns a positive bit signal (1) for recognizing a token at the node, the code will go through this routine.
         M.stop_motors();          // Halt motors to prepare for token collection.
         // VERTICAL LIFT. This is the part of the code where token collection happens. (plate rotates, magnet lowers vertically, triggers to magnetize token, lifts back up vertically, drops token in plate. 
         
      while(count_1 == 1) {     // This means while we have seen the horizontal intersection for the 1st time out of 8. Hence, count = 1.
        M.move_up_freely();       // Move up from initial white box until robot recognizes next line. 
        L.check_node_1();         // Since this is a loop routine, check to see if intersection changes while motors are moving towards the next intersection. 4This loops in a matter of millisecnds.
      }
        // You get the point!

      while (count_1 == 2) {    // Second visitation of horizontal intersection.
        M.move_left_readline();
        L.check_node_1();
      }
     while (count_1 == 3 || count_1 == 4  || count_1 == 5 || count_1 == 6 || count_1 == 7) {  // Third, fourth, fifth, sixth, or seventh visitation of the horizontal intersection.
        M.move_down_readline();
        L.check_node_1();
     }
     while (count_1 == 8){      // Eighth horizontal intersection
       M.move_down_set();
     // if (corner sensors == 0) QUIT entire program;
     }
     
     } else {                   // If camera bit is not true (0), does not see a token on platform!!! Then run this proceeding routine.
      
      while (count_1 == 1){     // First visitation of horizontal line (token not present inside platform). You get the point! The remaining while loops for this "tag = 1" follows this logic. 
        M.move_up_readline();
        L.check_node_1();
      }
      while (count_1 == 2) {
        M.move_left_readline();
        L.check_node_1();
      }
     while (count_1 == 3 || count_1 == 4  || count_1 == 5 || count_1 == 6 || count_1 == 7) {
         M.move_down_readline();
         L.check_node_1();
     }
     while (count_1 == 8){
        M.move_down_set();
        // if (corner sensors == 0) quit;
  } } } }                        // End of tag = 1 (horizontal intersection) routine.


  

// Cross-hair Intersection (tag = 2)
while (tag == 2) {
  while (count_2 == 1 || count_2 == 2 || count_2 == 3 || count_2 == 4 || count_2 == 5 || count_2 == 6 || count_2 == 7 || count_2 == 8 || count_2 == 9 || count_2 == 10 || count_2 == 11 || count_2 == 12) {
    if (camera_bit) {
      M.stop_motors();
      // VERTICAL LIFT
      
      while(count_2 == 1 || count_2 == 2 || count_2 == 3) {
        M.move_left_readline();
        L.check_node_2();
        }
      while (count_2 == 4) {
        M.move_up_readline();
        L.check_node_2();
        }
      while (count_2 == 5 || count_2 == 6 || count_2 == 7){
        M.move_left_readline();
        L.check_node_2();
        }
     while (count_2 == 8) {
        M.move_down_readline();
        L.check_node_2();
        }  
     while (count_2 = 9) {
        M.move_right_readline();
        L.check_node_2();
        }  
     while (count_2 == 10) {
        move_up_readline();
        check_node_2();
        }
     while (count_2 == 11) {
         M.move_left_readline();
         L.check_node_2();
        }
      while (count_2 == 12) { 
         M.move_down_readline();
         L.check_node_2();
        }   
        
      } else {
        
        while (count_2 == 1 || count_2 == 2 || count_2 == 3){
          M.move_left_readline();
          L.check_node_2();
        }
      while (count_2 == 4) {
         M.move_up_readline();
         L.check_node_2();
        }
     while (count_2 == 5 || count_2 == 6 || count_2 == 7){
         M.move_left_readline();
         L.check_node_2();
        }
    while (count_2 == 8){
         M.move_down_readline();
         L.check_node_2();
        }
    while (count_2 == 9) {
         M.move_right_readline();
         L.check_node_2();
        }
      while (count_2 == 11) {
         M.move_left_readline();
         L.check_node_2();
        }
       while (count_2 == 12) {
          M.move_down_readline();
          L.check_node_2();
         } } } } 


         

// Up-right cross slant Intersection (tag = 3)
while (tag == 3){
  while (count_3 == 1 || count_3 == 2 || count_3 == 3 || count_1 == 4 || count_3 == 5 || count_3 == 6 || count_3 == 7 || count_3 == 8 || count_3 == 9) {
    if (camera_bit) {
      M.stop_motors();
      // VERTICAL LIFT
      
      while (count_3 == 1 | count_3 == 2 || count_3 == 3) {
          M.move_up_right_readline();
          L.check_node_3();
          }

      while (count_3 == 4) {
          M.move_up_readline();
          L.check_node_3();
          }

       while (count_3 == 5) {
          M.move_down_left_readline();
          L.check_node_3();
          }

       while (count_3 == 6 || count_3 == 7 || count_3 == 8 || count_3 == 9) {
          M.move_up_right_readline();
          L.check_node_3();
          }
          
    } else {
  
      while (count_3 == 1 | count_3 == 2 || count_3 == 3) {
         M.move_up_readline();
         L.check_node_3();
          }

      while (count_3 == 4) {
         M.move_up_readline();
         L.check_node_3();
          }

      while (count_3 == 5) {
          M.move_down_left_readline();
          L.check_node_3();
          }

       while (count_3 == 6 || count_3 == 7 || count_3 == 8 || count_3 == 9) {
          M.move_up_right_readline();
          L.check_node_3();
       } } } }


          

// Bottom-right cross slant Intersection (tag = 4)
while (tag == 4){
  while (count_4 == 1 || count_4 == 2 || count_4 == 3 || count_4 == 4 || count_4 == 5 || count_4 == 6) {
    if (camera_bit) {
      stop_motors();
      // VERTICAL LIFT
      
      while (count_4 == 1 || count_4 == 2 || count_4 == 3) {
          M.move_down_right_readline();
          L.check_node_4();
          }

      while (count_4 == 4) {
          M.move_right_readline();
          L.check_node_4();
          }

       while (count_4 == 5) {
          M.move_up_right_readline();
          L.check_node_4();
          }

       while (count_4 == 6) {
          M.move_down_readline();
          L.check_node_4();
          }       
    } else {

      while (count_4 == 1 || count_4 == 2 || count_4 == 3) {
        // Move down-right a tad
          M.move_down_right_readline();
          L.check_node_4();
          }

      while (count_4 == 4) {
          M.move_right_readline();
          L.check_node_4();
          }

      while (count_4 == 5) {
          M.move_up_right_readline();
          L.check_node_4();
          }

      while (count_4 == 6) {
         M.move_down_readline();
         L.check_node_4();
          } } } }





// Up-left cross slant Intersection (tag = 5)
while (tag == 5){
  while (count_5 == 1 || count_5 == 2 || count_5 == 3 || count_5 == 4 || count_5 == 5) {
    if (camera_bit) {
       stop_motors();
      // VERTICAL LIFT
      
      while (count_5 == 1 || count_5 == 2 | count_5 == 3 || count_5 == 4) {
          M.move_down_right_readline();
          L.check_node_5();
          }

       while (count_5 == 5) {
          M.move_up_readline();
          L.check_node_5();
          }

    } else {

      while (count_5 == 1 || count_5 == 2 | count_5 == 3 || count_5 == 4) {
          M.move_down_right_readline();
          L.check_node_5();
          }

       while (count_5 == 5) {
         M.move_up_readline();
         L.check_node_5();
          } } } }



          

// Cyan & Grey Intersection (tag = 6)
while (tag == 6){
  while (count_6 == 1 || count_6 == 2 || count_6 == 3) {
    if (camera_bit) {
       stop_motors();
      // VERTICAL LIFT
      
     while (count_6 == 1) {
          M.move_up_right_set();
          M.move_down_left_color_reverse();
          L.check_node_6();
          } 

      while (count_6 == 2) {
          M.move_down_left_readline();
          L.check_node_6();
          } 

      while (count_6 == 3) {
          M.move_up_right_set();
          M.move_down_right_color_reverse();
          L.check_node_6();
          } 
          
    } else {
      
      while (count_6 == 1) {
          M.move_up_right_set();
          M.move_down_left_color_reverse();
          L.check_node_6();
          } 

       while (count_6 == 2) {
          M.move_down_left_readline();
          L.check_node_6();
          } 

       while (count_6 == 3) {
          M.move_up_right_set();
          M.move_down_right_color_reverse();
          L.check_node_6();
          } } } }

          

// Bottom-left Slant Intersection (tag = 7)
while (tag == 7){
  while (count_7 == 1 || count_7 == 2 || count_7 == 3 || count_7 == 4 || count_7 == 5 || count_7 == 6) {
    if (camera_bit) {
       stop_motors();
      // VERTICAL LIFT
      
       while (count_7 == 1 || count_7 == 2 || count_7 == 3) {
          M.move_up_right_readline();
          L.check_node_7(); 
          } 

       while (count_7 == 4) {
          M.move_down_readline();
          L.check_node_7(); 
          } 

       while (count_7 == 5) {
          M.move_up_right_readline();
          L.check_node_7(); 
          } 

        while (count_7 == 6) {
          M.move_left_readline();
          L.check_node_7(); 
          }
    
    } else {

      while (count_7 == 1 || count_7 == 2 || count_7 == 3) {
          M.move_up_right_readline();
          L.check_node_7(); 
          } 

       while (count_7 == 4) {
          M.move_down_readline();
          L.check_node_7(); 
          } 

      while (count_7 == 5) {
          M.move_up_right_readline();
          L.check_node_7(); 
          } 

     
      while (count_7 == 6) {      
          M.move_left_readline();
          L.check_node_7(); 
          } } } }



// Yellow Intersection (tag = 8)
while (tag == 8){
  while (count_8 == 1 || count_8 == 2) {
    if (camera_bit) {
      stop_motors();
      // VERTICAL LIFT
      
       while (count_8 == 1) {
          M.move_down_right_set();
          M.move_up_left_color_reverse()
          L.check_node_7(); 
          } 

       while (count_8 == 2) {
          M.move_up_left_readline();
          L.check_node_7(); 
          } 
                
    } else {

      while (count_8 == 1) {
          M.move_down_right_set();
          M.move_up_left_color_reverse()
          L.check_node_8(); 
          }  

      while (count_8 == 2) {
          M.move_up_left_readline();
          L.check_node_8();
          } } } }


      
// Red Intersection (tag = 9)
while (tag == 9){
  while (count_9 == 1 || count_9 == 2) {
    if (camera_bit) {
      M.stop_motors();
      // VERTICAL LIFT 
      
      while (count_9 == 1) {
          M.move_up_left_set();
          M.move_down_right_color_reverse();
          L.check_node_9();
          }  

       while (count_9 == 2) {
          M.move_down_right_readline();
          L.check_node_9();
          }  
          
    } else {

      while (count_9 == 1) {
          M.move_up_left_set();
          M.move_down_right_color_reverse();
          L.check_node_9();
          }  

        while (count_9 == 2) {
          M.move_down_right_readline();
          L.check_node_9();
          } } } }

// Magenta Intersection (tag = 10)
while (tag == 10){
  while (count_10 == 1 || count_10 == 2) {
    if (camera_bit) {
       M.stop_motors();
      // VERTICAL LIFT 
      
      while (count_10 == 1) {
          M.move_right_set();
          M.move_left_set();
          L.check_node_10();
          }  

    } else {

      while (count_10 == 1) {
          M.move_right_set();
          M.move_left_set();
          L.check_node_10();
          }

       while (count_10 == 2) {
          M.move_left_readline();
          L.check_node_10();
          } } } }

// Green Intersection (tag = 11)
while (tag == 11){
  while (count_11 == 1 || count_11 == 2) {
    if (camera_bit) {
       stop_motors();
      // VERTICAL LIFT 
      
        while (count_11 == 1) {
          M.move_left_set();
          M.move_right_color_reverse();
          L.check_node_11(); 
          }  

        while (count_11 == 2) {
          M.move_right_readline();
          L.check_node_11();
          }  

    } else {

        while (count_11 == 1) {
          M.move_left_set();
          M.move_right_color_reverse();
          L.check_node_11();
          } 

       while (count_11 == 2) {
          M.move_right_readline();
          L.check_node_11();
          } } } } 

// Blue Intersection (tag = 12)
while (tag == 12){
  while (count_12 == 1 || count_12 == 2) {
    if (camera_bit) {
      stop_motors();
      // VERTICAL LIFT 
      
       while (count_12 == 1) {
          M.move_down_left_set();
          M.move_up_right_set();
          L.check_node_12();
          }    

       while (count_12 == 2) {
          M.move_up_right_readline();
          L.check_node_12();
          }     

    } else {
      
      while (count_12 == 1) {
          M.move_down_left_set();
          M.move_up_right_set();
          L.check_node_12();
          } 
              
       while (count_12 == 2) {
          M.move_up_right_readline();
          L.check_node_12();
          } } } } 
}
}


///////////////////////////////////////////////////////////////////////
//Calibration for sensors
void manual_calibration() {

  int i;
  for (i = 0; i < 250; i++)  // the calibration will take a few seconds
  {
    qtrrc_1.calibrate(QTR_NO_EMITTER_PIN);
    delay(20);
  }

  if (DEBUG) { // if true, generate sensor dats via serial output
    Serial.begin(9600);
    for (int i = 0; i < 3; i++)
    {
      Serial.print(qtrrc_1.calibratedMinimumOn[i]);
      Serial.print(' ');
    }
    Serial.println();

    for (int i = 0; i < 3; i++)
    {
      Serial.print(qtrrc_1.calibratedMaximumOn[i]);
      Serial.print(' ');
    }
    Serial.println();
    Serial.println();
  }
}
