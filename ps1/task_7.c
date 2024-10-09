#include <superkarel.h>

void turn_right();
void turn_back();
void turn_south();

void pick_beeper_safe();

void check_entrance();
void check_room();
bool check_part();

int main() {
    turn_on("task_7.kw");

    set_step_delay(100);

    while(front_is_clear()) {
        check_entrance();
        step();
    }
    check_entrance();

    turn_back();
    while (front_is_clear()) {
        step();
    }
    turn_back();

    while(front_is_clear()) {
        check_room();
        step();
    }
    check_room();

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

void turn_south() {
    while(not_facing_south()) {
        turn_left();
    }
}

void pick_beeper_safe() {
    if(beepers_present()) {
        pick_beeper();
    }
}

void check_entrance() {
    if(left_is_blocked()) {
        return;
    }

    turn_left();
    step();

    put_beeper();

    turn_back();
    step();
    turn_left();
}

void check_room() {
    if(left_is_blocked()) {
        return;
    }

    turn_left();
    step();

    if(right_is_blocked() && left_is_blocked() && front_is_blocked()) {
        pick_beeper_safe();
        turn_back();
        step();
        turn_left();
        return;
    }

    put_beeper();

    if(check_part()) {
        pick_beeper();
    }

    turn_south();
    step();
    turn_left();
}

bool check_part() {
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
            turn_back();
            step();
        }

        if(no_beepers_present()) {
            continue;
        }

        pick_beeper();

        if(beepers_present()) {
            return true;
        }

        put_beeper();
        turn_back();
        if(facing_east()) {
            if(front_is_clear()) {
                step();
            } else if(left_is_clear()) {
                turn_left();
                step();
            } else {
                turn_back();
                step();
            }
        }

        check_part();
        return false;
    }
}