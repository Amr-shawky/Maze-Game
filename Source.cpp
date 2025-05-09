#include <gl/freeglut.h>
#include <cmath>
#include <iostream>
#include <string>
#include <ctime>

// Maze sizes for different levels
const int MAZE_SIZES[] = { 10, 15, 20, 25 }; // Level 0, 1, 2, 3
const int MAX_MAZE_SIZE = 25; // Largest size for array declaration
const int NUM_LEVELS = 4;

// Maze layouts (unchanged from original)
int mazes[NUM_LEVELS][MAX_MAZE_SIZE][MAX_MAZE_SIZE] = {
    // Level 0 (10x10, Easy)
    {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,1,1,0,0,0,1},
        {1,0,0,0,1,1,0,0,0,1},
        {1,1,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,1,1,1,1,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    },
    // Level 1 (15x15, Easy)
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    },
    // Level 2 (20x20, Medium)
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    },
    // Level 3 (25x25, Hard)
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,0,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    }
};

// Player properties
float playerX = 1.5f;
float playerZ = 1.5f;
float playerYaw = 0.0f;
float playerPitch = 0.0f;
const float PLAYER_SPEED = 0.1f;
const float ROTATION_SPEED = 0.05f;

// Player settings
int playerShape = 0; // 0: ball, 1: square, 2: triangle, 3: diamond, 4: stick, 5: human
float playerColor[3] = { 0.0f, 1.0f, 0.0f }; // Default green
float playerSize = 0.1f; // Default medium size (updated)

// Camera control
float cameraDistance = 0.0f; // Start with first-person view

// Moving obstacle properties
float obstacleX = 3.5f;
float obstacleZ = 3.5f;
float obstacleDirection = 1.0f;
const float OBSTACLE_SPEED = 0.05f;

// End points for each level
const float END_X[] = { 8.5f, 13.5f, 18.5f, 23.5f };
const float END_Z[] = { 8.5f, 13.5f, 18.5f, 23.5f };

// Coin properties
const int NUM_COINS = 5;
float coinX[NUM_LEVELS][NUM_COINS] = {
    {1.5, 3.5, 5.5, 7.5, 8.5},    // Level 0
    {1.5, 4.5, 7.5, 10.5, 13.5},  // Level 1
    {1.5, 5.5, 9.5, 13.5, 18.5},  // Level 2
    {1.5, 6.5, 11.5, 16.5, 23.5}  // Level 3
};
float coinZ[NUM_LEVELS][NUM_COINS] = {
    {2.5, 2.5, 4.5, 5.5, 1.5},    // Level 0
    {2.5, 4.5, 6.5, 8.5, 1.5},    // Level 1
    {2.5, 5.5, 7.5, 9.5, 1.5},    // Level 2
    {2.5, 6.5, 8.5, 10.5, 1.5}    // Level 3
};
bool coinCollected[NUM_COINS] = { false };
int score = 0;
float coinRotation = 0.0f;

// Key states
bool keys[256] = { false };

// Texture IDs (placeholders)
GLuint wallTexture = 0;
GLuint floorTexture = 0;

// Window dimensions
int windowWidth = 800;
int windowHeight = 600;

// Game states
enum GameState { START_SCREEN, LEVEL_SELECT, SETTINGS_SCREEN, COLOR_SETTINGS, SHAPE_SETTINGS, SIZE_SETTINGS, GAMEPLAY, WIN_SCREEN };
GameState gameState = START_SCREEN;
int currentLevel = 0;

// Button constants
const float BTN_WIDTH = 100;
const float BTN_HEIGHT = 50;
const float SPACING = 20;

// Color options
const float COLORS[6][3] = {
    {1.0, 0.0, 0.0}, // Red
    {0.0, 1.0, 0.0}, // Green
    {0.0, 0.0, 1.0}, // Blue
    {1.0, 1.0, 0.0}, // Yellow
    {0.0, 0.0, 0.0}, // Black
    {1.0, 1.0, 1.0}  // White
};

// Size options (updated to smaller sizes)
const float SIZES[3] = { 0.05, 0.1, 0.15 }; // Small, Medium, Large

