//
// Created by Toudonou on 12/31/24.
//

#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Snake.h"

namespace Snake {
    class Game {
    public:
        Game();

        ~Game() = default;

        void Run();

    private:
        int screenWidth{}, screenHeight{};
        int maxFps{};
        Image icon{};
        Sound snakeEatingCollisionSound{}, snakeWallCollisionSound{}, snakeSelfCollisionSound{};

        bool isPaused{};
        bool isGameOver{};
        float gameSpeed{};
        int score{};
        int worldRows{};
        int worldCols{};
        int tileSize{};
        Snake snake = Snake();
        Apple apple = Apple();

        void Init();

        void Update(int &fpsCounter);

        void Draw() const;

        void Input();

        void Restart();

        bool CollisionSnakeApple() const;

        bool CollisionSnakeSnake() const;

        bool CollisionWall() const;
    };
} // Snake

#endif //GAME_H
