#include "raylib.h"
#include <bits/stdc++.h>
using namespace std;
//Constants ------------------------------------------------------------
const int TILE = 50; //50 pixels for length and breadth
const int GRID = 20; //10 rows and 10 columns
const int HUD= 50; //To display score and stuff
const int WIN_W=TILE*GRID;
const int WIN_H=TILE*GRID;

//BFS function
vector<pair<int,int>> findPath(pair<int,int> start,pair<int,int> end,set<pair<int,int>>& obstacles)
{
    map<pair<int,int>, pair<int,int>> parent; //to store parent of cells we reached to
    queue<pair<int,int>> q; //queue DS for performing BFS
    set<pair<int,int>> vis; //To avoid forever looping
    q.push(start);
    vis.insert(start);
    while (!q.empty()){
        pair<int,int> front=q.front();
        q.pop();
        if (front==end)
        {
            vector<pair<int,int>> path;
            pair<int,int> curr = end;
            while (curr != start){
                path.push_back(curr);
                curr = parent[curr];
            }
            reverse(path.begin(), path.end());
            return path;
        }
        if (front.first-1>=0 && obstacles.count({front.first-1,front.second})==0  && !vis.count({front.first-1, front.second})){
            vis.insert({front.first-1,front.second});
            parent[{front.first-1, front.second}] = front;
            q.push({front.first-1,front.second});
        }
        if (front.first+1<=20 && obstacles.count({front.first+1,front.second})==0  && !vis.count({front.first+1, front.second})){
            vis.insert({front.first+1,front.second});
            parent[{front.first+1, front.second}] = front;
            q.push({front.first+1,front.second});
        }
        if (front.second-1>=0 && obstacles.count({front.first,front.second-1})==0 && !vis.count({front.first, front.second-1}) ){
            vis.insert({front.first,front.second-1});
            parent[{front.first, front.second-1}] = front;
            q.push({front.first,front.second-1});
        }
        if (front.second+1<=20 && obstacles.count({front.first,front.second+1})==0&& !vis.count({front.first, front.second+1})){
            vis.insert({front.first,front.second+1});
            parent[{front.first, front.second+1}] = front;
            q.push({front.first,front.second+1});
        }
    }
    return {};
}

