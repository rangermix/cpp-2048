#ifndef STATE_TRACKER_H
#define STATE_TRACKER_H

#include <vector>

class StateTracker {
   private:
    std::vector<std::vector<int>> board;
    int size;

    void generateBlock() { board[0][0] = 2; }

   public:
    enum Direction { UP, RIGHT, DOWN, LEFT };

    StateTracker(int n = 4)
        : board(std::vector<std::vector<int>>(n, std::vector<int>(n))),
          size(n) {
        board[1][0] = 2;
        board[3][2] = 2;
        board[2][3] = 2;
    }

    void move(Direction drc) {
        int fix;
        int init_curr = (drc==Direction::UP || drc==Direction::LEFT)?0:size-1;
        int init_next = (drc==Direction::UP || drc==Direction::LEFT)?1:size-2;
        int delta     = (drc==Direction::UP || drc==Direction::LEFT)?1:    -1;

        int pcurr = init_curr;
        int pnext = init_next;
        int& p1   = (drc==Direction::UP || drc==Direction::LEFT)?pnext:pcurr;
        int& p2   = (drc==Direction::UP || drc==Direction::LEFT)?pcurr:pnext;

        int& row_curr = (drc==Direction::UP || drc==Direction::DOWN)?pcurr:fix;
        int& row_next = (drc==Direction::UP || drc==Direction::DOWN)?pnext:fix;
        int& col_curr = (drc==Direction::LEFT || drc==Direction::RIGHT)?pcurr:fix;
        int& col_next = (drc==Direction::LEFT || drc==Direction::RIGHT)?pnext:fix;
        
        for (fix = 0; fix < size; ++fix) {
            pcurr = init_curr;
            pnext = init_next;
            while (pnext < size && pnext >= 0) {
                if (board[row_next][col_next] != 0) {
                    if (board[row_curr][col_curr] == 0) {
                        std::swap(board[row_next][col_next], board[row_curr][col_curr]);
                    } else if (board[row_next][col_next] == board[row_curr][col_curr]) {
                        board[row_curr][col_curr] += board[row_next][col_next];
                        board[row_next][col_next] = 0;
                        pcurr += delta;
                    } else if (p1-p2>1) {
                        pcurr += delta;
                        continue;
                    } else {
                        pcurr = pnext;
                    }
                }
                pnext += delta;
            }
        }

        generateBlock();
    }

    const std::vector<std::vector<int>>& getBoard() { return board; }
};

#endif
