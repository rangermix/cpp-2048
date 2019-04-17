#ifndef STATE_TRACKER_H
#define STATE_TRACKER_H

#include <vector>
#include <tuple>
#include <unordered_set>
#include <functional>

class StateTracker {
   private:
    std::function<size_t (const std::tuple<int, int>&)> hash = [](const auto& t){
        auto [i, j] = t;
        auto h = std::hash<int>();
        return h(10*i+j);
    };
    std::vector<std::vector<int>> board;
    std::unordered_set<std::tuple<int, int>, decltype(hash)> freeBlocks;
    int size;

    // TODO: implement findEmpty
    std::tuple<int, int> findEmpty() {
        // int n = freeBlocks.size();

        return std::make_tuple(0, 0);
    }

    void generateBlock() {
        auto [i, j] = findEmpty();
        update(i, j, 2);
    }

    void update(int i, int j, int val) {
        board[i][j] = val;
        if (val==0) {
            freeBlocks.emplace(i, j);
        } else {
            freeBlocks.erase(std::make_tuple(i, j));
        }
    }

   public:
    enum Direction { UP, RIGHT, DOWN, LEFT };

    StateTracker(int n = 4)
        : board(std::vector<std::vector<int>>(n, std::vector<int>(n))),
          freeBlocks(std::unordered_set<std::tuple<int, int>, decltype(hash)>(16, hash)),
          size(n) {
        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                freeBlocks.emplace(i, j);
            }
        }
        generateBlock();
        generateBlock();
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
                        int t = board[row_next][col_next];
                        update(row_next, col_next, board[row_curr][col_curr]);
                        update(row_curr, col_curr, t);
                    } else if (board[row_next][col_next] == board[row_curr][col_curr]) {
                        update(row_curr, col_curr, board[row_curr][col_curr]*2);
                        update(row_next, col_next, 0);
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
