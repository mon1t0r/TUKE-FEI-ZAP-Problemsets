#include <superkarel.h>

void turn_right();
void turn_back();

void move_to_beeper();

bool perform_turn();

int main() {
    turn_on("task_6.kw");

    set_step_delay(100);

    while (!perform_turn()) {
        move_to_beeper();
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

void move_to_beeper() {
    while(front_is_clear() && no_beepers_present()) {
        step();
    }
}

bool perform_turn() {
    if(no_beepers_present()) {
        return false;
    }

    while(not_facing_east()) {
        turn_left();
    }

    turn_left();
    pick_beeper();

    if(no_beepers_present()) {
        return false;
    }

    while(beepers_present()) {
        turn_left();
        pick_beeper();
    }

    return facing_north();
}