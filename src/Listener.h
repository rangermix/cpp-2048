#ifndef OPERATOR_H
#define OPERATOR_H

// #include <curses.h>
#include <conio.h>
#include <iostream>
#include "StateTracker.h"

class Listener {
   private:
    StateTracker& st;
    static constexpr int UP = 72;
    static constexpr int DOWN = 80;
    static constexpr int LEFT = 75;
    static constexpr int RIGHT = 77;

   public:
    Listener(StateTracker& t) : st(t) {}

    void listen() {
        int c = 0;
        bool finished = false;
        while (!finished) {
            finished = true;
            switch ((c = _getch())) {
                case UP:
                    st.move(StateTracker::Direction::UP);
                    break;
                case DOWN:
                    st.move(StateTracker::Direction::DOWN);
                    break;
                case LEFT:
                    st.move(StateTracker::Direction::LEFT);
                    break;
                case RIGHT:
                    st.move(StateTracker::Direction::RIGHT);
                    break;
                case 'q':
                    exit(0);
                default:
                    finished = false;
                    break;
            }
        }
    }
};

#endif
