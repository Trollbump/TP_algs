// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
    4. Пятнашки
    Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду:
                [ 1  2  3  4 ]
                [ 5  6  7  8 ]
                [ 9  10 11 12] 
                [ 13 14 15 0 ]
    где 0 задает пустую ячейку.
    Достаточно найти хотя бы какое-то решение.
    Число перемещений костяшек не обязано быть минимальным.
*/

#include <iostream>
#include <array>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cstring>

const char FieldSize = 16;
const std::array<char, FieldSize> finishField = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

struct GameStateHasher;

class GameState {
 public:
    GameState(const std::array<char, FieldSize> & field) : field(field), emptyPos(-1)
    {
        for (int i = 0; i < FieldSize; ++i) {
            if (field[i] == 0) emptyPos = i;
        }
    }

    GameState(const GameState & other) : field(other.field), emptyPos(other.emptyPos) {}
    GameState &operator=(const GameState &state) = default;

    bool IsComplete() const {
        return field == finishField;
    }

    bool IsSolvable() const {
        return (getInvCount() + 1 + emptyPos/4) % 2 == 0;
    }

    bool CanMoveUp() const {
        return emptyPos < 12;
    }

    bool CanMoveDown() const {
        return emptyPos > 4;
    }

    bool CanMoveLeft() const {
        return emptyPos % 4 != 3;
    }

    bool CanMoveRight() const {
        return emptyPos % 4 != 0;
    }

    GameState MoveUp() const {
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos + 4]);
        newState.emptyPos += 4;
        return newState;
    }

    GameState MoveDown() const {
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos - 4]);
        newState.emptyPos -= 4;
        return newState;
    }

    GameState MoveLeft() const {
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos + 1]);
        newState.emptyPos += 1;
        return newState;
    }

    GameState MoveRight() const {
        GameState newState(*this);
        std::swap(newState.field[emptyPos], newState.field[emptyPos - 1]);
        newState.emptyPos -= 1;
        return newState;
    }

    int Heuristic() const {
        int heuristic = 0, totalDist = 0;
        for (int i = 0; i < field.size(); ++i) {
            if (field[i] != 0) {
                totalDist = abs(field[i] - (i + 1));
            } else {
                totalDist = FieldSize - i;
            }

            heuristic += totalDist / 4;
            totalDist %= 4;
            if (totalDist == 3) {
                heuristic += 2;
            } else {
                heuristic += totalDist;
            }
        }

        return heuristic;
    }

    bool operator==(const GameState &other) const {
        return field == other.field;
    }

    bool operator<(const GameState &other) const {
        return Heuristic() > other.Heuristic();
    }

 private:
    size_t getInvCount() const {
        size_t inv_count = 0;
        for (int i = 0; i < FieldSize - 1; ++i) {
            for (int j = i+1; j < FieldSize; ++j) {
                if (field[i] && field[j] && field[i] > field[j]) {
                    ++inv_count;
                }
            }
        }
        return inv_count;
    }
    std::array<char, FieldSize> field;
    char emptyPos;

    friend struct GameStateHasher;
    friend std::ostream& operator<<(std::ostream &out, const GameState &state);
};

struct GameStateHasher {
 public:
     size_t operator()(const GameState & state) const {
         size_t hash = 0;
         std::memcpy(&hash, state.field.data(), sizeof(hash));
         return hash;
     }
};

std::ostream& operator<<(std::ostream &out, const GameState &state) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            out << static_cast<int>(state.field[i*4 + j]) << " ";
        }
        out << std::endl;
    }
    return out;
}

std::string GetSolution(const std::array<char, FieldSize> & field) {
    GameState startState(field);

    if (!startState.IsSolvable()) return "-1";

    std::unordered_map<GameState, std::string, GameStateHasher> visited;
    std::priority_queue<GameState> queue;

    visited[startState] = "";
    queue.emplace(startState);

    while (!(queue.top() == finishField)) {
        GameState state = queue.top();
        queue.pop();

        if (state.CanMoveLeft()) {
            GameState newState = state.MoveLeft();
            if (visited.find(newState) == visited.end()) { // not found
                visited[newState] = visited[state] + "L";
                queue.emplace(newState);
            }
        }

        if (state.CanMoveRight()) {
            GameState newState = state.MoveRight();
            if (visited.find(newState) == visited.end()) { // not found
                visited[newState] = visited[state] + "R";
                queue.emplace(newState);
            }
        }

        if (state.CanMoveUp()) {
            GameState newState = state.MoveUp();
            if (visited.find(newState) == visited.end()) { // not found
                visited[newState] = visited[state] + "U";
                queue.emplace(newState);
            }
        }

        if (state.CanMoveDown()) {
            GameState newState = state.MoveDown();
            if (visited.find(newState) == visited.end()) { // not found
                visited[newState] = visited[state] + "D";
                queue.emplace(newState);
            }
        }
    // std::cout << state << std::endl; // output all steps
    }

    return visited[finishField];
}

/*
Test:

0 1 2 3
5 6 7 4
9 10 11 8
13 14 15 12

Answer: 6 LLLUUU
*/

int main() {
    std::array<char, FieldSize> field{};
    int digit = 0;
    for (size_t i = 0; i < 16; ++i) {
        std::cin >> digit;
        field[i] = digit;
    }

    std::string solution = GetSolution(field);
    std::cout << solution.size() << std::endl << solution << std::endl;
    return 0;
}
