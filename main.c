#include "raylib.h"
#include <stdio.h>


typedef struct{
    Vector2 position;
    Vector2 velocity;
    float speed;
    Texture2D texture;
}PlayerChar;

typedef struct{
    Vector2 position;
    Vector2 velocity;
    Color color;
    Vector2 size;
}EnemyChar;


EnemyChar CreateEnemy(int screenWidth, int screenHeight){
    EnemyChar enemyCr;
    enemyCr.position = (Vector2){GetRandomValue(0, screenWidth -30), GetRandomValue(30, screenHeight - 30)};
    
    enemyCr.velocity = (Vector2){GetRandomValue(1, 5), GetRandomValue(5, 12)};
    
    enemyCr.size = (Vector2){25, 25};
    
    enemyCr.color = (Color){230, 41, 55, 255};
    
    return enemyCr;
}




int main(void){
    //LOAD ASSESTS ::START::
  
        
    //LOAD ASSESTS ::END::
    
    //CREATE VARIABLES ::START::
 
    
    int windowX = 800;
    int windowY = 450;
    InitWindow(windowX, windowY, "BALLS");
   
    
    char currentScoreString[12] = "00";
    int currentScoreInt = 0;
    float posX;
    float posY;
    float rectSize = 20;
    int enemyCount = 5;
    float scorecounter = 0;
    int healthCount = 100;
    int damagenormal = 5;
    
  
    
    Vector2 enemyVelocity = {8, 3};
    Vector2 enePos = {0, 0};
    
    
    
    
    
    
   
    //CREATE VARIABLES ::END::
    
    
    EnemyChar enemyChars[enemyCount];
    
    
    for(int i = 0; i < enemyCount; i ++){
        enemyChars[i] = CreateEnemy(windowX, windowY);
        
    }
    
    posX = windowX/2;
    posY = windowY/2;
    
    Texture2D playerTexture = LoadTexture("assets/sprites/mainCharSprites/player.png");
    
    PlayerChar player;
    
    player.position = (Vector2){posX, posY};
    player.velocity = (Vector2){0,0};
    player.speed = 10;
    player.texture = playerTexture;
    //mainSprite = LoadTexture("assest/sprites/mainCharSprites/mainChar.png")
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        
       
        
        player.velocity.x = 0;
        player.velocity.y = 0;
        
        
        
        snprintf(currentScoreString, sizeof(currentScoreString), "%d", currentScoreInt);
        
       
        
        
        scorecounter += 1;
        if(scorecounter == 60){
            currentScoreInt += 1;
            scorecounter = 0;
        }
        
        //PLAYER CODE ::START::
        
        if (IsKeyDown(KEY_RIGHT)) {
            player.velocity.x = player.speed;
            }
           
        if (IsKeyDown(KEY_LEFT)) player.velocity.x = -player.speed;
        
        if (IsKeyDown(KEY_DOWN))player.velocity.y = player.speed;
        
        if (IsKeyDown(KEY_UP)) player.velocity.y = -player.speed;
        
        player.position.x += player.velocity.x;
        player.position.y += player.velocity.y;
        
        
        if(player.position.x < 0) player.position.x = 0;
        if(player.position.x > windowX - player.texture.width) player.position.x = windowX - player.texture.width; 
        if(player.position.y < 0) player.position.y = 0;
        
        if(player.position.y > windowY - player.texture.height) player.position.y = windowY - player.texture.height;
        
        //PLAYER CODE ::END::
      
        //ENEMY CODE ::START::
        if(enePos.x > windowX-rectSize || enePos.x < 0 ){
            enemyVelocity.y *= -1;
            
            
        }
        if(enePos.y > windowY - rectSize || enePos.y  < 0){
            enemyVelocity.y *= -1;
            enemyVelocity.x *= -1;
            
            
        }
        enePos.x += enemyVelocity.x;
        enePos.y += enemyVelocity.y;
        
        
       
        
        
        
        
    
        
         for (int i = 0;  i < enemyCount; i++) {
            enemyChars[i].position.x += enemyChars[i].velocity.x;
            enemyChars[i].position.y += enemyChars[i].velocity.y;
            
            
            if(enemyChars[i].position.x <= enemyChars[i].size.x || enemyChars[i].position.x >= windowX - enemyChars[i].size.x){
            enemyChars[i].velocity.x *= -1;
            }
                
            if(enemyChars[i].position.y <= enemyChars[i].size.y || enemyChars[i].position.y >=  windowY - enemyChars[i].size.y){
                enemyChars[i].velocity.y *= -1;
                
            }
            
        }
       
        //ENEMY CODE ::END::
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            
            
            
            
            DrawText("Score:", 5, 0, 20, DARKGRAY);
            DrawText(currentScoreString,75, 0, 20, DARKGRAY);
            DrawText("Health:", 5, 25, 20, DARKGRAY);
            DrawText("100", 75, 25, 20, DARKGRAY);
            
            DrawTextureV(player.texture, player.position, WHITE);
            
            
            
                
            for(int i = 0; i < enemyCount; i++){
                
                DrawRectangleV(enemyChars[i].position, enemyChars[i].size, enemyChars[i].color);
                
            }
            
          
        EndDrawing();
           
    }
    
    CloseWindow();        

    return 0;
    
    
}