// Function prototypes
void init();
void display();
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void mouseMotion(int x, int y);
void mouseClick(int button, int state, int x, int y);
void timer(int value);
void drawWall(float x, float z);
void drawFloor();
void drawObstacle();
void drawPlayer();
void drawEndPoint();
void drawCoin(float x, float z);
void drawMiniMap();
void drawStartScreen();
void drawLevelSelectScreen();
void drawSettingsScreen();
void drawColorSettings();
void drawShapeSettings();
void drawSizeSettings();
void drawWinScreen();
void drawHUD();
bool checkCollision(float x, float z);
void updatePlayer();
void initGame();
void drawText(float x, float y, const char* text);
void drawTextWithShadow(float x, float y, const char* text, float color[3]);
void drawShape(int shape);

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("3D Maze Game");

    srand(static_cast<unsigned int>(time(NULL))); // Seed random number generator
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouseClick);
    glutTimerFunc(16, timer, 0); // ~60 FPS

    glutMainLoop();
    return 0;
}

// Initialize OpenGL settings and modify mazes
void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    GLfloat lightPos0[] = { 5.0f, 5.0f, 5.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    GLfloat lightPos1[] = { 0.0f, 5.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    // Modify mazes to add random paths
    for (int level = 0; level < NUM_LEVELS; level++) {
        int size = MAZE_SIZES[level];
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                if (mazes[level][i][j] == 1 && rand() % 10 == 0) { // 10% chance to remove wall
                    mazes[level][i][j] = 0;
                }
            }
        }
    }
}

// Display function to handle rendering based on game state
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (gameState == START_SCREEN) {
        drawStartScreen();
    }
    else if (gameState == LEVEL_SELECT) {
        drawLevelSelectScreen();
    }
    else if (gameState == SETTINGS_SCREEN) {
        drawSettingsScreen();
    }
    else if (gameState == COLOR_SETTINGS) {
        drawColorSettings();
    }
    else if (gameState == SHAPE_SETTINGS) {
        drawShapeSettings();
    }
    else if (gameState == SIZE_SETTINGS) {
        drawSizeSettings();
    }
    else if (gameState == GAMEPLAY) {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        float camX, camY, camZ;
        if (cameraDistance > 0.0f) {
            // Third-person view
            camX = playerX - cameraDistance * sin(playerYaw);
            camY = 1.5f + cameraDistance * 0.5f; // Adjust height
            camZ = playerZ - cameraDistance * cos(playerYaw);
            gluLookAt(camX, camY, camZ, playerX, 1.5f, playerZ, 0.0f, 1.0f, 0.0f);
        }
        else {
            // First-person view
            camX = playerX;
            camY = 1.5f;
            camZ = playerZ;
            float lookX = camX + sin(playerYaw);
            float lookY = camY + tan(playerPitch);
            float lookZ = camZ + cos(playerYaw);
            gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0f, 1.0f, 0.0f);
        }

        int size = MAZE_SIZES[currentLevel];
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (mazes[currentLevel][i][j] == 1) {
                    drawWall(static_cast<float>(i), static_cast<float>(j));
                }
            }
        }

        drawFloor();
        drawObstacle();
        drawPlayer();
        drawEndPoint();

        for (int i = 0; i < NUM_COINS; i++) {
            if (!coinCollected[i]) {
                drawCoin(coinX[currentLevel][i], coinZ[currentLevel][i]);
            }
        }

        drawMiniMap();
        drawHUD();

        float dx = playerX - END_X[currentLevel];
        float dz = playerZ - END_Z[currentLevel];
        if (dx * dx + dz * dz < 0.5f * 0.5f) {
            gameState = WIN_SCREEN;
        }
    }
    else if (gameState == WIN_SCREEN) {
        drawWinScreen();
    }

    glutSwapBuffers();
}

// Reshape function to handle window resizing
void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)width / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input handling with case-insensitivity
void keyboard(unsigned char key, int x, int y) {
    if (key == '+') {
        cameraDistance += 0.5f; // Zoom out
    }
    else if (key == '-') {
        cameraDistance -= 0.5f; // Zoom in
        if (cameraDistance < 0.0f) cameraDistance = 0.0f;
    }
    else if (key == 'w' || key == 'W') {
        keys['w'] = true;
    }
    else if (key == 's' || key == 'S') {
        keys['s'] = true;
    }
    else if (key == 'a' || key == 'A') {
        keys['a'] = true;
    }
    else if (key == 'd' || key == 'D') {
        keys['d'] = true;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'W') {
        keys['w'] = false;
    }
    else if (key == 's' || key == 'S') {
        keys['s'] = false;
    }
    else if (key == 'a' || key == 'A') {
        keys['a'] = false;
    }
    else if (key == 'd' || key == 'D') {
        keys['d'] = false;
    }
}

