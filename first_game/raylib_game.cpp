#include "raylib.h"
#include <bits/stdc++.h>
const int TILE = 50; //50 pixels for length and breadth
const int GRID = 10; //10 rows and 10 columns
const int HUD=50; //To display score and stuff

int main(){
    int high_score=0;

    srand(time(0));

    //timer
    float timeLeft=30.0f;

    //row and column for start position
    int Xr=rand()%10; 
    int Xc=rand()%10;

     //row and colum for collectible item
    int Collectible_r=rand()%10;
    int Collectible_c=rand()%10;

    int score=0;

    InitWindow(TILE * GRID, TILE * GRID+HUD, "Grid Game");
    SetTargetFPS(60);


    bool Gameover=false;
    float wallMessageTimer = 0.0f; // before loop
    while (!WindowShouldClose()){
        timeLeft-=GetFrameTime();
        
        bool boundaryHit=false;
        BeginDrawing();
        ClearBackground(BLACK);
        if (timeLeft<=0){
            Gameover=1;
            if (score>high_score)high_score=score;
        }
        if (Gameover){
            
            DrawText("GAME OVER", 100, 200, 50, RED);
            DrawText(TextFormat("Final Score: %d", score), 150, 270, 30, WHITE);
            DrawText(TextFormat("Highest Score: %d", high_score), 160, 320, 20, GREEN);
            DrawText("Press R to restart", 150, 370, 20, GRAY);
            if (IsKeyPressed(KEY_R)){
                score = 0;
                timeLeft = 30.0f;
                Gameover = false;
                Xr = rand()%10;
                Xc = rand()%10;
                Collectible_r = rand()%10;
                Collectible_c = rand()%10;
            }
        }

        else{
        if (IsKeyPressed(KEY_W)){
            if (Xr!=0)Xr--;
            else boundaryHit=1;
        }
        if (IsKeyPressed(KEY_S)){
            if (Xr!=9)Xr++;
            else boundaryHit=1;
        }
        if (IsKeyPressed(KEY_A)){
            if (Xc!=0)Xc--;
            else boundaryHit=1;
        }
        if (IsKeyPressed(KEY_D)){
            if (Xc!=9)Xc++;
            else boundaryHit=1;
        }

        

        //Check if Red Block is over Green Block
        if (Xr==Collectible_r && Xc==Collectible_c){
            score++;
            Collectible_r=rand()%10, Collectible_c=rand()%10;
        }

        DrawRectangle(0, 0, TILE*GRID, HUD, DARKGRAY);
        DrawLine(0, HUD, TILE*GRID, HUD, WHITE);

        // when boundary hit:
        if (boundaryHit) wallMessageTimer = 1.5f; // show for 1.5 seconds

        // every frame, count down and draw if still active:
        if (wallMessageTimer > 0){
            wallMessageTimer -= GetFrameTime();
            DrawText("You hit a Wall!", 160, 15, 20, RED);
        }
        DrawText(TextFormat("Score: %d", score), 10, 15, 20, WHITE);
        DrawText(TextFormat("Time: %1.f", timeLeft), 400,15,20,WHITE);
        
        //Draw Grid
        for (int i = 0; i < GRID; i++){
            for (int j = 0; j < GRID; j++){
                if (i==Xr && j==Xc){ //Generate Start block
                    DrawRectangle(j*TILE, i*TILE+HUD, TILE, TILE, RED);
                }
                else if (i==Collectible_r && j==Collectible_c){ //Generate collectible block
                    DrawRectangle(j*TILE,i*TILE+HUD,TILE,TILE,GREEN);
                }
                else DrawRectangleLines(j*TILE, i*TILE+HUD, TILE, TILE, DARKGRAY);
            }
        }
    }
        EndDrawing();

}
    CloseWindow();
    return 0;
}