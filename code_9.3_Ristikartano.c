#include <stdio.h>
#include <string.h>

#define MAX_GAMES 100

typedef struct {
    char name[100];
    int num_players;
    int average_play_time; // in minutes
    float rating; // from 0.0 to 10.0
    int times_played; // count of how many times played
    char link[200]; // link to the game
} BoardGame;

BoardGame collection[MAX_GAMES];
int game_count = 0;

// Function to save collection to CSV
void save_to_csv() {
    FILE *file = fopen("Board_Game_Collection.csv", "w");
    fprintf(file, "Name,Number of Players,Average Play Time,Rating,Times Played,Link\n");
    
    for (int i = 0; i < game_count; i++) {
        fprintf(file, "%s,%d,%d,%f,%d,%s\n", collection[i].name, collection[i].num_players,
                collection[i].average_play_time, collection[i].rating, collection[i].times_played, collection[i].link);
    }
    fclose(file);
    printf("Collection saved to Board_Game_Collection.csv\n");
}

// Function to add a game
void add_game() {
    if (game_count < MAX_GAMES) {
        printf("Enter game name: ");
        scanf(" %[^\n]", collection[game_count].name);
        printf("Enter number of players: ");
        scanf("%d", &collection[game_count].num_players);
        printf("Enter average play time (in minutes): ");
        scanf("%d", &collection[game_count].average_play_time);
        printf("Enter rating (0-10): ");
        scanf("%f", &collection[game_count].rating);
        printf("Enter link to the game: ");
        scanf(" %[^\n]", collection[game_count].link);
        collection[game_count].times_played = 0; // Initialize times played
        game_count++;
        printf("Game added successfully!\n");
        
        // Automatically save to CSV
        save_to_csv();
    } else {
        printf("Game collection is full!\n");
    }
}

// Function to play a game
void play_game() {
    char game_name[100];
    printf("Enter the name of the game you played: ");
    scanf(" %[^\n]", game_name);
    
    for (int i = 0; i < game_count; i++) {
        if (strcmp(collection[i].name, game_name) == 0) {
            collection[i].times_played++;
            printf("You played %s! Total plays: %d\n", collection[i].name, collection[i].times_played);
            return;
        }
    }
    printf("Game not found in your collection.\n");
}

// Function to display the most played game
void display_most_played() {
    int max_played = 0;
    char most_played_games[100][100]; // Array to hold names of most played games
    int count = 0;

    // Find the maximum times played
    for (int i = 0; i < game_count; i++) {
        if (collection[i].times_played > max_played) {
            max_played = collection[i].times_played;
        }
    }

    // Collect all games with the maximum times played
    for (int i = 0; i < game_count; i++) {
        if (collection[i].times_played == max_played) {
            strcpy(most_played_games[count], collection[i].name);
            count++;
        }
    }

    if (max_played > 0) {
        printf("Most played game(s) (%d times):\n", max_played);
        for (int i = 0; i < count; i++) {
            printf("- %s\n", most_played_games[i]);
        }
    } else {
        printf("No games have been played yet.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nBoard Game Collection Management System\n");
        printf("1. Add Game\n");
        printf("2. Play Game\n");
        printf("3. Display Most Played Game\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 1) {
            add_game();
        } else if (choice == 2) {
            play_game();
        } else if (choice == 3) {
            display_most_played();
        } else if (choice == 4) {
            break; // Exit the loop
        } else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