// Mouse motion handling for camera control
void mouseMotion(int x, int y) {
    static int prevX = -1;
    static int prevY = -1;
    if (prevX == -1) {
        prevX = x;
        prevY = y;
    }
    int deltaX = x - prevX;
    int deltaY = y - prevY;
    prevX = x;
    prevY = y;

    playerYaw -= deltaX * ROTATION_SPEED;
    playerPitch -= deltaY * ROTATION_SPEED;

    if (playerPitch > 1.5f) playerPitch = 1.5f;
    if (playerPitch < -1.5f) playerPitch = -1.5f;
}

// Mouse click handling for menu interactions
void mouseClick(int button, int state, int x, int y) {
    int adjustedY = windowHeight - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (gameState == START_SCREEN) {
            float btnWidth = 200;
            float btnHeight = 50;
            float spacing = 20;
            float totalHeight = 2 * btnHeight + spacing;
            float startY = (windowHeight - totalHeight) / 2;
            float btnX = (windowWidth - btnWidth) / 2;
            float settingsBtnY = startY + btnHeight + spacing;
            if (x >= btnX && x <= btnX + btnWidth) {
                if (adjustedY >= startY && adjustedY <= startY + btnHeight) {
                    gameState = LEVEL_SELECT;
                }
                else if (adjustedY >= settingsBtnY && adjustedY <= settingsBtnY + btnHeight) {
                    gameState = SETTINGS_SCREEN;
                }
            }
        }
        else if (gameState == LEVEL_SELECT) {
            float btnWidth = 200;
            float btnHeight = 50;
            float spacing = 20;
            float totalHeight = 3 * btnHeight + 2 * spacing;
            float startY = (windowHeight - totalHeight) / 2;
            float btnX = (windowWidth - btnWidth) / 2;

            if (x >= btnX && x <= btnX + btnWidth) {
                if (adjustedY >= startY && adjustedY <= startY + btnHeight) {
                    currentLevel = 1; // Easy
                    initGame();
                    gameState = GAMEPLAY;
                }
                else if (adjustedY >= startY + btnHeight + spacing && adjustedY <= startY + 2 * btnHeight + spacing) {
                    currentLevel = 2; // Medium
                    initGame();
                    gameState = GAMEPLAY;
                }
                else if (adjustedY >= startY + 2 * (btnHeight + spacing) && adjustedY <= startY + 3 * btnHeight + 2 * spacing) {
                    currentLevel = 3; // Hard
                    initGame();
                    gameState = GAMEPLAY;
                }
            }
        }
        else if (gameState == SETTINGS_SCREEN) {
            float btnWidth = BTN_WIDTH;
            float btnHeight = BTN_HEIGHT;
            float spacing = SPACING;
            float startY = (windowHeight - (4 * btnHeight + 3 * spacing)) / 2;
            float btnX = (windowWidth - btnWidth) / 2;
            for (int i = 0; i < 4; i++) {
                float y = startY + i * (btnHeight + spacing);
                if (btnX <= x && x <= btnX + btnWidth && y <= adjustedY && adjustedY <= y + btnHeight) {
                    if (i == 0) gameState = COLOR_SETTINGS;
                    else if (i == 1) gameState = SHAPE_SETTINGS;
                    else if (i == 2) gameState = SIZE_SETTINGS;
                    else if (i == 3) gameState = START_SCREEN;
                    break;
                }
            }
        }
        else if (gameState == COLOR_SETTINGS) {
            float btnWidth = BTN_WIDTH;
            float btnHeight = BTN_HEIGHT;
            float spacing = SPACING;
            float gridWidth = 3 * btnWidth + 2 * spacing;
            float gridHeight = 2 * btnHeight + spacing;
            float startX = (windowWidth - gridWidth) / 2;
            float startY = (windowHeight - gridHeight) / 2;
            for (int row = 0; row < 2; row++) {
                for (int col = 0; col < 3; col++) {
                    int index = row * 3 + col;
                    float bx = startX + col * (btnWidth + spacing);
                    float by = startY + row * (btnHeight + spacing);
                    if (bx <= x && x <= bx + btnWidth && by <= adjustedY && adjustedY <= by + btnHeight) {
                        playerColor[0] = COLORS[index][0];
                        playerColor[1] = COLORS[index][1];
                        playerColor[2] = COLORS[index][2];
                        gameState = SETTINGS_SCREEN;
                        return;
                    }
                }
            }
            // Back button
            float backX = (windowWidth - btnWidth) / 2;
            float backY = startY - btnHeight - spacing;
            if (backX <= x && x <= backX + btnWidth && backY <= adjustedY && adjustedY <= backY + btnHeight) {
                gameState = SETTINGS_SCREEN;
            }
        }
        else if (gameState == SHAPE_SETTINGS) {
            float btnWidth = BTN_WIDTH;
            float btnHeight = BTN_HEIGHT;
            float spacing = SPACING;
            float gridWidth = 3 * btnWidth + 2 * spacing;
            float gridHeight = 2 * btnHeight + spacing;
            float startX = (windowWidth - gridWidth) / 2;
            float startY = (windowHeight - gridHeight) / 2;
            for (int row = 0; row < 2; row++) {
                for (int col = 0; col < 3; col++) {
                    int index = row * 3 + col;
                    float bx = startX + col * (btnWidth + spacing);
                    float by = startY + row * (btnHeight + spacing);
                    if (bx <= x && x <= bx + btnWidth && by <= adjustedY && adjustedY <= by + btnHeight) {
                        playerShape = index;
                        gameState = SETTINGS_SCREEN;
                        return;
                    }
                }
            }
            // Back button
            float backX = (windowWidth - btnWidth) / 2;
            float backY = startY - btnHeight - spacing;
            if (backX <= x && x <= backX + btnWidth && backY <= adjustedY && adjustedY <= backY + btnHeight) {
                gameState = SETTINGS_SCREEN;
            }
        }
        else if (gameState == SIZE_SETTINGS) {
            float btnWidth = BTN_WIDTH;
            float btnHeight = BTN_HEIGHT;
            float spacing = SPACING;
            float startX = (windowWidth - btnWidth) / 2;
            float startY = (windowHeight - (3 * btnHeight + 2 * spacing)) / 2;
            for (int i = 0; i < 3; i++) {
                float y = startY + i * (btnHeight + spacing);
                if (startX <= x && x <= startX + btnWidth && y <= adjustedY && adjustedY <= y + btnHeight) {
                    playerSize = SIZES[i];
                    gameState = SETTINGS_SCREEN;
                    return;
                }
            }
            // Back button
            float backY = startY + 3 * (btnHeight + spacing);
            if (startX <= x && x <= startX + btnWidth && backY <= adjustedY && adjustedY <= backY + btnHeight) {
                gameState = SETTINGS_SCREEN;
            }
        }
    }
}

