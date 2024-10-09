#include <superkarel.h>

void turn_right();
void turn_back();

int main() {
    turn_on("task_1.kw");

    set_step_delay(100);

    if(no_beepers_present()) {
        put_beeper();

        do {
            if(right_is_clear()) {
                turn_right();
                step();
            } else if(front_is_clear()) {
                step();
            } else if(left_is_clear()) {
                turn_left();
                step();
            } else {
                turn_back();
                step();
            }

            if(beepers_present()) {
                if(beepers_in_bag()) {
                    break;
                }
                pick_beeper();
            }
        } while(no_beepers_present());
    }

    pick_beeper();
    
    while(not_facing_west()) {
        turn_left();
    }

    turn_off();
}

void turn_right() {
    turn_left();
    turn_left();
    turn_left();
}

void turn_back() {
    turn_left();
    turn_left();
}