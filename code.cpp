#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <random>
#include <chrono>
#include <string>

using namespace std;

// Game constants
const int WIDTH = 12;
const int HEIGHT = 20;
const int STARTING_SPEED = 450; // ms
const int INCREASE_SPEED = 20; // ms
const int LINESPERLEVEL = 10; 
const int THSCORE = 1000;  // SCORE threshold for speed increase

// KEY CODES 
const int ESC = 27;
const int LEFT = 75;
const int RIGHT = 77;
const int UP = 72;
const int DOWN = 80;
const int SPACE = 32;

// CODES FOR COLOURS
enum COLOURS {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};
//colors mapping
const COLOURS BLOCKS_COLOURS[] = {
    BLUE,         // I - blue
    YELLOW,       // O - yellow
    LIGHTMAGENTA, // T - purple
    RED,          // S - red
    GREEN,        // Z - green
    LIGHTRED,     // J - pink (using LIGHTRED as pink)
    BROWN         // L - orange (using BROWN as orange)
};

// tetrisblocks SHAPEs
const vector<vector<vector<int>>> BLOCKS = {
    {
        {1, 1},  // O
        {1, 1}
    },
   {
        {0, 0, 0, 0},// I
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
   
   {
        {0, 0, 1},
        {1, 1, 1}, // L
        {0, 0, 0}
    }, 
    {
        {0, 1, 0},
        {1, 1, 1}, // T
        {0, 0, 0}
    },
    {
        {0, 1, 1},
        {1, 1, 0}, // S
        {0, 0, 0}
    },
     {
        {1, 0, 0},
        {1, 1, 1},// J
        {0, 0, 0}
    },
    {
        {1, 1, 0},
        {0, 1, 1},// Z
        {0, 0, 0}
    }
};

// FUNCTIONS FOR HANDLING
void SET_COLOR(COLOURS txtcolor, COLOURS backgroundcolor = BLACK) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (txtcolor) | (backgroundcolor << 4));
}
void RESETCOLOR() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE | (BLACK << 4));
}
void CURSORPOSITION(int x, int y) {
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
// tetrisblocks class
class tetrisblocks {
private:
  int ROTATION; 
     int TYPE;
   char SYMBOL; 
    int x, y;
    COLOURS color;

public:
    tetrisblocks(int TYPE) : TYPE(TYPE), ROTATION(0), x(WIDTH / 2 - 2), y(0) {
        SYMBOL = '#';  // Using the same SYMBOL for all BLOCKS
        color = BLOCKS_COLOURS[TYPE];  // Set color based on tetrisblocks TYPE
    }
    vector<vector<int>> GET_SHAPE() const {
        vector<vector<int>> SHAPE = BLOCKS[TYPE];
        // Apply ROTATION
        for (int r = 0; r < ROTATION; r++) {
            SHAPE = MATRIX_ROTATE(SHAPE);
        }
        return SHAPE;
    }
    vector<vector<int>> MATRIX_ROTATE(const vector<vector<int>>& MATRIX) const {
        int n = MATRIX.size();
        vector<vector<int>> ROTATED_MATRIX(n, vector<int>(n, 0));  
        // ROTATE 90 degrees clockwise
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ROTATED_MATRIX[j][n - 1 - i] = MATRIX[i][j];
            }
        }
        return ROTATED_MATRIX;
    }
     void DOWN() {
        y++;
    }
    void RIGHT() {
        x++;
    }
    void LEFT() {
        x--;
    }
    void ROTATE() {
        ROTATION = (ROTATION + 1) % 4;
    }
    int GET_X() const { return x; }
    int GET_Y() const { return y; }
    char GET_SYMBOL() const { return SYMBOL; }
    COLOURS GET_COLOR() const { return color; }
    int GET_TYPE() const { return TYPE; }  
    void SET_X(int newX) { x = newX; }
    void SET_Y(int newY) { y = newY; }
    void SET_ROTATION(int newROTATION) { ROTATION = newROTATION; }
};
class TETRIS_GAME {
private:
    vector<vector<int>> GRID;
    vector<vector<int>> COLOR_GRID;  // Store color information
    tetrisblocks* CURRENT_PEICE;
    tetrisblocks* NEXT_PEICE;
    int LINES_GOT_CLEARED;
    bool PAUSED; // Track if the game is PAUSED
    int FALL_SPEED;
    int LEVEL;
    bool GAME_OVER;
    int SCORE;
    std::chrono::time_point<std::chrono::system_clock> LASTFALL;
    std::mt19937 rng;
public:
    TETRIS_GAME() : 
        GRID(HEIGHT, vector<int>(WIDTH, 0)),
        COLOR_GRID(HEIGHT, vector<int>(WIDTH, 0)),
        GAME_OVER(false),
        PAUSED(false), // Initialize PAUSED to false
        SCORE(0),
        LEVEL(1),
        LINES_GOT_CLEARED(0),
        FALL_SPEED(STARTING_SPEED) {
        // Initialize random number generator
        random_device rd;
        rng = mt19937(rd());
        // Create first PEICE
        CURRENT_PEICE = new tetrisblocks(GENERATE_RANDOME_PEICE());
        NEXT_PEICE = new tetrisblocks(GENERATE_RANDOME_PEICE());
        
        // Record start time
        LASTFALL = chrono::system_clock::now();
    }
void reset() {
        GRID.assign(HEIGHT, vector<int>(WIDTH, 0));
        COLOR_GRID.assign(HEIGHT, vector<int>(WIDTH, 0));
        delete CURRENT_PEICE;
        delete NEXT_PEICE;
        CURRENT_PEICE = new tetrisblocks(GENERATE_RANDOME_PEICE());
        NEXT_PEICE = new tetrisblocks(GENERATE_RANDOME_PEICE());
        GAME_OVER = false;
        PAUSED = false;
        SCORE = 0;
        LEVEL = 1;
        LINES_GOT_CLEARED = 0;
        FALL_SPEED = STARTING_SPEED;
        LASTFALL = chrono::system_clock::now();
    }
     int GENERATE_RANDOME_PEICE() {
        std::uniform_int_distribution<int> dist(0, BLOCKS.size() - 1);
        return dist(rng);
    }
    ~TETRIS_GAME() {
        delete CURRENT_PEICE;
        delete NEXT_PEICE;
    }
 void PLACE_PEICE() {
        vector<vector<int>> SHAPE = CURRENT_PEICE->GET_SHAPE();
        int PEICE_HEIGHT = SHAPE.size();
        int PEICE_WIDTH = SHAPE[0].size();
        int PEICETYPE = CURRENT_PEICE->GET_TYPE();
        
        for (int i = 0; i < PEICE_HEIGHT; i++) {
            for (int j = 0; j < PEICE_WIDTH; j++) {
                if (SHAPE[i][j] == 0) continue;
                
                int GRID_X = CURRENT_PEICE->GET_X() + j;
                int GRID_Y = CURRENT_PEICE->GET_Y() + i;
                
                if (GRID_Y < 0) {
                    GAME_OVER = true;
                    return;
                }
                
                GRID[GRID_Y][GRID_X] = 1;
                COLOR_GRID[GRID_Y][GRID_X] = PEICETYPE;  // Store the tetrisblocks TYPE for color reference
            }
        }
        // CHECK FOR THE LINES
        CLEAR_LINES();
        // CHECK IF THE GRID IS FULL OR NOT
        if (GRID[0][0] == 1 || GRID[0][1] == 1 || GRID[0][2] == 1 || GRID[0][3] == 1 || 
            GRID[0][4] == 1 || GRID[0][5] == 1 || GRID[0][6] == 1 || GRID[0][7] == 1 || 
            GRID[0][8] == 1 || GRID[0][9] == 1) {
            GAME_OVER = true;
        }      
        // CREATE A NEW PEICE
        delete CURRENT_PEICE;
        CURRENT_PEICE = NEXT_PEICE;
        NEXT_PEICE = new tetrisblocks(GENERATE_RANDOME_PEICE());
    }
    bool isCollision(const tetrisblocks& PEICE) const {
        vector<vector<int>> SHAPE = PEICE.GET_SHAPE();
        int PEICE_HEIGHT = SHAPE.size();
        int PEICE_WIDTH = SHAPE[0].size();
        
        for (int i = 0; i < PEICE_HEIGHT; i++) {
            for (int j = 0; j < PEICE_WIDTH; j++) {
                if (SHAPE[i][j] == 0) continue;
                
                int GRID_X = PEICE.GET_X() + j;
                int GRID_Y = PEICE.GET_Y() + i;
                
                // Check if out of bounds
                if (GRID_X < 0 || GRID_X >= WIDTH || GRID_Y >= HEIGHT) {
                    return true;
                }
                
                // Check if overlaps with placed blocks
                if (GRID_Y >= 0 && GRID[GRID_Y][GRID_X] == 1) {
                    return true;
                }
            }
        }
        return false;
    }
    void HARD_DROP() {
        while (!isCollision(*CURRENT_PEICE)) {
            CURRENT_PEICE->DOWN();
        }
        //MOVE ONE ROW UP 
        CURRENT_PEICE->SET_Y(CURRENT_PEICE->GET_Y() - 1);
        PLACE_PEICE();
    }
void CLEAR_LINES() {
        int LINES_GOT_CLEARED = 0; 
        for (int y = HEIGHT - 1; y >= 0; y--) {
            bool LINE_FULL = true;     
            for (int x = 0; x < WIDTH; x++) {
                if (GRID[y][x] == 0) {
                    LINE_FULL = false;
                    break;
                }
            }
            if (LINE_FULL) {
                LINES_GOT_CLEARED++;
                // MOVE ALL LINES ABOVE DOWN
                for (int y2 = y; y2 > 0; y2--) {
                    for (int x = 0; x < WIDTH; x++) {
                        GRID[y2][x] = GRID[y2 - 1][x];
                        COLOR_GRID[y2][x] = COLOR_GRID[y2 - 1][x];
                    }
                }
                // CLEAR THE TOP LINE
                for (int x = 0; x < WIDTH; x++) {
                    GRID[0][x] = 0;
                    COLOR_GRID[0][x] = 0;
                }
                // CHECK FOR THE SAME LINE AGAIN
                y++;
            }
        }
        
        // UPDATE SCORE AND THE LEVEL
        if (LINES_GOT_CLEARED > 0) {
            // Scoring: 100 * LINES_GOT_CLEARED * LEVEL
            this->SCORE += 100 * LINES_GOT_CLEARED * this->LEVEL;
            this->LINES_GOT_CLEARED += LINES_GOT_CLEARED;
            
            //UPDATE THE LEVEL
            this->LEVEL = 1 + (this->LINES_GOT_CLEARED );
            
            // UPDATE THE FALL SPEED BASED ON SPEED
            if (SCORE / THSCORE > 0) {
                FALL_SPEED = max(STARTING_SPEED - (SCORE / THSCORE) * INCREASE_SPEED, 100);
            }
        }
    }

