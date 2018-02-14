// Defines all possible motor movements.
// "[motor movement]_readline" syntax is the movement for reading a line.
// "[motor movement]_set" syntax is for moving the robot a set distance (not reading line).
// "[motor movement]_color_reverse" syntax is for the reversed movement of a previous movement that preceeded it. It holds the same distance as the preceeding movement.

class Motor_Move {

  public:

       void move_up_readline() {    
      
    }
    

       void move_up_freely() {                    // This is for the robot to move up coninuously until the line sensors recognizes the next intersection it approaches.
      
    }
    

       void move_up_set() {
      
    }


       void move_down_readline() {
      
    }
    

       void move_down_set() {
      
    }


       void move_left_readline() {
      
    }
    

       void move_left_set() {
      
    }
    

       void move_left_color_reverse() {
      
    }
    

       void move_right_readline() {
          
    }
    

       void move_right_set() {
      
    }


       void move_right_color_reverse() {
      
    }


       void move_up_left_readline() {
      
    }


       void move_up_left_set() {
      
    }
    

       void move_up_right_readline() {
      
    }
    


       void move_up_left_color_reverse() {
      
    }
    

       void move_up_right_readline() {
      
    }
    

       void move_up_right_set() {
      
    }
    

       void move_up_right_color_reverse() {
      
    }
    

       void move_down_right_readline() {
      
    }
    

       void move_down_right_set() {
      
    }
    

       void move_down_right_color_reverse() {
      
    }
    

       void move_down_left_readline() {
     
   }
   

       void move_down_left_set() {
    
   }


       void move_down_left_color_reverse() {
    
   }


       void stop_motors(){                // This function halts all drivetrain motors.
    
   }

};


