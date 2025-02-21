# Pong Game with AI

Using raylib for first time. I have made a simple pong game using C++ and raylib.

## Some Features

* Player vs. AI match.
* Added collision for ball with paddle and screen.
* Added only win condition.
* Reset the game by pressing spacebar.
* Displayed framerate.

## Build Instructions

1. **Install Raylib:** Ensure you have the Raylib library installed on your system.  You can find instructions for installation on the [Raylib website](https://www.raylib.com/).

2. **Compile and Run:**
  ```bash
  git clone https://github.com/EthicalAniruddha/AI-Pong.git && cd PongGame && bash build.bash && /a.out
```
## Code 

 **Structs:**
 ````bash
 struct Ball
{
    float x, y;         // Ball's x and y position
    float speedx, speedy; // Ball's speed in the x and y directions
    float radius;       // Ball's radius

    void drawCircle() {
        DrawCircle((int)x, (int)y, radius, WHITE); // Draws the ball
    }
};
 ````

  ````bash
struct Paddle
{
    float x, y;      // Paddle's x and y position (center)
    float speed;    // Paddle's speed
    float width, height; // Paddle's width and height

    Rectangle GetRect() {
        return Rectangle{(int)x - width/2,(int) y - height/2, width, height}; // Returns the paddle's rectangle for collision detection
    }

    void drawPaddle() {
        DrawRectangleRec(GetRect(), WHITE); // Draws the paddle
    }
};
 ````

 **Initialization:**
 ````bash
 InitWindow(800, 600, "Pong-Game -- Ethical Aniruddha"); // Creates the game window
 SetWindowState(FLAG_VSYNC_HINT); // Enables VSync
 ````

 **Object Creation:**
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

 **GameLoop:**
 ````bash
 while (!WindowShouldClose()) {
    .....game logic.....
}
 ````

 **AI Control:(Inefficient maybe?)**
 ````bash
 if (ball.x > 0) { // AI activation when the ball is on its side
    int ballCenterY = ball.y + ball.radius;
    int rightPaddleCenterY = rightPaddle.y + rightPaddle.height / 2;

    if (ballCenterY < rightPaddleCenterY) {
        rightPaddle.y -= rightPaddle.speed * GetFrameTime();
    } else if (ballCenterY > rightPaddleCenterY) {
        rightPaddle.y += rightPaddle.speed * GetFrameTime();
    }

    if (ball.x > GetScreenWidth()) { // Reset AI position if ball goes off-screen
        rightPaddle.y = GetScreenHeight() / 2;
    }
}
 ````

 ## Controls

* ```W``` to move up.
* ```S``` to move down.

## Dependency
* Raylib


## License

[The Unlicense](https://choosealicense.com/licenses/unlicense/)


## Screenshots

![App Screenshot](https://github.com/EthicalAniruddha/AI-Pong/blob/main/PongGame/win.png)

