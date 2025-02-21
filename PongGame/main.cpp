#include "raylib.h"
#include <cmath>
#include <algorithm>

struct Ball
{
    float x,y;
    float speedx, speedy;
    float radius;

    void drawCircle() {
        DrawCircle((int)x, (int)y, radius, WHITE); // Circle draws from the centre
    }
};

struct Paddle
{
    float x,y;
    float speed;
    float width, height;

    Rectangle GetRect() {
        return Rectangle{(int)x - width/2,(int) y - height/2, width, height};
    }

    void drawPaddle() {
        DrawRectangleRec(GetRect(), WHITE);
    }
};


int main() {
    InitWindow(800,600, "Pong-Game -- Ethical Aniruddha"); // width, height then title
    SetWindowState(FLAG_VSYNC_HINT);

    Ball ball;

    ball.x = GetScreenWidth()/2.0f;
    ball.y = GetScreenHeight()/2.0f;
    ball.radius = 5;
    ball.speedx = 300;
    ball.speedy = 300;

    Paddle leftPaddle, rightPaddle;

    leftPaddle.width = 10;
    leftPaddle.height = 100;
    leftPaddle.x = 50;
    leftPaddle.y = GetScreenHeight()/2;
    leftPaddle.speed = 500;

    rightPaddle.width = 10;
    rightPaddle.height = 100;
    rightPaddle.x = GetScreenWidth() - 50;
    rightPaddle.y = GetScreenHeight()/2;
    rightPaddle.speed = 500;

    const char* winnerText = nullptr;


    while (!WindowShouldClose()) {

        ball.x += ball.speedx*GetFrameTime();
        ball.y += ball.speedy*GetFrameTime();

        if(ball.y < 0) {
            ball.y = 0;
            ball.speedy *= -1;
        }

        if(ball.y > GetScreenHeight()) {
            ball.y = GetScreenHeight();
            ball.speedy *= -1;
        }

        if((leftPaddle.y - leftPaddle.height/2) < 0) {
            leftPaddle.y = leftPaddle.height/2;
        }

        if((leftPaddle.y + leftPaddle.height/2) > GetScreenHeight()) {
            leftPaddle.y = GetScreenHeight() - leftPaddle.height/2;
        }

        if((rightPaddle.y - rightPaddle.height/2)< 0) {
            rightPaddle.y = rightPaddle.height/2;
        }

        if((rightPaddle.y + rightPaddle.height/2)> GetScreenHeight()) {
            rightPaddle.y = GetScreenHeight() - rightPaddle.height/2;
        }

        if(IsKeyDown(KEY_W)) {
            leftPaddle.y -= leftPaddle.speed*GetFrameTime();
        }

        if(IsKeyDown(KEY_S)) {
            leftPaddle.y += leftPaddle.speed*GetFrameTime();
        }

        if (ball.x > 0) { // fully activate it ig
            int ballCenterY = ball.y + ball.radius;
            int rightPaddleCenterY = rightPaddle.y + rightPaddle.height / 2;
        
            if (ballCenterY < rightPaddleCenterY) { 
                rightPaddle.y -= rightPaddle.speed * GetFrameTime();
            } else if (ballCenterY > rightPaddleCenterY) { 
                rightPaddle.y += rightPaddle.speed * GetFrameTime();
            }

            if(ball.x > GetScreenWidth()) {
                rightPaddle.y = GetScreenHeight()/2;
            }
        }

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, leftPaddle.GetRect())) {
            if(ball.speedx < 0) { 
                ball.speedx *= -1.1f;
                ball.speedy = (ball.y - leftPaddle.y) / (leftPaddle.height/2) * ball.speedx;
            }
        }

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, rightPaddle.GetRect())) {
            if(ball.speedx > 0) {
                ball.speedx *= -1.1f;
                ball.speedy = (ball.y - rightPaddle.y) / (rightPaddle.height/2) * -ball.speedx;
            }
        }

        if (ball.x < 0) {
            winnerText = "AI Wins";
        } 

        if (ball.x > GetScreenWidth()) {
            winnerText = "Left Player Wins";
        }

        if(winnerText != nullptr && IsKeyPressed(KEY_SPACE)) {
            ball.x = GetScreenWidth()/2;
            ball.y = GetScreenHeight()/2;
            ball.speedx = 300;
            ball.speedy = 300;
            winnerText = nullptr;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            ball.drawCircle();
            leftPaddle.drawPaddle(); // width -> 10, height -> 100, x: 50, y = 600/2 - height/2 = 300-50 = 250
            rightPaddle.drawPaddle(); // width -> 10, height -> 100, x: 750 - 10 = 740, y = 600/2 - height/2 = 300-50 = 250
            if(winnerText != nullptr) {
                int textWidth = MeasureText(winnerText, 60);
                DrawText(winnerText,  GetScreenWidth()/2-textWidth/2, GetScreenHeight()/2-30, 60, YELLOW);
            }
            DrawFPS(10,10); // pos: x and pos: y
        EndDrawing();
    }

    CloseWindow();

    return 0;
}