// Timer function to handle game updates
void timer(int value) {
    if (gameState == GAMEPLAY) {
        updatePlayer();

        obstacleX += obstacleDirection * OBSTACLE_SPEED;
        if (obstacleX > 5.5f || obstacleX < 3.5f) {
            obstacleDirection *= -1;
        }

        float dx = playerX - obstacleX;
        float dz = playerZ - obstacleZ;
        if (dx * dx + dz * dz < 0.5f * 0.5f) {
            std::cout << "Collision with obstacle! Resetting position.\n";
            playerX = 1.5f;
            playerZ = 1.5f;
        }

        coinRotation += 1.0f;
        if (coinRotation > 360.0f) coinRotation -= 360.0f;

        for (int i = 0; i < NUM_COINS; i++) {
            if (!coinCollected[i]) {
                float dx = playerX - coinX[currentLevel][i];
                float dz = playerZ - coinZ[currentLevel][i];
                if (dx * dx + dz * dz < 0.3f * 0.3f) {
                    coinCollected[i] = true;
                    score += 10;
                }
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// Update player position based on input with corrected strafe directions
void updatePlayer() {
    float newX = playerX;
    float newZ = playerZ;

    if (keys['w']) {
        newX += PLAYER_SPEED * sin(playerYaw);
        newZ += PLAYER_SPEED * cos(playerYaw);
    }
    if (keys['s']) {
        newX -= PLAYER_SPEED * sin(playerYaw);
        newZ -= PLAYER_SPEED * cos(playerYaw);
    }
    if (keys['d']) {
        newX -= PLAYER_SPEED * cos(playerYaw); // Move left
        newZ += PLAYER_SPEED * sin(playerYaw);
    }
    if (keys['a']) {
        newX += PLAYER_SPEED * cos(playerYaw); // Move right
        newZ -= PLAYER_SPEED * sin(playerYaw);
    }

    if (!checkCollision(newX, newZ)) {
        playerX = newX;
        playerZ = newZ;
    }
}

// Draw wall at specified position
void drawWall(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 1.0f, z);
    glScalef(1.0f, 2.0f, 1.0f);
    glColor3f(0.7f, 0.7f, 0.7f);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

// Draw the floor of the maze
void drawFloor() {
    glPushMatrix();
    glTranslatef(MAZE_SIZES[currentLevel] / 2.0f, -0.05f, MAZE_SIZES[currentLevel] / 2.0f);
    glScalef(MAZE_SIZES[currentLevel], 0.1f, MAZE_SIZES[currentLevel]);
    glColor3f(0.2f, 0.2f, 0.2f);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();

    glPopMatrix();
}

// Draw the moving obstacle
void drawObstacle() {
    glPushMatrix();
    glTranslatef(obstacleX, 0.5f, obstacleZ);
    glScalef(0.5f, 0.5f, 0.5f);
    glColor3f(1.0f, 0.5f, 0.0f);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// Draw the player with selected shape, color, and size
void drawPlayer() {
    glPushMatrix();
    glTranslatef(playerX, 1.0f, playerZ);
    glScalef(playerSize, playerSize, playerSize);
    glColor3fv(playerColor);
    drawShape(playerShape);
    glPopMatrix();
}

// Draw the endpoint
void drawEndPoint() {
    glPushMatrix();
    glTranslatef(END_X[currentLevel], 1.0f, END_Z[currentLevel]);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidCube(0.5);
    glPopMatrix();
}

// Draw a coin at specified position
void drawCoin(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.5f, z);
    glRotatef(coinRotation, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidSphere(0.2, 10, 10);
    glPopMatrix();
}

// Draw the mini-map
void drawMiniMap() {
    glViewport(windowWidth - 100, windowHeight - 100, 100, 100);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, MAZE_SIZES[currentLevel], 0, MAZE_SIZES[currentLevel], -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.0f, 0.0f, 1.0f);
    int size = MAZE_SIZES[currentLevel];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (mazes[currentLevel][i][j] == 1) {
                glBegin(GL_QUADS);
                glVertex2f(i, j);
                glVertex2f(i + 1, j);
                glVertex2f(i + 1, j + 1);
                glVertex2f(i, j + 1);
                glEnd();
            }
        }
    }

    glColor3fv(playerColor);
    glBegin(GL_QUADS);
    glVertex2f(playerX - 0.1f, playerZ - 0.1f);
    glVertex2f(playerX + 0.1f, playerZ - 0.1f);
    glVertex2f(playerX + 0.1f, playerZ + 0.1f);
    glVertex2f(playerX - 0.1f, playerZ + 0.1f);
    glEnd();

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(obstacleX - 0.1f, obstacleZ - 0.1f);
    glVertex2f(obstacleX + 0.1f, obstacleZ - 0.1f);
    glVertex2f(obstacleX + 0.1f, obstacleZ + 0.1f);
    glVertex2f(obstacleX - 0.1f, obstacleZ + 0.1f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(END_X[currentLevel] - 0.1f, END_Z[currentLevel] - 0.1f);
    glVertex2f(END_X[currentLevel] + 0.1f, END_Z[currentLevel] - 0.1f);
    glVertex2f(END_X[currentLevel] + 0.1f, END_Z[currentLevel] + 0.1f);
    glVertex2f(END_X[currentLevel] - 0.1f, END_Z[currentLevel] + 0.1f);
    glEnd();

    for (int i = 0; i < NUM_COINS; i++) {
        if (!coinCollected[i]) {
            glColor3f(1.0f, 1.0f, 0.0f);
            glBegin(GL_QUADS);
            glVertex2f(coinX[currentLevel][i] - 0.05f, coinZ[currentLevel][i] - 0.05f);
            glVertex2f(coinX[currentLevel][i] + 0.05f, coinZ[currentLevel][i] - 0.05f);
            glVertex2f(coinX[currentLevel][i] + 0.05f, coinZ[currentLevel][i] + 0.05f);
            glVertex2f(coinX[currentLevel][i] - 0.05f, coinZ[currentLevel][i] + 0.05f);
            glEnd();
        }
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glViewport(0, 0, windowWidth, windowHeight);
}

// Draw the start screen
void drawStartScreen() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue at top
    glVertex2f(0, windowHeight);
    glVertex2f(windowWidth, windowHeight);
    glColor3f(0.5f, 0.0f, 0.5f); // Purple at bottom
    glVertex2f(windowWidth, 0);
    glVertex2f(0, 0);
    glEnd();

    float titleColor[3] = { 1.0f, 1.0f, 1.0f }; // White
    drawTextWithShadow(windowWidth / 2 - 100, windowHeight - 50, "3D Maze Game", titleColor);

    float btnWidth = 200;
    float btnHeight = 50;
    float spacing = 20;
    float totalHeight = 2 * btnHeight + spacing;
    float startY = (windowHeight - totalHeight) / 2;
    float btnX = (windowWidth - btnWidth) / 2;

    // Start button
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    glBegin(GL_QUADS);
    glVertex2f(btnX, startY);
    glVertex2f(btnX + btnWidth, startY);
    glVertex2f(btnX + btnWidth, startY + btnHeight);
    glVertex2f(btnX, startY + btnHeight);
    glEnd();
    float textColor[3] = { 1.0f, 1.0f, 1.0f }; // White
    drawTextWithShadow(btnX + 50, startY + 20, "Start", textColor);

    // Settings button
    float settingsBtnY = startY + btnHeight + spacing;
    glColor3f(0.0f, 0.0f, 1.0f); // Blue
    glBegin(GL_QUADS);
    glVertex2f(btnX, settingsBtnY);
    glVertex2f(btnX + btnWidth, settingsBtnY);
    glVertex2f(btnX + btnWidth, settingsBtnY + btnHeight);
    glVertex2f(btnX, settingsBtnY + btnHeight);
    glEnd();
    drawTextWithShadow(btnX + 50, settingsBtnY + 20, "Settings", textColor);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// Draw the level select screen
void drawLevelSelectScreen() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.678f, 0.847f, 0.902f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0, windowHeight);
    glEnd();

    float btnWidth = 200;
    float btnHeight = 50;
    float spacing = 20;
    float totalHeight = 3 * btnHeight + 2 * spacing;
    float startY = (windowHeight - totalHeight) / 2;
    float btnX = (windowWidth - btnWidth) / 2;

    for (int i = 0; i < 3; i++) {
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(btnX, startY + i * (btnHeight + spacing));
        glVertex2f(btnX + btnWidth, startY + i * (btnHeight + spacing));
        glVertex2f(btnX + btnWidth, startY + i * (btnHeight + spacing) + btnHeight);
        glVertex2f(btnX, startY + i * (btnHeight + spacing) + btnHeight);
        glEnd();

        glColor3f(0.0f, 0.0f, 0.0f);
        std::string levelText = "Level " + std::to_string(i + 1);
        drawText(btnX + 50, startY + i * (btnHeight + spacing) + 20, levelText.c_str());
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// Draw the main settings screen
void drawSettingsScreen() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.678f, 0.847f, 0.902f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0, windowHeight);
    glEnd();

    // Draw title
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(windowWidth / 2 - 50, windowHeight - 50, "Settings");

    // Draw category buttons
    const char* categories[] = { "Color", "Shape", "Size", "Back" };
    float btnWidth = BTN_WIDTH;
    float btnHeight = BTN_HEIGHT;
    float spacing = SPACING;
    float startY = (windowHeight - (4 * btnHeight + 3 * spacing)) / 2;
    float btnX = (windowWidth - btnWidth) / 2;

    for (int i = 0; i < 4; i++) {
        float y = startY + i * (btnHeight + spacing);
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(btnX, y);
        glVertex2f(btnX + btnWidth, y);
        glVertex2f(btnX + btnWidth, y + btnHeight);
        glVertex2f(btnX, y + btnHeight);
        glEnd();
        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(btnX + 10, y + 20, categories[i]);
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// Draw the color settings sub-menu
void drawColorSettings() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.678f, 0.847f, 0.902f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0, windowHeight);
    glEnd();

    // Draw title
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(windowWidth / 2 - 50, windowHeight - 50, "Select Color");

    // Draw color buttons in 2x3 grid
    const char* colorNames[] = { "Red", "Green", "Blue", "Yellow", "Black", "White" };
    float btnWidth = BTN_WIDTH;
    float btnHeight = BTN_HEIGHT;
    float spacing = SPACING;
    float gridWidth = 3 * btnWidth + 2 * spacing;
    float gridHeight = 2 * btnHeight + spacing;
    float startX = (windowWidth - gridWidth) / 2;
    float startY = (windowHeight - gridHeight) / 2;

    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++) {
            int index = row * 3 + col;
            float x = startX + col * (btnWidth + spacing);
            float y = startY + row * (btnHeight + spacing);
            glColor3f(0.5f, 0.5f, 0.5f);
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + btnWidth, y);
            glVertex2f(x + btnWidth, y + btnHeight);
            glVertex2f(x, y + btnHeight);
            glEnd();
            glColor3f(0.0f, 0.0f, 0.0f);
            drawText(x + 10, y + 20, colorNames[index]);
        }
    }

    // Draw back button
    float backX = (windowWidth - btnWidth) / 2;
    float backY = startY - btnHeight - spacing;
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(backX, backY);
    glVertex2f(backX + btnWidth, backY);
    glVertex2f(backX + btnWidth, backY + btnHeight);
    glVertex2f(backX, backY + btnHeight);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(backX + 10, backY + 20, "Back");

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// Draw the shape settings sub-menu
void drawShapeSettings() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.678f, 0.847f, 0.902f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0, windowHeight);
    glEnd();

    // Draw title
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(windowWidth / 2 - 50, windowHeight - 50, "Select Shape");

    // Draw shape buttons in 2x3 grid
    const char* shapeNames[] = { "Ball", "Square", "Triangle", "Diamond", "Stick", "Human" };
    float btnWidth = BTN_WIDTH;
    float btnHeight = BTN_HEIGHT;
    float spacing = SPACING;
    float gridWidth = 3 * btnWidth + 2 * spacing;
    float gridHeight = 2 * btnHeight + spacing;
    float startX = (windowWidth - gridWidth) / 2;
    float startY = (windowHeight - gridHeight) / 2;

    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++) {
            int index = row * 3 + col;
            float x = startX + col * (btnWidth + spacing);
            float y = startY + row * (btnHeight + spacing);
            glColor3f(0.5f, 0.5f, 0.5f);
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + btnWidth, y);
            glVertex2f(x + btnWidth, y + btnHeight);
            glVertex2f(x, y + btnHeight);
            glEnd();
            glColor3f(0.0f, 0.0f, 0.0f);
            drawText(x + 10, y + 20, shapeNames[index]);
        }
    }

    // Draw back button
    float backX = (windowWidth - btnWidth) / 2;
    float backY = startY - btnHeight - spacing;
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(backX, backY);
    glVertex2f(backX + btnWidth, backY);
    glVertex2f(backX + btnWidth, backY + btnHeight);
    glVertex2f(backX, backY + btnHeight);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(backX + 10, backY + 20, "Back");

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// Draw the size settings sub-menu
void drawSizeSettings() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.678f, 0.847f, 0.902f);
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(windowWidth, 0);
    glVertex2f(windowWidth, windowHeight);
    glVertex2f(0, windowHeight);
    glEnd();

    // Draw title
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(windowWidth / 2 - 50, windowHeight - 50, "Select Size");

    // Draw size buttons in a column
    const char* sizeNames[] = { "Small", "Medium", "Large" };
    float btnWidth = BTN_WIDTH;
    float btnHeight = BTN_HEIGHT;
    float spacing = SPACING;
    float startX = (windowWidth - btnWidth) / 2;
    float startY = (windowHeight - (3 * btnHeight + 2 * spacing)) / 2;

    for (int i = 0; i < 3; i++) {
        float y = startY + i * (btnHeight + spacing);
        glColor3f(0.5f, 0.5f, 0.5f);
        glBegin(GL_QUADS);
        glVertex2f(startX, y);
        glVertex2f(startX + btnWidth, y);
        glVertex2f(startX + btnWidth, y + btnHeight);
        glVertex2f(startX, y + btnHeight);
        glEnd();
        glColor3f(0.0f, 0.0f, 0.0f);
        drawText(startX + 10, y + 20, sizeNames[i]);
    }

    // Draw back button
    float backY = startY + 3 * (btnHeight + spacing);
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex2f(startX, backY);
    glVertex2f(startX + btnWidth, backY);
    glVertex2f(startX + btnWidth, backY + btnHeight);
    glVertex2f(startX, backY + btnHeight);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    drawText(startX + 10, backY + 20, "Back");

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// Draw the win screen
void drawWinScreen() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 0.0f);
    drawText(windowWidth / 2 - 50, windowHeight / 2, "You Win!");
    std::string scoreText = "Score: " + std::to_string(score);
    drawText(windowWidth / 2 - 50, windowHeight / 2 - 30, scoreText.c_str());

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// Draw HUD elements
void drawHUD() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    std::string scoreText = "Score: " + std::to_string(score);
    drawText(10, windowHeight - 20, scoreText.c_str());
    drawText(10, windowHeight - 40, "Zoom: [-] In    [+] Out");

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// Check for collision at position (x, z), updated to account for player size
bool checkCollision(float x, float z) {
    int size = MAZE_SIZES[currentLevel];
    float r = 0.5f * playerSize;

    int minX = static_cast<int>(floor(x - r));
    int maxX = static_cast<int>(ceil(x + r));
    int minZ = static_cast<int>(floor(z - r));
    int maxZ = static_cast<int>(ceil(z + r));

    for (int i = minX; i <= maxX; ++i) {
        for (int j = minZ; j <= maxZ; ++j) {
            if (i >= 0 && i < size && j >= 0 && j < size && mazes[currentLevel][i][j] == 1) {
                // Wall bounding box
                float wallLeft = i - 0.5f;
                float wallRight = i + 0.5f;
                float wallBottom = j - 0.5f;
                float wallTop = j + 0.5f;

                // Player bounding box
                float playerLeft = x - r;
                float playerRight = x + r;
                float playerBottom = z - r;
                float playerTop = z + r;

                // Check for overlap
                if (playerRight > wallLeft &&
                    playerLeft < wallRight &&
                    playerTop > wallBottom &&
                    playerBottom < wallTop) {
                    return true; // Collision detected
                }
            }
        }
    }
    return false; // No collision
}
// Initialize game state
void initGame() {
    playerX = 1.45f;  // Slightly offset from wall boundary
    playerZ = 1.45f;
    obstacleX = 3.5f;
    obstacleZ = 3.5f;
    obstacleDirection = 1.0f;
    for (int i = 0; i < NUM_COINS; i++) {
        coinCollected[i] = false;
    }
    score = 0;
}
// Draw text at position (x, y)
void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// Draw text with shadow
void drawTextWithShadow(float x, float y, const char* text, float color[3]) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x + 1, y - 1);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    glColor3f(color[0], color[1], color[2]);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// Draw the selected shape for the player
void drawShape(int shape) {
    switch (shape) {
    case 0: // Ball
        glutSolidSphere(0.5, 20, 20);
        break;
    case 1: // Square
        glutSolidCube(1.0);
        break;
    case 2: // Triangle (Cone)
        glutSolidCone(0.5, 1.0, 20, 20);
        break;
    case 3: // Diamond (Two cones)
        glPushMatrix();
        glutSolidCone(0.5, 1.0, 20, 20);
        glRotatef(180, 1, 0, 0);
        glutSolidCone(0.5, 1.0, 20, 20);
        glPopMatrix();
        break;
    case 4: // Stick (Thin cube)
        glPushMatrix();
        glScalef(0.1, 1.0, 0.1);
        glutSolidCube(1.0);
        glPopMatrix();
        break;
    case 5: // Human (Simple stick figure)
        // Body
        glPushMatrix();
        glScalef(0.2, 1.0, 0.2);
        glutSolidCube(1.0);
        glPopMatrix();
        // Head
        glPushMatrix();
        glTranslatef(0, 1.0, 0);
        glutSolidSphere(0.3, 20, 20);
        glPopMatrix();
        // Arms
        glPushMatrix();
        glTranslatef(-0.5, 0.5, 0);
        glScalef(1.0, 0.2, 0.2);
        glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.5, 0.5, 0);
        glScalef(1.0, 0.2, 0.2);
        glutSolidCube(1.0);
        glPopMatrix();
        // Legs
        glPushMatrix();
        glTranslatef(-0.2, -0.5, 0);
        glScalef(0.2, 1.0, 0.2);
        glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.2, -0.5, 0);
        glScalef(0.2, 1.0, 0.2);
        glutSolidCube(1.0);
        glPopMatrix();
        break;
    }
}