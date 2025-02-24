#include "raylib.h"

Color LightGreen = Color{129, 204, 184, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color Green = Color{141, 214, 138};
Color Yellow = Color{243, 231, 91, 255};

struct Paddle {
    public:
    float x, y;
    float speed;
    float height;
    float width;

    Rectangle GetRect() {
        return Rectangle{x, y, width, height};
    }

    void Draw() {
        DrawRectangleRounded(GetRect(), 0.8, 0, WHITE);
    }
};

Paddle aiPaddle; // right
Paddle humanPaddle; // left

struct Ball {
    public:
    float x, y;
    float speedX, speedY;
    float radius;

    void Draw() {
        DrawCircle(x, y, radius, Yellow);
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speedChoices[2] = {1, -1};
        speedX = 300, speedY = 300;
        aiPaddle.speed = 350;
        humanPaddle.speed = 350;
        speedX *= speedChoices[GetRandomValue(0, 1)];
        speedY *= speedChoices[GetRandomValue(0, 1)];
    }
};

Ball ball;

int main() {
    int height = 700;
    int width = 1300;
    InitWindow(width, height, "Pong -- EthicalAniruddha");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);

    ball.radius = 10;
    ball.x = width / 2;
    ball.y = height / 2;
    ball.speedX = 300;
    ball.speedY = 300;

    aiPaddle.height = 110;
    aiPaddle.width = 20;
    aiPaddle.speed = 350;
    aiPaddle.x = width - 10 - aiPaddle.width;
    aiPaddle.y = height / 2 - aiPaddle.height / 2;

    humanPaddle.height = 110;
    humanPaddle.width = 20;
    humanPaddle.speed = 350;
    humanPaddle.x = 10;
    humanPaddle.y = height / 2 - aiPaddle.height / 2;

    int humanScore = 0, aiScore = 0;

    // Button setup
    Rectangle autoPlayButton = {20, height - 60, 120, 40};
    Color buttonColor = LIGHTGRAY;
    bool autoPlay = false;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Vector2 mousePos = GetMousePosition();

        // Button logic
        if (CheckCollisionPointRec(mousePos, autoPlayButton)) {
            buttonColor = GRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                autoPlay = !autoPlay;
            }
        } else {
            buttonColor = LIGHTGRAY;
        }

        // Paddle movement
        if (autoPlay) {
            if (humanPaddle.y + humanPaddle.height / 2 > ball.y) {
                humanPaddle.y -= humanPaddle.speed * dt;
            } else if (humanPaddle.y + humanPaddle.height / 2 <= ball.y) {
                humanPaddle.y += humanPaddle.speed * dt;
            }
        } else {
            if (IsKeyDown(KEY_UP)) {
                humanPaddle.y -= humanPaddle.speed * dt;
            } else if (IsKeyDown(KEY_DOWN)) {
                humanPaddle.y += humanPaddle.speed * dt;
            }
        }

        if (aiPaddle.y + aiPaddle.height / 2 > ball.y) {
            aiPaddle.y -= aiPaddle.speed * dt;
        } else if (aiPaddle.y + aiPaddle.height / 2 <= ball.y) {
            aiPaddle.y += aiPaddle.speed * dt;
        }

        ball.x += ball.speedX * dt;
        ball.y += ball.speedY * dt;

        if (ball.y > height) {
            ball.y = height;
            ball.speedY *= -1;
        }
        if (ball.y < 0) {
            ball.y = 0;
            ball.speedY *= -1;
        }
        if (ball.x > width) {
            ball.x = width;
            ball.speedX *= -1;
            humanScore++;
            ball.ResetBall();
        }
        if (ball.x < 0) {
            ball.x = 0;
            ball.speedX *= -1;
            aiScore++;
            ball.ResetBall();
        }

        if (humanPaddle.y + humanPaddle.height > height) {
            humanPaddle.y = height - humanPaddle.height;
        }
        if (humanPaddle.y < 0) {
            humanPaddle.y = 0;
        }
        if (aiPaddle.y + aiPaddle.height > height) {
            aiPaddle.y = height - aiPaddle.height;
        }
        if (aiPaddle.y < 0) {
            aiPaddle.y = 0;
        }

        if (CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius, humanPaddle.GetRect())) {
            if (ball.x > 0) {
                ball.speedX *= -1.1f;
                aiPaddle.speed *= 1.1f;
                humanPaddle.speed *= 1.1f;
                ball.speedY = ((ball.y - humanPaddle.y) / (humanPaddle.height / 2.0f)) * ball.speedX;
            }
        }
        if (CheckCollisionCircleRec((Vector2){ball.x, ball.y}, ball.radius, aiPaddle.GetRect())) {
            if (ball.x < width) {
                ball.speedX *= -1.1f;
                aiPaddle.speed *= 1.1f;
                humanPaddle.speed *= 1.1f;
                ball.speedY = ((ball.y - aiPaddle.y) / (aiPaddle.height / 2.0f)) * -ball.speedX;
            }
        }

        BeginDrawing();
        ClearBackground(DarkGreen);
        DrawCircle(width / 2, height / 2, 150, LightGreen);
        DrawLine(width / 2, 0, width / 2, height, WHITE);
        DrawRectangleRec(autoPlayButton, buttonColor);
        DrawText(autoPlay ? "Auto: ON" : "Auto: OFF", autoPlayButton.x + 10, autoPlayButton.y + 10, 20, DARKGRAY);
        ball.Draw();
        aiPaddle.Draw();
        humanPaddle.Draw();
        DrawText(TextFormat("%i", humanScore), width / 4, 40, 40, GREEN);
        DrawText(TextFormat("%i", aiScore), 3 * width / 4, 40, 40, GREEN);
        DrawText(TextFormat("FPS: %d", GetFPS()), 20, 10, 17, Yellow);
        DrawText(TextFormat("Ball x: %.2f", ball.x), 100, 10, 17, Yellow);
        DrawText(TextFormat("Ball y: %.2f", ball.y), 220, 10, 17, Yellow);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
