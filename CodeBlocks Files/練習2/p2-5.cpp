//Answer provided by ChatGPT
#include <stdio.h>

int main() {
    int SZ, P;

    while (scanf("%d %d", &SZ, &P) && (SZ != 0 || P != 0)) {
        int center = (SZ + 1) / 2; // Center of the grid

        if (P == 1) {
            // If P is 1, it's always at the center
            printf("Line = %d, column = %d.\n", center, center);
            continue;
        }

        // Determine the ring (layer) of the position P
        int k = 0;
        int max_in_ring = 1;

        while (max_in_ring < P) {
            k++;
            max_in_ring = (2 * k + 1) * (2 * k + 1);
        }

        int side_len = 2 * k + 1; // Length of side of the current ring
        int min_in_ring = (side_len - 2) * (side_len - 2) + 1; // Minimum position in this ring

        // Starting position at bottom-right corner of the ring
        int x = center + k;
        int y = center + k;
        int offset = max_in_ring - P;

        // Move anti-clockwise to find the exact coordinates of P
        if (offset < side_len - 1) {
            y -= offset;
        } else if (offset < 2 * (side_len - 1)) {
            y -= (side_len - 1);
            x -= (offset - (side_len - 1));
        } else if (offset < 3 * (side_len - 1)) {
            y -= (side_len - 1);
            x -= (side_len - 1);
            y += (offset - 2 * (side_len - 1));
        } else {
            x += (offset - 3 * (side_len - 1)) - (side_len - 1);
        }

        // Output the result
        printf("Line = %d, column = %d.\n", y, x);
    }

    return 0;
}
