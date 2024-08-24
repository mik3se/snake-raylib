#include "raylib.h"
#include <vector>

struct snakeObject{
    float posX;
    float posY;
    int length;
};

int main() {
    const int screenWidth = 400;
    const int screenHeight = 400;

    snakeObject player = {(float)screenWidth/(25*2),(float)screenHeight/(25*2), 3};
    std::vector<Vector2> oldPos{};
    oldPos.push_back({(float)player.posX - 2,(float)player.posY});
    oldPos.push_back({(float)player.posX - 1,(float)player.posY});
    Vector2 apple = {(float)player.posX + 2, (float)player.posY};

    float deltaTime;
    float speedDivisor = 100.0f;

    Vector2 direction = {1, 0};
    bool flag = false;
    bool dead = false;
    bool appleEaten = false;
    int8_t hasMovedInDirection = 1;

    SetTraceLogLevel(LOG_ERROR);
    InitWindow(screenWidth, screenHeight, "snake - window");
    //SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    while(!WindowShouldClose()){
        //Update
        deltaTime = GetFrameTime() * 1000.0f;

        if(dead && IsKeyPressed(KEY_R)){
            player = {(float)screenWidth/(25*2),(float)screenHeight/(25*2), 3};
            oldPos.clear();
            oldPos.push_back({(float)player.posX - 2,(float)player.posY});
            oldPos.push_back({(float)player.posX - 1,(float)player.posY});
            apple = {(float)player.posX + 2, (float)player.posY};
            direction = {1, 0};
            hasMovedInDirection = 1;
            dead = false;
        }

        if(!dead && direction.y == 0 && hasMovedInDirection == 1){
            if(IsKeyPressed(KEY_W)){
                direction = {0, -1};
            }
            else if(IsKeyPressed(KEY_S)){
                direction = {0, 1};
            }
        }
        if(!dead && direction.x == 0 && hasMovedInDirection == 0){
            if(IsKeyPressed(KEY_A)){
                direction = {-1, 0};
            }
            else if(IsKeyPressed(KEY_D)){
                direction = {1, 0};
            }
        }
        if(!dead && (int)player.posX == (int)apple.x && (int)player.posY == (int)apple.y) {
            appleEaten = true;
            apple = {(float) GetRandomValue(0, 24), (float) GetRandomValue(0, 24)};
        }
        else if(!dead && ((int)(player.posX + direction.x * (1/speedDivisor) * deltaTime) != (int)player.posX || (int)(player.posY + direction.y * (1/speedDivisor) * deltaTime) != (int)player.posY)) {
            for (int i = 1; i < oldPos.size(); i++) {
                oldPos[i - 1] = oldPos[i];
            }
            if(appleEaten){
                player.length += 1;
                oldPos.push_back({(float)((int) player.posX), (float)((int) player.posY)});
                appleEaten = false;
            }
            oldPos[oldPos.size() - 1].x = (float)((int)player.posX);
            oldPos[oldPos.size() - 1].y = (float)((int)player.posY);
            if(direction.y == 0){
                hasMovedInDirection = 1;
            }
            else{
                hasMovedInDirection = 0;
            }
        }
        if(!dead && (int)(player.posX + direction.x * (1/speedDivisor) * deltaTime) >= 25
        || (int)(player.posY + direction.y * (1/speedDivisor) * deltaTime) >= 25
        || (int)(player.posX + direction.x * (1/speedDivisor) * deltaTime) < 0
        || (int)(player.posY + direction.y * (1/speedDivisor) * deltaTime) < 0){
            dead = true;
        }
        if(!dead) {
            player.posX += direction.x * (1/speedDivisor) * deltaTime;
            player.posY += direction.y * (1/speedDivisor) * deltaTime;
        }

        flag = true;
        while(flag && !dead) {
            for(int i = 0; i < oldPos.size(); i++) {
                if (apple.x == oldPos[i].x && apple.y == oldPos[i].y) {
                    flag = false;
                }
            }
            for(int i = 0; i < oldPos.size(); i++) {
                if ((int)player.posX == (int)oldPos[i].x && (int)player.posY == (int)oldPos[i].y) {
                    dead = true;
                }
            }
            if (!flag) {
                apple = {(float)GetRandomValue(0, 24), (float)GetRandomValue(0, 24)};
                flag = true;
            } else {
                flag = false;
            }
        }
        //Draw
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangle((int)apple.x * screenWidth/25, (int)apple.y * screenHeight/25, screenWidth/25, screenHeight/25, RED);
        for(int i = 0; i < player.length - 1; i++){
            DrawRectangle((int)(oldPos[oldPos.size() - (i + 1)].x) * screenWidth/25, (int)(oldPos[oldPos.size() - (i + 1)].y) * screenHeight/25, screenWidth/25, screenHeight/25, GREEN);
        }
        DrawRectangle((int)player.posX * screenWidth/25, (int)player.posY * screenHeight/25, screenWidth/25, screenHeight/25, GREEN);
        DrawText(TextFormat("%d", (int)player.length - 3), 10, 10, 20, WHITE);
        if(dead){
            DrawText("You Died!", screenWidth/2 - MeasureText("You Died!", 80)/2, screenHeight/2 - 65, 80, WHITE);
            DrawText("Press r to restart", screenWidth/2 - MeasureText("Press r to restart", 30)/2, screenHeight/2 + 35, 30, WHITE);
        }

        EndDrawing();
    }

    return 0;
}