#include "raylib.h"
#include <stdio.h>
#define STBTN 2

typedef struct{
    Vector2 position;
    Vector2 velocity;
    Rectangle rect;
    float speed;
    Texture2D texture;
    
}PlayerChar;

typedef struct{
    Vector2 position;
    Vector2 velocity;
    Color color;
    Vector2 size;
    Texture2D texture;
    Rectangle rect;
    bool isHit;
}EnemyChar;


typedef enum GameScreen{ Logo = 0,  HomeScreen, GamePlay, Ending} GameScreen;


EnemyChar CreateEnemy(int screenWidth, int screenHeight, Texture2D enemyTexture){
    EnemyChar enemyCr;
    enemyCr.position = (Vector2){GetRandomValue(0, screenWidth - enemyCr.texture.width), GetRandomValue(enemyCr.texture.height, screenHeight - enemyCr.texture.height)};
    
    enemyCr.velocity = (Vector2){GetRandomValue(1, 5), GetRandomValue(5, 12)};
    
    enemyCr.size = (Vector2){20, 20};
    enemyCr.texture = enemyTexture; 
    enemyCr.isHit = false;
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
    int enemyCount = 4;
    float scorecounter = 0;
    int healthCount = 100;
    char healthCountStr[4] = "100";
    int damagenormal = 5;
    bool btnAction;
    int btnState;
    Texture2D button = LoadTexture("assets/sprites/ui/startbtn.png");
    
    float framewidth = button.width/STBTN;
    Rectangle sourceRec = {0,0, framewidth, button.height};
    
    Rectangle btnBounds = {windowX/2.0f - button.width/STBTN/2, windowY/2.0f, button.width, framewidth};
    
    
   int startbtnState = 0;
   bool startbtnAction = false;
   
   Vector2 mousePoint = {0, 0};
    
    GameScreen currentScreen = Logo;
    int frameCounter = 0;
    
    
   
    //CREATE VARIABLES ::END::
    
    Texture2D playerTexture = LoadTexture("assets/sprites/mainCharSprites/player.png");
    Texture2D enemyTexture = LoadTexture("assets/sprites/enemySprites/fire.png");
    EnemyChar enemyChars[enemyCount];
    
    
    for(int i = 0; i < enemyCount; i ++){
        enemyChars[i] = CreateEnemy(windowX, windowY, enemyTexture);
        
    }
    
    
    
    //COLLISION CHECK 
  
    posX = windowX/2;
    posY = windowY/2;
    
    
    
    PlayerChar player;
    
    player.position = (Vector2){posX, posY};
    player.velocity = (Vector2){0,0};
    player.speed = 10;
    player.texture = playerTexture;
    
    
    
    //mainSprite = LoadTexture("assest/sprites/mainCharSprites/mainChar.png")
    
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        
        
        
        switch (currentScreen){
            case Logo:{
                frameCounter++;
                if (frameCounter > 300){
                    currentScreen = HomeScreen;
                }
            }break;
            case HomeScreen:{
                mousePoint = GetMousePosition();
                btnAction = false;

                if (CheckCollisionPointRec(mousePoint, btnBounds))
                {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
                    {
                        btnState = 2;
                    }
                    else
                    { 
                    btnState = 1;
                    }

                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                    { 
                    btnAction = true;
                    }
                }
                else 
                {
                    btnState = 0;
                }

                if (btnAction)
                {
                   currentScreen = GamePlay;
                }
                
                sourceRec.x = btnState*framewidth;
              
            }break;
            
            
           case GamePlay:{
            if(IsKeyPressed(KEY_END)){
                currentScreen = HomeScreen;
            } 
            }break;
        }
            
  
       
        
        player.velocity.x = 0;
        player.velocity.y = 0;
        
        
        
        snprintf(currentScoreString, sizeof(currentScoreString), "%d", currentScoreInt);
        
       
        
        
        scorecounter += 1;
        if(scorecounter == 60){
            currentScoreInt += 1;
            scorecounter = 0;
        }
        if(currentScoreInt == 60)
        {
            currentScreen = HomeScreen;
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
        
        player.rect = (Rectangle){player.position.x, player.position.y,player.texture.width, player.texture.height};
        
        if(player.position.x < 0) player.position.x = 0;
        if(player.position.x > windowX - player.texture.width) player.position.x = windowX - player.texture.width; 
        if(player.position.y < 0) player.position.y = 0;
        
        if(player.position.y > windowY - player.texture.height) player.position.y = windowY - player.texture.height;
        
        //PLAYER CODE ::END::
      
        //ENEMY CODE ::START::
    
        
        
        
    
        
         for (int i = 0;  i < enemyCount; i++) {
            enemyChars[i].position.x += enemyChars[i].velocity.x;
            enemyChars[i].position.y += enemyChars[i].velocity.y;
            
            
            
            if(enemyChars[i].position.x < 0 || enemyChars[i].position.x > windowX - enemyChars[i].texture.width){
            enemyChars[i].velocity.x *= -1;
            }
                
            if(enemyChars[i].position.y < enemyChars[i].size.y || enemyChars[i].position.y >  windowY - enemyChars[i].texture.height){
                enemyChars[i].velocity.y *= -1;
                
            }
            
            enemyChars[i].rect = (Rectangle){enemyChars[i].position.x, enemyChars[i].position.y, enemyChars[i].texture.width, enemyChars[i].texture.height};
            
        }
       
        //ENEMY CODE ::END::
        
        //CHECK FOR COLLISION PLAYER ENEMY COLLISION
        bool playerCollided;
        
        Rectangle playerRect = { player.position.x, player.position.y, player.texture.width, player.texture.height};
        playerCollided = false;
        snprintf(healthCountStr, sizeof(healthCountStr), "%d", healthCount);
        
        for (int i = 0; i < enemyCount; i++) {
            if (CheckCollisionRecs(playerRect, enemyChars[i].rect)) {
                
                if(!enemyChars[i].isHit){
                    enemyChars[i].isHit = true;
                    healthCount -= damagenormal;
                    playerCollided = true;
                }
                
                break; 
            }else{
                enemyChars[i].isHit = false;
            }
        }
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            
            switch(currentScreen)
            {
                case Logo:
                {
                    DrawText("BALLS THE GAME", 220, 100, 40, BLACK);
                }break;
                case HomeScreen:
                {
                    DrawText("Balls The Game", 250, 100, 40, DARKGREEN);
                    DrawTextureRec(button, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE);
                    DrawText("Top Score", 250, 300, 40, DARKGREEN);
                    DrawText("Settings", 250, 350, 40, DARKGREEN);
                    
                    
                }break;
                case GamePlay:
                {
                     DrawText("Score:", 5, 0, 20, DARKGRAY);
                    DrawText(currentScoreString,75, 0, 20, DARKGRAY);
                    
                    
                    if(playerCollided){
                        DrawTextureV(player.texture, player.position, RED);
                        
                        
                    }
                    else{
                        DrawTextureV(player.texture, player.position, WHITE);
                    }
                    snprintf(healthCountStr, sizeof(healthCountStr), "%d", healthCount);
                    
                    DrawText("Health:", 5, 20, 20, DARKGRAY);
                    DrawText(healthCountStr, 75, 20, 20, DARKGRAY);
                    
                    
                        
                    for(int i = 0; i < enemyCount; i++){
                       
                        
                        DrawTextureV(enemyChars[i].texture,enemyChars[i].position, WHITE);
                        
                    }
            
                }break;
                default: break;
            }
            
            
            
            
           
          
        EndDrawing();
           
    }
    
    CloseWindow();        

    return 0;
    
    
}