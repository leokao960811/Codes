#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Board dimensions
#define MAX_HEIGHT 11
#define MAX_WIDTH  13

// Directions for bomb explosion (up, down, left, right)
int directions[4][2] = { {0,-1}, {0,1}, {-1,0}, {1,0} };

// Function to compute the number of boxes that a bomb placed at (x,y) would destroy.
// It counts the center cell if it is a box and then for each direction, goes outwards up to 'range'.
// It stops when a box is hit in that direction.
int scoreBomb(int x, int y, char board[MAX_HEIGHT][MAX_WIDTH+1], int width, int height, int range) {
    int score = 0;
    // Check center cell.
    if (board[y][x] == '0') {
        score++;
    }
    // For each direction:
    for (int d = 0; d < 4; d++) {
        for (int r = 1; r <= range; r++) {
            int nx = x + directions[d][0] * r;
            int ny = y + directions[d][1] * r;
            // Check bounds.
            if (nx < 0 || nx >= width || ny < 0 || ny >= height)
                break;
            // If a box is encountered, count it and stop further propagation.
            if (board[ny][nx] == '0') {
                score++;
                break;
            }
            // If it is a floor, continue checking further cells.
            if (board[ny][nx] == '.')
                continue;
        }
    }
    return score;
}

// Helper function to choose the next move (one step) toward target (tx,ty) from current position (px,py).
// This function tries to move in the cardinal direction that reduces Manhattan distance,
// while ensuring that the destination is a floor tile.
void chooseNextMove(int px, int py, int tx, int ty, char board[MAX_HEIGHT][MAX_WIDTH+1], int width, int height, int *next_x, int *next_y) {
    // Compute differences.
    int dx = tx - px;
    int dy = ty - py;
    int stepX = 0, stepY = 0;
    // Choose horizontal or vertical move based on which difference is larger.
    if (abs(dx) >= abs(dy)) {
        stepX = (dx > 0) ? 1 : ((dx < 0) ? -1 : 0);
    } else {
        stepY = (dy > 0) ? 1 : ((dy < 0) ? -1 : 0);
    }

    int candidateX = px + stepX;
    int candidateY = py + stepY;

    // Check if the candidate move is within bounds and not a box.
    if (candidateX >= 0 && candidateX < width && candidateY >= 0 && candidateY < height && board[candidateY][candidateX] == '.') {
        *next_x = candidateX;
        *next_y = candidateY;
        return;
    }

    // If the preferred move isn¡¦t available, try all four directions.
    int bestDist = 1000;
    for (int d = 0; d < 4; d++) {
        int nx = px + directions[d][0];
        int ny = py + directions[d][1];
        if (nx >= 0 && nx < width && ny >= 0 && ny < height && board[ny][nx] == '.') {
            int dist = abs(tx - nx) + abs(ty - ny);
            if (dist < bestDist) {
                bestDist = dist;
                *next_x = nx;
                *next_y = ny;
            }
        }
    }
    // If no adjacent floor tile found, remain in place.
    // (Alternatively, you can choose to move anyway.)
}

// Main game loop.
int main()
{
    int width, height, my_id;
    scanf("%d%d%d", &width, &height, &my_id);

    // game loop
    while (1) {

        char board[MAX_HEIGHT][MAX_WIDTH+1] = {};
        for (int i = 0; i < height; i++) {
            scanf("%s", board[i]);
            fprintf(stderr, "%s\n", board[i]);
        }

        // Variables to store your player info.
        int my_x = -1, my_y = -1;
        int bombCount = 0;
        int myRange = 3; // Default bomb range.

        int entities;
        scanf("%d", &entities);
        for (int i = 0; i < entities; i++) {
            int entity_type, owner, x, y, param1, param2;
            scanf("%d%d%d%d%d%d", &entity_type, &owner, &x, &y, &param1, &param2);
            // Identify your player.
            if (entity_type == 0 && owner == my_id) {
                my_x = x;
                my_y = y;
                bombCount = param1; // Bombs available.
                myRange = param2;   // Your bomb explosion range.
                fprintf(stderr, "My Position: %d %d, Bombs: %d, Range: %d\n", my_x, my_y, bombCount, myRange);
            }
        }

        // Evaluate every cell on the board to find the best bomb placement.
        int bestScore = -1;
        int best_x = -1, best_y = -1;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                // Consider cells that are floor or even a box (bombing on a box will destroy it).
                if (board[i][j] == '.' || board[i][j] == '0') {
                    int score = scoreBomb(j, i, board, width, height, myRange);
                    if (score > bestScore) {
                        bestScore = score;
                        best_x = j;
                        best_y = i;
                    }
                }
            }
        }

        // Decide action.
        if (bombCount > 0 && bestScore > 0) {
            // Bomb if you have one and there's a benefit.
            printf("BOMB %d %d Player\n", best_x, best_y);
            fprintf(stderr, "BOMB at %d %d (Score: %d)\n", best_x, best_y, bestScore);
        } else {
            // Otherwise, move one step toward the best target.
            int next_x = my_x, next_y = my_y;
            chooseNextMove(my_x, my_y, best_x, best_y, board, width, height, &next_x, &next_y);
            printf("MOVE %d %d Player\n", next_x, next_y);
            fprintf(stderr, "MOVE to %d %d toward target %d %d\n", next_x, next_y, best_x, best_y);
        }
    }
    return 0;
}
