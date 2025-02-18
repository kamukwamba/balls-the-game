#include "raylib.h"

#define MAX_ENEMIES 10

typedef struct {
    Rectangle rect;  // Bounding box for collision
    Vector2 position; // Position for drawing texture
    Texture2D texture; // Texture for the enemy
} Enemy;

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Player vs Enemies Collision with Textures");

    // Load textures
    
    
    Texture2D playerTexture = LoadTexture("assets/sprites/mainCharSprites/player.png");
    Texture2D enemyTexture = LoadTexture("assets/sprites/enemySprites/fire.png");  // Replace with your enemy texture path

    // Player
    Vector2 playerPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
    Rectangle playerRect = { playerPosition.x, playerPosition.y, playerTexture.width, playerTexture.height };
    bool playerCollided = false;

    // Array of enemies
    Enemy enemies[MAX_ENEMIES];
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].position = (Vector2){ GetRandomValue(0, screenWidth - enemyTexture.width), GetRandomValue(0, screenHeight - enemyTexture.height) };
        enemies[i].rect = (Rectangle){ enemies[i].position.x, enemies[i].position.y, enemyTexture.width, enemyTexture.height };
        enemies[i].texture = enemyTexture;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Player movement
        if (IsKeyDown(KEY_RIGHT)) playerPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) playerPosition.x -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) playerPosition.y += 2.0f;
        if (IsKeyDown(KEY_UP)) playerPosition.y -= 2.0f;

        // Update player bounding box
        playerRect.x = playerPosition.x;
        playerRect.y = playerPosition.y;

        // Check for collisions between player and enemies
        playerCollided = false;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (CheckCollisionRecs(playerRect, enemies[i].rect)) {
                playerCollided = true;
                break; // Exit the loop early if a collision is detected
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw player
        DrawTextureV(playerTexture, playerPosition, WHITE);

        // Draw enemies
        for (int i = 0; i < MAX_ENEMIES; i++) {
            DrawTextureV(enemies[i].texture, enemies[i].position, WHITE);
        }

        // Display collision message
        if (playerCollided) {
            DrawText("Collision Detected!", 10, 10, 20, RED);
        }

        EndDrawing();
    }

    // Unload textures
    UnloadTexture(playerTexture);
    UnloadTexture(enemyTexture);

    CloseWindow();
    return 0;
}