//
// Created by Toudonou on 12/31/24.
//

#ifndef DEFINES_H
#define DEFINES_H

#include <cstdlib>

#include "raylib.h"

namespace Snake {
    enum class Direction {
        NONE,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    enum class SnakePartType {
        HEAD = 1,
        BODY = 2,
        TAIL = 3
    };

    struct Point {
        int x;
        int y;

        bool operator==(const Point &point) const { return x == point.x && y == point.y; }
    };

    struct SnakePart {
        Point position;
        Direction direction;
        SnakePartType type;
    };

    class Apple {
    public:
        Apple() = default;

        ~Apple() = default;

        void Draw(const int tileSize) const {
            DrawCircle(
                position.x * tileSize + tileSize / 2,
                position.y * tileSize + tileSize / 2,
                static_cast<float>(tileSize) / 2, RED
            );
        }

        void SetPosition(const Point &position) { this->position = position; }
        [[nodiscard]] Point GetPosition() const { return this->position; }

    private:
        Point position{};
    };

    inline int min(const int a, const int b) {
        return a < b ? a : b;
    }

    inline int random_number(const int min, const int max) {
        return min + (rand() % (max - min));
    }
} // Snake

#endif //DEFINES_H
