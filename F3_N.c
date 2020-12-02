#include <kilolib.h>
#include <stdlib.h>

// 1 represents 1 neighbour perceived: 0.815, 0.514 => 207.825, 131.07
// 2 represents 2 neighbours perceived: 0.056, 0.070 => 14.28, 17.85
// 3 represents 3 neighbours perceived: 0.134, 0.093 => 24.17, 23.715


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
                set_motors(244.8, 213.69);
                                count = 0;
            }
           
           //BLUE 2
            else if (count == 2) {
               set_color(RGB(0, 0, 1));
               spinup_motors();
               set_motors(87.975, 60.34575);
                               count = 0;
            }
            
            //RED 3
            else if (count == 3) {
                set_color(RGB(1, 0, 0));
                spinup_motors();
                set_motors(8.7975, 4.08);
                                count = 0;
            }
           
           // WHITE 0
            else {
               set_color(RGB(1, 1, 1));
              int randLmotor = rand() % 255 + 1;
               int randRmotor = rand() % 255 + 1;
               spinup_motors();
               set_motors(randLmotor, randRmotor);
                               count = 0;
            }
        }
    }
}

void message_rx(message_t *message, distance_measurement_t *distance){
   // message reception
   
    int dist = estimate_distance(distance);
    new_message = 1;
    
        // 57
    if (dist <= 57) {
        count = 1;
    }
        // 66
    else if (dist > 57 && dist <= 66) {
        count = 2;
    }
      //99
    else if (dist > 66 && dist <= 99) {
        count = 3;
    }
    
    else { 
        count = 0;
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