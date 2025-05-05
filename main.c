#include <stdio.h>
#include <stdlib.h>

// Function to calculate absolute difference
int abs_diff(int a, int b) {
    return (a > b) ? (a - b) : (b - a);
}

// FCFS algorithm with movement order
int fcfs(int *requests, int initial_head, int size) {
    int total_movement = 0;
    int current_head = initial_head;

    printf("FCFS Order: %d", current_head);
    // Process each request in order
    for (int i = 0; i < size; i++) {
        total_movement += abs_diff(current_head, requests[i]);
        current_head = requests[i];
        printf(" -> %d", current_head);
    }
    printf("\n");
    fflush(stdout);

    return total_movement;
}

// Function to sort requests (Bubble sort for simplicity)
void sort_requests(int *requests, int *sorted, int size) {
    for (int i = 0; i < size; i++) {
        sorted[i] = requests[i];
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
}

// SCAN algorithm with movement order (supports UP and DOWN)
int scan(int *requests, int initial_head, int size, int max_cylinders, int direction) {
    int total_movement = 0;
    int current_head = initial_head;
    int sorted[size];
    
    // Sort requests
    sort_requests(requests, sorted, size);
    
    // Find index where requests >= initial_head
    int split_index = 0;
    for (int i = 0; i < size; i++) {
        if (sorted[i] >= initial_head) {
            split_index = i;
            break;
        }
    }

    printf("SCAN %s Order: %d", (direction == 1 ? "UP" : "DOWN"), current_head);
    
    if (direction == 1) { // SCAN-UP: Move toward higher cylinders first
        // Move toward higher cylinders
        for (int i = split_index; i < size; i++) {
            total_movement += abs_diff(current_head, sorted[i]);
            current_head = sorted[i];
            printf(" -> %d", current_head);
        }

        // Go to the maximum cylinder before reversing
        if (split_index > 0) { // Only if there are requests to the left
            total_movement += abs_diff(current_head, max_cylinders - 1);
            current_head = max_cylinders - 1;
            printf(" -> %d", current_head);
            
            // Move to cylinder 0
            total_movement += abs_diff(current_head, 0);
            current_head = 0;
            printf(" -> %d", current_head);
            
            // Move toward higher cylinders from 0
            for (int i = split_index - 1; i >= 0; i--) {
                total_movement += abs_diff(current_head, sorted[i]);
                current_head = sorted[i];
                printf(" -> %d", current_head);
            }
        }
    } else { // SCAN-DOWN: Move toward lower cylinders first
        // Move toward lower cylinders
        for (int i = split_index - 1; i >= 0; i--) {
            total_movement += abs_diff(current_head, sorted[i]);
            current_head = sorted[i];
            printf(" -> %d", current_head);
        }

        // Go to cylinder 0 before reversing
        if (split_index < size) { // Only if there are requests to the right
            total_movement += abs_diff(current_head, 0);
            current_head = 0;
            printf(" -> %d", current_head);
            
            // Move to maximum cylinder
            total_movement += abs_diff(current_head, max_cylinders - 1);
            current_head = max_cylinders - 1;
            printf(" -> %d", current_head);
            
            // Move toward lower cylinders from max_cylinders
            for (int i = size - 1; i >= split_index; i--) {
                total_movement += abs_diff(current_head, sorted[i]);
                current_head = sorted[i];
                printf(" -> %d", current_head);
            }
        }
    }
    printf("\n");
    fflush(stdout);

    return total_movement;
}

// C-SCAN algorithm with movement order
int c_scan(int *requests, int initial_head, int size, int max_cylinders) {
    int total_movement = 0;
    int current_head = initial_head;
    int sorted[size];
    
    // Sort requests
    sort_requests(requests, sorted, size);
    
    // Find index where requests >= initial_head
    int split_index = 0;
    for (int i = 0; i < size; i++) {
        if (sorted[i] >= initial_head) {
            split_index = i;
            break;
        }
    }

    printf("C-SCAN Order: %d", current_head);
    // Move toward higher cylinders
    for (int i = split_index; i < size; i++) {
        total_movement += abs_diff(current_head, sorted[i]);
        current_head = sorted[i];
        printf(" -> %d", current_head);
    }

    // If there are requests to the left, jump to max cylinder and then to 0
    if (split_index > 0) {
        total_movement += abs_diff(current_head, max_cylinders - 1);
        current_head = max_cylinders - 1;
        printf(" -> %d", current_head);
        // Jump to 0 (don't count this movement)
        current_head = 0;
        printf(" -> %d", current_head);
        // Service remaining requests
        for (int i = 0; i < split_index; i++) {
            total_movement += abs_diff(current_head, sorted[i]);
            current_head = sorted[i];
            printf(" -> %d", current_head);
        }
    }
    printf("\n");
    fflush(stdout);

    return total_movement;
}

int main() {
    int queue_size, initial_head, max_cylinders, choice, scan_direction;

    // Get number of cylinders from user
    printf("Enter the number of cylinders: ");
    scanf("%d", &max_cylinders);
    if (max_cylinders <= 0) {
        printf("Error: Number of cylinders must be greater than 0\n");
        return 1;
    }

    // Get queue size from user
    printf("Enter the number of requests (queue size): ");
    scanf("%d", &queue_size);
    if (queue_size <= 0) {
        printf("Error: Queue size must be greater than 0\n");
        return 1;
    }

    // Get initial head position from user
    printf("Enter the initial head position (0 to %d): ", max_cylinders - 1);
    scanf("%d", &initial_head);
    if (initial_head < 0 || initial_head >= max_cylinders) {
        printf("Error: Initial head position must be between 0 and %d\n", max_cylinders - 1);
        return 1;
    }

    // Dynamically allocate array for requests
    int *requests = (int *)malloc(queue_size * sizeof(int));
    if (requests == NULL) {
        printf("Error: Memory allocation failed\n");
        return 1;
    }

    // Get requests from user
    printf("Enter the %d requests (each between 0 and %d):\n", queue_size, max_cylinders - 1);
    for (int i = 0; i < queue_size; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0 || requests[i] >= max_cylinders) {
            printf("Error: Request %d must be between 0 and %d\n", requests[i], max_cylinders - 1);
            free(requests);
            return 1;
        }
    }

    // Print the requests
    printf("\nRequests: ");
    for (int i = 0; i < queue_size; i++) {
        printf("%d ", requests[i]);
    }
    printf("\nInitial head position: %d\n", initial_head);
    printf("Max cylinder: %d (range 0 to %d)\n", max_cylinders - 1, max_cylinders - 1);
    fflush(stdout);

    // Loop to allow multiple algorithm selections
    while (1) {
        // Choose algorithm
        printf("\nChoose the algorithm to run (or 0 to exit):\n");
        printf("1. FCFS\n2. SCAN\n3. C-SCAN\nEnter your choice (0-3): ");
        scanf("%d", &choice);
        
        if (choice == 0) {
            printf("Exiting program...\n");
            break;
        }
        
        if (choice < 1 || choice > 3) {
            printf("Error: Invalid choice. Please choose between 0 and 3\n");
            continue;
        }

        // For SCAN, ask for direction
        if (choice == 2) {
            printf("Choose SCAN direction:\n1. UP (toward higher cylinders)\n2. DOWN (toward lower cylinders)\nEnter direction (1-2): ");
            scanf("%d", &scan_direction);
            if (scan_direction < 1 || scan_direction > 2) {
                printf("Error: Invalid direction. Please choose 1 or 2\n");
                continue;
            }
        } else {
            scan_direction = 1; // Default for non-SCAN algorithms (not used)
        }

        // Calculate total head movement based on chosen algorithm
        int total_movement = 0;
        printf("\nCalculating head movements...\n");
        switch (choice) {
            case 1:
                total_movement = fcfs(requests, initial_head, queue_size);
                printf("\nTotal Head Movement (FCFS): %d cylinders\n", total_movement);
                break;
            case 2:
                total_movement = scan(requests, initial_head, queue_size, max_cylinders, scan_direction);
                printf("\nTotal Head Movement (SCAN %s): %d cylinders\n", 
                       (scan_direction == 1 ? "UP" : "DOWN"), total_movement);
                break;
            case 3:
                total_movement = c_scan(requests, initial_head, queue_size, max_cylinders);
                printf("\nTotal Head Movement (C-SCAN): %d cylinders\n", total_movement);
                break;
        }
        fflush(stdout);
    }

    // Free allocated memory
    free(requests);

    // Pause to keep terminal open
    printf("\nPress Enter to exit...\n");
    getchar(); // Clear buffer
    getchar();

    return 0;
}