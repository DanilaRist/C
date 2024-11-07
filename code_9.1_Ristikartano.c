#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATIENTS 5

// Function to calculate BMI
double calculate_bmi(double weight, double height_in_meters) {
    return weight / (height_in_meters * height_in_meters);
}

// Function to calculate and display average BMI
double calculate_average_bmi(double bmi[], int total_patients) {
    double total_bmi = 0.0;
    for (int i = 0; i < total_patients; i++) {
        total_bmi += bmi[i];
    }
    return total_bmi / total_patients;
}

// Function to count patients by gender
void count_gender(char gender[], int total_patients, int *male_count, int *female_count) {
    *male_count = 0;
    *female_count = 0;
    for (int i = 0; i < total_patients; i++) {
        if (gender[i] == 'M' || gender[i] == 'm') {
            (*male_count)++;
        } else if (gender[i] == 'F' || gender[i] == 'f') {
            (*female_count)++;
        }
    }
}

// Function to count patients with BMI over 25
int count_bmi_over_25(double bmi[], int total_patients) {
    int count = 0;
    for (int i = 0; i < total_patients; i++) {
        if (bmi[i] > 25.0) {
            count++;
        }
    }
    return count;
}

// Function to save patient data to CSV files
void save_to_csv(char *filename, char data[][100], int total_patients) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < total_patients; i++) {
        fprintf(file, "%s\n", data[i]);
    }
    fclose(file);
}

void save_to_csv_numbers(char *filename, int data[], int total_patients) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < total_patients; i++) {
        fprintf(file, "%d\n", data[i]);
    }
    fclose(file);
}

void save_to_csv_doubles(char *filename, double data[], int total_patients) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < total_patients; i++) {
        fprintf(file, "%.2f\n", data[i]);
    }
    fclose(file);
}

// Validate if the input is numeric
int is_valid_number(char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i]) && input[i] != '.') {
            return 0;
        }
    }
    return 1;
}

// Validate gender input
int is_valid_gender(char gender) {
    return gender == 'M' || gender == 'm' || gender == 'F' || gender == 'f';
}

int main() {
    char first_name[MAX_PATIENTS][100], last_name[MAX_PATIENTS][100], gender[MAX_PATIENTS];
    int age[MAX_PATIENTS];
    double height_cm[MAX_PATIENTS], weight[MAX_PATIENTS], bmi[MAX_PATIENTS];
    char buffer[100];

    // Input patient details
    for (int i = 0; i < MAX_PATIENTS; i++) {
        printf("\n------------ Enter details for Patient %d ------------\n", i + 1);
        
        // First name
        printf("First Name: ");
        scanf("%s", first_name[i]);

        // Last name
        printf("Last Name: ");
        scanf("%s", last_name[i]);

        // Age
        while (1) {
            printf("Age: ");
            scanf("%s", buffer); // Take input as string for validation
            if (is_valid_number(buffer)) {
                age[i] = atoi(buffer);
                break;
            } else {
                printf("Invalid age. Please enter a valid number.\n");
            }
        }

        // Gender
        while (1) {
            printf("Gender (M/F): ");
            scanf(" %c", &gender[i]);
            if (is_valid_gender(gender[i])) {
                break;
            } else {
                printf("Invalid gender. Please enter 'M' for male or 'F' for female.\n");
            }
        }

        // Height (in centimeters)
        while (1) {
            printf("Height (in centimeters): ");
            scanf("%s", buffer); // Take input as string for validation
            if (is_valid_number(buffer)) {
                height_cm[i] = atof(buffer);
                break;
            } else {
                printf("Invalid height. Please enter a valid number in centimeters.\n");
            }
        }

        // Weight (in kilograms)
        while (1) {
            printf("Weight (in kg): ");
            scanf("%s", buffer); // Take input as string for validation
            if (is_valid_number(buffer)) {
                weight[i] = atof(buffer);
                break;
            } else {
                printf("Invalid weight. Please enter a valid number in kilograms.\n");
            }
        }

        // Convert height to meters and calculate BMI
        double height_in_meters = height_cm[i] / 100.0;
        bmi[i] = calculate_bmi(weight[i], height_in_meters);
    }

    // Calculate and display average BMI
    double avg_bmi = calculate_average_bmi(bmi, MAX_PATIENTS);
    printf("\nAverage BMI: %.2f\n", avg_bmi);

    // Count males and females
    int male_count, female_count;
    count_gender(gender, MAX_PATIENTS, &male_count, &female_count);
    printf("Number of Males: %d\n", male_count);
    printf("Number of Females: %d\n", female_count);

    // Count patients with BMI over 25
    int bmi_over_25_count = count_bmi_over_25(bmi, MAX_PATIENTS);
    printf("Number of Patients with BMI over 25: %d\n", bmi_over_25_count);

    // Save data to CSV files
    save_to_csv("first_name.csv", first_name, MAX_PATIENTS);
    save_to_csv("last_name.csv", last_name, MAX_PATIENTS);
    save_to_csv_numbers("age.csv", age, MAX_PATIENTS);
    save_to_csv_doubles("height.csv", height_cm, MAX_PATIENTS); // Save height in cm
    save_to_csv_doubles("weight.csv", weight, MAX_PATIENTS);
    save_to_csv_doubles("bmi.csv", bmi, MAX_PATIENTS);

    return 0;
}
