/* Header file for Line-Sensor Class. This is for:
(1) Identifying the location of the robot in accordance to node.
(2) Checking for new node for each iteration through the looping routine.
*/

class Line_Sensors {
  
  public:

// Node (Intersection) Identifier
// Assigns each recognized intersection to an integer. Ex: tag = 1, 2, 3, ..... 12. These integers are used as ID's for each individual intersection so that the program can keep track of its placement.
   void update_node() { 
      if (sensors_3[2] > 2000 && sensors_7[2] > 2000){                                                            // Horizontal Line tag
            tag = 1; 
      }
        else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){       // Cross-hair tag
            tag = 2;
        }
      else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {        // Up-right cross slant Intersection
            tag = 3;
        }
      else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {        // Bottom-right cross slant Intersection
            tag = 4;
        }
      else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {        // Up-left cross slant Intersection
            tag = 5;
        }
      else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {                               // Cyan & Grey Intersection
            tag = 6;
        }
      else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {        // Bottom-left Slant Intersection
            tag = 7;
        }
      else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {                                      // Yellow Intersection
            tag = 8;
        }
      else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {                                      // Red Intersection
            tag = 9;
        }
      else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {                                      // Magenta Intersection
            tag = 10;
        }
      else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {                                      // Green Intersection
            tag = 11;
        }
      else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {                                      // Blue Intersection
            tag = 12;
        }     
    }




// Horizontal intersection check. Checks all new intersections for any indication of a new intersection while robot is line following.
// These routines will occur as a check constantly through the looping. This loops with the motors. This will constantly check for any updated intersections. To tell the code to tailor its executions to a new intersection it recognized.  
  void check_node_1() {
       if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
            count_1++;
            setup();        // Loop back to the top of the setup routine in the main code file.
        }
        else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
            count_1++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
            count_1++;
            setup();
        }
        else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
            count_1++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
            count_1++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
            count_1++;
            setup();
        }
        else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
            count_1++;
            setup();
        }
        else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
            count_1++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
            count_1++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
            count_1++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
            count_1++;
            setup();
        }
        else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
            count_1++;
            setup();
        }  
        }

// Cross-hair Intersection check 
  void check_node_2() {
        if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
            count_2++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
            count_2++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
            count_2++;
            setup();
        }
        else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
            count_2++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
            count_2++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
            count_2++;
            setup();
        }
        else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
            count_2++;
            setup();
        }
        else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
            count_2++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
            count_2++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
            count_2++;
            setup();
        }
        else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
            count_2++;
            setup();
        }
        else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
            count_2++;
            setup();
        }  
        }

// Up-right cross slant Intersection check
  void check_node_3(){
          if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
              count_3++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
              count_3++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_3++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
              count_3++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
              count_3++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_3++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
              count_3++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
              count_3++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
              count_3++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_3++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
              count_3++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_3++;
              setup();
          }  
          }

// Bottom-right cross slant Intersection check
  void check_node_4(){
          if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
              count_4++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
              count_4++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_4++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
              count_4++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
              count_4++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_4++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
              count_4++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
              count_4++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
              count_4++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_4++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
              count_4++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_4++;
              setup();
          }  
          }

          
// Up-left cross slant Intersection check
  void check_node_5(){
        if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
              count_5++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
              count_5++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_5++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
              count_5++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
              count_5++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_5++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
              count_5++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
              count_5++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
              count_5++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_5++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
              count_5++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_5++;
              setup();
          }  
          }

// Cyan & Grey Intersection check
  void check_node_6(){
         if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
              count_6++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
              count_6++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_6++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
              count_6++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
              count_6++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_6++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
              count_6++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
              count_6++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
              count_6++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_6++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
              count_6++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_6++;
              setup();
          }  
          }

// Bottom-left Slant Intersection check
  void check_node_7(){
         if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
              count_7++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
              count_7++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_7++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
              count_7++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
              count_7++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_7++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
              count_7++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
              count_7++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
              count_7++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_7++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
              count_7++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_7++;
              setup();
          }  
          }

// Yellow Intersection check
  void check_node_8(){
          if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
              count_8++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
              count_8++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_8++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
              count_8++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
              count_8++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_8++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
              count_8++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
              count_8++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
              count_8++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_8++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
              count_8++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_8++;
              setup();
          }  
          }

// Red Intersection check
  void check_node_9(){
           if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
              count_9++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
              count_9++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_9++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
              count_9++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
              count_9++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_9++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
              count_9++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
              count_9++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
              count_9++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_9++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
              count_9++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_9++;
              setup();
          }  
          }

// Magenta Intersection check
  void check_node_10(){
          if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
              count_10++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
              count_10++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_10++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
              count_10++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
              count_10++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_10++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
              count_10++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
              count_10++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
              count_10++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_10++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
              count_10++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_10++;
              setup();
          }  
          }

// Green Intersection check
  void check_node_11(){
          if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
              count_11++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
              count_11++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_11++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
              count_11++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
              count_11++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_11++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
              count_11++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
              count_11++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
              count_11++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_11++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
              count_11++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_11++;
              setup();
          }
          }

// Blue Intersection check
  void check_node_12(){
          if (sensors_3[2] > 2000 && sensors_7[2] > 2000){ 
              count_12++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_5[2] > 2000 && sensors_7[2] > 2000){
              count_12++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_2[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_12++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_4[2] > 2000 && sensors_5[2] > 2000 && sensors_8[2] > 2000) {
              count_12++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] > 2000 && sensors_7[2] > 2000 && sensors_8[2] > 2000) {
              count_12++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] > 2000 && sensors_6[2] > 2000) {
              count_12++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] > 2000 && sensors_6[2] > 2000 && sensors_7[2] > 2000) {
              count_12++;
              setup();
          }
          else if (sensors_3[2] > 2000 && sensors_5[2] && sensors_8[2] > 2000) {
              count_12++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_4[2] && sensors_7[2] > 2000) {
              count_12++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_12++;
              setup();
          }
          else if (sensors_1[2] > 2000 && sensors_3[2] && sensors_5[2] > 2000) {
              count_12++;
              setup();
          }
          else if (sensors_2[2] > 2000 && sensors_5[2] && sensors_7[2] > 2000) {
              count_12++;
              setup();
          }
          }
};


