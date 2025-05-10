#include <stdio.h> // Include standard input/output library for functions like printf, scanf
#include <stdlib.h>// Include standard library for functions like rand, system
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "spacexplorer.h"


int main() {
    srand(time(NULL));

    Game game;
    int choice;


    displayWelcomeMessage();


    do {
        printf("\n===== SPACEXPLORER MAIN MENU =====\n");
        printf("1. Start New Game\n");
        printf("2. View Instructions\n");
        printf("3. View High Scores\n");
        printf("4. Exit\n");
        printf("Choose an option (1-4): ");
        if (scanf("%d", &choice) != 1) {

            printf("Invalid input. Please enter a number.\n");

            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                setupGame(&game);
                playGame(&game);
                break;
            case 2:
                displayInstructions();
                break;
            case 3:
                displayHighScores();
                break;
            case 4:
                printf("Thank you for playing SpaceXplorer! Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void displayWelcomeMessage() {
    printf("*************************************************\n");
    printf("*                 SPACEXPLORER                  *\n");
    printf("*                                               *\n");
    printf("* Welcome brave astronaut to the vast expanse   *\n");
    printf("* of deep space. Your mission is to navigate    *\n");
    printf("* back to Earth while cleaning up space junk.   *\n");
    printf("* Watch your fuel and avoid the asteroid!       *\n");
    printf("*************************************************\n");
    printf("* Use space junk to recycle for fuel & repairs  *\n");
    printf("* Find your way to Home (H) to win the game!    *\n");
    printf("* You need at least %d points to complete your  *\n", MIN_POINTS_TO_WIN);
    printf("* mission successfully.                         *\n");
    printf("*************************************************\n");
}

void displayInstructions() {
    printf("\n===== GAME INSTRUCTIONS =====\n");
    printf("You are an astronaut lost in deep space.\n");
    printf("Your mission is to collect space junk to upgrade your ship\n");
    printf("and eventually find your way back to Earth.\n\n");

    printf("CONTROLS:\n");
    printf("- W: Move Up\n");
    printf("- S: Move Down\n");
    printf("- A: Move Left\n");
    printf("- D: Move Right\n");
    printf("- I: Check Inventory/Ship Status\n");
    printf("- R: Recycle Space Junk\n");
    printf("- Q: Quit Game\n\n");

    printf("GAME ELEMENTS:\n");
    printf(" $: Your Spaceship\n");
    printf(" *: Space Junk\n");
    printf(" X: Asteroid (avoid this!)\n");
    printf(" H: Home (reach this to win)\n\n");

    printf("DIFFICULTY LEVELS:\n");
    printf("1. Easy:\n");
    printf("   - Fuel consumption: 1 unit per move\n");
    printf("   - Asteroid moves every 2 player moves\n");
    printf("   - Space junk available: 25 pieces\n\n");

    printf("2. Medium:\n");
    printf("   - Fuel consumption: 2 units per move\n");
    printf("   - Asteroid moves every player move\n");
    printf("   - Space junk available: 20 pieces\n\n");

    printf("3. Hard:\n");
    printf("   - Fuel consumption: 3 units per move\n");
    printf("   - Asteroid moves every player move\n");
    printf("   - Space junk available: 15 pieces\n\n");

    printf("WINNING THE GAME:\n");
    printf("- Collect at least %d points from space junk\n", MIN_POINTS_TO_WIN);
    printf("- Find your way back to Home (H)\n");
    printf("- If you reach Home without enough points, you'll need to\n");
    printf("  continue collecting more junk before returning\n\n");

    printf("TIPS:\n");
    printf("- Each move consumes fuel based on difficulty\n");
    printf("- Collect space junk to recycle into fuel and upgrades\n");
    printf("- Avoid the asteroid at all costs\n");
    printf("- Monitor your fuel levels and ship health\n");
    printf("- Higher difficulties have faster asteroids and higher fuel consumption\n");

    printf("\nPress Enter to continue...");
    getchar();
}

void setupGame(Game *game) {
    int difficulty;
    int validInput = 0;


    while (getchar() != '\n');


    while (!validInput) {
        // Choose difficulty
        printf("\n===== SELECT DIFFICULTY =====\n");
        printf("1. Easy\n");
        printf("2. Medium\n");
        printf("3. Hard\n");
        printf("Choose difficulty (1-3): ");

        if (scanf("%d", &difficulty) != 1) {

            printf("Please enter a number between 1 and 3.\n");

            while (getchar() != '\n');
            continue;
        }


        if (difficulty >= 1 && difficulty <= 3) {
            validInput = 1;
        } else {
            printf("Invalid choice. Please select a number between 1 and 3.\n");

            while (getchar() != '\n');
        }
    }


    initializeGame(game, difficulty);


    clearScreen();
    printf("Game initialized! Good luck, explorer!\n");
    printf("Press Enter to start...");
    getchar();

}

void initializeGame(Game *game, int difficulty) {
    int i, j;


    switch (difficulty) {
        case 1:
            game->difficulty = EASY;
            game->fuelConsumption = 1;
            game->asteroidMoveInterval = 2;
            game->junkCount = 25;
            break;
        case 2:
            game->difficulty = MEDIUM;
            game->fuelConsumption = 2;
            game->asteroidMoveInterval = 1;
            game->junkCount = 20;
            break;
        case 3:
            game->difficulty = HARD;
            game->fuelConsumption = 3;
            game->asteroidMoveInterval = 1;
            game->junkCount = 15;
            break;
        default:
            game->difficulty = MEDIUM;
            game->fuelConsumption = 2;
            game->asteroidMoveInterval = 1;
            game->junkCount = 20;
    }


    game->worldSize = 18;
    game->moveCount = 0;


    game->player.x = game->worldSize / 2;
    game->player.y = game->worldSize / 2;
    game->player.fuel = 100;
    game->player.health = 100;
    game->player.junkCollected = 0;
    game->player.score = 0;


    int edge = rand() % 4;


    if (rand() == rand()) {
        fprintf(stderr, "WARNING: Random number generator may not be properly seeded!\n");
    }

    switch (edge) {
        case 0:
            game->asteroid.x = rand() % game->worldSize;
            game->asteroid.y = 0;
            game->asteroid.dx = (rand() % 3) - 1;
            game->asteroid.dy = 1;
            break;
        case 1:
            game->asteroid.x = game->worldSize - 1;
            game->asteroid.y = rand() % game->worldSize;
            game->asteroid.dx = -1;
            game->asteroid.dy = (rand() % 3) - 1;
            break;
        case 2:
            game->asteroid.x = rand() % game->worldSize;
            game->asteroid.y = game->worldSize - 1;
            game->asteroid.dx = (rand() % 3) - 1;
            game->asteroid.dy = -1;
            break;
        case 3:
            game->asteroid.x = 0;
            game->asteroid.y = rand() % game->worldSize;
            game->asteroid.dx = 1;
            game->asteroid.dy = (rand() % 3) - 1;
            break;
    }


    if (game->asteroid.dx == 0 && game->asteroid.dy == 0) {
        game->asteroid.dx = 1;
    }


    if (edge == 0) {
        game->home.x = rand() % game->worldSize;
        game->home.y = game->worldSize - 1;
    } else if (edge == 1) {
        game->home.x = 0;
        game->home.y = rand() % game->worldSize;
    } else if (edge == 2) {
        game->home.x = rand() % game->worldSize;
        game->home.y = 0;
    } else {
        game->home.x = game->worldSize - 1;
        game->home.y = rand() % game->worldSize;
    }


    for (i = 0; i < MAX_WORLD_SIZE; i++) {
        for (j = 0; j < MAX_WORLD_SIZE; j++) {
            game->world[i][j] = EMPTY;
        }
    }


    game->world[game->player.y][game->player.x] = PLAYER;
    game->world[game->asteroid.y][game->asteroid.x] = ASTEROID;
    game->world[game->home.y][game->home.x] = HOME;


    placeSpaceJunk(game, game->junkCount);
}

void placeSpaceJunk(Game *game, int count) {
    int x, y;
    int placed = 0;
    int attempts = 0;
    const int MAX_ATTEMPTS = 1000;

    while (placed < count && attempts < MAX_ATTEMPTS) {
        x = rand() % game->worldSize;
        y = rand() % game->worldSize;
        attempts++;


        if (game->world[y][x] == EMPTY) {
            game->world[y][x] = JUNK;
            placed++;
        }
    }


    if (placed < count) {
        game->junkCount = placed;
    }
}

void displayGameState(Game *game) {
    int i, j;

    clearScreen();


    printf("=== SPACEXPLORER ===\n");
    printf("Difficulty: %s\n",
           game->difficulty == EASY ? "Easy" :
           game->difficulty == MEDIUM ? "Medium" : "Hard");
    printf("Fuel: %d units\n", game->player.fuel);
    printf("Ship Health: %d%%\n", game->player.health);
    printf("Space Junk Collected: %d\n", game->player.junkCollected);
    printf("Score: %d (need %d to win)\n", game->player.score, MIN_POINTS_TO_WIN);
    printf("Moves: %d\n\n", game->moveCount);


    printf("+");
    for (i = 0; i < game->worldSize; i++) {
        printf("-");
    }
    printf("+\n");


    for (i = 0; i < game->worldSize; i++) {
        printf("|");
        for (j = 0; j < game->worldSize; j++) {
            switch (game->world[i][j]) {
                case EMPTY:
                    printf(" ");
                    break;
                case PLAYER:
                    printf("@");
                    break;
                case JUNK:
                    printf("*");
                    break;
                case ASTEROID:
                    printf("X");
                    break;
                case HOME:
                    printf("H");
                    break;
                default:
                    printf(" ");
            }
        }
        printf("|\n");
    }


    printf("+");
    for (i = 0; i < game->worldSize; i++) {
        printf("-");
    }
    printf("+\n\n");


    printf("Controls: W (Up), S (Down), A (Left), D (Right), I (Status), R (Recycle), Q (Quit)\n");
    printf("NOTE: Enter only ONE letter command at a time and press Enter.\n");
}

void playGame(Game *game) {
    char input;
    int gameOver = 0;

    while (!gameOver) {

        displayGameState(game);


        printf("Enter command: ");
        if (scanf(" %c", &input) != 1) {
            // Handle input error
            printf("Invalid input. Please enter a single letter command (W, S, A, D, I, R, Q).\n");
            while (getchar() != '\n');
            continue;
        }

        input = toupper(input);


        switch (input) {
            case 'W':
                movePlayer(game, 0, -1);
                break;
            case 'S':
                movePlayer(game, 0, 1);
                break;
            case 'A':
                movePlayer(game, -1, 0);
                break;
            case 'D':
                movePlayer(game, 1, 0);
                break;
            case 'I':
                displayInventory(game);
                continue;
            case 'R':
                recycleJunk(game);
                continue;
            case 'Q':
                printf("Are you sure you want to quit? (Y/N): ");
                if (scanf(" %c", &input) != 1) {
                    printf("Invalid input. Continuing game.\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (toupper(input) == 'Y') {
                    gameOver = 1;
                    printf("Game aborted. Returning to main menu...\n");
                }
                continue;
            default:
                printf("Invalid command: '%c'. Please use W, S, A, D, I, R, or Q.\n", input);
                continue;
        }


        game->moveCount++;
        if (game->moveCount % game->asteroidMoveInterval == 0) {
            moveAsteroid(game);
        }


        if (checkWinCondition(game)) {
            gameOver = 1;
            displayGameState(game);
            printf("Congratulations! You've made it back home!\n");
            saveScore(game);
        } else if (checkLossCondition(game)) {
            gameOver = 1;
            displayGameState(game);

            if (game->player.fuel <= 0) {
                printf("Game Over! You've run out of fuel and are drifting in space forever.\n");
            } else {
                printf("Game Over! Your ship was destroyed by an asteroid.\n");
            }

            saveScore(game);
        }
    }
}

void movePlayer(Game *game, int dx, int dy) {
    int newX = game->player.x + dx;
    int newY = game->player.y + dy;


    if (newX < 0 || newX >= game->worldSize || newY < 0 || newY >= game->worldSize) {
        printf("Cannot move outside the boundaries of space!\n");
        return;
    }


    if (game->player.fuel < game->fuelConsumption) {
        printf("Not enough fuel to move!\n");
        return;
    }


    game->world[game->player.y][game->player.x] = EMPTY;


    if (game->world[newY][newX] == JUNK) {
        game->player.junkCollected++;
        game->player.score += 10;
        printf("You collected a piece of space junk!\n");
    } else if (game->world[newY][newX] == ASTEROID) {

        game->player.health = 0;
    } else if (game->world[newY][newX] == HOME) {

        if (game->player.score < MIN_POINTS_TO_WIN) {
            printf("You've reached home, but need at least %d points to win!\n", MIN_POINTS_TO_WIN);
            printf("You currently have %d points. Collect more space junk!\n", game->player.score);
        } else {

            game->player.score += 100;
        }
    }


    game->player.x = newX;
    game->player.y = newY;


    if (game->world[newY][newX] != ASTEROID) {
        game->world[newY][newX] = PLAYER;
    }


    game->player.fuel -= game->fuelConsumption;
}

void moveAsteroid(Game *game) {

    int newX = game->asteroid.x + game->asteroid.dx;
    int newY = game->asteroid.y + game->asteroid.dy;


    if (newX < 0) {
        newX = 0;
        game->asteroid.dx *= -1;
    } else if (newX >= game->worldSize) {
        newX = game->worldSize - 1;
        game->asteroid.dx *= -1;
    }

    if (newY < 0) {
        newY = 0;
        game->asteroid.dy *= -1;
    } else if (newY >= game->worldSize) {
        newY = game->worldSize - 1;
        game->asteroid.dy *= -1;
    }


    if (game->world[game->asteroid.y][game->asteroid.x] == ASTEROID) {
        game->world[game->asteroid.y][game->asteroid.x] = EMPTY;
    }


    game->asteroid.x = newX;
    game->asteroid.y = newY;


    if (game->asteroid.x == game->player.x && game->asteroid.y == game->player.y) {
        game->player.health = 0;
    } else {
        game->world[game->asteroid.y][game->asteroid.x] = ASTEROID;
    }
}

void displayInventory(Game *game) {
    printf("\n===== SHIP STATUS =====\n");
    printf("Fuel: %d units\n", game->player.fuel);
    printf("Ship Health: %d%%\n", game->player.health);
    printf("Space Junk Collected: %d pieces\n", game->player.junkCollected);
    printf("Score: %d points", game->player.score);


    if (game->player.score < MIN_POINTS_TO_WIN) {
        printf(" (need %d more to win)\n", MIN_POINTS_TO_WIN - game->player.score);
    } else {
        printf(" (enough to win! Find your way home!)\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
}

void recycleJunk(Game *game) {
    if (game->player.junkCollected <= 0) {
        printf("\nNo space junk to recycle!\n");
    } else {
        printf("\n===== RECYCLING OPTIONS =====\n");
        printf("1. Convert to Fuel (+20 fuel per junk)\n");
        printf("2. Repair Ship (+10%% health per junk)\n");
        printf("3. Cancel\n");

        int choice;
        printf("Choose an option (1-3): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Recycling canceled.\n");
            while (getchar() != '\n');
            choice = 3;
        }

        switch (choice) {
            case 1:
                game->player.fuel += 20 * game->player.junkCollected;
                printf("Recycled %d junk into %d fuel units!\n",
                       game->player.junkCollected, 20 * game->player.junkCollected);
                game->player.score += 5 * game->player.junkCollected;
                game->player.junkCollected = 0;
                break;
            case 2:
            {
                int repairAmount = 10 * game->player.junkCollected;
                game->player.health += repairAmount;
                if (game->player.health > 100) {
                    game->player.health = 100;
                }
                printf("Repaired ship for +%d%% health!\n", repairAmount);
                game->player.score += 5 * game->player.junkCollected;
                game->player.junkCollected = 0;
            }
                break;
            case 3:
                printf("Recycling canceled.\n");
                break;
            default:
                printf("Invalid choice. Recycling canceled.\n");
        }
    }

    printf("\nPress Enter to continue...");
    getchar();
}

int checkWinCondition(Game *game) {

    return (game->player.x == game->home.x &&
            game->player.y == game->home.y &&
            game->player.score >= MIN_POINTS_TO_WIN);
}

int checkLossCondition(Game *game) {

    return (game->player.fuel <= 0 || game->player.health <= 0);
}

void saveScore(Game *game) {
    char playerName[50];
    FILE *scoreFile;


    printf("Enter your name for the high score table: ");
    scanf("%49s", playerName);


    scoreFile = fopen("highscores.txt", "a");
    if (scoreFile == NULL) {
        printf("Error: Unable to save score.\n");
        return;
    }


    fprintf(scoreFile, "%s,%d,%s,%d\n",
            playerName,
            game->player.score,
            game->difficulty == EASY ? "Easy" :
            game->difficulty == MEDIUM ? "Medium" : "Hard",
            game->moveCount);

    fclose(scoreFile);
    printf("Score saved successfully!\n");
}

void displayHighScores() {
    FILE *scoreFile;
    char line[256];
    char name[50];
    int score, moves;
    char diffText[10];
    int count = 0;


    typedef struct {
        char name[50];
        int score;
        char difficulty[10];
        int moves;
    } ScoreEntry;

    ScoreEntry scores[MAX_SCORES];


    scoreFile = fopen("highscores.txt", "r");
    if (scoreFile == NULL) {
        printf("\n===== HIGH SCORES =====\n");
        printf("No high scores found.\n");
        printf("\nPress Enter to continue...");
        getchar();

        return;
    }


    while (fgets(line, sizeof(line), scoreFile) && count < MAX_SCORES) {
        if (sscanf(line, "%[^,],%d,%[^,],%d", name, &score, diffText, &moves) == 4) {
            strcpy(scores[count].name, name);
            scores[count].score = score;
            strcpy(scores[count].difficulty, diffText);
            scores[count].moves = moves;
            count++;
        }
    }

    fclose(scoreFile);


    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (scores[j].score < scores[j + 1].score) {
                ScoreEntry temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }


    printf("\n===== HIGH SCORES =====\n");
    printf("%-20s %-10s %-10s %-10s\n", "Name", "Score", "Difficulty", "Moves");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-20s %-10d %-10s %-10d\n",
               scores[i].name,
               scores[i].score,
               scores[i].difficulty,
               scores[i].moves);
    }

    if (count == 0) {
        printf("No high scores found.\n");
    }

    printf("\nPress Enter to continue...");
    getchar();
}

void clearScreen() {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}