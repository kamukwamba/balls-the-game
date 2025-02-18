#include "raylib.h"





int main(){
    
    const int screenWidth =  800;
    const int screenHieght = 450;
    
    
    InitWindow(screenWidth, screenHieght, "Balls");
    
    SetTargetFPS(60);
    
    while(!WindowShouldClose()){
        
        
       BeginDrawing();
       ClearBackground(GREEN);
       
       DrawCircle(screenWidth/2, screenHieght/2, 20, RED);
        
        
        
       EndDrawing();
        
    }
    
    CloseWindow();
    return 0;
}