    void update() {
        if (PAUSED) return; // SKIP UPDATE IF IT'S!

        auto now = chrono::system_clock::now();
        auto ELAPSED = chrono::duration_cast<chrono::milliseconds>(now - LASTFALL).count();
        
        if (ELAPSED > FALL_SPEED) {
            CURRENT_PEICE->DOWN();
            
            if (isCollision(*CURRENT_PEICE)) {
                CURRENT_PEICE->SET_Y(CURRENT_PEICE->GET_Y() - 1);
                PLACE_PEICE();
            }
            
            LASTFALL = now;
        }
    }

    void draw() {
        // CLEAR THE SCREEN FOR THE FIRST TIME
        static bool FIRSTDRAW = true;
        if (FIRSTDRAW) {
            system("cls");
            FIRSTDRAW = false;
        }
        
        // DRAW THE INFO SECTION
        CURSORPOSITION(0, 0);
        RESETCOLOR();
        cout << "WELCOME TO THE TETRIS GAME : MADE BY TIN TIGDA KAM BIGDA " << endl;
        cout << "SCORE " << SCORE << "  :::::: LEVEL " << LEVEL << " :::::: Lines " << LINES_GOT_CLEARED << endl;
        cout << endl;
    
        // IF GAME IS PAUSED THEN DISPLAY THE PAUSE MESSAGE
        if (PAUSED) {
            // Calculate center position
            int centerX = WIDTH + 1;  // Center of the game grid (WIDTH*2 characters wide + borders)
            int centerY = HEIGHT / 2 + 4;  // Vertical center
            
            // Move cursor to center position and print "PAUSED"
            CURSORPOSITION(centerX - 3, centerY);  // "PAUSED" is 6 characters, so offset by 3
            cout << "PAUSED";
            return; // SKIP THE REST OF DRAWING
        }
    
        // DRAW THE BORDER AND THE GRID
        CURSORPOSITION(0, 3);
        cout << "+" << string(WIDTH * 2, '-') << "+" << endl;
        
        // CREATE A TEMPORARY GRID WITH ONLY PLACED BLOCKS
        vector<vector<int>> TEMP_GRID = GRID;
        vector<vector<int>> TEMP_COLOUR_GRID = COLOR_GRID;
    
        // ADD CURRENT PIECE TO TEMPORARY GRID (for display only)
        if (!GAME_OVER) {
            vector<vector<int>> SHAPE = CURRENT_PEICE->GET_SHAPE();
            int PEICE_HEIGHT = SHAPE.size();
            int PEICE_WIDTH = SHAPE[0].size();
            int PEICETYPE = CURRENT_PEICE->GET_TYPE();
    
            for (int i = 0; i < PEICE_HEIGHT; i++) {
                for (int j = 0; j < PEICE_WIDTH; j++) {
                    if (SHAPE[i][j] == 0) continue;
    
                    int GRID_X = CURRENT_PEICE->GET_X() + j;
                    int GRID_Y = CURRENT_PEICE->GET_Y() + i;
    
                    if (GRID_X >= 0 && GRID_X < WIDTH && GRID_Y >= 0 && GRID_Y < HEIGHT) {
                        TEMP_GRID[GRID_Y][GRID_X] = 1;
                        TEMP_COLOUR_GRID[GRID_Y][GRID_X] = PEICETYPE;
                    }
                }
            }
        }
    
        // DRAW THE GRID WITH COLORS
        for (int y = 0; y < HEIGHT; y++) {
            CURSORPOSITION(0, y + 4);
            cout << "|";
            for (int x = 0; x < WIDTH; x++) {
                if (TEMP_GRID[y][x] == 1) {
                    COLOURS BLOCK_COLOR = BLOCKS_COLOURS[TEMP_COLOUR_GRID[y][x]];
                    SET_COLOR(BLOCK_COLOR);
                    cout << "##";
                    RESETCOLOR();
                } else {
                    cout << "  ";
                }
            }
            cout << "|";
        }
    
        CURSORPOSITION(0, HEIGHT + 4);
        cout << "+" << string(WIDTH * 2, '-') << "+" << endl;
    
        // DRAW NEXT PIECE AREA
        // First clear the next piece area
        for (int i = 0; i < 6; i++) {
            CURSORPOSITION(WIDTH * 2 + 5, i + 5);
            cout << "        "; // Clear the area
        }
    
        CURSORPOSITION(WIDTH * 2 + 5, 4);
        cout << "Next PEICE:";
        
        // DISPLAY NEXT PIECE
        vector<vector<int>> nextSHAPE = NEXT_PEICE->GET_SHAPE();
        COLOURS nextColor = BLOCKS_COLOURS[NEXT_PEICE->GET_TYPE()];
    
        for (int i = 0; i < nextSHAPE.size(); i++) {
            CURSORPOSITION(WIDTH * 2 + 5, i + 5);
            for (int j = 0; j < nextSHAPE[i].size(); j++) {
                if (nextSHAPE[i][j] == 1) {
                    SET_COLOR(nextColor);
                    cout << "##";
                    RESETCOLOR();
                } else {
                    cout << "  ";
                }
            }
        }
    
        // DRAW CONTROLS
        CURSORPOSITION(WIDTH * 2 + 5, 11);
        cout << "CONTROLS :";
        CURSORPOSITION(WIDTH * 2 + 5, 12);
        cout << "Left/Right: Move Left/Right";
        CURSORPOSITION(WIDTH * 2 + 5, 13);
        cout << "Up:-> ROTATE";
        CURSORPOSITION(WIDTH * 2 + 5, 14);
        cout << "Down:-> Soft Drop";
        CURSORPOSITION(WIDTH * 2 + 5, 15);
        cout << "Space: Hard Drop";
        CURSORPOSITION(WIDTH * 2 + 5, 16);
        cout << "P: Pause/Resume";
        CURSORPOSITION(WIDTH * 2 + 5, 17);
        cout << "1: End Game";
        CURSORPOSITION(WIDTH * 2 + 5, 18);
        cout << "2: Restart Game";
        CURSORPOSITION(WIDTH * 2 + 5, 19);
        cout << "ESC: Quit";
    
        // GAME OVER MESSAGE
        if (GAME_OVER) {
            CURSORPOSITION(WIDTH - 4, HEIGHT / 2 + 4);
            cout << "GAME OVER";
        }
    }
    void HANDLE_INPUT() {
        if (_kbhit()) {
            int ch = _getch();
            // FOR THE KEYS
            if (ch == 224) {
                ch = _getch();
                if (!PAUSED) { // IF GAME IS NOT PAUSED THEN HANDLE THE MOVEMENT
                    tetrisblocks tempPEICE = *CURRENT_PEICE; 
                    switch (ch) {
                        case LEFT:
                            CURRENT_PEICE->LEFT();
                            if (isCollision(*CURRENT_PEICE)) {
                                *CURRENT_PEICE = tempPEICE;
                            }
                            break;
                            
                        case RIGHT:
                            CURRENT_PEICE->RIGHT();
                            if (isCollision(*CURRENT_PEICE)) {
                                *CURRENT_PEICE = tempPEICE;
                            }
                            break;
                            
                        case UP
                    :
                            CURRENT_PEICE->ROTATE();
                            if (isCollision(*CURRENT_PEICE)) {
                                *CURRENT_PEICE = tempPEICE;
                            }
                            break;
                            
                        case DOWN:
                            CURRENT_PEICE->DOWN();
                            if (isCollision(*CURRENT_PEICE)) {
                                CURRENT_PEICE->SET_Y(CURRENT_PEICE->GET_Y() - 1);
                                PLACE_PEICE();
                            }
                            LASTFALL = chrono::system_clock::now();
                            break;
                    }
                }
            } else if (ch == SPACE) {
                HARD_DROP();
            } else if (ch == ESC
        ) {
                GAME_OVER = true;
            } else if (ch == 'p' || ch == 'P') { //PAUSED THE GAME(FOR PAUSSE THE GAME)
                PAUSED = !PAUSED; // TOGGLE PAUSED START FOR RESUME
            } else if (ch == '1') { // END THE GAME
                GAME_OVER = true;
            } else if (ch == '2') { // TESTART THE GAME
                reset();
            }
        }
    }
    bool isGAME_OVER() const {
        return GAME_OVER;
    }
};
int main() {
    // SETUP CONSOLE
    system("cls");
    // HIDE CURSOR
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);   
    // CREATE GAME INSTICTENCE
    TETRIS_GAME game;
    //GAME LOOP
    while (true) {
        game.HANDLE_INPUT();
        game.update();
        game.draw();   
        // CHECKING FOR THE GAME OVER
        if (game.isGAME_OVER()) {
            break;
        }    
        // CONTROLL GAME SPEED
        Sleep(50);
    }  
    // GAME OVER MESSAGE TO THE USER
    CURSORPOSITION(0, HEIGHT + 6);
    cout << "GAME IS OVER ! PLEASE PRESS 1 FOR EXIT OR PRESS 2 FOR REPLAY ! THANK YOU";
    
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == '1') {
                break; //EXIT GAME
            } else if (ch == '2') {
                game.reset(); //GAME RESTART
                main(); //RESART THE MAIN FUNCTION
            }
        }
    }  
    // RESET COLOUR BEFORE EXIT
    RESETCOLOR();
    return 0;
}