int main(){
    int high_score=0;

    srand(time(0));

    //timer
    float timeLeft=30.0f;

    //row and column for start position
    int Xr=rand()%GRID; 
    int Xc=rand()%GRID;

     //row and colum for collectible item
    int Collectible_r=rand()%GRID;
    int Collectible_c=rand()%GRID;
    bool newCollectible=false;

    //Obstacle set
    set<pair<int,int>> obstacles;
    for (int i=0;i<(GRID/2)*5;i++){
        obstacles.insert({rand()%GRID, rand()%GRID});
    }

    //score and steps
    int score=0;
    int minSteps=0;
    int stepsTaken=0;

    bool recalcPath = true;

    InitWindow(WIN_W, WIN_H+HUD, "Grid Game");
    SetTargetFPS(60);

    vector<pair<int,int>> MIN_PATH;
    bool Gameover=false;
    float wallMessageTimer = 0.0f; 
    float moveTimer = 0.0f;  
    const float MOVE_DELAY = 0.1f;

    while (!WindowShouldClose()){
        timeLeft-=GetFrameTime();
        moveTimer -= GetFrameTime();
        bool boundaryHit=false;
        BeginDrawing();
        ClearBackground(BLACK);
        if (timeLeft<=0){ //If time is over, make gameover=true
            Gameover=1;
            if (score>high_score)high_score=score;
        }
        
        //Check if path to collectible is zero
        if (recalcPath){
                MIN_PATH = findPath({Xr,Xc}, {Collectible_r,Collectible_c}, obstacles);
                while (MIN_PATH.empty()){
                Collectible_r = rand()%GRID;
                Collectible_c = rand()%GRID;
                MIN_PATH = findPath({Xr,Xc}, {Collectible_r,Collectible_c}, obstacles);
            }
            if (newCollectible) minSteps = MIN_PATH.size();
            newCollectible=false;
            recalcPath = false; // STOP recalculating
        }
        
        if (Gameover){ //GameOver Screen
            int centerY = WIN_H / 2;
            DrawText("GAME OVER",    (WIN_W - MeasureText("GAME OVER", 50)) / 2,    centerY - 80, 50, RED);

            const char* text = TextFormat("Final Score: %d", score);
            DrawText(text, (WIN_W - MeasureText(text, 30)) / 2, centerY - 10, 30, WHITE);

            text = TextFormat("Highest Score: %d", high_score);

            DrawText(text,  (WIN_W - MeasureText(text, 30)) / 2,  centerY + 30, 30, GREEN);

            text = "Press R to restart";
            DrawText(text,    (WIN_W - MeasureText(text, 20)) / 2,    centerY + 70, 20, GRAY);
            if (IsKeyPressed(KEY_R)){
                 recalcPath=true;
                score = 0;
                minSteps=0;
                stepsTaken=0;
                timeLeft = 30.0f;
                Gameover = false;
                Xr = rand()%GRID;
                Xc = rand()%GRID;
                Collectible_r = rand()%GRID;
                Collectible_c = rand()%GRID;
                newCollectible=false;
                obstacles.clear();
                for (int i=0;i<(GRID/2)*5;i++)obstacles.insert({rand()%GRID, rand()%GRID});
            }
        }

        else{
             auto tryMove = [&](int newR, int newC) {
                if (newR < 0 || newR >= GRID || newC < 0 || newC >= GRID) {
                    boundaryHit = true;
                } else if (obstacles.count({newR, newC})) {
                    boundaryHit = true;
                } else {
                    Xr = newR; Xc = newC;
                    stepsTaken++;
                    recalcPath = true;
                }
            };
        if (moveTimer<=0){
        if (IsKeyDown(KEY_W)){
            tryMove(Xr-1,Xc);
            moveTimer=MOVE_DELAY;
        }
        if (IsKeyDown(KEY_S)){
            tryMove(Xr+1,Xc);
            moveTimer=MOVE_DELAY;
        }
        if (IsKeyDown(KEY_A)){
            tryMove(Xr,Xc-1);
            moveTimer=MOVE_DELAY;
        }
        if (IsKeyDown(KEY_D)){
            tryMove(Xr,Xc+1);
            moveTimer=MOVE_DELAY;
        }}
        
        //Check if Red Block is over Green Block
        if (Xr==Collectible_r && Xc==Collectible_c){
            recalcPath=true;
            score += max(1, 10 - (stepsTaken - minSteps));
            stepsTaken=0;
            
            newCollectible=true;
            do {
                Collectible_r=rand()%GRID;
                Collectible_c=rand()%GRID;
            } while (obstacles.count({Collectible_r, Collectible_c}) || 
             findPath({Xr,Xc},{Collectible_r,Collectible_c},obstacles).empty());
        }

        DrawRectangle(0, 0, WIN_H, HUD, DARKGRAY);
        DrawLine(0, HUD, WIN_H, HUD, WHITE);

        // when boundary hit:
        if (boundaryHit) wallMessageTimer = 1.5f; // show for 1.5 seconds

        // every frame, count down and draw if still active:
        if (wallMessageTimer > 0){
            wallMessageTimer -= GetFrameTime();
            const char* text = "You hit a Wall!";
            int textWidth = MeasureText(text, 20);
            int x = (WIN_W - textWidth) / 2;
            DrawText(text, x, 15, 20, RED);
        }
        DrawText(TextFormat("Score: %d", score), 10, 15, 20, WHITE);
        const char* timerText = TextFormat("Time: %.1f", timeLeft);
DrawText(timerText, WIN_W - MeasureText(timerText, 20) - 10, 15, 20, WHITE);
        
        set<pair<int,int>> pathSet(MIN_PATH.begin(),MIN_PATH.end());

        //Draw Grid
        for (int i = 0; i < GRID; i++){
            for (int j = 0; j < GRID; j++){
                int x=j*TILE,y=i*TILE+HUD;
                if (i==Xr && j==Xc){ //Generate Start block
                    DrawRectangle(x, y, TILE, TILE, RED);
                }
                else if (obstacles.count({i,j})){ //Draw Obstacles
                    DrawRectangle(x, y, TILE, TILE, WHITE);
                }
                else if (i==Collectible_r && j==Collectible_c){ //Generate collectible block
                    DrawRectangle(x,y,TILE,TILE,GREEN);
                }
                else if (pathSet.count({i, j})){
                    DrawRectangle((float)x,(float)y,(float)TILE,(float)TILE,ColorAlpha(BLUE,0.4f));
                    DrawRectangleLinesEx({(float)x, (float)y, (float)TILE, (float)TILE}, 2.0f, BLUE);
                }
                else DrawRectangleLines(x, y, TILE, TILE, DARKGRAY);
            }
        }
    }
        EndDrawing();

}
    CloseWindow();
    return 0;
}