#include <superkarel.h>

void turn_right();
void turn_back();

int main() {
    turn_on("task_2.kw");

    set_step_delay(100);

    while(true) {
        if(right_is_clear()) {
            turn_right();
            step();
        } else if(front_is_clear()) {
            step();
        } else if(left_is_clear()) {
            turn_left();
            step();
        } else {
            break;
        }

        if(beepers_present()) {
            pick_beeper();
            turn_back();
        }
    };

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