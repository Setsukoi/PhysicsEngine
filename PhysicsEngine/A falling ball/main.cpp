#include "raylib.h"

struct BALL {
    Vector2 x; //displacement
    Vector2 v; //velocity
    Vector2 a; //acceleration
    int r; //radius
    Color color;
};

int main() {
    //Initialize the window
    const int WIDTH = 800;
    const int HEIGHT = 600;
    InitWindow(WIDTH, HEIGHT, "A falling ball");

    //Set target FPS
    SetTargetFPS(60);
    
    //Create a ball
    BALL ball;
    ball.x = {400, 100};
    ball.v = {0, 0};
    ball.a = {0, 980}; //500 pixels/s**2
    ball.r = 20;
    ball.color = BLACK;
    
    //User interaction
    bool isDragged = false;
    Vector2 mouse_x1 = {0, 0};

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        //Record mouse position and velocity for every fps
        Vector2 mouse_x2 = GetMousePosition();
        Vector2 mouse_v = {0, 0};
        if (dt > 0) {
            mouse_v.x = (mouse_x2.x - mouse_x1.x) / dt;
            mouse_v.y = (mouse_x2.y - mouse_x1.y) / dt;
        }
        mouse_x1 = mouse_x2;
        
        //Judge if the ball is dragged
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointCircle(mouse_x2, ball.x, ball.r))
            isDragged = true;
        
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if (isDragged) {
                isDragged = false;
                ball.v = mouse_v;
            }
        }
        
        if (isDragged) {
            ball.x = mouse_x2;
            ball.v = {0, 0};
        } else {
            ball.v.y += ball.a.y * dt;
            ball.x.x += ball.v.x * dt; //Constant velocity_x
            ball.x.y += ball.v.y * dt;
        }
        
        //Collision detection and energy loss
        if (!isDragged) {
            //upper wall
            if (ball.x.y - ball.r < 0) {
                ball.x.y = 0 + ball.r;
                ball.v.y = -ball.v.y * 0.8;
            }
    
            //lower wall
            if (ball.x.y + ball.r > HEIGHT) {
                ball.x.y = HEIGHT - ball.r;
                ball.v.y = -ball.v.y * 0.8;
            }
            
            //left wall
            if (ball.x.x - ball.r < 0) {
                ball.x.x = 0 + ball.r;
                ball.v.x = -ball.v.x * 0.8;
            }
            
            //right wall
            if (ball.x.x + ball.r > WIDTH) {
                ball.x.x = WIDTH - ball.r;
                ball.v.x = -ball.v.x * 0.8;
            }
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(ball.x, ball.r, ball.color);
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
