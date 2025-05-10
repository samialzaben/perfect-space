/* spacexplorer.h - Header file for SpaceXplorer game */

#ifndef SPACEXPLORER_H
#define SPACEXPLORER_H

/* Constants */
#define MAX_WORLD_SIZE 30
#define MAX_SCORES 10
#define MIN_POINTS_TO_WIN 50

/* Game element types */
#define EMPTY 0
#define PLAYER 1
#define JUNK 2
#define ASTEROID 3
#define HOME 4

/* Difficulty levels */
#define EASY 1
#define MEDIUM 2
#define HARD 3

/* Structures */
typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int x;
    int y;
    int dx; // Direction X (-1, 0, 1)
    int dy; // Direction Y (-1, 0, 1)
} MovingObject;

typedef struct {
    int x;
    int y;
    int fuel;
    int health;
    int junkCollected;
    int score;
} Player;

typedef struct {
    int worldSize;
    int world[MAX_WORLD_SIZE][MAX_WORLD_SIZE];
    Player player;
    MovingObject asteroid;
    Position home;
    int difficulty;
    int fuelConsumption;
    int asteroidMoveInterval;
    int junkCount;
    int moveCount;
} Game;

/* Function Prototypes */
void displayWelcomeMessage();
void displayInstructions();
void setupGame(Game *game);
void initializeGame(Game *game, int difficulty);
void placeSpaceJunk(Game *game, int count);
void displayGameState(Game *game);
void playGame(Game *game);
void movePlayer(Game *game, int dx, int dy);
void moveAsteroid(Game *game);
void displayInventory(Game *game);
void recycleJunk(Game *game);
int checkWinCondition(Game *game);
int checkLossCondition(Game *game);
void saveScore(Game *game);
void displayHighScores();
void clearScreen();

#endif /* SPACEXPLORER_H */