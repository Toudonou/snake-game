//
// Created by Toudonou on 1/1/25.
//

#include "raylib.h"
#include "Snake.h"

namespace Snake {
    void Snake::Reset(const int x, const int y) {
        bodyParts.clear();
        bodyParts.push_back(SnakePart{
            .position = {x, y}, .direction = Direction::NONE, .type = SnakePartType::HEAD
        });
        bodyParts.push_back(SnakePart{
            .position = {x - 1, y}, .direction = Direction::NONE, .type = SnakePartType::BODY
        });
        bodyParts.push_back(SnakePart{
            .position = {x - 2, y}, .direction = Direction::NONE, .type = SnakePartType::TAIL
        });
    }

    void Snake::Update() {
        if (bodyParts.front().direction == Direction::NONE) return;

        for (int i = static_cast<int>(bodyParts.size()) - 1; i > 0; i--) {
            bodyParts[i].position = bodyParts[i - 1].position;
            bodyParts[i].direction = bodyParts[i - 1].direction;
        }
        switch (bodyParts.front().direction) {
            case Direction::UP:
                bodyParts.front().position.y--;
                break;
            case Direction::DOWN:
                bodyParts.front().position.y++;
                break;
            case Direction::LEFT:
                bodyParts.front().position.x--;
                break;
            case Direction::RIGHT:
                bodyParts.front().position.x++;
                break;
            default: break;
        }
    }

    void Snake::Draw(const int tileSize) const {
        float step = 0;
        auto color = (Color){0, 117, 44, 255};

        for (const auto [position, direction, type]: bodyParts) {
            color.a = 255 - static_cast<unsigned char>((255 - 150) * step);
            DrawCircle(
                position.x * tileSize + tileSize / 2,
                position.y * tileSize + tileSize / 2,
                static_cast<float>(tileSize) / 2, color
            );
            step += 1 / static_cast<float>(bodyParts.size());
        }
    }

    void Snake::AddPart() {
        for (int i = 1; i < static_cast<int>(bodyParts.size()); i++) bodyParts[i].type = SnakePartType::BODY;
        bodyParts.push_back(SnakePart{
            .position = {-1, -1}, .direction = Direction::NONE, .type = SnakePartType::TAIL
        });
        Update();
    }
} // Snake
