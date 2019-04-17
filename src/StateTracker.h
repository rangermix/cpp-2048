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
        switch (drc) {
            case Direction::UP:
                moveUp();
                break;
            case Direction::RIGHT:
                moveRight();
                break;
            case Direction::DOWN:
                moveDown();
                break;
            case Direction::LEFT:
                moveLeft();
                break;
            default:
                break;
        }
        generateBlock();
    }

    void moveLeft() {
        for (int row = 0; row < size; ++row) {
            int pcurr = 0, pnext = 1;
            while (pnext < size) {
                if (board[row][pnext] != 0) {
                    if (board[row][pcurr] == 0) {
                        std::swap(board[row][pnext], board[row][pcurr]);
                    } else if (board[row][pnext] == board[row][pcurr]) {
                        board[row][pcurr] += board[row][pnext];
                        board[row][pnext] = 0;
                        ++pcurr;
                    } else if (pcurr<pnext-1) {
                        ++pcurr;
                        continue;
                    } else {
                        pcurr = pnext;
                    }
                }
                ++pnext;
            }
        }
    }

    void moveUp() {
        for (int col = 0; col < size; ++col) {
            int pcurr = 0, pnext = 1;
            while (pnext < size) {
                if (board[pnext][col] != 0) {
                    if (board[pcurr][col] == 0) {
                        std::swap(board[pnext][col], board[pcurr][col]);
                    } else if (board[pnext][col] == board[pcurr][col]) {
                        board[pcurr][col] += board[pnext][col];
                        board[pnext][col] = 0;
                        ++pcurr;
                    } else if (pcurr<pnext-1) {
                        ++pcurr;
                        continue;
                    } else {
                        pcurr = pnext;
                    }
                }
                ++pnext;
            }
        }
    }

    void moveRight() {
        for (int row = 0; row < size; ++row) {
            int pcurr = size - 1, pnext = size - 2;
            while (pnext >= 0) {
                if (board[row][pnext] != 0) {
                    if (board[row][pcurr] == 0) {
                        std::swap(board[row][pnext], board[row][pcurr]);
                    } else if (board[row][pnext] == board[row][pcurr]) {
                        board[row][pcurr] += board[row][pnext];
                        board[row][pnext] = 0;
                        --pcurr;
                    } else if (pcurr>pnext+1) {
                        --pcurr;
                        continue;
                    } else {
                        pcurr = pnext;
                    }
                }
                --pnext;
            }
        }
    }

    void moveDown() {
        for (int col = 0; col < size; ++col) {
            int pcurr = size - 1, pnext = size - 2;
            while (pnext >= 0) {
                if (board[pnext][col] != 0) {
                    if (board[pcurr][col] == 0) {
                        std::swap(board[pnext][col], board[pcurr][col]);
                    } else if (board[pnext][col] == board[pcurr][col]) {
                        board[pcurr][col] += board[pnext][col];
                        board[pnext][col] = 0;
                        --pcurr;
                    } else if (pcurr>pnext+1) {
                        --pcurr;
                        continue;
                    } else {
                        pcurr = pnext;
                    }
                }
                --pnext;
            }
        }
    }

    const std::vector<std::vector<int>>& getBoard() { return board; }
};

#endif
