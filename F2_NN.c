#include <kilolib.h>
#include <stdlib.h>

// initialise bases
int new_message = 0;
int count = 0;
message_t message;
uint32_t last_motion_update = 0;

void setup() {
   // start movement
    message.type = NORMAL;
    message.crc = message_crc(&message);
}

void loop() {
    
    if (kilo_ticks > last_motion_update + 32) {
        
        last_motion_update = kilo_ticks;
       
        if (new_message == 1) {
            new_message = 0;
            
            //GREEN 1
            if (count == 1) {
                set_color(RGB(0, 1, 0));
                spinup_motors();
                set_motors(20.705, 14.450);
                                count = 0;
            }
           
           //BLUE 2
            else if (count == 2) {
                
               set_color(RGB(0, 0, 1));
               spinup_motors();
               
                int rand2motor = rand() % 50 + 1;
        
                if (rand2motor <= 42) {
                    set_motors(93.30,11.475);
                                    count = 0;
                }
                
                else {
                     set_motors(92.05,229.24);
                                    count = 0;
                }
            }
           
           
           // WHITE 3
            else if (count == 3) {
                
                set_color(RGB(1, 1, 1));
                spinup_motors();
                
                int rand4motor = rand() % 50 + 1;
            
                if (rand4motor <= 41) {
                     set_motors(80.04,53.55);
                                    count = 0;
                }
                
                else {
                     set_motors(130.53,174.165);
                                    count = 0;
                }
            
            }
           
            // PINK 4
            else if (count == 4) {
               set_color(RGB(1, 0, 1));
               spinup_motors();
            set_motors(222.51,254.745);
               
              
            }
           
            // YELLOW/ORANGE 5
            else if (count == 5) {
               set_color(RGB(1, 1, 0));
               spinup_motors();
               
               int rand5motor = rand() % 50 + 1;
            
                if (rand5motor <= 26) {
            
                    set_motors(10.515, 216.981);
                               count = 0;
                }
                
                if (rand5motor > 26 && rand5motor <= 38) {
            
                    set_motors(154.27,1);
                               count = 0;
                }
                
                else {
                    set_motors(189.21,232.05);
                               count = 0;
                }
            }
           
            // RED 6
            else {
               set_color(RGB(1, 0, 0));
               spinup_motors();
               set_motors(240.21, 182.835);
                              count = 0;
            }
        }
           
       // NO NEIGHS - OFF
        else {
           set_color(RGB(0, 0, 0));
           spinup_motors();
           set_motors(225.93, 156.06);
        }
    }
}

void message_rx(message_t *message, distance_measurement_t *distance){
   // message reception
    new_message = 1;
    
        
    if (kilo_ticks < last_motion_update + 32 && new_message == 1) {
        count = count+1;
    }
}

message_t *message_tx()
{
    return &message;
}

int main() {
    kilo_init();
    kilo_message_rx = message_rx;
    kilo_message_tx = message_tx;
    kilo_start(setup, loop);
    return 0;
}