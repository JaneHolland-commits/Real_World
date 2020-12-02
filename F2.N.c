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
                set_motors(244.8,11.22);
                                count = 0;
            }
           
           //BLUE 2
            else if (count == 2) {
                
               set_color(RGB(0, 0, 1));
               spinup_motors();
               set_motors(169.06,10.71);
                                count = 0;
            }
           
           
           // WHITE 3
            else if (count == 3) {
                
                set_color(RGB(1, 1, 1));
                spinup_motors();
                
                int rand3motor = rand() % 50 + 1;
            
                if (rand3motor <= 16) {
                                 
                    set_motors(179.01,42.075);
                                    count = 0;
                }
                  
                else if (rand3motor > 16 && rand3motor <= 30) {               
                    set_motors(236.84,12.75);
                                   count = 0;
                }
                                 
                else if (rand3motor > 30 && rand3motor <= 40) {                  
                    set_motors(164.47,19.38);
                                count =0;
                }
                                 
                else {
                    set_motors(216.495,165.75);
                                    count = 0;
                }
            
            }
           
            // PINK 4
            else if (count == 4) {
               set_color(RGB(1, 0, 1));
               spinup_motors();
               
              
                int rand4motor = rand() % 50 + 1;
            
                if (rand4motor <= 16) {
                    
                    set_motors(239.7,252.45);
                    count = 0;
                }
                
                else if (rand4motor > 16 && rand4motor <= 29) {
                    
                    set_motors(71.14,74.2);
                    count = 0;
                }
                
                else if (rand4motor > 29 && rand4motor <= 36) {
                    
                    set_motors(202.725,115.51);
                    count = 0;
                }
                
                 else if (rand4motor > 36 && rand4motor <= 41) {
                    
                    set_motors(163.9,182.5);
                    count = 0;
                }
                
                else {
                    
                    set_motors(22.95,52.02);
                    count = 0;
                }
               
              
            }
           
            // YELLOW/ORANGE 5
            else if (count == 5) {
               set_color(RGB(1, 1, 0));
               spinup_motors();
               set_motors(95.88,252.45);
            }
           
            // RED 6
            else {
               set_color(RGB(1, 0, 0));
               spinup_motors();
               set_motors(164.22,203.133);
                              count = 0;
            }
        }
           
       // NO NEIGHS - OFF
        else {
           set_color(RGB(0, 0, 0));
           spinup_motors();
           set_motors(202.72, 146.62);
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