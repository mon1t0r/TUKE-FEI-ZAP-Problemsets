#include <superkarel.h>

void turn_right();
void turn_back();

void move_back_to_wall();

void put_beeper_safe();

void check_line();

int main() {
    turn_on("task_4.kw");

    set_step_delay(100);

    while(true) {
        turn_left();
        check_line();
        turn_left();

        if(front_is_blocked()) {
            break;
        }

        step();
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

void move_back_to_wall() {
    turn_back();
    while (front_is_clear()) {
        step();
    }
}

void put_beeper_safe() {
    if(no_beepers_present()) {
        put_beeper();
    }
}

void check_line() {
    while(front_is_clear() && no_beepers_present()) {
        step();
    }

    if(no_beepers_present()) {
        move_back_to_wall();
        return;
    }

    move_back_to_wall();
    turn_back();
    
    while(front_is_clear()) {
        put_beeper_safe();
        step();
    }

    put_beeper_safe();

    move_back_to_wall();
}