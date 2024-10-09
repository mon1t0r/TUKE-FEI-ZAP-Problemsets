#include <superkarel.h>

void turn_right();
void turn_back();
void turn_east();

void step_safe();
void move_to_wall();
void move_to_beeper();
void move_until_empty();

void pick_row();
void pick_all();

int main() {
    turn_on("task_3.kw");

    set_step_delay(100);

    turn_east();
    
    pick_row();
    turn_right();

    while(front_is_clear() && beepers_present()) {
        step();
        turn_right();
        move_to_wall();
        turn_back();

        pick_row();
        turn_right();
    }

    turn_back();

    if(no_beepers_present()) {
        step_safe();
    }

    move_until_empty();
    turn_left();

    pick_all();
    while (front_is_clear() && beepers_in_bag()) {
        if(right_is_blocked()) {
            put_beeper();
        }
        step();
    }
    turn_left();

    if(front_is_blocked()) {
        turn_back();
    }

    while(true) {
        step();
        turn_left();
        move_to_beeper();
        if(no_beepers_present()) {
            turn_left();
            step_safe();
            break;
        }
        
        pick_all();
        turn_left();
        step_safe();
        turn_left();

        while(front_is_clear()) {
            if(beepers_present()) {
                turn_left();
                step();

                put_beeper();

                turn_back();
                step();
                turn_left();

            }
            if(no_beepers_in_bag()) {
                break;
            }
            step();
        }
        turn_left();
        step();
        if(front_is_blocked()) {
            turn_left();
            move_to_beeper();
            turn_left();
            break;
        }
    }

    move_until_empty();
    turn_left();
    move_to_wall();
    turn_east();

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

void turn_east() {
    while(not_facing_east()) {
        turn_left();
    }
}

void step_safe() {
    if(front_is_clear()) {
        step();
    }
}

void move_to_wall() {
    while(front_is_clear()) {
        step();
    }
}

void move_to_beeper() {
    while (front_is_clear() && no_beepers_present()) {
        step();
    }
}

void move_until_empty() {
    while(front_is_clear() && beepers_present()) {
        step();
    }
    if(no_beepers_present()) {
        turn_back();
        step_safe();
        turn_back();
    }
}

void pick_row() {
    while(front_is_clear()) {
        if(beepers_present()) {
            pick_beeper();
        }
        step();
    }
    while(beepers_in_bag()) {
        put_beeper();
    }
}

void pick_all() {
    while(beepers_present()) {
        pick_beeper();
    }
}