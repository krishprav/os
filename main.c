#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "part1.h" // The header file for part 1
#include "part2.h" // The header file for part 2
#include "part3.h" // The header file for part 3
#include "part4.h" // The header file for part 4

// The main function of the program
int main(int argc, char *argv[]) {
    
    // Initialize some variables for input and choice
    char input[20];
    int choice;
    
    // Display a welcome message
    printf("Welcome to the DAC system. This program demonstrates how to control user access using discretionary access control.\n");
    
    // Check if the directory path is given as a command line argument
    if (argc != 2) {
        printf("Please provide the directory path as a command line argument.\n");
        exit(1);
    }
    
    // Loop until exit option is chosen
    while (1) {
        // Display the menu options
        display_menu();
        
        // Get the user input
        printf("Please enter your choice: ");
        scanf("%s", input);
        
        // Convert the input to an integer
        choice = atoi(input);
        
        // Perform different actions based on the choice
        switch (choice) {
            case 1:
                list_files(argv[1]); // Call the function from part1.h
                break;
            case 2:
                store_and_display_matrix(); // Call the function from part2.h
                break;
            case 3:
                list_files_by_owner(); // Call the function from part3.h
                break;
            case 4:
                display_owner_and_group(); // Call the function from part4.h
                break;
            case 5:
                change_file_permission(); // Call the function from part4.h
                break;
            case 6:
                printf("Thank you for using the DAC system. Goodbye.\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    
    return 0;
}