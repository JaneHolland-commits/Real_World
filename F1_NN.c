#include <kilolib.h>

int new_message = 0;
message_t message;
uint32_t last_motion_update = 0;

void setup() {
    message.type = NORMAL;
    message.crc = message_crc(&message);
}

void loop() {
    
    if (kilo_ticks > last_motion_update + 32) {
        
            last_motion_update = kilo_ticks;
            
        if (new_message == 1) {
            new_message = 0;
            set_color(RGB(0, 1, 0));
            spinup_motors();
            set_motors(12.75, 245.82);
    
        }
        else {
            set_color(RGB(1, 0, 0));
            spinup_motors();
            set_motors(93.585, 199.92);
        }
    }
}

void message_rx(message_t *message, distance_measurement_t *distance){
   new_message = 1;
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

