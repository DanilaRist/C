#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h> // For colored output on Windows
#else
    #define SetConsoleTextAttribute(hConsole, wAttributes)
#endif

#define NUM_GAMES 5

// Function to get the NPC's random choice
int get_npc_choice() {
    return rand() % 3; // Random number between 0 and 2
}

// Function to get the user's choice
int get_user_choice() {
    int choice;
    printf("Enter your choice (0 for Rock, 1 for Paper, 2 for Scissors): ");
    while (scanf("%d", &choice) != 1 || choice < 0 || choice > 2) {
        printf("Invalid input. Please enter 0 for Rock, 1 for Paper, or 2 for Scissors: ");
        while (getchar() != '\n'); // Clear the input buffer
    }
    return choice;
}

// Function to determine the winner
int determine_winner(int npc_choice, int user_choice) {
    if (npc_choice == user_choice) {
        return 0; // Tie
    } else if ((user_choice == 0 && npc_choice == 2) ||
               (user_choice == 1 && npc_choice == 0) ||
               (user_choice == 2 && npc_choice == 1)) {
        return 1; // User wins
    } else {
        return -1; // NPC wins
    }
}

// Function to save game results to CSV
void save_results_to_csv(int results[], char *player_name) {
    FILE *file = fopen("Game_Result.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(file, "Game,Result,%s\n", player_name);
    for (int i = 0; i < NUM_GAMES; i++) {
        fprintf(file, "%d,%d\n", i + 1, results[i]);
    }

    fclose(file);
}

// Function to print colored text
void print_colored(char *message, int color_code) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color_code);
        printf("%s", message);
        SetConsoleTextAttribute(hConsole, 15); // Reset to default color
    #else
        if (color_code == 1) {
            printf("\033[1;34m%s\033[0m", message); // Blue for win
        } else if (color_code == 2) {
            printf("\033[1;31m%s\033[0m", message); // Red for loss
        } else {
            printf("%s", message); // Default
        }
    #endif
}

int main() {
    srand(time(0)); // Seed the random number generator with the current time

    int game_results[NUM_GAMES]; // Array to store results of each game
    char player_name[50];

    // Ask for the player's name
    printf("Enter your name: ");
    scanf("%s", player_name);

    int play_again = 1;

    while (play_again) {
        // Display choice mapping
        printf("Choices: 0 for Rock, 1 for Paper, 2 for Scissors\n");

        // Play five games
        for (int i = 0; i < NUM_GAMES; i++) {
            printf("\n--- Game %d ---\n", i + 1);

            // NPC and user select their choices
            int npc_choice = get_npc_choice();
            int user_choice = get_user_choice();

            // Display NPC's choice
            printf("NPC chose: %s\n", (npc_choice == 0) ? "Rock" : (npc_choice == 1) ? "Paper" : "Scissors");

            // Determine the result of the game
            int result = determine_winner(npc_choice, user_choice);

            // Record the result
            game_results[i] = result;

            // Display the outcome
            if (result == 1) {
                print_colored("You win this round!\n", 1); // Blue for win
            } else if (result == -1) {
                print_colored("You lose this round.\n", 2); // Red for loss
            } else {
                printf("This round is a tie.\n");
            }
        }

        // Calculate the overall result
        int total_wins = 0, total_losses = 0;
        for (int i = 0; i < NUM_GAMES; i++) {
            if (game_results[i] == 1) total_wins++;
            else if (game_results[i] == -1) total_losses++;
        }

        // Display final result
        if (total_wins > total_losses) {
            char win_message[100];
            snprintf(win_message, sizeof(win_message), "Congratulations %s, you won!\n", player_name);
            print_colored(win_message, 1); // Blue for overall win
        } else if (total_losses > total_wins) {
            char lose_message[100];
            snprintf(lose_message, sizeof(lose_message), "Sorry %s, you lost.\n", player_name);
            print_colored(lose_message, 2); // Red for overall loss
        } else {
            printf("The game ended in a tie.\n");
        }

        // Save the results to CSV
        save_results_to_csv(game_results, player_name);
        printf("\nResults saved to Game_Result.csv\n");

        // Ask if the player wants to play again
        printf("\nDo you want to play again? (1 for Yes, 0 for No): ");
        scanf("%d", &play_again);
    }

    printf("Thank you for playing, %s!\n", player_name);

    return 0;
}
