#ifndef VIEWER_H
#define VIEWER_H

#include <conio.h>
#include <iomanip>
#include <iostream>
#include "StateTracker.h"

class Viewer {
   private:
    StateTracker& st;

   public:
    Viewer(StateTracker& t) : st(t) {}

    void printBoard() {
        auto board = st.getBoard();
        for (const auto& row : board) {
            for (const auto& num : row) {
                std::cout << std::setw(10) << (num == 0 ? 0 : num);
            }
            std::cout << "\n\n";
        }
        std::cout << "\n\n";
    }

    static void clearScreen() {
        // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
        // clrscr();
        // std::cout << "\033c";
    }
};

#endif
