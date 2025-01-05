//
// Created by Toudonou on 12/31/24.
//

#include "raylib.h"
#include "Game.h"

#include "assets_data.h"

namespace Snake {
    Game::Game() {
        Init();
    }

    void Game::Run() {
        int fpsCounter = 0;
        Restart();

        while (!WindowShouldClose()) {
            fpsCounter++;

            Input();
            Update(fpsCounter);
            Draw();
        }

        UnloadImage(icon);
        UnloadSound(snakeEatingCollisionSound);
        UnloadSound(snakeSelfCollisionSound);
        UnloadSound(snakeWallCollisionSound);

        CloseAudioDevice();
        CloseWindow();
    }

    void Game::Init() {
        maxFps = 60;

        isPaused = false;
        isGameOver = false;
        score = 0;
        gameSpeed = 0.2f;

        tileSize = 40;
        worldRows = 17;
        worldCols = 25;
        screenWidth = worldCols * tileSize;
        screenHeight = worldRows * tileSize;

        InitWindow(screenWidth, screenHeight, "Snake");
        InitAudioDevice();

        SetTargetFPS(maxFps);
        icon = LoadImageFromMemory(".png", apple_data_png, apple_data_png_len);
        SetWindowIcon(icon);
        snakeEatingCollisionSound = LoadSoundFromWave(
            LoadWaveFromMemory(".wav", snake_eat_wav, snake_eat_wav_len)
        );
        snakeWallCollisionSound = LoadSoundFromWave(
            LoadWaveFromMemory(".wav", snake_wall_collision_wav, snake_wall_collision_wav_len)
        );
        snakeSelfCollisionSound = LoadSoundFromWave(
            LoadWaveFromMemory(".wav", snake_self_collision_wav, snake_self_collision_wav_len)
        );
    }

    void Game::Update(int& fpsCounter) {
        if (CollisionSnakeSnake()) {
            PlaySound(snakeSelfCollisionSound);
            Restart();
            return;
        }
        if (CollisionWall()) {
            PlaySound(snakeWallCollisionSound);
            Restart();
            return;
        }

        if (CollisionSnakeApple()) {
            int counter = 0;
            PlaySound(snakeEatingCollisionSound);
            score++;
            do {
                apple.SetPosition({.x = random_number(0, worldCols), .y = random_number(0, worldRows)});
                counter++;
                if (counter > 1000) {
                    Restart();
                    return;
                }
            } while (CollisionSnakeApple());
            snake.AddPart();
        }

        if (fpsCounter > maxFps * gameSpeed) {
            fpsCounter = 0;
            snake.Update();
        }
    }

    void Game::Draw() const {
        BeginDrawing();
        ClearBackground(DARKGREEN);

        for (int i = 0; i < worldRows; i++) {
            for (int j = 0; j < worldCols; j++) {
                DrawRectangle(
                    j * tileSize, i * tileSize,
                    tileSize, tileSize,
                    (i + j) % 2 ? (Color){0, 228, 48, 255} : (Color){0, 228, 48, 250}
                );
            }
        }
        snake.Draw(tileSize);
        apple.Draw(tileSize);
        DrawText(TextFormat("Score : %d", score), 50, 50, 20, BLACK);
        EndDrawing();
    }

    void Game::Input() {
        if (IsKeyPressed(KEY_UP) && snake.GetDirection() != Direction::DOWN)
            snake.SetDirection(Direction::UP);
        else if (IsKeyPressed(KEY_DOWN) && snake.GetDirection() != Direction::UP)
            snake.SetDirection(Direction::DOWN);
        else if (IsKeyPressed(KEY_LEFT) && snake.GetDirection() != Direction::RIGHT)
            snake.SetDirection(Direction::LEFT);
        else if (IsKeyPressed(KEY_RIGHT) && snake.GetDirection() != Direction::LEFT)
            snake.SetDirection(Direction::RIGHT);
    }

    void Game::Restart() {
        isPaused = false;
        isGameOver = false;
        score = 0;
        snake.Reset(worldRows / 2, worldCols / 2);
        apple.SetPosition({.x = worldRows / 3, .y = worldRows / 2});
    }

    bool Game::CollisionSnakeApple() const {
        for (const auto& part : snake.GetSnakeParts()) {
            if (part.position == apple.GetPosition()) return true;
        }
        return false;
    }

    bool Game::CollisionSnakeSnake() const {
        const auto head = snake.GetSnakeParts().front();
        for (const auto& part : snake.GetSnakeParts()) {
            if (part.type != SnakePartType::HEAD && part.position == head.position) return true;
        }
        return false;
    }

    bool Game::CollisionWall() const {
        if (const auto head = snake.GetSnakeParts().front();
            !(0 <= head.position.x && head.position.x < worldCols) ||
            !(0 <= head.position.y && head.position.y < worldRows))
            return true;
        return false;
    }
} // Snake
