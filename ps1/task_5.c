#include <superkarel.h>

void turn_right();
void turn_back();

void move_to_wall();
void step_safe();

void put_beeper_safe();
void pick_beeper_safe();

void put_to_wall();
void turn_and_pick();

int main() {
    turn_on("task_5.kw");

    set_step_delay(100);

    while(not_facing_west()) {
        turn_left();
    }

    move_to_wall();
    turn_left();

    move_to_wall();
    turn_left();

    put_beeper();

    put_to_wall();
    turn_left();

    put_to_wall();
    turn_left();

    put_to_wall();
    turn_left();

    while (true) {
        while(front_is_clear() && beepers_present()) {
            step();
        }
        put_beeper_safe();

        step_safe();

        if(beepers_present()) {
            break;
        }

        while(front_is_clear() && no_beepers_present()) {
            step();
        }
        turn_back();
    }

    turn_back();
    step_safe();
    turn_right();
    
    while(front_is_clear()) {
        step();
        put_beeper_safe();
    }

    turn_and_pick();

    do {
        while(front_is_clear() && beepers_present()) {
            step();
        }

        turn_and_pick();
    } while(front_is_clear() && beepers_present());

    turn_back();
    step_safe();
    
    while(not_facing_north()) {
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

void move_to_wall() {
    while (front_is_clear()) {
        step();
    }
}

void step_safe() {
    if(front_is_clear()) {
        step();
    }
}

void put_beeper_safe() {
    if(no_beepers_present()) {
        put_beeper();
    }
}

void pick_beeper_safe() {
    if(beepers_present()) {
        pick_beeper();
    }
}

void put_to_wall() {
    while (front_is_clear()) {
        step();
        put_beeper();
    }
}

void turn_and_pick() {
    turn_back();
    step_safe();
    pick_beeper_safe();
    step_safe();
}