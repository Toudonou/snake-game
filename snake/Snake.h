//
// Created by Toudonou on 1/1/25.
//

#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "defines.h"

namespace Snake {
    class Snake {
    public:
        Snake() = default;

        void SetDirection(const Direction direction) { bodyParts[0].direction = direction; }

        [[nodiscard]] Direction GetDirection() const { return bodyParts[0].direction; }

        void Reset(int x, int y);

        void Update();

        void Draw(int tileSize) const;

        void AddPart();

        [[nodiscard]] Point GetPosition() const { return bodyParts.front().position; }
        [[nodiscard]] std::vector<SnakePart> GetSnakeParts() const { return bodyParts; }

    private:
        std::vector<SnakePart> bodyParts;
    };
} // Snake

#endif //SNAKE_H
