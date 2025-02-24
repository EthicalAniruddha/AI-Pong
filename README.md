# Pong Game 2 with AI

Using raylib for first time. I have made a simple pong game using C++ and raylib.

## Some Features

* Player vs. AI match.
* Auto match on
* Added collision for ball with paddle and screen.
* Removed win condition.
* Removed, reset the game by pressing spacebar.
* Displayed framerate, ball x and ball y position.
* Updated UI

## Build Instructions

1. **Install Raylib:** Ensure you have the Raylib library installed on your system.  You can find instructions for installation on the [Raylib website](https://www.raylib.com/).

2. **Compile and Run:**
  ```bash
  git clone https://github.com/EthicalAniruddha/AI-Pong.git && cd AI-Pong && cd PongGame2 && bash build.bash
```
## Code 

 **Structs:**
 ````bash
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
 ````

  ````bash
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
 ````

 **Initialization:**
 ````bash
 InitWindow(1300, 700, "Pong-Game -- Ethical Aniruddha"); // Creates the game window
 SetWindowState(FLAG_VSYNC_HINT); // Enables VSync
 ````

 **Object Creation:** (Almost same as old)
 ````bash
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

 const char* winnerText = nullptr; // Stores the winner text
 ````

 **GameLoop:** (Almost same)
 ````bash
 while (!WindowShouldClose()) {
    .....game logic.....
}
 ````

 **AI Control:(Inefficient maybe?)** (changed)
 ````bash
 if (aiPaddle.y + aiPaddle.height / 2 > ball.y) {
   aiPaddle.y -= aiPaddle.speed * dt;
 } else if (aiPaddle.y + aiPaddle.height / 2 <= ball.y) {
   aiPaddle.y += aiPaddle.speed * dt;
 }
 ````

 ## Controls (Change to only UP and DOWN)

* ```W``` to move up.
* ```S``` to move down.

## Dependency
* Raylib


## License

[The Unlicense](https://choosealicense.com/licenses/unlicense/)


## Screenshots

## OLD
![App Screenshot](https://github.com/EthicalAniruddha/AI-Pong/blob/main/PongGame/win.png)

## NEW
![App Screenshot](https://github.com/EthicalAniruddha/AI-Pong/blob/main/PongGame2/ai.png)

![App Screenshot](https://github.com/EthicalAniruddha/AI-Pong/blob/main/PongGame2/autoOn.png)

